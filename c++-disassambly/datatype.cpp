#include <stdio.h>
#include <unistd.h>
void int_func() {
    int in = 0x12345678;
}

void float_func() {
    float ft = 1.1;
}

int main(int argc,char* argv[]) {
    int_func();
    float_func();
while(1)
	sleep(10);
    return 0;
}

