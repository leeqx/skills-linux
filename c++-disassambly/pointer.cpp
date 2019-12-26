#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int pointer() {
	char* p = (char*)malloc(1);
	*p ='c'; 
	return 0;
}

