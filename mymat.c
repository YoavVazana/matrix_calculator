#include "mymat.h"


/*All methods receive a matrix that is designed to save the result and thus the data in the other matrices is saved*/

/*The add_mat function performs matrix addition between two matrices.*/
void add_mat(mat *matrixA,mat *matrixB,mat *matrixC)
{
	int i,j;

	for(i = 0; i < 4; i++){

		for(j = 0; j < 4; j++){

		matrixC->data[i][j] = matrixA->data[i][j] + matrixB->data[i][j];

		}
	}

	print_mat(matrixC);
}


/*The sub_mat function receives two matrices, does a subtraction between them and returns the result*/
void sub_mat(mat *matrixA,mat *matrixB,mat *matrixC)
{
	int i,j;

	for(i = 0; i < 4; i++){

		for(j = 0; j < 4; j++){

		matrixC->data[i][j] = matrixA->data[i][j] - matrixB->data[i][j];

		}
	}

	print_mat(matrixC);
}


/*The mul_mat function multiply two matrices.*/
void mul_mat(mat *matrixA,mat *matrixB,mat *matrixC)
{
	int i,j,k;

	for(i = 0; i < 4; i++){

	    for(j = 0; j < 4; j++){

		matrixC->data[i][j] = 0;

		for(k = 0; k < 4; k++){

		   matrixC->data[i][j] += 
		   matrixA->data[i][k] * matrixB->data[k][j];

		}
	    }
	}

	print_mat(matrixC);
}



/*The mul_scalar function accepts a matrix and a scalar and multiplies the matrix by a scalar*/
void mul_scalar(mat *matrixA,double x,mat *matrixB)
{
	int i,j;

	for(i = 0; i < 4; i++){

		for(j = 0; j < 4; j++){

			matrixB->data[i][j] = x * matrixA->data[i][j];
		}
	}

	print_mat(matrixB);
}


/*The trans_mat function receives a matrix and performs an interpolation on it, meaning that each row in the received matrix will be a column in the matrix that will return*/
void trans_mat(mat *matrixA, mat *matrixB)
{
	int i,j;

	for(i = 0; i < 4; i++){

		for(j = 0; j < 4; j++){

			matrixB->data[i][j] = matrixA->data[j][i];

		}
	}

	print_mat(matrixB);
}




