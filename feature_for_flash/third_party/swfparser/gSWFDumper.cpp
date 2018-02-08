

#include "SWF.h"

namespace SWF {

void print_indent( int n ) {
	for( int i=0; i<n; i++ ) printf("  ");
}

void Rectangle::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("Rectangle"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "bits"); 
	printf("%i\n", bits);

	print_indent(indent);
	printf("%s: ", "left"); 
	printf("%i\n", left);

	print_indent(indent);
	printf("%s: ", "right"); 
	printf("%i\n", right);

	print_indent(indent);
	printf("%s: ", "top"); 
	printf("%i\n", top);

	print_indent(indent);
	printf("%s: ", "bottom"); 
	printf("%i\n", bottom);

}


void String::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("String"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "value"); 
	printf("%s\n", value?value:"(nil)");

}

void String2::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("String2"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "value"); 
	printf("%s\n", value?value:"(nil)");

}


void DoAction::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x0C);
	
	
	printf("DoAction"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "actions"); 
	{
		printf("[list of %ss]\n", "Action");
		Action *item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}

void Header::addDetection( const char *szTagName, const char *szDetection )
{
	detections.push_back( std::make_pair( std::string(szTagName), std::string(szDetection) ) );
}

std::vector<std::pair<std::string, std::string> > & Header::getDetections()
{
	return detections;
}

void Header::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("Header"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
//	printf("%s: ", "size"); 
//	printf("[%s]\n", "Rectangle");
//	size.dump( indent+1, ctx );

	print_indent(indent);
	printf("%s: ", "framerate"); 
	printf("%i\n", framerate);

	print_indent(indent);
	printf("%s: ", "frames"); 
	printf("%i\n", frames);

	print_indent(indent);
	printf("%s: ", "tags"); 
	{
		printf("[list of %ss]\n", "Tag");
		Tag *item;
		ListItem<Tag>* i;
		i = tags.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}


void Symbol::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("Symbol"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "objectID"); 
	printf("%i\n", objectID);

	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%s\n", name?name:"(nil)");

}

void Parameter::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("Parameter"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "reg"); 
	printf("%i\n", reg);

	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%s\n", name?name:"(nil)");

}

void UChar::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("UChar"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "value"); 
	printf("%i\n", value);

}

void UShort::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("UShort"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "value"); 
	printf("%i\n", value);

}

void ULong::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("ULong"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "value"); 
	printf("%i\n", value);

}

void Short::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("Short"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "value"); 
	printf("%i\n", value);

}

void Float::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("Float"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "value"); 
}

void Double::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("Double"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "value"); 
}

void Kerning::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("Kerning"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "a"); 
	printf("%i\n", a);

	print_indent(indent);
	printf("%s: ", "b"); 
	printf("%i\n", b);

	print_indent(indent);
	printf("%s: ", "adjustment"); 
	printf("%i\n", adjustment);

}

void WideKerning::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("WideKerning"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "a"); 
	printf("%i\n", a);

	print_indent(indent);
	printf("%s: ", "b"); 
	printf("%i\n", b);

	print_indent(indent);
	printf("%s: ", "adjustment"); 
	printf("%i\n", adjustment);

}


void Event::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("Event"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "flags1"); 
	printf("%i\n", flags1);

	if( ctx->swfVersion>=6 ) {
		
	print_indent(indent);
	printf("%s: ", "flags2"); 
	printf("%i\n", flags2);

	}

	if( (flags1 | flags2) ) {
		
	print_indent(indent);
	printf("%s: ", "actionLength"); 
	print_indent(indent);
	printf("%s: ", "actions"); 
	{
		printf("[list of %ss]\n", "Action");
		Action *item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	}

}


void U30::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("U30"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "value"); 
	printf("%i\n", value);

}

void S24::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("S24"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "value"); 
	printf("%i\n", value);

}

void ValueKind::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("ValueKind"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "index"); 
	printf("%i\n", index);

	print_indent(indent);
	printf("%s: ", "kind"); 
	printf("%i\n", kind);

}

