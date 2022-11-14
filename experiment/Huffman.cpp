#include "Huffman.h"


//class Huffman
//{
//public:
//	// ѹ���ļ�
//	void compress(string& filename);
//	// ��ѹ���ļ�
//	void decompress(string& filename);
//};

inline void Huffman::compress(string& filename)
{
	if (filename == "")
		cin >> filename;
	BinaryStdIn::readFile(filename);
	Input input;
	vector<size_t> freqs(table_size);

	while (!BinaryStdIn::feof())
	{
		// ��ȡ�ļ�����, ����ÿ���ֽڵ�Ƶ��
		BinaryStdIn::readKB(input.content);
		input.length += input.content.size();

		for (int i = 0; i < input.content.size(); i++)
			freqs[(unsigned char)input.content[i]]++;
	}
	BinaryStdIn::close();

	// ͳ����֮���ٴδ��ļ�
	BinaryStdIn::readFile(filename);

	// �½�һ���ļ�׼��д��ѹ������ļ�
	filename += ".z";
	BinaryStdOut::writeFile(filename);

	// ���� Huffman ������
	MinHeapNode* root = buildTree(freqs);

	// ���������
	vector<string> st(table_size);
	buildCode(st, root, "");

	// �ڶ������ļ���д�������
	writeTree(root);

	// �ڶ������ļ���д�������ֽ���
	BinaryStdOut::write(input.length);

	// �� Huffman code ���������ļ�
	for (size_t i = 0; i < input.length; i++)
	{
		char ch = BinaryStdIn::readChar();
		if (!BinaryStdIn::feof())
		{
			string code = st[ch];
			for (int j = 0; j < code.size(); j++)
				if (code.at(j) == '1')
					BinaryStdOut::write(true);
				else
					BinaryStdOut::write(false);
		}
	}
	BinaryStdOut::close();
	BinaryStdIn::close();
}



inline void Huffman::decompress(string& filename)
{

}



// ��ӡ Huffman ����
void PrintCodes(const MinHeapNode* root, string str)
{
	if (root == NULL)
		return;

	if (IsLeaf(root))
		cout << root->symbol << ": " << str << endl;

	PrintCodes(root->left, str + '0');
	PrintCodes(root->right, str + '1');
}



// �ж��Ƿ���Ҷ�ӽڵ�
bool IsLeaf(const MinHeapNode* root)
{
	return root->left == NULL && root->right == NULL;
}



// ���� Huffman �� ����ӡ
void HuffmanCodes(char* symbols, size_t* freqs, int size)
{
	MinHeapNode* left, * right, * parent;

	// �� priority_queue ����һ����С��
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

	for (int i = 0; i < size; i++)
		minHeap.push(new MinHeapNode(symbols[i], freqs[i]));

	// ����С��ֻ��һ���ڵ��ʱ��, �� Huffman ���������ʱ, ����ѭ��
	while (minHeap.size() != 1)
	{
		// ����С����ȡ������freq��С�Ľڵ�
		left = minHeap.top();
		minHeap.pop();

		right = minHeap.top();
		minHeap.pop();


		// �ϲ�ȡ���������ڵ�
		// ����һ���µĽڵ�, �������������ֱ���ȡ���������ڵ�
		// ����symbol�� '*', ����freq�����Һ��ӵ�freq�ĺ�
		parent = new MinHeapNode('*', left->freq + right->freq);

		parent->left = left;
		parent->right = right;

		minHeap.push(parent);
	}

	PrintCodes(minHeap.top(), "");
}



// ���� Huffman ��
MinHeapNode* buildTree(vector<size_t>& freqs)
{
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
	for (int c = 0; c < table_size; c++)
		minHeap.push(new MinHeapNode((char)c, freqs[c]));
	while (minHeap.size() != 1)
	{
		MinHeapNode* left = minHeap.top();
		minHeap.pop();

		MinHeapNode* right = minHeap.top();
		minHeap.pop();

		MinHeapNode* parent = new MinHeapNode('*', left->freq + right->freq);
		parent->left = left;
		parent->right = right;
		minHeap.push(parent);
	}
	return minHeap.top();
}


// ���� Huffman ����
void buildCode(vector<string>& code_table, MinHeapNode* root, string huffman_code)
{
	if (IsLeaf(root))
	{
		code_table[root->symbol] = huffman_code;
		return;
	}
	buildCode(code_table, root->left, huffman_code + '0');
	buildCode(code_table, root->right, huffman_code + '1');
}



// �ڶ������ļ���д�� Huffman ��
void writeTree(MinHeapNode* root)
{
	if (IsLeaf(root))
	{
		BinaryStdOut::write(true);
		BinaryStdOut::write((Byte)root->symbol);
		return;
	}
	BinaryStdOut::write(false);
	writeTree(root->left);
	writeTree(root->right);
}



// �Ӷ������ļ��ж�ȡ Huffman ��
MinHeapNode* readTree()
{
	if (BinaryStdIn::readBool())
		return new MinHeapNode(BinaryStdIn::readChar(), 0, nullptr, nullptr);
	return new MinHeapNode('*', 0, readTree(), readTree());
}
