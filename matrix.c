#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define NUM_PAGES 1024
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
	int *data;
	int size;
} outbound_list_t;

outbound_list_t* parse_data(char *data) {
	char *number;
	static int num[NUM_PAGES];
	int count = 0;
	strtok(data, "[");
	while ((number = strtok(NULL, ",")) != NULL) {
		num[count] = atoi(number);
		count++;	
	}
	outbound_list_t* list = malloc(sizeof(outbound_list_t));
	list->data = num;
	list->size = count;
	//number = strtok(NULL, "]");
	//num[count] = atoi(number);
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
	while ((len = getline(&buffer, &linecap, csvStream)) > 0 && line_count <= 1) {
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
		outbound_list_t* list = parse_data(data);
		//print
		for(int i=0;i<list->size;i++) {
			printf("%d ", *(list->data + i));
		}
		printf("\n\n");
		line_count++;
	}

	for (int i=0;i<line_count;i++) {
	 	printf("%s\n", names[i]);
	}
	return 0;
}

