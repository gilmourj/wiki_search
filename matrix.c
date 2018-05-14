#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

#define BUFFER_SIZE 1024
#define NUM_PAGES 473
#define P_VAL .15

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

int construct_matrix(char *addr) {
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

	// Testing
	for (int j=0;j<line_count;j++) {
		for (int i=0;i<line_count;i++) {
			//printf("%.0f", pageMat[j][i]);
		}
		//printf("\n");
	}

	double stochastic = (double) (1.0/line_count);
	// Normalize the Matrix!
	for (int row=0;row<line_count;row++) {
		double normal;
		if (row_counts[row] == 0.0) normal = 0.0;
		else normal = (double) (1.0/row_counts[row]);
		for (int col=0;col<line_count;col++) {
			if (pageMat[row][col] >= .5) {
				pageMat[row][col] = (double) ((1.0 - P_VAL) * normal + P_VAL * stochastic);
			} else {
				pageMat[row][col] = (double) (P_VAL * stochastic);
			}
		}
	}

	// Create the initial state vector
	double initialVec[line_count];
	for (int i=0;i<line_count;i++) {
		initialVec[i] = stochastic;
	}
	// Create resulting matrix
	double resVec[line_count];
	// Multiply the matrices!!!
	double max_err = 1.0;
	while (max_err > .001) {
		multiply_vec(initialVec, pageMat, resVec, line_count);
		max_err = max_diff(initialVec, resVec, line_count);
		memcpy(initialVec, resVec, sizeof(double) * line_count);
	}
	
	/*
	print_vec(initialVec, line_count);
	printf("################## SOME LINE BREAK HERE #####################----------!!!!!!!!\n");
	int maximum_index = max_index(initialVec, line_count);
	printf("The max index is: %d\n", maximum_index);
	printf("The page name is: %s\n", names[maximum_index]);
	printf("And its value is: %.10f\n\n", initialVec[maximum_index]);

	printf("Let's print out some higher ranked Heroes::::::\n");
	for (int i=0;i<line_count;i++) {
		if (initialVec[i] > .01) {
			printf("%s ", names[i]);
		}
	}
	printf("\n");
	*/

	return 0;
}
