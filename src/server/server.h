// src/server/server.h
#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

// Defina constantes, estruturas e outras variáveis globais conforme necessário
#define PORT 8080
#define MAX_CLIENTS 10

// Estrutura para informações do cliente
struct ClientInfo
{
    int socket_fd;
    int id;

    // Outros campos relevantes (por exemplo, identificador único)
};

// Funções específicas do servidor
int initialize_server_socket(int port);
void accept_connections(int server_socket);
void handle_messages();
void send_periodic_message();

#endif // SERVER_H
