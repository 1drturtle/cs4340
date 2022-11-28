/*
    Create a TCP socket
*/

#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib") // Winsock Library

#define HOST "127.0.0.1"
#define PORT 8888

void handler(SOCKET client_sock);

int main(int argc, char *argv[])
{
    printf("--- Connecting ...");

    // library
    WSADATA wsa;
    // client socket
    SOCKET client_sock;
    // server information
    struct sockaddr_in server;

    // Set up connection
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    printf("Library Created");

    // Create a socket
    // socket(AF_INET, SOCK_STREAM, 0)
    // AF_INET -> IPV4
    // SOCK_STREAM -> TCP
    // 0 -> No extra flags
    if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d\n", WSAGetLastError());
    }
    printf("Socket Created");

    // populate server information
    // host is static, and inet_addr converts it to a machine-usable internet address
    server.sin_addr.s_addr = inet_addr(HOST);
    // AF_INET -> IPV4
    server.sin_family = AF_INET;
    // htons -> converts port to network byte order for TCP
    server.sin_port = htons(PORT);

    // Connect to remote server
    if (connect(client_sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("Connection error.");
        return 1;
    }

    printf("Socket Bound\n");

    puts("Connected. Starting program");
    handler(client_sock);

    // make sure we close the socket
    closesocket(client_sock);
    // break down the library
    WSACleanup();
    return 0;
}
void handler(SOCKET client_sock)
{

    // angle that user provides (radian)
    double user_angle;
    // trig type that user provides 1-6 (or 9 to quit)
    int trig_type;
    // result from server (radian)
    double result = 0;

    // trig type (binary, but takes integer)
    // sin:  1  cos: 2  tan: 3
    // asin: 4 acos: 5 atan: 6
    while (1)
    {
        // fetch user arguments
        printf("Enter Radian Angle to Convert > ");
        scanf("%lf", &user_angle);

        printf("Enter Math to perform. Sin=1, Cos=2, Tan=3. (add 3 for inverse, 9 for quit) > ");
        scanf("%d", &trig_type);
        // trig_type is 0 on invalid input
        if (trig_type == 0)
        {
            puts("\nInvalid Angle or Type performed, looping.");
            continue;
        }
        // break if 9
        else if (trig_type == 9)
        {
            puts("Quitting...");
            break;
        }

        // step one: send angle & trig type
        // - Send angle
        if (send(client_sock, (char *)&user_angle, sizeof(user_angle), 0) < 0)
        {
            puts("Server connection broken, quitting.");
            break;
        }
        // - Send type
        if (send(client_sock, (char *)&trig_type, sizeof(trig_type), 0) < 0)
        {
            puts("Server connection broken, quitting.");
            break;
        }
        // step two: receive result as double radians and print
        if (recv(client_sock, (char *)&result, sizeof(result), 0) == SOCKET_ERROR)
        {
            puts("Server connection broken, quitting.");
            break;
        }
        printf("result: %lf rads\n", result);
        // step three: loop! 🔁🔁
        puts("\nAgain!");
    }
}