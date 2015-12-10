#include <muduo/net/http/HttpServer.h>
#include <muduo/net/http/HttpRequest.h>
#include <muduo/net/http/HttpResponse.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Logging.h>

#include <iostream>
#include <map>
#include <fcntl.h>
#include <muduo/base/StringPiece.h>
#include "HttpCallback.h"

using namespace muduo;
using namespace muduo::net;

bool benchmark = false;

int main(int argc, char* argv[])
{
  int numThreads = 0;
  if (argc > 1)
  {
    benchmark = true;
    Logger::setLogLevel(Logger::WARN);
    numThreads = atoi(argv[1]);
  }
  EventLoop loop; 
  HttpServer server(&loop, InetAddress(8838),"5643",TcpServer::kReusePort);
  //设置httpcallback
  server.setHttpCallback(httpCallback);
  
  server.setThreadNum(numThreads);
  server.start();
  loop.loop();
}

