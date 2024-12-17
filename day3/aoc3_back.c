#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KNRM  "\x1B[0m"

int allTokens = 0;
int globalSum = 0;
int getNumber(char* numberStr){
  if(numberStr == NULL || strlen(numberStr) < 1 || strlen(numberStr) > 3){
    return -1;
  }
  bool isNumber = true;
  for(unsigned int j = 0; j<strlen(numberStr); j++){
    if(!isdigit(numberStr[j])){
      isNumber = false;
      break;
    }
  }

  if(isNumber){
    return atoi(numberStr);
  }

  return -1;
}

int tokenizeLine(char* line, size_t len){
  char *token;
  char **tokens = malloc(sizeof(char*) * (len + 1));
  char *savePtr;

  token = strtok_r(line, "m", &savePtr);
  int tokensIndex = 0;
  char *number = malloc(len);
  char *tokencopy = malloc(4);
  int num1, num2, sum = 0;
  bool isNumber = false;

  while(token != NULL){
    if(strlen(token) > 3 && token[0] == 'u' && token[1] == 'l' && token[2] == '('){
      tokens[tokensIndex] = malloc(strlen(token) + 1);
      if(tokens[tokensIndex] == NULL){
        perror("failed to allocate memory");
        return 0;
      }
      strcpy(tokens[tokensIndex], token+3);
      tokensIndex++;
    }
    token = strtok_r(NULL, "m", &savePtr);
  }

  
  for(unsigned int i = 0; i < tokensIndex; i++){
    num1 = -1;
    num2 = -1;
    number = strtok(tokens[i], ",");
    num2 = getNumber(number);
    number = strtok(NULL, ")");
    num1 = getNumber(number);


    if(num1 != -1 && num2 != -1){
      sum += num1 * num2;
    }
  }

  return sum;
}


int tokenizeLine_1(char* line, size_t len){
  char *token, *temp, *temp1;
  char **tokens = malloc(sizeof(char*) * (len + 1));
  char *savePtr;

  token = strtok_r(line, "d", &savePtr);
  int tokensIndex = 0;
  char *number = malloc(len);
  char *tokencopy = malloc(4);
  int num1, num2, sum = 0, prevSum;
  bool isNumber = false, multiply = true;
  
  while(token != NULL){
    printf("---------\n");

    if(strlen(token) > 6){
      temp = malloc(7);
      strncpy(temp, token, 6);
      temp[6]= '\0';
      if(strcmp(temp, "on't()") == 0){
        multiply = false;
      }
      free(temp);
    }

    if(strlen(token) > 3){
      temp1 = malloc(4);
      strncpy(temp1, token, 3);
      temp1[6]= '\0';
      if(strcmp(temp1, "o()") == 0){
        multiply = true;
      }
      free(temp1);
    }

    
    prevSum = globalSum;
    if(multiply){
      allTokens++;
      sum = tokenizeLine(token, strlen(token));
      globalSum+=sum;
      printf(KGRN "Sum:%d\n%s\n\n" KNRM, sum,token);
    }
    else{
      printf(KRED "%s\n\n" KNRM, token);
    }
    printf("GlobalSum: %d Sum:%d Change: %d\n", globalSum, sum,globalSum - prevSum);

    token = strtok_r(NULL, "d", &savePtr);
  }

  return sum;
}

int main() {
  FILE *file = fopen("input.txt", "r");

  if (file == NULL) {
    printf("Unable to open file");
    return 0;
  }

  char *line;
  size_t len = 0;
  ssize_t read;
  char *chars;
  char *token, *commaToken, *bracketToken, *num1Char, *num2Char;
  char *a = malloc(3), *b = malloc(3);
  unsigned long indexComma = 0, indexBracket = 0;
  unsigned long total = 0;

  bool isValid = false;
  while ((read = getline(&line, &len, file)) != -1) {
       tokenizeLine_1(line, len);
  }
  printf("Sum: %d\n", globalSum);
}
