#include<header.h>
int main()
{
	int Bluetooth_ret,ret;
	char device_file[40],data[40];

	char *client_btaddr="APPDS_VNTK@2015",  *passkey="94321";
	Bluetooth_ret = Check_Config_Mode(1); // 1 for switch on, 0 for switch off 
	if (Bluetooth_ret == 0 )
		fprintf(stdout,"configuration supports Bluetooth and USB modes\n");
	else 
		fprintf(stdout,"configuration supports serial and USB modes\n");

	memset(data,0,sizeof(data));

	Get_Weight_data_of_USB(data);
	fprintf(stdout,"From USB Node = %s\n",data);
	
	memset(data,0,sizeof(data));
	Get_Weight_data_of_Serial(data);
	fprintf(stdout,"From serial Node = %s\n",data);
	
	memset(data,0,sizeof(data));
	ret = Get_Weight_data_of_Bluetooth(client_btaddr,passkey,data); // bluetooth User name, Password Key
	fprintf(stdout,"From Bluetooth Node = %s\n",data);

	return 0;
}

int Serial_init()
{
	int ret = Check_Bluetooth_device(5);
	if ( ret == 0 )
	{
		fprintf(stdout,"This POS device Having bluetooth module, so we can't Use Serial\n");
		return -1;
	}
	return 0;
}
