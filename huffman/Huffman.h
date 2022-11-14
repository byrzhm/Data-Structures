#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "BinaryIn.h"
#include "BinaryOut.h"

#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

const int table_size = 256;

struct MinHeapNode
{
	// 编码前的字符
	char symbol;

	// 字符在文本中的频率
	size_t freq;

	// 左子树, 右子树
	MinHeapNode* left, * right;

	// 构造函数
	MinHeapNode(char symbol, size_t freq) :symbol(symbol), freq(freq), left(nullptr), right(nullptr) {};
	MinHeapNode(char symbol, size_t freq, MinHeapNode* left, MinHeapNode* right) :
		symbol(symbol), freq(freq), left(left), right(right) {};
};

class Huffman
{
public:
	// 压缩文件
	void compress(string& filename);
	// 解压缩文件
	void decompress(string& filename);
};


// 建立最小堆需要的结构体compare
struct compare {
	bool operator()(MinHeapNode* left, MinHeapNode* right) {
		return left->freq > right->freq;
	}
};



// 打印 Huffman 编码
void PrintCodes(const MinHeapNode* root, string str);

// 判断是否是叶子节点
bool IsLeaf(const MinHeapNode* root);

// 构建 Huffman 树 并打印
void HuffmanCodes(char* symbols, size_t* freqs, int size);

// 构造 Huffman 树
MinHeapNode* buildTree(vector<size_t>& freqs);

// 构造 Huffman 编码
void buildCode(vector<string>& code_table, MinHeapNode* root, string huffman_code);

// 在二进制文件中写入 Huffman 树
void writeTree(MinHeapNode* root);

// 从二进制文件中读取 Huffman 树
MinHeapNode* readTree();


#endif // HUFFMAN_H