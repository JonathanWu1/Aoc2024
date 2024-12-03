#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(){
	system("cls");
	FILE *file = fopen("input.txt", "r");

	if(file == NULL){
		return 0;
	}

	int c, firstInt, nextInt;
	char *ch = (char *)malloc(sizeof(char));
	char *nextCh = (char *)malloc(sizeof(char));
	int tenths = 1, countUnsafe = 0, diff = 0, val=0, countLine = 1;
	int *preVal = (int *)malloc(sizeof(int)), *direction = (int *)malloc(sizeof(int));

	preVal = NULL;
	direction = NULL;
	bool goNextLine = false, isUnsafe = false;

	while((c = getc(file)) != EOF){
		*ch = (char) c;
		
		if(goNextLine && c != '\n'){
			continue;
		}
		else if(*ch == '\n'){
			if(goNextLine == false){
				diff = *preVal - val;
				printf("diff: %d %d %d\n", diff, *preVal, val);
				if(abs(diff) > 3 || abs(diff) < 1 || diff * *direction <= 0){
					countUnsafe++;
				}
			}

			preVal = NULL;
			val = 0;
			tenths = 1;
			goNextLine = false;
			isUnsafe = false;
			countLine++;
			direction = NULL;
			
			printf("=======================\n");
		}
		else if(!isdigit(*ch)){
			if(preVal == NULL){
				printf("preVal was null\n");
				printf("val: %d \n", val);
				preVal = (int *) malloc(sizeof(int));
			}
			else{
				diff = *preVal - val;
				printf("diff: %d %d %d\n", diff, *preVal, val);
				if(direction == NULL){
					direction = (int *) malloc(sizeof(int));
					if(diff < 0){
						*direction = -1;
					}
					else if(diff > 0){
						*direction = 1;
					}
					else{
						*direction = 0;
					}
				}

				printf("direction: %d\n", *direction);

				if(abs(diff) > 3 || abs(diff) < 1 || diff * *direction <= 0){
					countUnsafe++;
					printf("found unsafe %d\n", countUnsafe);
					goNextLine = true;
					isUnsafe = true;
					continue;
				}

				printf("found safe\n");
			
			}

			*preVal = val;
			val = 0;
			tenths = 1;
		}
		else{
			val = ((val *tenths) + (*ch - '0'));
			tenths*=10;
		}
		printf("-------\n");
	}

	printf("count: %d", (countLine - countUnsafe));
	return 0;
}
