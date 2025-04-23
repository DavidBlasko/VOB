#include <stdio.h>
#include <string.h>
#include "huffman.h"

// CLI for Huffman compression and decompression - parses command line arguments and calls the appropriate functions
int main(int argc, char* argv[]) {
    const char* input_file = NULL;
    const char* output_file = NULL;
    const char* message = NULL;
    int compress = 0, decompress = 0;

    for (int i = 1; i < argc; ++i) {
        if ((strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) && i + 1 < argc) {
            input_file = argv[++i];
        }
        else if ((strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) && i + 1 < argc) {
            output_file = argv[++i];
        }
        else if ((strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--msg") == 0) && i + 1 < argc) {
            message = argv[++i];
        }
        else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--comp") == 0) {
            compress = 1;
        }
        else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--decomp") == 0) {
            decompress = 1;
        }
    }

    if (compress) {
        if (message) {
            compress_message(message, output_file);
        }
        else if (input_file && output_file) {
            compress_file(input_file, output_file);
        }
        else {
            fprintf(stderr, "[ERR] Error at input/output files for compression.\n");
        }
    }
    else if (decompress) {
        if (message) {
            decompress_message(message, output_file);
        }
        else if (input_file && output_file) {
            decompress_file(input_file, output_file);
        }
        else {
            fprintf(stderr, "[ERR] Error at input/output files for decompression.\n");
        }
    }
    else {
        fprintf(stderr, "[ERR] Unspecified operation (use -c/--comp or -d/--decomp).\n");
    }

    return 0;
}
