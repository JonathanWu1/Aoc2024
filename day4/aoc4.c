#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 200

int checkHorizontal(char **lines, int vpos, int hpos, char *search){
	unsigned int maxLength = strlen(lines[vpos]);
	unsigned int searchLength = strlen(search);

	if(maxLength - hpos < searchLength){
		return 0;
	}

	for(int searchPos = 0; searchPos < searchLength; searchPos++){
		if(search[searchPos] != lines[vpos][hpos]){
			return 0;
		}

		hpos++;
	}

	return 1;
}

int checkVertical(char **lines, int lineCount, int vpos, int hpos, char *search){

	unsigned int searchLength = strlen(search);

	if(lineCount - vpos < searchLength){
		return 0;
	}

	for(int searchPos = 0; searchPos < searchLength; searchPos++){
		if(search[searchPos] != lines[vpos][hpos]){
			return 0;
		}

		vpos++;
	}

	return 1;
}

int checkDiagonalLeft(char **lines, int lineCount, int vpos, int hpos, char *search){
	unsigned int searchLength = strlen(search);

	for(int searchPos = 0; searchPos < searchLength; searchPos++){

		if(vpos >= lineCount || hpos < 0 || search[searchPos] != lines[vpos][hpos]){
			return 0;
		}

		hpos--;
		vpos++;
	}

	return 1;
}

int checkDiagonalRight(char **lines, int lineCount, int vpos, int hpos, char *search){
	if(vpos >= lineCount){
		return 0;
	}

	unsigned int maxLength = strlen(lines[vpos]);
	unsigned int searchLength = strlen(search);

	if(lineCount - vpos < searchLength || maxLength - hpos < searchLength){
		return 0;
	}

	for(int searchPos = 0; searchPos < searchLength; searchPos++){
		if(search[searchPos] != lines[vpos][hpos]){
			return 0;
		}

		hpos++;
		vpos++;
	}


	return 1;
}


int main() {
	FILE *file = fopen("input.txt", "r");
	if (file == NULL) {
		printf("Unable to open file");
		return EXIT_FAILURE;
	}

	int capacity = INITIAL_CAPACITY;

	size_t lineLength = 0;
	size_t nread = 0;
	char *line;

	char **lines = malloc(capacity * sizeof(char *));
	int lineCount = 0;

	while ((nread = getline(&line, &lineLength, file)) != -1) {
		if (lineCount == capacity) {
			capacity *= 1.5;
			char **temp = realloc(lines, capacity);
			if (!temp) {
				perror("Failed to reallocate memory");
				free(line);
				for (size_t i = 0; i < lineCount; i++)
					free(lines[i]);
				free(lines);
				fclose(file);
				return EXIT_FAILURE;
			}
			lines = temp;
		}
		lines[lineCount] = malloc(nread);
		strncpy(lines[lineCount], line, nread - 1);
		lineCount++;
	}

	printf("\n");
	bool **lineColors = malloc(capacity * sizeof(bool *));
	for (int i = 0; i < lineCount; i++) {
		lineColors[i] = malloc(lineLength);
		for (int j = 0; j < lineLength; j++) {
			lineColors[i][j] = false;
		}
	}

	printf("\n");

	int count = 0;
	//int hcount = 0, vcount = 0, dlcount = 0, drcount = 0;

	int dr, dl;

	for (int i = 0; i < lineCount; i++) {
		for (int j = 0; j < strlen(lines[i]); j++) {
			dr = 0;
			dl = 0;
			//hcount += checkHorizontal(lines, i , j, "XMAS");
			//hcount += checkHorizontal(lines, i , j, "SAMX");

			//vcount += checkVertical(lines, lineCount, i , j, "XMAS");
			//vcount += checkVertical(lines, lineCount, i , j, "SAMX");

			dl += checkDiagonalLeft(lines, lineCount, i , j+2, "MAS");
			dl += checkDiagonalLeft(lines, lineCount, i , j+2, "SAM");

			dr += checkDiagonalRight(lines, lineCount, i, j, "SAM");
			dr += checkDiagonalRight(lines, lineCount, i, j, "MAS");

			if(dl > 0 && dr > 0){
				count++;
			}
		}
	}

	printf("XMAS: %d\n", count);

	count = 0;
	return EXIT_SUCCESS;
}
