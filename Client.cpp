#include<bits/stdc++.h>
#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
#include<fstream>
#include <stdlib.h> 
#include<arpa/inet.h>
#include <pthread.h>



using namespace std;
int BUFF_SIZE = 512;
int sockfdclient = 0;
int server_fd=0,sockfd;


void* SendPartition(void* arg)
{

int *chunk = (int *)arg;

 FILE *fp = fopen("input.txt","rb");//check path


	fseek(fp,(*chunk)*512,SEEK_SET);
int sizet = ftell(fp);
rewind(fp);

send(sockfd,&sizet,sizeof(int),0);

char Buffer[BUFF_SIZE];

int n;
while((n=fread(Buffer,sizeof(char),BUFF_SIZE,fp))>0 && sizet >0)
{

send(sockfd,Buffer,n,0);
memset(Buffer,'\0',BUFF_SIZE);
sizet = sizet-n;

}

cout<<"file transfer completed"<<"\n";

fclose(fp);
close(sockfd);
close(server_fd);
pthread_exit(0);



}




void* ServerCall(void* arg)
{
int *pno = (int *)arg;
pthread_t newthread[2];

cout<<"\n inside main server 1";
int new_socket, valread; 
int BUFF_SIZE = 1024;
char buffsz[1024];
    int opt = 1; 
    //int addrlen = sizeof(address); 

struct sockaddr_in address,cliaddr; 
     socklen_t clilen;

   server_fd = socket(AF_INET, SOCK_STREAM, 0) ;
    if (server_fd < 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
 /* if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } */

     address.sin_family = AF_INET; 
    address.sin_addr.s_addr= INADDR_ANY; 
    address.sin_port = htons(*pno); //check here 

       
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
 sockfd = accept(server_fd,(struct sockaddr *)&cliaddr,&clilen);
    if (sockfd <0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 

int chunk1,chunk2;
chunk1 = 0;
chunk2 = 1;

pthread_create(&newthread[0],NULL, SendPartition, &chunk1);
pthread_create(&newthread[1],NULL, SendPartition, &chunk2);
pthread_join(newthread[0], NULL);
pthread_join(newthread[1], NULL);


    //return NULL;

}



void* ReceivePartition(void* arg)
{

int *chunk = (int *)arg;
int n;
FILE *fp = fopen("Anni1.txt","wb");
    char Buffer[512];
    //bzero(Buffer,1024);
int file_size;

recv(sockfdclient,&file_size,sizeof(file_size),0);

while((n=recv(sockfdclient,Buffer,512,0))>0 && file_size>0 )
{
fwrite(Buffer,sizeof(char),n,fp);
memset(Buffer,'\0',1024);
file_size =file_size-n;
}
//bzero(Buffer,10214);//check bufer size

cout<<"\n file received";

fflush(stdin);
fclose(fp);
close(sockfdclient);
pthread_exit(0);


}


void* ClientCall(void* arg)
{

int *pno = (int *)arg;

cout<<"\n inside client ";

int valread,n; 
	

    sockfdclient = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	{ 
		printf("\n Socket creation error \n"); 
                exit(EXIT_FAILURE); 
		//return -1; 
	} 

    struct sockaddr_in serv_addr;

    //bzero((char *) &serv_addr , sizeof(serv_addr));
	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(*pno); 
        serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int status = connect(sockfdclient , (struct sockaddr *) &serv_addr ,sizeof(serv_addr));
	if (status < 0) 
	{ 
		printf("\nConnection Failed \n"); 
             exit(EXIT_FAILURE); 
		//return -1; 
	} 
	
         pthread_t newthread[2];

int chunk1,chunk2;
chunk1 = 0;
chunk2 = 1;

pthread_create(&newthread[0],NULL, ReceivePartition, &chunk1);
pthread_create(&newthread[1],NULL, ReceivePartition, &chunk2);
pthread_join(newthread[0], NULL);
pthread_join(newthread[1], NULL);

      

//return NULL;

}


void* ClientCallt(void* arg)
{

int *n = (int *)arg;
//int n;
//cin>>n;
int pno1 = 9922 , pno2 = 9923;
if(*n==1)
{
pthread_t newthread[2];
pthread_create(&newthread[0],NULL, ClientCall, &pno1);
pthread_create(&newthread[1],NULL, ClientCall, &pno2);
pthread_join(newthread[0], NULL);
pthread_join(newthread[1], NULL);

}

}

int main(int argc , char* argv[])
{
int n,pno,choice,result;

cout<<"\n press 1 to initialise client else press 0 for server ";

cin>>n;
pno = atoi(argv[1]);

if(n==1)
{
cout<<"\n press 1 for login as client and 0 for new registration ";
cin>>choice;

if(choice==0)
{

cout<<"\n enter your unique port no as username ";
	cin>>pno;
	int sockClientRegister = 0, valread; 
	

    sockClientRegister = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

    struct sockaddr_in serv_addr;

    //bzero((char *) &serv_addr , sizeof(serv_addr));
	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(9980); 
        serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int status = connect(sockClientRegister , (struct sockaddr *) &serv_addr ,sizeof(serv_addr));
cout<<"\n"<<status;
	if (status < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	

send(sockClientRegister,&choice,sizeof(int),0);
send(sockClientRegister,&pno,sizeof(int),0);
recv(sockClientRegister,&result,sizeof(int),0);
if(result==1)
cout<<"client recorded"<<"\n";
close(sockfd);
}


}

//cout<<"\n inside main ";

pthread_t newthread[2];
pthread_t threadclient;

pthread_create(&newthread[0],NULL, ServerCall, &pno);
pthread_create(&newthread[1],NULL, ClientCallt, &n);

if(n==1)
pthread_create(&threadclient,NULL, ClientCallt, &n);

pthread_join(newthread[0] , NULL);
pthread_join(newthread[1] , NULL);

return 0;

}
