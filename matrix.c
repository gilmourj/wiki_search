#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define NUM_PAGES 473
#define NUM_TEST 473
#define NUM_ITER 2

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

// This function multiplies mat1[][] and mat2[][],
// and stores the result in res[][]
//void multiply(int mat1[][], int mat2[][], int res[][], int N) {
//	int i, j, k;
//	for (i = 0; i < N; i++) {
//		for (j = 0; j < N; j++) {
//			res[i][j] = 0;
//			for (k = 0; k < N; k++)
//				res[i][j] += mat1[i][k]*mat2[k][j];
//		}
//	}
//}

// Printing the result
void print_vec(double resVec[], int size) {
	for (int i=0;i<size;i++) {
		printf("%.10f\n", resVec[i]);
	}
}

// Multiply matrix with vector
void multiply_vec(double mat1[][NUM_TEST], double mat2[], double res[], int N) {
	int i, j, k;
	for (i = 0; i < N; i++) {
			res[i] = 0;
			for (k = 0; k < N; k++)
				res[i] += mat1[i][k]*mat2[k];
	}
}

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
			//printf("%.0f", pageMat[j][i]);
		}
		//printf("\n");
	}

	// Create the initial state vector
	double initialMat[line_count];
	for (int i=0;i<line_count;i++) {
		initialMat[i] = (double) (1.0/line_count);
	}
	// Create resulting matrix
	double resVec[line_count];
	// Multiply the matrices!!!
	for (int i=0;i<NUM_ITER;i++) {
		multiply_vec(pageMat, initialMat, resVec, line_count);
		memcpy(initialMat, resVec, sizeof(double) * line_count);
		print_vec(initialMat, line_count);
		printf("################## SOME LINE BREAK HERE #####################----------!!!!!!!!\n");
	}

	return 0;
}