void MethodInfo::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("MethodInfo"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "paramCount"); 
	printf("%i\n", paramCount);

	print_indent(indent);
	printf("%s: ", "retType"); 
	printf("%i\n", retType);

	print_indent(indent);
	printf("%s: ", "paramTypes"); 
	{
		printf("[list of %ss]\n", "U30");
		U30 *item;
		ListItem<U30>* i;
		i = paramTypes.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "nameIndex"); 
	printf("%i\n", nameIndex);

	print_indent(indent);
	printf("%s: ", "hasParamNames"); 
	printf("%i\n", hasParamNames);

	print_indent(indent);
	printf("%s: ", "setSDXNs"); 
	printf("%i\n", setSDXNs);

	print_indent(indent);
	printf("%s: ", "isExplicit"); 
	printf("%i\n", isExplicit);

	print_indent(indent);
	printf("%s: ", "ignoreRest"); 
	printf("%i\n", ignoreRest);

	print_indent(indent);
	printf("%s: ", "hasOptional"); 
	printf("%i\n", hasOptional);

	print_indent(indent);
	printf("%s: ", "needRest"); 
	printf("%i\n", needRest);

	print_indent(indent);
	printf("%s: ", "needActivation"); 
	printf("%i\n", needActivation);

	print_indent(indent);
	printf("%s: ", "needArguments"); 
	printf("%i\n", needArguments);

	if( hasOptional ) {
		
		
	print_indent(indent);
	printf("%s: ", "optionalCount"); 
	printf("%i\n", optionalCount);

	print_indent(indent);
	printf("%s: ", "optional"); 
	{
		printf("[list of %ss]\n", "ValueKind");
		ValueKind *item;
		ListItem<ValueKind>* i;
		i = optional.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	}

	if( hasParamNames ) {
		
		
	print_indent(indent);
	printf("%s: ", "paramNames"); 
	{
		printf("[list of %ss]\n", "U30");
		U30 *item;
		ListItem<U30>* i;
		i = paramNames.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	}

}

void MetadataInfo::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("MetadataInfo"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "nameIndex"); 
	printf("%i\n", nameIndex);

	print_indent(indent);
	printf("%s: ", "valuesCount"); 
	printf("%i\n", valuesCount);

	print_indent(indent);
	printf("%s: ", "keys"); 
	{
		printf("[list of %ss]\n", "U30");
		U30 *item;
		ListItem<U30>* i;
		i = keys.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "values"); 
	{
		printf("[list of %ss]\n", "U30");
		U30 *item;
		ListItem<U30>* i;
		i = values.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}

void NamespaceSet::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("NamespaceSet"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "count"); 
	printf("%i\n", count);

	print_indent(indent);
	printf("%s: ", "namespaces"); 
	{
		printf("[list of %ss]\n", "U30");
		U30 *item;
		ListItem<U30>* i;
		i = namespaces.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}

void TraitInfo::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("TraitInfo"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "nameIndex"); 
	printf("%i\n", nameIndex);

	print_indent(indent);
	printf("%s: ", "reserved"); 
	printf("%i\n", reserved);

	print_indent(indent);
	printf("%s: ", "hasMetadata"); 
	printf("%i\n", hasMetadata);

	print_indent(indent);
	printf("%s: ", "override"); 
	printf("%i\n", override);

	print_indent(indent);
	printf("%s: ", "final"); 
	printf("%i\n", final);

	print_indent(indent);
	printf("%s: ", "trait"); 
	{
		printf("[list of %ss]\n", "Trait");
		Trait *item;
		ListItem<Trait>* i;
		i = trait.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	if( hasMetadata ) {
		
		
	print_indent(indent);
	printf("%s: ", "metadataCount"); 
	printf("%i\n", metadataCount);

	print_indent(indent);
	printf("%s: ", "metadata"); 
	{
		printf("[list of %ss]\n", "U30");
		U30 *item;
		ListItem<U30>* i;
		i = metadata.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	}

}

void InstanceInfo::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("InstanceInfo"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "nameIndex"); 
	printf("%i\n", nameIndex);

	print_indent(indent);
	printf("%s: ", "superIndex"); 
	printf("%i\n", superIndex);

	print_indent(indent);
	printf("%s: ", "reserved"); 
	printf("%i\n", reserved);

	print_indent(indent);
	printf("%s: ", "hasProtectedNS"); 
	printf("%i\n", hasProtectedNS);

	print_indent(indent);
	printf("%s: ", "interface"); 
	printf("%i\n", interface);

	print_indent(indent);
	printf("%s: ", "final"); 
	printf("%i\n", final);

	print_indent(indent);
	printf("%s: ", "sealed"); 
	printf("%i\n", sealed);

	if( hasProtectedNS ) {
		
		
	print_indent(indent);
	printf("%s: ", "protectedNS"); 
	printf("%i\n", protectedNS);

	}

	print_indent(indent);
	printf("%s: ", "interfaceCount"); 
	printf("%i\n", interfaceCount);

	print_indent(indent);
	printf("%s: ", "interfaces"); 
	{
		printf("[list of %ss]\n", "U30");
		U30 *item;
		ListItem<U30>* i;
		i = interfaces.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "iInitIndex"); 
	printf("%i\n", iInitIndex);

	print_indent(indent);
	printf("%s: ", "traitCount"); 
	printf("%i\n", traitCount);

	print_indent(indent);
	printf("%s: ", "traits"); 
	{
		printf("[list of %ss]\n", "TraitInfo");
		TraitInfo *item;
		ListItem<TraitInfo>* i;
		i = traits.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}

void ClassInfo::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("ClassInfo"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "cInitIndex"); 
	printf("%i\n", cInitIndex);

	print_indent(indent);
	printf("%s: ", "traitCount"); 
	printf("%i\n", traitCount);

	print_indent(indent);
	printf("%s: ", "traits"); 
	{
		printf("[list of %ss]\n", "TraitInfo");
		TraitInfo *item;
		ListItem<TraitInfo>* i;
		i = traits.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}

void ScriptInfo::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("ScriptInfo"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "initIndex"); 
	printf("%i\n", initIndex);

	print_indent(indent);
	printf("%s: ", "traitCount"); 
	printf("%i\n", traitCount);

	print_indent(indent);
	printf("%s: ", "traits"); 
	{
		printf("[list of %ss]\n", "TraitInfo");
		TraitInfo *item;
		ListItem<TraitInfo>* i;
		i = traits.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}

void Exception::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("Exception"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "tryStart"); 
	printf("%i\n", tryStart);

	print_indent(indent);
	printf("%s: ", "tryEnd"); 
	printf("%i\n", tryEnd);

	print_indent(indent);
	printf("%s: ", "target"); 
	printf("%i\n", target);

	print_indent(indent);
	printf("%s: ", "type"); 
	printf("%i\n", type);

	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

}

void MethodBody::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("MethodBody"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "methodInfo"); 
	printf("%i\n", methodInfo);

	print_indent(indent);
	printf("%s: ", "maxStack"); 
	printf("%i\n", maxStack);

	print_indent(indent);
	printf("%s: ", "maxRegs"); 
	printf("%i\n", maxRegs);

	print_indent(indent);
	printf("%s: ", "scopeDepth"); 
	printf("%i\n", scopeDepth);

	print_indent(indent);
	printf("%s: ", "maxScope"); 
	printf("%i\n", maxScope);

	print_indent(indent);
	printf("%s: ", "codeLength"); 
	printf("%i\n", codeLength);

	print_indent(indent);
	printf("%s: ", "code"); 
	{
		printf("[list of %ss]\n", "OpCode");
		OpCode *item;
		ListItem<OpCode>* i;
		i = code.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "exceptionCount"); 
	printf("%i\n", exceptionCount);

	print_indent(indent);
	printf("%s: ", "exceptions"); 
	{
		printf("[list of %ss]\n", "Exception");
		Exception *item;
		ListItem<Exception>* i;
		i = exceptions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "traitCount"); 
	printf("%i\n", traitCount);

	print_indent(indent);
	printf("%s: ", "traits"); 
	{
		printf("[list of %ss]\n", "TraitInfo");
		TraitInfo *item;
		ListItem<TraitInfo>* i;
		i = traits.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}

void Constants::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("Constants"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "intCount"); 
	printf("%i\n", intCount);

	print_indent(indent);
	printf("%s: ", "ints"); 
	{
		printf("[list of %ss]\n", "U30");
		U30 *item;
		ListItem<U30>* i;
		i = ints.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "uintCount"); 
	printf("%i\n", uintCount);

	print_indent(indent);
	printf("%s: ", "uints"); 
	{
		printf("[list of %ss]\n", "U30");
		U30 *item;
		ListItem<U30>* i;
		i = uints.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "doubleCount"); 
	printf("%i\n", doubleCount);

	print_indent(indent);
	printf("%s: ", "doubles"); 
	{
		printf("[list of %ss]\n", "Double");
		Double *item;
		ListItem<Double>* i;
		i = doubles.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "stringCount"); 
	printf("%i\n", stringCount);

	print_indent(indent);
	printf("%s: ", "strings"); 
	{
		printf("[list of %ss]\n", "String2");
		String2 *item;
		ListItem<String2>* i;
		i = strings.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "namespaceConstantCount"); 
	printf("%i\n", namespaceConstantCount);

	print_indent(indent);
	printf("%s: ", "namespaces"); 
	{
		printf("[list of %ss]\n", "NamespaceConstant");
		NamespaceConstant *item;
		ListItem<NamespaceConstant>* i;
		i = namespaces.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "namespaceSetCount"); 
	printf("%i\n", namespaceSetCount);

	print_indent(indent);
	printf("%s: ", "namespaceSets"); 
	{
		printf("[list of %ss]\n", "NamespaceSet");
		NamespaceSet *item;
		ListItem<NamespaceSet>* i;
		i = namespaceSets.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "multinameConstantCount"); 
	printf("%i\n", multinameConstantCount);

	print_indent(indent);
	printf("%s: ", "multinames"); 
	{
		printf("[list of %ss]\n", "MultinameConstant");
		MultinameConstant *item;
		ListItem<MultinameConstant>* i;
		i = multinames.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}

void Action3::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("Action3"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "minorVersion"); 
	printf("%i\n", minorVersion);

	print_indent(indent);
	printf("%s: ", "majorVersion"); 
	printf("%i\n", majorVersion);

	print_indent(indent);
	printf("%s: ", "constants"); 
	printf("[%s]\n", "Constants");
	constants.dump( indent+1, ctx );

	print_indent(indent);
	printf("%s: ", "methodInfoCount"); 
	printf("%i\n", methodInfoCount);

	print_indent(indent);
	printf("%s: ", "methods"); 
	{
		printf("[list of %ss]\n", "MethodInfo");
		MethodInfo *item;
		ListItem<MethodInfo>* i;
		i = methods.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "metadataInfoCount"); 
	printf("%i\n", metadataInfoCount);

	print_indent(indent);
	printf("%s: ", "metadata"); 
	{
		printf("[list of %ss]\n", "MetadataInfo");
		MetadataInfo *item;
		ListItem<MetadataInfo>* i;
		i = metadata.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "classCount"); 
	printf("%i\n", classCount);

	print_indent(indent);
	printf("%s: ", "instances"); 
	{
		printf("[list of %ss]\n", "InstanceInfo");
		InstanceInfo *item;
		ListItem<InstanceInfo>* i;
		i = instances.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "classes"); 
	{
		printf("[list of %ss]\n", "ClassInfo");
		ClassInfo *item;
		ListItem<ClassInfo>* i;
		i = classes.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "scriptCount"); 
	printf("%i\n", scriptCount);

	print_indent(indent);
	printf("%s: ", "scripts"); 
	{
		printf("[list of %ss]\n", "ScriptInfo");
		ScriptInfo *item;
		ListItem<ScriptInfo>* i;
		i = scripts.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "methodBodyCount"); 
	printf("%i\n", methodBodyCount);

	print_indent(indent);
	printf("%s: ", "methodBodies"); 
	{
		printf("[list of %ss]\n", "MethodBody");
		MethodBody *item;
		ListItem<MethodBody>* i;
		i = methodBodies.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}

void ZoneData::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("ZoneData"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "position"); 
	print_indent(indent);
	printf("%s: ", "size"); 
}

