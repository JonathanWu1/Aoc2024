#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *file = fopen("input.txt", "r");

	if(file == NULL){
		printf("Unable to open file");
		return 0;
	}

	char* line;
	size_t len = 0;
	ssize_t read;
	read = getline(&line, &len, file);
	while((read = getline(&line, &len, file)) != -1){

	}

}
