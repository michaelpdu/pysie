#include "TamarinWrapper.h"
#include "avmshellExport.h"
#include "TamarinStaticAnalyzer.h"
#include<iostream> 
#include<string>
#include "json.h"
#include <fstream>
#include <cassert>
#include <algorithm>
using namespace std;

#define MAX_ELEMENT_COUNT 46394
#define MAX_CLASS_COUNT 12429
#define MAX_BIN_COUNT 921
#define MAX_BIGINT_COUT 22641
#define MAX_FILE_SIZE 90830102
namespace docode {
    TamarinWrapper* TamarinWrapper::instance_ = NULL;
    bool TamarinWrapper::enable_ = false;
    TamarinWrapper* TamarinWrapper::GetInstance() {
        if (NULL == instance_) {
            instance_ = new TamarinWrapper();
        }

        return instance_;
    }

    bool TamarinWrapper::Initialize() {
       // enable_ = TMSA_CFG_READ_BOOL("pdf_swf_engine", "native_tamarin_enable", false);
        return true;
    }

    bool TamarinWrapper::Finalize() {
        return true;
    }

    void TamarinWrapper::FinalizeInstance() {
        delete instance_;
        instance_ = NULL;
    }

    bool TamarinWrapper::IsEnable() {
		return true;
    }
	void split(std::string& s, std::string& delim, std::vector< std::string >* ret)
	{
		size_t last = 0;
		size_t index = s.find_first_of(delim, last);
		if (index != std::string::npos)
		{
			ret->push_back(s.substr(last, index - last));
			last = index + 1;
			//index = s.find_first_of(delim, last);
		}
		if (index - last>0)
		{
			ret->push_back(s.substr(last, index - last));
		}
	}
	bool TamarinWrapper::get_match_strings(string feature_file) {

		string default_feature_file = feature_file;
		
		vector<string> strVec;
		string delim = ":";
		ifstream fin(default_feature_file);
		list<string>feature_string;
		string str;
		while (getline(fin, str))
		{		
			strVec.clear();
			split(str, delim, &strVec);
			if (strVec.size() >= 2) {
				if (stoi(strVec[0]) >10 && stoi(strVec[0]) <=500) {
					constant_number_index_map[stoi(strVec[0])] = strVec[1];
				}
				if (stoi(strVec[0]) > 500) {
					constant_string_index_map[stoi(strVec[0])] = strVec[1];
				}
			
			}

		}
		return true;
	}
	bool TamarinWrapper::isSusName(std::string class_name)
	{
		int len = class_name.length();
		if (len == 0) { return false; }
		int count = 0;
		for (int i = 0; i < len; i++)
		{
			char at = class_name[i];
			if (at == '-' || at == '_' || at == '|' || at == '\\' || at == '#' ||at == '@' ||at=='%'|| at == '\n'|| at == '\r'|| at == '\t' || at == '$' || at == '1'|| at == 'I')
			{
				count += 1;
			}
			else if (isalpha(at) == false && isalnum(at) == false)
			{
				count += 1;
			}
		}
		if (count / float(len) > 0.5)
		{
			return true;
		}
		return false;
	}
	float TamarinWrapper::checkSusClassNameRate(std::list<std::string>m_name, int count) {
		std::list<std::string>::iterator itor ;
		int sus_count = 0;
		if (count == 0) { return 0; }
		for (itor= m_name.begin(); itor!= m_name.end(); itor++)
		{
			std::string class_name = *itor;
			if (isSusName(class_name))sus_count += 1;
		}
		float rate = sus_count / (float)count;
		return rate;
	
	}
    void TamarinWrapper::ExecuteSwf(char* data, int data_len, std::string flashpath,std::string outpath, std::string label,std::string feature_file) {
        TamarinStaticAnalyzer* static_analyzer = TamarinStaticAnalyzer::GetInstance();
        if (!static_analyzer) {
            std::cout<<"tamarin static analyzer is NULL!";
            return;
        }
		bool get_success = get_match_strings(feature_file);
		if (!get_success)return;
		if (constant_number_index_map.size() > 0) {

		for (std::map<int, std::string>::iterator iter = constant_number_index_map.begin(); iter != constant_number_index_map.end(); ++iter) {
	
			static_analyzer->feature_map[iter->first] = "0";
			}

		}
		if (constant_string_index_map.size() > 0) {

			for (std::map<int, std::string>::iterator iter = constant_string_index_map.begin(); iter != constant_string_index_map.end(); ++iter) {
				static_analyzer->feature_map[iter->first] = "0";
			}

		}
		static_analyzer->constant_number_index_map = constant_number_index_map;
		static_analyzer->constant_string_index_map = constant_string_index_map;
		static_analyzer->bigint_cout = 0;    
        try {
            executeShell(data, data_len);
          
       } catch (...) {
           
       }

	   float m_total_class_info_count_ = (float)static_analyzer->total_class_info_count_/MAX_CLASS_COUNT;
	   static_analyzer->feature_map[3] = std::to_string(m_total_class_info_count_);
	   float sus_rate = checkSusClassNameRate(static_analyzer->m_class_name, static_analyzer->total_class_info_count_);
	   static_analyzer->feature_map[5] = std::to_string(sus_rate);
	   static_analyzer->feature_map[6] = std::to_string((float)static_analyzer->bigint_cout/MAX_BIGINT_COUT);
	   bool is_as3 = false;
	   if (swfFile.getTag(72) || swfFile.getTag(82)) {

		   is_as3 = true;
	   }
	   if (static_analyzer->isdecodefail == true) {
		   ofstream   ofresult("decodefail.txt ", ios::app);
		   ofresult << outpath<<endl;
	   }
	   if (static_analyzer->isuncompressfail == true) {
		   ofstream   ofresult("uncompressfail.txt ", ios::app);
		   ofresult << outpath<<endl;
	   }
	   dumpjsonfile(static_analyzer->feature_map, flashpath,outpath,label);
       return;
    }

