/*
    Create a TCP socket
*/

#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Winsock Library

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        puts("specify number to send to server");
        return -1;
    }
    int user_input = atoi(argv[1]);

    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char *message, server_reply[2000];
    char *out_buffer = calloc(256, sizeof(char));
    int recv_size;

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");

    // Create a socket
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }

    printf("Socket created.\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

    // Connect to remote server
    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    puts("Connected");

    // Send angle from argument
    printf("user in: %d\n", user_input);
    int converted_in = htonl(user_input);

    int send_status;

    send_status = send(s, &converted_in, sizeof(converted_in), 0);
    if (send_status < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");

    // Receive a reply from the server
    if ((recv_size = recv(s, server_reply, 2000, 0)) == SOCKET_ERROR)
    {
        puts("recv failed");
    }

    puts("Reply received\n");

    puts(server_reply);

    return 0;
}