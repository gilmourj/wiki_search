#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "matrix.h"
#include "ui.h"

#define BUFFER_SIZE 128
#define NUM_RESULTS 8

int main(int argc, char* argv[]) {
  int num_results = NUM_RESULTS;
  if (argc == 3) {
    num_results = atoi(argv[2]);
  }
  else if (argc != 2) { //the third is an optional parameter
		perror("Invalid syntax: driver [filename] (num_results)\n");
		exit(2);
	}
  //initialize UI
  //ui_init();
  //make matrix && calculate pagerank
  char *addr = argv[1];

  construct_matrix(addr);
  //make_matrix(argv[1]);
  char* names[NUM_PAGES];
  get_names(addr, names);
  //while running:
  while(true) {
    //query user input
    char input[BUFFER_SIZE];
    scanf("%s", input); // limit this to buffer size
    //find entry point page (matching title)
    if (strcmp(input, "quit") == 0) {
      ui_shutdown();
      return 0;
    }
    else {
      int index = 0;
      if (index != -1) {
        //while num_results < desired:
          //for each nth-level connection: //small dataset means we may move beyond first
            //arrange in order of pagerank within level
        //print results (links preferably)
      }
      else {
        printf("%s", input);
        printf(" is not known to The Avengers");
        continue;
      }
    }
    //repeat to allow for new search or quit
  }
}
