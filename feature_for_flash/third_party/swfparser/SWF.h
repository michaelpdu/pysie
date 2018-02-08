
#ifndef SWF_H
#define SWF_H

#include "SWFReader.h"
#include "SWFTag.h"
#include "SWFAction.h"
#include "SWFFilter.h"
#include "SWFTrait.h"
#include "SWFList.h"
#include "SWFIdItems.h"
#include "SWFOpCode.h"
#include <vector>
#include <string>

#undef interface

namespace SWF {

	class Context {
	public:
		Context();

		int swfVersion;
		bool transientPropsToXML;
		bool debugTrace;
		bool exportAssets;
		bool quiet;

		bool isLast;
		char tagVersion;
		bool alpha;
		bool many_shapes;

		bool convertEncoding;
		const char *swf_encoding;

		int fillBits;
		int lineBits;
		unsigned char glyphBits;
		unsigned char advanceBits;
		bool wideGlyphOffsets;
		bool wideMap;
		unsigned short glyphCount;

	};

	class Rectangle : public Item {
	public:
		Rectangle();
		virtual ~Rectangle();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Rectangle* get( Reader *r, int end, Context *ctx );
		static Rectangle* getByName( const char *name );

		int getbits();
		void setbits( int );
		int getleft();
		void setleft( int );
		int getright();
		void setright( int );
		int gettop();
		void settop( int );
		int getbottom();
		void setbottom( int );


	protected:
		int bits; // integer
		int left; // integer
		int right; // integer
		int top; // integer
		int bottom; // integer

	};

	class String : public Item {
	public:
		String();
		virtual ~String();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static String* get( Reader *r, int end, Context *ctx );
		static String* getByName( const char *name );

		char * getvalue();
		void setvalue( char * );


	protected:
		char * value; // string

	};

	class String2 : public Item {
	public:
		String2();
		virtual ~String2();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static String2* get( Reader *r, int end, Context *ctx );
		static String2* getByName( const char *name );

		char * getvalue();
		void setvalue( char * );


	protected:
		char * value; // string

	};

	class Symbol : public Item {
	public:
		Symbol();
		virtual ~Symbol();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Symbol* get( Reader *r, int end, Context *ctx );
		static Symbol* getByName( const char *name );

		unsigned short getobjectID();
		void setobjectID( unsigned short );
		char * getname();
		void setname( char * );


	protected:
		unsigned short objectID; // word
		char * name; // string

	};


	class UChar : public Item {
	public:
		UChar();
		virtual ~UChar();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static UChar* get( Reader *r, int end, Context *ctx );
		static UChar* getByName( const char *name );

		unsigned char getvalue();
		void setvalue( unsigned char );


	protected:
		unsigned char value; // byte

	};

	class UShort : public Item {
	public:
		UShort();
		virtual ~UShort();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static UShort* get( Reader *r, int end, Context *ctx );
		static UShort* getByName( const char *name );

		unsigned short getvalue();
		void setvalue( unsigned short );


	protected:
		unsigned short value; // word

	};

	class ULong : public Item {
	public:
		ULong();
		virtual ~ULong();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static ULong* get( Reader *r, int end, Context *ctx );
		static ULong* getByName( const char *name );

		int getvalue();
		void setvalue( int );


	protected:
		int value; // integer

	};

	class Short : public Item {
	public:
		Short();
		virtual ~Short();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Short* get( Reader *r, int end, Context *ctx );
		static Short* getByName( const char *name );

		unsigned short getvalue();
		void setvalue( unsigned short );


	protected:
		unsigned short value; // word

	};

	class Float : public Item {
	public:
		Float();
		virtual ~Float();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Float* get( Reader *r, int end, Context *ctx );
		static Float* getByName( const char *name );

		float getvalue();
		void setvalue( float );


	protected:
		float value; // float

	};

	class Double : public Item {
	public:
		Double();
		virtual ~Double();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Double* get( Reader *r, int end, Context *ctx );
		static Double* getByName( const char *name );

		double getvalue();
		void setvalue( double );


	protected:
		double value; // double2

	};

	class Kerning : public Item {
	public:
		Kerning();
		virtual ~Kerning();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Kerning* get( Reader *r, int end, Context *ctx );
		static Kerning* getByName( const char *name );

		unsigned char geta();
		void seta( unsigned char );
		unsigned char getb();
		void setb( unsigned char );
		int getadjustment();
		void setadjustment( int );


	protected:
		unsigned char a; // byte
		unsigned char b; // byte
		int adjustment; // integer

	};

	class WideKerning : public Item {
	public:
		WideKerning();
		virtual ~WideKerning();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static WideKerning* get( Reader *r, int end, Context *ctx );
		static WideKerning* getByName( const char *name );

		unsigned short geta();
		void seta( unsigned short );
		unsigned short getb();
		void setb( unsigned short );
		unsigned short getadjustment();
		void setadjustment( unsigned short );


	protected:
		unsigned short a; // word
		unsigned short b; // word
		unsigned short adjustment; // word

	};

	class Event : public Item {
	public:
		Event();
		virtual ~Event();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Event* get( Reader *r, int end, Context *ctx );
		static Event* getByName( const char *name );

		unsigned short getflags1();
		void setflags1( unsigned short );
		unsigned short getflags2();
		void setflags2( unsigned short );
		unsigned int getactionLength();
		void setactionLength( unsigned int );
		List<Action> *getactions();


	protected:
		unsigned short flags1; // word
		unsigned short flags2; // word
		unsigned int actionLength; // uint32
		List<Action> actions; // list

	};


	class U30 : public Item {
	public:
		U30();
		virtual ~U30();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static U30* get( Reader *r, int end, Context *ctx );
		static U30* getByName( const char *name );

		unsigned int getvalue();
		void setvalue( unsigned int );


	protected:
		unsigned int value; // u30

	};

	class S24 : public Item {
	public:
		S24();
		virtual ~S24();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static S24* get( Reader *r, int end, Context *ctx );
		static S24* getByName( const char *name );

		int getvalue();
		void setvalue( int );


	protected:
		int value; // s24

	};

	class ValueKind : public Item {
	public:
		ValueKind();
		virtual ~ValueKind();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static ValueKind* get( Reader *r, int end, Context *ctx );
		static ValueKind* getByName( const char *name );

		unsigned int getindex();
		void setindex( unsigned int );
		unsigned char getkind();
		void setkind( unsigned char );


	protected:
		unsigned int index; // u30
		unsigned char kind; // byte

	};

	class MethodInfo : public Item {
	public:
		MethodInfo();
		virtual ~MethodInfo();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static MethodInfo* get( Reader *r, int end, Context *ctx );
		static MethodInfo* getByName( const char *name );

		unsigned int getparamCount();
		void setparamCount( unsigned int );
		unsigned int getretType();
		void setretType( unsigned int );
		List<U30> *getparamTypes();
		unsigned int getnameIndex();
		void setnameIndex( unsigned int );
		bool gethasParamNames();
		void sethasParamNames( bool );
		bool getsetSDXNs();
		void setsetSDXNs( bool );
		bool getisExplicit();
		void setisExplicit( bool );
		bool getignoreRest();
		void setignoreRest( bool );
		bool gethasOptional();
		void sethasOptional( bool );
		bool getneedRest();
		void setneedRest( bool );
		bool getneedActivation();
		void setneedActivation( bool );
		bool getneedArguments();
		void setneedArguments( bool );
		unsigned int getoptionalCount();
		void setoptionalCount( unsigned int );
		List<ValueKind> *getoptional();
		List<U30> *getparamNames();


	protected:
		unsigned int paramCount; // u30
		unsigned int retType; // u30
		List<U30> paramTypes; // list
		unsigned int nameIndex; // u30
		bool hasParamNames; // bit
		bool setSDXNs; // bit
		bool isExplicit; // bit
		bool ignoreRest; // bit
		bool hasOptional; // bit
		bool needRest; // bit
		bool needActivation; // bit
		bool needArguments; // bit
		unsigned int optionalCount; // u30
		List<ValueKind> optional; // list
		List<U30> paramNames; // list

	};

	class MetadataInfo : public Item {
	public:
		MetadataInfo();
		virtual ~MetadataInfo();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static MetadataInfo* get( Reader *r, int end, Context *ctx );
		static MetadataInfo* getByName( const char *name );

		unsigned int getnameIndex();
		void setnameIndex( unsigned int );
		unsigned int getvaluesCount();
		void setvaluesCount( unsigned int );
		List<U30> *getkeys();
		List<U30> *getvalues();


	protected:
		unsigned int nameIndex; // u30
		unsigned int valuesCount; // u30
		List<U30> keys; // list
		List<U30> values; // list

	};

	class NamespaceSet : public Item {
	public:
		NamespaceSet();
		virtual ~NamespaceSet();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static NamespaceSet* get( Reader *r, int end, Context *ctx );
		static NamespaceSet* getByName( const char *name );

		unsigned int getcount();
		void setcount( unsigned int );
		List<U30> *getnamespaces();


	protected:
		unsigned int count; // u30
		List<U30> namespaces; // list

	};

	class TraitInfo : public Item {
	public:
		TraitInfo();
		virtual ~TraitInfo();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static TraitInfo* get( Reader *r, int end, Context *ctx );
		static TraitInfo* getByName( const char *name );

		unsigned int getnameIndex();
		void setnameIndex( unsigned int );
		bool getreserved();
		void setreserved( bool );
		bool gethasMetadata();
		void sethasMetadata( bool );
		bool getoverride();
		void setoverride( bool );
		bool getfinal();
		void setfinal( bool );
		List<Trait> *gettrait();
		unsigned int getmetadataCount();
		void setmetadataCount( unsigned int );
		List<U30> *getmetadata();


	protected:
		unsigned int nameIndex; // u30
		bool reserved; // bit
		bool hasMetadata; // bit
		bool override; // bit
		bool final; // bit
		List<Trait> trait; // list
		unsigned int metadataCount; // u30
		List<U30> metadata; // list

	};

	class InstanceInfo : public Item {
	public:
		InstanceInfo();
		virtual ~InstanceInfo();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static InstanceInfo* get( Reader *r, int end, Context *ctx );
		static InstanceInfo* getByName( const char *name );

		unsigned int getnameIndex();
		void setnameIndex( unsigned int );
		unsigned int getsuperIndex();
		void setsuperIndex( unsigned int );
		int getreserved();
		void setreserved( int );
		bool gethasProtectedNS();
		void sethasProtectedNS( bool );
		bool getinterface();
		void setinterface( bool );
		bool getfinal();
		void setfinal( bool );
		bool getsealed();
		void setsealed( bool );
		unsigned int getprotectedNS();
		void setprotectedNS( unsigned int );
		unsigned int getinterfaceCount();
		void setinterfaceCount( unsigned int );
		List<U30> *getinterfaces();
		unsigned int getiInitIndex();
		void setiInitIndex( unsigned int );
		unsigned int gettraitCount();
		void settraitCount( unsigned int );
		List<TraitInfo> *gettraits();


	protected:
		unsigned int nameIndex; // u30
		unsigned int superIndex; // u30
		int reserved; // integer
		bool hasProtectedNS; // bit
		bool interface; // bit
		bool final; // bit
		bool sealed; // bit
		unsigned int protectedNS; // u30
		unsigned int interfaceCount; // u30
		List<U30> interfaces; // list
		unsigned int iInitIndex; // u30
		unsigned int traitCount; // u30
		List<TraitInfo> traits; // list

	};

	class ClassInfo : public Item {
	public:
		ClassInfo();
		virtual ~ClassInfo();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static ClassInfo* get( Reader *r, int end, Context *ctx );
		static ClassInfo* getByName( const char *name );

		unsigned int getcInitIndex();
		void setcInitIndex( unsigned int );
		unsigned int gettraitCount();
		void settraitCount( unsigned int );
		List<TraitInfo> *gettraits();


	protected:
		unsigned int cInitIndex; // u30
		unsigned int traitCount; // u30
		List<TraitInfo> traits; // list

	};

	class ScriptInfo : public Item {
	public:
		ScriptInfo();
		virtual ~ScriptInfo();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static ScriptInfo* get( Reader *r, int end, Context *ctx );
		static ScriptInfo* getByName( const char *name );

		unsigned int getinitIndex();
		void setinitIndex( unsigned int );
		unsigned int gettraitCount();
		void settraitCount( unsigned int );
		List<TraitInfo> *gettraits();


	protected:
		unsigned int initIndex; // u30
		unsigned int traitCount; // u30
		List<TraitInfo> traits; // list

	};

	class Exception : public Item {
	public:
		Exception();
		virtual ~Exception();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Exception* get( Reader *r, int end, Context *ctx );
		static Exception* getByName( const char *name );

		unsigned int gettryStart();
		void settryStart( unsigned int );
		unsigned int gettryEnd();
		void settryEnd( unsigned int );
		unsigned int gettarget();
		void settarget( unsigned int );
		unsigned int gettype();
		void settype( unsigned int );
		unsigned int getname();
		void setname( unsigned int );


	protected:
		unsigned int tryStart; // u30
		unsigned int tryEnd; // u30
		unsigned int target; // u30
		unsigned int type; // u30
		unsigned int name; // u30

	};

	class MethodBody : public Item {
	public:
		MethodBody();
		virtual ~MethodBody();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static MethodBody* get( Reader *r, int end, Context *ctx );
		static MethodBody* getByName( const char *name );

		unsigned int getmethodInfo();
		void setmethodInfo( unsigned int );
		unsigned int getmaxStack();
		void setmaxStack( unsigned int );
		unsigned int getmaxRegs();
		void setmaxRegs( unsigned int );
		unsigned int getscopeDepth();
		void setscopeDepth( unsigned int );
		unsigned int getmaxScope();
		void setmaxScope( unsigned int );
		unsigned int getcodeLength();
		void setcodeLength( unsigned int );
		List<OpCode> *getcode();
		unsigned int getexceptionCount();
		void setexceptionCount( unsigned int );
		List<Exception> *getexceptions();
		unsigned int gettraitCount();
		void settraitCount( unsigned int );
		List<TraitInfo> *gettraits();


