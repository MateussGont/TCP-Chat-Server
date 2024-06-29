#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "messages.h"

#define SERVER_IP "127.0.0.1" // Endereço IP do servidor
#define SERVER_PORT 8080      // Porta do servidor

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Uso: %s <identificador>\n", argv[0]);
        return 1;
    }

    char *identifier = argv[1]; // Identificador passado como argumento 0-9

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        perror("socket");
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0)
    {
        perror("inet_pton");
        close(client_socket);
        return 1;
    }
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("connect");
        close(client_socket);
        return 1;
    }

    // Lógica do  cliente unificado
    msg_t message;
    char id;
    message.orig_uid = identifier;
    printf("Digite: <Mensagem> <ID do Usuário que sera enviada a mensagem> (zero caso seja mensagem geral)"); // Vazio caso seja mensagem para todos no servidor
    sleep(50);
    scanf("%s %s\n", &message.text, &id);
    message.dest_uid = atoi(id);

    while (1)
    {
        printf("\n");
        sleep(50);
        scanf(" %[^\n]", message.text); // Lê a mensagem até a quebra de linha

        // Envia o identificador e a mensagem ao servidor
        char full_message[276]; // Espaço para o identificador + mensagem
        snprintf(full_message, sizeof(full_message), "[%s] %s", identifier, message.text);
        send(client_socket, full_message, strlen(full_message), 0);

        char response[256];
        ssize_t bytes_received = recv(client_socket, response, sizeof(response), 0);
        if (bytes_received > 0)
        {
            printf("Resposta do servidor: %s\n", response);
        }
    }

    close(client_socket);
    return 0;
}