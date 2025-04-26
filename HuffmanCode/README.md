# Huffman CLI Compressor / Decompressor

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
