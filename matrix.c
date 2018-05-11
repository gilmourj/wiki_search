#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define NUM_PAGES 473
typedef struct link {
    char* link;
    struct link* next;
} link_t;

typedef struct list {
    link_t *head;
} list_t;

typedef struct page {
    char * name;
    char * link;
    int index;
    list_t *links;
} page_t;

typedef struct outbound_list {
	int data[NUM_PAGES];
	int size;
} outbound_list_t;

outbound_list_t* parse_data(char *data) {
	char *number;
	int count = 0;
	strtok(data, "[");
	outbound_list_t* list = malloc(sizeof(outbound_list_t));
	while ((number = strtok(NULL, ",")) != NULL) {
		list->data[count] = atoi(number);
		count++;
	}
	list->size = count;
	return list;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		perror("Invalid syntax: matrix [filename]\n");
		exit(2);
	}
	// Read csv file address from command line argument
	char *addr = argv[1];
	// Read CSV file
	FILE *csvStream = fopen(addr, "r");
	if (csvStream == NULL) {
		fprintf(stderr, "Error reading the csv file.");
		exit(2);
	}
	// Array of Marvel Character Names
	char *names[NUM_PAGES];
	// Allocate line buffer
	//char buffer[BUFFER_SIZE];
	char *buffer = NULL;
	size_t linecap = 0;
	size_t len;
	int line_count = 0;
	// Array of adjacency lists
	outbound_list_t* adjacency_lists[NUM_PAGES];
	while ((len = getline(&buffer, &linecap, csvStream)) > 0 && line_count < NUM_PAGES) {
		char *data = strtok(buffer, "|");
	  //printf("%s ", data);
		names[line_count] = malloc(sizeof(char) * BUFFER_SIZE);
		strncpy(names[line_count], buffer, BUFFER_SIZE);
		data = strtok(NULL, "|");
		data = strtok(NULL, "|");
		//Index of the webpage
		//printf("\t %s ", data);
		data = strtok(NULL, "|");
		data = strtok(NULL, "|");
		//List of outbound links
		//printf("\t %s \n", data);
		adjacency_lists[line_count] = parse_data(data);
		//print
		//for(int i=0;i<adjacency_lists[line_count]->size;i++) {
		//	printf("%d ", *(adjacency_lists[line_count]->data + i));
		//}
		//printf("\n\n");
		line_count++;
	}

	for (int i=0;i<line_count;i++) {
	 	//printf("%s\n", names[i]);
	}

	// Declare the PageRank matrix since we know it's line_count by line_count
	double pageMat[line_count][line_count];
	for (int j=0;j<line_count;j++) {
		for (int i=0;i<line_count;i++) {
			pageMat[j][i] = 0.0;
		}
	}

	// Fill it up!
	for (int row=0;row<line_count;row++) {
		outbound_list_t* list = adjacency_lists[row];

		for (int col=0;col<list->size;col++) {
				int data = list->data[col];
				// Temporary index bound check --- DELETE LATER
				if (data < line_count) {
				// Set the field to 1
				pageMat[row][data] = 1.0;
				}
				else break;
		}
		free(adjacency_lists[row]);
	}

	// Testing
	for (int j=0;j<line_count;j++) {
		for (int i=0;i<line_count;i++) {
			printf("%.0f", pageMat[j][i]);
		}
		printf("\n");
	}

	return 0;
}
