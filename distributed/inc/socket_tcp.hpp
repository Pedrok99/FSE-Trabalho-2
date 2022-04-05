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
#include <gpio.hpp>

using namespace std;

void sendMsg(int sock, char* msg, uint32_t msgsize)
{
   try
      {
      if (send(sock, msg, msgsize, 0) < 0)
      {
        std::cout << "Can't send message." << std::endl;
        close(sock);
        return;
      }
      std::cout << "Message sent." << std::endl;
    } catch(const std::exception& e)
    {
      cout << "Deu ruim pra mandar a msg" << endl;
    }

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
    cout << "ERROR: Não foi possível estabelecer conexão com : "<< ip << ':' << port << endl;
    return -1;
  }
  
  cout << "Conectado com sucesso a: "<< ip << ':' << port << endl;

  return sock;
}

void closeSocket(int sock){
  close(sock);
}

string getMsg(int sock){
  int bufferSize = 1024;
  string recievedString;
  char buf[1024];

  memset(buf, 0, bufferSize);
  cout << "Aguardando próxima mensagem." << endl;
  // wait for a message
  int bytesRecv = recv(sock, buf, bufferSize, 0);
  if (bytesRecv == -1)
  {
      std::cerr << "There was a connection issue." << std::endl;
      return "0=0";
  }
  if (bytesRecv == 0)
  {
      // std::cout << "The client disconnected" << std::endl;
      sleep(1);
      return "0=0";
  }
  // display message
  recievedString = std::string(buf, 0, bytesRecv);
  return recievedString;
  
}

#endif
