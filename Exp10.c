#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

// Define the message structure
struct Message {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    struct Message message;

    // Generate a unique key for the message queue
    key = ftok("msgqueue_example", 65);
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    // Sender: Write a message to the message queue
    message.msg_type = 1; // Message type (can be used for message filtering)
    strcpy(message.msg_text, "Hello, message queue!");
    msgsnd(msgid, &message, sizeof(message), 0);

    printf("Sender: Message sent\n");

    // Receiver: Read a message from the message queue
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Receiver: Received message: %s\n", message.msg_text);

    // Remove the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}

