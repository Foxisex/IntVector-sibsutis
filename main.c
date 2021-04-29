#include <stdio.h>
#include "IntVector.h"
#include <stdlib.h>
#include <ctype.h>

void display(IntVector* v) {
	printf("Capacity = %d Size = %d\n", (int) int_vector_get_capacity(v), (int) int_vector_get_size(v));
    			for (int i = 0; i < int_vector_get_size(v); i++) {
					printf("%d ", int_vector_get_item(v, i));
				}
}


int main()
{
	IntVector *v = int_vector_new(10);
					display(v);
					

	printf("\n\n");

	printf("1. Copy IntVector\n"
		   "2. Reset IntVector to zero\n"
		   "3. Change an element in array\n"
		   "4. Find out size of IntVector\n"
		   "5. Find out capacity of IntVector\n"
		   "6. Add an element in the end of array\n"
		   "7. Delete an element from the end of array\n"
		   "8. Equate size and capacity\n"
		   "9. Change size of the array\n"
		   "10.Change capacity of the IntVector\n"
		   "11.Exit of programm\n\n");


	int input;

	while (input != 11) {
		printf("\nWhat to do next: ");

		if(scanf("%d", &input) != 1) {
			printf("Fatal error: expected only digits\n");
			break;
		}
		 
		switch(input) {
			case 1:
				{IntVector *t = int_vector_copy(v);
				printf("Capacity of second vector = %d Size of second vector = %d\n",
				 (int) int_vector_get_capacity(t), (int) int_vector_get_size(t));
    			for (int i = 0; i < int_vector_get_size(t); i++) {
					printf("%d ", int_vector_get_item(t, i));
				}
				}					break;
			case 2: 
				int_vector_free(v);
    			display(v);
				break;
			case 3:
				printf("What element do you want to change?\n");
				int index;
				scanf("%d", &index);
				if(index <= v->size) {
					printf("What number do you want to set instead?\n");
					int item;
					scanf("%d", &item);
					int_vector_set_item(v, (index - 1), item);
					display(v);
				}
				else{ printf("Error: you get out of capacity\n"); }
				break;
			case 4:
				printf("Size = %d\n", (int) int_vector_get_size(v));
				break;
			case 5:
				printf("Capacity = %d\n", (int) int_vector_get_capacity(v));
				break;
			case 6:
				printf("What number do you want to add?\n");
				int x;
				scanf("%d", &x);
				int_vector_push_back(v, x);
				display(v);
				break;
			case 7:
				int_vector_pop_back(v);
				display(v);
				break;
			case 8:
				int_vector_shrink_to_fit(v);
				display(v);
				break;
			case 9:
				printf("What size do you what to set?\n");
				int j;
				scanf("%d", &j);
				int_vector_resize(v, j);
				display(v);
				break;
			case 10:
				printf("What capacity do you what to set?\n");
				int f;
				scanf("%d", &f);
				int_vector_reserve(v, f);
				display(v);
				break;
			case 11:
				break;
			default:
				printf("Error: expected number 1 - 11\n");
		}
		
	}
}