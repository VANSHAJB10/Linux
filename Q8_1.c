#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main(){
	int fd1;
	char * path = "/home/rex100/Desktop/myfifo";
	mkfifo(path,0666);
	char str1[80],str2[80];
	while(1){
		fd1 = open(path,O_WRONLY);
		fgets(str1,30,stdin);
		write(fd1,str1,strlen(str1)+1);
		close(fd1);

		fd1 = open(path,O_RDONLY);
		read(fd1,str2,sizeof(str2));
		printf("QUES1 %s\n",str2);
		close(fd1);
	}
}
