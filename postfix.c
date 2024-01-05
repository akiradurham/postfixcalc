#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int* stack = NULL; // intialize global variables for my stack
int size = 0;
int capacity = 0;

void push(int num) { // pushes parameter num onto stack
    	if (size >= capacity) { // if size is about to equal capacity (total size)
        	if (capacity == 0){
			capacity = 50; // give min size
		}
		else {
			capacity = capacity * 4; // else resize by *4
			stack = realloc(stack, capacity * sizeof(int)); // realloc memory to avoid mem leaks
		}
      	}
        stack[size++] = num; // push functions to top of stack and increase size
}

int pop() { // take value off top of stack
    	if (size <= 0) { // if stack is empty return 0
        	return 0;
    	}
	else {
        	return stack[--size]; // else return the top of stack and reduce size
    	}
}

int main() {
	capacity = 1; // initial capacity
	stack = malloc(capacity * sizeof(int)); // create the stack with capacity
	char input[999999]; // make input buffer
   	if (!fgets(input, sizeof(input), stdin)){ // if cant read return 1
		free(stack);
		return 1;
	}
	
	do { // large while loop that allows reading from multiple lines
		char *value = strtok(input, " \t\n"); // tokenize the input
	 	while (value != NULL){ // while tokenize is not null
			int num; // create variables to hold operators and operands
			char op;
	        	if (sscanf(value, "%d", &num) == 1) { // if input is a number push onto stack
	       	    		push(num);
			} 
			else if (sscanf(value, "%c", &op) == 1) { // else if it is a char
	            		if (size < 2){ // if there are not enough operands to perform an operation, return 0
					free(stack);
		               		return 0;
	      			}
	  			int b = pop(); // pull operands from stack
	           		int a = pop();
	            		switch (op) { // checks if valid operator and performs operation, pushes result
		                	case '+':
	        	         		push(a + b);
		        			break;
	        	     		case '-':
	                    			push(a - b);
	      					break;
	       	        		case '*':
	     			        	push(a * b);
       		           			break;
       		       			case '%':
	      		    			push(a % b);
              					break;
       					default:
    	        			   	free(stack);
                 				return 1;
         	   		}
			}
			char temp = '['; // printing function provided in writeup for stack
			for ( int i = 0; i < size; i++){
				printf("%c %d", temp, stack[i]);
				temp = ',';
			}
			puts(" ]");
			value = strtok(NULL, " \t\n"); 	
       		}
	} while (fgets(input, sizeof(input), stdin)); // while it can read from stdin (input from command line)
 	free(stack); // zero out and free values
	size = 0;
	capacity = 0;
	return 0;
}