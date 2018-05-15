#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

#define BUFFER_SIZE 1024
#define NUM_PAGES 473
#define P_VAL .15
#define INPUT_SIZE 128 //equal to BUFFER_SIZE in driver.c

// Printing the result
void print_vec(double resVec[], int size) {
	for (int i=0;i<size;i++) {
		printf("%.10f\n", resVec[i]);
	}

	printf("%s", "printed vectors");
}

// Multiply vetor by matrix
void multiply_vec(double mat1[], double mat2[][NUM_PAGES], double res[], int N) {
	int i, k;
	for (i = 0; i < N; i++) {
			res[i] = 0;
			for (k = 0; k < N; k++)
				res[i] += mat1[k]*mat2[k][i];
	}
}

// Max difference between 2 vectors
double max_diff(double v1[], double v2[], int size) {
	double max = 0.0;
	for (int i=0;i<size;i++) {
		double diff = fabs(v2[i] - v1[i]);
		if (diff > max) max = diff;
	}
	return max;
}

// Max index in a vector
int max_index(double v[], int size) {
	int index = 0;
	double max = 0.0;
	for (int i=0;i<size;i++) {
		if (v[i] > max) {
			max = v[i];
			index = i;
		}
	}
	return index;
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

void get_names(char* addr, char* names[NUM_PAGES]) {
	FILE *csvStream = fopen(addr, "r");
	if (csvStream == NULL) {
		fprintf(stderr, "Error reading the csv file.");
		exit(2);
	}
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
		//make list of names
		names[line_count] = (char*) malloc(sizeof(char) * BUFFER_SIZE);
		strncpy(names[line_count], buffer, BUFFER_SIZE);
		line_count++;
	}
	return;
}

int construct_matrix(char *addr, double initialVec[]) {
	// Read CSV file
	FILE *csvStream = fopen(addr, "r");
	if (csvStream == NULL) {
		fprintf(stderr, "Error reading the csv file.");
		exit(2);
	}
	// Allocate line buffer
	char *buffer = NULL;
	size_t linecap = 0;
	size_t len;
	int line_count = 0;
	// Array of adjacency lists
	outbound_list_t* adjacency_lists[NUM_PAGES];
	while ((len = getline(&buffer, &linecap, csvStream)) > 0 && line_count < NUM_PAGES) {
		char *data = strtok(buffer, "|");
		//get through the rest of the stuff
		data = strtok(NULL, "|");
		data = strtok(NULL, "|");
		data = strtok(NULL, "|");
		data = strtok(NULL, "|");
		adjacency_lists[line_count] = parse_data(data);
		line_count++;
	}

	// Declare the PageRank matrix since we know it's line_count by line_count
	double pageMat[line_count][line_count];
	for (int j=0;j<line_count;j++) {
		for (int i=0;i<line_count;i++) {
			pageMat[j][i] = 0.0;
		}
	}

	// Declare a row count array for normalization later
	int row_counts[line_count];
	// Fill it up!
	for (int row=0;row<line_count;row++) {
		outbound_list_t* list = adjacency_lists[row];
		row_counts[row] = list->size;
		for (int col=0;col<list->size;col++) {
				int data = list->data[col];
				// Set the field to 1
				pageMat[row][data] = 1.0;
		}
		free(adjacency_lists[row]);
	}

	double stochastic = (double) (1.0/line_count);
	// Normalize the Matrix!
	for (int row=0;row<line_count;row++) {
		if (row_counts[row] == 0) { 
			for (int col=0;col<line_count;col++) {
				pageMat[row][col] = stochastic;
			}
		} else {
			for (int col=0;col<line_count;col++) {
				pageMat[row][col] = (double) ((1.0 - P_VAL) * pageMat[row][col]/row_counts[row] + P_VAL * stochastic);
			}
		}
	}
	
	// Create the initial state vector
	for (int i=0;i<line_count;i++) {
		initialVec[i] = stochastic;
	}
	// Create resulting matrix
	double resVec[line_count];
	// Multiply the matrices!!!
	double max_err = 1.0;
	while (max_err > .0001) {
		multiply_vec(initialVec, pageMat, resVec, line_count);
		max_err = max_diff(initialVec, resVec, line_count);
		memcpy(initialVec, resVec, sizeof(double) * line_count);
	}

	return 0;
}
