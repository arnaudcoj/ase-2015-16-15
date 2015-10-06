#include <stdio.h>
#include <stdlib.h>
#include "switch.h"

struct ctx_s ctx_ping;
struct ctx_s ctx_pong;
struct ctx_s ctx_pang;

void f_ping(void *arg);
void f_pong(void *arg);
void f_pang(void *arg);

int main(void){
	create_ctx(16384, f_ping, NULL);
	create_ctx(16384, f_pong, NULL);
	create_ctx(16384, f_pang, NULL);
        yield();

	exit(EXIT_SUCCESS);
}

void f_ping(void * args){
	int i = 100;	
	while(i--) {
		printf("A");
		yield();
		printf("B");
		yield();
		printf("C");
		yield();
	}
}

void f_pong(void * args){
	while(1) {
		printf("1");
		yield();
		printf("2");
		yield();
	}
}

void f_pang(void * args){
	while(1) {
		printf("6");
		yield();
		printf("7");
		yield();
		printf("8");
		yield();
		printf("9");
		yield();
	}
}
