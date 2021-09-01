#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*
struct Map {
  struct Key key;
  struct Value value;
};  

struct Key {
    struct point p1;
    struct point p2;
    int i;
    int j;
};

int get_hash(Key *key){
    int result;
    result = key->i * key->i + (key->p1.x * key->p1.x) - (key->p2.x * key->p2.x)
    return (result % SIZE_OF_MAP);
}
*/
int main(void) { 
  FILE *file;
  char filename[200];
  char *newLine = NULL;
  size_t len = 0;
  ssize_t read;
  char *opCode;
 // struct Map map[SIZE_OF_MAP];

 // gets(filename);
  file = fopen("testcase.text","r");
  if (file == NULL) {
    exit(EXIT_FAILURE);
  }  
  while ((read = getline(&newLine, &len, file)) != -1) { 
    printf("%s", newLine);	  
    opCode = strtok(newLine, " ");

    if(strcmp("mov", opCode) == 0){
      char *reg = strtok(NULL, " ");	    
      char *constant = strtok(NULL, " ");
     /*  
      printf("%s ", opCode);
      printf("%s ", reg);
      printf("%s", constant); */
    }		    
  }
  for(int i = 0; i <= 9; i++){
    printf("register 0x%d: %p\n",i,&i);
  }	  
  for(char i = 'A'; i <= 'F'; i++){
    printf("register 0x%c: %p\n",i,&i); 
  }	  
  fclose(file);
  if(newLine)
    free(newLine);
  exit(EXIT_SUCCESS);
  return 0; 
   
}

//void mov(char *reg, char *constant){
  


