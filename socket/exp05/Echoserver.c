#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>
#include <arpa/inet.h>
#include<unistd.h>

#define MSG_CONFIRM 0

int main() {

  char buffer[1024] = {0};

  const int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (serverSocket < 0) {
    printf("Socket error\n");
    return 1;
  }

  struct sockaddr_in serverAddress;
  struct sockaddr_in clientAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(9000);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  const int b_val = bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
  if (b_val < 0) {
    printf("binding failed\n");
    return 1;
  }

  int len = sizeof(clientAddress);
  int n = recvfrom(serverSocket, buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr *)&clientAddress, &len);

  buffer[n] = '\0';

  printf("Client: %s\n", buffer);
  long long int nn  = 0;
  int s = sizeof(buffer)/sizeof(buffer[0]);

  
  nn = atoi(buffer);
  long long  ans = 1 ;

  for(int i =  1 ; i <= nn ; i++){
    ans*=i;
  }
  char fact[1024] = {0};
  

  sprintf(fact, "%ld", ans);


  sendto(serverSocket, fact, sizeof(fact), MSG_CONFIRM, (const struct sockaddr *)&clientAddress, len);

  close(serverSocket);

  return 0;
}