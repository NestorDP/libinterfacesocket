/**
 * @ Copyright 2020
 */

#include "ethernetinterface.hpp" 

sock::EthernetInterface::EthernetInterface () {
    fprintf(stdout, "Starting socket ...\n");
}

sock::EthernetInterface::~EthernetInterface (){
    close(this->sockfd);
    close(this->serverfd);
    printf("\nConnection closed\n\n");
}

void sock::EthernetInterface::create_socket(std::string ip_server, int port, bool protocol){
    this->prtlc = protocol;

    this->remote_addr.sin_family = AF_INET;
    this->remote_addr.sin_port = htons(port);
    this->remote_addr.sin_addr.s_addr = inet_addr(ip_server.c_str());
    memset(this->remote_addr.sin_zero, 0x0, 8);

    if(this->prtlc){
        if ((this->sockfd = socket(AF_INET,  SOCK_STREAM, 0)) == -1) {
            perror("\e[1;31mError on client socket creation:");
            printf("\e[0m");
            exit (EXIT_FAILURE);
        }
        printf("Client socket created with fd: %d\n", this->sockfd);
        
        if (connect(this->sockfd, (struct sockaddr*) &this->remote_addr,
                        sizeof(this->remote_addr)) == -1) {
            perror("\e[1;31mCan't connect to server");
            printf("\e[0m");
            exit (EXIT_FAILURE);
        }
        printf("Connection established with the server\n");
    }
    else{
        // if ((this->  = socket(AF_INET,  SOCK_DGRAM, 0)) == -1) {
        //     perror("\e[1;31mError on client socket creation:");
        //     printf("\e[0m");
        //     exit (EXIT_FAILURE);
        // }
        // printf("Client socket created with fd: %d\n", this->remotefd);
    }
    return;
}

void sock::EthernetInterface::create_socket(int port, bool protocol){
    socklen_t client_len = sizeof(this->remote_addr);

    this->prtlc = protocol;

    this->local_addr.sin_family = AF_INET;
    this->local_addr.sin_port = htons(port);
    this->local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(this->local_addr.sin_zero, 0x0, 8);

    if(this->prtlc){
        if ((this->serverfd = socket(AF_INET,  SOCK_STREAM, 0)) == -1) {
            perror("\e[1;31mError on server socket creation:");
            printf("\e[0m");
            exit(EXIT_FAILURE);
        }
        printf("TCP Server socket created with fd: %d\n", this->serverfd);
        int yes = 1;
        if(setsockopt(this->serverfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("Socket options error:");
            exit(EXIT_FAILURE);
        }
        if(bind(this->serverfd, (struct sockaddr *)&this->local_addr,
                    sizeof(this->local_addr)) == -1 ) {
            perror("Socket bind error:");
            exit(EXIT_FAILURE);
        }
        if(listen(this->serverfd, 2) == -1) {
            perror("Listen error:");
            exit(EXIT_FAILURE);
        }
        fprintf(stdout, "Listening on port %d\n", port);
        if ((this->sockfd = accept(this->serverfd,
                        (struct sockaddr *) &this->remote_addr, &client_len )) == -1) {
            perror("Accept error:");
            exit(EXIT_FAILURE);
        }
    }
    else{
        // if ((this->localfd = socket(AF_INET,  SOCK_DGRAM, 0)) == -1) {
        //     perror("\e[1;31mError on client socket creation:");
        //     printf("\e[0m");
        //     exit (EXIT_FAILURE);
        // }
        // printf("UDP Server socket created with fd: %d\n", this->localfd);

        // if(bind(this->localfd, (struct sockaddr *)&this->local_addr,
        //     sizeof(this->local_addr)) == -1 ) {
        //     perror("Socket bind error:");
        //     exit(EXIT_FAILURE);
        // }
    }
    return;
}

int sock::EthernetInterface::net_send(uint8_t *msg, unsigned int len_buffer, int unsigned len_msg){
    unsigned int num = 0;

    if (this->prtlc){
        for (size_t i = 0; i < len_msg; i = i + len_buffer){
            num = num + send(this->sockfd, msg + i , len_buffer, 0);
        }
    }
    else{
        // for (size_t i = 0; i < len_msg; i = i + len_buffer){
        //     num = num + sendto(localfd, msg + i , len_buffer, 0, 
        //         (const struct sockaddr *) &this->remote_addr, sizeof(remote_addr));
        // }
    }
    
    return num;  
}

int sock::EthernetInterface::net_recv(uint8_t *msg, unsigned int len_buffer, int unsigned len_msg){
    unsigned int num = 0;

    if (this->prtlc) {
        for(int unsigned i = 0; i < len_msg; i = i + len_buffer) {
            num = num + recv(this->sockfd, msg + i, len_buffer, MSG_WAITALL);
        }
    }
    else {
        // for(int unsigned i = 0; i < len_msg; i = i + len_buffer) {
        //     num = num + recvfrom(remotefd, msg + i, len_buffer, 0,
        //     (struct sockaddr *) &this->remote_addr, &len);
        // }
    }

    return num;
}
