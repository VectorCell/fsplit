/*
* fsplit.cc
*/

#include <cstdio>
#include <cstdint>
#include <cassert>

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

size_t copy_to_file (FILE *infile, FILE *outfile, size_t n_bytes)
{
	static const size_t BUFFER_SIZE = 32 * 1024;
	static uint8_t buffer[BUFFER_SIZE];
	size_t n_left = n_bytes;
	size_t count = 0;
	while ((n_left > 0) && (count = fread(buffer, sizeof(buffer[0]), min(n_left, BUFFER_SIZE), infile)) > 0) {
		fwrite(buffer, sizeof(buffer[0]), count, outfile);
		n_left -= count;
	}
	return n_bytes - n_left;
}

bool parse_args (int argc, char *argv[], vector<pair<string, size_t>>& files)
{
	if (argc <= 1) {
		cerr << "ERROR: no command line arguments." << endl;
		return false;
	}
	for (int k = 1; k < argc; k += 2) {
		string name = argv[k];
		string ssize = argv[k + 1];
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
		size_t size = p.second;
		outfile = fopen(name.c_str(), "w");
		if (size > 0)
			copy_to_file(infile, outfile, size);
		fclose(outfile);
	}

	return 0;
}
