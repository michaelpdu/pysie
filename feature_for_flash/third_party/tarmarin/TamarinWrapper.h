#pragma  once
#include<string>
#include<map>
#include"SWF.h"
#include"SWFFile.h"
#include<list>
namespace docode {
    class TamarinWrapper {
    public:
        static TamarinWrapper* GetInstance();
        static bool Initialize();
        static bool Finalize();
        static void FinalizeInstance();
        void ExecuteSwf(char* data, int data_len, std::string flashpath,std::string outpath, std::string label,std::string feature_file);
        bool IsEnable();
        bool IsLastExecuteAs3();
        bool IsHasOutputAbcs() {return isHasOutputABCs;}
		void dumpjsonfile(std::map<int, std::string>, std::string flashpath,std::string outpath, std::string label);
		SWF::File swfFile;
		SWF::Context swfContext;
		bool get_match_strings(std::string feature_file);
		std::map<int, std::string>constant_number_index_map;
		std::map<int, std::string>constant_string_index_map;
		std::list<std::string> m_feature_string;
		//std::map<std::string, std::string>feature_map_result;
		float checkSusClassNameRate(std::list<std::string>m_name, int count);
		bool isSusName(std::string);
    private:
        TamarinWrapper();
        bool isLastExecuteAs3_;
        bool isHasOutputABCs;
        static TamarinWrapper* instance_;
        static bool enable_;
    };

}
