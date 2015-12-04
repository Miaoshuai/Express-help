/*======================================================
    > File Name: HttpResponse.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年11月28日 星期六 09时15分06秒
 =======================================================*/

#ifndef MUDUO_NET_HTTPRESPONSE_H
#define MUDUO_NET_HTTPRESPONSE_H

#include <muduo/base/copyable.h>
#include <muduo/base/Types.h>

#include <map>

namespace muduo
{
namespace net
{
    class Buffer;
    class HttpResponse : public muduo::copyable
    {
        public:
            enum HttpStatusCode
            {
                kUnknow,
                k200Ok = 200,               //请求成功，实体的主体部分包含了所请求的资源
                k301MovedPermanently = 301, //资源重定向，响应的Location首部包含了资源现在所处的url
                k404NotFound = 404,         //服务器无法找到所请求的的资源
                k500ServerError = 500,      //服务器出错
            };
            explicit HttpResponse(bool close)
                :statusCode_(kUnknow),
                closeConnection_(close)
            {
            
            }
            //状态码
            void setStatusCode(HttpStatusCode code)
            {
                statusCode_ = code;
            }
            //状态信息
            void setStatusMessage(const string &message)
            {
                statusMessage_ = message;
            }
            //是否关闭连接
            void setCloseConnection(bool on)
            {
                closeConnection_ = on;
            }

            bool closeConnection()const
            {
                return closeConnection_;
            }

            //发给客户端数据类型如html或PNG等
            void setContentType(const string &contentType)
            {
                addHeader("Content-Type",contentType);
            }

            //添加头部内容
            void addHeader(const string &key,const string &value)
            {
                headers_[key] = value;
            }

            //添加发送体内容
            void setBody(const string &body)
            {
                body_ = body;
            }

            void appendToBuffer(Buffer *output)const;

        private:
            std::map<string,string> headers_;//保存头部
            HttpStatusCode statusCode_; //响应状态吗
            string statusMessage_;      //状态码对应的解释
            bool closeConnection_;      //是否关闭连接
            string body_;               //数具体
    }
}
}
