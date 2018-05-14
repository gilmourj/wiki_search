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
	//appropriately sized vector for pageRank calculations
	double rank_result[NUM_PAGES];
	//compute Page Rank
  construct_matrix(addr, rank_result);
  //make_matrix(argv[1]);
  char* names[NUM_PAGES];
  get_names(addr, names);

	//starter messsage
	char str[80];
	sprintf(str, "Starting page rank calculation. I got : %.10f", rank_result[0]);  
	ui_add_message(NULL, str);
  //while running:
  while(true) {
    char* message = ui_read_input();
    //find entry point page (matching title)
    if (strcmp(message, "quit") == 0) {
      ui_shutdown();
      return 0;
    }
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
