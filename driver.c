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
  ui_init();
  //make matrix && calculate pagerank
  char *addr = argv[1];
  construct_matrix(addr);
  //make_matrix(argv[1]);
  //while running:
  while(true) {
    char* message = ui_read_input();
    //find entry point page (matching title)
    if (strcmp(message, "quit") == 0) {
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
      char* output_message = strcat(message, " is not known to The Avengers");
      ui_add_message(NULL, output_message);
      ui_clear_input();
      free(message);
      continue;
    }
    //repeat to allow for new search or quit
  }
}
