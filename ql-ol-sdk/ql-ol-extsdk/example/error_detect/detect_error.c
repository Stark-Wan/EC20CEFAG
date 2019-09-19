#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 

#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <fcntl.h> 


#define portnumber                              3333
#define COMMAND_TIMEOUT_ERROR_INTERRUPT         "0x18000" 
#define DATA_CRC_ERROR                          "0x200000" 
#define DATA_TIMEOUT_ERROR                      "0x100000"
#define LINK_IS_DOWN                            40


static int super_system(const char * cmd, char *retmsg, int msg_len)
{
        FILE * fp;
        int res = -1;
        if (cmd == NULL || retmsg == NULL || msg_len < 0)
        {
                printf("Err: Fuc:%s system paramer invalid!\n", __func__);
                return 1;
        }
        if ((fp = popen(cmd, "r") ) == NULL)
        {
                perror("popen");
                printf("Err: Fuc:%s popen error: %s\n", __func__, strerror(errno));
                return 2;
        }
        else
        {
                memset(retmsg, 0, msg_len);
                while(fgets(retmsg, msg_len, fp));
                {
                        printf("Fuc: %s fgets buf is %s\n", __func__, retmsg);
                }
                if ( (res = pclose(fp)) == -1)
                {
                        printf("Fuc:%s close popen file pointer fp error!\n", __func__);
                        return 3;
                }
                retmsg[strlen(retmsg)-1] = '\0';
                return 0;
        }
}

int main(int argc, char *argv[]) 
{ 
    int sockfd,new_fd; 
    struct sockaddr_in server_addr; 
    struct sockaddr_in client_addr; 
    int sin_size; 
    int nbytes;
    char buffer[1024];
    char sdio_msg[20] = {0};
    char phy_msg[20] = {0};
    int sdio_err,phy_err,usb_err,codec_err,modem_err;


    if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:IPV4;SOCK_STREAM:TCP
    { 
        fprintf(stderr,"Socket error:%s\n\a",strerror(errno)); 
        exit(1); 
    } 


    bzero(&server_addr,sizeof(struct sockaddr_in));
    server_addr.sin_family=AF_INET;                 // Internet
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);  
    //server_addr.sin_addr.s_addr=inet_addr("192.168.0.3");
    server_addr.sin_port=htons(portnumber);
    

    if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
    { 
        fprintf(stderr,"Bind error:%s\n\a",strerror(errno)); 
        exit(1); 
    } 


    if(listen(sockfd,5)==-1) //µÈ´ýÁ¬½Ó
    { 
        fprintf(stderr,"Listen error:%s\n\a",strerror(errno)); 
        exit(1); 
    } 

    while(1) 
    { 
        sin_size=sizeof(struct sockaddr_in); 
        
        if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))==-1)
        { 
            fprintf(stderr,"Accept error:%s\n\a",strerror(errno)); 
            exit(1); 
        } 
        printf("Server get connection from %s\n", inet_ntoa(client_addr.sin_addr));
        
        sdio_err = phy_err = usb_err = codec_err = modem_err = 0;
        if((access("/sys/class/net/eth0/device",F_OK))!=-1) 
        {       system("echo 0x01 > /sys/class/net/eth0/device/phy_regnum");
                super_system("cat /sys/class/net/eth0/device/phy_regnum",phy_msg,sizeof(phy_msg));
        }
        
        if((access("/sys/devices/7824900.sdhci/mmc_host/mmc0/mmc0:0001",F_OK))!=-1) 
                super_system("cat /sys/devices/7824900.sdhci/nisr",sdio_msg,sizeof(sdio_msg));
        
        if(strstr(sdio_msg,COMMAND_TIMEOUT_ERROR_INTERRUPT))
                sdio_err = 1;
        else if(strstr(sdio_msg,DATA_CRC_ERROR))
                sdio_err = 2;
        else if(strstr(sdio_msg,DATA_TIMEOUT_ERROR))
                sdio_err = 3;
        
        if(atoi(phy_msg) && 0xFF == LINK_IS_DOWN)
                phy_err = 1;

        sprintf(buffer,"QUEC,SDIO,%d,PHY,%d,USB,%d,CODEC,%d,MODEM,%d,OL\r\n",sdio_err,phy_err,usb_err,codec_err,modem_err);

        
        if(nbytes=write(new_fd,buffer,strlen(buffer))==-1)
        { 
            fprintf(stderr,"Read Error:%s\n",strerror(errno)); 
            exit(1); 
        }          
        close(new_fd);
    } 


    close(sockfd); 
    exit(0); 
} 
