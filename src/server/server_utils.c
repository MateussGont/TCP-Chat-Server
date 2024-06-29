
#include "server.h"

int client_sockets[MAX_CLIENTS];
int num_clients = 0;

void add_client(int client_socket)
{
    if (num_clients < MAX_CLIENTS)
    {
        client_sockets[num_clients] = client_socket;
        num_clients++;
    }
    else
    {
        // Lidar com o limite máximo de clientes
        // Por exemplo, recusar a conexão ou desconectar o cliente mais antigo
    }
}

int initialize_server_socket(int port)
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    // Erros
    if (server_socket == -1)
    {
        perror("socket error");
        exit(EXIT_FAILURE);
    }
    if (port < 2)
    {
        printf("PORT NUMBER NOT PROVIDED - PROGRAM TERMINATED\n");
        exit(EXIT_FAILURE);
    }
    // Define atributos do socket
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    // Erros
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    if (listen(server_socket, MAX_CLIENTS) == -1)
    {
        perror("listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    // Retorna o socket
    return server_socket;
}

void accept_connections(int server_socket)
{
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
    if (client_socket == -1)
    {
        perror("accept");
        return;
    }

    if (num_clients < MAX_CLIENTS)
    {
        add_client(client_sockets[num_clients]);
    }
    else
    {
        // Servidor cheio, recuse a conexão
        const char *server_full_message = "Servidor cheio. Tente novamente mais tarde.";
        send(client_socket, server_full_message, strlen(server_full_message), 0);
        close(client_socket);
    }
}

void handle_messages()
{
    char buffer[256]; // msg_t msg
    printf("test\n");
    for (int i = 0; i < num_clients; i++)
    {
        ssize_t bytes_received = recv(client_sockets[i], buffer, sizeof(buffer), 0);
        printf("%s\n", buffer);
        if (bytes_received > 0)
        {

            if (strcmp(buffer, "OI") == 0)
            {
            }
            else if (strcmp(buffer, "TCHAU") == 0)
            {
            }
            else if (strcmp(buffer, "MSG") == 0)
            {
            }
            else
            {
                perror("MENSAGEM NAO ACEITA - TIPO DESCONHECIDO");
            }
        }
    }
}

void send_periodic_message()
{
    const char *periodic_message = "Mensagem periódica";
    if (!num_clients <= 0)
    {
        for (int i = 0; i < num_clients; i++)
        {
            ssize_t bytes_sent = send(client_sockets[i], periodic_message, strlen(periodic_message), 0);
            if (bytes_sent == -1)
            {
                perror("Erro ao enviar mensagem");
            }
        }
    }
    else
    {
        printf("SERVIDOR VAZIO");
    }
}

void error(const char *msg)
{
    perror(msg);
    exit(1);
}