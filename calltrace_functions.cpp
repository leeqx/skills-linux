#include <stdio.h>
#include <time.h>
#include <map>
#include <unistd.h>

#define NO_INSTRUMENT_FUNCTION __attribute__((__no_instrument_function__))

std::map<void*,time_t> g_map;
void NO_INSTRUMENT_FUNCTION __cyg_profile_func_enter(void *this_func, void *call_site) {
    fprintf(stdout, "%s-%p, call_site:%p\n",__func__, this_func,call_site);
}
void NO_INSTRUMENT_FUNCTION __cyg_profile_func_exit(void *this_func, void *call_site) {
    time_t end = time(NULL);
   // printf("cost:%d \n",time(NULL) - g_map[this_func]);
}

int test() {
    time_t a =time(NULL);
    printf("test time:%u\n",a);
    //g_map.insert(std::pair<void*,time_t>((void*)test,a));
    sleep(2);
}

int test2() {
    time_t a =time(NULL);
    printf("test2 time:%u\n",a);
    //g_map.insert(std::pair<void*,time_t>((void*)test2,a));
    sleep(2);
}
int main(int argc,char * argv[]) {
    test();
    //test2();
    return 0;
}

//编译：g++ -finstrument-functions -g calltrace_functions.cpp
// --noinstrument-functions-exclude-function-list=test
// --noinstrument-functions-exclude-file-list=test.cpp
