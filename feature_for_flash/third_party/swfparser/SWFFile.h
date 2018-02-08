#ifndef SWF_FILE_H
#define SWF_FILE_H

namespace SWF {

class Context;
class Tag;
class Header;
class DoABCContext;

class File {
	public:
		File();
		~File();
		//int load( FILE *fp, Context *ctx = NULL, unsigned int filesize=0 );
		int load( const char *fileData, Context *_ctx, unsigned int fileSize );
		void dump();
		void getDoABC(DoABCContext* doABC);
		
		Tag * getTag( int type );
        int getTagCount( int type);
		void getTags( int type, std::vector<Tag *> & vecTags );

		const unsigned char * getFileData() const;
		uint32_t getFileLength() const;

		std::vector<std::pair<std::string, std::string> > & GetDetections();
        std::string & GetEndContent() {return end_content_;}

		unsigned char* GetFwsData() {return fws_data_;}
		unsigned int GetFwsLen() {return fws_data_len_;}

		bool maybeCVE20070071();
        static bool decompress(  unsigned char *inputBuffer, size_t inLength, unsigned char *outputBuffer, size_t& outLength );
        static bool lzma_decompress(unsigned char *inputBuffer, size_t inLength, unsigned char *outputBuffer, size_t& outLength);
		int getFrameCount();
	protected:
		void compress( unsigned char *data, size_t len, FILE *fp );
		void decompress( unsigned char *data, size_t len, FILE *fp );

	
		Header* swf_header_;
		unsigned char swf_version_;
		
        bool is_uncompressed_;
        std::string end_content_;

	private:
		unsigned char* body_data_;
		uint32_t body_len_;

		unsigned char* fws_data_;
		unsigned int fws_data_len_;
};
	
	
}
#endif
