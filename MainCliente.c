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
	char MsjSend [50];
	char MsjRecv[50];

	int puerto;
	printf("Ingrese el puerto: ");
	scanf("%d",&puerto);
	char IP [20];
	printf("Ingrese la IP: ");
	scanf("%s",IP);
	direccion.sin_family = AF_INET;
	direccion.sin_addr.s_addr = inet_addr(IP); //inet_addr: conviere la direccion IP en un long int sin signo.
	direccion.sin_port = htons(puerto);
	
	Descriptor = socket (AF_INET, SOCK_STREAM, 0);
	if (Descriptor <0)
	{
		printf ("Error.!");
	 	return -1;
	 }
	
	int Connect;
	Connect=connect (Descriptor, (struct sockaddr *)&direccion, sizeof (direccion));
	if (Connect <0)
	{
		printf ("Error.!");
	 	return -1;
	}
	printf ("Esta conectado.! \n");
	
	int servicio = fork();
	
	while(servicio > 0)
	{
		if (servicio != 0)
		{
			printf("\n-Cliente: \t");
			scanf("%s",MsjSend);
			send(Descriptor, MsjSend, sizeof(MsjSend), 0);
			printf("Mensaje enviado.!");
		
			recv(Descriptor,MsjRecv,sizeof(MsjRecv),0); // recibimos lo que nos envia el cliente
			printf("\nServidor: :%s",MsjRecv);
		}
	}
	
return 1;

}

