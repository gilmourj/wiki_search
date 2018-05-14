#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

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
	int search_session = 1;

  //while running:
  while(true) {
    char* message = ui_read_input();
    for(int i=0; message[i]; i++) {
      message[i] = tolower(message[i]);
    }
    //find entry point page (matching title)
    if (strcmp(message, "quit") == 0) {
      ui_shutdown();
      return 0;
    }
    else {
			//Welcome screen for each query
			char initial_msg[50];
			sprintf(initial_msg, "Search session #%d", search_session);
			search_session++;
			ui_add_message("Google 0.5 Presents to you : ", initial_msg);
			//list of found relevant pages denoted by their indices
			int result_pages[10] = {-1};
			int page_count = 0;
      //see if the input is a substring of any name (lowercase everything)
      bool found = false;
      for (int i=0; i<NUM_PAGES; i++) {
        if (strstr(names[i], message) != NULL) {
          found = true;
					result_pages[page_count] = i;
					page_count++;
        }
      }
      if (found) {
				for (int i=0; i<page_count; i++) {
					char output_message[128];
					sprintf(output_message, "%s was found with Page Rank of %.8f", names[result_pages[i]], rank_result[result_pages[i]]);
					ui_add_message(NULL, output_message);
					ui_clear_input();
				}
				free(message);
        continue;
      }
      else {
        char* output_message = strcat(message, " is not known to The Avengers");
				ui_add_message(NULL, output_message);
        ui_clear_input();
        free(message);
        continue;
      }
    }
    //repeat to allow for new search or quit
  }
}
