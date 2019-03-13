#include <stdio.h>
#include <unistd.h>

#define NO_INSTRUMENT_FUNCTION __attribute__((__no_instrument_function__))


void NO_INSTRUMENT_FUNCTION __cyg_profile_func_enter(void *this_func, void *call_site);
void NO_INSTRUMENT_FUNCTION __cyg_profile_func_exit(void *this_func, void *call_site);
void __cyg_profile_func_enter(void *this_func, void *call_site) {
    fprintf(stdout, "enter:%p: call_site:%p\n", this_func,call_site);
}
void __cyg_profile_func_exit(void *this_func, void *call_site) {
    fprintf(stdout,"exit:%p:call_size:%p\n",this_func, call_site);
}

int test() {
    return 0;
}

int test2() {
    test();
    return 0;
}
int main(int argc,char * argv[]) {
    test2();
    return 0;
}

//编译：g++ -finstrument-functions -g instrument_functions.cpp -rdynamic
// 如果不希望某个函数或者文件插入该代码，则通过以下指令来进行排除
// --noinstrument-functions-exclude-function-list=test
// --noinstrument-functions-exclude-file-list=test.cpp
// ./instrument_functions |awk -F':' '{print $1;print $4}'|xargs -n 1 addr2line -e instrument_functions -s  -f
// output:
// [root@4ff40135c08e skills-linux]# ./a.out |awk -F':' '{print $2;print $4}'|xargs -n 1 addr2line -e a.out -s  -f
// main
// instrument_functions.cpp:24
// ??
// ??:0
// _Z5test2v
// instrument_functions.cpp:20
// main
// instrument_functions.cpp:26
// _Z4testv
// instrument_functions.cpp:16
// _Z5test2v
// instrument_functions.cpp:22
// _Z4testv
// instrument_functions.cpp:16
// _Z5test2v
// instrument_functions.cpp:22
// _Z5test2v
// instrument_functions.cpp:20
// main
// instrument_functions.cpp:26
// main
// instrument_functions.cpp:24
// ??
// ??:0
//
