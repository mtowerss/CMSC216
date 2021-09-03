#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void printRegisters();
void printMemory();
void mov(char *reg, char *constant);
void ldr(char *reg, int memLocation);
void ldi(char *reg1, char *reg2);
void str(char *reg, int memLocation);
char registerReturn(char *opCode);
char *defaultVal = "0x000000000000";
char *R0, *R1, *R2, *R3, *R4, *R5, *R6, *R7, *R8, *R9, *R10, *R11, *R12, *R13, *R14, *R15, *R16, *RPC;
char values[17][15];
char memory[65][15];
  
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
  char filename[200];
  char *newLine = NULL;
  size_t len = 0;
  ssize_t read;
  char *opCode;

  fillMemory();
  fillValues();
 // gets(filename);
  file = fopen("testcase.text","r");
  if (file == NULL) {
    exit(EXIT_FAILURE);
  }  
  while ((read = getline(&newLine, &len, file)) != -1) { 
    printf("%s", newLine);	  
    opCode = strtok(newLine, " ");
    char *reg = strtok(NULL, " ");	    

    if(strcmp("mov", opCode) == 0){
      char *constant = strtok(NULL, " ");
      mov(reg, constant);
    }
    else if (strcmp("ldr", opCode) == 0) {
      char *memLocation = strtok(NULL, " ");
      int location = atoi(memLocation);
      ldr(reg, location);
    }
    else if (strcmp("ldi", opCode) == 0) {
      char *reg2 = strtok(NULL, " ");
      ldi(reg, reg2);      
    }
    else if (strcmp("str", opCode) == 0) {
      char *memLocation = strtok(NULL, " ");
      int location = atoi(memLocation);
      str(reg, location);
    }	    
    else if (strcmp("sti", opCode) == 0) {

    }
    else if (strcmp("add", opCode) == 0) {

    }
    else if (strcmp("mul", opCode) == 0) {

    }
    else if (strcmp("cmp", opCode) == 0) {

    }
    else if (strcmp("b", opCode) == 0) {

    }
    else if (strcmp("beq", opCode) == 0) {

    }
  }
  printRegisters();
  printMemory();
  fclose(file);
  
      

  if(newLine)
    free(newLine);
  exit(EXIT_SUCCESS);
  return 0; 
   
}

void mov(char *reg, char *constant) {
  for(int i = 0; i < 17; i++){
    values[((int)reg[1])-48][i] = constant[i];
  }	    
 // values[(int)reg[1]] = constant;
	
}

void ldr(char *reg, int memLocation) {
  for(int i = 0; i < 15; i++){	  
    values[((int)reg[1])-48][i] = memory[memLocation][i];
  }    
}

void ldi(char *reg, char *reg2) {
  int reg3 = atoi(reg);
  int reg4 = atoi(reg2);  
  for(int i = 0; i < 15; i++) {
    values[reg3][i] = values[reg4][i];	  
  }
}

void str(char *reg, int memLocation) {
  for(int i = 0; i < 15; i++){	  
    memory[memLocation][i] = values[((int)reg[1])-48][i] ;
  }    
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
