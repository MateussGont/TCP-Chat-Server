// src/server/server.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h> // Para a primitiva select
#include "server.h"

int main(int argc, char *argv[]) // file name and portnumber
{
    // Inicializa o socket
    int server_socket = initialize_server_socket(PORT); // Defina a porta apropriada
    fd_set read_fds;
    int max_fd = server_socket;

    while (1)
    {
        // Verifica sockets
        FD_ZERO(&read_fds);
        FD_SET(server_socket, &read_fds);

        // printf("test\n");

        int activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
        if (activity == -1)
        {
            perror("select");
        }

        // Verifica se há atividade no socket do servidor
        if (FD_ISSET(server_socket, &read_fds))
        {
            accept_connections(server_socket);
            handle_messages();
            send_periodic_message();
        }
    }

    return 0;
}