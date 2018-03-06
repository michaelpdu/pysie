export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

# FIXME Set this variable to disable glibc memory "double free or corruption"
# check. Because the engine will crash on CLogger::~CLogger when destruct
# the global object "gLogger". The ideal solution is to use singleton mode
# for designing CLogger class, which can avoid global object construction/
# destruction problem. Mark Tang 2013/3/8 (Women's Day)
export MALLOC_CHECK_=0

# For SELinux
chcon -t texrel_shlib_t libtmsie.so >/dev/null 2>&1
chcon -t texrel_shlib_t libtmsiecore.so >/dev/null 2>&1
#chcon -t texrel_shlib_t libgsbv1.so >/dev/null 2>&1
#chcon -t texrel_shlib_t muyu.so >/dev/null 2>&1

chmod +x Talos >/dev/null 2>&1

if [ "$(readlink "$0")" = "" ]
    then scriptpath=$(cd "$(dirname "$0")"; pwd)
else
    scriptpath=$(cd "$(dirname "$(readlink "$0")")"; pwd)
fi

$scriptpath/Talos $*
