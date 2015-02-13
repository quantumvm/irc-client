#define NICK "phantomsheepbot"
#define CHANNEL "##ufsit"
#define IRC_NETWORK "irc.freenode.net"

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "network.h"


int init_input_thread(int * socket);
void * input_stream(void * socket);
void process_input();

//global socket

int global_socket;

int main(int argc){

    puts("Establishing socket...");
    int socket = get_socket();
    connect_to_socket(socket, IRC_NETWORK, "6667");

    global_socket = socket;

    //Send nick to server
    char nick[] = "NICK "NICK"\n";
    send(socket, nick, strlen(nick), 0);

    //Send user info to server
    char user_info[] = "USER " NICK " " NICK " irc.freenode.net :" NICK "\n";
    send(socket, user_info, strlen(user_info), 0);

    init_input_thread(&socket);

    char input[1024];
    while(1){
        //get input from stdin
        fgets(input, sizeof(input), stdin);

        //remove the trailing newline from fgets
        int slength = strlen(input);
        //if(input[slength-1]=='\n'){
        //    input[slength-1]='\x00';
        //}

        //send input to irc server
        send(socket, input, strlen(input), 0);
    }

}

//Invoked to start recieve thread
int init_input_thread(int * socket){
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, input_stream, socket);
}

//recieves input from buffer
void * input_stream(void * socket){
    char buffer[512];
    while(1){
        readLine(*((int*)socket), buffer, sizeof(buffer));
        process_input(buffer);
    }
}

void process_input(char * buffer){
    char buffer_copy;

    printf("%s",buffer);
}
