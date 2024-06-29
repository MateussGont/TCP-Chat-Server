# TCP-Chat-Server

Este projeto é um cliente e servidor de chat em C. Ele utiliza um Makefile para compilar os arquivos-fonte e gerar os binários.

## Compilação e Execução

1. **Compilação**:
   - Certifique-se de ter o GCC instalado.
   - Abra um terminal e navegue até o diretório do projeto.
   - Execute o seguinte comando para compilar o servidor:
     ```bash
     make server
     ```
   - Execute o seguinte comando para compilar o cliente:
     ```bash
     make client IDENTIFIER=<seu_identificador>
     ```
     Substitua `<seu_identificador>` pelo seu ID (0-9).

2. **Execução**:
   - Após a compilação, execute o servidor:
     ```bash
     ./server
     ```
   - Em outro terminal, execute o cliente:
     ```bash
     ./client <seu_identificador>
     ```
     Substitua `<seu_identificador>` pelo mesmo ID usado na compilação.

3. **Envio de Mensagens**:
   - Digite mensagens no cliente e pressione Enter para enviá-las.

## Limpeza

Para remover os binários gerados, execute:
```bash
make clean
```
# Server_Utils.c

## Função `add_client(int client_socket)`
- Adiciona um novo cliente ao array `client_sockets`.
- Se o número de clientes for menor que o limite máximo (`MAX_CLIENTS`), o socket do cliente é adicionado.
- Caso contrário, a função lida com o limite máximo de clientes (por exemplo, recusando a conexão ou desconectando o cliente mais antigo).

## Função `initialize_server_socket(int port)`
- Cria e inicializa um socket do servidor.
- Recebe um número de porta como argumento.
- Configura o socket com os atributos apropriados (família de endereços, endereço IP, porta).
- Trata erros (por exemplo, se o socket não puder ser criado ou se a porta não for válida).

## Função `accept_connections(int server_socket)`
- Aceita conexões de clientes.
- Recebe o socket do servidor como argumento.
- Quando um cliente se conecta, verifica se o número de clientes é menor que o limite máximo.
- Se for, o cliente é adicionado; caso contrário, a conexão é recusada e uma mensagem é enviada ao cliente.

## Função `handle_messages()`
- Lida com mensagens recebidas dos clientes.
- Itera sobre os clientes conectados e recebe mensagens.
- Dependendo do conteúdo da mensagem (por exemplo, "OI", "TCHAU" ou "MSG"), a função pode executar ações específicas.

## Função `send_periodic_message()`
- Envia uma mensagem periódica a todos os clientes conectados.
- Se não houver clientes, imprime "SERVIDOR VAZIO".
- Caso contrário, envia a mensagem para cada cliente.

## Função `error(const char *msg)`
- Trata erros e exibe uma mensagem de erro específica.

