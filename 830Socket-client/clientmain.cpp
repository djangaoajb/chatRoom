#pragma warning(disable:4996)
#include <Ws2tcpip.h> 
#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll


//void dealMsg(char *d) {
//    char* msg = d;
//    if (strcmp(msg, "show")) {
//        //展示聊天室
//    }
//    else if (strcmp(msg, "join")) {
//        //join聊天室
//    }
//    else if (strcmp(msg, "create")) {
//        //create聊天室
//    }
//    else if (strcmp(msg, "talk")) {
//        //聊天
//    }
//    else if (strcmp(msg, "leave")) {
//        //离开
//    }
//    else {
//        printf("输入错误");
//    }
//
//}

int main() {
    //初始化 DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //客户端套接字
    SOCKET CliSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    //绑定客户端套接字
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;  //使用IPv4地址
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    sockAddr.sin_port = htons(1234);  //端口



    // 建立连接
    if (connect(CliSock, (sockaddr*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR) {
        printf("tcp连接失败");
        closesocket(CliSock);
    }

    printf("与服务器建立成功\n");


    while (true)
    {
        //向服务端发数据
        printf("请输入向服务端发送的数据\n");
        char buff[20];
        scanf("%s", buff);
        // 判断指令-》发什么消息类型
        //dealMsg(buff);

        if (send(CliSock, buff, 20, 0) < 0) {
            printf("发送失败\n");
        }
    }


    while (1);
    //关闭套接字
    closesocket(CliSock);
    WSACleanup();

    return 0;
}