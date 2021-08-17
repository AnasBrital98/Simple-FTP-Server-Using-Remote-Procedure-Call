#include "ftp.h"


void ftpserverprogram_1(char *host,int option,char FilePath[20])
{
	CLIENT *clnt;
	int  *result_1;
	Path  initialzedownload_1_arg;
	void  *result_2;
	Path  initialzeupload_1_arg;
	data  *result_3;
	char *getfile_1_arg;
	void  *result_4;
	data  putfile_1_arg;
	int  *result_5;
	Path  changedirectory_1_arg;
	int  *result_6;
	Path  listdirectory_1_arg;
	int  *result_7;
	Path  removefile_1_arg;
	int SizeMax=25000,FileLenght=0,bytesReceived=0,bytesSended=0,output=0;
	FILE *file = NULL;   
#ifndef	DEBUG
	clnt = clnt_create (host, FTPServerProgram, version1, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
    
#endif	/* DEBUG */
	switch (option)
	{
	case 1 :
				strcpy(initialzedownload_1_arg.FileName,FilePath);
				if(( file = fopen(initialzedownload_1_arg.FileName,"w+") ) == NULL)
				{
					fprintf(stderr,"Failed to create The File with The Name %s ...\n",initialzedownload_1_arg.FileName);
					return;
				}			
				result_1 = initialzedownload_1(&initialzedownload_1_arg, clnt);
				if(!*result_1)
				{
					printf("File Not Found ...\n");
					return;
				}
				while(1)
				{
					result_3 = getfile_1((void*)&getfile_1_arg, clnt);
                    if((output = fwrite(result_3->buffer,1,result_3->size,file)) == -1)
					{
						fprintf(stderr,"Failed to write in The File %s ...\n",FilePath);
						return;
					}
					printf("%d bytes Received ...\n",output);
					bytesReceived += output;
					if(output < SizeMax)
					{
						fclose(file);
						printf("Total Bytes Received is %d ... \n",bytesReceived);
						printf("File Received Successfully ... \n");
						return;
					}
				}					
	break;

    case 2 :
                strcpy(initialzeupload_1_arg.FileName,FilePath);
                result_2 = initialzeupload_1(&initialzeupload_1_arg, clnt);
                if((file = fopen(FilePath,"r")) == NULL)
                {
                    fprintf(stderr,"Failed to Open The File %s ... \n",initialzeupload_1_arg.FileName);
                    return;
                }
                fseek(file,0,SEEK_END);
                FileLenght = ftell(file);
                fseek(file,0,SEEK_SET);
                printf("File Lenght = %d , File Name = %s \n",FileLenght,FilePath);                
                while(1)
                {
                    if((output = fread(putfile_1_arg.buffer,1,SizeMax,file)) == -1)
                    {
                        fprintf(stderr,"Failed to Read from The File %s ... \n",initialzeupload_1_arg.FileName);
                        return;
                    }
                    putfile_1_arg.size = output;
                    bytesSended += output;
                    result_4 = putfile_1(&putfile_1_arg, clnt);

                    if(bytesSended == FileLenght)
                    {
                        fclose(file);
                        printf("File Sended Successfully ... \n");
                        printf("bytes Sended : %d , File Lenght : %d \n",bytesSended,FileLenght);
                        printf("End of Transsmition ... \n");
                        return;
                    }
                }
                
    break;
    case 3 :
                strcpy(listdirectory_1_arg.FileName,FilePath);
                result_6 = listdirectory_1(&listdirectory_1_arg, clnt);
                if(!*result_6)
                {
                    fprintf(stderr,"Directory Not found ... \n");
                    return;
                }
    break;

    case 4 :
                strcpy(changedirectory_1_arg.FileName,FilePath);
                result_5 = changedirectory_1(&changedirectory_1_arg, clnt);
                if(!*result_5)
                {
                    fprintf(stderr,"Directory Not found ... \n");
                    return;
                }
    break;
    case 5 :
                strcpy(removefile_1_arg.FileName,FilePath);
                result_7 = removefile_1(&removefile_1_arg, clnt);
                if(!*result_7)
                {
                    fprintf(stderr,"Directory Not found ... \n");
                    return;
                }
    break;
}

	
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int main (int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr,"Not Enough Parameters ... \n");
		exit(EXIT_FAILURE);
	}	
	char *host;
	char FilePath[20];
	int option;
	host = argv[1];

	while(1)
	{
		printf("------------------------ Select One of The Available Options ------------------------ \n");
		printf("1 - Download a File from The Server ... \n");
		printf("2 - Upload a File to The Server ... \n");
		printf("3 - List The Content of The Server ... \n");
		printf("4 - Change The Directory inside The Server ... \n");
		printf("5 - Remove a File in The Server  ... \n");
		printf("6 - Quit ...");
		printf("----------------------------------------------------------------------------------------\n");
		printf("Enter Your Choise : ");
		scanf("%d",&option);
		
		switch (option)
		{
		case 1:		printf("Enter The Name of The File that you Want to Download   :  ");
					scanf("%s",FilePath);
					ftpserverprogram_1 (host,1,FilePath);                    
			break;
		case 2:		printf("Enter The Name of The File that you Want to Upload     :  ");
					scanf("%s",FilePath);
					ftpserverprogram_1 (host,2,FilePath);			
			break;
		case 3:		printf("Enter The Name of The Directory That You Want to list  :  ");
					scanf("%s",FilePath);
					ftpserverprogram_1 (host,3,FilePath);			
			break;
		case 4:		printf("Enter The Name of The Directory  :  ");
					scanf("%s",FilePath);
					ftpserverprogram_1 (host,4,FilePath);
			break;
		case 5:		printf("Enter The Name of The File That you Want to remove   :  ");
					scanf("%s",FilePath);
					ftpserverprogram_1 (host,5,FilePath);			
			break;
		case 6:
					printf("Good Bye See You The Next Time ... \n");
					exit(EXIT_SUCCESS);
			break;							
		default:	printf("Please Enter one of The Available Options  ... \n");					
			break;
		}
	}

	return 0;
}