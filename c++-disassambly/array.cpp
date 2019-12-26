#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/*
struct tt {
tt() {
int b = 0x12345678;
}
};
*/
int array(int argc,char* argv[]) {
	int array[2] = {0x12,0x34};
	array[2] =  0x45;
	return 0;
}

