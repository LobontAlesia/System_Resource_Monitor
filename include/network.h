//aceste functii obtin informatii despre cantitatea totala de date primite si trimise de la interfata de retea a sistemului
//aceste info sunt citite din fisierul /proc/net/dev care contine statistici despre interfetele de retea


unsigned long long getBytesRecieved() {
    FILE *fp;
    char line[1024];

    fp = fopen("/proc/net/dev", "r");
    if (fp == NULL) {
        printf("Error opening /proc/net/dev\n");
        return 0; 
    }

//citeste primele 2 linii cu informatii inutile
    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);

    unsigned long long total_rx_bytes = 0;


//citeste linie cu linie si extrage informatiile necesare
//strtok pentru a descompune cuvintele deparate de : si spatii
//extrage numele interfetei iface si numarul de biti primiti rx_bytes
//adauga rxbytes la totalul de biti primiti
    while (fgets(line, sizeof(line), fp)) {
        char *iface;
        unsigned long long rx_bytes;

        iface = strtok(line, ":");
        iface = strtok(NULL, " ");
        rx_bytes = strtoull(strtok(NULL, " "), NULL, 10);

        total_rx_bytes += rx_bytes;
    }

    fclose(fp);
    return total_rx_bytes;
}

//monitorizam ca si mai sus cantitatea de bytes trimiti
unsigned long long getBytesSent() {
    FILE *fp;
    char line[1024];

    fp = fopen("/proc/net/dev", "r");
    if (fp == NULL) {
        printf("Error opening /proc/net/dev\n");
        return 0; 
    }

    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);

    unsigned long long total_tx_bytes = 0;

    while (fgets(line, sizeof(line), fp)) {
        char *iface;
        unsigned long long tx_bytes;

        iface = strtok(line, ":");
        iface = strtok(NULL, " ");
        tx_bytes = strtoull(strtok(NULL, " "), NULL, 10);

        total_tx_bytes += tx_bytes;
    }

    fclose(fp);
    return total_tx_bytes;
}