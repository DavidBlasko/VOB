## 📚 Overview: What is Huffman Coding?

**Huffman coding** is a lossless data compression algorithm developed by David A. Huffman in 1952. 
It uses variable-length binary codes to represent characters, assigning shorter codes to more frequent characters 
and longer codes to less frequent ones. This optimizes the overall length of the compressed data.

The process consists of:
- Building a binary tree where each character is a leaf node.
- Combining nodes based on character frequencies into a tree structure.
- Traversing the tree to assign codes: left traversal adds a '0', right traversal adds a '1'.

The final compressed data, along with a header containing frequency information, allows reconstruction of the original data without loss.

---

# Huffman CLI Compressor / Decompressor

![Language](https://img.shields.io/badge/language-C-blue)
![License](https://img.shields.io/badge/license-MIT-green)

A simple command-line Huffman encoder and decoder written in pure C (C23 standard). This project demonstrates lossless data compression using the Huffman coding algorithm, capable of reading from text or file inputs and producing binary `.huff` outputs.

---

## 📦 Features

- Encode plain text input or file content using Huffman coding.
- Decode compressed `.huff` binary files back to readable text.
- CLI interface with standard arguments (`-i`, `-o`, `-m`, `-c`, `-d`).
- File headers contain full frequency tables to rebuild Huffman trees.
- Fully self-contained implementation in ANSI C (C23 compatible).
- Lightweight, fast, and easy to integrate or extend.

---

## 🚀 Getting Started

### ✅ Compilation

You can compile the project with any C compiler that supports C23. Example with GCC:

```bash
gcc -std=c23 -o huffman main.c huffman.c
```

### 🖥️ Running

#### Compression from file:

```bash
./huffman -i input.txt -o output.huff -c
```

#### Decompression to file:

```bash
./huffman -i output.huff -o decoded.txt -d
```

#### Compression from inline message:

```bash
./huffman -m "hello huffman compression" -c
```

> Note: Output is written to stdout unless `-o` is provided.

---

## 🔧 CLI Parameters

| Flag             | Description                              | Example                    |
|------------------|------------------------------------------|----------------------------|
| `-i`, `--input`  | Input file path                          | `-i input.txt`             |
| `-o`, `--output` | Output file path                         | `-o compressed.huff`       |
| `-m`, `--msg`    | Message to compress                      | `-m "hello world"`         |
| `-c`, `--comp`   | Enable compression                       | `-c`                       |
| `-d`, `--decomp` | Enable decompression                     | `-d`                       |

---

## 📁 File Format

The `.huff` file includes:
1. Header:
   - Number of unique characters (int)
   - List of characters and their frequencies
2. Encoded data in binary form

This allows reconstruction of the Huffman tree during decompression.

---

## 🛠️ How Huffman Coding Works in This Project

This project implements Huffman coding based on the construction of a binary tree.

### 1. Building the Huffman Tree
- First, the frequency of each character in the input text is calculated.
- Each character becomes a leaf node with its frequency.
- Two nodes with the lowest frequencies are selected and combined into a new internal node.
- This process repeats until only one node remains: the root of the tree.

### 2. Generating Huffman Codes
- The tree is traversed recursively:
  - Going left adds a `0` to the code.
  - Going right adds a `1` to the code.
- Each character is assigned its unique binary string based on the path from the root.

### 3. Compression Process
- The original text is replaced by the corresponding Huffman codes.
- Bits are grouped into bytes for efficient storage.
- Before the encoded data, a header is written:
  - The number of unique characters.
  - Each character and its frequency.
- This header allows full reconstruction of the Huffman tree during decompression.

### 4. Decompression Process
- The header is read first to rebuild the Huffman tree.
- The compressed bitstream is then traversed:
  - A `0` moves left in the tree.
  - A `1` moves right.
- Each time a leaf node is reached, the corresponding character is output.

### 5. File Structure
The `.huff` file consists of:
- [Header]
  - Number of unique characters (int)
  - List of (character, frequency) pairs
- [Compressed Data]
  - Raw Huffman-encoded bits grouped into bytes

This ensures that decompression is completely self-contained and does not require external metadata.

## 📂 Project Structure

```text
├── main.c          # CLI entry point and argument parsing
├── huffman.c       # Core Huffman logic (compression, decompression)
├── huffman.h       # Header file with function declarations
└── README.md       # Project documentation
```

---

## 🙌 Credits

Developed as part of a coursework project. Includes standard Huffman coding principles and bit-level I/O.
