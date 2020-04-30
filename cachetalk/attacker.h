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

#define DEBUG

long tset = 0;

Spy spy;
Trojan trojan;

