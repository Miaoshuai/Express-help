/*======================================================
    > File Name: http_request.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月27日 星期日 23时04分53秒
 =======================================================*/
#ifndef HTTP_REQUEST_H_
#define HTTP_REQUEST_H_

#include <string>
#include <map>
#include <assert>

namespace netlib
{
    class HttpRequest
    {
        public:
            enum Method
            {Invalid,Get,Post,Head,Options,Put,Delete};

            //设置方法
            bool setMethod(const char *start,const char *end)
            {
                assert(method_ == Invalid);
                string method(start,end);
                if(method == "GET")
                {
                    method_ = Get;
                }
                else if(method == "POST")
                {
                    method_ = Post;      
                }
                else if(method == "HEAD")
                {
                    method_ = Head;
                }
                else if(method == "PUT")
                {
                    method_ = Put;
                }
                else if(method == "DELETE")
                {
                    method_ = Delete;
                }                

                return method_ != Invalid;
            }

            //获得方法
            Method getMethod(void)
            {
                return method_;
            }

            std::string toStringForMethod(void)
            {
                switch(method_)
                {
                    case Get:
                        return std::string("GET");break;
                    case Post:
                        return std::string("POST");break;
                    case Head:
                        return std::string("HEAD");break;
                    case Options:
                        return std::string("OPTIONS");break;
                    case Put:
                        return std::string("PUT");break;
                    case Delete:
                        return std::string("DELETE");break;
                    default:
                        return NULL;
                }
                return NULL;
            }

            //设置路径
            void setPath(const char *start,const char *end)
            {
                path_.assign(start,end);
            }

            //获取路径
            std::string getPath()
            {
                return path_;
            }

            //设置body
            void setBody(const char *start,const char *end)
            {
                body_.assign(start,end);
            }

            //获取body
            std::string getBody(void)
            {
                return body_;
            }

            //增加请求头内容
            void addHeader(const char *start,const char *colon,const char *end)
            {
                std::string key(start,colon);
                ++colon;
                while(colon < end && isspace(*colon))
                {
                    ++colon;
                }

                std::string value(colon,end);
                while(!value.empty() && isspace(value[value.size() -1]))
                {
                    value.resize(value.size() -1);
                }

                headers_[key] = value;
            }

            //获得某个头部信息
            std::string getHeader(const std::string &key)
            {
                std::map<std::string,std::string>::iterator it = headers_.find(key);
                if(it != headers_.end())
                {
                    return it->second;
                }
                return NULL;   
            }

            //获得头部map
            std::map<std::string,std::string> &headers()
            {
                return headers_;
            }

        private:
            Method method_; //http请求的方法
            std::string path_;//请求路径
            std::string body_;   //请求体
            std::map<std::string,std::string> headers_;
    };
}

#endif