void ZoneArray::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
	
	printf("ZoneArray"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "count"); 
	printf("%i\n", count);

	print_indent(indent);
	printf("%s: ", "zones"); 
	{
		printf("[list of %ss]\n", "ZoneData");
		ZoneData *item;
		ListItem<ZoneData>* i;
		i = zones.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "zoneX"); 
	printf("%i\n", zoneX);

	print_indent(indent);
	printf("%s: ", "zoneY"); 
	printf("%i\n", zoneY);

	print_indent(indent);
	printf("%s: ", "reserved"); 
	printf("%i\n", reserved);

}

void UnknownFilter::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //-1);
	
	
	printf("UnknownFilter"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "data"); 
	printf("(length %i)\n", len );
	if( len && data != NULL ) {
		int i=0;
		while( i<len ) {
			print_indent( indent+1 );
			for( int n=0; n<8 && i<len; n++ ) {
				printf(" %02X",  data[i] );
				i++;
			}
			printf("\n");
		}
	}

}


void UnknownTag::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //-1);
	
	
	printf("UnknownTag"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "data"); 
	printf("(length %i)\n", len );
	if( len && data != NULL ) {
		int i=0;
		while( i<len ) {
			print_indent( indent+1 );
			for( int n=0; n<8 && i<len; n++ ) {
				printf(" %02X",  data[i] );
				i++;
			}
			printf("\n");
		}
	}

}

void End::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x00);
	
	
	printf("End"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}


void Export::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x38);
	
	
	printf("Export"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "count"); 
	printf("%i\n", count);

	print_indent(indent);
	printf("%s: ", "symbols"); 
	{
		printf("[list of %ss]\n", "Symbol");
		Symbol *item;
		ListItem<Symbol>* i;
		i = symbols.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}

void Import::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x39);
	
	
	printf("Import"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "url"); 
	printf("%s\n", url?url:"(nil)");

	print_indent(indent);
	printf("%s: ", "count"); 
	printf("%i\n", count);

	print_indent(indent);
	printf("%s: ", "symbols"); 
	{
		printf("[list of %ss]\n", "Symbol");
		Symbol *item;
		ListItem<Symbol>* i;
		i = symbols.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}

void DoInitAction::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x3B);
	
	
	printf("DoInitAction"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "sprite"); 
	printf("%i\n", sprite);

	print_indent(indent);
	printf("%s: ", "actions"); 
	{
		printf("[list of %ss]\n", "Action");
		Action *item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}


void ScriptLimits::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x41);
	
	
	printf("ScriptLimits"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "maxRecursionDepth"); 
	printf("%i\n", maxRecursionDepth);

	print_indent(indent);
	printf("%s: ", "timeout"); 
	printf("%i\n", timeout);

}


void ImportAssets2::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x47);
	
	
	printf("ImportAssets2"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "url"); 
	printf("%s\n", url?url:"(nil)");

	print_indent(indent);
	printf("%s: ", "reserved1"); 
	printf("%i\n", reserved1);

	print_indent(indent);
	printf("%s: ", "reserved2"); 
	printf("%i\n", reserved2);

	print_indent(indent);
	printf("%s: ", "count"); 
	printf("%i\n", count);

	print_indent(indent);
	printf("%s: ", "symbols"); 
	{
		printf("[list of %ss]\n", "Symbol");
		Symbol *item;
		ListItem<Symbol>* i;
		i = symbols.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}

void FileAttributes::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x45);
	
	
	printf("FileAttributes"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "reserved1"); 
	printf("%i\n", reserved1);

	print_indent(indent);
	printf("%s: ", "hasMetaData"); 
	printf("%i\n", hasMetaData);

	if( ctx->swfVersion < 9 ) {
		
	print_indent(indent);
	printf("%s: ", "reserved2"); 
	printf("%i\n", reserved2);

	}

	if( ctx->swfVersion >= 9 ) {
		
	print_indent(indent);
	printf("%s: ", "allowABC"); 
	printf("%i\n", allowABC);

	print_indent(indent);
	printf("%s: ", "suppressCrossDomainCaching"); 
	printf("%i\n", suppressCrossDomainCaching);

	print_indent(indent);
	printf("%s: ", "swfRelativeURLs"); 
	printf("%i\n", swfRelativeURLs);

	}

	print_indent(indent);
	printf("%s: ", "useNetwork"); 
	printf("%i\n", useNetwork);

	print_indent(indent);
	printf("%s: ", "reserved3"); 
	printf("%i\n", reserved3);

}


void Metadata::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x4D);
	
	
	printf("Metadata"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "RDF"); 
}


void DoABC::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x48);
	
	
	printf("DoABC"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "actions"); 
	printf("[%s]\n", "Action3");
	actions.dump( indent+1, ctx );

}

