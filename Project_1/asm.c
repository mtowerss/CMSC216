#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void printRegisters();
void printMemory();
void mov(char *reg, char *constant);
void ldr(char *reg, char *memLocation);
void ldi(char *reg1, char *reg2);
void str(char *reg, char *memLocation);
void sti(char *reg1, char *reg2);
void add(char *reg1, char *reg2, char *reg3);
void cmp(char *reg, char *reg2);
void b(char *constant);
void beq(char *constant);
char *defaultVal = "0x000000000000";
char values[17][15];
char memory[65][15];
int pointer = 0;  
int COMPARE_FLAG = 0;

void fillMemory(){
	for(int i = 0; i < 64; i++){
	  for(int j = 0; j < 12; j++){
	    memory[i][j] = defaultVal[j];
	  }
	}
}	

void fillValues(){
	for(int i = 0; i < 17; i++){
	  for(int j = 0; j < 12; j++){
	    values[i][j] = defaultVal[j];
	  }
	} 
}

int main(void) { 
  FILE *file;
  char *newLine = NULL;
  size_t len = 0;
  ssize_t read;
  char fileInstructions[64][25] = {};
  FILE *fp;  
  int count = 0;
  char *opCode;

  fillMemory();
  fillValues();
 // gets(filename);
  file = fopen("testcase.text","r");
  fp = fopen("testcase.text","r");

  if (file == NULL) {
    exit(EXIT_FAILURE);
  }  
  for(int i=0; i<64; i++) {
        for(int j=0; j<25; j++) {
            fscanf(fp,"%c",&fileInstructions[i][j]);
   	}

  }

    while ((read = getline(&newLine, &len, file)) != -1) { 
      printf("%s", newLine);
      for(int i = 0; i < strlen(newLine); i++){
        fileInstructions[count][i] = newLine[i];	
      }	      
      count++;
    }
  for(pointer = 0;pointer < count; pointer++){

    char splitStrings[10][10]; 
    int i, j, cnt;
    j = 0;
    cnt = 0;
    for (i = 0; i <= (strlen(fileInstructions[pointer])); i++) {
        if (fileInstructions[pointer][i] == ' ' || fileInstructions[pointer][i] == '\0') {
            splitStrings[cnt][j] = '\0';
            cnt++; 
            j = 0; 
        }
        else {
            splitStrings[cnt][j] = fileInstructions[pointer][i];
            j++;
        }
    }
    opCode = splitStrings[0];
    printf("%s", opCode);
    for(int i = 0; opCode[i]; i++){
      opCode[i] = tolower(opCode[i]);
    }    

    if(strcmp("mov", opCode) == 0){
      mov(splitStrings[1], splitStrings[2]);
    }
    else if (strcmp("ldr", opCode) == 0) {
      ldr(splitStrings[1], splitStrings[2]);
    }
    else if (strcmp("ldi", opCode) == 0) {
      ldi(splitStrings[1], splitStrings[2]);      
    }
    else if (strcmp("str", opCode) == 0) {
      str(splitStrings[1], splitStrings[2]);
    }	    
    else if (strcmp("sti", opCode) == 0) {
      sti(splitStrings[1], splitStrings[2]);  
    }
    else if (strcmp("add", opCode) == 0) {
      add(splitStrings[1], splitStrings[2], splitStrings[3]);
    }
    else if (strcmp("mul", opCode) == 0) {

    }
    else if (strcmp("cmp", opCode) == 0) {
      cmp(splitStrings[1], splitStrings[2]);
    }
    else if (strcmp("b", opCode) == 0) {
      b(splitStrings[1]);
    }
    else if (strcmp("beq", opCode) == 0) {
      beq(splitStrings[1]);
    }
  }
  printf("%c", '\n');
  printRegisters();
  printMemory();
  fclose(file);
  
      
/*
  if(newLine)
    free(newLine);
  exit(EXIT_SUCCESS); */ 
  return 0; 
   
}

void mov(char *reg, char *constant) {
 // for(int i = 0; i < 17; i++){
 //   values[((int)reg[1])-48][i] = constant[i];
 // }	    
  char temp[13];
  int j = 0, val;
  char temp2;
  int tempNum;
  if(constant[0] == '-'){
    temp[0] = '-';	  
    j = 1;
    val = 3;
  } else { 
    val = 2;
  }    
	  
  for(int i = val; i < 13; i++){	  
    temp[j] = constant[i];
    j++;
  }   
  tempNum = (int)strtol(temp, NULL, 16);
  sprintf(temp, "%x", tempNum);

  j = 0;
  int length = 12 - strlen(temp); 
  for(int i = length; i < 12; i++){
    if(isalpha(temp[j])){
      temp2 = toupper(temp[j]);
      values[((int)reg[1])-48][i] = temp2;
    } else {
    values[((int)reg[1])-48][i] = temp[j];
    }    
    j++;
  }
  values[((int)reg[1])-48][12] = '\n';
}

void ldr(char *reg, char *memLocation) {
  int number = (int)strtol(memLocation, NULL, 16);
  for(int i = 0; i < 15; i++){	  
    values[((int)reg[1])-48][i] = memory[number][i];
  }    
}

