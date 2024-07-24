#include<stdio.h>
//#include<conio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
	const char* sourceFile = "source.txt";
	const char* destinationFile = "destination.txt";
       	int source_fd = open(sourceFile, O_RDONLY);
	if(source_fd== -1){
		perror("Error opening source file.");
		return 1;
	}
	int dest_fd = open(destinationFile, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(dest_fd == -1){
		perror("Error opening dest file.");
		return 1;
	}
	char buffer[4096];
	ssize_t bytes_read;
	while((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0){
		ssize_t bytes_written = write(dest_fd, buffer, bytes_read);
		if(bytes_written != bytes_read){
			perror("Error writing to dest file.");
			close(source_fd);
			close(dest_fd);
			return 1;
		}
	}
	close(source_fd);
	close(dest_fd);
	printf("file copied ");
	return 0;
}
		

			
	

