#include "iman.h"
#include <netdb.h>
#include <arpa/inet.h>

#define PORT 80

void iman(char* command){

    char* REQUESTL = "GET /?topic=";
    char* REQUESTR = "&section=all HTTP/1.1\r\nHost: man.he.net\r\nUser-Agent: Oswald\r\nConnection: close\r\n\r\n";
    char* REQUEST = (char*)malloc(strlen(command) + strlen(REQUESTL) + strlen(REQUESTR) + 1);
    strcpy(REQUEST, REQUESTL);
    strcat(REQUEST, command);
    strcat(REQUEST, REQUESTR);
        // "GET / HTTP/1.1\r\n"
        // "Host: man.he.net\r\n\n";
        // "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/117.0\r\n"
        // "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\r\n"
        // "Accept-Language: en-US,en;q=0.5\r\n"
        // "Accept-Encoding: gzip, deflate\r\n"
        // "Connection: keep-alive\r\n"
        // "Referer: http://man.he.net/\r\n"
        // "Upgrade-Insecure-Requests: 1\r\n\n";
    
    struct hostent* host;
    host = gethostbyname("man.he.net");
    if (host == NULL) {
        perror("gethostbyname");
        return;
    }

    int skt;
    skt = socket(AF_INET, SOCK_STREAM, 0);
    if (skt == -1){
        perror("socket");
        return;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    memcpy(&server.sin_addr.s_addr, host->h_addr, host->h_length);

    int connection_status = connect(skt, (struct sockaddr*) &server, sizeof(server));

    if (connection_status == -1){
        perror("connect");
        close(skt);
        return;
    }

    int req_stat = send(skt, REQUEST, strlen(REQUEST), 0);
    if (req_stat == -1){
        perror("send");
        close(skt);
        return;
    }

    char buffer[BUFFER];
    int recieved;

    recieved = recv(skt, buffer, sizeof(buffer)-1, 0);

    int check = 0;
    int pos = 0;
    const char name[] = "NAME";
    int start = 0;
    // while (recieved > 0){
    //     buffer[recieved] = '\0';
    //     printf("%s", buffer);
    //     recieved = recv(skt, buffer, sizeof(buffer)-1, 0);
    // }
    while (1){
        for (int i = 0; i < recieved; i++){
            if (buffer[i] == name[pos]){
                pos++;
                if (pos == 1) start = i;
            }
            else pos = 0;
            if (pos == 4) check++;
            if (check == 2) break;
        }
        if (check == 2){
            break;
        }
    }

    while (recieved > 0){
        buffer[recieved] = '\0';
        printf("%s", &buffer[start]);
        recieved = recv(skt, buffer, sizeof(buffer)-1, 0);
        start = 0;
    }

    if (recieved == -1){
        perror("recv");
        return;
    }

    close(skt);

}