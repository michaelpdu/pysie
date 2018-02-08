
#include "TamarinStaticAnalyzer.h"
#include <string>
#include <stdio.h>
#include <list>
#include<iostream>

#include <vector>
#include <algorithm>

using namespace std;



namespace docode {

    TamarinStaticAnalyzer* TamarinStaticAnalyzer::instance_ = NULL;
	bool TamarinStaticAnalyzer::initialized = false;

    TamarinStaticAnalyzer* TamarinStaticAnalyzer::GetInstance() {
        if (!instance_) {
            instance_ = new TamarinStaticAnalyzer();
        }
        return instance_;
    }

    bool TamarinStaticAnalyzer::Initialize() {
	
        return true;
    }
    bool TamarinStaticAnalyzer::Finalize() {
        return true;
    }

    bool TamarinStaticAnalyzer::ParsePtnFile() {

       // std::string pattern_path = TMSA_CFG_READ_STRING("pdf_swf_engine", "native_tamarin_ptn_path", 
                              //  "pattern/pdf_swf/native_tamarin.ptn");
        std::string pattern_data;
        //if(!TMSA_GET_PATTERN_DATA(pattern_path, pattern_data)) {
          //  LOG_ERR("Get tamarin ptn file data failed!");
          //  return false;
       // }

       // ptn_file_ = new (std::nothrow) TamarinPtnFile();
        if (NULL == ptn_file_) {
          //  LOG_ERR("new tamarin ptn file failed!");
            return false;
        }

		return true;
    }

    void TamarinStaticAnalyzer::LoadPattern() {
        ParsePtnFile();
    }

    void TamarinStaticAnalyzer::FinalizeInstance() {
        delete instance_;
    }

    TamarinStaticAnalyzer::TamarinStaticAnalyzer() 
        : behavior_node_(NULL), ptn_file_(NULL)
    {
		//feature_map.clear();
		
		Initialize();
    }

    TamarinStaticAnalyzer::~TamarinStaticAnalyzer () {
        behavior_node_ = NULL;
        delete ptn_file_;
        ptn_file_ = NULL;
    }

    void TamarinStaticAnalyzer::SetBehaviorNode(BehaviorNode* node) {
        behavior_node_ = node;
    }

    void TamarinStaticAnalyzer::CheckConstNumber(unsigned int number) {
		if (number > 10000){
			bigint_cout += 1;
		}
        std::string hex_str = BinaryToHexString((unsigned char*)&number, 4);
		if (hex_str.empty()) {
			return;
		}
		string const_str_lower = hex_str;
		transform(const_str_lower.begin(), const_str_lower.end(), const_str_lower.begin(), ::tolower);
		if (constant_number_index_map.size() > 0) {

			for (std::map<int, std::string>::iterator iter = constant_number_index_map.begin(); iter != constant_number_index_map.end(); ++iter) {
				if (const_str_lower == iter->second) {
					feature_map[iter->first] = std::to_string(stoi(feature_map[iter->first]) + 1);
				
				}
			}

		}

    }

    void TamarinStaticAnalyzer::Check_CVE_2014_0498(const std::string& pattern) {
        //TRACE_FUNCTION;
       
    }

    void TamarinStaticAnalyzer::Check_CVE_2014_0499(const std::string& pattern){
        //TRACE_FUNCTION;
 
    }

	bool TamarinStaticAnalyzer::contains_pattern(const uint8_t* code, size_t code_len, std::string pattern) {
		return true;
	}

	void TamarinStaticAnalyzer::Check_CVE_2010_1297(const uint8_t* code, size_t code_len)
	{
		
	}

    void TamarinStaticAnalyzer::CheckConstString(const std::string& const_str) {
        if (const_str.empty()) {
            return;
        }
		string const_str_lower = const_str;
		transform(const_str_lower.begin(), const_str_lower.end(), const_str_lower.begin(), ::tolower);
		if (constant_string_index_map.size() > 0) {
			for (std::map<int, std::string>::iterator iter = constant_string_index_map.begin(); iter != constant_string_index_map.end(); ++iter) {
				if (const_str_lower==iter->second) {
					feature_map[iter->first] = std::to_string(stoi(feature_map[iter->first])+1);
				}
			}

		
		}
		
         
    }

    void TamarinStaticAnalyzer::CheckMethondInfoCount(unsigned int count) {
        
    }

    void TamarinStaticAnalyzer::CheckValidMethondInfoCount(unsigned int count, unsigned int maxlength) {
     
    }

    void TamarinStaticAnalyzer::CheckClassInfoCount(unsigned int count) {	                             
		total_class_info_count_ += count;
    }

    void TamarinStaticAnalyzer::IncorrectSwfFileLen() {
       
    }

    void TamarinStaticAnalyzer::OutPutBehavior(std::string& msg, bool special) {
     
    }

    void TamarinStaticAnalyzer::OutPutAS2BYTECODE(const char *msg, unsigned int length)
    {
        
    }

    void TamarinStaticAnalyzer::BreakOut(std::string& msg) {
        throw msg.c_str();
    }

    int TamarinStaticAnalyzer::GetValidMethodBodyLen() {
        return 0;
    }

    int TamarinStaticAnalyzer::GetNegativeNumberCount() {
		return 0;
    }

    void TamarinStaticAnalyzer::Reset() {
        isAs3_ = false;
        isHasOutputAbcs = false;
        bHasCheckValidMethodInfo = false;
        behavior_node_ = NULL;
        total_class_info_count_ = 0;
        total_valid_method_info_count = 0;
        method_body_max_length = 0;
    }

    bool TamarinStaticAnalyzer::IsAs3File() {
        return isAs3_;
    }

    bool TamarinStaticAnalyzer::HasOutputAbcs() {
        return isHasOutputAbcs;
    }

    void TamarinStaticAnalyzer::SetAs3FileFlag(bool flag) {
        isAs3_ = flag;
    }

    void TamarinStaticAnalyzer::NoAbcInSwf() {
       // LOG_DEBUG("No abc in swf!");
       // std::string& no_abc_behavior = ptn_file_->GetNoAbcInSwfBehavior();
       // OutPutBehavior(no_abc_behavior);
    }

	void TamarinStaticAnalyzer::OutputTotalCount() {
		//if (isAs3_){
	}


	std::string TamarinStaticAnalyzer::BinaryToHexString(unsigned char* binary, unsigned int length) {
		std::string hex_string = "";
		for (unsigned int index = 0; index < length; index++) {
			char digit[3];
			sprintf_s(digit, "%02x", binary[index]);
			//hex_string.append(digit);
			hex_string.insert(hex_string.begin(), digit, digit + 2);
		}
		return hex_string;
	}

	
	void TamarinStaticAnalyzer::setClassName(std::string name) {
	
		m_class_name.push_back(name);
	}
	

}