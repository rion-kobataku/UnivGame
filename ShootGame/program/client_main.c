/*****************************************************************
�ե�����̾	: client_main.c
��ǽ		: ���饤����ȤΥᥤ��롼����
*****************************************************************/

#include"common.h"
#include"client_func.h"

int main(int argc,char *argv[])
{
	char	serverName[MAX_NAME_SIZE];
	int		clientID;
    int		num;
    u_short port = PORT;
    int		endFlag = 1;

    /* �����������å� */
    switch(argc) {
  	case 1:
    	break;
  	case 2:
    	sprintf(serverName, "%s", argv[1]);
    	break;
  	case 3:
    	sprintf(serverName, "%s", argv[1]);
    	port = (u_short)atoi(argv[2]);
    	break;
  	default:
    	fprintf(stderr, "Usage: %s [server name] [port number]\n", argv[0]);
    	return 1;
  	}

    /* �����С��Ȥ���³ */
    if(SetUpClient(serverName ,port)==-1){
        fprintf(stderr,"setup failed : SetUpClient\n");
        return -1;
    }
    fprintf(stderr, "clientID = %d\n", clientID);

    SetUpClient(serverName ,port); // client¦�ν������
    
    /* ������ɥ��ν���� */
    if(InitWindows(clientID,num)==-1){
        fprintf(stderr,"setup failed : InitWindows\n");
        return -1;
    }

	/*�������ǡ����Υ�����*/
    PlayerLoad();
    PlayerDataLoad();
    EnemyLoad();
    EnemyDataLoad();

	/*�ƹ�¤�Τν����*/
    PlayerInit(num);
    EnemyInit();

    /* �ᥤ�󥤥٥�ȥ롼�� */
    while(endFlag){
        DrawGameMain(clientID, num);
        endFlag = SendRecvManager();
        //fprintf(stderr, "endFlag = %d\n", endFlag);
    };

    /* ��λ���� */
    DestroyWindow();
    CloseSoc();

    return 0;
}
