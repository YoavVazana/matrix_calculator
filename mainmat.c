#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "mymat.h"


mat MAT[NUMBER_OF_MATRICES];
void check_func(char *sentance,int *stop);

/*Creates a new 4x4 matrix and initializes its elements to zero.*/
mat* create_mat()
{
	mat *matrix = (mat*)malloc(sizeof(mat));
	if (matrix == NULL) {
        	perror("Error allocating memory for matrix");
      	        exit(EXIT_FAILURE);
    	}

	/*Initialize matrix elements to zero*/
	memset(matrix->data,0,sizeof(matrix->data));

	return matrix;
}

/*Frees the memory allocated for a matrix.*/
void free_mat(mat *matrix)
{
	free(matrix);
}


/*Reads a string representation of numbers separated by commas and populates a matrix.*/
void read_mat(mat *matrix,char *res)
{
	
	char input[MAX_CHAR_IN_SENTANCE];

	char *token;
	
	int countInput = 0,i,matrixIndex = 0,countCommas = 0;

	char *endptr;

	
	/*Copy input string to a local variable*/
	strcpy(input, res);
	
	/*Tokenize the input string*/
	token = strtok((char *)input," ,");

	/*Process each token until the matrix is filled or no more tokens*/
	while(token != NULL && matrixIndex < NUMBER_OF_CELLS_IN_MAT) {
		
		/*Convert token to a double*/
		strtod(token, &endptr);

		/*Check if conversion was successful*/
		if (*endptr != '\0') {
            		printf("Argument %s is not a real number.\n", token);
            		return;
        	}
 
		
		/*Populate the matrix with the converted number*/
		matrix->data[matrixIndex / NUMBER_OF_ROW_IN_MAT][matrixIndex % NUMBER_OF_ROW_IN_MAT] = atof(token);
			countInput++;
			matrixIndex++;
		
		
		/*Check for consecutive commas*/
		if(strcmp(token,",") == 0){
			countCommas++;

			if(countCommas > 1){
				printf("Multiple consecutive commas\n");
				return;
			}
		}else{
			countCommas = 0;/*Reset count if token is not a comma*/
		}

		/*Get the next token*/
		token = strtok(NULL," ,");
		
	}
	
	/*Check for a comma at the end of the input*/
	if(input[strlen(input) -1] == ',') {
		printf("Extraneous text after end of command \n");
		return;
	}


		/*Fill remaining matrix elements with zeros*/
		for(i = matrixIndex; i < NUMBER_OF_CELLS_IN_MAT ; i++){
			matrix->data[i / NUMBER_OF_ROW_IN_MAT][i % NUMBER_OF_ROW_IN_MAT] = 0;
		}

		/*Print the populated matrix*/
		print_mat(matrix);
	

	}




/*Prints the contents of a 4x4 matrix to the console.*/
void print_mat(mat *matrix)
{	
	int i,j;
	printf("The matrix is\n");
	for(i = 0; i < NUMBER_OF_ROW_IN_MAT; i++){
		for(j = 0; j < NUMBER_OF_ROW_IN_MAT; j++){
			printf("%.2f\t", matrix->data[i][j]);
			/*Print each matrix element with two decimal places*/
		}
		printf("\n");/*Move to the next row after printing each row*/
	}
}



int main()
{
	
	mat *MAT[NUMBER_OF_MATRICES];

	char command[MAX_CHAR_IN_SENTANCE];

	int stop = 1;
	int i;
	
	
	/*Allocate memory for six matrices*/
	for(i = 0;i < NUMBER_OF_MATRICES;i++){

		MAT[i] = create_mat();

	}

	
	/*Main loop to process user commands*/
	while(stop != 0){

		printf("Please type the command you want to execute \n");

		scanf("%99[^\n]" ,command);
		getchar();
	
		
		/*Process the command using check_func*/
		check_func(command,&stop);

		command[0] = '\0';
	}

	/*Free memory allocated for each matrix*/		
	for(i = 0; i < NUMBER_OF_MATRICES; i++){

		if (MAT[i] != NULL) {

			if(MAT[i] != NULL) {
        
        			free_mat(MAT[i]);

				MAT[i] = NULL;
    			}
		}
	}
	printf("Thank you! :]\n");

	return 0;
}
	
