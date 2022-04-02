#ifndef __socket_tpc__
#define  __socket_tpc__

#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <time.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>

using namespace std;

void sendMsg(int sock, char* msg, uint32_t msgsize)
{
    if (send(sock, msg, msgsize, 0) < 0)
    {
      std::cout << "Can't send message." << std::endl;
      close(sock);
      exit(1);
    }
    std::cout << "Message sent." << std::endl;
    return;
}

int initSocket(std::string ip, int port){
  int sock;
  struct sockaddr_in server_address;

  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  inet_pton(AF_INET, ip.c_str(), &server_address.sin_addr);
  server_address.sin_port = htons(port);

  if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    cout << "ERROR: Socket creation failed" << endl;
    return -1;
  }

  if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
    cout << "ERROR: Unable to connect to server" << endl;
    return -1;
  }
  
  cout << "Connected to: "<< ip << endl;

  return sock;
}

void closeSocket(int sock){
  close(sock);
}

#endif