void DoABCDefine::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x52);
	
	
	printf("DoABCDefine"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "flags"); 
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%s\n", name?name:"(nil)");

	print_indent(indent);
	printf("%s: ", "actions"); 
	printf("[%s]\n", "Action3");
	actions.dump( indent+1, ctx );

}

void SymbolClass::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x4C);
	
	
	printf("SymbolClass"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "count"); 
	printf("%i\n", count);

	print_indent(indent);
	printf("%s: ", "symbols"); 
	{
		printf("[list of %ss]\n", "Symbol");
		Symbol *item;
		ListItem<Symbol>* i;
		i = symbols.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}


void DefineBinaryData::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x57);
	
	
	printf("DefineBinaryData"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "objectID"); 
	printf("%i\n", objectID);

	print_indent(indent);
	printf("%s: ", "reserved"); 
	print_indent(indent);
	printf("%s: ", "data"); 
	printf("[%s]\n", "Rest");
	data.dump( indent+1, ctx );

}


void EnableDebugger::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x3A);
	
	
	printf("EnableDebugger"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "password"); 
	printf("%s\n", password?password:"(nil)");

}

void EnableDebugger2::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x40);
	
	
	printf("EnableDebugger2"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "reserved"); 
	printf("%i\n", reserved);

	print_indent(indent);
	printf("%s: ", "password"); 
	printf("%s\n", password?password:"(nil)");

}

void StackString::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x00);
	
	
	printf("StackString"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "value"); 
	printf("%s\n", value?value:"(nil)");

}

void StackFloat::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x01);
	
	
	printf("StackFloat"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "value"); 
}

void StackNull::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x02);
	
	
	printf("StackNull"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void StackUndefined::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x03);
	
	
	printf("StackUndefined"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void StackRegister::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x04);
	
	
	printf("StackRegister"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "reg"); 
	printf("%i\n", reg);

}

void StackBoolean::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x05);
	
	
	printf("StackBoolean"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "value"); 
	printf("%i\n", value);

}

void StackDouble::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x06);
	
	
	printf("StackDouble"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "value"); 
}

void StackInteger::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x07);
	
	
	printf("StackInteger"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "value"); 
}

void StackDictionaryLookup::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x08);
	
	
	printf("StackDictionaryLookup"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "index"); 
	printf("%i\n", index);

}

void StackLargeDictionaryLookup::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x09);
	
	
	printf("StackLargeDictionaryLookup"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "index"); 
	printf("%i\n", index);

}

void UnknownAction::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //-1);
	
	
	printf("UnknownAction"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "data"); 
	printf("(length %i)\n", len );
	if( len && data != NULL ) {
		int i=0;
		while( i<len ) {
			print_indent( indent+1 );
			for( int n=0; n<8 && i<len; n++ ) {
				printf(" %02X",  data[i] );
				i++;
			}
			printf("\n");
		}
	}

}

void EndAction::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x00);
	
	
	printf("EndAction"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}


void AddCast::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x0A);
	
	
	printf("AddCast"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void Substract::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x0B);
	
	
	printf("Substract"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void Mulitply::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x0C);
	
	
	printf("Mulitply"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void Divide::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x0D);
	
	
	printf("Divide"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void EqualCast::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x0E);
	
	
	printf("EqualCast"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void LessThanCast::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x0F);
	
	
	printf("LessThanCast"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void LogicalAND::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x10);
	
	
	printf("LogicalAND"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void LogicalOR::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x11);
	
	
	printf("LogicalOR"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void LogicalNOT::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x12);
	
	
	printf("LogicalNOT"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void StringEqual::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x13);
	
	
	printf("StringEqual"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void StringLength::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x14);
	
	
	printf("StringLength"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void SubString::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x15);
	
	
	printf("SubString"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void Pop::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x17);
	
	
	printf("Pop"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void IntegralPart::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x18);
	
	
	printf("IntegralPart"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void GetVariable::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x1C);
	
	
	printf("GetVariable"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void SetVariable::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x1D);
	
	
	printf("SetVariable"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void SetTargetDynamic::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x20);
	
	
	printf("SetTargetDynamic"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void ConcatenateString::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x21);
	
	
	printf("ConcatenateString"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void GetProperty::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x22);
	
	
	printf("GetProperty"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void SetProperty::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x23);
	
	
	printf("SetProperty"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void DuplicateSprite::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x24);
	
	
	printf("DuplicateSprite"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void RemoveSprite::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x25);
	
	
	printf("RemoveSprite"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void Trace::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x26);
	
	
	printf("Trace"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}


void StringLessThan::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x29);
	
	
	printf("StringLessThan"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void Throw::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x2A);
	
	
	printf("Throw"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void CastObject::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x2B);
	
	
	printf("CastObject"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void Implements::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x2C);
	
	
	printf("Implements"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void Random::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x30);
	
	
	printf("Random"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void MultibyteStringLength::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x31);
	
	
	printf("MultibyteStringLength"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void ORD::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x32);
	
	
	printf("ORD"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void CHR::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x33);
	
	
	printf("CHR"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void GetTimer::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x34);
	
	
	printf("GetTimer"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void MultibyteSubString::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x35);
	
	
	printf("MultibyteSubString"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void MultibyteORD::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x36);
	
	
	printf("MultibyteORD"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void MultibyteCHR::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x37);
	
	
	printf("MultibyteCHR"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void Delete::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x3A);
	
	
	printf("Delete"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void DeleteAll::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x3B);
	
	
	printf("DeleteAll"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void SetLocalVariable::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x3C);
	
	
	printf("SetLocalVariable"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void CallFunction::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x3D);
	
	
	printf("CallFunction"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void Return::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x3E);
	
	
	printf("Return"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void Modulo::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x3F);
	
	
	printf("Modulo"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void New::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x40);
	
	
	printf("New"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void DeclareLocalVariable::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x41);
	
	
	printf("DeclareLocalVariable"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void DeclareArray::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x42);
	
	
	printf("DeclareArray"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void DeclareObject::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x43);
	
	
	printf("DeclareObject"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void TypeOf::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x44);
	
	
	printf("TypeOf"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void GetTarget::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x45);
	
	
	printf("GetTarget"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void Enumerate::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x46);
	
	
	printf("Enumerate"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void AddTyped::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x47);
	
	
	printf("AddTyped"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void LessThanTyped::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x48);
	
	
	printf("LessThanTyped"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void EqualTyped::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x49);
	
	
	printf("EqualTyped"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void DefineNumber::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x4A);
	
	
	printf("DefineNumber"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void DefineString::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x4B);
	
	
	printf("DefineString"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void Duplicate::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x4C);
	
	
	printf("Duplicate"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void Swap::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x4D);
	
	
	printf("Swap"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void GetMember::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x4E);
	
	
	printf("GetMember"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void SetMember::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x4F);
	
	
	printf("SetMember"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void Increment::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x50);
	
	
	printf("Increment"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void Decrement::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x51);
	
	
	printf("Decrement"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void CallMethod::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x52);
	
	
	printf("CallMethod"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void NewMethod::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x53);
	
	
	printf("NewMethod"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void InstanceOf::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x54);
	
	
	printf("InstanceOf"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void EnumerateObject::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x55);
	
	
	printf("EnumerateObject"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void AND::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x60);
	
	
	printf("AND"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OR::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x61);
	
	
	printf("OR"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void XOR::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x62);
	
	
	printf("XOR"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void ShiftLeft::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x63);
	
	
	printf("ShiftLeft"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void ShiftRight::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x64);
	
	
	printf("ShiftRight"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void ShiftRightUnsigned::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x65);
	
	
	printf("ShiftRightUnsigned"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void StrictEqual::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x66);
	
	
	printf("StrictEqual"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void GreaterThanTyped::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x67);
	
	
	printf("GreaterThanTyped"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void StringGreaterThan::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x68);
	
	
	printf("StringGreaterThan"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void Extends::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x69);
	
	
	printf("Extends"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void GotoFrame::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x81);
	
	
	printf("GotoFrame"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "frame"); 
	printf("%i\n", frame);

}

