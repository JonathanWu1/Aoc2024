#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int isUnSafe(int values[], int valueCount){
	if(valueCount > 2){
		int d = values[0] - values[1];
		int direction = 0;
		if(d < 0){
			direction = -1;
		}
		else if(d > 0){
			direction = 1;
		}

		if(direction == 0){
			return 1;
		}
		else{
			for(int i = 0; i < valueCount - 1; i++){
				int diff = values[i] - values[i+1];
				/*printf("%d, %d %d %d\n", i, values[i], values[i+1], diff);*/
				if(abs(diff) > 3 || abs(diff) < 1 || diff/direction <= 0){
					return 1;
				}
			}
		}
	}
	else{
		return 1;
	}
	return 0;
}
int main(){
	system("cls");
	FILE *file = fopen("input.txt", "r");

	if(file == NULL){
		return 0;
	}

	char ch[100], chCopy[5];
	int values[10] = {0}, valuesCopy[10] = {0};
	int intIndex, spaceIndex, valueIndex, valueCount, value, unsafeCount = 0, lineCount = 0, potentiallyUnsafe = 0, storedValue = 0, skipIndex = 0;
	int unsafe = 0;;
	while((fgets(ch, sizeof(ch), file))){
		printf("====================== \n");
		intIndex = 0;
		spaceIndex = 0;
		valueIndex = 0;
		valueCount = 0;
		potentiallyUnsafe = 0;
		unsafe = 0;
		skipIndex = 0;
		char *token = strtok(ch, " ");
		while (token != NULL) {
			values[valueIndex] = atoi(token);
			valueCount++;
			valueIndex++;
			token = strtok(NULL, " ");
		}
		for(int i = 0; i < valueCount; i++){
			printf("%d ", values[i]);
		}

		printf("\n-----------------\n");
		lineCount++;

		unsafe = isUnSafe(values, valueCount);
		if(unsafe == 1){
			printf("unsafe");
		}
		for(int i = 0; i < valueCount ; i++){
			printf("%lli", sizeof(values));
			printf("\n-----------------\n");

			for(int j = 0; j < valueCount; j++){
				valuesCopy[j] = values[j];
			}

			for(int j = skipIndex; j< valueCount -1; j++){
				valuesCopy[j] = values[j+1];
			}
			for(int j = 0; j < valueCount; j++){
				printf("%d ", valuesCopy[j]);
			}
			printf("\n");
			int b = isUnSafe(valuesCopy, valueCount -1);
			printf("%d \n", b);
			unsafe *= isUnSafe(valuesCopy, valueCount -1);
			skipIndex++;
		}
		printf("unsafe: %d", unsafe);
		unsafeCount+= unsafe;

	}


	printf("total: %d \n", lineCount );
	printf("unsafe: %d \n", unsafeCount );
	printf("safe: %d \n", lineCount - unsafeCount);
	if (feof(file)) {
		printf("End of file reached.\n");
	} else if (ferror(file)) {
		printf("An error occurred.\n");
	}
}
