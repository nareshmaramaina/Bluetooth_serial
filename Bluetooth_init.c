#include<header.h>

int Bluetooth_Switch(int arg)
{
	int  ret =0 ;
	ret = gl11_iodev_open();
	if ( ret != 0 )
	{
		fprintf(stdout,"gl11_iodev_open not found\n");
		return -1;
	}
	void *handle;
	char (*bluetooth)(char);
	char *error;

	handle = dlopen ("libgl11pos.so", RTLD_NOW);
	if (!handle) {
		fputs (dlerror(), stderr);
		return -1;
	}

	bluetooth = dlsym(handle, "gl11_bluetooth_control");
	if ((error = dlerror()) != NULL) 
	{
		fputs(error, stderr);
		return -1;
	}
	ret =  (*bluetooth)(arg);

	dlclose(handle);
	gl11_iodev_close();
	return ret;

}

int  Check_Bluetooth_device(int times)
{
	int bt_check=-1,i;

	for (i=0; i<times ;i++)
	{

		bt_check = usb_device_presence("0a12","0001");
		if( bt_check == 0)
			return 0;
		else
			printf("Bluetooth not found usb_device_presence = %d\n",bt_check);	


	}	
	return -1;

}
int usb_device_presence (char *vendor_id, char *product_id)
{
	FILE *fp=NULL;

	char tmp_buf[80]="";

	int ver_flag=0;

	char info[512]="";

	memset(tmp_buf,0x00,80);

	sprintf(tmp_buf,"Vendor=%s ProdID=%s",vendor_id,product_id);

	fp=fopen("/proc/bus/usb/devices","r");

	if (fp == NULL)
		return -1;


	while (fgets(info, sizeof(info), fp) != NULL )
	{

		if (strstr(info,"Vendor="))
		{
			if (strstr(info,tmp_buf))
			{
				ver_flag=1;
         break;
                        }

                }
        }

        fclose(fp);

        if (ver_flag)
                return 0;
        else
                return -1;
}
int Check_Config_Mode()
{
	int ret;
	ret = Check_Bluetooth_device(5);
	if(ret == 0)
		printf("Bluetooth found\n");
	else 
		ret =  Bluetooth_Switch(1);
	return ret;
}


/*int main()
  {

  Check_Config_Mode(1); 

  }*/
