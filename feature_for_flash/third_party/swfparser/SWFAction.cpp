#include "SWFAction.h"
#include "SWF.h"
#include <cstring>

namespace SWF {

	//void Action::wrtieHeaderHelper(Action* this_, Writer *w, Context *ctx, size_t len ) 
	//{
	//	this_->w->putByte( this_->type );
	//	if( this_->type >= 0x80 ) {
	//		this_->w->putWord( len-=3 );
	//	}
	//}

Action *Action::get( Reader *r, int end, Context *ctx ) {
	uint16_t h = r->getByte();
	int type = h;
	int len = 0;
	if( type >= 0x80 ) {
		len = r->getWord();
	}
	
	if( type == 0 ) return( new EndAction ); // terminator
	
	Action *ret = getByType( type );
	
//	printf("ACTION %02X len %i: %p\n", type, len, ret );

	if( !ret ) {
		ret = new UnknownAction;
	}

	ret->setType( type );
	ret->setLength( len );
	ret->parse( r, r->getPosition()+len, ctx );
	
	return ret;
}	


}
