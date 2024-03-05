#include "../include/cpu.h"
#include "../include/memory.h"
#include "../include/io.h"
#include "../include/network.h"
#include "../include/ip.h"
#include "../include/bandwith.h"

#include <ncurses.h>
#include <string.h>  // Am adăugat pentru a include funcția memset
#include <sys/sysinfo.h>  // Am adăugat pentru a include structura sysinfo


int main(int argc, const char* argv[]) {
    double cpuUsage = 0.0;
    unsigned long long receivedBytes = 0.0; 
    unsigned long long sentBytes = 0.0;
    int cpuCores = 0;
    int cpuSpeed = 0;
    int nrIO = 0;
    double cpuSpeedGHz = 0;
    double freeRam, currentRamUsage, totalRam, freeDiskSpace, totalDiskSpace, currentDiskSpace,
           currentRamUsagePercent, currentDiskUsagePercent;
    char barOut[1024];
    int ramPercentBar = 0;
    int cpuPercentBar = 0;
    int diskPercentBar = 0;

    initscr();
    curs_set(0);

    //verificam daca terminalul suporta culori
    if (has_colors() == FALSE) {
        endwin();
        printf("Terminal does not support colors\n");
        exit(1);
    }

//   initializam perechile de culori 
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_BLACK, COLOR_BLACK);

//bucla infinita pentru a actualiza continuu informatiile
    while (1) {
        cpuCores = getNumberOfProcessors();
        nrIO = numberOfIODevices();
        sentBytes = getBytesSent();
        cpuUsage = get_overall_cpu_usage();
        cpuSpeed = getClockSpeed();
        cpuSpeedGHz = (double)cpuSpeed / 1000.0;
        freeRam = getAvailableMemory();
        totalRam = getTotalMemory();
        currentRamUsage = getCurrentMemoryUsage();
        freeDiskSpace = getAvailableDiskSpace();
        totalDiskSpace = getTotalDiskSpace();
        currentDiskSpace = getCurrentDiskSpace();
        currentRamUsagePercent = (currentRamUsage / totalRam) * 100.0; //inmultesc cu 100 pt a obtine procentul
        currentDiskUsagePercent = (currentDiskSpace / totalDiskSpace) * 100.0;
        ramPercentBar = currentRamUsagePercent / 5; //impart la 5 pentru a le putea reprezenta in bara de progres
        cpuPercentBar = cpuUsage / 5;
        diskPercentBar = currentDiskUsagePercent / 5;

        attron(COLOR_PAIR(6));
        for (int i = 0; i < 14; i++) {
            for (int j = 0; j < 57; j++) {
                mvprintw(i, j, " ");
            }
        }
        attron(COLOR_PAIR(1));
        mvprintw(2, 4, "         Resource Monitor - Alesia Lobont");
        getIP();
        getBandwidth();
        for (int i = 1; i < 59; i++) {
            mvprintw(0, i, "#");
            mvprintw(4, i, "#");
            mvprintw(16, i, "#");
            mvprintw(24, i, "#");
        }
        for (int i = 0; i < 25; i++) {
            mvprintw(i, 1, "#");
            mvprintw(i, 58, "#");
        }

        attron(COLOR_PAIR(1));
        mvprintw(6, 4, "CPU Cores: ");
        attron(COLOR_PAIR(2));
        mvprintw(6, 16, "%d", cpuCores);

        attron(COLOR_PAIR(1));
        mvprintw(7, 4, "CPU Speed: ");
        attron(COLOR_PAIR(2));
        mvprintw(7, 16, "%0.3f GHz", cpuSpeedGHz);

        attron(COLOR_PAIR(1));
        mvprintw(8, 4, "CPU Usage: ");
        mvprintw(8, 16, "[");
        mvprintw(8, 39, "]");
        attron(COLOR_PAIR(2));
        mvprintw(8, 41, "%0.2f%% ", cpuUsage);
        for (int i = 0; i < cpuPercentBar; i++) {
            strcat(barOut, "|");
        }
        mvprintw(8, 17, "%s", barOut);

        attron(COLOR_PAIR(1));
        mvprintw(9, 4, "RAM Usage:  [");
        for (int i = 0; i < ramPercentBar; i++) {
            strcat(barOut, "|");
        }
        if (ramPercentBar < 10)
            attron(COLOR_PAIR(4));
        else if (ramPercentBar >= 10 && ramPercentBar < 16)
            attron(COLOR_PAIR(2));
        else if (ramPercentBar >= 16)
            attron(COLOR_PAIR(3));
        mvprintw(9, 17, "%s", barOut);
        attron(COLOR_PAIR(1));
        mvprintw(9, 39, "]");
        currentRamUsagePercent > 80.0 ? attron(COLOR_PAIR(3)) : attron(COLOR_PAIR(2));
        mvprintw(9, 40, " %0.2f GB  %0.2f%%", currentRamUsage, currentRamUsagePercent);
        memset(barOut, 0, strlen(barOut));

        attron(COLOR_PAIR(1));
        mvprintw(10, 4, "RAM Available: ");
        attron(COLOR_PAIR(2));
        mvprintw(10, 20, "%0.2f GB", freeRam);

        attron(COLOR_PAIR(1));
        mvprintw(11, 4, "Total RAM: ");
        attron(COLOR_PAIR(2));
        mvprintw(11, 16, "%0.2f GB", totalRam);
        attron(COLOR_PAIR(1));

        attron(COLOR_PAIR(1));
        mvprintw(12, 4, "Disk Usage: [");
        for (int i = 0; i < diskPercentBar; i++) {
            strcat(barOut, "|");
        }
        if (diskPercentBar < 10)
            attron(COLOR_PAIR(4));
        else if (diskPercentBar >= 10 && ramPercentBar < 16)
            attron(COLOR_PAIR(2));
        else if (diskPercentBar >= 16)
            attron(COLOR_PAIR(3));
        mvprintw(12, 17, "%s", barOut);
        attron(COLOR_PAIR(1));
        mvprintw(12, 39, "]");
        currentDiskUsagePercent > 80.0 ? attron(COLOR_PAIR(3)) : attron(COLOR_PAIR(2));
        mvprintw(12, 41, " %0.2f GB  %0.2f%%", currentDiskSpace, currentDiskUsagePercent);
        memset(barOut, 0, strlen(barOut));

        attron(COLOR_PAIR(1));
        mvprintw(13, 4, "Available Space: ");
        attron(COLOR_PAIR(2));
        mvprintw(13, 22, "%0.2f GB", freeDiskSpace);

        attron(COLOR_PAIR(1));
        mvprintw(14, 4, "Total Disk Space: ");
        attron(COLOR_PAIR(2));
        mvprintw(14, 23, "%0.2f GB", totalDiskSpace);

        attron(COLOR_PAIR(1));
        mvprintw(18, 4, "Number of IO Devices: ");
        attron(COLOR_PAIR(2));
        mvprintw(18, 28, "%d", nrIO);

        refresh();
        sleep(1);
    }

    return 0;
}
