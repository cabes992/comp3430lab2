#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#define OFFSET_BYTE 0x3c // offset defined for where signature is
#define PORTABLE_EXECUTABLE 0x4550 // (chars "PE\0\0") used to confirm presence of signature

typedef struct COFF_HEADER {
	uint16_t machine;
	uint16_t no_of_sections;
	uint32_t time_stamp_date; //time in COFF header is 32 bits
	uint32_t symbol_table;
	uint32_t no_of_symbols;
	uint16_t size_of_header;
	uint16_t character;	
} coff_header;

int main(int argc, char* argv[]) {
	int return_code = 1;
	if (argc == 2) {
		return_code = 0;
		int pefile = open(argv[1], O_RDONLY);
		uint32_t buff = 0; //buffer to store portions of file read
		coff_header my_header = {0};
		
		//Reading value at 0x3c 
		lseek(pefile, OFFSET_BYTE, SEEK_CUR);
		read(pefile, &buff, 1);
		
		//Read 4 bytes at position defined in 0x3c
		lseek(pefile, buff, SEEK_SET);
		read(pefile, &buff, 4);
		
		//Make sure signature is present where expected 
		if (buff == PORTABLE_EXECUTABLE) {
			//Reading contents of file COFF header into my_header struct
			read(pefile, &my_header, 20);
			
			//Printing contents of my_header
			
			printf("Machine Type: %#04x\n", my_header.machine);
			printf("Number of Sections: %d\n", my_header.no_of_sections);
			
			//cast from uint32_t timestamp to a 64 bit time_t to satisfy input
			printf("Created: %s", asctime(gmtime( (time_t*)  &(my_header.time_stamp_date)   )));
			printf("Symbol table start: %#010x\n", my_header.symbol_table);
			printf("Number of symbols: %d\n", my_header.no_of_symbols);
			printf("Size of optional header: %d\n", my_header.size_of_header);
			printf("Characteristics: %#.4x\n", my_header.character);
		}
	}
	printf("Provide a file please\n");
	return return_code;
}
