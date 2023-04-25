#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main(){
	int fd1;
	char *path = "/home/rex100/Desktop/myfifo";
	mkfifo(path,0666);
	char str1[80],str2[80];
	while(1){
		fd1 = open(path,O_RDONLY);
		read(fd1,str1,40);
		printf("QUES1A %s\n",str1);
		close(fd1);

		fd1 = open(path,O_WRONLY);
		fgets(str2,30,stdin);
		write(fd1,str2,strlen(str2)+1);
		close(fd1);
}
	return 0 ;
}