void GetURL::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x83);
	
	
	printf("GetURL"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "url"); 
	printf("%s\n", url?url:"(nil)");

	print_indent(indent);
	printf("%s: ", "target"); 
	printf("%s\n", target?target:"(nil)");

}

void StoreRegister::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x87);
	
	
	printf("StoreRegister"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "reg"); 
	printf("%i\n", reg);

}

void Dictionary::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x88);
	
	
	printf("Dictionary"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "length"); 
	printf("%i\n", length);

	print_indent(indent);
	printf("%s: ", "strings"); 
	{
		printf("[list of %ss]\n", "String");
		String *item;
		ListItem<String>* i;
		i = strings.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}

void WaitForFrame::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x8A);
	
	
	printf("WaitForFrame"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "frame"); 
	printf("%i\n", frame);

	print_indent(indent);
	printf("%s: ", "skip"); 
	printf("%i\n", skip);

}

void SetTarget::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x8B);
	
	
	printf("SetTarget"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "label"); 
	printf("%s\n", label?label:"(nil)");

}

void GotoLabel::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x8C);
	
	
	printf("GotoLabel"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "label"); 
	printf("%s\n", label?label:"(nil)");

}

void WaitForFrameDynamic::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x8D);
	
	
	printf("WaitForFrameDynamic"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "frame"); 
	printf("%i\n", frame);

	print_indent(indent);
	printf("%s: ", "skip"); 
	printf("%i\n", skip);

}

void DeclareFunction2::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x8E);
	
	
	printf("DeclareFunction2"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%s\n", name?name:"(nil)");

	print_indent(indent);
	printf("%s: ", "argc"); 
	printf("%i\n", argc);

	print_indent(indent);
	printf("%s: ", "regc"); 
	printf("%i\n", regc);

	print_indent(indent);
	printf("%s: ", "preloadParent"); 
	printf("%i\n", preloadParent);

	print_indent(indent);
	printf("%s: ", "preloadRoot"); 
	printf("%i\n", preloadRoot);

	print_indent(indent);
	printf("%s: ", "suppressSuper"); 
	printf("%i\n", suppressSuper);

	print_indent(indent);
	printf("%s: ", "preloadSuper"); 
	printf("%i\n", preloadSuper);

	print_indent(indent);
	printf("%s: ", "suppressArguments"); 
	printf("%i\n", suppressArguments);

	print_indent(indent);
	printf("%s: ", "preloadArguments"); 
	printf("%i\n", preloadArguments);

	print_indent(indent);
	printf("%s: ", "suppressThis"); 
	printf("%i\n", suppressThis);

	print_indent(indent);
	printf("%s: ", "preloadThis"); 
	printf("%i\n", preloadThis);

	print_indent(indent);
	printf("%s: ", "reserved"); 
	printf("%i\n", reserved);

	print_indent(indent);
	printf("%s: ", "preloadGlobal"); 
	printf("%i\n", preloadGlobal);

	print_indent(indent);
	printf("%s: ", "args"); 
	{
		printf("[list of %ss]\n", "Parameter");
		Parameter *item;
		ListItem<Parameter>* i;
		i = args.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "length"); 
	printf("%i\n", length);

	print_indent(indent);
	printf("%s: ", "actions"); 
	{
		printf("[list of %ss]\n", "Action");
		Action *item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}

void Try::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x8F);
	
	
	printf("Try"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "reserved"); 
	printf("%i\n", reserved);

	print_indent(indent);
	printf("%s: ", "catchInRegister"); 
	printf("%i\n", catchInRegister);

	print_indent(indent);
	printf("%s: ", "doFinally"); 
	printf("%i\n", doFinally);

	print_indent(indent);
	printf("%s: ", "doCatch"); 
	printf("%i\n", doCatch);

	print_indent(indent);
	printf("%s: ", "trySize"); 
	printf("%i\n", trySize);

	print_indent(indent);
	printf("%s: ", "catchSize"); 
	printf("%i\n", catchSize);

	print_indent(indent);
	printf("%s: ", "finallySize"); 
	printf("%i\n", finallySize);

	if( catchInRegister ) {
		
		
	print_indent(indent);
	printf("%s: ", "reg"); 
	printf("%i\n", reg);

	}

}

void With::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x94);
	
	
	printf("With"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "size"); 
	printf("%i\n", size);

}

void PushData::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x96);
	
	
	printf("PushData"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "items"); 
	{
		printf("[list of %ss]\n", "StackItem");
		StackItem *item;
		ListItem<StackItem>* i;
		i = items.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}

void GetURL2::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x9A);
	
	
	printf("GetURL2"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "method"); 
	printf("%i\n", method);

}

void DeclareFunction::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x9B);
	
	
	printf("DeclareFunction"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%s\n", name?name:"(nil)");

	print_indent(indent);
	printf("%s: ", "argc"); 
	printf("%i\n", argc);

	print_indent(indent);
	printf("%s: ", "args"); 
	{
		printf("[list of %ss]\n", "String");
		String *item;
		ListItem<String>* i;
		i = args.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

	print_indent(indent);
	printf("%s: ", "length"); 
	printf("%i\n", length);

}

void BranchAlways::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x99);
	
	
	printf("BranchAlways"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "byteOffset"); 
	printf("%i\n", byteOffset);

}

void BranchIfTrue::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x9D);
	
	
	printf("BranchIfTrue"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "byteOffset"); 
	printf("%i\n", byteOffset);

}

void CallFrame::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x9E);
	
	
	printf("CallFrame"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void GotoExpression::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x9F);
	
	
	printf("GotoExpression"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "play"); 
	printf("%i\n", play);

}

void PrivateNamespace::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //5);
	
	
	printf("PrivateNamespace"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "index"); 
	printf("%i\n", index);

}

void Namespace::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //8);
	
	
	printf("Namespace"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "index"); 
	printf("%i\n", index);

}

void PackageNamespace::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //22);
	
	
	printf("PackageNamespace"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "index"); 
	printf("%i\n", index);

}

