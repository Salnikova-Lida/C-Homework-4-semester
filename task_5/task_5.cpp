#include <iostream>
#include <unistd.h>

#include "log.h" 


int main() {
  Log* l = Log::Instance();
  l->message(LOG_NORMAL, "Hi there!"); // won't be printed
  sleep(1);
  l->message(LOG_NORMAL, "I have just logged in");
  sleep(3);
  l->message(LOG_NORMAL, "Can you tell me something interesting about this messanger?");
  sleep(4);
  l->message(LOG_NORMAL, "Yeah, of course!");
  sleep(2);
  l->message(LOG_NORMAL, "There are a lot of interesting funstions");
  sleep(1);
  l->message(LOG_WARNING, "High server load, possible delay in sending");
  sleep(1);
  l->message(LOG_NORMAL, "? what was it?");
  sleep(2);
  l->message(LOG_NORMAL, "Just a usual thing here, this app is very popular");
  sleep(3);
  l->message(LOG_NORMAL, "Why wont they just use more servers?");
  sleep(1);
  l->message(LOG_WARNING, "High server load, possible delay in sending");
  sleep(1);
  l->message(LOG_ERROR, "Out of network");
  Log::Instance()->print();
}