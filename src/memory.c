#include "../include/memory.h"

struct sysinfo info;

struct statvfs stat;

//cantitatea totala de memorie ram a sistemului
//sysinfo e utilizat pentru a obtine info despre sistem si extrage practic totalul de memorie ram din structura sysinfo
// valoarea e apoi convertita in GB
double getTotalMemory() {

    double totalRam;
    
    if(sysinfo(&info) < 0) perror("sysinfo");

    totalRam = (double) info.totalram / (MEM_GB);

    return totalRam;
}

//cantitatea de memorie ram disponibila in gb
double getAvailableMemory() {

    double freeRam;

    if(sysinfo(&info) < 0) perror("sysinfo");

    freeRam  = (double) info.freeram / (MEM_GB);

    return freeRam;
}

//calculeaza cantitatea de memorie ram utilizata la un moment dat
double getCurrentMemoryUsage() {
    //utilizeaza getTotalMemory si getAvailableMemory pentru a calcula cantitatea totala apoi calculam diferenta
    double totalRam, freeRam, ramUsage;

    if(sysinfo(&info) < 0) perror("sysinfo");

    totalRam = getTotalMemory();
    freeRam = getAvailableMemory();
    ramUsage = totalRam - freeRam;

    return ramUsage;
}

//calculeaza cantitatea totala de spatiu pe disc pt un anumit director - root in acest caz
double getTotalDiskSpace() {

    double spaceAvailable, totalSpace, spaceUsed;
    const char *path = "/root";

    if(statvfs(path, &stat) < 0) perror("sysStatvfs");

    totalSpace = (double)(stat.f_frsize * stat.f_blocks) / (MEM_GB);

    return totalSpace;
}

//returneaza cantitatea disponibila de spatiu pe disc in root
double getAvailableDiskSpace() {

    double spaceAvailable, totalSpace, spaceUsed;
    const char *path = "/root";

    if(statvfs(path, &stat) < 0) perror("sysStatvfs");

    spaceAvailable = (double) (stat.f_bsize * stat.f_bavail) / (MEM_GB);

    return spaceAvailable;
}


//---------------------------------------------------------------------------------
// getCurrentDiskSpace(): get current disk space allocated on the system
//
// output:                return spaceUsed
//---------------------------------------------------------------------------------

//calculeaza cantitayea de spatiu pe disc utilizata la un moment dat
double getCurrentDiskSpace() {

    double spaceAvailable, totalSpace, spaceUsed;
    const char *path = "/root";

    if(statvfs(path, &stat) < 0) perror("sysStatvfs");

    totalSpace = (double)(stat.f_frsize * stat.f_blocks) / (MEM_GB);
    spaceAvailable = (double) (stat.f_bsize * stat.f_bavail) / (MEM_GB);
    spaceUsed = totalSpace - spaceAvailable;

    return spaceUsed;
}


//---------------------------------------------------------------------------------