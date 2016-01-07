/* servidor */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
  {
    perror(msg);
    exit(1);
  }

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];

     struct sockaddr_in serv_addr, cli_addr;
     int n;

     if (argc < 2)
       {
         fprintf(stderr,"ERROR, no hay ningun puerto\n");
         exit(1);
       }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);

     if (sockfd < 0) 
        error("ERROR de apertura de socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));

     portno = atoi(argv[1]);

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
              error("ERROR en la conexion");

     listen(sockfd,5);

     clilen = sizeof(cli_addr);

     newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);

     if (newsockfd < 0) 
          error("ERROR en aceptar");

     bzero(buffer,256);
     n = read(newsockfd,buffer,255);

     if (n < 0)
	 error("ERROR al leer del socket");
     
     printf("Aqui esta el mensaje: %s \n",buffer);
     
     n = write(newsockfd,"Tengo el mensaje",18);
     if (n < 0)
	 error("ERROR al escribir en el socket");
     
     close(newsockfd);
     close(sockfd);
     return 0; 
}
