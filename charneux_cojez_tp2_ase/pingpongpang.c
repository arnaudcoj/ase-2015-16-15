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
	init_ctx(&ctx_ping, 16384, f_ping, NULL);
	init_ctx(&ctx_pong, 16384, f_pong, NULL);
	init_ctx(&ctx_pang, 16384, f_pang, NULL);
	switch_to_ctx(&ctx_ping);

	exit(EXIT_SUCCESS);
}

void f_ping(void * args){
	int i = 100;	
	while(i--) {
		printf("A");
		switch_to_ctx(&ctx_pong);
		printf("B");
		switch_to_ctx(&ctx_pong);
		printf("C");
		switch_to_ctx(&ctx_pong);
	}
}

void f_pong(void * args){
	while(1) {
		printf("1");
		switch_to_ctx(&ctx_pang);
		printf("2");
		switch_to_ctx(&ctx_pang);
	}
}

void f_pang(void * args){
	while(1) {
		printf("6");
		switch_to_ctx(&ctx_ping);
		printf("7");
		switch_to_ctx(&ctx_ping);
		printf("8");
		switch_to_ctx(&ctx_ping);
		printf("9");
		switch_to_ctx(&ctx_ping);
	}
}
