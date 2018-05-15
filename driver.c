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
    if (num_results > NUM_PAGES) {
      num_results = NUM_PAGES;
    }
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
  //get links and names for each page
  char* names[NUM_PAGES];
  get_names(addr, names);
  char* links[NUM_PAGES];
  get_links(addr, links);

	//starter messsage
	ui_add_message(NULL, "-------------------------- Welcome to HeroRank ---------------------------");
	ui_add_message(NULL, "-------------- World's Premier Search Engine for the MCU --------------");
	int search_session = 0; //zero index search sessions

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
			char initial_msg[128];
			sprintf(initial_msg, "Search session #%d: %d results found in %d milliseconds", search_session, NUM_RESULTS, 1);
			search_session++;
			ui_add_message("HeroRank Presents to you : ", initial_msg);
			//list of found relevant pages denoted by their indices
			int result_pages[num_results];
			int page_count = 0;
      //see if the input is a substring of any name (lowercase everything)
      bool found = false;
      for (int i=0; i<NUM_PAGES; i++) {
				if (page_count > num_results) break;
        if (strstr(names[i], message) != NULL && page_count < num_results) {
          found = true;
					result_pages[page_count] = i;
					page_count++;
        }
      }
      if (found) {
        sort_results(num_results, result_pages, rank_result);
				for (int i=0; i<page_count; i++) {
					char output_message[256];
					sprintf(output_message, "http://marvel.wikia.com%s was found with Page Rank of %.8f", links[result_pages[i]], rank_result[result_pages[i]]);
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
