#ifndef MATRIX_H
#define MATRIX_H

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

// Printing the result
void print_vec(double resVec[], int size);

// Multiply vetor by matrix
void multiply_vec(double mat1[], double mat2[][NUM_PAGES], double res[], int N);

// Max difference between 2 vectors
double max_diff(double v1[], double v2[], int size);

// Max index in a vector
int max_index(double v[], int size);

outbound_list_t* parse_data(char *data);

void get_names(char* addr, char* names[NUM_PAGES]);

void get_links(char* addr, char* links[NUM_PAGES]);

int construct_matrix(char *addr, double initialVec[], outbound_list_t* list[NUM_PAGES]);

void sort_results(int num_results, int result_pages[num_results], double rank_result[NUM_PAGES]);

#endif
