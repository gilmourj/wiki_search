#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
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
	char **names = malloc(sizeof(char*) * 512);
	// Allocate line buffer
	//char buffer[BUFFER_SIZE];
	char *buffer = NULL;
	size_t linecap = 0;
	size_t len;
	int line_count = 0;
	while ((len = getline(&buffer, &linecap, csvStream)) > 0 && line_count <= 50) {
		char *data = strtok(buffer, "|");
		printf("\t'%s'\n", data);
		//strncpy(names[line_count], buffer, BUFFER_SIZE);
		//data = strtok(NULL, "|");
		//printf("\t'%s'\n", data);
		line_count++;
	}

	for (int i=0;i<line_count;i++) {
		printf("%s\n", names[i]);
	}
	return 0;

}
