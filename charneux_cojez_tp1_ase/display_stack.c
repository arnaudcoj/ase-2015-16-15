#include <stdio.h>
#include <stdlib.h>

void q1 (int param1, int param2);
void f1 (int param1, int param2);
void f2 (int param1, int param2);

int main (void) {
  q1(32, 67);
  return 0;
}

void q1 (int param1, int param2) {
  unsigned int var_esp = 0;
  unsigned int var_ebp = 0;

  asm ("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
       : "=r"(var_esp),"=r"(var_ebp)
       :
       :);

  printf("esp = %u\nebp = %u\n", var_esp, var_ebp);
  printf("&var_esp = %u\n&var_ebp = %u\n", &var_esp, &var_ebp);
  printf("&param1 = %u\n&param2 = %u\n", &param1, &param2);

  f1(12, 42);
  
  return;
}

void f1 (int param1, int param2) {
  unsigned int var_esp = 0;
  unsigned int var_ebp = 0;
  
  asm ("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
       :"=r"(var_esp),"=r"(var_ebp)
       :
       :);

  printf("\tesp = %u\n\tebp = %u\n", var_esp, var_ebp);
  printf("\t&var_esp = %u\n\t&var_ebp = %u\n", &var_esp, &var_ebp);
  printf("\t&param1 = %u\n\t&param2 = %u\n", &param1, &param2);

  f2(64, 3);

  return ;
}

void f2 (int param1, int param2) {

  unsigned int var_esp = 0;
  unsigned int var_ebp = 0;
  
  asm ("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
       : "=r"(var_esp),"=r"(var_ebp)
       :
       :);

  printf("\t\tesp = %u\n\t\tebp = %u\n", var_esp, var_ebp);
  printf("\t\t&var_esp = %u\n\t\t&var_ebp = %u\n", &var_esp, &var_ebp);
  printf("\t\t&param1 = %u\n\t\t&param2 = %u\n", &param1, &param2);

  return ;
}
