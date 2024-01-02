#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *DELIM = "(,";

typedef struct {
  int *array;
  size_t used;
  size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, char *element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(char));
  }
  a->array[a->used++] = element;
}

void insertArrayRoom(Array *a, room* element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(long));
  }
  a->array[a->used++] = element;
}

typedef struct room { 
  Array *connections;
  int data;
  char *item;
} room;

/*void addNeighbor(struct room* newRoom){
  room -> neighbors = (struct room)realloc(neighors,10*sizeof(struct room));
  neighbors[position] = newRoom;
  room -> position = position+=1;
}; */

  room* newRoom(char *item){
    room* room = (struct room*)malloc(sizeof(struct room));
    room -> item = item;
    initArray(room->connections, 10);
  return (room);
}

int main() {
  const long MAX_LINE_SIZE = 255; 
  char buffer[MAX_LINE_SIZE];
  char rooms[MAX_LINE_SIZE];
  printf("Enter rooms, input 0 to stop\n");
  while(buffer[0] != '0'){
      fgets(buffer, MAX_LINE_SIZE-1, stdin);
      char *output = strtok(buffer," (");

      printf("Room %s", output);
      struct room *userRoom = newRoom(output);
      Array *rooms;
      initArray(rooms, 10);
      insertArrayRoom(rooms, userRoom);
     // while(output != NULL && output[strlen(output)-1] != ')'){
       for(int i = 0; output != NULL; i++){
        output = strtok(NULL, "(, )");  
        printf("\nNeighbors %s", output);
        insertArray(userRoom->connections, output);
        }
        //output = strtok(NULL, " ");
        printf(" Item %s\n", output); 
      //  printf("%s",userRoom->connections[0]);    
      //struct room* root = newRoom(buffer);

      //puts(buffer);
  }
  printf("Enter starting room number, followed by end room (seperated by comma)\n");
  fgets(buffer, MAX_LINE_SIZE-1, stdin);
  char *val1 = strtok(buffer, ",");
  char *val2 = strtok(NULL," ");
  printf("You chose to start in room %s and end in room %s.", val1,val2);   

}
