
struct data{
char buffer[25000];
int size;
};

typedef struct data data;

struct Path
{
char FileName[20];
};

typedef struct Path Path;

program FTPServerProgram
{
version version1
{
	int initialzeDownload(Path)=1;
	void initialzeUpload(Path)=2;
	data getFile()=3;
	void putFile(data)=4;	
	int changeDirectory(Path)=5;
	int listDirectory(Path)=6;	
	int removeFile(Path)=7;
}=1;

}=0x20000001;
