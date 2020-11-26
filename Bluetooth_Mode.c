#include<header.h>
void bt_connect(char *bt_id);
int  Get_Weight_data_of_Bluetooth(char *client_btaddr,char *passkey,char *data) // bluetooth User name, Password Key
{

	int ret;
	char macid[20];
	ret = Check_Config_Mode();	
	if ( ret != 0 )
	{
		fprintf(stdout,"Bluetooth Module Not found\n");
		return -1;
	}
	if ( Copy_Weight_data_of_Bluetooth_node(data) == 0 )
		return 0;

	memset(macid,0,sizeof(macid));

	system("/etc/rc.d/init.d/bluetooth start ");

	ret = get_bluetooth_macid(client_btaddr,macid);
	if ( ret != 0 )
	{
		fprintf(stdout,"Not Found %s Device \n",client_btaddr);
		return -1;
	}

	fprintf(stdout,"%s\n",macid);
	ret = Pair(macid,passkey);
	if ( ret != 0 )
	{
		fprintf(stdout,"Pair Failed %s Device,  passkey = %s\n",client_btaddr,passkey);
		return -1;
	}

	bt_connect(macid);	
	return   Copy_Weight_data_of_Bluetooth_node(data);
}

int Pair(char *Passkey, char *macid)
{
	char cmd[256];
	int i,ret;
	memset(cmd,0,sizeof(cmd));

	sprintf(cmd,"simple-agent %s %s",Passkey,macid);
	for( i = 0 ; i < 2 ; i++ )
	{
	fprintf(stdout,"cmd = %s\n",cmd);
		ret =   system(cmd);
		if ( ret == 0 )
			break;
		else 
		{
			fprintf(stdout,"Retrying Paitnr\n");
			sleep(1);
		}
	}


	return ret;
}


int get_bluetooth_macid(char *client_btaddr, char *macid)
{
	FILE *fp;
	char Buff[20]="";
	char cmd[256];
	int i;
	char *filename="/tmp/.WSSN_Scan_list_OPDS";
	memset(cmd,0,sizeof(cmd));


	fprintf(stderr,"\nBluetooth device Scanning .....\n");


	sprintf(cmd,"hcitool scan | grep %s > %s",client_btaddr,filename);

	for( i = 0 ; i < 3 ; i++ )
	{
		memset(Buff,0,sizeof(Buff));
		system(cmd);
		fp = fopen(filename,"r");

		if(fp == NULL)
		{
			fprintf(stderr," %s unable to open scaning file \n",filename);
			return -1;
		}


		fread(Buff,20,1,fp);

		sscanf(Buff,"%s",macid);

		fclose(fp);

		remove(filename);

		if( strlen(macid) != 0)
			return 0;
		else
		{
			fprintf(stdout," %s not found, retrying, buff = %s\n" ,client_btaddr,Buff);
			sleep(1);
		}
	}


	return -1;
}

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


void bt_connect(char *bt_id)
{
	char buffer[40]="";
	int ret=0;
	if ( access("/dev/rfcomm0",F_OK) != 0  )
		system("killall rfcomm");
	
	sprintf(buffer,"rfcomm connect 0 %s 1 &", bt_id);
	system(buffer);
	fprintf(stdout,"Buffer = %s\n",buffer);
	sleep(2);
	return;
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
		return -1;
	}
	system("rmmod lcd_dat23");
	sleep(1);
	return 0;
}
int Copy_Weight_data_of_Bluetooth_node(char *data)
{
	char *Bluetooth_node="/dev/rfcomm0";
	if ( access("/dev/rfcomm0",F_OK) != 0  )
	{
		return -1;
	}
	return copy_weight_data(Bluetooth_node,9600,data);
}
