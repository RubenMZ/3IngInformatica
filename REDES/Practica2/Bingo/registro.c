#include "registro.h"
#include <string.h>


	int aceptaUsuario(char * nombre){
		FILE* f;
		char linea[MSG_SIZE];
		char * nombre2;

		if ((f=fopen("usuarios.txt", "r"))==NULL)
		{
			printf("No se puede abrir el fichero.\n");
			exit(-1);
		}

		while(fgets(linea, MSG_SIZE, f)!=NULL){
			linea[strlen(linea)-1]='\0';
			nombre2 = cortarCadena(linea, MSG_SIZE, ' ');
			if (strcmp(nombre2,nombre)==0)
				return 1;
		}
		fclose(f);
			
		return 0;
	}

	void inicializarUsuario(Usuario *u, int id){
		u->id = id;
        strcpy(u->nombre, "");
        strcpy(u->pass, "");
        u->estado = 0;
        u->partida = -1;
	}

	char * cortarCadena(char * cadena, int n, char c){
		int i=0;
		char * cortada;

		cortada = (char * )malloc(MSG_SIZE*sizeof(char));

		while(i<n && cadena[i]!=c){
			cortada[i]=cadena[i];
			++i;
		}
		return cortada;
	}


	int aceptaPass(char * nombre, char* pass){
		FILE* f;
		char linea[MSG_SIZE];
		char * nombre2;
		char * pass2;

		pass2 = (char * )malloc(MSG_SIZE*sizeof(char));

		if ((f=fopen("usuarios.txt", "r"))==NULL)
		{
			printf("No se puede abrir el fichero.\n");
			exit(-1);
		}

		while(fgets(linea, MSG_SIZE, f)!=NULL){
			linea[strlen(linea)-1]='\0';
			nombre2 = cortarCadena(linea, MSG_SIZE, ' ');
			strncpy(pass2, linea+strlen(nombre2)+1, MSG_SIZE);
			if (strcmp(nombre2,nombre)==0 && strcmp(pass2,pass)==0)
			{
				return 1;
			}
		}
		fclose(f);
		return 0;
	}


	int registrarUsuario(char * nombre, char * pass){
		FILE* f;

		if ((f=fopen("usuarios.txt", "a"))==NULL)
		{
			printf("No se puede abrir el fichero.\n");
			exit(-1);
		}
		if(aceptaUsuario(nombre)==1)
			return 0;
		else
			fprintf(f, "%s %s\n", nombre, pass);
		
		fclose(f);
		return 1;
	}

	int registroComandos(char* argv, Usuario* user)
	{
		char * aux1, *aux2;
		char * str1, *str2;
		char str[MSG_SIZE];
		char c=' ';

		printf("%s\n", argv);

			aux1=cortarCadena(argv, MSG_SIZE, c);
			strncpy(str, argv+strlen(aux1)+1, MSG_SIZE);
			str1=cortarCadena(str, MSG_SIZE,  c);
			strncpy(str, str+strlen(str1)+1, MSG_SIZE);
			aux2=cortarCadena(str, MSG_SIZE,  c);
			strncpy(str, str+strlen(aux2)+1, MSG_SIZE);
			str2=str;

			if (strcmp(aux1,"-u")==0 && strcmp(aux2, "-p")==0)
			{
				strcpy(user->nombre, str1);
				strcpy(user->pass, str2);
			}else{
				if (strcmp(aux1,"-p")==0 && strcmp(aux2,"-u")==0)
				{
					strcpy(user->pass, str1);
					strcpy(user->nombre, str2);

				}else{
					return 0;
				}
			}
		return 1;
	}


	char * cifrarPass(char * cadena){
		char *ret;
		int i=0;

		ret =(char *)malloc(MSG_SIZE*sizeof(char));

		for (i = 0; i < strlen(cadena); ++i)
		{
			ret[i]='*';
		}
		ret[i]='\0';

		return ret;
	}

	void continuarRegistro(Usuario usuario){

		if(usuario.estado==0)
            send(usuario.id,"-ERR. Introduce USUARIO <nombre> o REGISTER -u <nombre> -p <pass>", strlen("-ERR. Introduce USUARIO <nombre> o REGISTER -u <nombre> -p <pass>"),0);
        
		if(usuario.estado==1)
            send(usuario.id,"-ERR. Introduce PASSWORD <pass>", strlen("-ERR. Introduce PASSWORD <pass>"),0);
        
        if(usuario.estado==2)
            send(usuario.id,"Introduce INICIAR-PARTIDA", strlen("Introduce INICIAR-PARTIDA"),0);
     
     	if(usuario.estado==3)
     		send(usuario.id, "Esperando partida... o partida ya comenzada",
     			strlen("Esperando partida... o partida ya comenzada"),0);   
	}

	Usuario buscarUsuario(int id, Usuario usuarios[], int n){
		int i;
		Usuario u;

		for (i = 0; i < n; ++i)
		{
			if (usuarios[i].id==id)
			{
				u=usuarios[i];
			}
		}
		return u;
	}

	int buscarPosicion(int id, Usuario usuarios[], int n){
		int i;
		int pos;

		for (i = 0; i < n; ++i)
		{
			if (usuarios[i].id==id)
			{
				pos=i;
			}
		}
		return pos;
	}

	Partida * buscarPartida(int id, Partida partidas[], int n){
		int i,j;
		Partida * p;

		for (i = 0; i < n; ++i)
		{
			for (j = 0; j < partidas[i].numUsuarios; ++j)
			{
				if (partidas[i].usuarios[j]==id)
				{
					p=&partidas[i];
				}
			}
		}
		return p;
	}