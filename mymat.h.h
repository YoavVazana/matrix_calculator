
typedef struct {
	float data[4][4];
}mat;

#define NUMBER_OF_MATRICES 6
#define MAX_CHAR_IN_SENTANCE 100
#define NUMBER_OF_CELLS_IN_MAT 16
#define NUMBER_OF_ROW_IN_MAT 4

extern mat MAT[6];


void print_mat(mat *matrix);
void read_mat(mat *matrix,char *res);
void add_mat(mat *matrixA,mat *matrixB,mat *matrixC);
void sub_mat(mat *matrixA,mat *matrixB,mat *matrixC);
void mul_mat(mat *matrixA,mat *matrixB,mat *matrixC);
void mul_scalar(mat *matrixA,double x,mat *matrixB);
void trans_mat(mat *matrixA, mat *matrixB);
