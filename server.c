#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Funktion für die Kommunikation zwischen Client und Server.
void func(int connfd)
{
    char buff[MAX];
    int n;

    // Endlosschleife für die Kommunikation
    for (;;)
    {
        bzero(buff, MAX);

        // Nachricht vom Client lesen und in den Puffer kopieren
        read(connfd, buff, sizeof(buff));

        // Pufferinhalt ausgeben (vom Client empfangene Nachricht)
        printf("Vom Client: %s\n", buff);

        bzero(buff, MAX);
        n = 0;

        // Servernachricht im Puffer speichern
        printf("Antwort an Client: ");
        while ((buff[n++] = getchar()) != '\n')
            ;

        // Pufferinhalt an Client senden
        write(connfd, buff, sizeof(buff));

        // Wenn die Nachricht "exit" enthält, beendet der Server die Kommunikation
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Server beendet...\n");
            break;
        }
    }
}

// Hauptfunktion
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // Socket erstellen
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket konnte nicht erstellt werden...\n");
        exit(0);
    } else {
        printf("Socket erfolgreich erstellt.\n");
    }

    // Setze SO_REUSEADDR Socket-Option
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero(&servaddr, sizeof(servaddr));
    
    // Serveradresse und Port festlegen
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Socket an die Serveradresse binden
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0) {
        printf("Binding fehlgeschlagen...\n");
        exit(0);
    } else {
        printf("Socket erfolgreich gebunden.\n");
    }

    // Socket in den Listenmodus versetzen und auf Verbindungen warten
    if ((listen(sockfd, 5)) != 0)
    {
        printf("Listen fehlgeschlagen...\n");
        exit(0);
    }
    else
        printf("Server hört...\n");

    len = sizeof(cli);

    // Datenpaket vom Client akzeptieren
    connfd = accept(sockfd, (SA *)&cli, (socklen_t *)&len);
    if (connfd < 0)
    {
        printf("Verbindungsaufbau fehlgeschlagen...\n");
        exit(0);
    }
    else
        printf("Server akzeptiert die Verbindung...\n");

    // Funktion für die Kommunikation zwischen Client und Server aufrufen
    func(connfd);

    // Nach der Kommunikation den Socket schließen
    close(sockfd);

    return 0;
}
