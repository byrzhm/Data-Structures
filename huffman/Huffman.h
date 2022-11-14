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
	// ����ǰ���ַ�
	char symbol;

	// �ַ����ı��е�Ƶ��
	size_t freq;

	// ������, ������
	MinHeapNode* left, * right;

	// ���캯��
	MinHeapNode(char symbol, size_t freq) :symbol(symbol), freq(freq), left(nullptr), right(nullptr) {};
	MinHeapNode(char symbol, size_t freq, MinHeapNode* left, MinHeapNode* right) :
		symbol(symbol), freq(freq), left(left), right(right) {};
};

class Huffman
{
public:
	// ѹ���ļ�
	void compress(string& filename);
	// ��ѹ���ļ�
	void decompress(string& filename);
};


// ������С����Ҫ�Ľṹ��compare
struct compare {
	bool operator()(MinHeapNode* left, MinHeapNode* right) {
		return left->freq > right->freq;
	}
};



// ��ӡ Huffman ����
void PrintCodes(const MinHeapNode* root, string str);

// �ж��Ƿ���Ҷ�ӽڵ�
bool IsLeaf(const MinHeapNode* root);

// ���� Huffman �� ����ӡ
void HuffmanCodes(char* symbols, size_t* freqs, int size);

// ���� Huffman ��
MinHeapNode* buildTree(vector<size_t>& freqs);

// ���� Huffman ����
void buildCode(vector<string>& code_table, MinHeapNode* root, string huffman_code);

// �ڶ������ļ���д�� Huffman ��
void writeTree(MinHeapNode* root);

// �Ӷ������ļ��ж�ȡ Huffman ��
MinHeapNode* readTree();


#endif // HUFFMAN_H