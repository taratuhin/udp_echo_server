
/**
 *   \file     udp_server.c
 *   \version  0.01
 *   \date     2024.04.12
 */

#include  <sys/socket.h>
#include  <netinet/in.h>
#include  <arpa/inet.h>
#include  <strings.h>
#include  <stdio.h>

#define  SERVER_PORT 3333
#define  MAX_LINE 4096


static  void  dg_echo( int  sockfd, struct  sockaddr  * p_cli_addr, socklen_t  clilen );
static  void  graph( void );


/**
 *   \brief   Точка входа
 *   \param   argc - количество входных параметров
 *   \param  *argv - входные параметры
 *   \return  Код завершения
 */
int  main( int  argc, char  * argv[] )
{
    int  sock_fd;
    struct  sockaddr_in  server_addr;
    struct  sockaddr_in  client_addr;


    sock_fd = socket( AF_INET, SOCK_DGRAM, 0 );
    bzero( &server_addr, sizeof( server_addr ) );
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr( "192.168.0.1" );
    server_addr.sin_port = htons( SERVER_PORT );

    bind( sock_fd, ( struct  sockaddr  * ) &server_addr, sizeof( server_addr ) );

    dg_echo( sock_fd, ( struct  sockaddr  * ) &client_addr, sizeof( client_addr ) );

    return 0;
}


/**
 *   \brief   Эхо-UDP
 *   \param   sock_fd - дескриптор
 *   \param  *p_client_addr - структура описывает сокет для работы с протоколами IP
 *   \param   client_len - размер структуры p_cliet_addr
 *   \return  Нет
 */
static  void  dg_echo( int  sock_fd, struct  sockaddr  * p_client_addr, socklen_t  client_len )
{
    int  n;
    socklen_t  len;
    char  mesg[MAX_LINE];


    for ( ; ; )
    {
        len = client_len;
        n = recvfrom( sock_fd, mesg, MAX_LINE, 0, p_client_addr, &len );
        sendto( sock_fd, mesg, n, 0, p_client_addr, len );
        graph();
    }
}


/**
 *   \brief  Индикатор обмена
 *   \param  Нет
 *   \param  Нет
 */
static  void  graph( void )
{
    static  int  position = 0;
    const  char  * progress = "-\\|/-\\|/";


    printf( "\r%c",  progress[position++ % sizeof( progress )] );
    fflush( stdout );
}

