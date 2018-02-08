

#include "SWF.h"
#include "SWFItem.h"
#include "SWFList.h"


namespace SWF {

	//////////////////////////////////// Rectangle

	bool Rectangle::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Rectangle",
				r->getPosition(),
				r->getBits(),
				end );
		}

		bits = r->getNBitInt(5);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"bits",
				bits );
		}
		left = r->getNBitInt(bits,true);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"left",
				left );
		}
		right = r->getNBitInt(bits,true);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"right",
				right );
		}
		top = r->getNBitInt(bits,true);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"top",
				top );
		}
		bottom = r->getNBitInt(bits,true);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"bottom",
				bottom );
		}

		r->byteAlign();


		return r->getError() == SWFR_OK;
	}



	//////////////////////////////////// String

	bool String::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"String",
				r->getPosition(),
				r->getBits(),
				end );
		}

		value = r->getString();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %s\n",
				"value",
				value );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// String2

	bool String2::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"String2",
				r->getPosition(),
				r->getBits(),
				end );
		}

		value = r->getPStringU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %s\n",
				"value",
				value );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Header

	bool Header::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Header",
				r->getPosition(),
				r->getBits(),
				end );
		}

		//Rectangle
		size.parse(r,end,ctx);
		framerate = r->getNBitInt(16);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"framerate",
				framerate );
		}
		frames = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"frames",
				frames );
		}

		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s @%i-%i :%i\n",
					"Tag",
					"tags",
					r->getPosition(),
					r->getBits(),
					end );
			}
			int myend = end;


			if( r->getPosition() < myend ) {
				Tag *item;
				item = Tag::get(r,end,ctx);
                bool hasSavedContentAtEnd = false;

                while( item && r->getPosition() <= myend ) {
                    if (item->getType() == 0 && hasSavedContentAtEnd == false) {
                        hasFoundEndTag = true;
                    }
                    if ( item->getLength() >= 4 && item->getType() == 0x56 ) {
                        // DefineSceneAndFrameLabelData
                        // Check for cve_2007_0071
                        maybe_cve_2007_0071_ = true;

                        unsigned char *pData = NULL;
                        int size;
                        reinterpret_cast<UnknownTag *>(item)->getdata( &pData, &size );
                        if ( pData != NULL ) {
                            uint32_t sceneCount = Reader::getU30( pData );
                            if ( sceneCount >= 0x3fffffff ) {
                                this->addDetection( "fileformat", "swf_parser_cve_2007_0071" );
                                return r->getError() == SWFR_OK;
                            }
                        }
                    }
                    if ( item->getLength() > 8 ) {
                        tags.append( item );
                        
                    }
                    else if (item->getType() == 69){ //const int kTagFileAttributes = 69;
                        tags.append( item );
                    } else {
                        delete item;
                    }

                    if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() )) {
                        // compose a 0x100 flag
                        if (hasFoundEndTag && !hasSavedContentAtEnd) {
                            int offset = r->getPosition();
                            uint32_t len = end - offset;
                            UnknownTag *ret = new UnknownTag();
                            ret->setType(0x100);
                            unsigned char *data = new unsigned char[ len ];
                            memset(data, '\0', len);
                            if (r->getData( data, len )) {
                                ret->setdata(data, len);
                            }
                            delete[] data;
                            data = NULL;
                            tags.append(static_cast<SWF::Tag*>(ret));

                            hasSavedContentAtEnd = true;
                            r->seekTo(offset);
                        }

                        item = Tag::get(r,myend,ctx);
                    } else {
                        item = NULL;
                    }
                }

				if (item != NULL) {
					delete item;
					item = NULL;
				}
            }
		}

		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Symbol

	bool Symbol::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Symbol",
				r->getPosition(),
				r->getBits(),
				end );
		}

		objectID = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"objectID",
				objectID );
		}
		name = r->getString();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %s\n",
				"name",
				name );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Parameter

	bool Parameter::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Parameter",
				r->getPosition(),
				r->getBits(),
				end );
		}

		reg = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"reg",
				reg );
		}
		name = r->getString();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %s\n",
				"name",
				name );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// UChar

	bool UChar::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"UChar",
				r->getPosition(),
				r->getBits(),
				end );
		}

		value = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"value",
				value );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// UShort

	bool UShort::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"UShort",
				r->getPosition(),
				r->getBits(),
				end );
		}

		value = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"value",
				value );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// ULong

	bool ULong::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"ULong",
				r->getPosition(),
				r->getBits(),
				end );
		}

		value = r->getNBitInt(32);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"value",
				value );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Short

	bool Short::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Short",
				r->getPosition(),
				r->getBits(),
				end );
		}

		value = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"value",
				value );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Float

	bool Float::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Float",
				r->getPosition(),
				r->getBits(),
				end );
		}

		value = r->getFloat();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %g\n",
				"value",
				value );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Double

	bool Double::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Double",
				r->getPosition(),
				r->getBits(),
				end );
		}

		value = r->getDouble2();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %g\n",
				"value",
				value );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Kerning

	bool Kerning::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Kerning",
				r->getPosition(),
				r->getBits(),
				end );
		}

		a = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"a",
				a );
		}
		b = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"b",
				b );
		}
		adjustment = r->getNBitInt(16,true);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"adjustment",
				adjustment );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// WideKerning

	bool WideKerning::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"WideKerning",
				r->getPosition(),
				r->getBits(),
				end );
		}

		a = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"a",
				a );
		}
		b = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"b",
				b );
		}
		adjustment = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"adjustment",
				adjustment );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Event

	bool Event::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Event",
				r->getPosition(),
				r->getBits(),
				end );
		}


		r->byteAlign();
		flags1 = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"flags1",
				flags1 );
		}

		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE IF %s - ", "ctx->swfVersion>=6" );
		}
		if( ctx->swfVersion>=6 ) {
			if( ctx->debugTrace ) {
				fprintf( stderr, "TRUE\n" );
			}
			flags2 = r->getWord();
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE %s: %i\n",
					"flags2",
					flags2 );
			}

		} else {
			if( ctx->debugTrace ) {
				fprintf( stderr, "FALSE\n" );
			}

		}

		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE IF %s - ", "(flags1 | flags2)" );
		}
		if( (flags1 | flags2) ) {
			if( ctx->debugTrace ) {
				fprintf( stderr, "TRUE\n" );
			}
			actionLength = r->getInt();
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE %s: %i\n",
					"actionLength",
					actionLength );
			}

			{
				if( ctx->debugTrace ) {
					fprintf( stderr, "PARSE list<%s> %s @%i-%i :%i\n",
						"Action",
						"actions",
						r->getPosition(),
						r->getBits(),
						end );
				}
				int myend = end;

				myend = r->getPosition() + actionLength;


				if( r->getPosition() < myend ) {
					Action *item;
					item = Action::get(r,end,ctx);
					while( item && r->getPosition() <= myend ) {
						actions.append( item );
						if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
							item = Action::get(r,myend,ctx);
						else item = NULL;
					}

					if (item != NULL) {
						delete item;
					}
				}
			}

		} else {
			if( ctx->debugTrace ) {
				fprintf( stderr, "FALSE\n" );
			}

		}


		return r->getError() == SWFR_OK;
	}



	//////////////////////////////////// U30

	bool U30::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"U30",
				r->getPosition(),
				r->getBits(),
				end );
		}

		value = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"value",
				value );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// S24

	bool S24::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"S24",
				r->getPosition(),
				r->getBits(),
				end );
		}

		value = r->getS24();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"value",
				value );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// ValueKind

	bool ValueKind::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"ValueKind",
				r->getPosition(),
				r->getBits(),
				end );
		}

		index = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"index",
				index );
		}
		kind = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"kind",
				kind );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// MethodInfo

	bool MethodInfo::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"MethodInfo",
				r->getPosition(),
				r->getBits(),
				end );
		}

		paramCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"paramCount",
				paramCount );
		}
		retType = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"retType",
				retType );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"U30",
					"paramTypes",
					paramCount,
					r->getPosition(),
					r->getBits(),
					end );
			}
			U30 *item;
			for( int i=0; i<paramCount; i++ ) {
				item = U30::get(r,end,ctx);
				paramTypes.append( item );
			}
		}
		nameIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"nameIndex",
				nameIndex );
		}
		hasParamNames = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"hasParamNames",
				hasParamNames );
		}
		setSDXNs = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"setSDXNs",
				setSDXNs );
		}
		isExplicit = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"isExplicit",
				isExplicit );
		}
		ignoreRest = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"ignoreRest",
				ignoreRest );
		}
		hasOptional = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"hasOptional",
				hasOptional );
		}
		needRest = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"needRest",
				needRest );
		}
		needActivation = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"needActivation",
				needActivation );
		}
		needArguments = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"needArguments",
				needArguments );
		}

		if( hasOptional ) {

			optionalCount = r->getU30();
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE %s: %i\n",
					"optionalCount",
					optionalCount );
			}


			{
				if( ctx->debugTrace ) {
					fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
						"ValueKind",
						"optional",
						optionalCount,
						r->getPosition(),
						r->getBits(),
						end );
				}
				ValueKind *item;
				for( int i=0; i<optionalCount; i++ ) {
					item = ValueKind::get(r,end,ctx);
					optional.append( item );
				}
			}

		} else {

		}

		if( hasParamNames ) {



			{
				if( ctx->debugTrace ) {
					fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
						"U30",
						"paramNames",
						paramCount,
						r->getPosition(),
						r->getBits(),
						end );
				}
				U30 *item;
				for( int i=0; i<paramCount; i++ ) {
					item = U30::get(r,end,ctx);
					paramNames.append( item );
				}
			}

		} else {

		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// MetadataInfo

	bool MetadataInfo::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"MetadataInfo",
				r->getPosition(),
				r->getBits(),
				end );
		}

		nameIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"nameIndex",
				nameIndex );
		}
		valuesCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"valuesCount",
				valuesCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"U30",
					"keys",
					valuesCount,
					r->getPosition(),
					r->getBits(),
					end );
			}
			U30 *item;
			for( int i=0; i<valuesCount; i++ ) {
				item = U30::get(r,end,ctx);
				keys.append( item );
			}
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"U30",
					"values",
					valuesCount,
					r->getPosition(),
					r->getBits(),
					end );
			}
			U30 *item;
			for( int i=0; i<valuesCount; i++ ) {
				item = U30::get(r,end,ctx);
				values.append( item );
			}
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// NamespaceSet

	bool NamespaceSet::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"NamespaceSet",
				r->getPosition(),
				r->getBits(),
				end );
		}

		count = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"count",
				count );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"U30",
					"namespaces",
					count,
					r->getPosition(),
					r->getBits(),
					end );
			}
			U30 *item;
			for( int i=0; i<count; i++ ) {
				item = U30::get(r,end,ctx);
				namespaces.append( item );
			}
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// TraitInfo

	bool TraitInfo::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"TraitInfo",
				r->getPosition(),
				r->getBits(),
				end );
		}

		nameIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"nameIndex",
				nameIndex );
		}
		reserved = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"reserved",
				reserved );
		}
		hasMetadata = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"hasMetadata",
				hasMetadata );
		}
		override = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"override",
				override );
		}
		final = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"final",
				final );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"Trait",
					"trait",
					1,
					r->getPosition(),
					r->getBits(),
					end );
			}
			Trait *item;
			for( int i=0; i<1; i++ ) {
				item = Trait::get(r,end,ctx);
				trait.append( item );
			}
		}

		if( hasMetadata ) {

			metadataCount = r->getU30();
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE %s: %i\n",
					"metadataCount",
					metadataCount );
			}


			{
				if( ctx->debugTrace ) {
					fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
						"U30",
						"metadata",
						metadataCount,
						r->getPosition(),
						r->getBits(),
						end );
				}
				U30 *item;
				for( int i=0; i<metadataCount; i++ ) {
					item = U30::get(r,end,ctx);
					metadata.append( item );
				}
			}

		} else {

		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// InstanceInfo

	bool InstanceInfo::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"InstanceInfo",
				r->getPosition(),
				r->getBits(),
				end );
		}

		nameIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"nameIndex",
				nameIndex );
		}
		superIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"superIndex",
				superIndex );
		}
		reserved = r->getNBitInt(4);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"reserved",
				reserved );
		}
		hasProtectedNS = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"hasProtectedNS",
				hasProtectedNS );
		}
		interface = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"interface",
				interface );
		}
		final = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"final",
				final );
		}
		sealed = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"sealed",
				sealed );
		}

		if( hasProtectedNS ) {

			protectedNS = r->getU30();
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE %s: %i\n",
					"protectedNS",
					protectedNS );
			}

		} else {

		}
		interfaceCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"interfaceCount",
				interfaceCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"U30",
					"interfaces",
					interfaceCount,
					r->getPosition(),
					r->getBits(),
					end );
			}
			U30 *item;
			for( int i=0; i<interfaceCount; i++ ) {
				item = U30::get(r,end,ctx);
				interfaces.append( item );
			}
		}
		iInitIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"iInitIndex",
				iInitIndex );
		}
		traitCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"traitCount",
				traitCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"TraitInfo",
					"traits",
					traitCount,
					r->getPosition(),
					r->getBits(),
					end );
			}
			TraitInfo *item;
			for( int i=0; i<traitCount; i++ ) {
				item = TraitInfo::get(r,end,ctx);
				traits.append( item );
			}
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// ClassInfo

	bool ClassInfo::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"ClassInfo",
				r->getPosition(),
				r->getBits(),
				end );
		}

		cInitIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"cInitIndex",
				cInitIndex );
		}
		traitCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"traitCount",
				traitCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"TraitInfo",
					"traits",
					traitCount,
					r->getPosition(),
					r->getBits(),
					end );
			}
			TraitInfo *item;
			for( int i=0; i<traitCount; i++ ) {
				item = TraitInfo::get(r,end,ctx);
				traits.append( item );
			}
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// ScriptInfo

	bool ScriptInfo::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"ScriptInfo",
				r->getPosition(),
				r->getBits(),
				end );
		}

		initIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"initIndex",
				initIndex );
		}
		traitCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"traitCount",
				traitCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"TraitInfo",
					"traits",
					traitCount,
					r->getPosition(),
					r->getBits(),
					end );
			}
			TraitInfo *item;
			for( int i=0; i<traitCount; i++ ) {
				item = TraitInfo::get(r,end,ctx);
				traits.append( item );
			}
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Exception

	bool Exception::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Exception",
				r->getPosition(),
				r->getBits(),
				end );
		}

		tryStart = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"tryStart",
				tryStart );
		}
		tryEnd = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"tryEnd",
				tryEnd );
		}
		target = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"target",
				target );
		}
		type = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"type",
				type );
		}
		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// MethodBody

	bool MethodBody::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"MethodBody",
				r->getPosition(),
				r->getBits(),
				end );
		}

		methodInfo = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"methodInfo",
				methodInfo );
		}
		maxStack = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"maxStack",
				maxStack );
		}
		maxRegs = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"maxRegs",
				maxRegs );
		}
		scopeDepth = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"scopeDepth",
				scopeDepth );
		}
		maxScope = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"maxScope",
				maxScope );
		}
		codeLength = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"codeLength",
				codeLength );
		}

		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s @%i-%i :%i\n",
					"OpCode",
					"code",
					r->getPosition(),
					r->getBits(),
					end );
			}
			int myend = end;

			myend = r->getPosition() + codeLength;


			if( r->getPosition() < myend ) {
				OpCode *item;
				item = OpCode::get(r,end,ctx);
				while( item && r->getPosition() <= myend ) {
					code.append( item );
					if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
						item = OpCode::get(r,myend,ctx);
					else item = NULL;
				}

				if (item != NULL) {
					delete item;
				}
			}
		}
		exceptionCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"exceptionCount",
				exceptionCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"Exception",
					"exceptions",
					exceptionCount,
					r->getPosition(),
					r->getBits(),
					end );
			}
			Exception *item;
			for( int i=0; i<exceptionCount; i++ ) {
				item = Exception::get(r,end,ctx);
				exceptions.append( item );
			}
		}
		traitCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"traitCount",
				traitCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"TraitInfo",
					"traits",
					traitCount,
					r->getPosition(),
					r->getBits(),
					end );
			}
			TraitInfo *item;
			for( int i=0; i<traitCount; i++ ) {
				item = TraitInfo::get(r,end,ctx);
				traits.append( item );
			}
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Constants

	bool Constants::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Constants",
				r->getPosition(),
				r->getBits(),
				end );
		}

		intCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"intCount",
				intCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"U30",
					"ints",

					( intCount < 1
					? 0
					: intCount - 1 )
					,
					r->getPosition(),
					r->getBits(),
					end );
			}
			U30 *item;
			for( int i=0; i<
				( intCount < 1
				? 0
				: intCount - 1 )
				; i++ ) {
					item = U30::get(r,end,ctx);
					ints.append( item );
			}
		}
		uintCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"uintCount",
				uintCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"U30",
					"uints",

					( uintCount < 1
					? 0
					: uintCount - 1 )
					,
					r->getPosition(),
					r->getBits(),
					end );
			}
			U30 *item;
			for( int i=0; i<
				( uintCount < 1
				? 0
				: uintCount - 1 )
				; i++ ) {
					item = U30::get(r,end,ctx);
					uints.append( item );
			}
		}
		doubleCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"doubleCount",
				doubleCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"Double",
					"doubles",

					( doubleCount < 1
					? 0
					: doubleCount - 1 )
					,
					r->getPosition(),
					r->getBits(),
					end );
			}
			Double *item;
			for( int i=0; i<
				( doubleCount < 1
				? 0
				: doubleCount - 1 )
				; i++ ) {
					item = Double::get(r,end,ctx);
					doubles.append( item );
			}
		}
		stringCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"stringCount",
				stringCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"String2",
					"strings",

					( stringCount < 1
					? 0
					: stringCount - 1 )
					,
					r->getPosition(),
					r->getBits(),
					end );
			}
			String2 *item;
			for( int i=0; i<
				( stringCount < 1
				? 0
				: stringCount - 1 )
				; i++ ) {
					item = String2::get(r,end,ctx);
					strings.append( item );
			}
		}
		namespaceConstantCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"namespaceConstantCount",
				namespaceConstantCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"NamespaceConstant",
					"namespaces",

					( namespaceConstantCount < 1
					? 0
					: namespaceConstantCount - 1 )
					,
					r->getPosition(),
					r->getBits(),
					end );
			}
			NamespaceConstant *item;
			for( int i=0; i<
				( namespaceConstantCount < 1
				? 0
				: namespaceConstantCount - 1 )
				; i++ ) {
					item = NamespaceConstant::get(r,end,ctx);
					namespaces.append( item );
			}
		}
		namespaceSetCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"namespaceSetCount",
				namespaceSetCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"NamespaceSet",
					"namespaceSets",

					( namespaceSetCount < 1
					? 0
					: namespaceSetCount - 1 )
					,
					r->getPosition(),
					r->getBits(),
					end );
			}
			NamespaceSet *item;
			for( int i=0; i<
				( namespaceSetCount < 1
				? 0
				: namespaceSetCount - 1 )
				; i++ ) {
					item = NamespaceSet::get(r,end,ctx);
					namespaceSets.append( item );
			}
		}
		multinameConstantCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"multinameConstantCount",
				multinameConstantCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"MultinameConstant",
					"multinames",

					( multinameConstantCount < 1
					? 0
					: multinameConstantCount - 1 )
					,
					r->getPosition(),
					r->getBits(),
					end );
			}
			MultinameConstant *item;
			for( int i=0; i<
				( multinameConstantCount < 1
				? 0
				: multinameConstantCount - 1 )
				; i++ ) {
					item = MultinameConstant::get(r,end,ctx);
					multinames.append( item );
			}
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Action3

	bool Action3::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Action3",
				r->getPosition(),
				r->getBits(),
				end );
		}

		minorVersion = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"minorVersion",
				minorVersion );
		}
		majorVersion = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"majorVersion",
				majorVersion );
		}
		constants.parse(r,end,ctx);
		methodInfoCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"methodInfoCount",
				methodInfoCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"MethodInfo",
					"methods",
					methodInfoCount,
					r->getPosition(),
					r->getBits(),
					end );
			}
			MethodInfo *item;
			for( int i=0; i<methodInfoCount; i++ ) {
				item = MethodInfo::get(r,end,ctx);
				methods.append( item );
			}
		}
		metadataInfoCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"metadataInfoCount",
				metadataInfoCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"MetadataInfo",
					"metadata",
					metadataInfoCount,
					r->getPosition(),
					r->getBits(),
					end );
			}
			MetadataInfo *item;
			for( int i=0; i<metadataInfoCount; i++ ) {
				item = MetadataInfo::get(r,end,ctx);
				metadata.append( item );
			}
		}
		classCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"classCount",
				classCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"InstanceInfo",
					"instances",
					classCount,
					r->getPosition(),
					r->getBits(),
					end );
			}
			InstanceInfo *item;
			for( int i=0; i<classCount; i++ ) {
				item = InstanceInfo::get(r,end,ctx);
				instances.append( item );
			}
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"ClassInfo",
					"classes",
					classCount,
					r->getPosition(),
					r->getBits(),
					end );
			}
			ClassInfo *item;
			for( int i=0; i<classCount; i++ ) {
				item = ClassInfo::get(r,end,ctx);
				classes.append( item );
			}
		}
		scriptCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"scriptCount",
				scriptCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"ScriptInfo",
					"scripts",
					scriptCount,
					r->getPosition(),
					r->getBits(),
					end );
			}
			ScriptInfo *item;
			for( int i=0; i<scriptCount; i++ ) {
				item = ScriptInfo::get(r,end,ctx);
				scripts.append( item );
			}
		}
		methodBodyCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"methodBodyCount",
				methodBodyCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"MethodBody",
					"methodBodies",
					methodBodyCount,
					r->getPosition(),
					r->getBits(),
					end );
			}
			MethodBody *item;
			for( int i=0; i<methodBodyCount; i++ ) {
				item = MethodBody::get(r,end,ctx);
				methodBodies.append( item );
			}
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// ZoneData

	bool ZoneData::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"ZoneData",
				r->getPosition(),
				r->getBits(),
				end );
		}

		position = r->getHalf();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %g\n",
				"position",
				position );
		}
		size = r->getHalf();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %g\n",
				"size",
				size );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// ZoneArray

	bool ZoneArray::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"ZoneArray",
				r->getPosition(),
				r->getBits(),
				end );
		}

		count = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"count",
				count );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"ZoneData",
					"zones",
					count,
					r->getPosition(),
					r->getBits(),
					end );
			}
			ZoneData *item;
			for( int i=0; i<count; i++ ) {
				item = ZoneData::get(r,end,ctx);
				zones.append( item );
			}
		}
		zoneX = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"zoneX",
				zoneX );
		}
		zoneY = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"zoneY",
				zoneY );
		}
		reserved = r->getNBitInt(6);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"reserved",
				reserved );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// UnknownFilter

	bool UnknownFilter::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"UnknownFilter",
				r->getPosition(),
				r->getBits(),
				end );
		}


		{
			int sz = len;

			data = new unsigned char[ sz ];
			r->getData( data, sz );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// UnknownTag

	bool UnknownTag::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"UnknownTag",
				r->getPosition(),
				r->getBits(),
				end );
		}


		{
			int sz = len;

			data = new unsigned char[ sz ];
			r->getData( data, sz );
		}

		if( r->getPosition() != file_offset + len ) {
			fprintf( stderr, "WARNING: end of tag %s is @%i, should be @%i\n",
				"UnknownTag",
				r->getPosition(),
				file_offset+len );
			r->seekTo( file_offset + len );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// End

	bool End::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"End",
				r->getPosition(),
				r->getBits(),
				end );
		}


		if( r->getPosition() != file_offset + len ) {
			fprintf( stderr, "WARNING: end of tag %s is @%i, should be @%i\n",
				"End",
				r->getPosition(),
				file_offset+len );
			r->seekTo( file_offset + len );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// DoAction

	bool DoAction::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"DoAction",
				r->getPosition(),
				r->getBits(),
				end );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s @%i-%i :%i\n",
					"Action",
					"actions",
					r->getPosition(),
					r->getBits(),
					end );
			}
			int myend = end;


			if( r->getPosition() < myend ) {
				Action *item;
				item = Action::get(r,end,ctx);
				while( item && r->getPosition() <= myend ) {
					actions.append( item );
					if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
						item = Action::get(r,myend,ctx);
					else item = NULL;
				}

				if (item != NULL) {
					delete item;
				}
			}
		}

		if( r->getPosition() != file_offset + len ) {
			fprintf( stderr, "WARNING: end of tag %s is @%i, should be @%i\n",
				"DoAction",
				r->getPosition(),
				file_offset+len );
			r->seekTo( file_offset + len );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Export

	bool Export::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Export",
				r->getPosition(),
				r->getBits(),
				end );
		}

		count = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"count",
				count );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"Symbol",
					"symbols",
					count,
					r->getPosition(),
					r->getBits(),
					end );
			}
			Symbol *item;
			for( int i=0; i<count; i++ ) {
				item = Symbol::get(r,end,ctx);
				symbols.append( item );
			}
		}

		if( r->getPosition() != file_offset + len ) {
			fprintf( stderr, "WARNING: end of tag %s is @%i, should be @%i\n",
				"Export",
				r->getPosition(),
				file_offset+len );
			r->seekTo( file_offset + len );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Import

	bool Import::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Import",
				r->getPosition(),
				r->getBits(),
				end );
		}

		url = r->getString();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %s\n",
				"url",
				url );
		}
		count = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"count",
				count );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"Symbol",
					"symbols",
					count,
					r->getPosition(),
					r->getBits(),
					end );
			}
			Symbol *item;
			for( int i=0; i<count; i++ ) {
				item = Symbol::get(r,end,ctx);
				symbols.append( item );
			}
		}

		if( r->getPosition() != file_offset + len ) {
			fprintf( stderr, "WARNING: end of tag %s is @%i, should be @%i\n",
				"Import",
				r->getPosition(),
				file_offset+len );
			r->seekTo( file_offset + len );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// DoInitAction

	bool DoInitAction::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"DoInitAction",
				r->getPosition(),
				r->getBits(),
				end );
		}

		sprite = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"sprite",
				sprite );
		}

		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s @%i-%i :%i\n",
					"Action",
					"actions",
					r->getPosition(),
					r->getBits(),
					end );
			}
			int myend = end;


			if( r->getPosition() < myend ) {
				Action *item;
				item = Action::get(r,end,ctx);
				while( item && r->getPosition() <= myend ) {
					actions.append( item );
					if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
						item = Action::get(r,myend,ctx);
					else item = NULL;
				}

				if (item != NULL) {
					delete item;
				}
			}
		}

		if( r->getPosition() != file_offset + len ) {
			fprintf( stderr, "WARNING: end of tag %s is @%i, should be @%i\n",
				"DoInitAction",
				r->getPosition(),
				file_offset+len );
			r->seekTo( file_offset + len );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// ScriptLimits

	bool ScriptLimits::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"ScriptLimits",
				r->getPosition(),
				r->getBits(),
				end );
		}

		maxRecursionDepth = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"maxRecursionDepth",
				maxRecursionDepth );
		}
		timeout = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"timeout",
				timeout );
		}

		if( r->getPosition() != file_offset + len ) {
			fprintf( stderr, "WARNING: end of tag %s is @%i, should be @%i\n",
				"ScriptLimits",
				r->getPosition(),
				file_offset+len );
			r->seekTo( file_offset + len );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// ImportAssets2

	bool ImportAssets2::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"ImportAssets2",
				r->getPosition(),
				r->getBits(),
				end );
		}

		url = r->getString();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %s\n",
				"url",
				url );
		}
		reserved1 = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"reserved1",
				reserved1 );
		}
		reserved2 = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"reserved2",
				reserved2 );
		}
		count = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"count",
				count );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"Symbol",
					"symbols",
					count,
					r->getPosition(),
					r->getBits(),
					end );
			}
			Symbol *item;
			for( int i=0; i<count; i++ ) {
				item = Symbol::get(r,end,ctx);
				symbols.append( item );
			}
		}

		if( r->getPosition() != file_offset + len ) {
			fprintf( stderr, "WARNING: end of tag %s is @%i, should be @%i\n",
				"ImportAssets2",
				r->getPosition(),
				file_offset+len );
			r->seekTo( file_offset + len );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// FileAttributes

	bool FileAttributes::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"FileAttributes",
				r->getPosition(),
				r->getBits(),
				end );
		}

		reserved1 = r->getNBitInt(3);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"reserved1",
				reserved1 );
		}
		hasMetaData = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"hasMetaData",
				hasMetaData );
		}

		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE IF %s - ", "ctx->swfVersion < 9" );
		}
		if( ctx->swfVersion < 8 ) {
			if( ctx->debugTrace ) {
				fprintf( stderr, "TRUE\n" );
			}
			reserved2 = r->getNBitInt(3);
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE %s: %i\n",
					"reserved2",
					reserved2 );
			}

		} else {
			if( ctx->debugTrace ) {
				fprintf( stderr, "FALSE\n" );
			}

		}

		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE IF %s - ", "ctx->swfVersion >= 9" );
		}
		if( ctx->swfVersion >= 8 ) {
			if( ctx->debugTrace ) {
				fprintf( stderr, "TRUE\n" );
			}
			allowABC = r->getNBitInt(1);
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE %s: %i\n",
					"allowABC",
					allowABC );
			}
			suppressCrossDomainCaching = r->getNBitInt(1);
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE %s: %i\n",
					"suppressCrossDomainCaching",
					suppressCrossDomainCaching );
			}
			swfRelativeURLs = r->getNBitInt(1);
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE %s: %i\n",
					"swfRelativeURLs",
					swfRelativeURLs );
			}

		} else {
			if( ctx->debugTrace ) {
				fprintf( stderr, "FALSE\n" );
			}

		}
		useNetwork = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"useNetwork",
				useNetwork );
		}
		reserved3 = r->getNBitInt(24);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"reserved3",
				reserved3 );
		}

		if( r->getPosition() != file_offset + len ) {
			fprintf( stderr, "WARNING: end of tag %s is @%i, should be @%i\n",
				"FileAttributes",
				r->getPosition(),
				file_offset+len );
			r->seekTo( file_offset + len );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Metadata

	bool Metadata::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Metadata",
				r->getPosition(),
				r->getBits(),
				end );
		}

		RDF = r->getString();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %s\n",
				"RDF",
				RDF );
		}

		if( r->getPosition() != file_offset + len ) {
			fprintf( stderr, "WARNING: end of tag %s is @%i, should be @%i\n",
				"Metadata",
				r->getPosition(),
				file_offset+len );
			r->seekTo( file_offset + len );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// DoABC

	bool DoABC::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"DoABC",
				r->getPosition(),
				r->getBits(),
				end );
		}

		actions.parse(r,end,ctx);

		if( r->getPosition() != file_offset + len ) {
			fprintf( stderr, "WARNING: end of tag %s is @%i, should be @%i\n",
				"DoABC",
				r->getPosition(),
				file_offset+len );
			r->seekTo( file_offset + len );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// DoABCDefine

	bool DoABCDefine::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"DoABCDefine",
				r->getPosition(),
				r->getBits(),
				end );
		}

		flags = r->getInt();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"flags",
				flags );
		}
		name = r->getString();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %s\n",
				"name",
				name );
		}

		actions.parse(r,end,ctx);

		if( r->getPosition() != file_offset + len ) {
			fprintf( stderr, "WARNING: end of tag %s is @%i, should be @%i\n",
				"DoABCDefine",
				r->getPosition(),
				file_offset+len );
			r->seekTo( file_offset + len );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// SymbolClass

	bool SymbolClass::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"SymbolClass",
				r->getPosition(),
				r->getBits(),
				end );
		}

		count = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"count",
				count );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"Symbol",
					"symbols",
					count,
					r->getPosition(),
					r->getBits(),
					end );
			}
			Symbol *item;
			for( int i=0; i<count; i++ ) {
				item = Symbol::get(r,end,ctx);
				symbols.append( item );
			}
		}

		if( r->getPosition() != file_offset + len ) {
			fprintf( stderr, "WARNING: end of tag %s is @%i, should be @%i\n",
				"SymbolClass",
				r->getPosition(),
				file_offset+len );
			r->seekTo( file_offset + len );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// DefineBinaryData

	bool DefineBinaryData::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"DefineBinaryData",
				r->getPosition(),
				r->getBits(),
				end );
		}

		objectID = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"objectID",
				objectID );
		}
		reserved = r->getInt();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"reserved",
				reserved );
		}
		data.parse(r,end,ctx);

		if( r->getPosition() != file_offset + len ) {
			fprintf( stderr, "WARNING: end of tag %s is @%i, should be @%i\n",
				"DefineBinaryData",
				r->getPosition(),
				file_offset+len );
			r->seekTo( file_offset + len );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// EnableDebugger

	bool EnableDebugger::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"EnableDebugger",
				r->getPosition(),
				r->getBits(),
				end );
		}

		password = r->getString();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %s\n",
				"password",
				password );
		}

		if( r->getPosition() != file_offset + len ) {
			fprintf( stderr, "WARNING: end of tag %s is @%i, should be @%i\n",
				"EnableDebugger",
				r->getPosition(),
				file_offset+len );
			r->seekTo( file_offset + len );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// EnableDebugger2

	bool EnableDebugger2::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"EnableDebugger2",
				r->getPosition(),
				r->getBits(),
				end );
		}

		reserved = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"reserved",
				reserved );
		}
		password = r->getString();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %s\n",
				"password",
				password );
		}

		if( r->getPosition() != file_offset + len ) {
			fprintf( stderr, "WARNING: end of tag %s is @%i, should be @%i\n",
				"EnableDebugger2",
				r->getPosition(),
				file_offset+len );
			r->seekTo( file_offset + len );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// StackString

	bool StackString::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"StackString",
				r->getPosition(),
				r->getBits(),
				end );
		}

		value = r->getString();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %s\n",
				"value",
				value );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// StackFloat

	bool StackFloat::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"StackFloat",
				r->getPosition(),
				r->getBits(),
				end );
		}

		value = r->getFloat();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %g\n",
				"value",
				value );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// StackNull

	bool StackNull::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"StackNull",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// StackUndefined

	bool StackUndefined::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"StackUndefined",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// StackRegister

	bool StackRegister::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"StackRegister",
				r->getPosition(),
				r->getBits(),
				end );
		}

		reg = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"reg",
				reg );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// StackBoolean

	bool StackBoolean::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"StackBoolean",
				r->getPosition(),
				r->getBits(),
				end );
		}

		value = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"value",
				value );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// StackDouble

	bool StackDouble::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"StackDouble",
				r->getPosition(),
				r->getBits(),
				end );
		}

		value = r->getDouble();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %g\n",
				"value",
				value );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// StackInteger

	bool StackInteger::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"StackInteger",
				r->getPosition(),
				r->getBits(),
				end );
		}

		value = r->getInt();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"value",
				value );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// StackDictionaryLookup

	bool StackDictionaryLookup::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"StackDictionaryLookup",
				r->getPosition(),
				r->getBits(),
				end );
		}

		index = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"index",
				index );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// StackLargeDictionaryLookup

	bool StackLargeDictionaryLookup::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"StackLargeDictionaryLookup",
				r->getPosition(),
				r->getBits(),
				end );
		}

		index = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"index",
				index );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// UnknownAction

	bool UnknownAction::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"UnknownAction",
				r->getPosition(),
				r->getBits(),
				end );
		}


		{
			int sz = len;

			data = new unsigned char[ sz ];
			r->getData( data, sz );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// EndAction

	bool EndAction::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"EndAction",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// AddCast

	bool AddCast::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"AddCast",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Substract

	bool Substract::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Substract",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Mulitply

	bool Mulitply::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Mulitply",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Divide

	bool Divide::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Divide",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// EqualCast

	bool EqualCast::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"EqualCast",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// LessThanCast

	bool LessThanCast::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"LessThanCast",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// LogicalAND

	bool LogicalAND::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"LogicalAND",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// LogicalOR

	bool LogicalOR::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"LogicalOR",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// LogicalNOT

	bool LogicalNOT::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"LogicalNOT",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// StringEqual

	bool StringEqual::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"StringEqual",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// StringLength

	bool StringLength::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"StringLength",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// SubString

	bool SubString::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"SubString",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Pop

	bool Pop::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Pop",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// IntegralPart

	bool IntegralPart::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"IntegralPart",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// GetVariable

	bool GetVariable::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"GetVariable",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// SetVariable

	bool SetVariable::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"SetVariable",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// SetTargetDynamic

	bool SetTargetDynamic::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"SetTargetDynamic",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// ConcatenateString

	bool ConcatenateString::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"ConcatenateString",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// GetProperty

	bool GetProperty::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"GetProperty",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// SetProperty

	bool SetProperty::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"SetProperty",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// DuplicateSprite

	bool DuplicateSprite::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"DuplicateSprite",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// RemoveSprite

	bool RemoveSprite::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"RemoveSprite",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Trace

	bool Trace::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Trace",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}



	//////////////////////////////////// StringLessThan

	bool StringLessThan::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"StringLessThan",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Throw

	bool Throw::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Throw",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// CastObject

	bool CastObject::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"CastObject",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Implements

	bool Implements::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Implements",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Random

	bool Random::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Random",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// MultibyteStringLength

	bool MultibyteStringLength::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"MultibyteStringLength",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// ORD

	bool ORD::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"ORD",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// CHR

	bool CHR::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"CHR",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// GetTimer

	bool GetTimer::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"GetTimer",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// MultibyteSubString

	bool MultibyteSubString::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"MultibyteSubString",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// MultibyteORD

	bool MultibyteORD::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"MultibyteORD",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// MultibyteCHR

	bool MultibyteCHR::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"MultibyteCHR",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Delete

	bool Delete::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Delete",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// DeleteAll

	bool DeleteAll::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"DeleteAll",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// SetLocalVariable

	bool SetLocalVariable::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"SetLocalVariable",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// CallFunction

	bool CallFunction::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"CallFunction",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Return

	bool Return::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Return",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Modulo

	bool Modulo::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Modulo",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// New

	bool New::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"New",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// DeclareLocalVariable

	bool DeclareLocalVariable::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"DeclareLocalVariable",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// DeclareArray

	bool DeclareArray::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"DeclareArray",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// DeclareObject

	bool DeclareObject::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"DeclareObject",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// TypeOf

	bool TypeOf::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"TypeOf",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// GetTarget

	bool GetTarget::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"GetTarget",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Enumerate

	bool Enumerate::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Enumerate",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// AddTyped

	bool AddTyped::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"AddTyped",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// LessThanTyped

	bool LessThanTyped::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"LessThanTyped",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// EqualTyped

	bool EqualTyped::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"EqualTyped",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// DefineNumber

	bool DefineNumber::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"DefineNumber",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// DefineString

	bool DefineString::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"DefineString",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Duplicate

	bool Duplicate::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Duplicate",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Swap

	bool Swap::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Swap",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// GetMember

	bool GetMember::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"GetMember",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// SetMember

	bool SetMember::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"SetMember",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Increment

	bool Increment::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Increment",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Decrement

	bool Decrement::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Decrement",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// CallMethod

	bool CallMethod::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"CallMethod",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// NewMethod

	bool NewMethod::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"NewMethod",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// InstanceOf

	bool InstanceOf::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"InstanceOf",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// EnumerateObject

	bool EnumerateObject::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"EnumerateObject",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// AND

	bool AND::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"AND",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OR

	bool OR::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OR",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// XOR

	bool XOR::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"XOR",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// ShiftLeft

	bool ShiftLeft::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"ShiftLeft",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// ShiftRight

	bool ShiftRight::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"ShiftRight",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// ShiftRightUnsigned

	bool ShiftRightUnsigned::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"ShiftRightUnsigned",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// StrictEqual

	bool StrictEqual::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"StrictEqual",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// GreaterThanTyped

	bool GreaterThanTyped::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"GreaterThanTyped",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// StringGreaterThan

	bool StringGreaterThan::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"StringGreaterThan",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Extends

	bool Extends::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Extends",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// GotoFrame

	bool GotoFrame::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"GotoFrame",
				r->getPosition(),
				r->getBits(),
				end );
		}

		frame = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"frame",
				frame );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// GetURL

	bool GetURL::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"GetURL",
				r->getPosition(),
				r->getBits(),
				end );
		}

		url = r->getString();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %s\n",
				"url",
				url );
		}
		target = r->getString();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %s\n",
				"target",
				target );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// StoreRegister

	bool StoreRegister::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"StoreRegister",
				r->getPosition(),
				r->getBits(),
				end );
		}

		reg = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"reg",
				reg );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Dictionary

	bool Dictionary::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Dictionary",
				r->getPosition(),
				r->getBits(),
				end );
		}

		length = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"length",
				length );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"String",
					"strings",
					length,
					r->getPosition(),
					r->getBits(),
					end );
			}
			String *item;
			for( int i=0; i<length; i++ ) {
				item = String::get(r,end,ctx);
				strings.append( item );
			}
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// WaitForFrame

	bool WaitForFrame::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"WaitForFrame",
				r->getPosition(),
				r->getBits(),
				end );
		}

		frame = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"frame",
				frame );
		}
		skip = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"skip",
				skip );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// SetTarget

	bool SetTarget::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"SetTarget",
				r->getPosition(),
				r->getBits(),
				end );
		}

		label = r->getString();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %s\n",
				"label",
				label );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// GotoLabel

	bool GotoLabel::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"GotoLabel",
				r->getPosition(),
				r->getBits(),
				end );
		}

		label = r->getString();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %s\n",
				"label",
				label );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// WaitForFrameDynamic

	bool WaitForFrameDynamic::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"WaitForFrameDynamic",
				r->getPosition(),
				r->getBits(),
				end );
		}

		frame = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"frame",
				frame );
		}
		skip = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"skip",
				skip );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// DeclareFunction2

	bool DeclareFunction2::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"DeclareFunction2",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getString();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %s\n",
				"name",
				name );
		}
		argc = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"argc",
				argc );
		}
		regc = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"regc",
				regc );
		}
		preloadParent = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"preloadParent",
				preloadParent );
		}
		preloadRoot = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"preloadRoot",
				preloadRoot );
		}
		suppressSuper = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"suppressSuper",
				suppressSuper );
		}
		preloadSuper = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"preloadSuper",
				preloadSuper );
		}
		suppressArguments = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"suppressArguments",
				suppressArguments );
		}
		preloadArguments = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"preloadArguments",
				preloadArguments );
		}
		suppressThis = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"suppressThis",
				suppressThis );
		}
		preloadThis = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"preloadThis",
				preloadThis );
		}
		reserved = r->getNBitInt(7);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"reserved",
				reserved );
		}
		preloadGlobal = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"preloadGlobal",
				preloadGlobal );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"Parameter",
					"args",
					argc,
					r->getPosition(),
					r->getBits(),
					end );
			}
			Parameter *item;
			for( int i=0; i<argc; i++ ) {
				item = Parameter::get(r,end,ctx);
				args.append( item );
			}
		}
		length = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"length",
				length );
		}

		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s @%i-%i :%i\n",
					"Action",
					"actions",
					r->getPosition(),
					r->getBits(),
					end );
			}
			int myend = end;

			myend = r->getPosition() + length;


			if( r->getPosition() < myend ) {
				Action *item;
				item = Action::get(r,end,ctx);
				while( item && r->getPosition() <= myend ) {
					actions.append( item );
					if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
						item = Action::get(r,myend,ctx);
					else item = NULL;

				}
			}
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Try

	bool Try::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Try",
				r->getPosition(),
				r->getBits(),
				end );
		}

		reserved = r->getNBitInt(5);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"reserved",
				reserved );
		}
		catchInRegister = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"catchInRegister",
				catchInRegister );
		}
		doFinally = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"doFinally",
				doFinally );
		}
		doCatch = r->getNBitInt(1);
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"doCatch",
				doCatch );
		}
		trySize = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"trySize",
				trySize );
		}
		catchSize = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"catchSize",
				catchSize );
		}
		finallySize = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"finallySize",
				finallySize );
		}

		if( catchInRegister ) {

			reg = r->getByte();
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE %s: %i\n",
					"reg",
					reg );
			}

		} else {

		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// With

	bool With::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"With",
				r->getPosition(),
				r->getBits(),
				end );
		}

		size = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"size",
				size );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// PushData

	bool PushData::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"PushData",
				r->getPosition(),
				r->getBits(),
				end );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s @%i-%i :%i\n",
					"StackItem",
					"items",
					r->getPosition(),
					r->getBits(),
					end );
			}
			int myend = end;


			if( r->getPosition() < myend ) {
				StackItem *item;
				item = StackItem::get(r,end,ctx);
				while( item && r->getPosition() <= myend ) {
					items.append( item );
					if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
						item = StackItem::get(r,myend,ctx);
					else item = NULL;
				}

				if (item != NULL) {
					delete item;
				}
			}
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// GetURL2

	bool GetURL2::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"GetURL2",
				r->getPosition(),
				r->getBits(),
				end );
		}

		method = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"method",
				method );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// DeclareFunction

	bool DeclareFunction::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"DeclareFunction",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getString();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %s\n",
				"name",
				name );
		}
		argc = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"argc",
				argc );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"String",
					"args",
					argc,
					r->getPosition(),
					r->getBits(),
					end );
			}
			String *item;
			for( int i=0; i<argc; i++ ) {
				item = String::get(r,end,ctx);
				args.append( item );
			}
		}
		length = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"length",
				length );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// BranchAlways

	bool BranchAlways::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"BranchAlways",
				r->getPosition(),
				r->getBits(),
				end );
		}

		byteOffset = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"byteOffset",
				byteOffset );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// BranchIfTrue

	bool BranchIfTrue::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"BranchIfTrue",
				r->getPosition(),
				r->getBits(),
				end );
		}

		byteOffset = r->getWord();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"byteOffset",
				byteOffset );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// CallFrame

	bool CallFrame::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"CallFrame",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// GotoExpression

	bool GotoExpression::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"GotoExpression",
				r->getPosition(),
				r->getBits(),
				end );
		}

		play = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"play",
				play );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// PrivateNamespace

	bool PrivateNamespace::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"PrivateNamespace",
				r->getPosition(),
				r->getBits(),
				end );
		}

		index = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"index",
				index );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Namespace

	bool Namespace::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Namespace",
				r->getPosition(),
				r->getBits(),
				end );
		}

		index = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"index",
				index );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// PackageNamespace

	bool PackageNamespace::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"PackageNamespace",
				r->getPosition(),
				r->getBits(),
				end );
		}

		index = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"index",
				index );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// PackageInternalNamespace

	bool PackageInternalNamespace::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"PackageInternalNamespace",
				r->getPosition(),
				r->getBits(),
				end );
		}

		index = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"index",
				index );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// ProtectedNamespace

	bool ProtectedNamespace::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"ProtectedNamespace",
				r->getPosition(),
				r->getBits(),
				end );
		}

		index = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"index",
				index );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// ExplicitNamespace

	bool ExplicitNamespace::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"ExplicitNamespace",
				r->getPosition(),
				r->getBits(),
				end );
		}

		index = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"index",
				index );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// MultinameLNamespace

	bool MultinameLNamespace::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"MultinameLNamespace",
				r->getPosition(),
				r->getBits(),
				end );
		}

		index = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"index",
				index );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// QName

	bool QName::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"QName",
				r->getPosition(),
				r->getBits(),
				end );
		}

		namespaceIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"namespaceIndex",
				namespaceIndex );
		}
		nameIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"nameIndex",
				nameIndex );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// QNameA

	bool QNameA::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"QNameA",
				r->getPosition(),
				r->getBits(),
				end );
		}

		namespaceIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"namespaceIndex",
				namespaceIndex );
		}
		nameIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"nameIndex",
				nameIndex );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Multiname

	bool Multiname::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Multiname",
				r->getPosition(),
				r->getBits(),
				end );
		}

		nameIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"nameIndex",
				nameIndex );
		}
		namespaceSetIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"namespaceSetIndex",
				namespaceSetIndex );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// MultinameA

	bool MultinameA::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"MultinameA",
				r->getPosition(),
				r->getBits(),
				end );
		}

		nameIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"nameIndex",
				nameIndex );
		}
		namespaceSetIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"namespaceSetIndex",
				namespaceSetIndex );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// RTQName

	bool RTQName::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"RTQName",
				r->getPosition(),
				r->getBits(),
				end );
		}

		nameIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"nameIndex",
				nameIndex );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// RTQNameA

	bool RTQNameA::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"RTQNameA",
				r->getPosition(),
				r->getBits(),
				end );
		}

		nameIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"nameIndex",
				nameIndex );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// MultinameL

	bool MultinameL::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"MultinameL",
				r->getPosition(),
				r->getBits(),
				end );
		}

		namespaceSetIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"namespaceSetIndex",
				namespaceSetIndex );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// RTQNameL

	bool RTQNameL::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"RTQNameL",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// RTQNameLA

	bool RTQNameLA::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"RTQNameLA",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// TypeName

	bool TypeName::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"TypeName",
				r->getPosition(),
				r->getBits(),
				end );
		}

		nameIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"nameIndex",
				nameIndex );
		}
		nameCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"nameCount",
				nameCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"U30",
					"types",
					nameCount,
					r->getPosition(),
					r->getBits(),
					end );
			}
			U30 *item;
			for( int i=0; i<nameCount; i++ ) {
				item = U30::get(r,end,ctx);
				types.append( item );
			}
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Slot

	bool Slot::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Slot",
				r->getPosition(),
				r->getBits(),
				end );
		}

		slotID = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"slotID",
				slotID );
		}
		typeIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"typeIndex",
				typeIndex );
		}
		valueIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"valueIndex",
				valueIndex );
		}

		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE IF %s - ", "valueIndex != 0" );
		}
		if( valueIndex != 0 ) {
			if( ctx->debugTrace ) {
				fprintf( stderr, "TRUE\n" );
			}
			valueKind = r->getByte();
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE %s: %i\n",
					"valueKind",
					valueKind );
			}

		} else {
			if( ctx->debugTrace ) {
				fprintf( stderr, "FALSE\n" );
			}

		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Const

	bool Const::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Const",
				r->getPosition(),
				r->getBits(),
				end );
		}

		slotID = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"slotID",
				slotID );
		}
		typeIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"typeIndex",
				typeIndex );
		}
		valueIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"valueIndex",
				valueIndex );
		}

		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE IF %s - ", "valueIndex != 0" );
		}
		if( valueIndex != 0 ) {
			if( ctx->debugTrace ) {
				fprintf( stderr, "TRUE\n" );
			}
			valueKind = r->getByte();
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE %s: %i\n",
					"valueKind",
					valueKind );
			}

		} else {
			if( ctx->debugTrace ) {
				fprintf( stderr, "FALSE\n" );
			}

		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Method

	bool Method::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Method",
				r->getPosition(),
				r->getBits(),
				end );
		}

		dispID = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"dispID",
				dispID );
		}
		methodInfo = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"methodInfo",
				methodInfo );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Getter

	bool Getter::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Getter",
				r->getPosition(),
				r->getBits(),
				end );
		}

		dispID = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"dispID",
				dispID );
		}
		methodInfo = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"methodInfo",
				methodInfo );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Setter

	bool Setter::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Setter",
				r->getPosition(),
				r->getBits(),
				end );
		}

		dispID = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"dispID",
				dispID );
		}
		methodInfo = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"methodInfo",
				methodInfo );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Class

	bool Class::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Class",
				r->getPosition(),
				r->getBits(),
				end );
		}

		slotID = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"slotID",
				slotID );
		}
		classInfo = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"classInfo",
				classInfo );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// Function

	bool Function::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"Function",
				r->getPosition(),
				r->getBits(),
				end );
		}

		slotID = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"slotID",
				slotID );
		}
		methodInfo = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"methodInfo",
				methodInfo );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// UnknownOpCode

	bool UnknownOpCode::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"UnknownOpCode",
				r->getPosition(),
				r->getBits(),
				end );
		}


		{
			int sz = len;

			data = new unsigned char[ sz ];
			r->getData( data, sz );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpBkPt

	bool OpBkPt::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpBkPt",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpNop

	bool OpNop::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpNop",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpThrow

	bool OpThrow::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpThrow",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpGetSuper

	bool OpGetSuper::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpGetSuper",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpSetSuper

	bool OpSetSuper::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpSetSuper",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpDXNs

	bool OpDXNs::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpDXNs",
				r->getPosition(),
				r->getBits(),
				end );
		}

		dxns = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"dxns",
				dxns );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpDXNsLate

	bool OpDXNsLate::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpDXNsLate",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpKill

	bool OpKill::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpKill",
				r->getPosition(),
				r->getBits(),
				end );
		}

		address = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"address",
				address );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpLabel

	bool OpLabel::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpLabel",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIfNlt

	bool OpIfNlt::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIfNlt",
				r->getPosition(),
				r->getBits(),
				end );
		}

		target = r->getS24();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"target",
				target );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIfNle

	bool OpIfNle::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIfNle",
				r->getPosition(),
				r->getBits(),
				end );
		}

		target = r->getS24();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"target",
				target );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIfNgt

	bool OpIfNgt::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIfNgt",
				r->getPosition(),
				r->getBits(),
				end );
		}

		target = r->getS24();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"target",
				target );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIfNge

	bool OpIfNge::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIfNge",
				r->getPosition(),
				r->getBits(),
				end );
		}

		target = r->getS24();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"target",
				target );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpJump

	bool OpJump::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpJump",
				r->getPosition(),
				r->getBits(),
				end );
		}

		target = r->getS24();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"target",
				target );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIfTrue

	bool OpIfTrue::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIfTrue",
				r->getPosition(),
				r->getBits(),
				end );
		}

		target = r->getS24();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"target",
				target );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIfFalse

	bool OpIfFalse::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIfFalse",
				r->getPosition(),
				r->getBits(),
				end );
		}

		target = r->getS24();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"target",
				target );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIfEq

	bool OpIfEq::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIfEq",
				r->getPosition(),
				r->getBits(),
				end );
		}

		target = r->getS24();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"target",
				target );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIfNe

	bool OpIfNe::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIfNe",
				r->getPosition(),
				r->getBits(),
				end );
		}

		target = r->getS24();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"target",
				target );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIfLt

	bool OpIfLt::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIfLt",
				r->getPosition(),
				r->getBits(),
				end );
		}

		target = r->getS24();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"target",
				target );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIfLe

	bool OpIfLe::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIfLe",
				r->getPosition(),
				r->getBits(),
				end );
		}

		target = r->getS24();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"target",
				target );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIfGt

	bool OpIfGt::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIfGt",
				r->getPosition(),
				r->getBits(),
				end );
		}

		target = r->getS24();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"target",
				target );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIfGe

	bool OpIfGe::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIfGe",
				r->getPosition(),
				r->getBits(),
				end );
		}

		target = r->getS24();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"target",
				target );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIfStrictEq

	bool OpIfStrictEq::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIfStrictEq",
				r->getPosition(),
				r->getBits(),
				end );
		}

		target = r->getS24();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"target",
				target );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIfStrictNe

	bool OpIfStrictNe::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIfStrictNe",
				r->getPosition(),
				r->getBits(),
				end );
		}

		target = r->getS24();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"target",
				target );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpLookupSwitch

	bool OpLookupSwitch::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpLookupSwitch",
				r->getPosition(),
				r->getBits(),
				end );
		}

		defaulTarget = r->getS24();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"defaulTarget",
				defaulTarget );
		}
		caseCount = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"caseCount",
				caseCount );
		}


		{
			if( ctx->debugTrace ) {
				fprintf( stderr, "PARSE list<%s> %s: %i items, @%i-%i :%i\n",
					"S24",
					"targetTable",

					( caseCount + 1 )
					,
					r->getPosition(),
					r->getBits(),
					end );
			}
			S24 *item;
			for( int i=0; i<
				( caseCount + 1 )
				; i++ ) {
					item = S24::get(r,end,ctx);
					targetTable.append( item );
			}
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpPushWith

	bool OpPushWith::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpPushWith",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpPopScope

	bool OpPopScope::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpPopScope",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpNextName

	bool OpNextName::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpNextName",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpHasNext

	bool OpHasNext::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpHasNext",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpPushNull

	bool OpPushNull::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpPushNull",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpPushUndefined

	bool OpPushUndefined::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpPushUndefined",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpNextValue

	bool OpNextValue::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpNextValue",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpPushByte

	bool OpPushByte::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpPushByte",
				r->getPosition(),
				r->getBits(),
				end );
		}

		value = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"value",
				value );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpPushShort

	bool OpPushShort::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpPushShort",
				r->getPosition(),
				r->getBits(),
				end );
		}

		value = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"value",
				value );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpPushTrue

	bool OpPushTrue::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpPushTrue",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpPushFalse

	bool OpPushFalse::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpPushFalse",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpPushNaN

	bool OpPushNaN::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpPushNaN",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpPop

	bool OpPop::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpPop",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpDup

	bool OpDup::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpDup",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpSwap

	bool OpSwap::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpSwap",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpPushString

	bool OpPushString::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpPushString",
				r->getPosition(),
				r->getBits(),
				end );
		}

		index = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"index",
				index );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpPushInt

	bool OpPushInt::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpPushInt",
				r->getPosition(),
				r->getBits(),
				end );
		}

		index = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"index",
				index );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpPushUInt

	bool OpPushUInt::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpPushUInt",
				r->getPosition(),
				r->getBits(),
				end );
		}

		index = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"index",
				index );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpPushDouble

	bool OpPushDouble::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpPushDouble",
				r->getPosition(),
				r->getBits(),
				end );
		}

		index = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"index",
				index );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpPushScope

	bool OpPushScope::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpPushScope",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpPushNamespace

	bool OpPushNamespace::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpPushNamespace",
				r->getPosition(),
				r->getBits(),
				end );
		}

		index = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"index",
				index );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpHasNext2

	bool OpHasNext2::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpHasNext2",
				r->getPosition(),
				r->getBits(),
				end );
		}

		object = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"object",
				object );
		}
		index = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"index",
				index );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpNewFunction

	bool OpNewFunction::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpNewFunction",
				r->getPosition(),
				r->getBits(),
				end );
		}

		index = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"index",
				index );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpCall

	bool OpCall::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpCall",
				r->getPosition(),
				r->getBits(),
				end );
		}

		argc = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"argc",
				argc );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpConstruct

	bool OpConstruct::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpConstruct",
				r->getPosition(),
				r->getBits(),
				end );
		}

		argc = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"argc",
				argc );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpCallMethod

	bool OpCallMethod::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpCallMethod",
				r->getPosition(),
				r->getBits(),
				end );
		}

		dispID = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"dispID",
				dispID );
		}
		argc = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"argc",
				argc );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpCallStatic

	bool OpCallStatic::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpCallStatic",
				r->getPosition(),
				r->getBits(),
				end );
		}

		methodID = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"methodID",
				methodID );
		}
		argc = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"argc",
				argc );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpCallSuper

	bool OpCallSuper::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpCallSuper",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}
		argc = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"argc",
				argc );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpCallProperty

	bool OpCallProperty::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpCallProperty",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}
		argc = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"argc",
				argc );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpReturnVoid

	bool OpReturnVoid::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpReturnVoid",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpReturnValue

	bool OpReturnValue::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpReturnValue",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpConstructSuper

	bool OpConstructSuper::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpConstructSuper",
				r->getPosition(),
				r->getBits(),
				end );
		}

		argc = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"argc",
				argc );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpConstructProp

	bool OpConstructProp::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpConstructProp",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}
		argc = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"argc",
				argc );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpCallPropLex

	bool OpCallPropLex::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpCallPropLex",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}
		argc = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"argc",
				argc );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpCallSuperVoid

	bool OpCallSuperVoid::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpCallSuperVoid",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}
		argc = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"argc",
				argc );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpCallPropVoid

	bool OpCallPropVoid::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpCallPropVoid",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}
		argc = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"argc",
				argc );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpApplyType

	bool OpApplyType::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpApplyType",
				r->getPosition(),
				r->getBits(),
				end );
		}

		type = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"type",
				type );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpNewObject

	bool OpNewObject::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpNewObject",
				r->getPosition(),
				r->getBits(),
				end );
		}

		argc = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"argc",
				argc );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpNewArray

	bool OpNewArray::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpNewArray",
				r->getPosition(),
				r->getBits(),
				end );
		}

		argc = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"argc",
				argc );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpNewActivation

	bool OpNewActivation::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpNewActivation",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpNewClass

	bool OpNewClass::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpNewClass",
				r->getPosition(),
				r->getBits(),
				end );
		}

		classIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"classIndex",
				classIndex );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpGetDescendants

	bool OpGetDescendants::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpGetDescendants",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpNewCatch

	bool OpNewCatch::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpNewCatch",
				r->getPosition(),
				r->getBits(),
				end );
		}

		exceptionIndex = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"exceptionIndex",
				exceptionIndex );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpFindPropStrict

	bool OpFindPropStrict::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpFindPropStrict",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpFindProperty

	bool OpFindProperty::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpFindProperty",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpFindDef

	bool OpFindDef::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpFindDef",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpGetLex

	bool OpGetLex::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpGetLex",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpSetProperty

	bool OpSetProperty::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpSetProperty",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpGetLocal

	bool OpGetLocal::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpGetLocal",
				r->getPosition(),
				r->getBits(),
				end );
		}

		address = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"address",
				address );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpSetLocal

	bool OpSetLocal::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpSetLocal",
				r->getPosition(),
				r->getBits(),
				end );
		}

		address = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"address",
				address );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpGetGlobalScope

	bool OpGetGlobalScope::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpGetGlobalScope",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpGetScopeObject

	bool OpGetScopeObject::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpGetScopeObject",
				r->getPosition(),
				r->getBits(),
				end );
		}

		scopeIndex = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"scopeIndex",
				scopeIndex );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpGetProperty

	bool OpGetProperty::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpGetProperty",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpInitProperty

	bool OpInitProperty::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpInitProperty",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpDeleteProperty

	bool OpDeleteProperty::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpDeleteProperty",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpGetSlot

	bool OpGetSlot::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpGetSlot",
				r->getPosition(),
				r->getBits(),
				end );
		}

		slotID = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"slotID",
				slotID );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpSetSlot

	bool OpSetSlot::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpSetSlot",
				r->getPosition(),
				r->getBits(),
				end );
		}

		slotID = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"slotID",
				slotID );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpGetGlobalSlot

	bool OpGetGlobalSlot::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpGetGlobalSlot",
				r->getPosition(),
				r->getBits(),
				end );
		}

		slotID = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"slotID",
				slotID );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpSetGlobalSlot

	bool OpSetGlobalSlot::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpSetGlobalSlot",
				r->getPosition(),
				r->getBits(),
				end );
		}

		slotID = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"slotID",
				slotID );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpConvertS

	bool OpConvertS::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpConvertS",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpEscXelem

	bool OpEscXelem::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpEscXelem",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpEscXattr

	bool OpEscXattr::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpEscXattr",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpConvertI

	bool OpConvertI::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpConvertI",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpConvertU

	bool OpConvertU::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpConvertU",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpConvertD

	bool OpConvertD::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpConvertD",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpConvertB

	bool OpConvertB::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpConvertB",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpConvertO

	bool OpConvertO::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpConvertO",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpCheckFilter

	bool OpCheckFilter::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpCheckFilter",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpCoerce

	bool OpCoerce::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpCoerce",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpCoerceB

	bool OpCoerceB::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpCoerceB",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpCoerceA

	bool OpCoerceA::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpCoerceA",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpCoerceI

	bool OpCoerceI::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpCoerceI",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpCoerceD

	bool OpCoerceD::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpCoerceD",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpCoerceS

	bool OpCoerceS::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpCoerceS",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpAsType

	bool OpAsType::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpAsType",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpAsTypeLate

	bool OpAsTypeLate::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpAsTypeLate",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpCoerceU

	bool OpCoerceU::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpCoerceU",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpCoerceO

	bool OpCoerceO::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpCoerceO",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpNegate

	bool OpNegate::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpNegate",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIncrement

	bool OpIncrement::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIncrement",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIncLocal

	bool OpIncLocal::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIncLocal",
				r->getPosition(),
				r->getBits(),
				end );
		}

		address = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"address",
				address );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpDecrement

	bool OpDecrement::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpDecrement",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpDecLocal

	bool OpDecLocal::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpDecLocal",
				r->getPosition(),
				r->getBits(),
				end );
		}

		address = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"address",
				address );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpTypeOf

	bool OpTypeOf::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpTypeOf",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpNot

	bool OpNot::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpNot",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpBitNot

	bool OpBitNot::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpBitNot",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpAdd

	bool OpAdd::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpAdd",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpSubtract

	bool OpSubtract::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpSubtract",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpMultiply

	bool OpMultiply::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpMultiply",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpDivide

	bool OpDivide::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpDivide",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpModulo

	bool OpModulo::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpModulo",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpLShift

	bool OpLShift::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpLShift",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpRShift

	bool OpRShift::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpRShift",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpURShift

	bool OpURShift::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpURShift",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpBitAnd

	bool OpBitAnd::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpBitAnd",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpBitOr

	bool OpBitOr::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpBitOr",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpBitXor

	bool OpBitXor::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpBitXor",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpEquals

	bool OpEquals::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpEquals",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpStrictEquals

	bool OpStrictEquals::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpStrictEquals",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpLessThan

	bool OpLessThan::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpLessThan",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpLessEquals

	bool OpLessEquals::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpLessEquals",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpGreaterThan

	bool OpGreaterThan::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpGreaterThan",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpGreaterEquals

	bool OpGreaterEquals::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpGreaterEquals",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpInstanceOf

	bool OpInstanceOf::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpInstanceOf",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIsType

	bool OpIsType::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIsType",
				r->getPosition(),
				r->getBits(),
				end );
		}

		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIsTypeLate

	bool OpIsTypeLate::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIsTypeLate",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIn

	bool OpIn::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIn",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIncrementI

	bool OpIncrementI::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIncrementI",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpDecrementI

	bool OpDecrementI::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpDecrementI",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpIncLocalI

	bool OpIncLocalI::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpIncLocalI",
				r->getPosition(),
				r->getBits(),
				end );
		}

		address = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"address",
				address );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpDecLocalI

	bool OpDecLocalI::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpDecLocalI",
				r->getPosition(),
				r->getBits(),
				end );
		}

		address = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"address",
				address );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpNegateI

	bool OpNegateI::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpNegateI",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpAddI

	bool OpAddI::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpAddI",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpSubtractI

	bool OpSubtractI::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpSubtractI",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpMultiplyI

	bool OpMultiplyI::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpMultiplyI",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpGetLocal0

	bool OpGetLocal0::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpGetLocal0",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpGetLocal1

	bool OpGetLocal1::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpGetLocal1",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpGetLocal2

	bool OpGetLocal2::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpGetLocal2",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpGetLocal3

	bool OpGetLocal3::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpGetLocal3",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpSetLocal0

	bool OpSetLocal0::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpSetLocal0",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpSetLocal1

	bool OpSetLocal1::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpSetLocal1",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpSetLocal2

	bool OpSetLocal2::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpSetLocal2",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpSetLocal3

	bool OpSetLocal3::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpSetLocal3",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpDebugReg

	bool OpDebugReg::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpDebugReg",
				r->getPosition(),
				r->getBits(),
				end );
		}

		unknown = r->getByte();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"unknown",
				unknown );
		}
		name = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"name",
				name );
		}
		reg = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"reg",
				reg );
		}
		line = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"line",
				line );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpDebugLine

	bool OpDebugLine::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpDebugLine",
				r->getPosition(),
				r->getBits(),
				end );
		}

		line = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"line",
				line );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpDebugFile

	bool OpDebugFile::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpDebugFile",
				r->getPosition(),
				r->getBits(),
				end );
		}

		file = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"file",
				file );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpBkPtLine

	bool OpBkPtLine::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpBkPtLine",
				r->getPosition(),
				r->getBits(),
				end );
		}

		line = r->getU30();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s: %i\n",
				"line",
				line );
		}


		return r->getError() == SWFR_OK;
	}


	//////////////////////////////////// OpTimestamp

	bool OpTimestamp::parse( Reader *r, int end, Context *ctx ) {
		file_offset = r->getPosition();
		if( ctx->debugTrace ) {
			fprintf( stderr, "PARSE %s @%i-%i :%i\n",
				"OpTimestamp",
				r->getPosition(),
				r->getBits(),
				end );
		}



		return r->getError() == SWFR_OK;
	}



}

