CC = clang++ -std=c++11
CFLAGS = -Wall -g
LDFLAGS = -lmuduo_net -lmuduo_base -pthread

server: HttpServer_test.o HttpServer.o HttpResponse.o  HttpCallback.o HttpContext.o
	${CC}  HttpServer_test.o HttpServer.o HttpResponse.o  HttpCallback.o HttpContext.o -o server ${LDFLAGS}
HttpServer_test.o:HttpCallback.h
	${CC} ${LDFLAGS}  -c HttpServer_test.cc 
HttpServer.o:HttpServer.h HttpContext.h HttpRequest.h HttpResponse.h
	${CC} ${LDFLAGS} -c HttpServer.cc
HttpResponse.o:HttpResponse.h
	${CC} ${LDFLAGS} -c HttpResponse.cc
HttpCallback.o:
	${CC} ${LDFLAGS} -c HttpCallback.cpp
HttpContext.o:
	${CC} ${LDFLAGS} -c HttpContext.cc
.PHONY:clean	
clean:
	rm *.o server
