#include "stdafx.h"

#include "FlashAnalyzer.h"
#include <string>
#include "SWF.h"
#include "SWFFile.h"
#include <fstream>
#include <iostream>
#include<list>
#include "TamarinWrapper.h"
#include "yara.h"
#include <sstream> 
using namespace std;
using namespace SWF;

FlashAnalyzer::FlashAnalyzer()
{
	
}

FlashAnalyzer* FlashAnalyzer::GetAnalyzer() {
	static FlashAnalyzer instance;
	return &instance;
}


FlashAnalyzer::~FlashAnalyzer()
{
}

void FlashAnalyzer::setFeature() 
{


}

void FlashAnalyzer::analyzerFolder(string &flashFolder)
{


}

void FlashAnalyzer::set_label(int label)
{
	m_label = label;
}
int FlashAnalyzer::get_label()
{
	return m_label;
}
void FlashAnalyzer::getFeature(string label,string flashpath, string outpath,string feature_file)
{
	filebuf *pbuf;
	ifstream filestr;
	long size;
	char * buffer;
	string feature = "";
	filestr.open(flashpath, ios::binary);  
	pbuf = filestr.rdbuf();
	// get file size
	size = pbuf->pubseekoff(0, ios::end, ios::in);
	if (size < 0){	
		return;
	}
	pbuf->pubseekpos(0, ios::in);
	buffer = new char[size];
	// get file content 
	pbuf->sgetn(buffer, size);
	filestr.close();	
	const unsigned char* orginData =(const unsigned char*)buffer;	
	AnalyzeFlashInTamarin(orginData, size, flashpath,outpath,label,feature_file);	
	delete[]buffer;
	return ;
}
bool FlashAnalyzer::isSWF( const unsigned char * raw, long length)
{
	if (length >= 3 &&   //min length
		(raw[0] == (char)0x43 || raw[0] == (char)0x46 || raw[0] == (char)0x5a) &&    //C or F or Z
		raw[1] == (char)0x57 &&   //W
		raw[2] == (char)0x53    //S
		)
	{
		return true;
	}
	return false;
}


bool FlashAnalyzer::check_constants_string(File *swfFile, Context *swfContext,string feature_string)
{
	bool isExists = false;
	const unsigned char* fileData = swfFile->getFileData();
	int fileLen = static_cast<int>(swfFile->getFileLength());
	Reader *f_reader = new Reader(fileData, size_t(fileLen));
	Constants f_constants;
	f_constants.parse(f_reader, f_reader->getPosition() + fileLen, swfContext);
	List<String2> *const_string = f_constants.getstrings();
	String2 *item;
	list<string> * constant_string_list = new list<string>;
	ListItem<String2>* i;
	i = const_string->first();
	int a = 0;
	while (i) {
		item = i->data();
		string value = item->getvalue();
		cout << a << " constants_String:" << value << "\n";
		if (value.find(feature_string)!=-1) {
			isExists = true;
			return isExists;
		}
		i = i->next();
		a = a + 1;
	}
	return isExists;
}

void FlashAnalyzer::AnalyzeFlashInTamarin(const unsigned char * swfData,int swfLen, string flashpath,string outpath, string label,string feature_file) {
	//TRACE_FUNCTION;
	string decision;
	bool b_isSWF = this->isSWF(swfData, swfLen);
	//bool is_as3 = false;
	const char* swfData_ = (const char*)swfData;
	if (b_isSWF) {
		
		docode::TamarinWrapper* tamarin_instance = docode::TamarinWrapper::GetInstance();
		if (tamarin_instance) {
			if (!tamarin_instance->IsEnable()) {
				return ;
			}
		}
		else {
			return ;
		}
		int loadSize = tamarin_instance->swfFile.load(swfData_, &tamarin_instance->swfContext, swfLen);
		if (0 == loadSize) {
			cout << "[SWF] Failed to parse swf file.";
			return;
		}
		tamarin_instance->ExecuteSwf((char*)swfData, swfLen, flashpath,outpath,label,feature_file);
		return ;
	}
}

int FlashAnalyzer::callback_function(
	int message,
	void* message_data,
	void* user_data)
{
	cout << "message = " << message << endl;
	if (1 == message)
	{
		YR_RULE* temp = (YR_RULE*)message_data;
		if (temp)
		{
			for (size_t i = 0; i < MAX_THREADS; i++)
			{
				if (temp->strings->matches[i].count > 0)
				{
					struct _YR_MATCH* tempStru = temp->strings->matches[i].head;
					while (tempStru)
					{
						cout << tempStru->data << endl;
						tempStru = tempStru->next;
					}
				}
				else
				{
					break;
				}
			}
		}
		cout << "identifier" << temp->identifier << endl;
		cout << "match success!\n";
	}
	else if (2 == message)
	{
		cout << "no match!\n";
	}
	else if (3 == message)
	{
		cout << "match finish!\n";
	}
	cout << "hello call_back!\n";
	return 0;
}



