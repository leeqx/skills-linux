/**
 * 编译命令:
 * g++ backtrace.cpp -g -rdynamic -o backtrace
 * output:
 * [root@4ff40135c08e skills-linux]# ./backtrace
 * ./backtrace(_Z9function3v+0x26) [0x400853]
 * ./backtrace(_Z9function2v+0x9) [0x4008b4]
 * ./backtrace(_Z9function1v+0x9) [0x4008bf]
 * ./backtrace(main+0x14) [0x4008d5]
 *lib64/libc.so.6(__libc_start_main+0xf5) [0x7f1d5841b445]
 *./backtrace() [0x400769]
 *
 *
 */
#include <execinfo.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void function3() {
    #define SIZE 100
    void* buffer[SIZE];
    int nptrs = 0;
    nptrs = backtrace(buffer,SIZE);

    char** strings = backtrace_symbols(buffer,nptrs);
    if(strings != NULL) {
        for(int i = 0; i < nptrs;i++) {
            printf("%s\n",strings[i]);
        }
    }
}
void function2() {
    function3();
}
void function1() {
    function2();
}
int main(int argc,char* argv[]) {
    function1();
    return 0;
}

