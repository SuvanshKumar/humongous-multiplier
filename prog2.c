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

int num1_length, num2_length, block_size, thread_count_no,rem_chunk;

sem_t semaph;

pthread_t tid[ 50 ]; 

//  Multiply function
void *multiply(void *args)
{
	int t_thread_no=(intptr_t)args;
	int i, j;
	int start_id, end_id;
	int res;
	start_id = t_thread_no * block_size;
	end_id = start_id + block_size - 1;

	// executing For the last thread
	if(t_thread_no == (thread_count_no - 1))
		end_id =  end_id + rem_chunk;
    sem_wait( &semaph );
	for(i = 0;i< num2_length;++i){
		for(j = start_id; j<=end_id; ++j){
			// multiplying the corresponding digits and storing the results.
			res = first_multiplic_number[j] * second_multiplic_number[i];
			// Adding the previous result to the current multiplication values
			result_multi[i + j] = result_multi[i + j] +res % 10;
			result_multi[i + j +1] = result_multi[i + j +1] + res / 10;
			
		}
	}
	// signaling the semaph
    sem_post( &semaph );
}

int main()
{
	//  Opening the 2 input text files
	FILE* First_file=fopen("input1.txt","r");
	FILE* Second_file=fopen("input2.txt","r");
	num1_length=0; 
	num2_length=0;
	char ch;
	// Initializing the mutual exclusion semaph.
	sem_init( &semaph, 0, 1 );
	printf("Enter thread count \n");
	scanf("%d",&thread_count_no);
    if(thread_count_no<1 || thread_count_no>50){
        printf("Invalid thread count -- defaulting thread count to 5");
        thread_count_no = 5;
    }
	int flag=0;
	int len=0;
	int i, j;
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
	j = 0;
	// number of digits for the second number
	num2_length = len;
	while((ch = fgetc(Second_file)) != EOF){
		// extracting digits for second multiplicant
		second_multiplic_number[num2_length - (j + 1)]=ch-'0';
		j++;
	}
	//  calculating the chink size
	block_size=num1_length/thread_count_no;
	// last chunk size
    rem_chunk= num1_length%thread_count_no;
	// Create no_threads identical threads each one running the multiply()
	// function, saving the thread-id in the tid array, and using the default 
	// attributes.  Each thread calls the function multiply(), with one
	// argument "i", used as the thread number.
	for( i = 0; i < thread_count_no; i++) 
	{
		pthread_create( &tid[ i ], NULL, multiply, (void *) (intptr_t)i );
	}

	// Wait until all the threads to exit.  This suspends the calling thread,
	// i.e., the main program, until all target threads complete.

	for( i = 0; i < thread_count_no; i++ ) 
		pthread_join( tid[ i ], NULL );
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
 FILE* Output_file=fopen("multithreaded_multiplied.txt","w");
    for(i = total_len; i>=0;--i)
	fprintf(Output_file,"%d", result_multi[i]);
	printf("\n");

}