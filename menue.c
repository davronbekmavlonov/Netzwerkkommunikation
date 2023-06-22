#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#define MAX 80
#define PORT 8080
#define BUFFER_SIZE 80
#define SA struct sockaddr

void getServerIP() {
    struct addrinfo hints, *result;
    struct in_addr addr;
    char serverName[255];

    printf("Geben Sie den Namen des Servers ein: ");
    scanf("%s", serverName);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;

    if (getaddrinfo(serverName, NULL, &hints, &result) != 0) {
        printf("Fehler beim Abrufen der IP-Adresse des Servers.\n");
        return;
    }

    addr.s_addr = ((struct sockaddr_in*)(result->ai_addr))->sin_addr.s_addr;
    printf("IP-Adresse des Servers: %s\n", inet_ntoa(addr));

    freeaddrinfo(result);
}

void startServer() {
    int sockfd, client_sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    char buffer[BUFFER_SIZE];

     // Socket erstellen
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Fehler beim Erstellen des Sockets");
        exit(1);
    }

    // Serveradresse einrichten
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Socket an die Serveradresse binden
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Fehler beim Binden des Sockets");
        exit(1);
    }

// Auf eingehende Verbindungen warten
    listen(sockfd, 5);
    printf("Server gestartet. Warte auf Verbindungen...\n");

    // Verbindung akzeptieren
    client_addr_len = sizeof(client_addr);
    client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_sockfd < 0) {
        perror("Fehler beim Akzeptieren der Verbindung");
        exit(1);
    }

     printf("Verbindung hergestellt\n");

    // Daten senden und empfangen
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        printf("Nachricht eingeben: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Nachricht an den Client senden
        if (send(client_sockfd, buffer, strlen(buffer), 0) < 0) {
            perror("Fehler beim Senden der Nachricht");
            exit(1);
        }

        // Verbindung beenden, wenn "exit" eingegeben wird
        if (strncmp(buffer, "exit", 4) == 0)
            break;

        memset(buffer, 0, BUFFER_SIZE);

        // Nachricht vom Client empfangen
        if (recv(client_sockfd, buffer, BUFFER_SIZE, 0) < 0) {
            perror("Fehler beim Empfangen der Nachricht");
            exit(1);

	     }

        printf("Nachricht vom Client: %s", buffer);
    }

    // Verbindung schließen
    close(client_sockfd);
    close(sockfd);
}

void func(int sockfd) 
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}
 


void startClient() {
    char nachricht [255];
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];


    // Socket erstellen
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Fehler beim Erstellen des Sockets");
        exit(1);
    }
    else 
	printf("Socket erfolgreich erstellt.\n");
	bzero(&server_addr, sizeof(server_addr));
	
    
 // Serveradresse einrichten
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    // Verbindung zum Server herstellen
    if (connect(sockfd, (SA*)&server_addr, sizeof(server_addr)) != 0) {
        perror("Fehler beim Herstellen der Verbindung");
        exit(0);
    }
    else 
    
    printf("Verbindung zum Server hergestellt\n");
    printf("Nachricht: ");
    
    // Kommunikation mit Server beginnen
    func(sockfd);
    
    // Socket schliessen
    close(sockfd);
    }
    void funktion_1() {
    printf("Mein Profil.\n");
    getServerIP();
   
}

    void funktion_2() {
    printf("Information zum Server.\n");
    
   
    
}

    void funktion_3() {
    printf("Nachricht senden.\n");
    startClient();
    
}

    void menue_anzeigen() {
    
    printf("Menü:\n");
    printf("1.Mein Profil.\n");
    printf("2.Service Informationen erhalten\n");
    printf("3.Nachricht senden\n");
    printf("4. Beenden\n");
}
    
    int main (int argc, char **argv){
    //void startServer();
    
    int auswahl;
    
        menue_anzeigen();
        printf("Menue: ");
        scanf("%d", &auswahl);

        switch (auswahl) {
            case 1:
                funktion_1();
                break;
            case 2:
                funktion_2();
                break;
            case 3:
                funktion_3();
               
                break;
            case 4:
                printf("Programm wird beendet.\n");
                return 0;
            default:
                printf("Ungültige Auswahl. Bitte versuchen Sie es erneut.\n");
                break;
        }
    
    
    return 0;
    }

    // Daten



