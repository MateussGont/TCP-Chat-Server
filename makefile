CC = gcc
CFLAGS = -Wall -Wextra -Isrc
LDFLAGS = -lm

# Variáveis de caminho para os arquivos-fonte
FILE_PATH_client = src/client/client.c
FILE_PATH_server = src/server/server.c src/server/server_utils.c

all: server client

server: $(FILE_PATH_server)
	$(CC) $(CFLAGS) -o server $(FILE_PATH_server) $(LDFLAGS)
	./server

client: $(FILE_PATH_client)
	$(CC) $(CFLAGS) -o client $(FILE_PATH_client) $(LDFLAGS)
	./client $(IDENTIFIER)  # Passe o ID como argumento

clean:
	rm -f server client