void ldi(char *reg, char *reg2) {
  int reg3 = atoi(reg);
  int reg4 = atoi(reg2);  
  for(int i = 0; i < 15; i++) {
    values[reg3][i] = values[reg4][i];	  
  }
}

void str(char *reg, char *memLocation) {
  int number = (int)strtol(memLocation, NULL, 16);	
  char temp[13];
  int j = 0;
  char temp2;
  for(int i = 2; i < 12; i++){	  
    temp[j] = values[((int)reg[1])-48][i];
    j++;
  }    
  j = 0;
  int length = 13 - strlen(temp); 
  for(int i = length; i < 14; i++){
    if(isalpha(temp[j])){
      temp2 = toupper(temp[j]);
      memory[number][i] = temp2;
    } else {
    memory[number][i] = temp[j];
    }    
    j++;
  }
  memory[number][strcspn(memory[number], "\n")] = 0;
}

void sti(char *reg, char *reg2) {
  char *temp;
  if (reg[0] == 'R'){ 
    memmove(reg, reg+1, strlen(reg));
  }  
  if (reg2[0] == 'R'){ 
    memmove(reg2, reg2+1, strlen(reg2));
  }
  int tempNum = (int)strtol(values[atoi(reg2)], NULL, 16);
  sprintf(temp, "%x", tempNum);

//  printf("%s", temp); 
  int j = 0;
  for(int i = 12 - strlen(temp); i < 12; i++) {
    memory[tempNum][i] = temp[j];	  
  }
//  values[reg4][strcspn(values[reg4], "\n")] = 0;
}	

void add(char *reg, char *reg2, char *reg3){	
  memmove(reg, reg+1, strlen(reg));
  memmove(reg2, reg2+1, strlen(reg2));
  memmove(reg3, reg3+1, strlen(reg3));
  int val1 = (int)strtol(values[atoi(reg2)], NULL, 16); 
  int val2 = (int)strtol(values[atoi(reg3)], NULL, 16);
  int finalVal = val1 + val2;
  char newVal[9];
  sprintf(newVal, "%d", finalVal);
  int j =0;
  for(int i = 12 - strlen(newVal); i < 12; i++){
    values[atoi(reg)][i] = newVal[j];
    j++;  
  }  

}

void cmp(char* reg, char* reg2){
  memmove(reg, reg+1, strlen(reg));
  memmove(reg2, reg2+1, strlen(reg2));
  int val1 = (int)strtol(values[atoi(reg)], NULL, 16); 
  int val2 = (int)strtol(values[atoi(reg2)], NULL, 16);
  int *compare = &COMPARE_FLAG;
//  printf("%d" "%d", val1, val2);
  if(val1 == val2){
    *compare = 1; 	  
  }   	  

}	

void b(char *constant){
  memmove(constant, constant+2, strlen(constant));
  int *constantNum = &pointer;
  *constantNum = atoi(constant)-1;
//  printf("%d", pointer);
}	

void beq(char *constant){
  memmove(constant, constant+2, strlen(constant));
  int j = 0;
  if(COMPARE_FLAG != 0){
	  for(int i = 13 - strlen(constant); i < 13; i++){	  
	    values[16][i] = constant[j];
	    j++;
	  }
   int *newPoint = &pointer;
   printf("%d", atoi(constant));
   *newPoint = atoi(constant);  
   
   }
  //printf("%d",atoi(constant));	  
}	




void printMemory(){
  printf("%s","\n");	  
  for(int i = 0; i < 65; i++){
    if( i == 0) {
      printf("%s:  ", "0x00");      
    }	    
    if( i == 8) {
      printf("\n%s:  ", "0x08");      
    }
    if( i == 16) {
      printf("\n%s:  ", "0x10");      
    }
    if( i == 24) {
      printf("\n%s:  ", "0x18");      
    }
    if( i == 32) {
      printf("\n%s:  ", "0x20");      
    }
    if( i == 40) {
      printf("\n%s:  ", "0x28");      
    }
    if( i == 48) {
      printf("\n%s:  ", "0x30");      
    }
    if( i == 56) {
      printf("\n%s:  ", "0x38");      
    }
    if((i%8 == 0) && i != 0){
      printf("%s ", memory[i]);	    
    } else {  
      printf("%s ", memory[i]);
    }
  }  

}

void printRegisters(){
  printf("register 0x0: %s\n",values[0]);
  printf("register 0x1: %s",values[1]);
  printf("register 0x2: %s",values[2]);
  printf("register 0x3: %s\n",values[3]); 
  printf("register 0x4: %s\n",values[4]);
  printf("register 0x5: %s\n",values[5]);
  printf("register 0x6: %s\n",values[6]);
  printf("register 0x7: %s\n",values[7]);
  printf("register 0x8: %s\n",values[8]);
  printf("register 0x9: %s\n",values[9]);
  printf("register 0xA: %s\n",values[10]);
  printf("register 0xB: %s\n",values[11]);
  printf("register 0xC: %s\n",values[12]);
  printf("register 0xD: %s\n",values[13]);
  printf("register 0xE: %s\n",values[14]);
  printf("register 0xF: %s\n",values[15]);
  printf("register  PC: %s\n",values[16]);
}	
