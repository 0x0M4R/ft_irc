// #include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
//create and open a socket to connect to
int main(int ac,char **av)
{
    (void)av;
    int sockfd, newsockfd, portno;
    // (void)newsockfd;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    int n;
    if (ac < 2) {
        std::cout << "ERROR, no port provided" <<std::endl;
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
       std::cout << "ERROR opening socket" << std::endl;
       exit(1);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    int temp_i;
    std::istringstream o(av[1]);
    if (o >> temp_i && o.eof() && !o.fail())
        portno = temp_i;
    else 
    {
        std::cout << "Invalid port number!" << std::endl;
        exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "ERROR on binding" << std::endl;
        exit(1);
    }
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, 
                (struct sockaddr *) &cli_addr, 
                &clilen);
    if (newsockfd < 0)
    {
        std::cout << "ERROR on accept" << std::endl;
        exit(1);
    }
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0) 
    {
        std::cout << "ERROR reading from socket" << std::endl;
        exit(1);
    }
    printf("Here is the message: %s\n",buffer);
    n = write(newsockfd,"I got your message",18);
    if (n < 0) 
    {
        std::cout << "ERROR writing to socket" << std::endl;
        exit(1);
    }
    close(newsockfd);
    close(sockfd);
    return 0; 
}