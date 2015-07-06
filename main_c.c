/* 
 * File:   main_c.c
 * Author: dominik
 *
 * Created on 6 lipiec 2015, 09:27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 1501
#define ADDRESS "127.0.0.1"

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server;
    char message[128], server_reply[2000];

    //Create socket
    if (sock = socket(AF_INET, SOCK_STREAM, 0) == -1) {
        perror("socket");
        return EXIT_FAILURE;
    }

    //Prepare structure sockaddr_in
    server.sin_family = AF_INET; // rodzaj gniazda z ktorego kozysta TCP/IP
    server.sin_port = htons(PORT); // numer portu
    server.sin_addr.s_addr = inet_addr(ADDRESS);

    //Connect to remote server
    if (connect(sock, (struct sockaddr *) &server, sizeof (server)) < 0) {
        perror("connect");
        return EXIT_FAILURE;
    }
    
    //keep communicating with server
    while (1) {
        printf("Enter message : ");
        scanf("%s", message);

        //Send some data
        if (send(sock, message, strlen(message), 0) < 0) {
            puts("Send failed");
            return 1;
        }

        //Receive a reply from the server
        if (recv(sock, server_reply, 2000, 0) < 0) {
            puts("recv failed");
            break;
        }

        puts("Server reply :");
        puts(server_reply);
    }

    close(sock);
    return (EXIT_SUCCESS);
}