void PackageInternalNamespace::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //23);
	
	
	printf("PackageInternalNamespace"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "index"); 
	printf("%i\n", index);

}

void ProtectedNamespace::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //24);
	
	
	printf("ProtectedNamespace"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "index"); 
	printf("%i\n", index);

}

void ExplicitNamespace::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //25);
	
	
	printf("ExplicitNamespace"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "index"); 
	printf("%i\n", index);

}

void MultinameLNamespace::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //26);
	
	
	printf("MultinameLNamespace"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "index"); 
	printf("%i\n", index);

}

void QName::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //7);
	
	
	printf("QName"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "namespaceIndex"); 
	printf("%i\n", namespaceIndex);

	print_indent(indent);
	printf("%s: ", "nameIndex"); 
	printf("%i\n", nameIndex);

}

void QNameA::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //13);
	
	
	printf("QNameA"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "namespaceIndex"); 
	printf("%i\n", namespaceIndex);

	print_indent(indent);
	printf("%s: ", "nameIndex"); 
	printf("%i\n", nameIndex);

}

void Multiname::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //9);
	
	
	printf("Multiname"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "nameIndex"); 
	printf("%i\n", nameIndex);

	print_indent(indent);
	printf("%s: ", "namespaceSetIndex"); 
	printf("%i\n", namespaceSetIndex);

}

void MultinameA::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //14);
	
	
	printf("MultinameA"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "nameIndex"); 
	printf("%i\n", nameIndex);

	print_indent(indent);
	printf("%s: ", "namespaceSetIndex"); 
	printf("%i\n", namespaceSetIndex);

}

void RTQName::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //15);
	
	
	printf("RTQName"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "nameIndex"); 
	printf("%i\n", nameIndex);

}

void RTQNameA::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //16);
	
	
	printf("RTQNameA"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "nameIndex"); 
	printf("%i\n", nameIndex);

}

void MultinameL::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //27);
	
	
	printf("MultinameL"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "namespaceSetIndex"); 
	printf("%i\n", namespaceSetIndex);

}

void RTQNameL::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //17);
	
	
	printf("RTQNameL"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void RTQNameLA::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //18);
	
	
	printf("RTQNameLA"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void TypeName::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //29);
	
	
	printf("TypeName"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "nameIndex"); 
	printf("%i\n", nameIndex);

	print_indent(indent);
	printf("%s: ", "nameCount"); 
	printf("%i\n", nameCount);

	print_indent(indent);
	printf("%s: ", "types"); 
	{
		printf("[list of %ss]\n", "U30");
		U30 *item;
		ListItem<U30>* i;
		i = types.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}

void Slot::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0);
	
	
	printf("Slot"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "slotID"); 
	printf("%i\n", slotID);

	print_indent(indent);
	printf("%s: ", "typeIndex"); 
	printf("%i\n", typeIndex);

	print_indent(indent);
	printf("%s: ", "valueIndex"); 
	printf("%i\n", valueIndex);

	if( valueIndex != 0 ) {
		
	print_indent(indent);
	printf("%s: ", "valueKind"); 
	printf("%i\n", valueKind);

	}

}

void Const::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //6);
	
	
	printf("Const"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "slotID"); 
	printf("%i\n", slotID);

	print_indent(indent);
	printf("%s: ", "typeIndex"); 
	printf("%i\n", typeIndex);

	print_indent(indent);
	printf("%s: ", "valueIndex"); 
	printf("%i\n", valueIndex);

	if( valueIndex != 0 ) {
		
	print_indent(indent);
	printf("%s: ", "valueKind"); 
	printf("%i\n", valueKind);

	}

}

void Method::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //1);
	
	
	printf("Method"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "dispID"); 
	printf("%i\n", dispID);

	print_indent(indent);
	printf("%s: ", "methodInfo"); 
	printf("%i\n", methodInfo);

}

void Getter::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //2);
	
	
	printf("Getter"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "dispID"); 
	printf("%i\n", dispID);

	print_indent(indent);
	printf("%s: ", "methodInfo"); 
	printf("%i\n", methodInfo);

}

void Setter::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //3);
	
	
	printf("Setter"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "dispID"); 
	printf("%i\n", dispID);

	print_indent(indent);
	printf("%s: ", "methodInfo"); 
	printf("%i\n", methodInfo);

}

void Class::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //4);
	
	
	printf("Class"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "slotID"); 
	printf("%i\n", slotID);

	print_indent(indent);
	printf("%s: ", "classInfo"); 
	printf("%i\n", classInfo);

}

void Function::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //5);
	
	
	printf("Function"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "slotID"); 
	printf("%i\n", slotID);

	print_indent(indent);
	printf("%s: ", "methodInfo"); 
	printf("%i\n", methodInfo);

}

void UnknownOpCode::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //-1);
	
	
	printf("UnknownOpCode"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "data"); 
	printf("(length %i)\n", len );
	if( len && data != NULL ) {
		int i=0;
		while( i<len ) {
			print_indent( indent+1 );
			for( int n=0; n<8 && i<len; n++ ) {
				printf(" %02X",  data[i] );
				i++;
			}
			printf("\n");
		}
	}

}

void OpBkPt::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x01);
	
	
	printf("OpBkPt"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpNop::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x02);
	
	
	printf("OpNop"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpThrow::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x03);
	
	
	printf("OpThrow"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpGetSuper::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x04);
	
	
	printf("OpGetSuper"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

}

void OpSetSuper::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x05);
	
	
	printf("OpSetSuper"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

}

void OpDXNs::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x06);
	
	
	printf("OpDXNs"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "dxns"); 
	printf("%i\n", dxns);

}

void OpDXNsLate::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x07);
	
	
	printf("OpDXNsLate"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpKill::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x08);
	
	
	printf("OpKill"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "address"); 
	printf("%i\n", address);

}

void OpLabel::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x09);
	
	
	printf("OpLabel"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpIfNlt::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x0C);
	
	
	printf("OpIfNlt"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "target"); 
	printf("%i\n", target);

}

void OpIfNle::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x0D);
	
	
	printf("OpIfNle"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "target"); 
	printf("%i\n", target);

}

void OpIfNgt::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x0E);
	
	
	printf("OpIfNgt"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "target"); 
	printf("%i\n", target);

}

void OpIfNge::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x0F);
	
	
	printf("OpIfNge"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "target"); 
	printf("%i\n", target);

}

void OpJump::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x10);
	
	
	printf("OpJump"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "target"); 
	printf("%i\n", target);

}

void OpIfTrue::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x11);
	
	
	printf("OpIfTrue"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "target"); 
	printf("%i\n", target);

}

void OpIfFalse::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x12);
	
	
	printf("OpIfFalse"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "target"); 
	printf("%i\n", target);

}

void OpIfEq::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x13);
	
	
	printf("OpIfEq"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "target"); 
	printf("%i\n", target);

}

void OpIfNe::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x14);
	
	
	printf("OpIfNe"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "target"); 
	printf("%i\n", target);

}

void OpIfLt::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x15);
	
	
	printf("OpIfLt"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "target"); 
	printf("%i\n", target);

}

