#ifndef MI_USER_H
#define MI_USER_H

#include "config_hardware.h"
#include <hardware.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mi_syscall.h"

int sum(void *ptr);
void init_user(void);

#endif //MI_USER_H
