/*======================================================
    > File Name: HttpCallback.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月08日 星期二 16时50分43秒
 =======================================================*/
#include <muduo/net/http/HttpRequest.h>
#include <muduo/net/http/HttpResponse.h>
#include <muduo/base/StringPiece.h>

#include <string>
#include <vector>
#include <map>

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

//从字符串中截取配置名字和配置内容
std::pair<std::string,std::string> intercept(const char *str)
{
    int i=0;
    std::pair<std::string,std::string> option;    //保存每行的关键字和其对应的值

    while(1)
    {
        if(str[i] == ' ')
        {
            std::string s1(str,&str[i - 1]);
            option.first = s1;
            std::string s2(&str[i] + 3);
            option.second = s2;
            return option;   
        }
        else
        {
            i++;
        }
    }
}

//从字符串中提取map的key和value
std::pair<std::string,std::string> extract(const char *str)
{
    std::pair<std::string,std::string> value;

    for(int i=0;; i++)
    {
        if(str[i] == ' ')
        {
            std::string s1(str,&str[i - 1]);
            value.first = s1;
            std::string s2(&str[i] + 3);
            value.second = s2;
            return value;
        }
    }
}


//获得MIME的map(将包含文件后缀名和对应MIME类型装载成一个map)
std::map<std::string,std::string> getAllMIME(void)
{
    std::map<std::string,std::string> m;

    FILE *fp = fopen("/home/shreck/html/MIME.txt","r");
    if(!fp)
    {
        printf("打开MIME文件出错\n");
    }

    char buf[1024];
    while(fgets(buf,sizeof(buf),fp) != NULL)
    {
        if(buf[0] == '#')
        {
            continue;
        }
        else
        {
            m.insert(extract(buf));                                        
        }
        bzero(buf,sizeof(buf));
    }
    fclose(fp);
    return m;
}


//根据key在配置文件中获得对应的属性
std::string getMessageFromFile(const std::string &key)
{
    //打开配置文件
    FILE *fp = fopen("/home/shreck/Express_help/express_help.conf","r");
    if(!fp)
    {
        printf("打开配置文件失败!\n");
    }
    char buf[1024];
    std::pair<std::string,std::string> option;
    
    while(fgets(buf,sizeof(buf),fp) != NULL)
    {
        if(buf[0] == '#')
        {
            continue;
        }
        else
        {
            option = intercept(buf);
            if(option.first == key)
            {
                return option.second;
            }       
        }
        bzero(&buf,sizeof(buf));
    }
    fclose(fp);
    return NULL;   
}



//获得客户端要获取的文件的后缀名
std::string getContentType(const std::string path)
{
    std::string key;
    for(int i = 0 ;; i++)   //获得要取资源的后缀名
    {
        if(path[i] == '.')
        {
            std::string t(&path[i],path.size() - i + 1);
            key = t;
        }   
    }
    auto m = getAllMIME();

    auto it = m.find(key);
    if(it == m.end())
    {
        printf("表中没有此后缀名\n");
    }
    else
    {
        return it->second;
    }
}

std::string getFileContent(int fd)
{
    char body[1024*1024*10];
    int ret = read(fd,body,sizeof(body));
    if(ret < 0)
    {
        printf("读文件出错\n");
    }
    close(fd);
    return body;
}

//http服务器回调
void httpCallback(const muduo::net::HttpRequest &req,muduo::net::HttpResponse *resp)
{
    std::string site = getMessageFromFile("webHome");//站点跟目录
    
    //获得要获取文件的描述符
    std::string path(site);
    path = path + req.path().data();
    int fd = open(path.c_str(),O_RDONLY);
    //请求的资源不存在
    if(fd == -1)
        {
        resp->setStatusCode(muduo::net::HttpResponse::k404NotFound);
        resp->setStatusMessage("服务器没有找到您所访问的资源\n");
        resp->setContentType("text/plain");
        resp->addHeader("Server","shreck");
        resp->setCloseConnection(true);
    }
    //请求成功
    else
    {
        resp->setStatusCode(muduo::net::HttpResponse::k200Ok);
        resp->setStatusMessage("OK");
        resp->setContentType(getContentType(req.path().data()).c_str());
        resp->addHeader("Server","shreck");
        resp->setBody(getFileContent(fd).c_str());       
    }    
}