void OpIfLe::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x16);
	
	
	printf("OpIfLe"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "target"); 
	printf("%i\n", target);

}

void OpIfGt::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x17);
	
	
	printf("OpIfGt"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "target"); 
	printf("%i\n", target);

}

void OpIfGe::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x18);
	
	
	printf("OpIfGe"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "target"); 
	printf("%i\n", target);

}

void OpIfStrictEq::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x19);
	
	
	printf("OpIfStrictEq"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "target"); 
	printf("%i\n", target);

}

void OpIfStrictNe::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x1A);
	
	
	printf("OpIfStrictNe"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "target"); 
	printf("%i\n", target);

}

void OpLookupSwitch::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x1B);
	
	
	printf("OpLookupSwitch"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "defaulTarget"); 
	printf("%i\n", defaulTarget);

	print_indent(indent);
	printf("%s: ", "caseCount"); 
	printf("%i\n", caseCount);

	print_indent(indent);
	printf("%s: ", "targetTable"); 
	{
		printf("[list of %ss]\n", "S24");
		S24 *item;
		ListItem<S24>* i;
		i = targetTable.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}

}

void OpPushWith::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x1C);
	
	
	printf("OpPushWith"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpPopScope::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x1D);
	
	
	printf("OpPopScope"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpNextName::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x1E);
	
	
	printf("OpNextName"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpHasNext::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x1F);
	
	
	printf("OpHasNext"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpPushNull::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x20);
	
	
	printf("OpPushNull"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpPushUndefined::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x21);
	
	
	printf("OpPushUndefined"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpNextValue::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x23);
	
	
	printf("OpNextValue"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpPushByte::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x24);
	
	
	printf("OpPushByte"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "value"); 
	printf("%i\n", value);

}

void OpPushShort::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x25);
	
	
	printf("OpPushShort"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "value"); 
	printf("%i\n", value);

}

void OpPushTrue::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x26);
	
	
	printf("OpPushTrue"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpPushFalse::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x27);
	
	
	printf("OpPushFalse"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpPushNaN::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x28);
	
	
	printf("OpPushNaN"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpPop::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x29);
	
	
	printf("OpPop"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpDup::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x2A);
	
	
	printf("OpDup"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpSwap::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x2B);
	
	
	printf("OpSwap"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpPushString::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x2C);
	
	
	printf("OpPushString"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "index"); 
	printf("%i\n", index);

}

void OpPushInt::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x2D);
	
	
	printf("OpPushInt"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "index"); 
	printf("%i\n", index);

}

void OpPushUInt::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x2E);
	
	
	printf("OpPushUInt"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "index"); 
	printf("%i\n", index);

}

void OpPushDouble::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x2F);
	
	
	printf("OpPushDouble"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "index"); 
	printf("%i\n", index);

}

void OpPushScope::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x30);
	
	
	printf("OpPushScope"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpPushNamespace::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x31);
	
	
	printf("OpPushNamespace"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "index"); 
	printf("%i\n", index);

}

void OpHasNext2::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x32);
	
	
	printf("OpHasNext2"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "object"); 
	printf("%i\n", object);

	print_indent(indent);
	printf("%s: ", "index"); 
	printf("%i\n", index);

}

void OpNewFunction::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x40);
	
	
	printf("OpNewFunction"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "index"); 
	printf("%i\n", index);

}

void OpCall::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x41);
	
	
	printf("OpCall"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "argc"); 
	printf("%i\n", argc);

}

void OpConstruct::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x42);
	
	
	printf("OpConstruct"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "argc"); 
	printf("%i\n", argc);

}

void OpCallMethod::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x43);
	
	
	printf("OpCallMethod"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "dispID"); 
	printf("%i\n", dispID);

	print_indent(indent);
	printf("%s: ", "argc"); 
	printf("%i\n", argc);

}

void OpCallStatic::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x44);
	
	
	printf("OpCallStatic"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "methodID"); 
	printf("%i\n", methodID);

	print_indent(indent);
	printf("%s: ", "argc"); 
	printf("%i\n", argc);

}

void OpCallSuper::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x45);
	
	
	printf("OpCallSuper"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

	print_indent(indent);
	printf("%s: ", "argc"); 
	printf("%i\n", argc);

}

void OpCallProperty::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x46);
	
	
	printf("OpCallProperty"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

	print_indent(indent);
	printf("%s: ", "argc"); 
	printf("%i\n", argc);

}

void OpReturnVoid::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x47);
	
	
	printf("OpReturnVoid"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpReturnValue::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x48);
	
	
	printf("OpReturnValue"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpConstructSuper::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x49);
	
	
	printf("OpConstructSuper"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "argc"); 
	printf("%i\n", argc);

}

void OpConstructProp::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x4A);
	
	
	printf("OpConstructProp"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

	print_indent(indent);
	printf("%s: ", "argc"); 
	printf("%i\n", argc);

}

void OpCallPropLex::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x4C);
	
	
	printf("OpCallPropLex"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

	print_indent(indent);
	printf("%s: ", "argc"); 
	printf("%i\n", argc);

}

void OpCallSuperVoid::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x4E);
	
	
	printf("OpCallSuperVoid"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

	print_indent(indent);
	printf("%s: ", "argc"); 
	printf("%i\n", argc);

}

void OpCallPropVoid::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x4F);
	
	
	printf("OpCallPropVoid"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

	print_indent(indent);
	printf("%s: ", "argc"); 
	printf("%i\n", argc);

}

void OpApplyType::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x53);
	
	
	printf("OpApplyType"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "type"); 
	printf("%i\n", type);

}

void OpNewObject::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x55);
	
	
	printf("OpNewObject"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "argc"); 
	printf("%i\n", argc);

}

void OpNewArray::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x56);
	
	
	printf("OpNewArray"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "argc"); 
	printf("%i\n", argc);

}

void OpNewActivation::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x57);
	
	
	printf("OpNewActivation"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpNewClass::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x58);
	
	
	printf("OpNewClass"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "classIndex"); 
	printf("%i\n", classIndex);

}

void OpGetDescendants::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x59);
	
	
	printf("OpGetDescendants"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

}

void OpNewCatch::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x5A);
	
	
	printf("OpNewCatch"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "exceptionIndex"); 
	printf("%i\n", exceptionIndex);

}

void OpFindPropStrict::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x5D);
	
	
	printf("OpFindPropStrict"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

}

void OpFindProperty::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x5E);
	
	
	printf("OpFindProperty"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

}

void OpFindDef::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x5F);
	
	
	printf("OpFindDef"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

}

void OpGetLex::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x60);
	
	
	printf("OpGetLex"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

}

void OpSetProperty::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x61);
	
	
	printf("OpSetProperty"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

}

void OpGetLocal::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x62);
	
	
	printf("OpGetLocal"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "address"); 
	printf("%i\n", address);

}

void OpSetLocal::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x63);
	
	
	printf("OpSetLocal"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "address"); 
	printf("%i\n", address);

}

