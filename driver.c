#include <stdio.h>
#include <stdbool.h>

#include "matrix.h"
#include "ui.h"

#define BUFFER_SIZE 128
#define NUM_RESULTS 8

int main(int argc, char* argv[]) {
  int num_results = NUM_RESULTS;
  if (argc == 3) {
    num_results = strtoi(argv[2]);
  }
  else if (argc != 2) { //the third is an optional parameter
		perror("Invalid syntax: driver [filename] (num_results)\n");
		exit(2);
	}
  ui_init();
  //make matrix && calculate pagerank
  make_matrix(argv[1]);
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
    /*else if input in list_of_names {
      //while num_results < desired:
        //for each nth-level connection: //small dataset means we may move beyond first
          //arrange in order of pagerank within level
      //print results (links preferably)
    }*/
    else {
      printf(input);
      printf(" is not known to The Avengers");
      continue;
    }
    //repeat to allow for new search or quit
  }
}