    TamarinWrapper::TamarinWrapper() : isLastExecuteAs3_(false), isHasOutputABCs(false) {

    }

    bool TamarinWrapper::IsLastExecuteAs3() {
        return isLastExecuteAs3_;
    }


		

	void TamarinWrapper::dumpjsonfile(std::map<int, std::string> feature_map, std::string flashpath,std::string outpath, std::string label) {

		Json::Value root;
		Json::FastWriter writer;
		Json::Value json_p;
		std::ofstream ofs;
		std::string json_file;
		const unsigned char* fileData = swfFile.getFileData();
		int fileLen = static_cast<int>(swfFile.getFileLength());
		if (NULL == fileData || fileLen <= 0) {
			return;
		}
		
		int defineshape_count = swfFile.getTagCount(0x02) + swfFile.getTagCount(0x16) + swfFile.getTagCount(0x20) + swfFile.getTagCount(0x53);
		int definesprite_count = swfFile.getTagCount(0x27);
		int definetext_count = swfFile.getTagCount(0x25)+ swfFile.getTagCount(0xB);
		int definebits_count = swfFile.getTagCount(0x24) + swfFile.getTagCount(0x6) + swfFile.getTagCount(0x23);
		int definevideo_count = swfFile.getTagCount(0x3C);
		int definesound_count= swfFile.getTagCount(0xE);
		int definefont_count = swfFile.getTagCount(0x4B);
		int defineplace_count = swfFile.getTagCount(0x1A);
		int definebutton_count = swfFile.getTagCount(0x22);
		int definemorphshape_count = swfFile.getTagCount(0x2E);
		int frame_count = swfFile.getFrameCount();
		int Element_cout = defineshape_count + definesprite_count + definetext_count + definebits_count + definevideo_count + definesound_count + definefont_count + defineplace_count + definebutton_count + definemorphshape_count+ frame_count;
		int binarydata_count= swfFile.getTagCount(0x57);
		float f_fileLen = (float)fileLen/ MAX_FILE_SIZE;
		feature_map[1] = std::to_string(f_fileLen);
		float f_Element_cout = (float)Element_cout/MAX_ELEMENT_COUNT;
		feature_map[2] = std::to_string(f_Element_cout);
		float f_binarydata_count = (float)binarydata_count/MAX_BIN_COUNT;
		feature_map[4] = std::to_string(f_binarydata_count);
		
		for (std::map<int, std::string>::iterator iter = feature_map.begin();iter != feature_map.end();++iter) {
			json_p[std::to_string(iter->first)] = iter->second;
		}	
		json_p["flash_file_path"] = flashpath;
		json_p["flash_label"] = label;
		root.append(json_p);
		ofs.open(outpath);

		json_file = writer.write(root);
		assert(ofs.is_open());
		ofs << root.toStyledString();
	}

}
