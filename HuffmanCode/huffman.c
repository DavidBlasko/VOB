#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include "huffman.h"

#define MAX_TREE_HT 256

// Huffman tree node
struct MinHeapNode {
    char data;                          // Character
    unsigned freq;                      // Frequency of character
    struct MinHeapNode* left, * right;  // Left and right children
};

// Array to store Huffman codes for each character
char codes[256][MAX_TREE_HT];

// Create a new node for Huffman tree
struct MinHeapNode* createNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// Calculate character frequencies in the input string
void calcFrequencies(const char* str, int freq[], char* chars, int* uniqueCount) {
    int count[256] = { 0 };
    for (int i = 0; str[i]; i++)
        count[(unsigned char)str[i]]++;

    *uniqueCount = 0;
    for (int i = 0; i < 256; i++) {
        if (count[i]) {
            freq[*uniqueCount] = count[i];
            chars[*uniqueCount] = (char)i;
            (*uniqueCount)++;
        }
    }
}

// Build the Huffman tree from characters and their frequencies
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    // Create leaf nodes for each unique character
    struct MinHeapNode* nodes[256];
    for (int i = 0; i < size; i++)
        nodes[i] = createNode(data[i], freq[i]);

    // Combine nodes until there is only one node (the root)
    int n = size;
    while (n > 1) {
        int min1 = 0, min2 = 1;
        if (nodes[min2]->freq < nodes[min1]->freq) {
            int tmp = min1; min1 = min2; min2 = tmp;
        }

        for (int i = 2; i < n; i++) {
            if (nodes[i]->freq < nodes[min1]->freq) {
                min2 = min1;
                min1 = i;
            }
            else if (nodes[i]->freq < nodes[min2]->freq) {
                min2 = i;
            }
        }
        
        // Create new internal node with two minimum frequency children
        struct MinHeapNode* z = createNode('$', nodes[min1]->freq + nodes[min2]->freq);
        z->left = nodes[min1];
        z->right = nodes[min2];

        if (min1 > min2) {
            int tmp = min1; min1 = min2; min2 = tmp;
        }

        nodes[min1] = z;
        for (int i = min2 + 1; i < n; i++)
            nodes[i - 1] = nodes[i];
        n--;
    }

    return nodes[0];
}

// Recursively build Huffman codes for each character by traversing the tree
void buildCodes(struct MinHeapNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        buildCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        buildCodes(root->right, arr, top + 1);
    }

    if (!root->left && !root->right) {
        for (int i = 0; i < top; i++)
            codes[(unsigned char)root->data][i] = arr[i] + '0';
        codes[(unsigned char)root->data][top] = '\0';
    }
}

// Wrapper to initiate the code generation
void printCodes(struct MinHeapNode* root, int arr[], int top) {
    buildCodes(root, arr, top);
}

// Write the header to the compressed file (frequency table and text length)
void writeHeader(FILE* out, char chars[], int freq[], int uniqueCount, int textLength) {
    // Write number of unique characters
    fwrite(&uniqueCount, sizeof(int), 1, out);

    // Write each character and its frequency
    for (int i = 0; i < uniqueCount; i++) {
        fwrite(&chars[i], sizeof(char), 1, out);
        fwrite(&freq[i], sizeof(int), 1, out);
    }
    fwrite(&textLength, sizeof(int), 1, out); // Save original text length
}

// Compress a file using Huffman coding
void compress_file(const char* input_path, const char* output_path) {
    FILE* in = fopen(input_path, "r");
    if (!in) {
        perror("[ERR] Cannot open input file");
        return;
    }

    // Read entire input file into memory
    fseek(in, 0, SEEK_END);
    long len = ftell(in);
    rewind(in);
    char* text = malloc(len + 1);
    fread(text, 1, len, in);
    text[len] = '\0';
    fclose(in);

    // Build Huffman tree based on text frequencies
    int freq[256];
    char chars[256];
    int uniqueCount = 0;
    calcFrequencies(text, freq, chars, &uniqueCount);
    struct MinHeapNode* root = buildHuffmanTree(chars, freq, uniqueCount);
    int arr[MAX_TREE_HT];
    printCodes(root, arr, 0);

    // Open output file and write header
    FILE* out = fopen(output_path, "wb");
    writeHeader(out, chars, freq, uniqueCount, (int)strlen(text));

    // Encode and write text as bits
    uint8_t buffer = 0;
    int bit_count = 0;
    for (int i = 0; text[i]; i++) {
        char* code = codes[(unsigned char)text[i]];
        for (int j = 0; code[j]; j++) {
            buffer <<= 1;
            if (code[j] == '1') buffer |= 1;
            bit_count++;
            if (bit_count == 8) {
                fwrite(&buffer, 1, 1, out);
                buffer = 0;
                bit_count = 0;
            }
        }
    }
    if (bit_count) {
        buffer <<= (8 - bit_count);
        fwrite(&buffer, 1, 1, out);
    }

    fclose(out);
    free(text);
    printf("[INFO] Compression done.\n");
}

// Read and rebuild the Huffman tree and text length from the file header
struct MinHeapNode* rebuildTreeFromHeader(FILE* in, int* textLength) {
    int uniqueCount;
    fread(&uniqueCount, sizeof(int), 1, in);
    char chars[256];
    int freq[256];
    for (int i = 0; i < uniqueCount; i++) {
        fread(&chars[i], sizeof(char), 1, in);
        fread(&freq[i], sizeof(int), 1, in);
    }
    fread(textLength, sizeof(int), 1, in);
    return buildHuffmanTree(chars, freq, uniqueCount);
}

// Decompress a file encoded with Huffman coding
void decompress_file(const char* input_path, const char* output_path) {
    FILE* in = fopen(input_path, "rb");
    if (!in) {
        perror("[ERR] Cannot open input file");
        return;
    }

    // Rebuild Huffman tree from header
    int textLength = 0;
    struct MinHeapNode* root = rebuildTreeFromHeader(in, &textLength);
    struct MinHeapNode* curr = root;
    FILE* out = fopen(output_path, "w");

    // Read bits and traverse the Huffman tree
    int decodedChars = 0;
    int byte;
    while (decodedChars < textLength) {
        byte = fgetc(in);
        if (byte == EOF) break;

        for (int i = 7; i >= 0; i--) {
            if (decodedChars >= textLength) break;
            int bit = (byte >> i) & 1;
            curr = bit ? curr->right : curr->left;
            if (!curr->left && !curr->right) {
                fputc(curr->data, out);
                curr = root;
                decodedChars++;
            }
        }
    }

    fclose(in);
    fclose(out);
    printf("[INFO] Decompression done.\n");
}

// Compress a string (in memory)
void compress_message(const char* input, const char* output_path) {
    int freq[256];
    char chars[256];
    int uniqueCount = 0;
    calcFrequencies(input, freq, chars, &uniqueCount);
    struct MinHeapNode* root = buildHuffmanTree(chars, freq, uniqueCount);
    int arr[MAX_TREE_HT];
    printCodes(root, arr, 0);

    FILE* out = stdout;
    if (output_path != NULL) out = fopen(output_path, "w");
    if (!out) {
        perror("[ERR] Cannot open output file");
        return;
    }

    for (int i = 0; input[i]; ++i) {
        fprintf(out, "%s", codes[(unsigned char)input[i]]);
    }

    if (output_path != NULL) fclose(out);
    printf("\n[INFO] String compression done.\n");
}

// Decompress a string (in memory)
void decompress_message(const char* input, const char* output_path) {
    fprintf(stderr, "[WARN] Decompression from encoded string not supported in full mode. Use .huff files.\n");
}
