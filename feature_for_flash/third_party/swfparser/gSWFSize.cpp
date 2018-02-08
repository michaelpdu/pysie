

#include "SWF.h"
#include <cstring>

namespace SWF {

size_t Rectangle::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	r += 5;

	r += bits;

	r += bits;

	r += bits;

	r += bits;

	if( r%8 != 0 ) r += 8-(r%8);


//	printf("Rectangle sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


size_t UnknownFilter::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += len * 8;


	r += Filter::getHeaderSize( r-start_at );
//	printf("UnknownFilter sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


size_t UnknownTag::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += len * 8;


	r += Tag::getHeaderSize( r-start_at );
//	printf("UnknownTag sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t End::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Tag::getHeaderSize( r-start_at );
//	printf("End sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


size_t DoAction::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		Action* item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


	r += Tag::getHeaderSize( r-start_at );
//	printf("DoAction sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


size_t Export::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 16;

	{
		Symbol* item;
		ListItem<Symbol>* i;
		i = symbols.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


	r += Tag::getHeaderSize( r-start_at );
//	printf("Export sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Import::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
		
		r += ((url ? strlen( url ) : 0)+bytes)*8;
	}

	r += 16;

	{
		Symbol* item;
		ListItem<Symbol>* i;
		i = symbols.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


	r += Tag::getHeaderSize( r-start_at );
//	printf("Import sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t DoInitAction::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 16;

	{
		Action* item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


	r += Tag::getHeaderSize( r-start_at );
//	printf("DoInitAction sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


size_t ScriptLimits::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 16;

	r += 16;


	r += Tag::getHeaderSize( r-start_at );
//	printf("ScriptLimits sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


size_t ImportAssets2::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
		
		r += ((url ? strlen( url ) : 0)+bytes)*8;
	}

	r += 8;

	r += 8;

	r += 16;

	{
		Symbol* item;
		ListItem<Symbol>* i;
		i = symbols.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


	r += Tag::getHeaderSize( r-start_at );
//	printf("ImportAssets2 sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t FileAttributes::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 3;

	r++;

	if( ctx->swfVersion < 9 ) {
		
	r += 3;

	}

	if( ctx->swfVersion >= 9 ) {
		
	r++;

	r++;

	r++;

	}

	r++;

	r += 24;


	r += Tag::getHeaderSize( r-start_at );
//	printf("FileAttributes sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


size_t Metadata::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += ((RDF ? strlen( RDF ) : 0)+1)*8;


	r += Tag::getHeaderSize( r-start_at );
//	printf("Metadata sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


size_t DoABC::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += actions.getSize(ctx,r);


	r += Tag::getHeaderSize( r-start_at );
//	printf("DoABC sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t DoABCDefine::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 32;

	{
		int bytes = 1;
		
		r += ((name ? strlen( name ) : 0)+bytes)*8;
	}

	r += actions.getSize(ctx,r);


	r += Tag::getHeaderSize( r-start_at );
//	printf("DoABCDefine sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t SymbolClass::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 16;

	{
		Symbol* item;
		ListItem<Symbol>* i;
		i = symbols.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


	r += Tag::getHeaderSize( r-start_at );
//	printf("SymbolClass sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


size_t DefineBinaryData::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 16;

	r += 32;

	r += data.getSize(ctx,r);


	r += Tag::getHeaderSize( r-start_at );
//	printf("DefineBinaryData sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


size_t EnableDebugger::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
		
		r += ((password ? strlen( password ) : 0)+bytes)*8;
	}


	r += Tag::getHeaderSize( r-start_at );
//	printf("EnableDebugger sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t EnableDebugger2::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 16;

	{
		int bytes = 1;
		
		r += ((password ? strlen( password ) : 0)+bytes)*8;
	}


	r += Tag::getHeaderSize( r-start_at );
//	printf("EnableDebugger2 sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t StackString::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
		
		r += ((value ? strlen( value ) : 0)+bytes)*8;
	}


	r += StackItem::getHeaderSize( r-start_at );
//	printf("StackString sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t StackFloat::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 32;


	r += StackItem::getHeaderSize( r-start_at );
//	printf("StackFloat sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t StackNull::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += StackItem::getHeaderSize( r-start_at );
//	printf("StackNull sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t StackUndefined::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += StackItem::getHeaderSize( r-start_at );
//	printf("StackUndefined sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t StackRegister::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 8;


	r += StackItem::getHeaderSize( r-start_at );
//	printf("StackRegister sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t StackBoolean::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 8;


	r += StackItem::getHeaderSize( r-start_at );
//	printf("StackBoolean sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t StackDouble::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 64;


	r += StackItem::getHeaderSize( r-start_at );
//	printf("StackDouble sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t StackInteger::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 32;


	r += StackItem::getHeaderSize( r-start_at );
//	printf("StackInteger sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t StackDictionaryLookup::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 8;


	r += StackItem::getHeaderSize( r-start_at );
//	printf("StackDictionaryLookup sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t StackLargeDictionaryLookup::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 16;


	r += StackItem::getHeaderSize( r-start_at );
//	printf("StackLargeDictionaryLookup sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t UnknownAction::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += len * 8;


	r += Action::getHeaderSize( r-start_at );
//	printf("UnknownAction sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t EndAction::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("EndAction sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


size_t AddCast::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("AddCast sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Substract::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("Substract sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Mulitply::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("Mulitply sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Divide::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("Divide sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t EqualCast::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("EqualCast sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t LessThanCast::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("LessThanCast sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t LogicalAND::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("LogicalAND sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t LogicalOR::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("LogicalOR sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t LogicalNOT::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("LogicalNOT sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t StringEqual::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("StringEqual sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t StringLength::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("StringLength sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t SubString::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("SubString sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Pop::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("Pop sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t IntegralPart::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("IntegralPart sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t GetVariable::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("GetVariable sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t SetVariable::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("SetVariable sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t SetTargetDynamic::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("SetTargetDynamic sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t ConcatenateString::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("ConcatenateString sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t GetProperty::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("GetProperty sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t SetProperty::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("SetProperty sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t DuplicateSprite::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("DuplicateSprite sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t RemoveSprite::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("RemoveSprite sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Trace::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("Trace sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


size_t StringLessThan::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("StringLessThan sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Throw::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("Throw sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t CastObject::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("CastObject sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Implements::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("Implements sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Random::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("Random sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t MultibyteStringLength::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("MultibyteStringLength sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t ORD::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("ORD sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t CHR::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("CHR sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t GetTimer::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("GetTimer sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t MultibyteSubString::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("MultibyteSubString sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t MultibyteORD::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("MultibyteORD sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t MultibyteCHR::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("MultibyteCHR sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Delete::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("Delete sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t DeleteAll::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("DeleteAll sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t SetLocalVariable::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("SetLocalVariable sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t CallFunction::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("CallFunction sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Return::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("Return sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Modulo::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("Modulo sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t New::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("New sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t DeclareLocalVariable::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("DeclareLocalVariable sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t DeclareArray::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("DeclareArray sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t DeclareObject::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("DeclareObject sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t TypeOf::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("TypeOf sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t GetTarget::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("GetTarget sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Enumerate::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("Enumerate sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t AddTyped::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("AddTyped sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t LessThanTyped::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("LessThanTyped sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t EqualTyped::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("EqualTyped sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t DefineNumber::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("DefineNumber sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t DefineString::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("DefineString sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Duplicate::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("Duplicate sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Swap::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("Swap sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t GetMember::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("GetMember sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t SetMember::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("SetMember sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Increment::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("Increment sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Decrement::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("Decrement sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t CallMethod::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("CallMethod sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t NewMethod::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("NewMethod sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t InstanceOf::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("InstanceOf sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t EnumerateObject::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("EnumerateObject sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t AND::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("AND sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OR::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("OR sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t XOR::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("XOR sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t ShiftLeft::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("ShiftLeft sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t ShiftRight::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("ShiftRight sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t ShiftRightUnsigned::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("ShiftRightUnsigned sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t StrictEqual::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("StrictEqual sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t GreaterThanTyped::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("GreaterThanTyped sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t StringGreaterThan::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("StringGreaterThan sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Extends::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("Extends sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t GotoFrame::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 16;


	r += Action::getHeaderSize( r-start_at );
//	printf("GotoFrame sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t GetURL::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
		
		r += ((url ? strlen( url ) : 0)+bytes)*8;
	}

	{
		int bytes = 1;
		
		r += ((target ? strlen( target ) : 0)+bytes)*8;
	}


	r += Action::getHeaderSize( r-start_at );
//	printf("GetURL sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t StoreRegister::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 8;


	r += Action::getHeaderSize( r-start_at );
//	printf("StoreRegister sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Dictionary::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 16;

	{
		String* item;
		ListItem<String>* i;
		i = strings.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


	r += Action::getHeaderSize( r-start_at );
//	printf("Dictionary sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t WaitForFrame::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 16;

	r += 8;


	r += Action::getHeaderSize( r-start_at );
//	printf("WaitForFrame sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t SetTarget::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
		
		r += ((label ? strlen( label ) : 0)+bytes)*8;
	}


	r += Action::getHeaderSize( r-start_at );
//	printf("SetTarget sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t GotoLabel::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
		
		r += ((label ? strlen( label ) : 0)+bytes)*8;
	}


	r += Action::getHeaderSize( r-start_at );
//	printf("GotoLabel sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t WaitForFrameDynamic::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 16;

	r += 8;


	r += Action::getHeaderSize( r-start_at );
//	printf("WaitForFrameDynamic sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t DeclareFunction2::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
		
		r += ((name ? strlen( name ) : 0)+bytes)*8;
	}

	r += 16;

	r += 8;

	r++;

	r++;

	r++;

	r++;

	r++;

	r++;

	r++;

	r++;

	r += 7;

	r++;

	{
		Parameter* item;
		ListItem<Parameter>* i;
		i = args.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	r += 16;

	{
		Action* item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


	r += Action::getHeaderSize( r-start_at );
//	printf("DeclareFunction2 sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Try::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 5;

	r++;

	r++;

	r++;

	r += 16;

	r += 16;

	r += 16;

	if( catchInRegister ) {
		
		
	r += 8;

	}


	r += Action::getHeaderSize( r-start_at );
//	printf("Try sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t With::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 16;


	r += Action::getHeaderSize( r-start_at );
//	printf("With sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t PushData::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		StackItem* item;
		ListItem<StackItem>* i;
		i = items.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


	r += Action::getHeaderSize( r-start_at );
//	printf("PushData sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t GetURL2::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 8;


	r += Action::getHeaderSize( r-start_at );
//	printf("GetURL2 sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t DeclareFunction::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
		
		r += ((name ? strlen( name ) : 0)+bytes)*8;
	}

	r += 16;

	{
		String* item;
		ListItem<String>* i;
		i = args.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	r += 16;


	r += Action::getHeaderSize( r-start_at );
//	printf("DeclareFunction sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t BranchAlways::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 16;


	r += Action::getHeaderSize( r-start_at );
//	printf("BranchAlways sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t BranchIfTrue::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 16;


	r += Action::getHeaderSize( r-start_at );
//	printf("BranchIfTrue sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t CallFrame::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += Action::getHeaderSize( r-start_at );
//	printf("CallFrame sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t GotoExpression::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 8;


	r += Action::getHeaderSize( r-start_at );
//	printf("GotoExpression sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t PrivateNamespace::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; index > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += NamespaceConstant::getHeaderSize( r-start_at );
//	printf("PrivateNamespace sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Namespace::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; index > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += NamespaceConstant::getHeaderSize( r-start_at );
//	printf("Namespace sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t PackageNamespace::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; index > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += NamespaceConstant::getHeaderSize( r-start_at );
//	printf("PackageNamespace sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t PackageInternalNamespace::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; index > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += NamespaceConstant::getHeaderSize( r-start_at );
//	printf("PackageInternalNamespace sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t ProtectedNamespace::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; index > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += NamespaceConstant::getHeaderSize( r-start_at );
//	printf("ProtectedNamespace sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t ExplicitNamespace::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; index > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += NamespaceConstant::getHeaderSize( r-start_at );
//	printf("ExplicitNamespace sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t MultinameLNamespace::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; index > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += NamespaceConstant::getHeaderSize( r-start_at );
//	printf("MultinameLNamespace sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t QName::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; namespaceIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; nameIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += MultinameConstant::getHeaderSize( r-start_at );
//	printf("QName sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t QNameA::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; namespaceIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; nameIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += MultinameConstant::getHeaderSize( r-start_at );
//	printf("QNameA sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Multiname::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; nameIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; namespaceSetIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += MultinameConstant::getHeaderSize( r-start_at );
//	printf("Multiname sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t MultinameA::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; nameIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; namespaceSetIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += MultinameConstant::getHeaderSize( r-start_at );
//	printf("MultinameA sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t RTQName::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; nameIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += MultinameConstant::getHeaderSize( r-start_at );
//	printf("RTQName sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t RTQNameA::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; nameIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += MultinameConstant::getHeaderSize( r-start_at );
//	printf("RTQNameA sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t MultinameL::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; namespaceSetIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += MultinameConstant::getHeaderSize( r-start_at );
//	printf("MultinameL sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t RTQNameL::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += MultinameConstant::getHeaderSize( r-start_at );
//	printf("RTQNameL sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t RTQNameLA::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += MultinameConstant::getHeaderSize( r-start_at );
//	printf("RTQNameLA sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t TypeName::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; nameIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; nameCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		U30* item;
		ListItem<U30>* i;
		i = types.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


	r += MultinameConstant::getHeaderSize( r-start_at );
//	printf("TypeName sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Slot::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; slotID > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; typeIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; valueIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	if( valueIndex != 0 ) {
		
	r += 8;

	}


	r += Trait::getHeaderSize( r-start_at );
//	printf("Slot sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Const::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; slotID > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; typeIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; valueIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	if( valueIndex != 0 ) {
		
	r += 8;

	}


	r += Trait::getHeaderSize( r-start_at );
//	printf("Const sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Method::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; dispID > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; methodInfo > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += Trait::getHeaderSize( r-start_at );
//	printf("Method sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Getter::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; dispID > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; methodInfo > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += Trait::getHeaderSize( r-start_at );
//	printf("Getter sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Setter::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; dispID > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; methodInfo > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += Trait::getHeaderSize( r-start_at );
//	printf("Setter sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Class::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; slotID > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; classInfo > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += Trait::getHeaderSize( r-start_at );
//	printf("Class sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Function::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; slotID > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; methodInfo > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += Trait::getHeaderSize( r-start_at );
//	printf("Function sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t UnknownOpCode::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += len * 8;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("UnknownOpCode sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpBkPt::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpBkPt sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpNop::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpNop sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpThrow::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpThrow sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpGetSuper::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpGetSuper sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpSetSuper::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpSetSuper sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpDXNs::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; dxns > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpDXNs sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpDXNsLate::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpDXNsLate sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpKill::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; address > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpKill sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpLabel::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpLabel sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIfNlt::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 24;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIfNlt sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIfNle::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 24;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIfNle sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIfNgt::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 24;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIfNgt sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIfNge::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 24;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIfNge sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpJump::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 24;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpJump sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIfTrue::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 24;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIfTrue sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIfFalse::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 24;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIfFalse sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIfEq::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 24;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIfEq sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIfNe::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 24;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIfNe sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIfLt::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 24;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIfLt sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIfLe::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 24;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIfLe sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIfGt::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 24;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIfGt sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIfGe::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 24;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIfGe sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIfStrictEq::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 24;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIfStrictEq sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIfStrictNe::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 24;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIfStrictNe sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpLookupSwitch::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 24;

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; caseCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		S24* item;
		ListItem<S24>* i;
		i = targetTable.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpLookupSwitch sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpPushWith::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpPushWith sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpPopScope::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpPopScope sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpNextName::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpNextName sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpHasNext::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpHasNext sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpPushNull::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpPushNull sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpPushUndefined::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpPushUndefined sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpNextValue::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpNextValue sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpPushByte::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 8;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpPushByte sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpPushShort::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; value > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpPushShort sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpPushTrue::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpPushTrue sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpPushFalse::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpPushFalse sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpPushNaN::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpPushNaN sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpPop::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpPop sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpDup::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpDup sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpSwap::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpSwap sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpPushString::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; index > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpPushString sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpPushInt::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; index > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpPushInt sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpPushUInt::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; index > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpPushUInt sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpPushDouble::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; index > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpPushDouble sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpPushScope::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpPushScope sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpPushNamespace::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; index > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpPushNamespace sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpHasNext2::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; object > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; index > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpHasNext2 sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpNewFunction::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; index > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpNewFunction sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpCall::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; argc > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpCall sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpConstruct::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; argc > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpConstruct sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpCallMethod::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; dispID > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; argc > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpCallMethod sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpCallStatic::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; methodID > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; argc > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpCallStatic sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpCallSuper::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; argc > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpCallSuper sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpCallProperty::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; argc > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpCallProperty sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpReturnVoid::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpReturnVoid sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpReturnValue::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpReturnValue sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpConstructSuper::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; argc > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpConstructSuper sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpConstructProp::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; argc > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpConstructProp sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpCallPropLex::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; argc > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpCallPropLex sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpCallSuperVoid::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; argc > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpCallSuperVoid sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpCallPropVoid::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; argc > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpCallPropVoid sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpApplyType::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; type > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpApplyType sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpNewObject::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; argc > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpNewObject sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpNewArray::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; argc > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpNewArray sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpNewActivation::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpNewActivation sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpNewClass::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; classIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpNewClass sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpGetDescendants::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpGetDescendants sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpNewCatch::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; exceptionIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpNewCatch sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpFindPropStrict::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpFindPropStrict sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpFindProperty::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpFindProperty sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpFindDef::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpFindDef sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpGetLex::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpGetLex sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpSetProperty::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpSetProperty sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpGetLocal::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; address > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpGetLocal sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpSetLocal::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; address > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpSetLocal sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpGetGlobalScope::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpGetGlobalScope sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpGetScopeObject::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 8;


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpGetScopeObject sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpGetProperty::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpGetProperty sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpInitProperty::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpInitProperty sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpDeleteProperty::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpDeleteProperty sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpGetSlot::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; slotID > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpGetSlot sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpSetSlot::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; slotID > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpSetSlot sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpGetGlobalSlot::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; slotID > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpGetGlobalSlot sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpSetGlobalSlot::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; slotID > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpSetGlobalSlot sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpConvertS::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpConvertS sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpEscXelem::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpEscXelem sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpEscXattr::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpEscXattr sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpConvertI::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpConvertI sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpConvertU::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpConvertU sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpConvertD::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpConvertD sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpConvertB::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpConvertB sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpConvertO::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpConvertO sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpCheckFilter::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpCheckFilter sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpCoerce::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpCoerce sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpCoerceB::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpCoerceB sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpCoerceA::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpCoerceA sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpCoerceI::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpCoerceI sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpCoerceD::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpCoerceD sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpCoerceS::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpCoerceS sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpAsType::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpAsType sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpAsTypeLate::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpAsTypeLate sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpCoerceU::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpCoerceU sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpCoerceO::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpCoerceO sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpNegate::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpNegate sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIncrement::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIncrement sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIncLocal::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; address > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIncLocal sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpDecrement::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpDecrement sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpDecLocal::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; address > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpDecLocal sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpTypeOf::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpTypeOf sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpNot::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpNot sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpBitNot::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpBitNot sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpAdd::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpAdd sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpSubtract::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpSubtract sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpMultiply::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpMultiply sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpDivide::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpDivide sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpModulo::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpModulo sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpLShift::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpLShift sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpRShift::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpRShift sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpURShift::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpURShift sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpBitAnd::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpBitAnd sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpBitOr::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpBitOr sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpBitXor::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpBitXor sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpEquals::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpEquals sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpStrictEquals::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpStrictEquals sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpLessThan::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpLessThan sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpLessEquals::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpLessEquals sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpGreaterThan::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpGreaterThan sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpGreaterEquals::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpGreaterEquals sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpInstanceOf::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpInstanceOf sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIsType::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIsType sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIsTypeLate::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIsTypeLate sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIn::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIn sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIncrementI::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIncrementI sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpDecrementI::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpDecrementI sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpIncLocalI::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; address > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpIncLocalI sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpDecLocalI::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; address > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpDecLocalI sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpNegateI::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpNegateI sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpAddI::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpAddI sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpSubtractI::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpSubtractI sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpMultiplyI::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpMultiplyI sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpGetLocal0::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpGetLocal0 sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpGetLocal1::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpGetLocal1 sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpGetLocal2::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpGetLocal2 sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpGetLocal3::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpGetLocal3 sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpSetLocal0::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpSetLocal0 sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpSetLocal1::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpSetLocal1 sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpSetLocal2::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpSetLocal2 sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpSetLocal3::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpSetLocal3 sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpDebugReg::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	r += 8;

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; reg > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; line > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpDebugReg sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpDebugLine::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; line > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpDebugLine sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpDebugFile::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; file > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpDebugFile sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpBkPtLine::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; line > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpBkPtLine sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t OpTimestamp::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;
	

	r += OpCode::getHeaderSize( r-start_at );
//	printf("OpTimestamp sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


size_t String::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	{
		int bytes = 1;
		
		r += ((value ? strlen( value ) : 0)+bytes)*8;
	}


//	printf("String sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t String2::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	{
		int bytes = 1;
		
			if( value ) {
				int len = strlen( value );
				uint32_t limit = 0x80;
				for(; len > limit - 1; limit *= 0x80) {
					bytes++;
				}
			}
		
		r += ((value ? strlen( value ) : 0)+bytes)*8;
	}


//	printf("String2 sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


size_t Header::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	//Rectangle
//	r += size.getSize(ctx,r);

	r += 16;

	r += 16;

	{
		Tag* item;
		ListItem<Tag>* i;
		i = tags.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


//	printf("Header sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}



size_t Symbol::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	r += 16;

	{
		int bytes = 1;
		
		r += ((name ? strlen( name ) : 0)+bytes)*8;
	}


//	printf("Symbol sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


size_t Parameter::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	r += 8;

	{
		int bytes = 1;
		
		r += ((name ? strlen( name ) : 0)+bytes)*8;
	}


//	printf("Parameter sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t UChar::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	r += 8;


//	printf("UChar sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t UShort::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	r += 16;


//	printf("UShort sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t ULong::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	r += 32;


//	printf("ULong sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Short::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	r += 16;


//	printf("Short sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Float::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	r += 32;


//	printf("Float sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Double::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	r += 64;


//	printf("Double sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Kerning::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	r += 8;

	r += 8;

	r += 16;


//	printf("Kerning sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t WideKerning::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	r += 16;

	r += 16;

	r += 16;


//	printf("WideKerning sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


size_t Event::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	if( r%8 != 0 ) r += 8-(r%8);

	r += 16;

	if( ctx->swfVersion>=6 ) {
		
	r += 16;

	}

	if( (flags1 | flags2) ) {
		
	r += 32;

	{
		Action* item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	}


//	printf("Event sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


size_t U30::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; value > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


//	printf("U30 sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t S24::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	r += 24;


//	printf("S24 sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t ValueKind::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; index > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	r += 8;


//	printf("ValueKind sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t MethodInfo::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; paramCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; retType > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		U30* item;
		ListItem<U30>* i;
		i = paramTypes.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; nameIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	r++;

	r++;

	r++;

	r++;

	r++;

	r++;

	r++;

	r++;

	if( hasOptional ) {
		
		
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; optionalCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		ValueKind* item;
		ListItem<ValueKind>* i;
		i = optional.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	}

	if( hasParamNames ) {
		
		
	{
		U30* item;
		ListItem<U30>* i;
		i = paramNames.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	}


//	printf("MethodInfo sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t MetadataInfo::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; nameIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; valuesCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		U30* item;
		ListItem<U30>* i;
		i = keys.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	{
		U30* item;
		ListItem<U30>* i;
		i = values.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


//	printf("MetadataInfo sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t NamespaceSet::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; count > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		U30* item;
		ListItem<U30>* i;
		i = namespaces.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


//	printf("NamespaceSet sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t TraitInfo::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; nameIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	r++;

	r++;

	r++;

	r++;

	{
		Trait* item;
		ListItem<Trait>* i;
		i = trait.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	if( hasMetadata ) {
		
		
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; metadataCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		U30* item;
		ListItem<U30>* i;
		i = metadata.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	}


//	printf("TraitInfo sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t InstanceInfo::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; nameIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; superIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	r += 4;

	r++;

	r++;

	r++;

	r++;

	if( hasProtectedNS ) {
		
		
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; protectedNS > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; interfaceCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		U30* item;
		ListItem<U30>* i;
		i = interfaces.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; iInitIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; traitCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		TraitInfo* item;
		ListItem<TraitInfo>* i;
		i = traits.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


//	printf("InstanceInfo sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t ClassInfo::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; cInitIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; traitCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		TraitInfo* item;
		ListItem<TraitInfo>* i;
		i = traits.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


//	printf("ClassInfo sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t ScriptInfo::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; initIndex > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; traitCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		TraitInfo* item;
		ListItem<TraitInfo>* i;
		i = traits.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


//	printf("ScriptInfo sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Exception::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; tryStart > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; tryEnd > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; target > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; type > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; name > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}


//	printf("Exception sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t MethodBody::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; methodInfo > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; maxStack > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; maxRegs > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; scopeDepth > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; maxScope > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; codeLength > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		OpCode* item;
		ListItem<OpCode>* i;
		i = code.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; exceptionCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		Exception* item;
		ListItem<Exception>* i;
		i = exceptions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; traitCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		TraitInfo* item;
		ListItem<TraitInfo>* i;
		i = traits.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


//	printf("MethodBody sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Constants::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; intCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		U30* item;
		ListItem<U30>* i;
		i = ints.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; uintCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		U30* item;
		ListItem<U30>* i;
		i = uints.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; doubleCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		Double* item;
		ListItem<Double>* i;
		i = doubles.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; stringCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		String2* item;
		ListItem<String2>* i;
		i = strings.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; namespaceConstantCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		NamespaceConstant* item;
		ListItem<NamespaceConstant>* i;
		i = namespaces.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; namespaceSetCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		NamespaceSet* item;
		ListItem<NamespaceSet>* i;
		i = namespaceSets.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; multinameConstantCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		MultinameConstant* item;
		ListItem<MultinameConstant>* i;
		i = multinames.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


//	printf("Constants sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t Action3::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	r += 16;

	r += 16;

	r += constants.getSize(ctx,r);

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; methodInfoCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		MethodInfo* item;
		ListItem<MethodInfo>* i;
		i = methods.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; metadataInfoCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		MetadataInfo* item;
		ListItem<MetadataInfo>* i;
		i = metadata.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; classCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		InstanceInfo* item;
		ListItem<InstanceInfo>* i;
		i = instances.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	{
		ClassInfo* item;
		ListItem<ClassInfo>* i;
		i = classes.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; scriptCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		ScriptInfo* item;
		ListItem<ScriptInfo>* i;
		i = scripts.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	{
		int bytes = 1;
	
		uint32_t limit = 0x80;
		for(; methodBodyCount > limit - 1; limit *= 0x80) {
			bytes++;
		}

		r += bytes * 8;
	}

	{
		MethodBody* item;
		ListItem<MethodBody>* i;
		i = methodBodies.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}


//	printf("Action3 sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t ZoneData::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	r += 16;

	r += 16;


//	printf("ZoneData sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}

size_t ZoneArray::calcSize( Context *ctx, int start_at ) {
	size_t r = start_at;

	r += Item::getHeaderSize( r-start_at );

	
	r += 8;

	{
		ZoneData* item;
		ListItem<ZoneData>* i;
		i = zones.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}

	r += 1;

	r += 1;

	r += 6;


//	printf("ZoneArray sz %i bits (%.2f bytes, start %i)\n", r-start_at, ((float)r-start_at)/8, start_at );

	return r-start_at;
}


}

