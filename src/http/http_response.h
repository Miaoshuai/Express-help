/*======================================================
    > File Name: http_response.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月28日 星期一 12时41分53秒
 =======================================================*/
#ifndef HTTP_RESPONSE_H_
#define HTTP_RESPONSE_H_

#include <stdio.h>
#include <map>
#include <string>
#include "buffer.h"

namespace netlib
{
    class HttpResponse
    {
        public:
            enum HttpStatusCode
            {
                Unknown,
                200Ok = 200,
                301MovedPermanently = 301,
                400BadRequest = 400,
                404NotFound = 404,
            };
            HttpResponse(bool close)
                :statusCode_(Unknown),
                isCloseConnection_(close)
            {
            }

            //设置状态码
            void setStatusCode(HttpStatusCode code)
            {
                statusCode_ = code;
            }

            //设置status的说明
            void setStatusMessage(const std::string &message)
            {
                statusMessage_ = message;
            }

            //设置是否关闭
            void setCloseConnection(bool on)
            {
                isCloseConnection_ = on;
            }

            //返回close状态
            bool getCloseConnection()
            {
                return isCloseConnection_;
            }

            //设置内容类型
            void setContentType(const std::string &contentType)
            {
                addHeader("Content-Type",contentType);
            }

            //增加某条头部
            void addHeader(const std::string &key,const std::string &value)
            {
                headers_[key] = value;
            }

            void setFd(int fd)
            {
                fd_ = fd;
            }

            void appendToBuffer(Buffer *output);
        private:
            std::map<std::string,std::string> headers_;
            HttpStatusCode statusCode_;
            std::string statusMessage_;
            bool isCloseConnection_;
            int fd_;        
    };
}

#endif
