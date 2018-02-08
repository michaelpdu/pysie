#include "SWFTag.h"
#include "SWF.h"
#include <cstring>

namespace SWF {

Tag *Tag::get( Reader *r, int end, Context *ctx ) {
	uint16_t h = r->getWord();
	int type = h>>6;

    //fprintf(stderr,"now processing type=[%i].\n", type );

	uint32_t len = h&0x3F;
	if( len == 0x3F ) { // long size
		len = r->getInt();
	}
	
	// sanity check, no larger than 10M
	if( len > 0xA00000 ) { 
		fprintf(stderr,"ridiculous tag size: %i, ignoring.\n", len );
//		r->setEOF();
		return NULL;
	}

	if ( len + r->getPosition() > end  ) {
		fprintf(stderr,"tag reached end of file. curr_pos=[%i],tag_len=[%i],end=[%i]\n", 
            r->getPosition(),len,end);
		return NULL;
	}

	Tag *ret = getByType( type );
	
	if( !ret ) {
		ret = new UnknownTag;
	}
	
	ret->setType( type );
	ret->setLength( len );
	ret->parse( r, r->getPosition()+len, ctx );

	return ret;
}

//void Tag::writeHeader( Writer *w, Context *ctx, size_t len ) {
////	printf("write tag %02X, len %i, recorded %i(+header, 2 or 6), position %i\n", type, len, this->len, w->getPosition() );
//	// shouldnt this be 0x3f - macromedia flash seems to use long length for > 1F...
//	len -= (len >= SWF_LONG_TAG + 6) ? 6 : 2;
//	uint16_t h = type<<6;
//	if( len >= SWF_LONG_TAG ) {
//		h |= 0x3F;
//		w->putWord(h);
//		w->putInt(len);
//	} else {
//		h |= len;
//		w->putWord(h);
//	}
//}
}
