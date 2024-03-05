#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

//functie  destinată să afișeze informații despre traficul de rețea 
void getBandwidth() {
    //caractere de control pentru a muta cursorul in terminal
    printf("\033[23;4H"); 
    unsigned long long int rx_bytes, tx_bytes;
    char line[200], interface_name[20];
    //deschidem fisierul /proc/net/dev pentru a obtine informatii despre traficul de retea
    FILE* net_dev = fopen("/proc/net/dev", "r");

    while (fgets(line, sizeof(line), net_dev)) {
        if (strstr(line, ":")) {
            // extrage informații despre interfață, inclusiv numele interfeței, cantitatea de bytes primiți și cantitatea de bytes trimiși.
            sscanf(line, "%[^:]: %llu %*u %*u %*u %*u %*u %*u %*u %llu", interface_name, &rx_bytes, &tx_bytes);
            printf("\033[23;4H\033[2k"); // Clear the line and move cursor to the beginning of the line
            printf(" Received: %llu  Transmitted: %llu", rx_bytes/1000, tx_bytes/1000); //Afișarea informațiilor despre traficul de rețea. Cantitățile de bytes sunt afișate în kilobyți, de unde și împărțirea la 1000.
            fflush(stdout); // golim bufferul
            sleep(1); // asteptam 1 secunda pt a actualiza informatiile
        }
    }

    fclose(net_dev);
}