	protected:
		unsigned int methodInfo; // u30
		unsigned int maxStack; // u30
		unsigned int maxRegs; // u30
		unsigned int scopeDepth; // u30
		unsigned int maxScope; // u30
		unsigned int codeLength; // u30
		List<OpCode> code; // list
		unsigned int exceptionCount; // u30
		List<Exception> exceptions; // list
		unsigned int traitCount; // u30
		List<TraitInfo> traits; // list

	};

	class Constants : public Item {
	public:
		Constants();
		virtual ~Constants();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Constants* get( Reader *r, int end, Context *ctx );
		static Constants* getByName( const char *name );

		unsigned int getintCount();
		void setintCount( unsigned int );
		List<U30> *getints();
		unsigned int getuintCount();
		void setuintCount( unsigned int );
		List<U30> *getuints();
		unsigned int getdoubleCount();
		void setdoubleCount( unsigned int );
		List<Double> *getdoubles();
		unsigned int getstringCount();
		void setstringCount( unsigned int );
		List<String2> *getstrings();
		unsigned int getnamespaceConstantCount();
		void setnamespaceConstantCount( unsigned int );
		List<NamespaceConstant> *getnamespaces();
		unsigned int getnamespaceSetCount();
		void setnamespaceSetCount( unsigned int );
		List<NamespaceSet> *getnamespaceSets();
		unsigned int getmultinameConstantCount();
		void setmultinameConstantCount( unsigned int );
		List<MultinameConstant> *getmultinames();


	protected:
		unsigned int intCount; // u30
		List<U30> ints; // list
		unsigned int uintCount; // u30
		List<U30> uints; // list
		unsigned int doubleCount; // u30
		List<Double> doubles; // list
		unsigned int stringCount; // u30
		List<String2> strings; // list
		unsigned int namespaceConstantCount; // u30
		List<NamespaceConstant> namespaces; // list
		unsigned int namespaceSetCount; // u30
		List<NamespaceSet> namespaceSets; // list
		unsigned int multinameConstantCount; // u30
		List<MultinameConstant> multinames; // list

	};

	class Action3 : public Item {
	public:
		Action3();
		virtual ~Action3();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Action3* get( Reader *r, int end, Context *ctx );
		static Action3* getByName( const char *name );

		unsigned short getminorVersion();
		void setminorVersion( unsigned short );
		unsigned short getmajorVersion();
		void setmajorVersion( unsigned short );
		Constants *getconstants();
		unsigned int getmethodInfoCount();
		void setmethodInfoCount( unsigned int );
		List<MethodInfo> *getmethods();
		unsigned int getmetadataInfoCount();
		void setmetadataInfoCount( unsigned int );
		List<MetadataInfo> *getmetadata();
		unsigned int getclassCount();
		void setclassCount( unsigned int );
		List<InstanceInfo> *getinstances();
		List<ClassInfo> *getclasses();
		unsigned int getscriptCount();
		void setscriptCount( unsigned int );
		List<ScriptInfo> *getscripts();
		unsigned int getmethodBodyCount();
		void setmethodBodyCount( unsigned int );
		List<MethodBody> *getmethodBodies();


	protected:
		unsigned short minorVersion; // word
		unsigned short majorVersion; // word
		Constants constants; // object
		unsigned int methodInfoCount; // u30
		List<MethodInfo> methods; // list
		unsigned int metadataInfoCount; // u30
		List<MetadataInfo> metadata; // list
		unsigned int classCount; // u30
		List<InstanceInfo> instances; // list
		List<ClassInfo> classes; // list
		unsigned int scriptCount; // u30
		List<ScriptInfo> scripts; // list
		unsigned int methodBodyCount; // u30
		List<MethodBody> methodBodies; // list

	};

	class ZoneData : public Item {
	public:
		ZoneData();
		virtual ~ZoneData();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static ZoneData* get( Reader *r, int end, Context *ctx );
		static ZoneData* getByName( const char *name );

		float getposition();
		void setposition( float );
		float getsize();
		void setsize( float );


	protected:
		float position; // half
		float size; // half

	};

	class ZoneArray : public Item {
	public:
		ZoneArray();
		virtual ~ZoneArray();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static ZoneArray* get( Reader *r, int end, Context *ctx );
		static ZoneArray* getByName( const char *name );

		unsigned char getcount();
		void setcount( unsigned char );
		List<ZoneData> *getzones();
		int getzoneX();
		void setzoneX( int );
		int getzoneY();
		void setzoneY( int );
		int getreserved();
		void setreserved( int );


	protected:
		unsigned char count; // byte
		List<ZoneData> zones; // list
		int zoneX; // integer
		int zoneY; // integer
		int reserved; // integer

	};

	class UnknownTag : public Tag {
	public:
		UnknownTag();
		virtual ~UnknownTag();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static UnknownTag* get( Reader *r, int end, Context *ctx );
		static UnknownTag* getByName( const char *name );


		void getdata( unsigned char **dst, int *size );
		void setdata( const unsigned char *src, int size );


	protected:
		unsigned char * data; // data

		static int id;

	};

	class End : public Tag {
	public:
		End();
		virtual ~End();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static End* get( Reader *r, int end, Context *ctx );
		static End* getByName( const char *name );



	protected:

		static int id;

	};

	class Export : public Tag {
	public:
		Export();
		virtual ~Export();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Export* get( Reader *r, int end, Context *ctx );
		static Export* getByName( const char *name );

		unsigned short getcount();
		void setcount( unsigned short );
		List<Symbol> *getsymbols();


	protected:
		unsigned short count; // word
		List<Symbol> symbols; // list

		static int id;

	};

	class Import : public Tag {
	public:
		Import();
		virtual ~Import();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Import* get( Reader *r, int end, Context *ctx );
		static Import* getByName( const char *name );

		char * geturl();
		void seturl( char * );
		unsigned short getcount();
		void setcount( unsigned short );
		List<Symbol> *getsymbols();


	protected:
		char * url; // string
		unsigned short count; // word
		List<Symbol> symbols; // list

		static int id;

	};

	class DoInitAction : public Tag {
	public:
		DoInitAction();
		virtual ~DoInitAction();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static DoInitAction* get( Reader *r, int end, Context *ctx );
		static DoInitAction* getByName( const char *name );

		unsigned short getsprite();
		void setsprite( unsigned short );
		List<Action> *getactions();


	protected:
		unsigned short sprite; // word
		List<Action> actions; // list

		static int id;

	};

	class ScriptLimits : public Tag {
	public:
		ScriptLimits();
		virtual ~ScriptLimits();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static ScriptLimits* get( Reader *r, int end, Context *ctx );
		static ScriptLimits* getByName( const char *name );

		unsigned short getmaxRecursionDepth();
		void setmaxRecursionDepth( unsigned short );
		unsigned short gettimeout();
		void settimeout( unsigned short );


	protected:
		unsigned short maxRecursionDepth; // word
		unsigned short timeout; // word

		static int id;

	};

	class ImportAssets2 : public Tag {
	public:
		ImportAssets2();
		virtual ~ImportAssets2();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static ImportAssets2* get( Reader *r, int end, Context *ctx );
		static ImportAssets2* getByName( const char *name );

		char * geturl();
		void seturl( char * );
		unsigned char getreserved1();
		void setreserved1( unsigned char );
		unsigned char getreserved2();
		void setreserved2( unsigned char );
		unsigned short getcount();
		void setcount( unsigned short );
		List<Symbol> *getsymbols();


	protected:
		char * url; // string
		unsigned char reserved1; // byte
		unsigned char reserved2; // byte
		unsigned short count; // word
		List<Symbol> symbols; // list

		static int id;

	};

	class FileAttributes : public Tag {
	public:
		FileAttributes();
		virtual ~FileAttributes();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static FileAttributes* get( Reader *r, int end, Context *ctx );
		static FileAttributes* getByName( const char *name );

		int getreserved1();
		void setreserved1( int );
		bool gethasMetaData();
		void sethasMetaData( bool );
		int getreserved2();
		void setreserved2( int );
		bool getallowABC();
		void setallowABC( bool );
		bool getsuppressCrossDomainCaching();
		void setsuppressCrossDomainCaching( bool );
		bool getswfRelativeURLs();
		void setswfRelativeURLs( bool );
		bool getuseNetwork();
		void setuseNetwork( bool );
		int getreserved3();
		void setreserved3( int );


	protected:
		int reserved1; // integer
		bool hasMetaData; // bit
		int reserved2; // integer
		bool allowABC; // bit
		bool suppressCrossDomainCaching; // bit
		bool swfRelativeURLs; // bit
		bool useNetwork; // bit
		int reserved3; // integer

		static int id;

	};


	class Metadata : public Tag {
	public:
		Metadata();
		virtual ~Metadata();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Metadata* get( Reader *r, int end, Context *ctx );
		static Metadata* getByName( const char *name );

		char * getRDF();
		void setRDF( char * );


	protected:
		char * RDF; // xml

		static int id;

	};

	class DoABC : public Tag {
	public:
		DoABC();
		virtual ~DoABC();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static DoABC* get( Reader *r, int end, Context *ctx );
		static DoABC* getByName( const char *name );

		Action3 *getactions();


	protected:
		Action3 actions; // object

		static int id;

	};

	class DoABCDefine : public Tag {
	public:
		DoABCDefine();
		virtual ~DoABCDefine();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static DoABCDefine* get( Reader *r, int end, Context *ctx );
		static DoABCDefine* getByName( const char *name );

		unsigned int getflags();
		void setflags( unsigned int );
		char * getname();
		void setname( char * );
		Action3 *getactions();


	protected:
		unsigned int flags; // uint32
		char * name; // string
		Action3 actions; // object

		static int id;

	};

	class SymbolClass : public Tag {
	public:
		SymbolClass();
		virtual ~SymbolClass();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static SymbolClass* get( Reader *r, int end, Context *ctx );
		static SymbolClass* getByName( const char *name );

		unsigned short getcount();
		void setcount( unsigned short );
		List<Symbol> *getsymbols();


	protected:
		unsigned short count; // word
		List<Symbol> symbols; // list

		static int id;

	};

	class DefineBinaryData : public Tag {
	public:
		DefineBinaryData();
		virtual ~DefineBinaryData();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static DefineBinaryData* get( Reader *r, int end, Context *ctx );
		static DefineBinaryData* getByName( const char *name );

		unsigned short getobjectID();
		void setobjectID( unsigned short );
		unsigned int getreserved();
		void setreserved( unsigned int );
		Rest *getdata();


	protected:
		unsigned short objectID; // word
		unsigned int reserved; // uint32
		Rest data; // object

		static int id;

	};


	class EnableDebugger : public Tag {
	public:
		EnableDebugger();
		virtual ~EnableDebugger();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static EnableDebugger* get( Reader *r, int end, Context *ctx );
		static EnableDebugger* getByName( const char *name );

		char * getpassword();
		void setpassword( char * );


	protected:
		char * password; // string

		static int id;

	};

	class EnableDebugger2 : public Tag {
	public:
		EnableDebugger2();
		virtual ~EnableDebugger2();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static EnableDebugger2* get( Reader *r, int end, Context *ctx );
		static EnableDebugger2* getByName( const char *name );

		unsigned short getreserved();
		void setreserved( unsigned short );
		char * getpassword();
		void setpassword( char * );


	protected:
		unsigned short reserved; // word
		char * password; // string

		static int id;

	};

	class StackString : public StackItem {
	public:
		StackString();
		virtual ~StackString();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static StackString* get( Reader *r, int end, Context *ctx );
		static StackString* getByName( const char *name );

		char * getvalue();
		void setvalue( char * );


	protected:
		char * value; // string

		static int id;

	};

	class StackFloat : public StackItem {
	public:
		StackFloat();
		virtual ~StackFloat();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static StackFloat* get( Reader *r, int end, Context *ctx );
		static StackFloat* getByName( const char *name );

		float getvalue();
		void setvalue( float );


	protected:
		float value; // float

		static int id;

	};

	class StackNull : public StackItem {
	public:
		StackNull();
		virtual ~StackNull();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static StackNull* get( Reader *r, int end, Context *ctx );
		static StackNull* getByName( const char *name );



	protected:

		static int id;

	};

	class StackUndefined : public StackItem {
	public:
		StackUndefined();
		virtual ~StackUndefined();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static StackUndefined* get( Reader *r, int end, Context *ctx );
		static StackUndefined* getByName( const char *name );



	protected:

		static int id;

	};

	class StackRegister : public StackItem {
	public:
		StackRegister();
		virtual ~StackRegister();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static StackRegister* get( Reader *r, int end, Context *ctx );
		static StackRegister* getByName( const char *name );

		unsigned char getreg();
		void setreg( unsigned char );


	protected:
		unsigned char reg; // byte

		static int id;

	};

	class StackBoolean : public StackItem {
	public:
		StackBoolean();
		virtual ~StackBoolean();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static StackBoolean* get( Reader *r, int end, Context *ctx );
		static StackBoolean* getByName( const char *name );

		unsigned char getvalue();
		void setvalue( unsigned char );


	protected:
		unsigned char value; // byte

		static int id;

	};

	class StackDouble : public StackItem {
	public:
		StackDouble();
		virtual ~StackDouble();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static StackDouble* get( Reader *r, int end, Context *ctx );
		static StackDouble* getByName( const char *name );

		double getvalue();
		void setvalue( double );


	protected:
		double value; // double

		static int id;

	};

	class StackInteger : public StackItem {
	public:
		StackInteger();
		virtual ~StackInteger();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static StackInteger* get( Reader *r, int end, Context *ctx );
		static StackInteger* getByName( const char *name );

		unsigned int getvalue();
		void setvalue( unsigned int );


	protected:
		unsigned int value; // uint32

		static int id;

	};

	class StackDictionaryLookup : public StackItem {
	public:
		StackDictionaryLookup();
		virtual ~StackDictionaryLookup();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static StackDictionaryLookup* get( Reader *r, int end, Context *ctx );
		static StackDictionaryLookup* getByName( const char *name );

		unsigned char getindex();
		void setindex( unsigned char );


	protected:
		unsigned char index; // byte

		static int id;

	};

