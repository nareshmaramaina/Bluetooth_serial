#include<header.h>
int Get_Weight_data_of_Serial(char *data)
{
	char *Serial_node="/dev/ttymxc0";
	int ret;
	ret = system("grep console=ttymxc0 /proc/cmdline -q");
	if ( ret == 0 )
	{
		fprintf(stdout," Please Disable Serial Console mode\n");
		return -4;
	}
	ret  = Check_Config_Mode();
	if ( ret == 0 ) 
	{
		fprintf(stdout,"Device Won't support serial type data \n");
		return -3;
	}
	return copy_weight_data(Serial_node,9600,data);
}

