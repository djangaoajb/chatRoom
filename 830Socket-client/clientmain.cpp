#pragma warning(disable:4996)
#include <Ws2tcpip.h> 
#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll


//void dealMsg(char *d) {
//    char* msg = d;
//    if (strcmp(msg, "show")) {
//        //չʾ������
//    }
//    else if (strcmp(msg, "join")) {
//        //join������
//    }
//    else if (strcmp(msg, "create")) {
//        //create������
//    }
//    else if (strcmp(msg, "talk")) {
//        //����
//    }
//    else if (strcmp(msg, "leave")) {
//        //�뿪
//    }
//    else {
//        printf("�������");
//    }
//
//}

int main() {
    //��ʼ�� DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //�ͻ����׽���
    SOCKET CliSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    //�󶨿ͻ����׽���
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
    sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //�����IP��ַ
    sockAddr.sin_port = htons(1234);  //�˿�



    // ��������
    if (connect(CliSock, (sockaddr*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR) {
        printf("tcp����ʧ��");
        closesocket(CliSock);
    }

    printf("������������ɹ�\n");


    while (true)
    {
        //�����˷�����
        printf("�����������˷��͵�����\n");
        char buff[20];
        scanf("%s", buff);
        // �ж�ָ��-����ʲô��Ϣ����
        //dealMsg(buff);

        if (send(CliSock, buff, 20, 0) < 0) {
            printf("����ʧ��\n");
        }
    }


    while (1);
    //�ر��׽���
    closesocket(CliSock);
    WSACleanup();

    return 0;
}