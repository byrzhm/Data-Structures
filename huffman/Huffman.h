#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <vector>


using std::vector;
using std::string;


// �����Ĵ�СΪ 256
extern const int table_size;


class Huffman {
public:
	// ѹ���ļ�
	void compress(string filename);
	// ��ѹ���ļ�
	void decompress(string filename);
};



struct MinHeapNode {
	// ����ǰ���ַ�
	char symbol;

	// �ַ����ı��е�Ƶ��
	size_t freq;

	// ������, ������
	MinHeapNode* left, * right;

	// ���캯��
	MinHeapNode(char symbol, size_t freq) :
		symbol(symbol), freq(freq), left(nullptr), right(nullptr) {};
	MinHeapNode(char symbol, size_t freq, MinHeapNode* left, MinHeapNode* right) :
		symbol(symbol), freq(freq), left(left), right(right) {};
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
void buildCode(vector<string>& code_table, MinHeapNode* root);

// �ڶ������ļ���д�� Huffman ��
void writeTree(MinHeapNode* root);

// �Ӷ������ļ��ж�ȡ Huffman ��
MinHeapNode* readTree();



#endif