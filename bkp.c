#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<termios.h>
#include<string.h>
#define SUCCESS 0
#define FAILURE -1
#define ERROR -2


/*int data_weight(char *node,char *data)
{
	struct termios my_termios;
	int Baudrate=0, pid,l,n,m;
	char *ptr; char buff[20]="";
	int i=0;

	unsigned char send[1024]="",recv[40]="";

	static int fd;

	memset(&my_termios, 0, sizeof(struct termios));

	Baudrate=B9600;


	fd = open(node,O_RDWR|O_NOCTTY|O_NONBLOCK);
	if( fd < 0 || Baudrate ==0 ) {  fprintf(stderr,"Unable to open port\n"); return -1; }


	tcflush(fd,TCIFLUSH);
	my_termios.c_cflag=Baudrate|CS8|CREAD;//|PARENB;
	my_termios.c_cc[VMIN]=0;
	my_termios.c_cc[VTIME]=0;
	tcsetattr(fd,TCSANOW,&my_termios);

	memset(recv,0x00,40);
	sleep(1);
jump:
	m = read(fd,&recv,40);

	if(m > 0)
	{
		if((ptr = strchr(recv,'+'))!=NULL)
		{
			ptr=ptr+1;
			while(i<10)
			{
				buff[i]=ptr[i];
				i++;
			}
		}
		else
			goto jump;

		strcpy(data,buff);

	}
	else
		return -2;

	close(fd);
	return 0;
} */


int bt_connect(char *bt_id)
{
	char buffer[40]="";
	int ret=0;
	sprintf(buffer, "rfcomm connect 0 %s 1 &", bt_id);
	ret = system(buffer);
	sleep(5);
	ret = system("ls /dev/rfcomm0 > /dev/null");
	if(ret != 0)
		return -1;
	return 0;


}

int bt_scan(char *bt_id)
{
	FILE *fp;
	int rd;
	char *line=NULL,*str;
	int len=20;
	char buff[20]="";
	int i=0;

	system("hcitool scan > scaning.txt");
	fp = fopen("scaning.txt","r");
	if(fp == NULL)
	{
		printf("unable to open scaning file \n");
		return -2;
	}


	while(rd = getline(&line, &len, fp) !=NULL)
	{

		if((str = (char *)strstr(line,"APPDS_VNTK@2015")) != NULL)
		{
			line=line+1;
			strncpy(buff,line,17);	   
			printf("bt_id==%s\n",buff);
			strcpy(bt_id,buff);
			fclose(fp);
			return 0;

		}
		i++;
		if(i>20)
			break;
	}
	return -1;
}

int bt_node_chk()
{
	int ret;
	ret = system("ls /dev/rfcomm0 > /dev/null");
	if(ret != 0)
	{
		return -1;
	}
	return 0;

}

int bt_pwr_on()
{
	FILE *fp, *fp1;
	int ret=0,i;
	char buff[100]="",buff1[100]="",*chr;
	char buffer[50]="";
	system("insmod /vision/lcd_dat23.ko");
	sleep(2);
	system("lsusb > lsusb.txt");
	fp1 = fopen("lsusb.txt","r");
	fseek(fp1,0,2);
	ret = ftell(fp1);
	rewind(fp1);
	char *ch=(char *)malloc(ret);
	for(i=0;i<ret;i++)
	{
		ch[i]=fgetc(fp1);
	}
	chr = strstr(ch,"0a12:0001");
	if(chr == NULL)
	{
		printf("\t\tBluetooth Device Failure \n");
		system("rm -rf lsusb.txt");
		fclose(fp1);
		return ERROR;
	}
	fclose(fp1);
	printf("\t\tBluetooth Device Success \n");

	system("hciconfig > hciconfig.txt");
	fp = fopen("hciconfig.txt","r");
	if( fp == NULL )
	{
		printf("hciconfi file not found\n");
		return -1;

	}

	fread(buffer,30,1,fp);
	chr = strstr(buffer,"hci0:");
	if(chr == NULL)
	{
		printf("\t\t Bluetooth poweron Failed ... \n\n");
		return FAILURE;
	}
	sprintf(buff1,"/etc/rc.d/init.d/bluetooth start");
	ret = system(buff1);
	sleep(1);
	system("rm -rf hciconfig.txt");
	system("rm -rf lsusb.txt");
	fclose(fp);
	free(ch);
	return SUCCESS;

}



int bt_pwroff()
{
	int ret=0;
	char buff[100]="",buff1[100]="";
	sprintf(buff,"/etc/rc.d/init.d/bluetooth stop");
	system("rfcomm release 0");
	ret = system(buff);
	if(ret != 0 )
	{
		fprintf(stderr,"\t\t Stoping Bluetooth Service Failure\n\n");
		return FAILURE;
	}
	system("rmmod lcd_dat23");
	sleep(1);
	return SUCCESS;
}


int bt_paring(char *client_btaddr, char *passkey)
{
	FILE *fp;
	int ret,i ;
	char buff[50]="";
	char details[50]="";


	sprintf(buff,"simple-agent %s %s > client_paring.txt",client_btaddr,passkey);
	system(buff);
        sleep(1);
	fp = fopen("client_paring.txt","r");
	fseek(fp,0,2);
	ret = ftell(fp);
	rewind(fp);
	for(i=0;i<ret;i++)
	{
		details[i]=fgetc(fp);
	}
	if(strstr(details,"Pairing failed:"))
	{
		fclose(fp);
		return -1;
	}
	else if(strstr(details,"Pairing sucessfull"))
	{
		fclose(fp);
		return 0;
	}
}
