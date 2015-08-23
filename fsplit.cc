// fsplit.c

#include <cstdint>
#include <cstdio>
//#include <unistd.h>

#include <iostream>

using namespace std;

#define BUFFER_SIZE (1024U * 32U)
typedef uint8_t buffer_type;

void copyto (FILE* infile, FILE* outfile) {
	buffer_type buffer[BUFFER_SIZE];
	size_t count;
	while ((count = fread(buffer, sizeof(buffer_type), BUFFER_SIZE, infile))) {
		fwrite(buffer, sizeof(buffer_type), count, outfile);
	}
}

int main (int argc, char *argv[]) {
	cout << "sizeof(buffer_type): " << sizeof(buffer_type) << endl;
	copyto(stdin, stdout);
	return 0;
}
