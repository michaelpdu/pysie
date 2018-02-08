// FlashML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream> 
#include<string> 
#define NOMINMAX
#include <windows.h> 
#include "FlashAnalyzer.h"
#include "cmdline.h"

using namespace std;

bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   

	return false;    
}
int main(int argc, char *argv[])
{
	cmdline::parser a;
	a.add<string>("label", 'l', "flash label", true, "");
	a.add<string>("path", 'p', "flash path", true, "");
	a.add<string>("outpath", 'o', "output path", true, "");
	a.add<string>("feature", 'f', "feature_file", true, "");
	a.add("help", 0, "print this message");
	a.set_program_name("FlashML");
	a.parse_check(argc, argv);
	FlashAnalyzer* flash_analyzer = FlashAnalyzer::GetAnalyzer();
	
	flash_analyzer->getFeature(a.get<string>("label"),a.get<string>("path"), a.get<string>("outpath"), a.get<string>("feature"));
	
}

