#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdbool.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>

//constanta pentru conversia din bytes in GB
#define MEM_GB 1000 * 1000 * 1000
 
double getTotalMemory();
double getAvailableMemory();
double getCurrentMemoryUsage();

double getTotalDiskSpace();
double getAvailableDiskSpace();
double getCurrentDiskSpace();

#endif