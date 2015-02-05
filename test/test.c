#include <stdio.h>
#include <stdlib.h>
// #include "mymalloc.h"

int main(){
	char *p;
	char *q;
	size_t s;
	
	printf("size_t:%d\n",sizeof(s));
	p = (char *)malloc(200);
	q = (char *)malloc(150);
	p = "china\n";
	q = "japan\n";
	printf("%s,%s",p,q);
	return 0;
}