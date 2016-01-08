/*
* fsplit.cc
*/

#include <cstdio>
#include <cstdint>

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

#define BUFFER_SIZE (32 * 1024)

using namespace std;

size_t copy_to_file (FILE *infile, FILE *outfile, size_t n_bytes)
{
	uint8_t buffer[BUFFER_SIZE];
	size_t bytes_written = 0;
	size_t count = 0;
	if (n_bytes != (size_t)(-1)) {
		while ((n_bytes > 0) && (count = fread(buffer, 1, (n_bytes < BUFFER_SIZE ? n_bytes : BUFFER_SIZE), infile)) > 0) {
			fwrite(buffer, 1, count, outfile);
			n_bytes -= count;
			bytes_written += count;
		}
	} else {
		while ((count = fread(buffer, 1, BUFFER_SIZE, infile)) > 0) {
			fwrite(buffer, 1, count, outfile);
			bytes_written += count;
		}
	}
	return bytes_written;
}

bool parse_args (int argc, char *argv[], vector<pair<string, size_t>>& files)
{
	if (argc <= 1) {
		cerr << "ERROR: no command line arguments." << endl;
		return false;
	}
	for (int k = 1; k < argc; k += 2) {
		string name = argv[k];
		size_t size = 0;
		if (k < argc - 1) {
			if (sizeof(size_t) == sizeof(unsigned long)) {
				size = stoul(string(argv[k + 1]));
			} else if (sizeof(size_t) == sizeof(unsigned long long)) {
				size = stoull(string(argv[k + 1]));
			} else {
				cerr << "ERROR: sizeof(size_t) matched no known size_t typedef" << endl;
				return false;
			}
		}
		files.push_back(make_pair(name, size));
	}
	return true;
}

int main (int argc, char *argv[])
{
	vector<pair<string, size_t>> files;
	if (!parse_args(argc, argv, files)) {
		cerr << "Unable to parse program arguments, exiting." << endl;
		exit(1);
	}

	FILE *infile = stdin;
	FILE *outfile;
	for (auto& p : files) {
		string& name = p.first;
		size_t size = p.second != 0 ? p.second : -1;
		cout << "size: " << size << endl;
		outfile = fopen(name.c_str(), "w");
		copy_to_file(infile, outfile, size);
		fclose(outfile);
	}

	return 0;
}
