#include "Varint.h"
#define MAXLEN 10

int main()
{
	uint32_t number;
	uint8_t buf[4]; 
	uint8_t *buffer; 
	int size_of_encode, size_of_buffer; 
	uint32_t decoded_number; 
	const uint8_t **bufp;
	int i; 
	FILE* uncomp_file = fopen("uncompressed.dat", "w+b"); 
	FILE* comp_file = fopen("compressed.dat", "w+b"); 
	if ((uncomp_file == NULL) || (comp_file == NULL)) {
		printf("File openning error\n"); 
		return -1; 
	} 

	for(int i = 0; i < MAXLEN; i++) {
		number = generate_number(); 
		fwrite(&number, sizeof(uint32_t), 1, uncomp_file); 
		size_of_encode = encode_varint(number, buf); 
		fwrite(buf, sizeof(uint8_t), size_of_encode, comp_file);
	}
	rewind(uncomp_file);
	bufp = (const uint8_t**)&buffer; 
	fseek(comp_file, 0, SEEK_END); 
	size_of_buffer = ftell(comp_file); 
	rewind(comp_file); 
	buffer = (uint8_t*)malloc(size_of_buffer); 
	fread(buffer, sizeof(uint8_t), size_of_buffer, comp_file); 
	for (i = 0; i < MAXLEN; i++) {
		decoded_number = decode_varint(bufp); 
		fread(&number, sizeof(uint32_t), 1, uncomp_file); 
		if (number != decoded_number) {
			printf("Error: numbers are not equal\n"); 
			break; 
		} 
	} 
	return 0; 
}
