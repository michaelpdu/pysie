#pragma  once

namespace tmsa{
    class ProfileUnit;
}
namespace docode {
    class TamarinProfile {
    public:
        TamarinProfile(char* name);
        ~TamarinProfile();
    private:
        tmsa::ProfileUnit* profile_;
    };
}
#ifdef TAMARIN_PROFILE
#define TAMARIN_PROFILE_VAR_NAME(pos) pu##pos
#define TAMARIN_PROFILE_VAR_NAME_LINE TAMARIN_PROFILE_VAR_NAME(__LINE__)
#define TAMARIN_PROFILE_NAME(name) docode::TamarinProfile TAMARIN_PROFILE_VAR_NAME_LINE(name)
#define TAMARIN_PROFILE_FUNCTION  docode::TamarinProfile TAMARIN_PROFILE_VAR_NAME_LINE(__FUNCTION__)
#else
#define TAMARIN_PROFILE_NAME(name) 
#define TAMARIN_PROFILE_FUNCTION
#endif