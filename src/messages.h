// src/include/messages.h
#ifndef MESSAGES_H
#define MESSAGES_H

#define MAX_TEXT_LENGTH 140
#define SERVER_ID 0

enum MessageType
{
    OI = 0,
    TCHAU = 1,
    MSG = 2
};

// Struct para representar as mensagens
typedef struct
{
    unsigned short int type;
    unsigned short int orig_uid;
    unsigned short int dest_uid;
    unsigned short int text_len;
    unsigned char text[MAX_TEXT_LENGTH + 1];
} msg_t;

#endif