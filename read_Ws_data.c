#include<header.h>
int copy_weight_data(char *device_file,int baudrate,char *data)
{
	struct termios my_termios,old_termios;
	int length=0, fd,flag=0,ret,i; 
	char recv[40];
	memset(&my_termios, 0, sizeof(struct termios));


	switch (baudrate)
	{
		case 300:    baudrate=B300; break;
		case 1200:   baudrate=B1200; break;
		case 2400:   baudrate=B2400; break;
		case 9600:   baudrate=B9600; break;
		case 19200:  baudrate=B19200; break;
		case 38400:  baudrate=B38400; break;
#ifdef B57600
		case 57600:  baudrate=B57600; break;
#endif
#ifdef B115200
		case 115200: baudrate=B115200; break;
#endif
#ifdef B230400
		case 230400: baudrate=B230400; break;
#endif
		default: baudrate=B9600;
			 fprintf(stdout,"Baudrate input wrong, Proceeding with 9600 defaultly\n");
	}


	fd = open(device_file,O_RDONLY|O_NOCTTY|O_NONBLOCK);
	if( fd < 0 || baudrate ==0 ) 
	{ 
		fprintf(stderr,"Unable to open port \n Please check the Arguments\n"); 
		return -1;
	}

	tcgetattr(fd,&old_termios);
	tcflush(fd,TCIFLUSH);
	my_termios.c_cflag=baudrate|CS8|CREAD;/*|PARENB;*/
	my_termios.c_cc[VMIN]=0;
	my_termios.c_cc[VTIME]=0;
	tcsetattr(fd,TCSANOW,&my_termios);

	sleep(1);
	for ( i =0; i<3;i++)
	{
		memset(recv,0,sizeof(recv));
		length = read(fd,recv,36);
		if ( length > 0 )
		{	
			ret = parse_and_copy_format_data(recv,data);
			if ( ret == 0 )
			{
				flag=1;
				break;
			}

		}
		usleep(1000);
	}
	close(fd);
	if ( flag == 1 )
		return 0;
	else
		return -2;

}
int parse_and_copy_format_data(char *inputdata,char *outputdata)
{
	int i,flag=0,len=0;
	char *ptr=NULL;
	char buff[40];
	memset(buff,0,sizeof(buff));
	if (  (  ( ptr = strstr(inputdata,"-") ) != NULL ) || ( ( ptr = strstr(inputdata,"+") ) != NULL )  )
	{

		buff[0] = ptr[0];
		len = strlen(ptr);

		for(i=1;i<len;i++)
		{
			if ( ptr[i] == 'g')
			{
				buff[i]=ptr[i];
				i++;
				flag=1;
				break;
			}
			buff[i]=ptr[i];
		}
		buff[i]='\0';

	}

	if ( flag == 1 )
	{
		strcpy(outputdata,buff);
		return 0;
	}
	else return -1;
}

