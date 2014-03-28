#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

 int main(){
	struct sockaddr_in direccion;
	int Descriptor;
	//char MsjSend [50];
	char MsjRecv[50];
	
	Descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (Descriptor <0)
	{	printf ("Error.!");
	 	return -1;
	}
	else
	{
		int puerto;
		printf("Ingrese el puerto: ");
		scanf("%d",&puerto);
		direccion.sin_family = AF_INET;
		direccion.sin_port = htons (puerto);
		direccion.sin_addr.s_addr =htonl(INADDR_ANY);

		int Bind = bind(Descriptor, (struct sockaddr *)&direccion,sizeof (direccion));
		if (Bind<0)
		{
			perror ("Error.!");
			return -1;
		}
		listen (Descriptor, 3);
		
		struct sockaddr_in Cliente;
		int DescripConect;
		socklen_t cliente_largo;
		cliente_largo = sizeof (struct sockaddr_in);

		DescripConect = accept (Descriptor, (struct sockaddr *)&Cliente, &cliente_largo);
		if (DescripConect < 0)
		{
			printf ("Error.!");
			return -1;
		}
		printf("Se Conectó  %d\n", DescripConect);
		
		
		
		
				//printf("Antes: %s",MsjRecv);
				recv(DescripConect,MsjRecv,sizeof(MsjRecv),0); // recibimos lo que nos envia el cliente
				printf("-Cliente: %s ",MsjRecv);
		
			//	printf("\n-Servidor: \t");
			//	scanf("%s",MsjSend);
			//	send(DescripConect, MsjSend, sizeof(MsjSend), 0);
			//	printf("Mensaje enviado.! \n");
			
		
	return 1;
 }
}
