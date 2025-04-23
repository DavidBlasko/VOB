#ifndef HUFFMAN_H
#define HUFFMAN_H

// Forward declaration of Huffman tree node
struct MinHeapNode;

// Compress and Decompress functions
void compress_message(const char* input, const char* output_path);
void decompress_message(const char* input, const char* output_path);
void compress_file(const char* input_path, const char* output_path);
void decompress_file(const char* input_path, const char* output_path);

#endif