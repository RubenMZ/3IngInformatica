#include "registro.h"


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
		close(f);
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
		close(f);
		return 0;
	}


	int registrarUsuario(char * nombre, char * pass){
		FILE* f;
		char linea[MSG_SIZE];

		if ((f=fopen("usuarios.txt", "a"))==NULL)
		{
			printf("No se puede abrir el fichero.\n");
			exit(-1);
		}

		fprintf(f, "%s %s\n", nombre, pass);
		close(f);
		return 0;
	}

	char * cifrarPass(char * cadena){
		char ret[MSG_SIZE];
		int i=0;

		for (i = 0; i < strlen(cadena); ++i)
		{
			ret[i]='*';
		}
		ret[i]='\0';

		return ret;
	}

	void continuarRegistro(Usuario usuario){

		if(usuario.estado==0)
            send(usuario.id,"Introduce USUARIO <nombre>", strlen("Introduce USUARIO <nombre>"),0);
        
		if(usuario.estado==1)
            send(usuario.id,"Introduce PASSWORD <pass>", strlen("Introduce PASSWORD <pass>"),0);
        
        if(usuario.estado==2)
            send(usuario.id,"Introduce INICIAR-PARTIDA", strlen("Introduce INICIAR-PARTIDA"),0);
     
     	if(usuario.estado==3)
     		send(usuario.id, "Esperando partida... o partida ya comenzada",
     			strlen("Esperando partida... o partida ya comenzada"),0);   
	}