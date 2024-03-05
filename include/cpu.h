#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdbool.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/resource.h>


int getNumberOfProcessors();
static inline uint64_t getCycles();
static inline uint32_t getMillisecondCounter();
int getClockSpeed();
double get_overall_cpu_usage();

#endif