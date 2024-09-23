#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "mymat.h"

void send_to_func1(int func_num,int param_num,char *endOfSentance);
void send_to_func2(int func_num, int param_num1, int param_num2);
void send_to_func3(int func_num, int param_num1, double scalar, int param_num2);
void send_to_func4(int func_num, int param_num1, int param_num2, int param_num3);
int double_commas(char *input);
int check_first_comma(char *sentance);
int check_commas_between(char *sentance,int start);
void fix_spaces(char *sentence);

/*Checks the legality of the command and directs it to the desired function.*/
void check_func(char *sentance,int *stop)
{	
	
	char *endptr;
	
	double num;

	int is_valid = 0,scalar;
	
	int length_sentance = strlen(sentance);	

	char endOfSentance[MAX_CHAR_IN_SENTANCE];

	int boll;

	int i,saveFuncIndex = 0,saveParamIndex1 = 0,
	saveParamIndex2 = 0,saveParamIndex3 = 0;

	const char *func_names[] = {"read_mat","print_mat","add_mat","sub_mat",
			           "mul_mat", "mul_scalar", "trans_mat","stop"};

	const char *param_names[] = {"MAT_A", "MAT_B", "MAT_C", "MAT_D", 
				    "MAT_E", "MAT_F"};
	char *token;

	char original_sentance[MAX_CHAR_IN_SENTANCE];

	char original_sentance2[MAX_CHAR_IN_SENTANCE];

	char original_sentance3[MAX_CHAR_IN_SENTANCE];

	/*Two copies of the string for new parsing by strtok*/
        strcpy(original_sentance, sentance);

	strcpy(original_sentance2, sentance);

	/*Tokenize the input command*/
	token = strtok(sentance," ");
 
	/*Fix spaces in the original command*/
        fix_spaces(original_sentance);

	/*Print the original command*/
	printf("your command is: %s \n",original_sentance);
	
	/*Check for extraneous text after the end of the command*/
	if (strlen(sentance) > 0 && sentance[length_sentance - 1] == ',') {

		printf("Extraneous text after end of command \n");

		return;
	}


	/*Check for double commas in the original command*/
	boll = double_commas(original_sentance);

	if(!boll){

		return;
	}


	/*Looking for whether there is a comma immediately after the function 		name*/
	boll = check_first_comma(original_sentance);


	if(!boll){

		return;
	}



	/*Looking for whether the first word in the command corresponds to one 		of the reserved functions*/
	for(i = 0; i < sizeof(func_names) / sizeof(func_names[0]); i++){

		if(strcmp(token,func_names[i]) == 0){

			is_valid = 1;

			saveFuncIndex = i;
		}
	}

	/*Checks if the function name is valid*/
	if(!is_valid){

		printf("Error - undefined command name\n");

		return;

	}

	

	/*Checking if the user pressed stop*/
	if(saveFuncIndex == 7){

		/*Handle the "stop" command*/
		if(length_sentance == 4 && strcmp(sentance, "stop") == 0){

			*stop = 0;

			return;
		
		}else{
			printf("Extraneous text after end of command \n");
			
			return;
		}
	}

	/*Fix spaces in the original command*/
	fix_spaces(original_sentance2);	
	
	/*Tokenize the modified command*/
	token = strtok(original_sentance2," ");
	
	token = strtok(NULL, ",");
	
	is_valid = 0;

	/*Checks the name of the first matrix*/
	for(i = 0;i < sizeof(param_names)/sizeof(param_names[0]);i++){

		if(strcmp(token,param_names[i]) == 0){

			is_valid = 1;

			saveParamIndex1 = i;

		}

	}

	
	/*Checking if the name is correct*/	
	if(!is_valid){

		printf("Error- Invalid matrix name\n");

		return;
	}


	/*If the required function is read_mat or print_mat we can send them 		because both receive one matrix*/
	if(saveFuncIndex == 0 || saveFuncIndex == 1){

		token = strtok(NULL,"\n");

		if(token != NULL){

			strncpy(endOfSentance , token , sizeof(endOfSentance) - 1);

			endOfSentance[sizeof(endOfSentance) - 1] = '\0';
		}


		/*Checking if unnecessary characters have been typed*/
		if(saveFuncIndex == 1 && 
		   length_sentance != strlen("print_mat MAT_A")){

			if(length_sentance > strlen("print_mat MAT_A")){

				printf("Extraneous text after end of command \n");

				return;

			}else if(length_sentance < strlen("print_mat MAT_A")){

				printf("Missing argument\n");

				return;

			}
		}else{

		/*sends to the appropriate function*/
		send_to_func1(saveFuncIndex,saveParamIndex1,endOfSentance);
		}
			
	/*Process the "mul_scalar" command*/
	}else if(saveFuncIndex == 5){
		
		token = strtok(NULL,", ");
		num = strtod(token, &endptr);

		/*Check if the scalar is a valid real number*/
		if (*endptr != '\0') {

            		printf("Argument %s is not a real number.\n", token);

            		return;
        	}

		/*Determine the length of the scalar value*/
		num = strlen(token);

		/*Convert the scalar value to an integer*/
		scalar = atof(token);

		/*Extract the matrix parameter*/
		token = strtok(NULL,", ");

		is_valid = 0;
		
		/*Validate the matrix parameter*/
		for(i = 0; i < sizeof(param_names)/sizeof(param_names[0]);i++){

			if(strcmp(token,param_names[i]) == 0){

				is_valid = 1;

				saveParamIndex2 = i;

				break;
				}
			}


		/*Checks if the matrix name is valid*/
		if(!is_valid){

			printf("Error- Invalid matrix name\n");

			return;
		}


		/*Check for extraneous or missing text in the command*/
		if(length_sentance > strlen("mul_scalar MAT_A,,MAT_B") + num){

			printf("Extraneous text after end of command \n");

			return;

		}else if(length_sentance < strlen("mul_scalar MAT_A,,MAT_B") + num){

			printf("Missing argument \n");

			return;

		}else{

			/*sends to the appropriate function*/
			send_to_func3(saveFuncIndex,saveParamIndex1,scalar,saveParamIndex2);
		}

			
		   
	
	/*Process commands for matrix operations (addition, subtraction, multiplication) and matrix transposition.*/				
	}else if((saveFuncIndex >= 2 && saveFuncIndex < 5)||saveFuncIndex == 6){

		token = strtok(NULL,", ");

		is_valid = 0;

		/*Validate the second matrix parameter*/
		for(i = 0; i < sizeof(param_names)/sizeof(param_names[0]);i++){

			if(strcmp(token,param_names[i]) == 0){

				is_valid = 1;

				saveParamIndex2 = i;

				break;
			}
		}


		/*Checks if the matrix name is valid*/
		if(!is_valid){

			printf("Error- Invalid matrix name\n");

			return;
		}


		/*Checks the correctness of the command length*/
		if(saveFuncIndex == 6){
			
			if(length_sentance > strlen("trans_mat MAT_A,MAT_B")){

				printf("Extraneous text after end of command \n");

				return;

			}else if(length_sentance < strlen("trans_mat MAT_A,MAT_B")){

				printf("Missing argument \n");

				return;

			}else{

			/*sends to the appropriate function*/
			send_to_func2(saveFuncIndex,saveParamIndex1,saveParamIndex2);
			}
			

		/*Process commands for matrix operations (addition, subtraction, multiplication)*/
		}else if(saveFuncIndex >= 2 && saveFuncIndex <= 4){

			/*Checks the correctness of the command length*/
			if(length_sentance > strlen("add_mat MAT_A,MAT_B,MAT_C")){

				printf("Extraneous text after end of command \n");

				return;
				
			}else if(length_sentance < strlen("add_mat MAT_A,MAT_B,MAT_C")) {

				printf("Missing argument \n");

				return;
			}	

			token = strtok(NULL,", ");

			is_valid = 0;

			/*Validate the third matrix parameter*/
			for(i = 0; i < sizeof(param_names)/sizeof(param_names[0]);i++){

				if(strcmp(token,param_names[i]) == 0){

					is_valid = 1;

					saveParamIndex3 = i;

					break;
				}
			}

			
			/*Checks if the matrix name is valid*/
			if(!is_valid){

				printf("Error- Invalid matrix name\n");

				return;
			}

			
			/*sends to the appropriate function*/
			send_to_func4(saveFuncIndex,saveParamIndex1,saveParamIndex2,saveParamIndex3);
			

		}

	}

	
	
	/*Check commas between parameters based on the func name*/
	if(saveFuncIndex != 0 && saveFuncIndex != 1 && saveFuncIndex != 7){
		if(saveFuncIndex == 6){	
			i = 1;
			boll = check_commas_between(original_sentance3,i);
		}else{
			i = 0;
			boll = check_commas_between(original_sentance3,i);
		}

		if(!boll){

			return;
		}
		
	}		

}



