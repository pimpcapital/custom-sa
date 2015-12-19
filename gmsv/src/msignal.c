#include <signal.h>
#include <unistd.h>

#include <stdio.h>

#include "buf.h"
#include "net.h"
#include "char.h"
#include "lssproto_serv.h"
#include "saacproto_cli.h"
#include "log.h"

static void endlsprotocol( void )
{
    lssproto_CleanupServer();
    saacproto_CleanupClient();
}

static void allDataDump( void )
{
  closeAllLogFile();
	storeCharaData();
}

void shutdownProgram( void )
{
    printf("关闭SAAC连接:%d\n",close( acfd ));
    printf("关闭绑定端口:%d\n",close( bindedfd ));
    memEnd();
}
extern int player_online;
extern int player_maxonline;
char saacfunc[255]="";
void sigshutdown( int number )
{
		if( number == 0 ){
			print( "\nGMSV正常关闭\n" );
		}else{
			print( "\n=========以下是服务器出错原因=========\n");
            print( "标准信息: %d\n" , number  );
			print( "在线人数: %d\n", player_online);
			print( "最高在线: %d\n", player_maxonline);
			print( "SAAC函数: %s\n", saacfunc);
			print( "=========以上是服务器出错原因=========\n");
		}
		remove( "gmsvlog.err2");
		rename( "gmsvlog.err1", "gmsvlog.err2" );
		rename( "gmsvlog.err", "gmsvlog.err1" );
		rename( "gmsvlog", "gmsvlog.err" );

    allDataDump();

    signal( SIGINT , SIG_IGN );
    signal( SIGQUIT, SIG_IGN );
    signal( SIGKILL, SIG_IGN );
    signal( SIGSEGV, SIG_IGN );
    signal( SIGPIPE, SIG_IGN );
    signal( SIGTERM, SIG_IGN );

    shutdownProgram();
    exit(number);
}



void signalset( void )
{
    // CoolFish: Test Signal 2001/10/26
    print("\n开始获取信号..\n");

		print("SIGINT:%d\n", SIGINT);
		print("SIGQUIT:%d\n", SIGQUIT);
		print("SIGKILL:%d\n", SIGKILL);
		print("SIGSEGV:%d\n", SIGSEGV);
		print("SIGPIPE:%d\n", SIGPIPE);
		print("SIGTERM:%d\n", SIGTERM);
    
    signal( SIGINT , sigshutdown );
    signal( SIGQUIT, sigshutdown );
    signal( SIGKILL, sigshutdown );
    signal( SIGSEGV, sigshutdown );
    signal( SIGPIPE, SIG_IGN );
    signal( SIGTERM, sigshutdown );
}