	class StackLargeDictionaryLookup : public StackItem {
	public:
		StackLargeDictionaryLookup();
		virtual ~StackLargeDictionaryLookup();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static StackLargeDictionaryLookup* get( Reader *r, int end, Context *ctx );
		static StackLargeDictionaryLookup* getByName( const char *name );

		unsigned short getindex();
		void setindex( unsigned short );


	protected:
		unsigned short index; // word

		static int id;

	};

	class UnknownAction : public Action {
	public:
		UnknownAction();
		virtual ~UnknownAction();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static UnknownAction* get( Reader *r, int end, Context *ctx );
		static UnknownAction* getByName( const char *name );


		void getdata( unsigned char **dst, int *size );
		void setdata( const unsigned char *src, int size );


	protected:
		unsigned char * data; // data

		static int id;

	};

	class EndAction : public Action {
	public:
		EndAction();
		virtual ~EndAction();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static EndAction* get( Reader *r, int end, Context *ctx );
		static EndAction* getByName( const char *name );



	protected:

		static int id;

	};


	class AddCast : public Action {
	public:
		AddCast();
		virtual ~AddCast();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static AddCast* get( Reader *r, int end, Context *ctx );
		static AddCast* getByName( const char *name );



	protected:

		static int id;

	};

	class Substract : public Action {
	public:
		Substract();
		virtual ~Substract();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Substract* get( Reader *r, int end, Context *ctx );
		static Substract* getByName( const char *name );



	protected:

		static int id;

	};

	class Mulitply : public Action {
	public:
		Mulitply();
		virtual ~Mulitply();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Mulitply* get( Reader *r, int end, Context *ctx );
		static Mulitply* getByName( const char *name );



	protected:

		static int id;

	};

	class Divide : public Action {
	public:
		Divide();
		virtual ~Divide();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Divide* get( Reader *r, int end, Context *ctx );
		static Divide* getByName( const char *name );



	protected:

		static int id;

	};

	class EqualCast : public Action {
	public:
		EqualCast();
		virtual ~EqualCast();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static EqualCast* get( Reader *r, int end, Context *ctx );
		static EqualCast* getByName( const char *name );



	protected:

		static int id;

	};

	class LessThanCast : public Action {
	public:
		LessThanCast();
		virtual ~LessThanCast();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static LessThanCast* get( Reader *r, int end, Context *ctx );
		static LessThanCast* getByName( const char *name );



	protected:

		static int id;

	};

	class LogicalAND : public Action {
	public:
		LogicalAND();
		virtual ~LogicalAND();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static LogicalAND* get( Reader *r, int end, Context *ctx );
		static LogicalAND* getByName( const char *name );



	protected:

		static int id;

	};

	class LogicalOR : public Action {
	public:
		LogicalOR();
		virtual ~LogicalOR();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static LogicalOR* get( Reader *r, int end, Context *ctx );
		static LogicalOR* getByName( const char *name );



	protected:

		static int id;

	};

	class LogicalNOT : public Action {
	public:
		LogicalNOT();
		virtual ~LogicalNOT();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static LogicalNOT* get( Reader *r, int end, Context *ctx );
		static LogicalNOT* getByName( const char *name );



	protected:

		static int id;

	};

	class StringEqual : public Action {
	public:
		StringEqual();
		virtual ~StringEqual();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static StringEqual* get( Reader *r, int end, Context *ctx );
		static StringEqual* getByName( const char *name );



	protected:

		static int id;

	};

	class StringLength : public Action {
	public:
		StringLength();
		virtual ~StringLength();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static StringLength* get( Reader *r, int end, Context *ctx );
		static StringLength* getByName( const char *name );



	protected:

		static int id;

	};

	class SubString : public Action {
	public:
		SubString();
		virtual ~SubString();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static SubString* get( Reader *r, int end, Context *ctx );
		static SubString* getByName( const char *name );



	protected:

		static int id;

	};

	class Pop : public Action {
	public:
		Pop();
		virtual ~Pop();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Pop* get( Reader *r, int end, Context *ctx );
		static Pop* getByName( const char *name );



	protected:

		static int id;

	};

	class IntegralPart : public Action {
	public:
		IntegralPart();
		virtual ~IntegralPart();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static IntegralPart* get( Reader *r, int end, Context *ctx );
		static IntegralPart* getByName( const char *name );



	protected:

		static int id;

	};

	class GetVariable : public Action {
	public:
		GetVariable();
		virtual ~GetVariable();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static GetVariable* get( Reader *r, int end, Context *ctx );
		static GetVariable* getByName( const char *name );



	protected:

		static int id;

	};

	class SetVariable : public Action {
	public:
		SetVariable();
		virtual ~SetVariable();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static SetVariable* get( Reader *r, int end, Context *ctx );
		static SetVariable* getByName( const char *name );



	protected:

		static int id;

	};

	class SetTargetDynamic : public Action {
	public:
		SetTargetDynamic();
		virtual ~SetTargetDynamic();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static SetTargetDynamic* get( Reader *r, int end, Context *ctx );
		static SetTargetDynamic* getByName( const char *name );



	protected:

		static int id;

	};

	class ConcatenateString : public Action {
	public:
		ConcatenateString();
		virtual ~ConcatenateString();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static ConcatenateString* get( Reader *r, int end, Context *ctx );
		static ConcatenateString* getByName( const char *name );



	protected:

		static int id;

	};

	class GetProperty : public Action {
	public:
		GetProperty();
		virtual ~GetProperty();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static GetProperty* get( Reader *r, int end, Context *ctx );
		static GetProperty* getByName( const char *name );



	protected:

		static int id;

	};

	class SetProperty : public Action {
	public:
		SetProperty();
		virtual ~SetProperty();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static SetProperty* get( Reader *r, int end, Context *ctx );
		static SetProperty* getByName( const char *name );



	protected:

		static int id;

	};

	class DuplicateSprite : public Action {
	public:
		DuplicateSprite();
		virtual ~DuplicateSprite();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static DuplicateSprite* get( Reader *r, int end, Context *ctx );
		static DuplicateSprite* getByName( const char *name );



	protected:

		static int id;

	};

	class RemoveSprite : public Action {
	public:
		RemoveSprite();
		virtual ~RemoveSprite();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static RemoveSprite* get( Reader *r, int end, Context *ctx );
		static RemoveSprite* getByName( const char *name );



	protected:

		static int id;

	};

	class Trace : public Action {
	public:
		Trace();
		virtual ~Trace();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Trace* get( Reader *r, int end, Context *ctx );
		static Trace* getByName( const char *name );



	protected:

		static int id;

	};


	class StringLessThan : public Action {
	public:
		StringLessThan();
		virtual ~StringLessThan();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static StringLessThan* get( Reader *r, int end, Context *ctx );
		static StringLessThan* getByName( const char *name );



	protected:

		static int id;

	};

	class Throw : public Action {
	public:
		Throw();
		virtual ~Throw();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Throw* get( Reader *r, int end, Context *ctx );
		static Throw* getByName( const char *name );



	protected:

		static int id;

	};

	class CastObject : public Action {
	public:
		CastObject();
		virtual ~CastObject();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static CastObject* get( Reader *r, int end, Context *ctx );
		static CastObject* getByName( const char *name );



	protected:

		static int id;

	};

	class Implements : public Action {
	public:
		Implements();
		virtual ~Implements();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Implements* get( Reader *r, int end, Context *ctx );
		static Implements* getByName( const char *name );



	protected:

		static int id;

	};

	class Random : public Action {
	public:
		Random();
		virtual ~Random();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Random* get( Reader *r, int end, Context *ctx );
		static Random* getByName( const char *name );



	protected:

		static int id;

	};

	class MultibyteStringLength : public Action {
	public:
		MultibyteStringLength();
		virtual ~MultibyteStringLength();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static MultibyteStringLength* get( Reader *r, int end, Context *ctx );
		static MultibyteStringLength* getByName( const char *name );



	protected:

		static int id;

	};

	class ORD : public Action {
	public:
		ORD();
		virtual ~ORD();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static ORD* get( Reader *r, int end, Context *ctx );
		static ORD* getByName( const char *name );



	protected:

		static int id;

	};

	class CHR : public Action {
	public:
		CHR();
		virtual ~CHR();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static CHR* get( Reader *r, int end, Context *ctx );
		static CHR* getByName( const char *name );



	protected:

		static int id;

	};

	class GetTimer : public Action {
	public:
		GetTimer();
		virtual ~GetTimer();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static GetTimer* get( Reader *r, int end, Context *ctx );
		static GetTimer* getByName( const char *name );



	protected:

		static int id;

	};

	class MultibyteSubString : public Action {
	public:
		MultibyteSubString();
		virtual ~MultibyteSubString();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static MultibyteSubString* get( Reader *r, int end, Context *ctx );
		static MultibyteSubString* getByName( const char *name );



	protected:

		static int id;

	};

	class MultibyteORD : public Action {
	public:
		MultibyteORD();
		virtual ~MultibyteORD();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static MultibyteORD* get( Reader *r, int end, Context *ctx );
		static MultibyteORD* getByName( const char *name );



	protected:

		static int id;

	};

	class MultibyteCHR : public Action {
	public:
		MultibyteCHR();
		virtual ~MultibyteCHR();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static MultibyteCHR* get( Reader *r, int end, Context *ctx );
		static MultibyteCHR* getByName( const char *name );



	protected:

		static int id;

	};

	class Delete : public Action {
	public:
		Delete();
		virtual ~Delete();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Delete* get( Reader *r, int end, Context *ctx );
		static Delete* getByName( const char *name );



	protected:

		static int id;

	};

	class DeleteAll : public Action {
	public:
		DeleteAll();
		virtual ~DeleteAll();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static DeleteAll* get( Reader *r, int end, Context *ctx );
		static DeleteAll* getByName( const char *name );



	protected:

		static int id;

	};

	class SetLocalVariable : public Action {
	public:
		SetLocalVariable();
		virtual ~SetLocalVariable();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static SetLocalVariable* get( Reader *r, int end, Context *ctx );
		static SetLocalVariable* getByName( const char *name );



	protected:

		static int id;

	};

	class CallFunction : public Action {
	public:
		CallFunction();
		virtual ~CallFunction();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static CallFunction* get( Reader *r, int end, Context *ctx );
		static CallFunction* getByName( const char *name );



	protected:

		static int id;

	};

	class Return : public Action {
	public:
		Return();
		virtual ~Return();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Return* get( Reader *r, int end, Context *ctx );
		static Return* getByName( const char *name );



	protected:

		static int id;

	};

	class Modulo : public Action {
	public:
		Modulo();
		virtual ~Modulo();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Modulo* get( Reader *r, int end, Context *ctx );
		static Modulo* getByName( const char *name );



	protected:

		static int id;

	};

	class New : public Action {
	public:
		New();
		virtual ~New();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static New* get( Reader *r, int end, Context *ctx );
		static New* getByName( const char *name );



	protected:

		static int id;

	};

	class DeclareLocalVariable : public Action {
	public:
		DeclareLocalVariable();
		virtual ~DeclareLocalVariable();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static DeclareLocalVariable* get( Reader *r, int end, Context *ctx );
		static DeclareLocalVariable* getByName( const char *name );



	protected:

		static int id;

	};

	class DeclareArray : public Action {
	public:
		DeclareArray();
		virtual ~DeclareArray();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static DeclareArray* get( Reader *r, int end, Context *ctx );
		static DeclareArray* getByName( const char *name );



	protected:

		static int id;

	};

	class DeclareObject : public Action {
	public:
		DeclareObject();
		virtual ~DeclareObject();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static DeclareObject* get( Reader *r, int end, Context *ctx );
		static DeclareObject* getByName( const char *name );



	protected:

		static int id;

	};

	class TypeOf : public Action {
	public:
		TypeOf();
		virtual ~TypeOf();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static TypeOf* get( Reader *r, int end, Context *ctx );
		static TypeOf* getByName( const char *name );



	protected:

		static int id;

	};

	class GetTarget : public Action {
	public:
		GetTarget();
		virtual ~GetTarget();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static GetTarget* get( Reader *r, int end, Context *ctx );
		static GetTarget* getByName( const char *name );



	protected:

		static int id;

	};

	class Enumerate : public Action {
	public:
		Enumerate();
		virtual ~Enumerate();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Enumerate* get( Reader *r, int end, Context *ctx );
		static Enumerate* getByName( const char *name );



	protected:

		static int id;

	};

	class AddTyped : public Action {
	public:
		AddTyped();
		virtual ~AddTyped();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static AddTyped* get( Reader *r, int end, Context *ctx );
		static AddTyped* getByName( const char *name );



	protected:

		static int id;

	};

	class LessThanTyped : public Action {
	public:
		LessThanTyped();
		virtual ~LessThanTyped();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static LessThanTyped* get( Reader *r, int end, Context *ctx );
		static LessThanTyped* getByName( const char *name );



	protected:

		static int id;

	};

	class EqualTyped : public Action {
	public:
		EqualTyped();
		virtual ~EqualTyped();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static EqualTyped* get( Reader *r, int end, Context *ctx );
		static EqualTyped* getByName( const char *name );



	protected:

		static int id;

	};

	class DefineNumber : public Action {
	public:
		DefineNumber();
		virtual ~DefineNumber();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static DefineNumber* get( Reader *r, int end, Context *ctx );
		static DefineNumber* getByName( const char *name );



	protected:

		static int id;

	};

	class DefineString : public Action {
	public:
		DefineString();
		virtual ~DefineString();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static DefineString* get( Reader *r, int end, Context *ctx );
		static DefineString* getByName( const char *name );



	protected:

		static int id;

	};

	class Duplicate : public Action {
	public:
		Duplicate();
		virtual ~Duplicate();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Duplicate* get( Reader *r, int end, Context *ctx );
		static Duplicate* getByName( const char *name );



	protected:

		static int id;

	};

	class Swap : public Action {
	public:
		Swap();
		virtual ~Swap();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Swap* get( Reader *r, int end, Context *ctx );
		static Swap* getByName( const char *name );



	protected:

		static int id;

	};

	class GetMember : public Action {
	public:
		GetMember();
		virtual ~GetMember();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static GetMember* get( Reader *r, int end, Context *ctx );
		static GetMember* getByName( const char *name );



