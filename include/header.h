#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<termios.h>
#include<string.h>
int Check_Config_Mode(); 
/*
 int Check_Config_Mode(); Function will check the config type, Actually main  intension is to tell the Device config type having Bluetooth or not. If Bluetooth present assuming device is 1105, so serial cable we not able to Connect. 
               On return 0; configuration supports Bluetooth and USB modes
               On return < 0; configuration supports serial and USB modes
*/

int Get_Weight_data_of_USB( char *data);
/*
   int Get_Weight_data_of_USB( char *data);

   Give Function char buffer Argument  for  get the Weight data of USB node, And Buffer should be minimum 40 bytes 

   On Success, this function will returns 0 and Weighing Scale Weight data will get in the  char *data Buffer )  
   On Failure, return < 0, 
   i.e, return -1   USB node not found 
   return -2   data not found in Weighing Scale USB node  */


int Get_Weight_data_of_Serial( char *data);
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

int  Get_Weight_data_of_Bluetooth(char *client_btaddr,char *passkey,char *data); // bluetooth User name, Password Key

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
   return -5   Pairing Failed */




void bt_pwroff(); // Power Of Bluetooth Module


int Bluetooth_Switch(int arg);
int usb_device_presence (char *vendor_id, char *product_id);
int  Check_Bluetooth(int times);
int gl11_iodev_open();
int gl11_iodev_close();
int gl11_host_pwron();
int Check_and_Get_USB_Node(char *usb_node);
int copy_weight_data(char *device_file,int baudrate,char *data);
int parse_and_copy_format_data(char *inputdata,char *outputdata);
int Copy_Weight_data_of_Bluetooth_node(char *data);
void bt_connect(char *bt_id);
int Pair(char *Passkey, char *macid);
int get_bluetooth_macid(char *client_btaddr, char *macid);
