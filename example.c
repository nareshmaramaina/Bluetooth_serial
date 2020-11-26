#include"header.h"
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
		printf(" len %d \n",len);
		
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
int main()
{
char buff[40]="";
char *Output="000.010 K\n+000.000 Kgl\n+";
printf("Value =%d\n",parse_and_copy_format_data(Output,buff));

printf("Output Buffer = %s\n",buff);
return 0;
}
