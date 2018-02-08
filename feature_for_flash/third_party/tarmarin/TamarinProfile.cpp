#include "TamarinProfile.h"
#include <string>
namespace docode {

    TamarinProfile::TamarinProfile(char* name) {
        std::string strName = name;
       // profile_ = new tmsa::ProfileUnit(strName);
    }

    TamarinProfile::~TamarinProfile() {
        delete profile_;
    }
}