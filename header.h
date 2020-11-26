#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<termios.h>
#include<string.h>
int Bluetooth_Switch(int arg);
int usb_device_presence (char *vendor_id, char *product_id);
int  Check_Bluetooth(int times);
int gl11_iodev_open();
int gl11_iodev_close();
int Check_and_Get_USB_Node(char *usb_node);
int copy_weight_data(char *device_file,int baudrate,char *data);
int parse_and_copy_format_data(char *inputdata,char *outputdata);