void OpGetGlobalScope::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x64);
	
	
	printf("OpGetGlobalScope"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpGetScopeObject::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x65);
	
	
	printf("OpGetScopeObject"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "scopeIndex"); 
	printf("%i\n", scopeIndex);

}

void OpGetProperty::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x66);
	
	
	printf("OpGetProperty"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

}

void OpInitProperty::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x68);
	
	
	printf("OpInitProperty"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

}

void OpDeleteProperty::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x6A);
	
	
	printf("OpDeleteProperty"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

}

void OpGetSlot::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x6C);
	
	
	printf("OpGetSlot"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "slotID"); 
	printf("%i\n", slotID);

}

void OpSetSlot::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x6D);
	
	
	printf("OpSetSlot"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "slotID"); 
	printf("%i\n", slotID);

}

void OpGetGlobalSlot::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x6E);
	
	
	printf("OpGetGlobalSlot"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "slotID"); 
	printf("%i\n", slotID);

}

void OpSetGlobalSlot::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x6F);
	
	
	printf("OpSetGlobalSlot"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "slotID"); 
	printf("%i\n", slotID);

}

void OpConvertS::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x70);
	
	
	printf("OpConvertS"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpEscXelem::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x71);
	
	
	printf("OpEscXelem"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpEscXattr::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x72);
	
	
	printf("OpEscXattr"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpConvertI::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x73);
	
	
	printf("OpConvertI"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpConvertU::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x74);
	
	
	printf("OpConvertU"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpConvertD::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x75);
	
	
	printf("OpConvertD"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpConvertB::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x76);
	
	
	printf("OpConvertB"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpConvertO::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x77);
	
	
	printf("OpConvertO"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpCheckFilter::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x78);
	
	
	printf("OpCheckFilter"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpCoerce::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x80);
	
	
	printf("OpCoerce"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

}

void OpCoerceB::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x81);
	
	
	printf("OpCoerceB"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpCoerceA::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x82);
	
	
	printf("OpCoerceA"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpCoerceI::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x83);
	
	
	printf("OpCoerceI"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpCoerceD::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x84);
	
	
	printf("OpCoerceD"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpCoerceS::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x85);
	
	
	printf("OpCoerceS"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpAsType::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x86);
	
	
	printf("OpAsType"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

}

void OpAsTypeLate::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x87);
	
	
	printf("OpAsTypeLate"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpCoerceU::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x88);
	
	
	printf("OpCoerceU"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpCoerceO::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x89);
	
	
	printf("OpCoerceO"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpNegate::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x90);
	
	
	printf("OpNegate"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpIncrement::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x91);
	
	
	printf("OpIncrement"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpIncLocal::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x92);
	
	
	printf("OpIncLocal"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "address"); 
	printf("%i\n", address);

}

void OpDecrement::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x93);
	
	
	printf("OpDecrement"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpDecLocal::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x94);
	
	
	printf("OpDecLocal"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "address"); 
	printf("%i\n", address);

}

void OpTypeOf::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x95);
	
	
	printf("OpTypeOf"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpNot::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x96);
	
	
	printf("OpNot"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpBitNot::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0x97);
	
	
	printf("OpBitNot"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpAdd::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xA0);
	
	
	printf("OpAdd"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpSubtract::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xA1);
	
	
	printf("OpSubtract"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpMultiply::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xA2);
	
	
	printf("OpMultiply"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpDivide::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xA3);
	
	
	printf("OpDivide"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpModulo::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xA4);
	
	
	printf("OpModulo"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpLShift::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xA5);
	
	
	printf("OpLShift"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpRShift::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xA6);
	
	
	printf("OpRShift"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpURShift::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xA7);
	
	
	printf("OpURShift"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpBitAnd::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xA8);
	
	
	printf("OpBitAnd"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpBitOr::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xA9);
	
	
	printf("OpBitOr"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpBitXor::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xAA);
	
	
	printf("OpBitXor"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpEquals::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xAB);
	
	
	printf("OpEquals"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpStrictEquals::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xAC);
	
	
	printf("OpStrictEquals"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpLessThan::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xAD);
	
	
	printf("OpLessThan"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpLessEquals::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xAE);
	
	
	printf("OpLessEquals"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpGreaterThan::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xAF);
	
	
	printf("OpGreaterThan"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpGreaterEquals::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xB0);
	
	
	printf("OpGreaterEquals"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpInstanceOf::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xB1);
	
	
	printf("OpInstanceOf"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpIsType::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xB2);
	
	
	printf("OpIsType"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

}

void OpIsTypeLate::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xB3);
	
	
	printf("OpIsTypeLate"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpIn::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xB4);
	
	
	printf("OpIn"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpIncrementI::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xC0);
	
	
	printf("OpIncrementI"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpDecrementI::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xC1);
	
	
	printf("OpDecrementI"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpIncLocalI::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xC2);
	
	
	printf("OpIncLocalI"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "address"); 
	printf("%i\n", address);

}

void OpDecLocalI::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xC3);
	
	
	printf("OpDecLocalI"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "address"); 
	printf("%i\n", address);

}

void OpNegateI::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xC4);
	
	
	printf("OpNegateI"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpAddI::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xC5);
	
	
	printf("OpAddI"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpSubtractI::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xC6);
	
	
	printf("OpSubtractI"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpMultiplyI::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xC7);
	
	
	printf("OpMultiplyI"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpGetLocal0::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xD0);
	
	
	printf("OpGetLocal0"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpGetLocal1::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xD1);
	
	
	printf("OpGetLocal1"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpGetLocal2::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xD2);
	
	
	printf("OpGetLocal2"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpGetLocal3::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xD3);
	
	
	printf("OpGetLocal3"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpSetLocal0::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xD4);
	
	
	printf("OpSetLocal0"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpSetLocal1::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xD5);
	
	
	printf("OpSetLocal1"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpSetLocal2::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xD6);
	
	
	printf("OpSetLocal2"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpSetLocal3::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xD7);
	
	
	printf("OpSetLocal3"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}

void OpDebugReg::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xEF);
	
	
	printf("OpDebugReg"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "unknown"); 
	printf("%i\n", unknown);

	print_indent(indent);
	printf("%s: ", "name"); 
	printf("%i\n", name);

	print_indent(indent);
	printf("%s: ", "reg"); 
	printf("%i\n", reg);

	print_indent(indent);
	printf("%s: ", "line"); 
	printf("%i\n", line);

}

void OpDebugLine::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xF0);
	
	
	printf("OpDebugLine"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "line"); 
	printf("%i\n", line);

}

void OpDebugFile::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xF1);
	
	
	printf("OpDebugFile"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "file"); 
	printf("%i\n", file);

}

void OpBkPtLine::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xF2);
	
	
	printf("OpBkPtLine"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
	print_indent(indent);
	printf("%s: ", "line"); 
	printf("%i\n", line);

}

void OpTimestamp::dump( int indent, Context *ctx ) {
	print_indent(indent);
	
		printf("[%02X] ", type ); //0xF3);
	
	
	printf("OpTimestamp"); // (sz %i)", getSize( ctx ) );
	
	printf("\n");
	indent++;
	
}


}

