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
	start_sched();
	// le sleep sert a attendre 1 seconde, dans le cas contraire, l'application fini trop vite pour pouvoir réaliser le ping pong
	printf("\ntest retour au main\n");
	exit(EXIT_SUCCESS);
}

void f_ping(void * args){
	int i = 10000;	
	while(i--) {
		printf("A");
		printf("B");
		printf("C");
	}
}

void f_pong(void * args){
	while(1) {
		printf("1");
		printf("2");
	}
}

void f_pang(void * args){
	while(1) {
		printf("6");
		printf("7");
		printf("8");
		printf("9");
	}
}
