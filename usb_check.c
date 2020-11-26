#include<header.h>
int usb_node_check(char *usb_node)
{
	int ret=0,flag=0,i=0;
	char buff[128];

	for(i = 0; i < 8; i++)
	{
		memset(buff, 0, sizeof(buff));
		sprintf(buff, "udevadm info --name=/dev/ttyUSB%d --attribute-walk | grep 10c4", i);//calon

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

