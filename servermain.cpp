#pragma warning(disable:4996)
#include <Ws2tcpip.h> 
#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll


//void dealStr(char *data) {
//    // ����data����
//    char* msg = data;
//    if (strcmp(msg, "show") == 0) {
//        //��ʾ������
//    }
//    else if(strncmp(msg, "join") == 0){
//        //����������
//    }
//    else if (strcmp(msg, "create") == 0) {
//        //����������
//    }
//    else if (strcmp(msg, "talk") == 0) {
//        //����
//    }
//    else if(strcmp(msg,"leave")==0) {
//        //�뿪����
//    }
//
//}

int main() {
    //��ʼ�� DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //�����׽���
    SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    //���׽���
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
    sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //�����IP��ַ
    sockAddr.sin_port = htons(1234);  //�˿�
    bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

    //�������״̬
    listen(servSock, 20);



    // select��Ҫ������socket��Ϣ
    fd_set allsockets;
    FD_ZERO(&allsockets);
    FD_SET(servSock, &allsockets);

    while (true)
    {

        // tmp���������ǵ�ǰ���ӵ���Ϣ
        fd_set tmp = allsockets;

        const timeval tval = { 1,0 };
        int ret=select(NULL,&tmp,NULL,NULL, &tval);   //selecģ�ʹ���,ɸѡ֮��û����server socket
        if (ret = 0) {
            Sleep(1);
            continue;
        }

        for (int i = 0; i < tmp.fd_count; i++) {
            /*
            �������� 1.serverSocket��������  2.���͸�clntSock����  
            */

            if (tmp.fd_array[i] == servSock) {
                //���տͻ�������
                SOCKADDR clntAddr;
                int nSize = sizeof(SOCKADDR);
                SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);         
                if (clntSock == SOCKET_ERROR) {
                    printf("tcp����ʧ��");
                }
                printf("tcp���ֳɹ�\n");
                FD_SET(clntSock, &allsockets);
            }
            else {
                // client socket�������¼���֤���ͻ��˷�������
                    char str[20] = {};
                    int result=recv(tmp.fd_array[i], str, 20, NULL);                 
                    if (result > 0) {                     
                        printf("���ܵ�����:%s\n", str);
                    }
                    else {
                        FD_CLR(tmp.fd_array[i],&allsockets);
                        // �޳���ǰ��client socket                      
                        printf("�Ͽ�����");
                        break;
                    }
                
            }
        }
    }


   


    while (1);
    //�ر��׽���
    //closesocket(clntSock);
    closesocket(servSock);

    //��ֹ DLL ��ʹ��
    WSACleanup();

    return 0;
}