#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void printRegisters();
void mov(char *reg, char *constant);
char registerReturn(char *opCode);

char *R0, *R1, *R2, *R3, *R4, *R5, *R6, *R7, *R8, *R9, *R10, *R11, *R12, *R13, *R14, *R15, *R16, *RPC;

int main(void) { 
  FILE *file;
  char filename[200];
  char *newLine = NULL;
  size_t len = 0;
  ssize_t read;
  char *opCode;

 // gets(filename);
  file = fopen("testcase.text","r");
  if (file == NULL) {
    exit(EXIT_FAILURE);
  }  
  while ((read = getline(&newLine, &len, file)) != -1) { 
    printf("%s", newLine);	  
    opCode = strtok(newLine, " ");
    if(strcmp("beq", opCode) != 0 && strcmp("b", opCode) !=0) {
      char *reg = strtok(NULL, " ");	    
      if(strcmp("R1", reg) == 0)
        	      
    }


    if(strcmp("mov", opCode) == 0){
      char *constant = strtok(NULL, " ");
      if(reg
      mov(reg, constant);
    }
    else if (strcmp("ldr", opCode) == 0) {

    }
    else if (strcmp("ldi", opCode) == 0) {

    }
    else if (strcmp("str", opCode) == 0) {

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

  fclose(file);

  if(newLine)
    free(newLine);
  exit(EXIT_SUCCESS);
  return 0; 
   
}
char registerReturn(char *registerVal) {

}	

void mov(char *reg, char *constant) {
  reg = constant;
	
}









void printRegisters(){
  printf("register 0x0: %s\n",R0);
  printf("register 0x1: %s\n",R1);
  printf("register 0x2: %s\n",R2);
  printf("register 0x3: %s\n",R3); 
  printf("register 0x4: %s\n",R4);
  printf("register 0x5: %s\n",R5);
  printf("register 0x6: %s\n",R6);
  printf("register 0x7: %s\n",R7);
  printf("register 0x8: %s\n",R8);
  printf("register 0x9: %s\n",R9);
  printf("register 0xA: %s\n",R11);
  printf("register 0xB: %s\n",R12);
  printf("register 0xC: %s\n",R13);
  printf("register 0xD: %s\n",R14);
  printf("register 0xE: %s\n",R15);
  printf("register 0xF: %s\n",R16);
  printf("register  PC: %s\n",RPC);

}	
