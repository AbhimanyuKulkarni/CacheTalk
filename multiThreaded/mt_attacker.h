#include <stdio.h>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "spy.h"
#include "trojan.h"
#ifndef _COMMON_H
#include "common.h"
#endif
using namespace std;

long tset = 0;

void *spy_wrapper(void *arg);
void *trojan_wrapper(void *arg);
