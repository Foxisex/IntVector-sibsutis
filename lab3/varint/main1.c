#include "Varint.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define LEN 10

int main() 
{
	//const int Size = 2;
	FILE *file = NULL;
	uint32_t arr[100000] = {0};

	for (int i = 0; i < LEN; i++) {
		arr[i] = generate_number();
	}

	file = fopen("uncompressed.dat", "wb");
	if (file == NULL) {
		printf("Error");
		getchar();
		return 1;
	}

	fwrite(arr, sizeof(int), LEN, file);
	fclose(file);
	FILE *file_2 = NULL;
	file_2 = fopen("compressed.dat", "wb");
	if (file_2 == NULL) {
		printf("Error");
		getchar();
		return 1;
	}

	int num;
	uint8_t* buf = (uint8_t*) calloc(4, sizeof(uint8_t));

	for (int i = 0; i < LEN; i++) {
		num = arr[i];
		int size_of_encode = encode_varint(arr[i], buf);
		fwrite(buf, sizeof(uint8_t), size_of_encode, file_2);
	}

	fclose(file_2);

	FILE *file_3 = NULL;
	file_3 = fopen("compressed.dat", "rb");
	  if (file_3 == NULL) {
	   printf("Error");getchar();
	   return 1;
	}

	int8_t* bufc = (uint8_t*) calloc(4, sizeof(uint8_t));
	uint8_t byte;

	for (int j = 0; j <40; j++) {
		for ( int i = 0; i < 4; i++) {
			fread(&byte, sizeof(uint8_t), 1, file_3);
			bufc[i] = byte;
			if (!(byte&1<<7)) {
				break;
			}
		}

		unsigned int check = decode_varint(&bufc);
		printf("%d     %d\n", arr[j], check);
	}
	return 0;
}