	protected:

		static int id;

	};

	class SetMember : public Action {
	public:
		SetMember();
		virtual ~SetMember();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static SetMember* get( Reader *r, int end, Context *ctx );
		static SetMember* getByName( const char *name );



	protected:

		static int id;

	};

	class Increment : public Action {
	public:
		Increment();
		virtual ~Increment();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Increment* get( Reader *r, int end, Context *ctx );
		static Increment* getByName( const char *name );



	protected:

		static int id;

	};

	class Decrement : public Action {
	public:
		Decrement();
		virtual ~Decrement();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Decrement* get( Reader *r, int end, Context *ctx );
		static Decrement* getByName( const char *name );



	protected:

		static int id;

	};

	class CallMethod : public Action {
	public:
		CallMethod();
		virtual ~CallMethod();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static CallMethod* get( Reader *r, int end, Context *ctx );
		static CallMethod* getByName( const char *name );



	protected:

		static int id;

	};

	class NewMethod : public Action {
	public:
		NewMethod();
		virtual ~NewMethod();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static NewMethod* get( Reader *r, int end, Context *ctx );
		static NewMethod* getByName( const char *name );



	protected:

		static int id;

	};

	class InstanceOf : public Action {
	public:
		InstanceOf();
		virtual ~InstanceOf();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static InstanceOf* get( Reader *r, int end, Context *ctx );
		static InstanceOf* getByName( const char *name );



	protected:

		static int id;

	};

	class EnumerateObject : public Action {
	public:
		EnumerateObject();
		virtual ~EnumerateObject();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static EnumerateObject* get( Reader *r, int end, Context *ctx );
		static EnumerateObject* getByName( const char *name );



	protected:

		static int id;

	};

	class AND : public Action {
	public:
		AND();
		virtual ~AND();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static AND* get( Reader *r, int end, Context *ctx );
		static AND* getByName( const char *name );



	protected:

		static int id;

	};

	class OR : public Action {
	public:
		OR();
		virtual ~OR();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OR* get( Reader *r, int end, Context *ctx );
		static OR* getByName( const char *name );



	protected:

		static int id;

	};

	class XOR : public Action {
	public:
		XOR();
		virtual ~XOR();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static XOR* get( Reader *r, int end, Context *ctx );
		static XOR* getByName( const char *name );



	protected:

		static int id;

	};

	class ShiftLeft : public Action {
	public:
		ShiftLeft();
		virtual ~ShiftLeft();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static ShiftLeft* get( Reader *r, int end, Context *ctx );
		static ShiftLeft* getByName( const char *name );



	protected:

		static int id;

	};

	class ShiftRight : public Action {
	public:
		ShiftRight();
		virtual ~ShiftRight();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static ShiftRight* get( Reader *r, int end, Context *ctx );
		static ShiftRight* getByName( const char *name );



	protected:

		static int id;

	};

	class ShiftRightUnsigned : public Action {
	public:
		ShiftRightUnsigned();
		virtual ~ShiftRightUnsigned();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static ShiftRightUnsigned* get( Reader *r, int end, Context *ctx );
		static ShiftRightUnsigned* getByName( const char *name );



	protected:

		static int id;

	};

	class StrictEqual : public Action {
	public:
		StrictEqual();
		virtual ~StrictEqual();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static StrictEqual* get( Reader *r, int end, Context *ctx );
		static StrictEqual* getByName( const char *name );



	protected:

		static int id;

	};

	class GreaterThanTyped : public Action {
	public:
		GreaterThanTyped();
		virtual ~GreaterThanTyped();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static GreaterThanTyped* get( Reader *r, int end, Context *ctx );
		static GreaterThanTyped* getByName( const char *name );



	protected:

		static int id;

	};

	class StringGreaterThan : public Action {
	public:
		StringGreaterThan();
		virtual ~StringGreaterThan();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static StringGreaterThan* get( Reader *r, int end, Context *ctx );
		static StringGreaterThan* getByName( const char *name );



	protected:

		static int id;

	};

	class Extends : public Action {
	public:
		Extends();
		virtual ~Extends();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Extends* get( Reader *r, int end, Context *ctx );
		static Extends* getByName( const char *name );



	protected:

		static int id;

	};

	class GotoFrame : public Action {
	public:
		GotoFrame();
		virtual ~GotoFrame();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static GotoFrame* get( Reader *r, int end, Context *ctx );
		static GotoFrame* getByName( const char *name );

		unsigned short getframe();
		void setframe( unsigned short );


	protected:
		unsigned short frame; // word

		static int id;

	};

	class GetURL : public Action {
	public:
		GetURL();
		virtual ~GetURL();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static GetURL* get( Reader *r, int end, Context *ctx );
		static GetURL* getByName( const char *name );

		char * geturl();
		void seturl( char * );
		char * gettarget();
		void settarget( char * );


	protected:
		char * url; // string
		char * target; // string

		static int id;

	};

	class StoreRegister : public Action {
	public:
		StoreRegister();
		virtual ~StoreRegister();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static StoreRegister* get( Reader *r, int end, Context *ctx );
		static StoreRegister* getByName( const char *name );

		unsigned char getreg();
		void setreg( unsigned char );


	protected:
		unsigned char reg; // byte

		static int id;

	};

	class Dictionary : public Action {
	public:
		Dictionary();
		virtual ~Dictionary();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Dictionary* get( Reader *r, int end, Context *ctx );
		static Dictionary* getByName( const char *name );

		unsigned short getlength();
		void setlength( unsigned short );
		List<String> *getstrings();


	protected:
		unsigned short length; // word
		List<String> strings; // list

		static int id;

	};

	class WaitForFrame : public Action {
	public:
		WaitForFrame();
		virtual ~WaitForFrame();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static WaitForFrame* get( Reader *r, int end, Context *ctx );
		static WaitForFrame* getByName( const char *name );

		unsigned short getframe();
		void setframe( unsigned short );
		unsigned char getskip();
		void setskip( unsigned char );


	protected:
		unsigned short frame; // word
		unsigned char skip; // byte

		static int id;

	};

	class SetTarget : public Action {
	public:
		SetTarget();
		virtual ~SetTarget();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static SetTarget* get( Reader *r, int end, Context *ctx );
		static SetTarget* getByName( const char *name );

		char * getlabel();
		void setlabel( char * );


	protected:
		char * label; // string

		static int id;

	};

	class DoAction : public Tag {
	public:
		DoAction();
		virtual ~DoAction();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );

		static DoAction* get( Reader *r, int end, Context *ctx );
		static DoAction* getByName( const char *name );

		List<Action> *getactions();


	protected:
		List<Action> actions; // list

