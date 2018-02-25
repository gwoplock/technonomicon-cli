#include "net.h"


int main(){
   int socket = openTechServer();
   techListen(socket);
}