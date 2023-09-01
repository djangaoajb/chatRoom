#pragma warning(disable:4996)
#include <Ws2tcpip.h> 
#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll


//void dealStr(char *data) {
//    // 更具data处理
//    char* msg = data;
//    if (strcmp(msg, "show") == 0) {
//        //显示聊天室
//    }
//    else if(strncmp(msg, "join") == 0){
//        //加入聊天室
//    }
//    else if (strcmp(msg, "create") == 0) {
//        //创建聊天室
//    }
//    else if (strcmp(msg, "talk") == 0) {
//        //聊天
//    }
//    else if(strcmp(msg,"leave")==0) {
//        //离开聊天
//    }
//
//}

int main() {
    //初始化 DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //创建套接字
    SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    //绑定套接字
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;  //使用IPv4地址
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    sockAddr.sin_port = htons(1234);  //端口
    bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

    //进入监听状态
    listen(servSock, 20);



    // select需要的配置socket信息
    fd_set allsockets;
    FD_ZERO(&allsockets);
    FD_SET(servSock, &allsockets);

    while (true)
    {

        // tmp保存了我们当前连接的信息
        fd_set tmp = allsockets;

        const timeval tval = { 1,0 };
        int ret=select(NULL,&tmp,NULL,NULL, &tval);   //selec模型创建,筛选之后没有了server socket
        if (ret = 0) {
            Sleep(1);
            continue;
        }

        for (int i = 0; i < tmp.fd_count; i++) {
            /*
            几种请求： 1.serverSocket接受请求  2.发送给clntSock请求  
            */

            if (tmp.fd_array[i] == servSock) {
                //接收客户端请求
                SOCKADDR clntAddr;
                int nSize = sizeof(SOCKADDR);
                SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);         
                if (clntSock == SOCKET_ERROR) {
                    printf("tcp握手失败");
                }
                printf("tcp握手成功\n");
                FD_SET(clntSock, &allsockets);
            }
            else {
                // client socket有网络事件，证明客户端发送数据
                    char str[20] = {};
                    int result=recv(tmp.fd_array[i], str, 20, NULL);                 
                    if (result > 0) {                     
                        printf("接受的数据:%s\n", str);
                    }
                    else {
                        FD_CLR(tmp.fd_array[i],&allsockets);
                        // 剔除当前的client socket                      
                        printf("断开连接");
                        break;
                    }
                
            }
        }
    }


   


    while (1);
    //关闭套接字
    //closesocket(clntSock);
    closesocket(servSock);

    //终止 DLL 的使用
    WSACleanup();

    return 0;
}