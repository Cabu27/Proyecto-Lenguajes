#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char usuarios[50];
	char IPs[50];
	int puertos;
	printf("Ingrese el nombre de usuario:\n");
	scanf("%s",usuarios);
	printf("Ingrese la IP:\n");
	scanf("%s",IPs);
	printf("Ingrese el puerto'n");
	scanf("%d",&puertos);
	FILE *archivo;
	archivo = fopen("contactos.txt","a");
	fprintf(archivo,"%s %s %d\n",usuarios,IPs,puertos);
	fclose(archivo);
return 0;
}
