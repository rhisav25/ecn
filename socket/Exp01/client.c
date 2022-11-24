#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
 
int main(){
 
  char *ip = "127.0.0.1";
  int port = 5566;
 
  int soc;
  struct sockaddr_in addr;
  socklen_t addr_size;
  char buffer[1024];
  int n;
 
  soc = socket(AF_INET, SOCK_STREAM, 0);
  if (soc < 0){
    perror("Socket error !, Couldn't Create TCP Scoket");
    exit(1);
  }
  printf("TCP  Socket Created Succesfully.\n");
 
  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = port;
  addr.sin_addr.s_addr = inet_addr(ip);
  while(1){ 
  connect(soc, (struct sockaddr*)&addr, sizeof(addr));
  printf("Connected to the Server Succesfully !.\n");
 
  bzero(buffer, 1024);
  char str[20];
  scanf("%[^\n]%*c", str);
  //strcpy(buffer, "Hello , from the Client Side !.");
  strcpy(buffer, str);
  printf("Client: %s\n", buffer);
  send(soc, buffer, strlen(buffer), 0);
 
  bzero(buffer, 1024);
  recv(soc, buffer, sizeof(buffer), 0);
  printf("Server: %s\n", buffer); }
 
  close(soc);
  printf("Succesfully Disconnected from the Server.\n");
 
  return 0;
}