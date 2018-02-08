#pragma  once
#include <string>
#include <vector>
#include<fstream>
#include<map>
#include<list>
//#include "StringObject.h"
namespace docode {
    class TamarinPtnFile;
    class BehaviorNode;
    class TamarinStaticAnalyzer {
    public:
        static TamarinStaticAnalyzer* GetInstance();
        bool Initialize();
        bool Finalize();
        void LoadPattern();
        static void FinalizeInstance();
        void Reset();
        void SetBehaviorNode(BehaviorNode* node);
        void CheckConstNumber(unsigned int number);
        void CheckConstString(const std::string& const_str);
        void CheckMethondInfoCount(unsigned int count);
        void CheckValidMethondInfoCount(unsigned int count, unsigned int maxlength);
        void CheckClassInfoCount(unsigned int count);
        void IncorrectSwfFileLen();
        void BreakOut(std::string& msg);
        int GetValidMethodBodyLen();
        int GetNegativeNumberCount();
        void OutPutBehavior(std::string& msg, bool special=false);
        void OutPutAS2BYTECODE(const char *msg, unsigned int length);
        bool IsAs3File();
        bool HasOutputAbcs();
        void SetAs3FileFlag(bool flag);
        void NoAbcInSwf();
        void OutputTotalCount();
		
		void Check_CVE_2010_1297(const uint8_t* code, size_t code_len);
		std::string BinaryToHexString(unsigned char* binary, unsigned int length);
		std::string m_outpath;
	
		std::map<int, std::string>feature_map;
		std::map<int, std::string>constant_number_index_map;
		std::map<int, std::string>constant_string_index_map;
		std::list<std::string> m_feature_string;
		int total_class_info_count_;
		void setClassName(std::string name);
		std::list<std::string > m_class_name;
		bool isdecodefail;
		bool isuncompressfail;
		int bigint_cout;
    private:
        bool ParsePtnFile();
        void Check_CVE_2014_0498(const std::string& pattern);
        void Check_CVE_2014_0499(const std::string& pattern);
		bool contains_pattern(const uint8_t* code, size_t code_len, std::string pattern);
        TamarinStaticAnalyzer();
        ~TamarinStaticAnalyzer();
        bool isAs3_;
        bool isHasOutputAbcs;
        bool bHasCheckValidMethodInfo;
      
        int total_valid_method_info_count;
        unsigned int method_body_max_length;
        TamarinPtnFile* ptn_file_;
        BehaviorNode* behavior_node_;
        static TamarinStaticAnalyzer* instance_;
		static bool initialized;
    };
}