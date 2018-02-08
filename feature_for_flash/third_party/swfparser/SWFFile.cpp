#include "SWF.h"
#include "DoABCContext.h"
#include "SWFFile.h"
#include "SWFReader.h"
#include <cstring>
#include <cstdlib>
#include "zlib.h"
#include "LzmaLib.h"

#include <iostream>

namespace SWF {

File::File() {
	// "sane" defaults
	is_uncompressed_ = true;
	swf_version_ = 7;
    body_len_ = 0;
	swf_header_ = NULL;
	body_data_ = NULL;
	fws_data_ = NULL;
	fws_data_len_ = 0;
//	maybe_cve_2007_0071_ = false;
}

File::~File() {
	delete swf_header_;
	if( body_data_ ) {
		delete[] body_data_;
		body_data_ = NULL;
	}
	if (fws_data_) {
		delete[] fws_data_;
		fws_data_ = NULL;
		fws_data_len_ = 0;
	}
}



void File::dump() {
	Context ctx;
	if( !swf_header_ ) {
		fprintf(stderr,"no SWF loaded to save\n");
		return;
	}
	ctx.swfVersion = swf_version_;
	swf_header_->dump( 2, &ctx );
}

std::vector<std::pair<std::string, std::string> > &File::GetDetections() {
	return swf_header_->getDetections();
}

Tag* File::getTag( int type ) {
	Tag *item;
	ListItem<Tag>* i;
    i = swf_header_->gettags()->first();
	while( i ) {
		item = i->data();
		if ( item ) {
			if (item->getType() == type) {
				return item;
			}
		}
		i = i->next();
	}
	return NULL;
}

int File::getTagCount( int type ) {
    int icount = 0;
    Tag *item;
    ListItem<Tag>* i;
    i = swf_header_->gettags()->first();
    while( i ) {
        item = i->data();
        if ( item ) {
            if (item->getType() == type) {
                ++icount;
            }
        }
        i = i->next();
    }
    return icount;
}

bool File::maybeCVE20070071() {
	if(swf_header_ != NULL) {
		return swf_header_->maybeCVE20070071();
	} 
	return false;
}


void File::getTags( int type, std::vector<Tag *> & vecTags ) {
	Tag *item;
	ListItem<Tag>* i;
	i = swf_header_->gettags()->first();
	while( i ) {
		item = i->data();
		if ( item ) {
			if (item->getType() == type) {
				vecTags.push_back( item );
			}
		}
		i = i->next();
	}
}



const unsigned char * File::getFileData() const {
	return body_data_;
}



uint32_t File::getFileLength() const {
	return body_len_;
}

void File::getDoABC(DoABCContext* doABC) {
	Context ctx;
	if( !swf_header_ ) {
#ifdef SWF_VERBOSE
		fprintf(stderr,"no SWF loaded to save\n");
#endif
		return;
	}
#ifdef SWF_VERBOSE
	fprintf(stderr, "In dumpDoABC, version %i, size %i, %scompressed\n", swf_version_, 
        body_len_, (is_uncompressed_?"un":"") );
#endif
	ctx.swfVersion = swf_version_;
    Tag* tag;
	ListItem<Tag>* tag_node;
	tag_node = swf_header_->gettags()->first();
    while(tag_node) {
        tag = tag_node->data();
        if(tag) {
            unsigned int tag_type = tag->getType();
            if(tag_type == 82 || tag_type == 72) {
                unsigned int do_abc_len = tag->getLength();
                unsigned int file_offset = tag->getFileOffset();
                if(do_abc_len<=0 ) {
                    continue;
                }

                if(tag_type == 72) {
                    do_abc_len += 5;
                }

                unsigned char* do_abc_data = new unsigned char[do_abc_len];
                if(!do_abc_data || !body_data_) {
                    return;
                }

                if(tag_type == 72) {
                    memset(do_abc_data,0,5);
                    memcpy(do_abc_data+5,body_data_+file_offset,do_abc_len-5);
                } else {
                    memcpy(do_abc_data,body_data_+file_offset,do_abc_len);
                }

                int abc_len = 0;
                if(tag_type == 72) {
                    abc_len = do_abc_len - 5;
                } else {
                    abc_len = do_abc_len;
                }
                doABC->setContext(do_abc_data, abc_len);
                //fprintf(stderr,"get abc context succ, len=[%i]\n",do_abc_len);

                //return;
            }
        }

        tag_node = tag_node->next();
    }
}

int File::load( const char *fileData, Context *_ctx, unsigned int fileSize ) {
	uint32_t totalSize = 0;
    uint32_t retFileLen = 0;
    Context *ctx = _ctx ? _ctx : new Context;
	Reader* stream_reader = NULL;

	if ( NULL == fileData ) goto fail;

	// check first third char
	char sig[3];
	memcpy( sig, fileData, 3 );
	if ( strncmp( sig,"CWS",2 ) && strncmp( sig,"FWS",2 ) && strncmp( sig,"ZWS",2 ) ) {
		fprintf( stderr,"ERROR: input is no SWF\n" );
		goto fail;
	}

	// get flash version
	swf_version_ = ctx->swfVersion = fileData[3];

	// get total size from [4,5,6,7]
	totalSize = (fileData[4] & 0xFF);
	totalSize += (fileData[5] & 0xFF) << 8;
	totalSize += (fileData[6] & 0xFF) << 16;
	totalSize += (fileData[7] & 0xFF) << 24;
    if (totalSize == 0) {
        fprintf( stderr,"ERROR: SWF total len is 0\n" );
        goto fail;
    }
	// 
    is_uncompressed_ = (sig[0] == 'F');
    if(is_uncompressed_) {
        if(totalSize != fileSize) {
            fprintf(stderr,"WARNING: size specified in SWF (%i) != filesize (%i), using filesize-8.\n",
                totalSize, fileSize );
        } 
        body_len_ = fileSize - 8;
        body_data_ = new(std::nothrow) unsigned char[body_len_];
        if (NULL == body_data_) {
            fprintf(stderr,"ERROR: Failed to allocate memory for SWF content! uncompress length (%i)",
                (body_len_));
            goto fail;
        }
        memcpy(body_data_,(fileData+8),body_len_);
        retFileLen = body_len_ + 8;

		// build uncompressed swf file
		fws_data_len_ = fileSize;
		fws_data_ = new unsigned char[fileSize+1];
		memset(fws_data_, '\0', fileSize+1);
		memcpy(fws_data_, fileData, fileSize);
    } else {
        if ('C' == sig[0]) {
            body_len_ = totalSize-8;
            body_data_ = new(std::nothrow) unsigned char[body_len_];
            if (NULL == body_data_) {
                fprintf(stderr,"ERROR: Failed to allocate memory for SWF content! uncompress length (%i)",
                    body_len_);
                goto fail;
            }
            memset(body_data_, '\0', body_len_);
            size_t maybe_length = body_len_;
            if(!decompress((unsigned char *)(fileData+8), fileSize - 8, body_data_, maybe_length)) {
                goto fail;
            } else {
                if(maybe_length != body_len_) {
                    fprintf(stderr,"WARNING: except length (%i) , uncompress length (%i)",
                        body_len_,maybe_length);
                }
                body_len_ = maybe_length; //do not contain the first 8 bytes
            }
            retFileLen = body_len_ + 8;
        } else if ('Z' == sig[0]) {
            body_len_ = totalSize-12;
            body_data_ = new(std::nothrow) unsigned char[body_len_];
            if (NULL == body_data_) {
                fprintf(stderr,"ERROR: Failed to allocate memory for SWF content! uncompress length (%i)",
                    body_len_);
                goto fail;
            }
            memset(body_data_, '\0', body_len_);
            size_t maybe_length = body_len_;
            if(!lzma_decompress((unsigned char *)(fileData+12), fileSize-12, body_data_, maybe_length)) {
                std::cout << "LZMA Decompress Error!" << std::endl;
                if (maybe_length <= 0) {
                    std::cout << "Decompressed data length is too small." << std::endl;
                    goto fail;
                }
            } 
            if(maybe_length != body_len_) {
                fprintf(stderr,"WARNING: except length (%i) , uncompress length (%i)",
                    body_len_,maybe_length);
            }
            body_len_ = maybe_length; //do not contain the first 12 bytes
            retFileLen = body_len_ + 12;
        } else {
            goto fail;
        }

		// build uncompressed swf file
		// 8 = "FWS"+version+'total length', 4='\x40\x00\x00\x00'
		fws_data_len_ = ('Z' == sig[0]) ? (8+body_len_+4) : (8+body_len_);

		fws_data_ = new unsigned char[fws_data_len_];
		memset(fws_data_, '\0', fws_data_len_);
		fws_data_[0] = 'F';
		fws_data_[1] = 'W';
		fws_data_[2] = 'S';
		fws_data_[3] = fileData[3];
		fws_data_[4] = fws_data_len_ & 0xFF;
		fws_data_[5] = (fws_data_len_ >> 8) & 0xFF;
		fws_data_[6] = (fws_data_len_ >> 16) & 0xFF;
		fws_data_[7] = (fws_data_len_ >> 24) & 0xFF;
		memcpy(fws_data_+8, body_data_, body_len_);
		if ('Z' == sig[0]) {
		    fws_data_[fws_data_len_-4] = 0x40;
		    fws_data_[fws_data_len_-3] = 0x00;
		    fws_data_[fws_data_len_-2] = 0x00;
		    fws_data_[fws_data_len_-1] = 0x00;
		}
    }

    stream_reader = new Reader(body_data_, body_len_);
    swf_header_ = new Header;
    swf_header_->parse( stream_reader, body_len_, ctx );
    if (!swf_header_->findEndTag()) {
        // if don't find end tag in parsing process,
        // we will save 100 byte content at the end of input content
        int copied_data_size = 128;
        if (fileSize <= copied_data_size) {
            end_content_ = std::string(fileData, fileSize);
        } else {
            end_content_ = std::string(fileData + (fileSize-copied_data_size), copied_data_size);
        }
    }

    if( stream_reader->getError() != SWFR_OK ) {
        if( stream_reader->getError() == SWFR_EOF ) {
            fprintf(stderr,"WARNING: reached EOF while reading SWF\n");
        } else {
            fprintf(stderr,"unknown error while reading SWF\n");
            goto fail;
        }
    }	
    if( stream_reader ) delete stream_reader;
    if( !_ctx && ctx ) delete ctx;
    return retFileLen;

fail:
	if( !_ctx && ctx ) delete ctx;
	return 0;

    
}

#define MAX_BUFFER 1000000

int File::getFrameCount()
{
	if (!swf_header_) return 0;
	int i=swf_header_->getframes();
	return i;
}

void File::compress( unsigned char *inputBuffer, size_t len, FILE *fp ) {
	z_stream stream;
	static unsigned char outputBuffer[ MAX_BUFFER ];
	int status, count;
	stream.avail_in = len;
	stream.next_in = inputBuffer;
	stream.next_out = outputBuffer;
	stream.zalloc = (alloc_func) NULL;
	stream.zfree = (free_func) NULL;
	stream.opaque = (voidpf) 0;
	stream.avail_out = MAX_BUFFER;
	status = deflateInit( &stream, Z_BEST_COMPRESSION );
	if( status != Z_OK ) {
		fprintf( stderr, "Error compressing SWF: %s\n", stream.msg );
		return;
	}
	while( true ) {
		if( stream.avail_in == 0 ) break;
		status = deflate( &stream, Z_NO_FLUSH );
		if( status != Z_OK ) {
			fprintf( stderr, "Error compressing SWF: %s\n", stream.msg );
			return;
		}
		count = MAX_BUFFER - stream.avail_out;
		if( count ) {
			fwrite( outputBuffer, 1, count, fp );
		}
		stream.next_out = outputBuffer;
		stream.avail_out = MAX_BUFFER;
	}
	stream.next_out = outputBuffer;
	stream.avail_out = MAX_BUFFER;
	do {
		status = deflate( &stream, Z_FINISH );
		count = MAX_BUFFER - stream.avail_out;
		if( count ) {
			fwrite( outputBuffer, 1, count, fp );
		}
		stream.next_out = outputBuffer;
		stream.avail_out = MAX_BUFFER;
	} while( status == Z_OK );

	if( status != Z_STREAM_END ) {
		fprintf( stderr, "Error compressing SWF: %s\n", stream.msg );
		deflateEnd(&stream);
		return;
	}
	status = deflateEnd(&stream);
	if( status != Z_OK ) {
		fprintf( stderr, "Error compressing SWF: %s\n", stream.msg );
	}
}

bool File::decompress(unsigned char *inputBuffer, 
        size_t inLength, 
        unsigned char *outputBuffer, 
        size_t& outLength) {
    
    if(NULL == inputBuffer || NULL == outputBuffer || inLength <= 0) {
        return false;
    }

	z_stream stream;
	int status;
	stream.avail_in = inLength;
	stream.next_in = inputBuffer;
	stream.avail_out = outLength;
	stream.next_out = outputBuffer;
	stream.zalloc = (alloc_func) NULL;
	stream.zfree = (free_func) NULL;
	stream.opaque = (voidpf) 0;
	status = inflateInit( &stream );
	if( status != Z_OK ) {
		fprintf( stderr, "Error decompressing SWF: %s\n", stream.msg );
		return false;
	}

	status = inflate( &stream, Z_SYNC_FLUSH );

    //fprintf( stderr, "[Stan]decompressing SWF length: %i\n", outLength );
    outLength = stream.total_out;

	if( status != Z_STREAM_END && status != Z_OK ) {
		fprintf( stderr, "Error decompressing SWF: %s\n", stream.msg );
		inflateEnd(&stream);
		return false;
	}

	status = inflateEnd(&stream);
	if (status != Z_OK) {
		fprintf( stderr, "Error decompressing SWF: %s\n", stream.msg );
	}

    return true;
}

bool File::lzma_decompress(unsigned char *inputBuffer,
                           size_t inLength,
                           unsigned char *outputBuffer,
                           size_t& outLength)
{
//#ifdef __linux__
//    std::cout << "LzmaUncompress is not supported on Linux." << std::endl;
//    return false;
//#else
    unsigned char props[5] = {0};
    memcpy(props, inputBuffer, 5);
    size_t size_in = inLength-5;
    int sz_ret = LzmaUncompress(outputBuffer, &outLength, inputBuffer+5, &size_in, props, 5);

    if (size_in != inLength-5) {
//         std::cout << "Warning: size_in = " << inLength-5
//             << ", real size_in = " << size_in << std::endl;
    }

    if (SZ_OK == sz_ret) {
        return true;
    } else {
        std::cout << "Error in LzmaUncompress, return code = "<< sz_ret << std::endl;
        return false;
    }
//#endif
}

}

