/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "avmshell.h"
#include "zlib.h"
#include "TamarinProfile.h"
#include "TamarinStaticAnalyzer.h"
#include "SWFFile.h"
namespace avmshell
{
    // it's silly to write this again, but i'm being lazy.
    class SwfParser {
        int bitPos;
        int bitBuf;
    public:
        avmplus::ScriptBuffer swf;
        uint32_t pos;
        SwfParser(avmplus::ScriptBuffer swf)
            : bitPos(0)
            , bitBuf(0)
            , swf(swf)
            , pos(0)
        {
        }

        void skipHeader() {
            // skip rect
            int n = readUBits(5);
            readUBits(n); // xmin
            readUBits(n); // xmax
            readUBits(n); // ymin
            readUBits(n); // ymax

            // skip frame rate and frame count
            pos += 4;
        }

        int readU8() {
            return swf[pos++];
        }
        int readU16() {
            return readU8() | readU8()<<8;
        }
        uint32_t readU32() {
            return readU8() | readU8()<<8 | readU8()<<16 | readU8()<<24;
        }

        uint32_t readU30(int &valueLength)
        {
            valueLength = 0;
            uint32_t tmppos = pos;
            unsigned int result = swf[tmppos];
            if (!(result & 0x00000080))
            {
                valueLength++;
                return result;
            }
            result = (result & 0x0000007f) | swf[tmppos+1]<<7;
            if (!(result & 0x00004000))
            {
                valueLength += 2;
                return result;
            }
            result = (result & 0x00003fff) | swf[tmppos+2]<<14;
            if (!(result & 0x00200000))
            {
                valueLength += 3;
                return result;
            }
            result = (result & 0x001fffff) | swf[tmppos+3]<<21;
            if (!(result & 0x10000000))
            {
                valueLength += 4;
                return result;
            }
            result = (result & 0x0fffffff) | swf[tmppos+4]<<28;
            valueLength += 5;
            return result;
        }

        void fillBitBuf() {
            bitBuf = readU8();
            bitPos = 8;
        }

        int readUBits(int n) {
            if (n == 0)
                return 0;
            int bitsLeft = n;
            int result = 0;
            if (!bitPos)
                fillBitBuf();
            int shift;
            for (shift = bitsLeft - bitPos; shift > 0; shift = bitsLeft - bitPos) {
                result |= bitBuf << shift;
                bitsLeft -= bitPos;
                fillBitBuf();
            }
            // consume part of buffer
            result |= bitBuf >> -shift;
            bitPos -= bitsLeft;
            bitBuf &= 0xff >> (8 - bitPos); // mask consumed bits
            return result;
        }

        int readSBits(int n) {
            AvmAssert(n <= 32);
            int num = readUBits(n);
            int shift = 32 - n;
            return (num << shift) >> shift; // sign extend
        }

        void skipString() {
            while (readU8() != 0)
            {}
        }
    };

    /**
     * isSwf() - return true if the swf magic # is present, ignoring version.
     */
    bool isSwf(avmplus::ScriptBuffer swf) {
        if (swf.getSize() < 4)
            return false;
        uint32_t magic = swf[0] | swf[1]<<8 | swf[2]<<16;
        const uint32_t SWF = 'S'<<16 | 'W'<<8 | 'F';
        const uint32_t SWC = 'S'<<16 | 'W'<<8 | 'C';
        const uint32_t ZWS = 'S'<<16 | 'W'<<8 | 'Z';
        return magic == SWF || magic == SWC || magic == ZWS;
    }

    static const int stagDoABC  = 72;
    static const int stagDoABC2 = 82;

    static void handleDoABC(int type, SwfParser &parser, int taglen,
                  avmplus::Toplevel* toplevel, avmplus::CodeContext* codeContext,
                  avmplus::GCList<avmplus::PoolObject>& deferred)
    {
        TAMARIN_PROFILE_FUNCTION;
        avmplus::AvmCore *core = toplevel->core();
        int tagstart = parser.pos;
        const int kDoAbcLazyInitializeFlag = 1;
        uint32_t flags = 0;

        if (type == stagDoABC2)
        {
            // Flags (UI32) A 32-bit flags value, which may
            // contain the following bits set: kDoAbcLazyInitializeFlag = 1: Indicates that
            // the ABC block should not be executed immediately, but only parsed. A later
            // finddef may cause its scripts to execute.
            flags = parser.readU32();

            // skip the abc name
            parser.skipString();
        }

        // parse and execute the abc.

        // allocate a new buffer and copy abc into it; the abc buffer will be referenced
        // by PoolObject and can outlive the swf it came from.  Using a ReadOnlyScriptBuffer
        // avoids copying, but interior pointers to the swf data do not pin the swf in memory.
        int abclen = taglen - (parser.pos - tagstart);
        avmplus::ScriptBuffer code(core->newScriptBuffer(abclen));
        VMPI_memcpy(&code[0], &parser.swf[parser.pos], abclen);

        // FIXME get api from the SWF
        avmplus::ApiVersion apiVersion = core->getApiVersionFromCallStack();

        // TODO: just parse because we are using Tamarin for static analysis only.
        if (flags & kDoAbcLazyInitializeFlag) {
            avmplus::PoolObject* pool = core->parseActionBlock(code, 0, toplevel, codeContext->domainEnv()->domain(), NULL, apiVersion);
            deferred.add(pool);
            // defer: handleActionPool(pool/* result of parse */, domainEnv, toplevel, codeContext);
        } else {
            core->handleActionBlock(code, 0, toplevel, NULL, codeContext, apiVersion);
        }
        parser.pos += abclen;
    }