		static int id;

	};

	class GotoLabel : public Action {
	public:
		GotoLabel();
		virtual ~GotoLabel();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static GotoLabel* get( Reader *r, int end, Context *ctx );
		static GotoLabel* getByName( const char *name );

		char * getlabel();
		void setlabel( char * );


	protected:
		char * label; // string

		static int id;

	};

	class WaitForFrameDynamic : public Action {
	public:
		WaitForFrameDynamic();
		virtual ~WaitForFrameDynamic();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static WaitForFrameDynamic* get( Reader *r, int end, Context *ctx );
		static WaitForFrameDynamic* getByName( const char *name );

		unsigned short getframe();
		void setframe( unsigned short );
		unsigned char getskip();
		void setskip( unsigned char );


	protected:
		unsigned short frame; // word
		unsigned char skip; // byte

		static int id;

	};

	class Parameter : public Item {
	public:
		Parameter();
		virtual ~Parameter();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Parameter* get( Reader *r, int end, Context *ctx );
		static Parameter* getByName( const char *name );

		unsigned char getreg();
		void setreg( unsigned char );
		char * getname();
		void setname( char * );


	protected:
		unsigned char reg; // byte
		char * name; // string

	};

	class Header : public Item {
	public:
		Header();
		virtual ~Header();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Header* get( Reader *r, int end, Context *ctx );
		static Header* getByName( const char *name );

		Rectangle *getsize();
		int getframerate();
		void setframerate( int );
		unsigned short getframes();
		void setframes( unsigned short );

		List<Tag> *gettags();

		void addDetection( const char *szTagName, const char *szDetection );
		std::vector<std::pair<std::string, std::string> > & getDetections();
        bool findEndTag() {return hasFoundEndTag;}

		bool maybeCVE20070071() {
			return maybe_cve_2007_0071_;
		}

	protected:
		Rectangle size; // object
		int framerate; // integer
		unsigned short frames; // word
		List<Tag> tags; // list
		std::vector<std::pair<std::string, std::string> > detections;
        bool hasFoundEndTag;

	private:
		bool maybe_cve_2007_0071_;
	};

	class UnknownFilter : public Filter {
	public:
		UnknownFilter();
		virtual ~UnknownFilter();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static UnknownFilter* get( Reader *r, int end, Context *ctx );
		static UnknownFilter* getByName( const char *name );


		void getdata( unsigned char **dst, int *size );
		void setdata( const unsigned char *src, int size );


	protected:
		unsigned char * data; // data

		static int id;

	};

	class DeclareFunction2 : public Action {
	public:
		DeclareFunction2();
		virtual ~DeclareFunction2();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static DeclareFunction2* get( Reader *r, int end, Context *ctx );
		static DeclareFunction2* getByName( const char *name );

		char * getname();
		void setname( char * );
		unsigned short getargc();
		void setargc( unsigned short );
		unsigned char getregc();
		void setregc( unsigned char );
		bool getpreloadParent();
		void setpreloadParent( bool );
		bool getpreloadRoot();
		void setpreloadRoot( bool );
		bool getsuppressSuper();
		void setsuppressSuper( bool );
		bool getpreloadSuper();
		void setpreloadSuper( bool );
		bool getsuppressArguments();
		void setsuppressArguments( bool );
		bool getpreloadArguments();
		void setpreloadArguments( bool );
		bool getsuppressThis();
		void setsuppressThis( bool );
		bool getpreloadThis();
		void setpreloadThis( bool );
		int getreserved();
		void setreserved( int );
		bool getpreloadGlobal();
		void setpreloadGlobal( bool );
		List<Parameter> *getargs();
		unsigned short getlength();
		void setlength( unsigned short );
		List<Action> *getactions();


	protected:
		char * name; // string
		unsigned short argc; // word
		unsigned char regc; // byte
		bool preloadParent; // bit
		bool preloadRoot; // bit
		bool suppressSuper; // bit
		bool preloadSuper; // bit
		bool suppressArguments; // bit
		bool preloadArguments; // bit
		bool suppressThis; // bit
		bool preloadThis; // bit
		int reserved; // integer
		bool preloadGlobal; // bit
		List<Parameter> args; // list
		unsigned short length; // word
		List<Action> actions; // list

		static int id;

	};

	class Try : public Action {
	public:
		Try();
		virtual ~Try();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Try* get( Reader *r, int end, Context *ctx );
		static Try* getByName( const char *name );

		int getreserved();
		void setreserved( int );
		bool getcatchInRegister();
		void setcatchInRegister( bool );
		bool getdoFinally();
		void setdoFinally( bool );
		bool getdoCatch();
		void setdoCatch( bool );
		unsigned short gettrySize();
		void settrySize( unsigned short );
		unsigned short getcatchSize();
		void setcatchSize( unsigned short );
		unsigned short getfinallySize();
		void setfinallySize( unsigned short );
		unsigned char getreg();
		void setreg( unsigned char );


	protected:
		int reserved; // integer
		bool catchInRegister; // bit
		bool doFinally; // bit
		bool doCatch; // bit
		unsigned short trySize; // word
		unsigned short catchSize; // word
		unsigned short finallySize; // word
		unsigned char reg; // byte

		static int id;

	};

	class With : public Action {
	public:
		With();
		virtual ~With();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static With* get( Reader *r, int end, Context *ctx );
		static With* getByName( const char *name );

		unsigned short getsize();
		void setsize( unsigned short );


	protected:
		unsigned short size; // word

		static int id;

	};

	class PushData : public Action {
	public:
		PushData();
		virtual ~PushData();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static PushData* get( Reader *r, int end, Context *ctx );
		static PushData* getByName( const char *name );

		List<StackItem> *getitems();


	protected:
		List<StackItem> items; // list

		static int id;

	};

	class GetURL2 : public Action {
	public:
		GetURL2();
		virtual ~GetURL2();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static GetURL2* get( Reader *r, int end, Context *ctx );
		static GetURL2* getByName( const char *name );

		unsigned char getmethod();
		void setmethod( unsigned char );


	protected:
		unsigned char method; // byte

		static int id;

	};

	class DeclareFunction : public Action {
	public:
		DeclareFunction();
		virtual ~DeclareFunction();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static DeclareFunction* get( Reader *r, int end, Context *ctx );
		static DeclareFunction* getByName( const char *name );

		char * getname();
		void setname( char * );
		unsigned short getargc();
		void setargc( unsigned short );
		List<String> *getargs();
		unsigned short getlength();
		void setlength( unsigned short );


	protected:
		char * name; // string
		unsigned short argc; // word
		List<String> args; // list
		unsigned short length; // word

		static int id;

	};

	class BranchAlways : public Action {
	public:
		BranchAlways();
		virtual ~BranchAlways();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static BranchAlways* get( Reader *r, int end, Context *ctx );
		static BranchAlways* getByName( const char *name );

		unsigned short getbyteOffset();
		void setbyteOffset( unsigned short );


	protected:
		unsigned short byteOffset; // word

		static int id;

	};

	class BranchIfTrue : public Action {
	public:
		BranchIfTrue();
		virtual ~BranchIfTrue();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static BranchIfTrue* get( Reader *r, int end, Context *ctx );
		static BranchIfTrue* getByName( const char *name );

		unsigned short getbyteOffset();
		void setbyteOffset( unsigned short );


	protected:
		unsigned short byteOffset; // word

		static int id;

	};

	class CallFrame : public Action {
	public:
		CallFrame();
		virtual ~CallFrame();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static CallFrame* get( Reader *r, int end, Context *ctx );
		static CallFrame* getByName( const char *name );



	protected:

		static int id;

	};

	class GotoExpression : public Action {
	public:
		GotoExpression();
		virtual ~GotoExpression();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static GotoExpression* get( Reader *r, int end, Context *ctx );
		static GotoExpression* getByName( const char *name );

		unsigned char getplay();
		void setplay( unsigned char );


	protected:
		unsigned char play; // byte

		static int id;

	};

	class PrivateNamespace : public NamespaceConstant {
	public:
		PrivateNamespace();
		virtual ~PrivateNamespace();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static PrivateNamespace* get( Reader *r, int end, Context *ctx );
		static PrivateNamespace* getByName( const char *name );

		unsigned int getindex();
		void setindex( unsigned int );


	protected:
		unsigned int index; // u30

		static int id;

	};

	class Namespace : public NamespaceConstant {
	public:
		Namespace();
		virtual ~Namespace();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Namespace* get( Reader *r, int end, Context *ctx );
		static Namespace* getByName( const char *name );

		unsigned int getindex();
		void setindex( unsigned int );


	protected:
		unsigned int index; // u30

		static int id;

	};

	class PackageNamespace : public NamespaceConstant {
	public:
		PackageNamespace();
		virtual ~PackageNamespace();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static PackageNamespace* get( Reader *r, int end, Context *ctx );
		static PackageNamespace* getByName( const char *name );

		unsigned int getindex();
		void setindex( unsigned int );


	protected:
		unsigned int index; // u30

		static int id;

	};

	class PackageInternalNamespace : public NamespaceConstant {
	public:
		PackageInternalNamespace();
		virtual ~PackageInternalNamespace();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static PackageInternalNamespace* get( Reader *r, int end, Context *ctx );
		static PackageInternalNamespace* getByName( const char *name );

		unsigned int getindex();
		void setindex( unsigned int );


	protected:
		unsigned int index; // u30

		static int id;

	};

	class ProtectedNamespace : public NamespaceConstant {
	public:
		ProtectedNamespace();
		virtual ~ProtectedNamespace();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static ProtectedNamespace* get( Reader *r, int end, Context *ctx );
		static ProtectedNamespace* getByName( const char *name );

		unsigned int getindex();
		void setindex( unsigned int );


	protected:
		unsigned int index; // u30

		static int id;

	};

	class ExplicitNamespace : public NamespaceConstant {
	public:
		ExplicitNamespace();
		virtual ~ExplicitNamespace();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static ExplicitNamespace* get( Reader *r, int end, Context *ctx );
		static ExplicitNamespace* getByName( const char *name );

		unsigned int getindex();
		void setindex( unsigned int );


	protected:
		unsigned int index; // u30

		static int id;

	};

	class MultinameLNamespace : public NamespaceConstant {
	public:
		MultinameLNamespace();
		virtual ~MultinameLNamespace();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static MultinameLNamespace* get( Reader *r, int end, Context *ctx );
		static MultinameLNamespace* getByName( const char *name );

		unsigned int getindex();
		void setindex( unsigned int );


	protected:
		unsigned int index; // u30

		static int id;

	};

	class QName : public MultinameConstant {
	public:
		QName();
		virtual ~QName();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static QName* get( Reader *r, int end, Context *ctx );
		static QName* getByName( const char *name );

		unsigned int getnamespaceIndex();
		void setnamespaceIndex( unsigned int );
		unsigned int getnameIndex();
		void setnameIndex( unsigned int );


	protected:
		unsigned int namespaceIndex; // u30
		unsigned int nameIndex; // u30

		static int id;

	};

	class QNameA : public MultinameConstant {
	public:
		QNameA();
		virtual ~QNameA();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static QNameA* get( Reader *r, int end, Context *ctx );
		static QNameA* getByName( const char *name );

		unsigned int getnamespaceIndex();
		void setnamespaceIndex( unsigned int );
		unsigned int getnameIndex();
		void setnameIndex( unsigned int );


	protected:
		unsigned int namespaceIndex; // u30
		unsigned int nameIndex; // u30

		static int id;

	};

	class Multiname : public MultinameConstant {
	public:
		Multiname();
		virtual ~Multiname();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Multiname* get( Reader *r, int end, Context *ctx );
		static Multiname* getByName( const char *name );

		unsigned int getnameIndex();
		void setnameIndex( unsigned int );
		unsigned int getnamespaceSetIndex();
		void setnamespaceSetIndex( unsigned int );


	protected:
		unsigned int nameIndex; // u30
		unsigned int namespaceSetIndex; // u30

		static int id;

	};

	class MultinameA : public MultinameConstant {
	public:
		MultinameA();
		virtual ~MultinameA();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static MultinameA* get( Reader *r, int end, Context *ctx );
		static MultinameA* getByName( const char *name );

		unsigned int getnameIndex();
		void setnameIndex( unsigned int );
		unsigned int getnamespaceSetIndex();
		void setnamespaceSetIndex( unsigned int );


	protected:
		unsigned int nameIndex; // u30
		unsigned int namespaceSetIndex; // u30

		static int id;

	};

	class RTQName : public MultinameConstant {
	public:
		RTQName();
		virtual ~RTQName();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static RTQName* get( Reader *r, int end, Context *ctx );
		static RTQName* getByName( const char *name );

		unsigned int getnameIndex();
		void setnameIndex( unsigned int );


	protected:
		unsigned int nameIndex; // u30

		static int id;

	};

	class RTQNameA : public MultinameConstant {
	public:
		RTQNameA();
		virtual ~RTQNameA();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static RTQNameA* get( Reader *r, int end, Context *ctx );
		static RTQNameA* getByName( const char *name );

		unsigned int getnameIndex();
		void setnameIndex( unsigned int );


	protected:
		unsigned int nameIndex; // u30

		static int id;

	};

	class MultinameL : public MultinameConstant {
	public:
		MultinameL();
		virtual ~MultinameL();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static MultinameL* get( Reader *r, int end, Context *ctx );
		static MultinameL* getByName( const char *name );

		unsigned int getnamespaceSetIndex();
		void setnamespaceSetIndex( unsigned int );


	protected:
		unsigned int namespaceSetIndex; // u30

		static int id;

	};

	class RTQNameL : public MultinameConstant {
	public:
		RTQNameL();
		virtual ~RTQNameL();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static RTQNameL* get( Reader *r, int end, Context *ctx );
		static RTQNameL* getByName( const char *name );



	protected:

		static int id;

	};

	class RTQNameLA : public MultinameConstant {
	public:
		RTQNameLA();
		virtual ~RTQNameLA();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static RTQNameLA* get( Reader *r, int end, Context *ctx );
		static RTQNameLA* getByName( const char *name );



	protected:

		static int id;

	};

	class TypeName : public MultinameConstant {
	public:
		TypeName();
		virtual ~TypeName();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static TypeName* get( Reader *r, int end, Context *ctx );
		static TypeName* getByName( const char *name );

		unsigned int getnameIndex();
		void setnameIndex( unsigned int );
		unsigned int getnameCount();
		void setnameCount( unsigned int );
		List<U30> *gettypes();


	protected:
		unsigned int nameIndex; // u30
		unsigned int nameCount; // u30
		List<U30> types; // list

		static int id;

	};

	class Slot : public Trait {
	public:
		Slot();
		virtual ~Slot();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Slot* get( Reader *r, int end, Context *ctx );
		static Slot* getByName( const char *name );

		unsigned int getslotID();
		void setslotID( unsigned int );
		unsigned int gettypeIndex();
		void settypeIndex( unsigned int );
		unsigned int getvalueIndex();
		void setvalueIndex( unsigned int );
		unsigned char getvalueKind();
		void setvalueKind( unsigned char );


	protected:
		unsigned int slotID; // u30
		unsigned int typeIndex; // u30
		unsigned int valueIndex; // u30
		unsigned char valueKind; // byte

		static int id;

	};

	class Const : public Trait {
	public:
		Const();
		virtual ~Const();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Const* get( Reader *r, int end, Context *ctx );
		static Const* getByName( const char *name );

		unsigned int getslotID();
		void setslotID( unsigned int );
		unsigned int gettypeIndex();
		void settypeIndex( unsigned int );
		unsigned int getvalueIndex();
		void setvalueIndex( unsigned int );
		unsigned char getvalueKind();
		void setvalueKind( unsigned char );


	protected:
		unsigned int slotID; // u30
		unsigned int typeIndex; // u30
		unsigned int valueIndex; // u30
		unsigned char valueKind; // byte

		static int id;

	};

	class Method : public Trait {
	public:
		Method();
		virtual ~Method();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Method* get( Reader *r, int end, Context *ctx );
		static Method* getByName( const char *name );

		unsigned int getdispID();
		void setdispID( unsigned int );
		unsigned int getmethodInfo();
		void setmethodInfo( unsigned int );


	protected:
		unsigned int dispID; // u30
		unsigned int methodInfo; // u30

		static int id;

	};

	class Getter : public Trait {
	public:
		Getter();
		virtual ~Getter();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Getter* get( Reader *r, int end, Context *ctx );
		static Getter* getByName( const char *name );

		unsigned int getdispID();
		void setdispID( unsigned int );
		unsigned int getmethodInfo();
		void setmethodInfo( unsigned int );


	protected:
		unsigned int dispID; // u30
		unsigned int methodInfo; // u30

		static int id;

	};

	class Setter : public Trait {
	public:
		Setter();
		virtual ~Setter();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Setter* get( Reader *r, int end, Context *ctx );
		static Setter* getByName( const char *name );

		unsigned int getdispID();
		void setdispID( unsigned int );
		unsigned int getmethodInfo();
		void setmethodInfo( unsigned int );


	protected:
		unsigned int dispID; // u30
		unsigned int methodInfo; // u30

		static int id;

	};

	class Class : public Trait {
	public:
		Class();
		virtual ~Class();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Class* get( Reader *r, int end, Context *ctx );
		static Class* getByName( const char *name );

		unsigned int getslotID();
		void setslotID( unsigned int );
		unsigned int getclassInfo();
		void setclassInfo( unsigned int );


	protected:
		unsigned int slotID; // u30
		unsigned int classInfo; // u30

		static int id;

	};

	class Function : public Trait {
	public:
		Function();
		virtual ~Function();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static Function* get( Reader *r, int end, Context *ctx );
		static Function* getByName( const char *name );

		unsigned int getslotID();
		void setslotID( unsigned int );
		unsigned int getmethodInfo();
		void setmethodInfo( unsigned int );


	protected:
		unsigned int slotID; // u30
		unsigned int methodInfo; // u30

		static int id;

	};

	class UnknownOpCode : public OpCode {
	public:
		UnknownOpCode();
		virtual ~UnknownOpCode();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static UnknownOpCode* get( Reader *r, int end, Context *ctx );
		static UnknownOpCode* getByName( const char *name );


		void getdata( unsigned char **dst, int *size );
		void setdata( const unsigned char *src, int size );


	protected:
		unsigned char * data; // data

		static int id;

	};

	class OpBkPt : public OpCode {
	public:
		OpBkPt();
		virtual ~OpBkPt();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpBkPt* get( Reader *r, int end, Context *ctx );
		static OpBkPt* getByName( const char *name );



	protected:

		static int id;

	};

	class OpNop : public OpCode {
	public:
		OpNop();
		virtual ~OpNop();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpNop* get( Reader *r, int end, Context *ctx );
		static OpNop* getByName( const char *name );



	protected:

		static int id;

	};

	class OpThrow : public OpCode {
	public:
		OpThrow();
		virtual ~OpThrow();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpThrow* get( Reader *r, int end, Context *ctx );
		static OpThrow* getByName( const char *name );



	protected:

		static int id;

	};

	class OpGetSuper : public OpCode {
	public:
		OpGetSuper();
		virtual ~OpGetSuper();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpGetSuper* get( Reader *r, int end, Context *ctx );
		static OpGetSuper* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );


	protected:
		unsigned int name; // u30

		static int id;

	};

	class OpSetSuper : public OpCode {
	public:
		OpSetSuper();
		virtual ~OpSetSuper();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpSetSuper* get( Reader *r, int end, Context *ctx );
		static OpSetSuper* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );


	protected:
		unsigned int name; // u30

		static int id;

	};

	class OpDXNs : public OpCode {
	public:
		OpDXNs();
		virtual ~OpDXNs();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpDXNs* get( Reader *r, int end, Context *ctx );
		static OpDXNs* getByName( const char *name );

		unsigned int getdxns();
		void setdxns( unsigned int );


	protected:
		unsigned int dxns; // u30

		static int id;

	};

	class OpDXNsLate : public OpCode {
	public:
		OpDXNsLate();
		virtual ~OpDXNsLate();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpDXNsLate* get( Reader *r, int end, Context *ctx );
		static OpDXNsLate* getByName( const char *name );



	protected:

		static int id;

	};

	class OpKill : public OpCode {
	public:
		OpKill();
		virtual ~OpKill();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpKill* get( Reader *r, int end, Context *ctx );
		static OpKill* getByName( const char *name );

		unsigned int getaddress();
		void setaddress( unsigned int );


	protected:
		unsigned int address; // u30

		static int id;

	};

	class OpLabel : public OpCode {
	public:
		OpLabel();
		virtual ~OpLabel();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpLabel* get( Reader *r, int end, Context *ctx );
		static OpLabel* getByName( const char *name );



	protected:

		static int id;

	};

	class OpIfNlt : public OpCode {
	public:
		OpIfNlt();
		virtual ~OpIfNlt();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIfNlt* get( Reader *r, int end, Context *ctx );
		static OpIfNlt* getByName( const char *name );

		int gettarget();
		void settarget( int );


	protected:
		int target; // s24

		static int id;

	};

	class OpIfNle : public OpCode {
	public:
		OpIfNle();
		virtual ~OpIfNle();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIfNle* get( Reader *r, int end, Context *ctx );
		static OpIfNle* getByName( const char *name );

		int gettarget();
		void settarget( int );


	protected:
		int target; // s24

		static int id;

	};

	class OpIfNgt : public OpCode {
	public:
		OpIfNgt();
		virtual ~OpIfNgt();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIfNgt* get( Reader *r, int end, Context *ctx );
		static OpIfNgt* getByName( const char *name );

		int gettarget();
		void settarget( int );


	protected:
		int target; // s24

		static int id;

	};

	class OpIfNge : public OpCode {
	public:
		OpIfNge();
		virtual ~OpIfNge();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIfNge* get( Reader *r, int end, Context *ctx );
		static OpIfNge* getByName( const char *name );

		int gettarget();
		void settarget( int );


	protected:
		int target; // s24

		static int id;

	};

	class OpJump : public OpCode {
	public:
		OpJump();
		virtual ~OpJump();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpJump* get( Reader *r, int end, Context *ctx );
		static OpJump* getByName( const char *name );

		int gettarget();
		void settarget( int );


	protected:
		int target; // s24

		static int id;

	};

	class OpIfTrue : public OpCode {
	public:
		OpIfTrue();
		virtual ~OpIfTrue();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIfTrue* get( Reader *r, int end, Context *ctx );
		static OpIfTrue* getByName( const char *name );

		int gettarget();
		void settarget( int );


	protected:
		int target; // s24

		static int id;

	};

	class OpIfFalse : public OpCode {
	public:
		OpIfFalse();
		virtual ~OpIfFalse();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIfFalse* get( Reader *r, int end, Context *ctx );
		static OpIfFalse* getByName( const char *name );

		int gettarget();
		void settarget( int );


	protected:
		int target; // s24

		static int id;

	};

	class OpIfEq : public OpCode {
	public:
		OpIfEq();
		virtual ~OpIfEq();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIfEq* get( Reader *r, int end, Context *ctx );
		static OpIfEq* getByName( const char *name );

		int gettarget();
		void settarget( int );


	protected:
		int target; // s24

		static int id;

	};

	class OpIfNe : public OpCode {
	public:
		OpIfNe();
		virtual ~OpIfNe();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIfNe* get( Reader *r, int end, Context *ctx );
		static OpIfNe* getByName( const char *name );

		int gettarget();
		void settarget( int );


	protected:
		int target; // s24

		static int id;

	};

	class OpIfLt : public OpCode {
	public:
		OpIfLt();
		virtual ~OpIfLt();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIfLt* get( Reader *r, int end, Context *ctx );
		static OpIfLt* getByName( const char *name );

		int gettarget();
		void settarget( int );


	protected:
		int target; // s24

		static int id;

	};

	class OpIfLe : public OpCode {
	public:
		OpIfLe();
		virtual ~OpIfLe();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIfLe* get( Reader *r, int end, Context *ctx );
		static OpIfLe* getByName( const char *name );

		int gettarget();
		void settarget( int );


	protected:
		int target; // s24

		static int id;

	};

	class OpIfGt : public OpCode {
	public:
		OpIfGt();
		virtual ~OpIfGt();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIfGt* get( Reader *r, int end, Context *ctx );
		static OpIfGt* getByName( const char *name );

		int gettarget();
		void settarget( int );


	protected:
		int target; // s24

		static int id;

	};

	class OpIfGe : public OpCode {
	public:
		OpIfGe();
		virtual ~OpIfGe();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIfGe* get( Reader *r, int end, Context *ctx );
		static OpIfGe* getByName( const char *name );

		int gettarget();
		void settarget( int );


	protected:
		int target; // s24

		static int id;

	};

	class OpIfStrictEq : public OpCode {
	public:
		OpIfStrictEq();
		virtual ~OpIfStrictEq();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIfStrictEq* get( Reader *r, int end, Context *ctx );
		static OpIfStrictEq* getByName( const char *name );

		int gettarget();
		void settarget( int );


	protected:
		int target; // s24

		static int id;

	};

	class OpIfStrictNe : public OpCode {
	public:
		OpIfStrictNe();
		virtual ~OpIfStrictNe();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIfStrictNe* get( Reader *r, int end, Context *ctx );
		static OpIfStrictNe* getByName( const char *name );

		int gettarget();
		void settarget( int );


	protected:
		int target; // s24

		static int id;

	};

	class OpLookupSwitch : public OpCode {
	public:
		OpLookupSwitch();
		virtual ~OpLookupSwitch();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpLookupSwitch* get( Reader *r, int end, Context *ctx );
		static OpLookupSwitch* getByName( const char *name );

		int getdefaulTarget();
		void setdefaulTarget( int );
		unsigned int getcaseCount();
		void setcaseCount( unsigned int );
		List<S24> *gettargetTable();


	protected:
		int defaulTarget; // s24
		unsigned int caseCount; // u30
		List<S24> targetTable; // list

		static int id;

	};

	class OpPushWith : public OpCode {
	public:
		OpPushWith();
		virtual ~OpPushWith();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpPushWith* get( Reader *r, int end, Context *ctx );
		static OpPushWith* getByName( const char *name );



	protected:

		static int id;

	};

	class OpPopScope : public OpCode {
	public:
		OpPopScope();
		virtual ~OpPopScope();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpPopScope* get( Reader *r, int end, Context *ctx );
		static OpPopScope* getByName( const char *name );



	protected:

		static int id;

	};

	class OpNextName : public OpCode {
	public:
		OpNextName();
		virtual ~OpNextName();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpNextName* get( Reader *r, int end, Context *ctx );
		static OpNextName* getByName( const char *name );



	protected:

		static int id;

	};

	class OpHasNext : public OpCode {
	public:
		OpHasNext();
		virtual ~OpHasNext();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpHasNext* get( Reader *r, int end, Context *ctx );
		static OpHasNext* getByName( const char *name );



	protected:

		static int id;

	};

	class OpPushNull : public OpCode {
	public:
		OpPushNull();
		virtual ~OpPushNull();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpPushNull* get( Reader *r, int end, Context *ctx );
		static OpPushNull* getByName( const char *name );



	protected:

		static int id;

	};

	class OpPushUndefined : public OpCode {
	public:
		OpPushUndefined();
		virtual ~OpPushUndefined();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpPushUndefined* get( Reader *r, int end, Context *ctx );
		static OpPushUndefined* getByName( const char *name );



	protected:

		static int id;

	};

	class OpNextValue : public OpCode {
	public:
		OpNextValue();
		virtual ~OpNextValue();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpNextValue* get( Reader *r, int end, Context *ctx );
		static OpNextValue* getByName( const char *name );



	protected:

		static int id;

	};

	class OpPushByte : public OpCode {
	public:
		OpPushByte();
		virtual ~OpPushByte();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpPushByte* get( Reader *r, int end, Context *ctx );
		static OpPushByte* getByName( const char *name );

		unsigned char getvalue();
		void setvalue( unsigned char );


	protected:
		unsigned char value; // byte

		static int id;

	};

	class OpPushShort : public OpCode {
	public:
		OpPushShort();
		virtual ~OpPushShort();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpPushShort* get( Reader *r, int end, Context *ctx );
		static OpPushShort* getByName( const char *name );

		unsigned int getvalue();
		void setvalue( unsigned int );


	protected:
		unsigned int value; // u30

		static int id;

	};

	class OpPushTrue : public OpCode {
	public:
		OpPushTrue();
		virtual ~OpPushTrue();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpPushTrue* get( Reader *r, int end, Context *ctx );
		static OpPushTrue* getByName( const char *name );



	protected:

		static int id;

	};

	class OpPushFalse : public OpCode {
	public:
		OpPushFalse();
		virtual ~OpPushFalse();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpPushFalse* get( Reader *r, int end, Context *ctx );
		static OpPushFalse* getByName( const char *name );



	protected:

		static int id;

	};

	class OpPushNaN : public OpCode {
	public:
		OpPushNaN();
		virtual ~OpPushNaN();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpPushNaN* get( Reader *r, int end, Context *ctx );
		static OpPushNaN* getByName( const char *name );



	protected:

		static int id;

	};

	class OpPop : public OpCode {
	public:
		OpPop();
		virtual ~OpPop();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpPop* get( Reader *r, int end, Context *ctx );
		static OpPop* getByName( const char *name );



	protected:

		static int id;

	};

	class OpDup : public OpCode {
	public:
		OpDup();
		virtual ~OpDup();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpDup* get( Reader *r, int end, Context *ctx );
		static OpDup* getByName( const char *name );



	protected:

		static int id;

	};

	class OpSwap : public OpCode {
	public:
		OpSwap();
		virtual ~OpSwap();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpSwap* get( Reader *r, int end, Context *ctx );
		static OpSwap* getByName( const char *name );



	protected:

		static int id;

	};

	class OpPushString : public OpCode {
	public:
		OpPushString();
		virtual ~OpPushString();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpPushString* get( Reader *r, int end, Context *ctx );
		static OpPushString* getByName( const char *name );

		unsigned int getindex();
		void setindex( unsigned int );


	protected:
		unsigned int index; // u30

		static int id;

	};

	class OpPushInt : public OpCode {
	public:
		OpPushInt();
		virtual ~OpPushInt();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpPushInt* get( Reader *r, int end, Context *ctx );
		static OpPushInt* getByName( const char *name );

		unsigned int getindex();
		void setindex( unsigned int );


	protected:
		unsigned int index; // u30

		static int id;

	};

	class OpPushUInt : public OpCode {
	public:
		OpPushUInt();
		virtual ~OpPushUInt();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpPushUInt* get( Reader *r, int end, Context *ctx );
		static OpPushUInt* getByName( const char *name );

		unsigned int getindex();
		void setindex( unsigned int );


	protected:
		unsigned int index; // u30

		static int id;

	};

	class OpPushDouble : public OpCode {
	public:
		OpPushDouble();
		virtual ~OpPushDouble();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpPushDouble* get( Reader *r, int end, Context *ctx );
		static OpPushDouble* getByName( const char *name );

		unsigned int getindex();
		void setindex( unsigned int );


	protected:
		unsigned int index; // u30

		static int id;

	};

	class OpPushScope : public OpCode {
	public:
		OpPushScope();
		virtual ~OpPushScope();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpPushScope* get( Reader *r, int end, Context *ctx );
		static OpPushScope* getByName( const char *name );



	protected:

		static int id;

	};

	class OpPushNamespace : public OpCode {
	public:
		OpPushNamespace();
		virtual ~OpPushNamespace();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpPushNamespace* get( Reader *r, int end, Context *ctx );
		static OpPushNamespace* getByName( const char *name );

		unsigned int getindex();
		void setindex( unsigned int );


	protected:
		unsigned int index; // u30

		static int id;

	};

	class OpHasNext2 : public OpCode {
	public:
		OpHasNext2();
		virtual ~OpHasNext2();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpHasNext2* get( Reader *r, int end, Context *ctx );
		static OpHasNext2* getByName( const char *name );

		unsigned int getobject();
		void setobject( unsigned int );
		unsigned int getindex();
		void setindex( unsigned int );


	protected:
		unsigned int object; // u30
		unsigned int index; // u30

		static int id;

	};

	class OpNewFunction : public OpCode {
	public:
		OpNewFunction();
		virtual ~OpNewFunction();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpNewFunction* get( Reader *r, int end, Context *ctx );
		static OpNewFunction* getByName( const char *name );

		unsigned int getindex();
		void setindex( unsigned int );


	protected:
		unsigned int index; // u30

		static int id;

	};

	class OpCall : public OpCode {
	public:
		OpCall();
		virtual ~OpCall();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpCall* get( Reader *r, int end, Context *ctx );
		static OpCall* getByName( const char *name );

		unsigned int getargc();
		void setargc( unsigned int );


	protected:
		unsigned int argc; // u30

		static int id;

	};

	class OpConstruct : public OpCode {
	public:
		OpConstruct();
		virtual ~OpConstruct();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpConstruct* get( Reader *r, int end, Context *ctx );
		static OpConstruct* getByName( const char *name );

		unsigned int getargc();
		void setargc( unsigned int );


	protected:
		unsigned int argc; // u30

		static int id;

	};

	class OpCallMethod : public OpCode {
	public:
		OpCallMethod();
		virtual ~OpCallMethod();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpCallMethod* get( Reader *r, int end, Context *ctx );
		static OpCallMethod* getByName( const char *name );

		unsigned int getdispID();
		void setdispID( unsigned int );
		unsigned int getargc();
		void setargc( unsigned int );


	protected:
		unsigned int dispID; // u30
		unsigned int argc; // u30

		static int id;

	};

	class OpCallStatic : public OpCode {
	public:
		OpCallStatic();
		virtual ~OpCallStatic();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpCallStatic* get( Reader *r, int end, Context *ctx );
		static OpCallStatic* getByName( const char *name );

		unsigned int getmethodID();
		void setmethodID( unsigned int );
		unsigned int getargc();
		void setargc( unsigned int );


	protected:
		unsigned int methodID; // u30
		unsigned int argc; // u30

		static int id;

	};

	class OpCallSuper : public OpCode {
	public:
		OpCallSuper();
		virtual ~OpCallSuper();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpCallSuper* get( Reader *r, int end, Context *ctx );
		static OpCallSuper* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );
		unsigned int getargc();
		void setargc( unsigned int );


	protected:
		unsigned int name; // u30
		unsigned int argc; // u30

		static int id;

	};

	class OpCallProperty : public OpCode {
	public:
		OpCallProperty();
		virtual ~OpCallProperty();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpCallProperty* get( Reader *r, int end, Context *ctx );
		static OpCallProperty* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );
		unsigned int getargc();
		void setargc( unsigned int );


	protected:
		unsigned int name; // u30
		unsigned int argc; // u30

		static int id;

	};

	class OpReturnVoid : public OpCode {
	public:
		OpReturnVoid();
		virtual ~OpReturnVoid();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpReturnVoid* get( Reader *r, int end, Context *ctx );
		static OpReturnVoid* getByName( const char *name );



	protected:

		static int id;

	};

	class OpReturnValue : public OpCode {
	public:
		OpReturnValue();
		virtual ~OpReturnValue();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpReturnValue* get( Reader *r, int end, Context *ctx );
		static OpReturnValue* getByName( const char *name );



	protected:

		static int id;

	};

	class OpConstructSuper : public OpCode {
	public:
		OpConstructSuper();
		virtual ~OpConstructSuper();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpConstructSuper* get( Reader *r, int end, Context *ctx );
		static OpConstructSuper* getByName( const char *name );

		unsigned int getargc();
		void setargc( unsigned int );


	protected:
		unsigned int argc; // u30

		static int id;

	};

	class OpConstructProp : public OpCode {
	public:
		OpConstructProp();
		virtual ~OpConstructProp();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpConstructProp* get( Reader *r, int end, Context *ctx );
		static OpConstructProp* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );
		unsigned int getargc();
		void setargc( unsigned int );


	protected:
		unsigned int name; // u30
		unsigned int argc; // u30

		static int id;

	};

	class OpCallPropLex : public OpCode {
	public:
		OpCallPropLex();
		virtual ~OpCallPropLex();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpCallPropLex* get( Reader *r, int end, Context *ctx );
		static OpCallPropLex* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );
		unsigned int getargc();
		void setargc( unsigned int );


	protected:
		unsigned int name; // u30
		unsigned int argc; // u30

		static int id;

	};

	class OpCallSuperVoid : public OpCode {
	public:
		OpCallSuperVoid();
		virtual ~OpCallSuperVoid();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpCallSuperVoid* get( Reader *r, int end, Context *ctx );
		static OpCallSuperVoid* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );
		unsigned int getargc();
		void setargc( unsigned int );


	protected:
		unsigned int name; // u30
		unsigned int argc; // u30

		static int id;

	};

	class OpCallPropVoid : public OpCode {
	public:
		OpCallPropVoid();
		virtual ~OpCallPropVoid();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpCallPropVoid* get( Reader *r, int end, Context *ctx );
		static OpCallPropVoid* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );
		unsigned int getargc();
		void setargc( unsigned int );


	protected:
		unsigned int name; // u30
		unsigned int argc; // u30

		static int id;

	};

	class OpApplyType : public OpCode {
	public:
		OpApplyType();
		virtual ~OpApplyType();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpApplyType* get( Reader *r, int end, Context *ctx );
		static OpApplyType* getByName( const char *name );

		unsigned int gettype();
		void settype( unsigned int );


	protected:
		unsigned int type; // u30

		static int id;

	};

	class OpNewObject : public OpCode {
	public:
		OpNewObject();
		virtual ~OpNewObject();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpNewObject* get( Reader *r, int end, Context *ctx );
		static OpNewObject* getByName( const char *name );

		unsigned int getargc();
		void setargc( unsigned int );


	protected:
		unsigned int argc; // u30

		static int id;

	};

	class OpNewArray : public OpCode {
	public:
		OpNewArray();
		virtual ~OpNewArray();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpNewArray* get( Reader *r, int end, Context *ctx );
		static OpNewArray* getByName( const char *name );

		unsigned int getargc();
		void setargc( unsigned int );


	protected:
		unsigned int argc; // u30

		static int id;

	};

	class OpNewActivation : public OpCode {
	public:
		OpNewActivation();
		virtual ~OpNewActivation();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpNewActivation* get( Reader *r, int end, Context *ctx );
		static OpNewActivation* getByName( const char *name );



	protected:

		static int id;

	};

	class OpNewClass : public OpCode {
	public:
		OpNewClass();
		virtual ~OpNewClass();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpNewClass* get( Reader *r, int end, Context *ctx );
		static OpNewClass* getByName( const char *name );

		unsigned int getclassIndex();
		void setclassIndex( unsigned int );


	protected:
		unsigned int classIndex; // u30

		static int id;

	};

	class OpGetDescendants : public OpCode {
	public:
		OpGetDescendants();
		virtual ~OpGetDescendants();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpGetDescendants* get( Reader *r, int end, Context *ctx );
		static OpGetDescendants* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );


	protected:
		unsigned int name; // u30

		static int id;

	};

	class OpNewCatch : public OpCode {
	public:
		OpNewCatch();
		virtual ~OpNewCatch();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpNewCatch* get( Reader *r, int end, Context *ctx );
		static OpNewCatch* getByName( const char *name );

		unsigned int getexceptionIndex();
		void setexceptionIndex( unsigned int );


	protected:
		unsigned int exceptionIndex; // u30

		static int id;

	};

	class OpFindPropStrict : public OpCode {
	public:
		OpFindPropStrict();
		virtual ~OpFindPropStrict();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpFindPropStrict* get( Reader *r, int end, Context *ctx );
		static OpFindPropStrict* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );


	protected:
		unsigned int name; // u30

		static int id;

	};

	class OpFindProperty : public OpCode {
	public:
		OpFindProperty();
		virtual ~OpFindProperty();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpFindProperty* get( Reader *r, int end, Context *ctx );
		static OpFindProperty* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );


	protected:
		unsigned int name; // u30

		static int id;

	};

	class OpFindDef : public OpCode {
	public:
		OpFindDef();
		virtual ~OpFindDef();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpFindDef* get( Reader *r, int end, Context *ctx );
		static OpFindDef* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );


	protected:
		unsigned int name; // u30

		static int id;

	};

	class OpGetLex : public OpCode {
	public:
		OpGetLex();
		virtual ~OpGetLex();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpGetLex* get( Reader *r, int end, Context *ctx );
		static OpGetLex* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );


	protected:
		unsigned int name; // u30

		static int id;

	};

	class OpSetProperty : public OpCode {
	public:
		OpSetProperty();
		virtual ~OpSetProperty();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpSetProperty* get( Reader *r, int end, Context *ctx );
		static OpSetProperty* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );


	protected:
		unsigned int name; // u30

		static int id;

	};

	class OpGetLocal : public OpCode {
	public:
		OpGetLocal();
		virtual ~OpGetLocal();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpGetLocal* get( Reader *r, int end, Context *ctx );
		static OpGetLocal* getByName( const char *name );

		unsigned int getaddress();
		void setaddress( unsigned int );


	protected:
		unsigned int address; // u30

		static int id;

	};

	class OpSetLocal : public OpCode {
	public:
		OpSetLocal();
		virtual ~OpSetLocal();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpSetLocal* get( Reader *r, int end, Context *ctx );
		static OpSetLocal* getByName( const char *name );

		unsigned int getaddress();
		void setaddress( unsigned int );


	protected:
		unsigned int address; // u30

		static int id;

	};

	class OpGetGlobalScope : public OpCode {
	public:
		OpGetGlobalScope();
		virtual ~OpGetGlobalScope();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpGetGlobalScope* get( Reader *r, int end, Context *ctx );
		static OpGetGlobalScope* getByName( const char *name );



	protected:

		static int id;

	};

	class OpGetScopeObject : public OpCode {
	public:
		OpGetScopeObject();
		virtual ~OpGetScopeObject();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpGetScopeObject* get( Reader *r, int end, Context *ctx );
		static OpGetScopeObject* getByName( const char *name );

		unsigned char getscopeIndex();
		void setscopeIndex( unsigned char );


	protected:
		unsigned char scopeIndex; // byte

		static int id;

	};

	class OpGetProperty : public OpCode {
	public:
		OpGetProperty();
		virtual ~OpGetProperty();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpGetProperty* get( Reader *r, int end, Context *ctx );
		static OpGetProperty* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );


	protected:
		unsigned int name; // u30

		static int id;

	};

	class OpInitProperty : public OpCode {
	public:
		OpInitProperty();
		virtual ~OpInitProperty();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpInitProperty* get( Reader *r, int end, Context *ctx );
		static OpInitProperty* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );


	protected:
		unsigned int name; // u30

		static int id;

	};

	class OpDeleteProperty : public OpCode {
	public:
		OpDeleteProperty();
		virtual ~OpDeleteProperty();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpDeleteProperty* get( Reader *r, int end, Context *ctx );
		static OpDeleteProperty* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );


	protected:
		unsigned int name; // u30

		static int id;

	};

	class OpGetSlot : public OpCode {
	public:
		OpGetSlot();
		virtual ~OpGetSlot();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpGetSlot* get( Reader *r, int end, Context *ctx );
		static OpGetSlot* getByName( const char *name );

		unsigned int getslotID();
		void setslotID( unsigned int );


	protected:
		unsigned int slotID; // u30

		static int id;

	};

	class OpSetSlot : public OpCode {
	public:
		OpSetSlot();
		virtual ~OpSetSlot();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpSetSlot* get( Reader *r, int end, Context *ctx );
		static OpSetSlot* getByName( const char *name );

		unsigned int getslotID();
		void setslotID( unsigned int );


	protected:
		unsigned int slotID; // u30

		static int id;

	};

	class OpGetGlobalSlot : public OpCode {
	public:
		OpGetGlobalSlot();
		virtual ~OpGetGlobalSlot();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpGetGlobalSlot* get( Reader *r, int end, Context *ctx );
		static OpGetGlobalSlot* getByName( const char *name );

		unsigned int getslotID();
		void setslotID( unsigned int );


	protected:
		unsigned int slotID; // u30

		static int id;

	};

	class OpSetGlobalSlot : public OpCode {
	public:
		OpSetGlobalSlot();
		virtual ~OpSetGlobalSlot();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpSetGlobalSlot* get( Reader *r, int end, Context *ctx );
		static OpSetGlobalSlot* getByName( const char *name );

		unsigned int getslotID();
		void setslotID( unsigned int );


	protected:
		unsigned int slotID; // u30

		static int id;

	};

	class OpConvertS : public OpCode {
	public:
		OpConvertS();
		virtual ~OpConvertS();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpConvertS* get( Reader *r, int end, Context *ctx );
		static OpConvertS* getByName( const char *name );



	protected:

		static int id;

	};

	class OpEscXelem : public OpCode {
	public:
		OpEscXelem();
		virtual ~OpEscXelem();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpEscXelem* get( Reader *r, int end, Context *ctx );
		static OpEscXelem* getByName( const char *name );



	protected:

		static int id;

	};

	class OpEscXattr : public OpCode {
	public:
		OpEscXattr();
		virtual ~OpEscXattr();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpEscXattr* get( Reader *r, int end, Context *ctx );
		static OpEscXattr* getByName( const char *name );



	protected:

		static int id;

	};

	class OpConvertI : public OpCode {
	public:
		OpConvertI();
		virtual ~OpConvertI();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpConvertI* get( Reader *r, int end, Context *ctx );
		static OpConvertI* getByName( const char *name );



	protected:

		static int id;

	};

	class OpConvertU : public OpCode {
	public:
		OpConvertU();
		virtual ~OpConvertU();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpConvertU* get( Reader *r, int end, Context *ctx );
		static OpConvertU* getByName( const char *name );



	protected:

		static int id;

	};

	class OpConvertD : public OpCode {
	public:
		OpConvertD();
		virtual ~OpConvertD();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpConvertD* get( Reader *r, int end, Context *ctx );
		static OpConvertD* getByName( const char *name );



	protected:

		static int id;

	};

	class OpConvertB : public OpCode {
	public:
		OpConvertB();
		virtual ~OpConvertB();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpConvertB* get( Reader *r, int end, Context *ctx );
		static OpConvertB* getByName( const char *name );



	protected:

		static int id;

	};

	class OpConvertO : public OpCode {
	public:
		OpConvertO();
		virtual ~OpConvertO();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpConvertO* get( Reader *r, int end, Context *ctx );
		static OpConvertO* getByName( const char *name );



	protected:

		static int id;

	};

	class OpCheckFilter : public OpCode {
	public:
		OpCheckFilter();
		virtual ~OpCheckFilter();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpCheckFilter* get( Reader *r, int end, Context *ctx );
		static OpCheckFilter* getByName( const char *name );



	protected:

		static int id;

	};

	class OpCoerce : public OpCode {
	public:
		OpCoerce();
		virtual ~OpCoerce();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpCoerce* get( Reader *r, int end, Context *ctx );
		static OpCoerce* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );


	protected:
		unsigned int name; // u30

		static int id;

	};

	class OpCoerceB : public OpCode {
	public:
		OpCoerceB();
		virtual ~OpCoerceB();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpCoerceB* get( Reader *r, int end, Context *ctx );
		static OpCoerceB* getByName( const char *name );



	protected:

		static int id;

	};

	class OpCoerceA : public OpCode {
	public:
		OpCoerceA();
		virtual ~OpCoerceA();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpCoerceA* get( Reader *r, int end, Context *ctx );
		static OpCoerceA* getByName( const char *name );



	protected:

		static int id;

	};

	class OpCoerceI : public OpCode {
	public:
		OpCoerceI();
		virtual ~OpCoerceI();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpCoerceI* get( Reader *r, int end, Context *ctx );
		static OpCoerceI* getByName( const char *name );



	protected:

		static int id;

	};

	class OpCoerceD : public OpCode {
	public:
		OpCoerceD();
		virtual ~OpCoerceD();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpCoerceD* get( Reader *r, int end, Context *ctx );
		static OpCoerceD* getByName( const char *name );



	protected:

		static int id;

	};

	class OpCoerceS : public OpCode {
	public:
		OpCoerceS();
		virtual ~OpCoerceS();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpCoerceS* get( Reader *r, int end, Context *ctx );
		static OpCoerceS* getByName( const char *name );



	protected:

		static int id;

	};

	class OpAsType : public OpCode {
	public:
		OpAsType();
		virtual ~OpAsType();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpAsType* get( Reader *r, int end, Context *ctx );
		static OpAsType* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );


	protected:
		unsigned int name; // u30

		static int id;

	};

	class OpAsTypeLate : public OpCode {
	public:
		OpAsTypeLate();
		virtual ~OpAsTypeLate();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpAsTypeLate* get( Reader *r, int end, Context *ctx );
		static OpAsTypeLate* getByName( const char *name );



	protected:

		static int id;

	};

	class OpCoerceU : public OpCode {
	public:
		OpCoerceU();
		virtual ~OpCoerceU();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpCoerceU* get( Reader *r, int end, Context *ctx );
		static OpCoerceU* getByName( const char *name );



	protected:

		static int id;

	};

	class OpCoerceO : public OpCode {
	public:
		OpCoerceO();
		virtual ~OpCoerceO();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpCoerceO* get( Reader *r, int end, Context *ctx );
		static OpCoerceO* getByName( const char *name );



	protected:

		static int id;

	};

	class OpNegate : public OpCode {
	public:
		OpNegate();
		virtual ~OpNegate();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpNegate* get( Reader *r, int end, Context *ctx );
		static OpNegate* getByName( const char *name );



	protected:

		static int id;

	};

	class OpIncrement : public OpCode {
	public:
		OpIncrement();
		virtual ~OpIncrement();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIncrement* get( Reader *r, int end, Context *ctx );
		static OpIncrement* getByName( const char *name );



	protected:

		static int id;

	};

	class OpIncLocal : public OpCode {
	public:
		OpIncLocal();
		virtual ~OpIncLocal();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIncLocal* get( Reader *r, int end, Context *ctx );
		static OpIncLocal* getByName( const char *name );

		unsigned int getaddress();
		void setaddress( unsigned int );


	protected:
		unsigned int address; // u30

		static int id;

	};

	class OpDecrement : public OpCode {
	public:
		OpDecrement();
		virtual ~OpDecrement();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpDecrement* get( Reader *r, int end, Context *ctx );
		static OpDecrement* getByName( const char *name );



	protected:

		static int id;

	};

	class OpDecLocal : public OpCode {
	public:
		OpDecLocal();
		virtual ~OpDecLocal();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpDecLocal* get( Reader *r, int end, Context *ctx );
		static OpDecLocal* getByName( const char *name );

		unsigned int getaddress();
		void setaddress( unsigned int );


	protected:
		unsigned int address; // u30

		static int id;

	};

	class OpTypeOf : public OpCode {
	public:
		OpTypeOf();
		virtual ~OpTypeOf();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpTypeOf* get( Reader *r, int end, Context *ctx );
		static OpTypeOf* getByName( const char *name );



	protected:

		static int id;

	};

	class OpNot : public OpCode {
	public:
		OpNot();
		virtual ~OpNot();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpNot* get( Reader *r, int end, Context *ctx );
		static OpNot* getByName( const char *name );



	protected:

		static int id;

	};

	class OpBitNot : public OpCode {
	public:
		OpBitNot();
		virtual ~OpBitNot();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpBitNot* get( Reader *r, int end, Context *ctx );
		static OpBitNot* getByName( const char *name );



	protected:

		static int id;

	};

	class OpAdd : public OpCode {
	public:
		OpAdd();
		virtual ~OpAdd();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpAdd* get( Reader *r, int end, Context *ctx );
		static OpAdd* getByName( const char *name );



	protected:

		static int id;

	};

	class OpSubtract : public OpCode {
	public:
		OpSubtract();
		virtual ~OpSubtract();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpSubtract* get( Reader *r, int end, Context *ctx );
		static OpSubtract* getByName( const char *name );



	protected:

		static int id;

	};

	class OpMultiply : public OpCode {
	public:
		OpMultiply();
		virtual ~OpMultiply();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpMultiply* get( Reader *r, int end, Context *ctx );
		static OpMultiply* getByName( const char *name );



	protected:

		static int id;

	};

	class OpDivide : public OpCode {
	public:
		OpDivide();
		virtual ~OpDivide();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpDivide* get( Reader *r, int end, Context *ctx );
		static OpDivide* getByName( const char *name );



	protected:

		static int id;

	};

	class OpModulo : public OpCode {
	public:
		OpModulo();
		virtual ~OpModulo();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpModulo* get( Reader *r, int end, Context *ctx );
		static OpModulo* getByName( const char *name );



	protected:

		static int id;

	};

	class OpLShift : public OpCode {
	public:
		OpLShift();
		virtual ~OpLShift();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpLShift* get( Reader *r, int end, Context *ctx );
		static OpLShift* getByName( const char *name );



	protected:

		static int id;

	};

	class OpRShift : public OpCode {
	public:
		OpRShift();
		virtual ~OpRShift();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpRShift* get( Reader *r, int end, Context *ctx );
		static OpRShift* getByName( const char *name );



	protected:

		static int id;

	};

	class OpURShift : public OpCode {
	public:
		OpURShift();
		virtual ~OpURShift();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpURShift* get( Reader *r, int end, Context *ctx );
		static OpURShift* getByName( const char *name );



	protected:

		static int id;

	};

	class OpBitAnd : public OpCode {
	public:
		OpBitAnd();
		virtual ~OpBitAnd();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpBitAnd* get( Reader *r, int end, Context *ctx );
		static OpBitAnd* getByName( const char *name );



	protected:

		static int id;

	};

	class OpBitOr : public OpCode {
	public:
		OpBitOr();
		virtual ~OpBitOr();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpBitOr* get( Reader *r, int end, Context *ctx );
		static OpBitOr* getByName( const char *name );



	protected:

		static int id;

	};

	class OpBitXor : public OpCode {
	public:
		OpBitXor();
		virtual ~OpBitXor();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpBitXor* get( Reader *r, int end, Context *ctx );
		static OpBitXor* getByName( const char *name );



	protected:

		static int id;

	};

	class OpEquals : public OpCode {
	public:
		OpEquals();
		virtual ~OpEquals();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpEquals* get( Reader *r, int end, Context *ctx );
		static OpEquals* getByName( const char *name );



	protected:

		static int id;

	};

	class OpStrictEquals : public OpCode {
	public:
		OpStrictEquals();
		virtual ~OpStrictEquals();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpStrictEquals* get( Reader *r, int end, Context *ctx );
		static OpStrictEquals* getByName( const char *name );



	protected:

		static int id;

	};

	class OpLessThan : public OpCode {
	public:
		OpLessThan();
		virtual ~OpLessThan();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpLessThan* get( Reader *r, int end, Context *ctx );
		static OpLessThan* getByName( const char *name );



	protected:

		static int id;

	};

	class OpLessEquals : public OpCode {
	public:
		OpLessEquals();
		virtual ~OpLessEquals();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpLessEquals* get( Reader *r, int end, Context *ctx );
		static OpLessEquals* getByName( const char *name );



	protected:

		static int id;

	};

	class OpGreaterThan : public OpCode {
	public:
		OpGreaterThan();
		virtual ~OpGreaterThan();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpGreaterThan* get( Reader *r, int end, Context *ctx );
		static OpGreaterThan* getByName( const char *name );



	protected:

		static int id;

	};

	class OpGreaterEquals : public OpCode {
	public:
		OpGreaterEquals();
		virtual ~OpGreaterEquals();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpGreaterEquals* get( Reader *r, int end, Context *ctx );
		static OpGreaterEquals* getByName( const char *name );



	protected:

		static int id;

	};

	class OpInstanceOf : public OpCode {
	public:
		OpInstanceOf();
		virtual ~OpInstanceOf();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpInstanceOf* get( Reader *r, int end, Context *ctx );
		static OpInstanceOf* getByName( const char *name );



	protected:

		static int id;

	};

	class OpIsType : public OpCode {
	public:
		OpIsType();
		virtual ~OpIsType();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIsType* get( Reader *r, int end, Context *ctx );
		static OpIsType* getByName( const char *name );

		unsigned int getname();
		void setname( unsigned int );


	protected:
		unsigned int name; // u30

		static int id;

	};

	class OpIsTypeLate : public OpCode {
	public:
		OpIsTypeLate();
		virtual ~OpIsTypeLate();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIsTypeLate* get( Reader *r, int end, Context *ctx );
		static OpIsTypeLate* getByName( const char *name );



	protected:

		static int id;

	};

	class OpIn : public OpCode {
	public:
		OpIn();
		virtual ~OpIn();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIn* get( Reader *r, int end, Context *ctx );
		static OpIn* getByName( const char *name );



	protected:

		static int id;

	};

	class OpIncrementI : public OpCode {
	public:
		OpIncrementI();
		virtual ~OpIncrementI();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIncrementI* get( Reader *r, int end, Context *ctx );
		static OpIncrementI* getByName( const char *name );



	protected:

		static int id;

	};

	class OpDecrementI : public OpCode {
	public:
		OpDecrementI();
		virtual ~OpDecrementI();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpDecrementI* get( Reader *r, int end, Context *ctx );
		static OpDecrementI* getByName( const char *name );



	protected:

		static int id;

	};

	class OpIncLocalI : public OpCode {
	public:
		OpIncLocalI();
		virtual ~OpIncLocalI();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpIncLocalI* get( Reader *r, int end, Context *ctx );
		static OpIncLocalI* getByName( const char *name );

		unsigned int getaddress();
		void setaddress( unsigned int );


	protected:
		unsigned int address; // u30

		static int id;

	};

	class OpDecLocalI : public OpCode {
	public:
		OpDecLocalI();
		virtual ~OpDecLocalI();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpDecLocalI* get( Reader *r, int end, Context *ctx );
		static OpDecLocalI* getByName( const char *name );

		unsigned int getaddress();
		void setaddress( unsigned int );


	protected:
		unsigned int address; // u30

		static int id;

	};

	class OpNegateI : public OpCode {
	public:
		OpNegateI();
		virtual ~OpNegateI();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpNegateI* get( Reader *r, int end, Context *ctx );
		static OpNegateI* getByName( const char *name );



	protected:

		static int id;

	};

	class OpAddI : public OpCode {
	public:
		OpAddI();
		virtual ~OpAddI();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpAddI* get( Reader *r, int end, Context *ctx );
		static OpAddI* getByName( const char *name );



	protected:

		static int id;

	};

	class OpSubtractI : public OpCode {
	public:
		OpSubtractI();
		virtual ~OpSubtractI();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpSubtractI* get( Reader *r, int end, Context *ctx );
		static OpSubtractI* getByName( const char *name );



	protected:

		static int id;

	};

	class OpMultiplyI : public OpCode {
	public:
		OpMultiplyI();
		virtual ~OpMultiplyI();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpMultiplyI* get( Reader *r, int end, Context *ctx );
		static OpMultiplyI* getByName( const char *name );



	protected:

		static int id;

	};

	class OpGetLocal0 : public OpCode {
	public:
		OpGetLocal0();
		virtual ~OpGetLocal0();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpGetLocal0* get( Reader *r, int end, Context *ctx );
		static OpGetLocal0* getByName( const char *name );



	protected:

		static int id;

	};

	class OpGetLocal1 : public OpCode {
	public:
		OpGetLocal1();
		virtual ~OpGetLocal1();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpGetLocal1* get( Reader *r, int end, Context *ctx );
		static OpGetLocal1* getByName( const char *name );



	protected:

		static int id;

	};

	class OpGetLocal2 : public OpCode {
	public:
		OpGetLocal2();
		virtual ~OpGetLocal2();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpGetLocal2* get( Reader *r, int end, Context *ctx );
		static OpGetLocal2* getByName( const char *name );



	protected:

		static int id;

	};

	class OpGetLocal3 : public OpCode {
	public:
		OpGetLocal3();
		virtual ~OpGetLocal3();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpGetLocal3* get( Reader *r, int end, Context *ctx );
		static OpGetLocal3* getByName( const char *name );



	protected:

		static int id;

	};

	class OpSetLocal0 : public OpCode {
	public:
		OpSetLocal0();
		virtual ~OpSetLocal0();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpSetLocal0* get( Reader *r, int end, Context *ctx );
		static OpSetLocal0* getByName( const char *name );



	protected:

		static int id;

	};

	class OpSetLocal1 : public OpCode {
	public:
		OpSetLocal1();
		virtual ~OpSetLocal1();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpSetLocal1* get( Reader *r, int end, Context *ctx );
		static OpSetLocal1* getByName( const char *name );



	protected:

		static int id;

	};

	class OpSetLocal2 : public OpCode {
	public:
		OpSetLocal2();
		virtual ~OpSetLocal2();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpSetLocal2* get( Reader *r, int end, Context *ctx );
		static OpSetLocal2* getByName( const char *name );



	protected:

		static int id;

	};

	class OpSetLocal3 : public OpCode {
	public:
		OpSetLocal3();
		virtual ~OpSetLocal3();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpSetLocal3* get( Reader *r, int end, Context *ctx );
		static OpSetLocal3* getByName( const char *name );



	protected:

		static int id;

	};

	class OpDebugReg : public OpCode {
	public:
		OpDebugReg();
		virtual ~OpDebugReg();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpDebugReg* get( Reader *r, int end, Context *ctx );
		static OpDebugReg* getByName( const char *name );

		unsigned char getunknown();
		void setunknown( unsigned char );
		unsigned int getname();
		void setname( unsigned int );
		unsigned int getreg();
		void setreg( unsigned int );
		unsigned int getline();
		void setline( unsigned int );


	protected:
		unsigned char unknown; // byte
		unsigned int name; // u30
		unsigned int reg; // u30
		unsigned int line; // u30

		static int id;

	};

	class OpDebugLine : public OpCode {
	public:
		OpDebugLine();
		virtual ~OpDebugLine();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpDebugLine* get( Reader *r, int end, Context *ctx );
		static OpDebugLine* getByName( const char *name );

		unsigned int getline();
		void setline( unsigned int );


	protected:
		unsigned int line; // u30

		static int id;

	};

	class OpDebugFile : public OpCode {
	public:
		OpDebugFile();
		virtual ~OpDebugFile();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpDebugFile* get( Reader *r, int end, Context *ctx );
		static OpDebugFile* getByName( const char *name );

		unsigned int getfile();
		void setfile( unsigned int );


	protected:
		unsigned int file; // u30

		static int id;

	};

	class OpBkPtLine : public OpCode {
	public:
		OpBkPtLine();
		virtual ~OpBkPtLine();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpBkPtLine* get( Reader *r, int end, Context *ctx );
		static OpBkPtLine* getByName( const char *name );

		unsigned int getline();
		void setline( unsigned int );


	protected:
		unsigned int line; // u30

		static int id;

	};

	class OpTimestamp : public OpCode {
	public:
		OpTimestamp();
		virtual ~OpTimestamp();

		virtual bool parse( Reader *r, int end, Context *ctx );
		virtual void dump( int indent, Context *ctx );
		virtual size_t calcSize( Context *ctx, int start_at );
		//		virtual void write( Writer *w, Context *ctx );
		//		virtual void writeXML( xmlNodePtr xml, Context *ctx );
		//		virtual void parseXML( xmlNodePtr xml, Context *ctx );

		static OpTimestamp* get( Reader *r, int end, Context *ctx );
		static OpTimestamp* getByName( const char *name );



	protected:

		static int id;

	};


}
#endif
