#include "../include/cpu.h"
#include <string.h>  // Am adăugat pentru a include funcția memset
#include <sys/sysinfo.h>  // Am adăugat pentru a include structura sysinfo
#include <time.h>  // Am adăugat pentru a include structura timespec

//stocam informatiile despre timp
struct timespec t;

//functia care returneaza utilizarea totala a cpu ului in procente
double get_overall_cpu_usage() {
    struct sysinfo sysinf;
    memset(&sysinf, 0, sizeof sysinf);
    //obtinem informatii despre sistem
    if (!sysinfo(&sysinf)) {
        //calculam factorul de conversie pentru incarcarea medie a sistemului
        float f_load = 1.f / (1 << SI_LOAD_SHIFT);
        //calculam si returnam utilizarea totala a cpu ului in procente luand in considerare numarul de procesoare
        return sysinf.loads[0] * f_load * 100 / get_nprocs();
    }
    return 0.0;  // Adăugat pentru a evita avertismente de tip
}

int getNumberOfProcessors() {
    return get_nprocs();
}

//returneaza numarul de cicluri de ceas
static inline uint64_t getCycles() {
    unsigned a, d;
    //citim valorile eax si edx care contin numarul de cicluri de ceas
    asm volatile("rdtsc" : "=a" (a), "=d" (d));
    //returnam si construim valoarea pe 64 de biti
    return ((uint64_t)a) | (((uint64_t)d) << 32);
}

//returneaza numarul de milisecunde
static inline uint32_t getMillisecondCounter() {
    //uint32 - numar pe 32 de biti
    uint32_t millisecondCounter;
    //obtinem timpul curent
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t);
    //calculam numarul de milisecunde
    millisecondCounter = (uint32_t)(t.tv_sec * 1000 + t.tv_nsec / 1000000);
    return millisecondCounter;
}

//returneaza viteza de ceas a procesorului
int getClockSpeed() {
    const uint64_t cycles = getCycles();
    const uint32_t millis = getMillisecondCounter();
    int lastResult = 0;

    //bucla infinita de asteptare pt aprox 1 milion de iteratii pt a masura timpul
    for (;;) {
        int n = 1000000;
        while (--n > 0) {}

        const uint32_t milliSecondsElapsed = getMillisecondCounter() - millis;
        const uint64_t cyclesNow = getCycles();

        //verificam daca au trecut cel putin 80 de milisecunde pt a evita calculele in perioade scurte
        if (milliSecondsElapsed > 80) {
            //Calcularea noii viteze a ceasului în kilohertzi.
            const int newResult = (int)(((cyclesNow - cycles) / milliSecondsElapsed) / 1000);

    //verificam daca au trecut cel putin 500 de milisecunde sau daca viteza de ceas este mai mare decat 100
            if (milliSecondsElapsed > 500 || (lastResult == newResult && newResult > 100))
                return newResult;

            lastResult = newResult;
        }
    }
    return lastResult;
}
