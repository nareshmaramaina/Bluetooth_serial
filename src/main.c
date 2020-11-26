#include<header.h>
void Report(int Mode,int return_Status,char *data);
int main()
{
	int Bluetooth_Mode,ret,num,Mode;
	char data[40];

	//char client_btaddr[40]="APPDS_VNTK@2015",  passkey[40]="94321";
	char client_btaddr[40],  passkey[40];

	Bluetooth_Mode = Check_Config_Mode();
	if (Bluetooth_Mode == 0 )
		fprintf(stdout,"configuration supports Bluetooth and USB modes\n");
	else
		fprintf(stdout,"configuration supports serial and USB modes\n");

	while(1)
	{
		memset(data,0,sizeof(data));
		if ( Bluetooth_Mode == 0 )
			fprintf(stdout,"Enter a number\n 1) Bluetooth Mode \t 2) USB Mode\t3) Quit");
		else 
			fprintf(stdout,"Enter a number\n 1) Serial Mode \t 2) USB Mode\t3) Quit");

		scanf("%d",&num);
		if ( num == 3)
			break;
		else if ( num == 1 && Bluetooth_Mode == 0 )
		{
			Mode=3;
			memset(client_btaddr,0,sizeof(client_btaddr));	
			fprintf(stdout,"Enter Weighing Scale Bluetooth Client Address Name, Example: APPDS_VNTK@2015\n");
			scanf("%s",client_btaddr);
			fprintf(stdout,"Enter Weighing Scale Bluetooth passkey, Example: 94321\n");
			scanf("%s",passkey);
		}
		else if ( num == 1 && Bluetooth_Mode != 0 )
			Mode=1;
		else if ( num == 2 )
			Mode=2;
		else 
		{
			fprintf(stdout,"Invalid Entered %d, Choose Valid one \n",num);
			continue;
		}
		if ( Mode == 1 )
			ret = Get_Weight_data_of_Serial(data);
		else if ( Mode == 2 )
			ret = Get_Weight_data_of_USB(data); 
		else if ( Mode == 3 )
			ret = Get_Weight_data_of_Bluetooth(client_btaddr,passkey,data); // bluetooth User name, Password Key
		else 
			fprintf(stdout,"Invalid Mode\n");
		Report(Mode,ret,data);
	}
	fprintf(stdout,"Exiting, Application \n");
	return 0;
}
void Report(int Mode,int return_Status,char *data)
{
	char mode[40];
	memset(mode,0,sizeof(mode));

	if ( Mode == 1 ) 
		strcpy(mode,"Serial");
	else if ( Mode == 2 )
		strcpy(mode,"USB");
	else if ( Mode == 3 )
		strcpy(mode,"Bluetooth");

	if ( return_Status == 0 )
		fprintf(stdout,"From %s Node, Weight data is %s\n",mode,data);
	else if (  return_Status == -1 )
		fprintf(stdout,"%s Node not found\n",mode);
	else if (  return_Status == -2 )
		fprintf(stdout,"data not found in Weighing Scale %s node\n",mode);
	else if (  return_Status == -3 )
		fprintf(stdout,"Device Won't Support %s \n",mode);
	else if (  Mode == 1 && return_Status == -4 )
		fprintf(stdout,"Please Disable the Device Serial Console mode through console icon\n");
	else if (  Mode == 3 && return_Status == -4 )
		fprintf(stdout,"Bluetooth Client Address not Found in Scanning\n");
	else if ( Mode == 3 && return_Status == -5 )
		fprintf(stdout,"Bluetooth Pairing Failed\n");
	else fprintf(stdout,"Unknown Error\n");
	return ;
}
/*
   int Get_Weight_data_of_USB( char *data);

   Give Function char buffer Argument  for  get the Weight data of USB node, And Buffer should be minimum 40 bytes 

   On Success, this function will returns 0 and Weighing Scale Weight data will get in the  char *data Buffer )  
   On Failure, return < 0, 
   i.e, return -1   USB node not found 
   return -2   data not found in Weighing Scale USB node  */	


/*
   int Get_Weight_data_of_Serial( char *data);
   Give Function char buffer Argument  for  get the Weight data of Serial node, And Buffer should be minimum 40 bytes 

   On Success, this function will returns 0 and Weighing Scale Weight data will get in the  char *data Buffer )  
   On Failure, return < 0, 
   i.e, return -1   Serial node not found 
   return -2   data not found in Weighing Scale Serial node
   return -3   Device Won't support serial mode  
   return -4   Please Disable the Device Serial Console mode through console icon
   */	


/*

   int  Get_Weight_data_of_Bluetooth(char *client_btaddr,char *passkey,char *data); // bluetooth User name, Password Key
   Give Function Argument 1, Bluetooth Client Address, Example: APPDS_VNTK@2015 
   Give Function Argument 2, Bluetooth passkey  Example: 94321
   Give Function Argument 3, char buffer  for  get the Weight data of USB node, And Buffer should be minimum 40 bytes 


   On Success, this function will returns 0 and Weighing Scale Weight data will get in the  char *data Buffer )
   On Failure, return < 0,
   i.e, return -1   Bluetooth node not found
   return -2   data not found in Weighing Scale Bluetooth node
   return -3   Device Won't Support Bluetooth  
   return -4   Bluetooth Client Address not Found in Scanning
   return -5	 Pairing Failed
   */

