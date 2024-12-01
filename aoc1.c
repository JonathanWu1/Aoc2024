#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct node{
	int value;
	struct node * next;
	struct node * prev;
} node_t;

node_t* next(node_t node){
	return node.next;
}

int findMin(int* col[], int size){
	if(size <= 0){
		return -1;
	}

	int minValue = INT_MAX;
	int minIndex = -1;
	for(int i = 0; i < size; i++){
		if(col[i] == NULL){
			continue;
		}
		else if(*col[i] < minValue){
			minValue = *col[i];
			minIndex = i;
		}
	}


	if(minIndex != -1){
		col[minIndex] = NULL;
	}

	return minValue;
}


int main(){
	FILE *file = fopen("input.txt", "r");

	char buffer[100];

	int* col1[1000] ={0};
	int* col2[1000] ={0};

	int sizeOccr = 100000;
	int col1copy[1000] = {0};
	int col2Occr[100000] = {0};

	char line[15];
	int rowIndex = 0;
	while(fgets(line, sizeof(line), file)){
		char* a = strtok(line, " ");
		col1[rowIndex] = (int*)malloc(sizeof(int));
		*col1[rowIndex] = atoi(a);
		col1copy[rowIndex] = atoi(a);
		a = strtok(NULL, " ");
		col2[rowIndex] = (int*)malloc(sizeof(int));
		*col2[rowIndex] = atoi(a);
		rowIndex++;
	}

	int distance = 0;
	for(int i = 0; i<1000; i++){
		int minCol1 = findMin(col1, 1000);
		int minCol2 = findMin(col2, 1000);

		col2Occr[minCol2] += 1;

		distance += abs(minCol1 - minCol2);
	}
	printf("%d\n", distance);

	int occurance = 0;
	for(int i = 0; i < 1000; i++){
		if(col2Occr[col1copy[i]] == 0){
			continue;
		}
		/*printf("%d %d\n", col1copy[i], col2Occr[col1copy[i]]);*/
		occurance += col1copy[i] * col2Occr[col1copy[i]];
		printf("%d %d\n", i, occurance);
	}
	
	printf("------");
	printf("%d", occurance);


	fclose(file);
	return 0;
}
