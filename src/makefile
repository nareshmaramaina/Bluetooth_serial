CC= arm-none-linux-gnueabi-gcc -Wall 
bin_strip=arm-none-linux-gnueabi-strip

CFLAGS=-Wall  -I ../include  
libs=-L ../lib/ -lgl11pos -lpcsclite -ldl 
Get_Weighing_Scale_data:main.c Bluetooth_init.c USB_mode.c read_Ws_data.c Serial_Mode.c Bluetooth_Mode.c

	$(CC)  $?  $(libs)  $(CFLAGS) -o $@
	$(bin_strip) $@ 
clean:
	rm Get_Weighing_Scale_data 
