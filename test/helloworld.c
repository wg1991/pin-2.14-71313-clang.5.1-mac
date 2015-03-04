#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include "mymalloc.h"
int main(){
	char *p;
	char *q;
	size_t s;
	
	printf("size_t:%d\n",sizeof(s));
	p = (char *)mymalloc(200);
	q = (char *)mymalloc(150);
	p = "china\n";
	q = "japan\n";
   int a = &p;
   printf("%p\n",a);
   a = a >> 16;
   printf("%p\n",a);
   a = (a+1) << 16;
   printf("%p\n",a);

//    size_t s;
//    s = 128;
//    int i = s/(64*1024);
//    printf("%d\n",i);
//    char a;
//    a = (char)(log(s)/log(2));
//    printf("%d\n",a);

    // char *p;
    // p = (char*)malloc(1024*1024*1024);
    // printf("%p\n",p);
    // p = (char*)((((unsigned long long)p>>16)+1)<<16);
    // unsigned long long i;
    // i = (unsigned long long)p;
    // i = i>>16;
    // printf("%p,%d\n",i,i);
    // printf("%p\n",p);
    
	return 0;
}


