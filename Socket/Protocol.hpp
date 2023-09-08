#pragma once

class CallBack{
    public:
        CallBack()
        {}
        void operator()(int sock)
        {
            HandlerRequest(sock);
        }
        void HandlerRequest(int sock)
        {
            LOG(INFO, "Hander Request Begin");
#ifdef DEBUG
            //For Test
            char buffer[4096];
            recv(sock, buffer, sizeof(buffer), 0);
            std::cout << "-------------begin----------------" << std::endl;
            std::cout << buffer << std::endl;
            std::cout << "-------------end----------------" << std::endl;
#else 
            EndPoint *ep = new EndPoint(sock);
            ep->RecvHttpRequest(); //1. 接收请求
            if(!ep->IsStop()){ //一定要注意逻辑关系
                LOG(INFO, "Recv No Error, Begin Build And Send");
                ep->BuildHttpResponse();//2. 构建响应
                ep->SendHttpResponse(); //3. 发送响应
            }
            delete ep;
#endif
            LOG(INFO, "Hander Request End");
        }
        ~CallBack()
        {}
};
