#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>



void error(char *msg)
{
perror(msg);
exit(1);
}
int main(int argc, char *argv[])
{
int sockfd, newsockfd, portno, clilen, num1,num2, opcion;
char buffer[256];
char buffer1[256];
char resultado [256];
char signo [256];
int res =0;
struct sockaddr_in serv_addr, cli_addr;
int n,m,p;
if (argc < 2) {
fprintf(stderr,"ERROR, no se ha ingresado el puerto\n");
exit(1);
}
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0)
error("ERROR opening socket");
bzero((char *) &serv_addr, sizeof(serv_addr));
portno = atoi(argv[1]);
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(portno);
if (bind(sockfd, (struct sockaddr *) &serv_addr,
sizeof(serv_addr)) < 0)
error("ERROR en binding");
listen(sockfd,5);
clilen = sizeof(cli_addr);
newsockfd = accept(sockfd,
(struct sockaddr *) &cli_addr,
&clilen);
if (newsockfd < 0)
error("ERROR en accept");

bzero(buffer,256);
n = read(newsockfd,buffer,255);
if (n < 0) error("ERROR leyendo del socket");
printf("El numero ingresado fue: %s\n",buffer);
n = write(newsockfd,buffer,18);
if (n < 0) error("ERROR escribiendo en el socket");

bzero(buffer1,256);
m = read(newsockfd,buffer1,255);
if (m < 0) error("ERROR leyendo del socket");
printf("El numero ingresado fue: %s\n",buffer1);
m = write(newsockfd,buffer1,18);
if (m < 0) error("ERROR escribiendo en el socket");

bzero(signo,256);
p = read(newsockfd,signo,255);
if (p < 0) error("ERROR leyendo del socket");
opcion=atoi(signo);
if (opcion == 1){
res=atoi(buffer)+atoi(buffer1);
printf("El resultado es: %d\n",res);
sprintf(resultado,"El resultado es: %d",res);
}
if (opcion == 2){
res=atoi(buffer)-atoi(buffer1);
sprintf(resultado,"El resultado es: %d",res); 
printf("El resultado es: %d\n",res);
}
if (opcion == 3){
res=atoi(buffer)*atoi(buffer1);
sprintf(resultado, "El resultado es: %d",res); 
printf("El resultado es: %d\n",res);
}
if (opcion == 4){
res=atoi(buffer)/atoi(buffer1);
sprintf(resultado,"El resultado es: %d",res); 
printf("El resultado es: %d\n",res);
}
p = write(newsockfd,resultado,18);
 


	/*num1=atoi(buffer); 
	num2=atoi(buffer1);
	if (signo=='+')
	res=num1+num2; 
        printf(res,"%d"); 
        if (signo=='-')
	res=num1-num2; 
        printf(res,"%d"); 
        if (signo=='*')
	res=num1+num2; 
        printf(res,"%d"); 
        if (signo=='/')
	{
	res=num1/num2;
	if (num2=0)
	printf("division para 0 imposible.");
	else
	printf(res,"%d");
	}*/

return 0;
}
