#include "ftp.h"
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static FILE *file;
static int FileLenght,ByteSended=0,ByteReceived=0,output=0,SizeMax=25000;

int * initialzedownload_1_svc(Path *argp, struct svc_req *rqstp)
{
	static int  result = 1;
	struct stat st;
	memset(&st,'0',sizeof(st));
	if(stat(argp->FileName,&st) == -1)
	{
		result = 0; 
		return &result;
	}
	if((file = fopen(argp->FileName,"r")) == NULL)
	{
		fprintf(stderr,"Failed to open The File ...\n");
		exit(EXIT_FAILURE);
	}
	printf("Starting Transmission The File %s ...\n",argp->FileName);	
	fseek(file,0,SEEK_END);
	FileLenght = ftell(file);
	fseek(file,0,SEEK_SET);
	printf("The size of The File is %d \n",FileLenght);
	return &result;
}

void * initialzeupload_1_svc(Path *argp, struct svc_req *rqstp)
{
	static char * result;
	if((file = fopen(argp->FileName,"w+")) == NULL)
	{
		fprintf(stderr,"Failed to Create The File ... \n");
		exit(EXIT_FAILURE);
	}
	printf("Starting Receiving The File %s ...\n",argp->FileName);	
	return (void *) &result;
}

data * getfile_1_svc(void *argp, struct svc_req *rqstp)
{
	static data  result;
	if(file != NULL)
	{		
		if(FileLenght-ByteSended < SizeMax)
		{
			SizeMax = FileLenght-ByteSended;			
		}
		if((output = fread(result.buffer,1,SizeMax,file)) != SizeMax)
		{
			fprintf(stderr,"Failed to read from The File ...\n");
			exit(EXIT_FAILURE);
		}
		result.size = output;
		ByteSended += output;

		if(ByteSended == FileLenght)
		{
			fclose(file);
			ByteSended = 0;
			printf("File Sended Successfully ... \n");
			printf("bytes Sended : %d , bytes Received : %d ...\n",ByteSended,FileLenght);
			printf("End of Transsmition ... \n");
		}
	}
	return &result;
}

void * putfile_1_svc(data *argp, struct svc_req *rqstp)
{
	static char * result;
	if(file != NULL)
	{
		if((output = fwrite(argp->buffer,1,argp->size,file)) != SizeMax)
		{
			fprintf(stderr,"Failed to write from The File ...\n");
			exit(EXIT_FAILURE);
		}
		ByteReceived += output;
		if(output < SizeMax)
		{
			fclose(file);
			ByteReceived = 0;
			printf("File Received Successfully ... \n");
			printf("Total bytes Received : %d  ...\n",ByteReceived);
			printf("End of Transsmition ... \n");
		}
	}
	

	return (void *) &result;
}

int * changedirectory_1_svc(Path *argp, struct svc_req *rqstp)
{
	static int  result = 1;
	struct stat st;
	memset(&st,'0',sizeof(st));
	if(stat(argp->FileName,&st) == -1)
	{
		result = 0;
		return &result;
	}
	char command[30];
	sprintf(command,"cd %s",argp->FileName); 
	system(command);
	return &result;
}

int * listdirectory_1_svc(Path *argp, struct svc_req *rqstp)
{
	static int  result = 1;
	struct stat st;
	memset(&st,'0',sizeof(st));
	if(stat(argp->FileName,&st) == -1)
	{
		result = 0;
		return &result;
	}
	char command[30];
	sprintf(command,"ls %s",argp->FileName); 
	system(command);
	return &result;
}

int * removefile_1_svc(Path *argp, struct svc_req *rqstp)
{
	static int  result = 1;
	struct stat st;
	memset(&st,'0',sizeof(st));
	if(stat(argp->FileName,&st) == -1)
	{
		result = 0;
		return &result;
	}
	char command[30];
	sprintf(command,"rm  %s",argp->FileName); 
	system(command);
	
	return &result;
}