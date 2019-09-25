
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


char html_buf1[]=
"HTTP/1.1 200 OK Date: Sat, 31 Dec 2005 23:59:59 GMT Content-Type: text/html;charset=ISO-8859-1 Content-Length: 135";
char html_buf2[]=
"<!DOCTYPE html><html><head><meta charset=\"utf-8\"><title>01234(runoob.com)</title></head><body><h1>1234</h1><p>4567890</p></body></html>";

#define BUFFSIZE 1024

int main(int argc, char *argv[])
{
	int server_sockfd = 0;
	int client_sockfd = 0;
	int len = 0;
	int sin_size = 0;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	char buf[BUFFSIZE] = {0};

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(1234);

	if((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket error!\n");
		return -1;
	}
	printf("server_socke =%d\n",server_sockfd); 


	int reuse = 1;
	setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));


	if(bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
	{
		perror("bind error!\n");
		return -1;
	}
	printf("bind success\n"); 


	while(1)
	{




		if(listen(server_sockfd, 5) < 0)
		{
			perror("listen error!\n");
			return -1;
		} 
		printf("listen socket %d \n",server_sockfd);
		sin_size= sizeof(struct sockaddr_in);

		if((client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &sin_size)) < 0)
		{
			perror("accept error!\n");
			return -1;
		}
		printf("accept \n");

		//  printf("accept client %s\n",inet_ntoa(client_addr.sin_addr));
		//		len = send(client_sockfd,"123456",6,0);

		while((len = recv(client_sockfd, buf, BUFFSIZE, 0)) >0)
		{
			buf[len] = '\0';

			printf("rec len %d buf = %s\n",len,buf);

			send(client_sockfd,html_buf1,sizeof(html_buf1),0); 
			send(client_sockfd,"\r\n",2,0); 
			send(client_sockfd,html_buf2,sizeof(html_buf2),0); 

			//	if(send(client_sockfd,html_buf,sizeof(html_buf),0) < 0)
			//	{
			//		perror("send error!\n");
			//		return -1;
			//	}
			//	else
			//	{
			//		printf("send SUCCESS:\n");
			//	}
		}


		close(client_sockfd);

	} 
	close(client_sockfd);
	close(server_sockfd);


	return 0;
}



