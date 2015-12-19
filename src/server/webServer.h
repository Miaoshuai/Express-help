/*======================================================
    > File Name: httpServer.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月19日 星期六 18时49分06秒
 =======================================================*/
#ifndef WEB_SERVER_
#define WEB_SERVER_

class WebServer
{
    public:
        WebServer();
        ~WebServer();

        void start();
    private:
        char ip_;
        int  port_;
};

#endif
