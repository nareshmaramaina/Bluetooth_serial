inGt Pair(char *Passkey, char *macid)
{
        FILE *fp;
        char Buff[24]="";
        char cmd[256];
        int i;
        char *filename="/tmp/.WSSN_Pair_result_OPDS";
        memset(cmd,0,sizeof(cmd));

        sprintf(cmd,"simple-agent %s %s | grep success -i > %s",macid,Passkey,filename);

        for( i = 0 ; i < 3 ; i++ )
        {
                memset(buff,0,sizeof(buff));
                system(cmd);
                fp = fopen(filename,"r");

                if(fp == NULL)
                {
                        fprintf(stderr," %s unable to open  file \n",filename);
                        return -1;
                }


                fread(Buff,24,1,fp);


                fclose(fp);

                remove(filename);

                if( strstr(Buff,"Pairing sucessfull") != NULL)
                        return 0;
                else
                {
                        fprintf(stdout," Pairing Failed, retrying\n");
                        sleep(1);
                }
        }


        return -1;
}
int bt_paring(char *Passkey, char *passkey)
{
        FILE *fp;
        int ret,i ;
        char buff[50]="";
        char details[50]="";


        sprintf(buff,"simple-agent %s %s > client_paring.txt",Passkey,passkey);
        system(buff);
        sleep(1);
        fp = fopen("client_paring.txt","r");
        fseek(fp,0,2);
        ret = ftell(fp);
        rewind(fp);
        for(i=0;i<ret;i++)
        {
                details[i]=fgetc(fp);
        }
        if(strstr(details,"Pairing failed:"))
        {
                fclose(fp);
                return -1;
        }
        else if(strstr(details,"Pairing sucessfull"))
        {
                fclose(fp);
                return 0;
        }
}
int Copy_Weight_data_of_Bluetooth_node(char *data)
{
	char *Bluetooth_node="/dev/rfcomm0";
	copy_weight_data(Bluetooth_node,9600,data);
	return ret;
}

