#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h> 

//functie folosita pentru a obtine adresa IP si numele hostului
void getIP() {
    char hostbuffer[256];
    int hostname;
    //structura folosita pentru a obtine adresa IP
    struct addrinfo hints, *res;

    //functie folosita pentru a obtine numele hostului
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    //verificam daca functia gethostname a fost executata cu succes
    if (hostname == -1) {
        perror("gethostname");
        exit(1);
    }
    //afisam numele hostului
    printf("\033[21;20HHostname: %s", hostbuffer);

    //functie folosita pentru a obtine adresa IP
    memset(&hints, 0, sizeof(hints));
    // Se specifică familia de adrese IP pe care să o utilizeze, în acest caz, IPv4.
    hints.ai_family = AF_INET;
    // Se specifică tipul de socket, în acest caz, un socket de tipul TCP (SOCK_STREAM).
    hints.ai_socktype = SOCK_STREAM;
    //Se setează flagul pentru a obține informații potrivite pentru utilizarea unui socket pasiv.
    hints.ai_flags = AI_PASSIVE;

    //obtinem informatii despre adresa IP
    if (getaddrinfo(hostbuffer, "http", &hints, &res) != 0) {
        perror("getaddrinfo");
        exit(1);
    }

    char ip[INET_ADDRSTRLEN];
    //convertim adresa ip binara in adresa ip text
    inet_ntop(AF_INET, &((struct sockaddr_in *)res->ai_addr)->sin_addr, ip, INET_ADDRSTRLEN);
    printf("\033[21;5HIP: %s", ip);
    
    //eliberam memoria
    freeaddrinfo(res);
}
