#include<stdio.h>

int main(){
	
	union{
		short s;
		char c[sizeof(short)];
	
	} un;
	
	un.s = 0x0102;
	if(sizeof(short) == 2){
		if(un.c[0] == 1 && un.c[1] == 2){
			printf("Big-Endian");
		}
		else{
			printf("Little Endian");
		}
	
	}
	else{
		printf("Size of short = %d", sizeof(short));
	}
	
	printf("\n %d", un.s);
	
	return 0;
}
