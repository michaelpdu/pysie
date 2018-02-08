#pragma once
#include<string>
#include "SWF.h"
#include "SWFFile.h"
#include <map>
using std::string;

class FlashAnalyzer
{
public:		
	static FlashAnalyzer *GetAnalyzer();
	void setFeature();
	void analyzerFolder(string& flashFolder);
	bool isSWF(const unsigned char * raw, long length);
	~FlashAnalyzer();
	void set_label(int label);
	int get_label();
	void getFeature(string label,string flashpath, string outpath,string feature_file);
	bool check_constants_string(SWF::File *swfFile, SWF::Context *swfContext ,string feature_string);
	std::map<int, string>feature_match_strings;
	void AnalyzeFlashInTamarin(const unsigned char * swfData, int swfLen, string flashpath,string outpath, string label,string feature_file);
	static int callback_function(int message, void* message_data, void* user_data);
private:
	FlashAnalyzer();
	int m_label;
};