    /*
     * Execute a swf as follows:
     * skip the header
     * for each DoABC2 tag
     *   if lazy, parse it but don't run it:  parseActionBlock()
     * else
     *   run it via handleActionBlock() just as if it were on the commandline
     */
    bool handleSwf(const char *filename, avmplus::ScriptBuffer swf,
                   avmplus::Toplevel* toplevel, avmplus::CodeContext* codeContext,
                   bool test_only, uint32_t file_size)
    {
        TAMARIN_PROFILE_FUNCTION;
        bool has_abc = false;
        SwfParser parser(swf);
        parser.pos = 4; // skip magic #
        uint32_t swflen = parser.readU32();
        avmplus::AvmCore *core = toplevel->core();
        avmplus::GCList<avmplus::PoolObject> deferred(core->gc, avmplus::kListInitialCapacity);
        if (swf[0] == 'C') {
            // decompress the swf
            swflen -= 8;
            avmplus::ScriptBuffer newswf(core->newScriptBuffer(swflen));
            size_t dlen = (size_t)swflen;
            size_t outLen = (size_t)(swf.getSize()-8);

            if (!SWF::File::decompress((unsigned char*)&swf[8], outLen, 
                    (unsigned char*)&newswf[0],
                    dlen)){
                if (!test_only)
                    core->console << filename << ": error decompressing CWS"  << "\n";
                return false;
            }
            swf = newswf;
            parser = SwfParser(newswf);
            parser.pos = 0;
        } else if (swf[0] == 'Z') {
			file_size -= 12;
            avmplus::ScriptBuffer newswf(core->newScriptBuffer(swflen));
            size_t maybe_length = swflen;
            if(!SWF::File::lzma_decompress((unsigned char*)&swf[12], file_size, (unsigned char*)&newswf[0], maybe_length)) {
				docode::TamarinStaticAnalyzer* analyzer = docode::TamarinStaticAnalyzer::GetInstance();
				
                core->console << "LZMA Decompress Error!" << "\n";
                if (maybe_length <= 0) {
                    core->console << "Decompressed data length is too small." << "\n";
					analyzer->isuncompressfail = true;
					return false;
                }
                
            } 
            swf = newswf;
            parser = SwfParser(newswf);
            parser.pos = 0;
        }
        if (swflen != swf.getSize()) {
            docode::TamarinStaticAnalyzer* analyzer = docode::TamarinStaticAnalyzer::GetInstance();
           // if (analyzer) {
               // analyzer->IncorrectSwfFileLen();
           // }
            if (!test_only)
                core->console << filename <<
                    ": incorrect size: " << (uint32_t)swf.getSize() <<
                    " should be " << swflen << "\n";
			//analyzer->isdecodefail = true;
			//return false;
        }
        parser.skipHeader();
        uint32_t oldpos = parser.pos;
        uint32_t newpos = parser.pos;
        while (parser.pos < swflen) {
            int tag = parser.readU16();
            int type = tag >> 6;
            uint32_t taglen = (tag & 63);
            if (taglen == 63)
                taglen = parser.readU32();
            if (type == stagDoABC || type == stagDoABC2) {
                has_abc = true;
                docode::TamarinStaticAnalyzer* instance = docode::TamarinStaticAnalyzer::GetInstance();
                if (instance) {
                   // instance->SetAs3FileFlag(has_abc);
                }

                docode::TamarinStaticAnalyzer* analyzer = docode::TamarinStaticAnalyzer::GetInstance();
                if (analyzer) {
                    //analyzer->OutPutAS2BYTECODE((const char *)(parser.swf.getBuffer() + parser.pos), taglen);
                }

                if (!test_only) {
                    try{
                        newpos = parser.pos + taglen;
                        handleDoABC(type, parser, taglen, toplevel, codeContext, deferred);
                    }
                    catch(...)
                    {
                        //fprintf(stderr, "Throw exception in handleDoABC\n");
                        parser.pos = newpos;
                    }
                }
            }
            else if (type == 0x56 && taglen >= 4)
            {
                int Conutlength = 0;
                uint32_t sceneCount = parser.readU30(Conutlength);
                //fprintf(stderr, "sceneCount %u\n", sceneCount);
                if ( sceneCount >= 0x3fffffff ) {
                    docode::TamarinStaticAnalyzer* analyzer = docode::TamarinStaticAnalyzer::GetInstance();
                    if (analyzer) {
                        std::string msg("swf_parser_cve_2007_0071");
                       // analyzer->OutPutBehavior(msg, true);
                    }
                }
                parser.pos += taglen;
            }
            else
                parser.pos += taglen;

            if (parser.pos <= oldpos) {
                has_abc = false;    // broken file or broken parser, but either way we can't process it
                break;
            }
            oldpos = parser.pos;
        }
        if (!test_only) {
            /*for (int i = 0, n = deferred.length(); i < n; i++) {
                core->handleActionPool(deferred[i], toplevel, codeContext);
            }*/
        }
        docode::TamarinStaticAnalyzer* instance = docode::TamarinStaticAnalyzer::GetInstance();
        if (instance && !has_abc) {
           // instance->NoAbcInSwf();
        }
        return has_abc;
    }
}
