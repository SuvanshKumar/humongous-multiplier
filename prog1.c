// importing all the required header files
#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define max_input_size 1000000
#define max_output_size 2000000
//  Initializing the arrays

int first_multiplic_number[max_input_size];
int second_multiplic_number[max_input_size];
int result_multi[max_output_size];

int num1_length, num2_length;
//  Multiply function
void multiply()
{
	int i, j;
	int res;
	for(i = 0;i< num2_length;++i){
		for(j = 0; j<num1_length; ++j){
			// // multiplying the corresponding digits and storing the results.
			res = first_multiplic_number[j] * second_multiplic_number[i];
			// Adding the previous result to the current multiplication values
			result_multi[i + j] = result_multi[i + j] + res % 10;
			result_multi[i + j +1] =result_multi[i + j +1] + res / 10;
		}
	}
}

int main()
{
	//  Opening the 2 input text files
	FILE* First_file=fopen("input1.txt","r");
	FILE* Second_file=fopen("input2.txt","r");
	num1_length=0; 
	num2_length=0;
	char ch;
	int flag=0;
	int len=0;
	int i;
	while((ch = fgetc(First_file)) != '|'){
		len=(len * 10) + ch - '0';
	}
	i = 0;
	// number of digits for the first number
	num1_length = len;
	while((ch = fgetc(First_file)) != EOF){
		// extracting digits for first multiplicant
		first_multiplic_number[num1_length - (i + 1)]=ch-'0';
		i++;
	}
	
	len = 0;
	while((ch = fgetc(Second_file)) != '|'){
			len=(len * 10) + ch - '0';
	}
	i = 0;
	// number of digits for the second number
	num2_length = len;
	while((ch = fgetc(Second_file)) != EOF){
		// extracting digits for second multiplicant
		second_multiplic_number[num2_length - (i + 1)]=ch-'0';
		i++;
	}
	// Calling the multiply function
    multiply();
	//  storing the results into the output array
	for(i = 0; i < max_output_size;++i){
		result_multi[i + 1] = result_multi[i+1] + (result_multi[i]/10);
		result_multi[i] %= 10;
	}

	int total_len =  num1_length + num2_length - 1;
    // printf("%d",result[0]);
    // printf("%d",result[1]);
    // printf("%d",result[2]);
	while(result_multi[total_len] == 0)
		total_len--; 
// storing the results into the text file
 FILE* Output_file=fopen("single_multiplied.txt","w");
    for(i = total_len; i>=0;--i)
	fprintf(Output_file,"%d", result_multi[i]);
	printf("\n");

}