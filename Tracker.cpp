// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include<arpa/inet.h>
#include<iostream>

using namespace std;

int main() 
{ 
int arr[1024];
int count=0;
cout<<"\n inside tracker ";
int server_fd, new_socket, valread,n; 

struct sockaddr_in address,cliaddr; 
     socklen_t clilen;

   server_fd = socket(AF_INET, SOCK_STREAM, 0) ;
    if (server_fd < 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       

     address.sin_family = AF_INET; 
    address.sin_addr.s_addr= INADDR_ANY; 
    address.sin_port = htons(9980);  

       
   int addrlen = sizeof(sockaddr);
    if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
 clilen=sizeof(cliaddr);
int sockfd = accept(server_fd,(struct sockaddr *)&cliaddr,&clilen);
    if (sockfd <0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 

  int choice,cno,result;
recv(sockfd,&choice,sizeof(int),0);

if(choice==0)
{
recv(sockfd,&cno,sizeof(int),0);
arr[count] =cno;
count++;
result=1;
send(sockfd,&result,sizeof(int),0);

}
fflush(stdin);
close(sockfd);
close(server_fd);

    return 0; 
}
