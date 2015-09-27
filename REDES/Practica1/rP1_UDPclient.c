#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define PORT 2000
#define BUFFER_SIZE 50

int main(int argc, char const *argv[]){
  int cd = socket(AF_INET, SOCK_DGRAM, 0);
  if(cd == -1){
    perror("Socket error");
    return -1;
  }

  struct sockaddr_in server;
  socklen_t server_size = sizeof(server);
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  printf("1 - DAY.\n");
  printf("2 - TIME.\n");
  printf("3 - DAYTIME\n");
  printf("Choose: ");
  int choice;
  scanf("%d", &choice);

  char buffer[BUFFER_SIZE];
  switch(choice){
    case 1:
      strcpy(buffer, "DAY");
      break;
    case 2:
      strcpy(buffer, "TIME");
      break;
    case 3:
      strcpy(buffer, "DAYTIME");
      break;
  }

  fd_set readset;
  FD_ZERO(&readset);
  FD_SET(cd, &readset);

  struct timeval timeout;
  timeout.tv_sec = atoi(argv[2]);
  timeout.tv_usec = 0;

  int result = select(cd+1, &readset, NULL, NULL, &timeout);
  if(result == -1){
    perror("Select error\n");
  }else if(result == 0){
    printf("Se ha agotado el tiempo\n");
  }else{
    if(recvfrom(cd, &buffer, sizeof(buffer), 0, (struct sockaddr *) &server, &server_size) > 0){
      printf("Leido %s\n", buffer);
    }else{
      printf("Error al leer del servidor\n");
    }
  }
  close(cd);

  /*int enviado = sendto(cd, &buffer, sizeof(buffer), 0, (struct sockaddr *) &server, server_size);
  if(enviado < 0){
    printf("Error al solicitar el servicio\n");
  }else{
    int recibido = recvfrom(cd, buffer, sizeof(buffer), 0, (struct sockaddr *) &server, &server_size);
    if(recibido > 0){
      printf("%s\n", buffer);
    }
    else{
      printf ("Error al leer del servidor\n");
    }
  }
  close(cd);*/

return 0;
}