/*Passes the values ​​to the appropriate functions*/
/*Transfers to the add_mat, sub_mat, mul_mat functions*/
void send_to_func4(int func_num,int param_num1,int param_num2,int param_num3){
	
	if(func_num == 2){

		add_mat(&MAT[param_num1],&MAT[param_num2],&MAT[param_num3]);

	}else if(func_num == 3){

		sub_mat(&MAT[param_num1],&MAT[param_num2],&MAT[param_num3]);

	}else{

		mul_mat(&MAT[param_num1],&MAT[param_num2],&MAT[param_num3]);
	}
}



/*Passes to the mul_scalar function*/
void send_to_func3(int func_num,int param_num1,double scalar,int param_num2){

	mul_scalar(&MAT[param_num1],scalar,&MAT[param_num2]);
}


/*Passes to the trans_mat function*/
void send_to_func2(int func_num,int param_num1,int param_num2){

	trans_mat(&MAT[param_num1],&MAT[param_num2]);
}


/*Transfers to functions read_mat, print_mat*/
void send_to_func1(int func_num,int param_num,char *endOfSentance){

	if(func_num == 0){

		read_mat(&MAT[param_num],endOfSentance);

	}else if(func_num == 1){

		print_mat(&MAT[param_num]);
	}


}


/*Check for the presence of consecutive commas in the input string*/
int double_commas(char *input) {

	char *double_commas = strstr(input, ",,");
	
	if(double_commas != NULL){

		printf("Multiple consecutive commas\n");

		return 0;
	}
	return 1;
}


