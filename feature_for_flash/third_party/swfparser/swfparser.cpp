#include "SWFFile.h"
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>

using namespace SWF;

bool quiet = false;
bool verbose = false;
bool dump = true;
bool nonet = false;
const char *swf_encoding = "UTF-8";
const char *internal_stylesheet = NULL;

void usage() {
	fprintf( stderr,
		"   SWF processing tool\n"
		"\n"
		"usage: swfparser <in>\n"
		"\n"
		"<in> is a single SWF file, or 'stdin'\n"
		"\n"
	);
}

int swfparser( int argc, char *argv[] ) {
	const char *infile = NULL, *outfile = "stdout";
	bool success = false;
	FILE *in_fp=0, *out_fp=0;
	bool std_in, std_out;

	File *input = new File();
	unsigned int filesize, size, xmlsize;
	struct stat filestat;
	char sig;
	Context ctx;
	DoABCContext *doABC = new DoABCContext();

	// parse filenames
	if( argc < 1 || argc > 2 ) {
		usage();
		goto fail;
	}
	infile = argv[1];;
	
	// open files
	std_in = !strncmp( infile, "stdin", 5 );
	std_out = !strncmp( outfile, "stdout", 6 );
	in_fp = std_in ? stdin : fopen( infile, "rb" );
	if( !in_fp ) {
		fprintf(stderr,"ERROR: could not open file %s for reading\n", infile?infile:"stdin" );
		goto fail;
	}
	
	if( !quiet ) fprintf(stderr,"Reading from %s\n", infile );
	
	// stat filesize
	filesize = (unsigned int)-1;
	if( !std_in ) {
		stat( infile, &filestat );
	filesize = filestat.st_size;
	}
	
	// setup context
	ctx.debugTrace = verbose;
	ctx.quiet = quiet;

	// setup encoding conversion.
	if (strcmp(swf_encoding, "UTF-8")) {
		ctx.convertEncoding = true;
		ctx.swf_encoding = swf_encoding;
	}

	// treat input as SWF, produce binary ABCContext
	if( (size = input->load( in_fp, &ctx, filesize )) != 0 ) {
		
		input->getDoABC(doABC);
		int len = doABC->getLen();
		unsigned char *temp = doABC->getContext();


		if (temp != NULL && len != 0) {
			printf("doABC->getLen() = %d\n", len);
			printf("doABC->getContext() Start: \n");
			
			FILE *fp;

			fp = fopen("data.dat", "wb");

			if(fp!=NULL) {
				fwrite(temp,sizeof(unsigned char),len,fp);
			} else {
				printf("File Open failed!! \n");
			}

			fclose(fp);
			printf("doABC->getContext() END! \n");
			
		}


//		if( dump ) input->dump();

		out_fp = std_out ? stdout : fopen( outfile, "wb" );
		if( !out_fp ) {
			fprintf(stderr,"ERROR: could not open file %s for writing\n", outfile );
			goto fail;
		}


		success = true;
	}

fail:
	if( in_fp && !std_in ) fclose(in_fp);
	if( out_fp && !std_out ) fclose(out_fp);
	if (input) {
		delete input;
		input = NULL;
	}
	if (doABC) {
		delete doABC;
		doABC = NULL;
	}
	
	return success ? 0 : -1;
}

int main( int argc, char *argv[] ) {
	int retVal = -1;

	retVal = swfparser( argc, &argv[0] );

		
fail:
	return -1;
}

