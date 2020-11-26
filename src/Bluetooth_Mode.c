#include<header.h>
int  Get_Weight_data_of_Bluetooth(char *client_btaddr,char *passkey,char *data) // bluetooth User name, Password Key
{

	int ret;
	char macid[20];
	ret = Check_Config_Mode();	
	if ( ret != 0 )
	{
		fprintf(stdout,"Device Won't Support Bluetooth  \n");
		return -3;
	}
	if ( Copy_Weight_data_of_Bluetooth_node(data) == 0 )
		return 0;

	memset(macid,0,sizeof(macid));

	system("/etc/rc.d/init.d/bluetooth start ");

	ret = get_bluetooth_macid(client_btaddr,macid);
	if ( ret != 0 )
	{
		fprintf(stdout,"Not Found %s Device \n",client_btaddr);
		return -4;
	}

	ret = Pair(macid,passkey);
	if ( ret != 0 )
	{
		fprintf(stdout,"Pair Failed %s Device,  passkey = %s, Macid = %s\n",client_btaddr,passkey,macid);
		return -5;
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
		ret =   system(cmd);
		if ( ret == 0 )
			break;
		else 
		{
			fprintf(stdout,"Retrying Pairing\n");
			sleep(1);
		}
	}

	return ret;
}

int Pair(char *Passkey, char *macid);
int get_bluetooth_macid(char *client_btaddr, char *macid);

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

void bt_connect(char *bt_id)
{
	char buffer[40]="";
	if ( access("/dev/rfcomm0",F_OK) != 0  )
		system("killall rfcomm >/dev/null 2>&1");

	sprintf(buffer,"rfcomm connect 0 %s 1 &", bt_id);
	system(buffer);
	sleep(2);
	return;
}


int Copy_Weight_data_of_Bluetooth_node(char *data)
{
	char *Bluetooth_node="/dev/rfcomm0";
	if ( access("/dev/rfcomm0",F_OK) != 0  )
		return -1;
	return copy_weight_data(Bluetooth_node,9600,data);
}
