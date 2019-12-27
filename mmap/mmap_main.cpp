#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
/**
64位的程序虚拟地址从00400000 开始，前面有4MB的gap，堆（malloc,new)分配的内存前面总有16字节的多余分配用于存储前面一个未分配的内存大小（前面8个自己），以及当前chuck的大小（后面八个字节）注意小端

虚拟地址范围     权限   在当前进程的偏移量   主设备：次设备号 inode   映射文件
00400000-00401000 r-xp 00000000 00:50 12888685791                        /Users/nano/projects/skills-linux/mmap/a.out  #可读、可执行权限表示的是a.out的代码段
00600000-00601000 r--p 00000000 00:50 12888685791                        /Users/nano/projects/skills-linux/mmap/a.out  #data 段
00601000-00602000 rw-p 00001000 00:50 12888685791                        /Users/nano/projects/skills-linux/mmap/a.out  #BSS可读可写的权限表示的是a.out的数据段
01266000-01287000 rw-p 00000000 00:00 0                                  [heap]
7fabcfc60000-7fabcfe23000 r-xp 00000000 08:01 2623731                    /usr/lib64/libc-2.17.so
7fabcfe23000-7fabd0022000 ---p 001c3000 08:01 2623731                    /usr/lib64/libc-2.17.so
7fabd0022000-7fabd0026000 r--p 001c2000 08:01 2623731                    /usr/lib64/libc-2.17.so
7fabd0026000-7fabd0028000 rw-p 001c6000 08:01 2623731                    /usr/lib64/libc-2.17.so
7fabd0028000-7fabd002d000 rw-p 00000000 00:00 0
7fabd002d000-7fabd0042000 r-xp 00000000 08:01 2623776                    /usr/lib64/libgcc_s-4.8.5-20150702.so.1
7fabd0042000-7fabd0241000 ---p 00015000 08:01 2623776                    /usr/lib64/libgcc_s-4.8.5-20150702.so.1
7fabd0241000-7fabd0242000 r--p 00014000 08:01 2623776                    /usr/lib64/libgcc_s-4.8.5-20150702.so.1
7fabd0242000-7fabd0243000 rw-p 00015000 08:01 2623776                    /usr/lib64/libgcc_s-4.8.5-20150702.so.1
7fabd0243000-7fabd0344000 r-xp 00000000 08:01 2623839                    /usr/lib64/libm-2.17.so
7fabd0344000-7fabd0543000 ---p 00101000 08:01 2623839                    /usr/lib64/libm-2.17.so
7fabd0543000-7fabd0544000 r--p 00100000 08:01 2623839                    /usr/lib64/libm-2.17.so
7fabd0544000-7fabd0545000 rw-p 00101000 08:01 2623839                    /usr/lib64/libm-2.17.so
7fabd0545000-7fabd062e000 r-xp 00000000 08:01 2623955                    /usr/lib64/libstdc++.so.6.0.19
7fabd062e000-7fabd082d000 ---p 000e9000 08:01 2623955                    /usr/lib64/libstdc++.so.6.0.19
7fabd082d000-7fabd0835000 r--p 000e8000 08:01 2623955                    /usr/lib64/libstdc++.so.6.0.19
7fabd0835000-7fabd0837000 rw-p 000f0000 08:01 2623955                    /usr/lib64/libstdc++.so.6.0.19
7fabd0837000-7fabd084c000 rw-p 00000000 00:00 0
7fabd084c000-7fabd086e000 r-xp 00000000 08:01 2623707                    /usr/lib64/ld-2.17.so
7fabd0a62000-7fabd0a67000 rw-p 00000000 00:00 0
7fabd0a6b000-7fabd0a6d000 rw-p 00000000 00:00 0
7fabd0a6d000-7fabd0a6e000 r--p 00021000 08:01 2623707                    /usr/lib64/ld-2.17.so
7fabd0a6e000-7fabd0a6f000 rw-p 00022000 08:01 2623707                    /usr/lib64/ld-2.17.so
7fabd0a6f000-7fabd0a70000 rw-p 00000000 00:00 0
7fffef468000-7fffef489000 rw-p 00000000 00:00 0                          [stack]
7fffef592000-7fffef594000 r--p 00000000 00:00 0                          [vvar]
7fffef594000-7fffef596000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
*/
int g_test= 0;
int g_test1;
int main(int argc,char* argv[]) {
    int fd = open("test.txt",O_RDONLY);
	static int s_test = 0;
	int *pint = new int;
	printf("%p %p %p %p %p %p heap:%p\n",&argc, &argv,&fd,&g_test,&s_test,&g_test1,pint);
	while(1) {sleep(1);}
    return 0;
    void* addr = mmap(NULL,4096, PROT_READ, MAP_SHARED,fd,0);
    if(addr != MAP_FAILED) {
        while(1) {
        sleep(1);
        }
    } else {
        printf("map failed:%s\n",strerror(errno));
    }
    return 0;
}