/*Check for an illegal comma placement at the beginning of the sentence.*/
int check_first_comma(char *sentance)
{
	char *comma_position = strchr(sentance,',');

	char *before_comma;

	char *tow_before_comma;
	
	if(comma_position != NULL){ 

		before_comma = comma_position - 1;

		tow_before_comma = comma_position - 2;

		if((before_comma >= sentance && *before_comma >= 'a' && *before_comma <= 'z') ||
			(tow_before_comma >= sentance && (*before_comma == ' ') && 
			*tow_before_comma >= 'a' && *tow_before_comma <= 'z')){
		
		printf("Illegal comma\n");

		return 0;
		}
	}
	
	return 1;
}



/*Check for the correct number of commas between parameters in the input sentence.*/
int check_commas_between(char *sentance,int start)
{
char *token = strtok(sentance, ",");
    
int sum = start;	

    while (token != NULL)

    {
	
	sum++;
        token = strtok(NULL, ",");
       
	
    }
	
	if(sum == 3){

	return 1;
	}else{
		printf("missing comma \n");
		return 0;
	}
}


/*Remove extra spaces in the input sentence.*/
void fix_spaces(char *sentence) {

    char *src = sentence;

    char *dest = sentence;

    int isFirstSpace = 1; 

    while (*src != '\0' && *src == ' ') {

        src++;

    }

    while (*src != '\0') {

        if (*src != ' ' || (isFirstSpace && *(src - 1) != ' ')) {

            *dest++ = *src;

            if (*src == ' ') {

                isFirstSpace = 0; 

            }
        }

        src++;
    }

    *dest = '\0'; 

}













