#include<header.h>
int USB_init()
{
	int  ret =0 ;
	ret = gl11_iodev_open();
	if ( ret != 0 )
	{
		fprintf(stdout,"gl11_iodev_open not found\n");
		return -1;
	}

	gl11_host_pwron();

	ret = system("insmod /vision/cp210x.ko 2&> /dev/null");
	if ( ret == 0 )
		sleep(1);

	gl11_iodev_close();

	return 0;
}
int Get_Weight_data_of_USB(char *data)
{
	char USB_node[40];
	int ret;
	USB_init();
	memset(USB_node,0,sizeof(USB_node));	
	ret = Check_and_Copy_USB_Node(USB_node);
	if (ret == 0 )
	{
		fprintf(stdout,"Usb Node Found, %s \n",USB_node);
		ret = copy_weight_data(USB_node,9600,data);
	}
	else 
		fprintf(stdout,"USB node not Found\n");

	return ret;
}
int Check_and_Copy_USB_Node(char *usb_node)
{
	int ret=0,flag=0,i=0;
	char buff[128];

	for(i = 0; i < 8; i++)
	{
		memset(buff, 0, sizeof(buff));
		sprintf(buff, "udevadm info --name=/dev/ttyUSB%d --attribute-walk | grep 10c4 -q", i);//calon

		ret = system(buff);
		if(ret == 0)
		{
			sprintf(usb_node, "/dev/ttyUSB%d", i);
			flag = 1;
			break;
		}
	}

	if(flag)
		return 0;
	else
		return -1;

	return 0;
}
