#include "huffman.h"
#include "BinaryIn.h"
#include "BinaryOut.h"

#include <stack>
#include <queue>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::priority_queue;
using std::stack;

// �����Ĵ�СΪ 256
const int table_size = 256;

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





// �ڶ������ļ���д�� Huffman ��
void writeTree(MinHeapNode* root)
{
	stack<MinHeapNode *> s;
	s.push(root);

	while (!s.empty())
	{
		MinHeapNode* pnode = s.top();
		s.pop();
		if (IsLeaf(pnode))
		{
			BinaryStdOut::write(true);
			BinaryStdOut::write((char)pnode->symbol);
		}
		else
		{
			BinaryStdOut::write(false);
			s.push(pnode->right);
			s.push(pnode->left);
		}
	}
}



// �Ӷ������ļ��ж�ȡ Huffman ��
MinHeapNode* readTree()
{
	MinHeapNode* root = new MinHeapNode('*', 0, nullptr, nullptr);
	stack<MinHeapNode **> s;
	s.push(&root);

	while (!s.empty())
	{
		MinHeapNode** ppnode = s.top();
		s.pop();
		if (BinaryStdIn::readBool())
			(*ppnode)->symbol = BinaryStdIn::readChar();
		else
		{
			(*ppnode)->left = new MinHeapNode('*', 0, nullptr, nullptr);
			(*ppnode)->right = new MinHeapNode('*', 0, nullptr, nullptr);
			s.push(&(*ppnode)->right);
			s.push(&(*ppnode)->left);
		}
	}
	return root;
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


static struct pair
{
	MinHeapNode* ptr;
	string str;
	pair(MinHeapNode* ptr, string str) :ptr(ptr),str(str){};
};



// ���� Huffman ����
void buildCode(vector<string>& code_table, MinHeapNode* root)
{
	pair cp(root, "");
	stack<pair> s;
	s.push(cp);

	while (!s.empty())
	{
		pair temp = s.top();
		s.pop();

		if (IsLeaf(temp.ptr))
			code_table[(unsigned char)(temp.ptr)->symbol] = temp.str;
		else
		{
			s.push(pair(temp.ptr->right, temp.str + '1'));
			s.push(pair(temp.ptr->left, temp.str + '0'));
		}
	}
}



void Huffman::compress(string filename)
{
	if (filename == "")
	{
		cout << "��������ѹ�����ļ�: ";
		cin >> filename;
	}
	BinaryStdIn::readFile(filename);
	char content[READ_SIZE];
	size_t input_length = 0;
	vector<size_t> freqs(table_size);

	cout << "���ڶ�ȡ�������ļ�...";
	while (!BinaryStdIn::feof())
	{	// ��ȡ�ļ�����, ����ÿ���ֽڵ�Ƶ��
		
		int count;
		input_length += (count = BinaryStdIn::readKB(content));
		
		for (int i = 0; i < count; i++)
			freqs[(int)(unsigned char)content[i]]++;
	}
	cout << "���" << endl;
	BinaryStdIn::close();

	// ͳ����֮���ٴδ��ļ�
	BinaryStdIn::readFile(filename);

	// �½�һ���ļ�׼��д��ѹ������ļ�
	filename += ".dat";
	BinaryStdOut::writeFile(filename);

	// ���� Huffman ������
	cout << "���ڽ�����������...";
	MinHeapNode* root = buildTree(freqs);
	cout << "���" << endl;

	// ���������
	cout << "���ڹ��������...";
	vector<string> st(table_size);
	buildCode(st, root);
	cout << "���" << endl;


	// �ڶ������ļ���д�������
	cout << "����д�������...";
	writeTree(root);
	cout << "���" << endl;



	// �ڶ������ļ���д�������ֽ���
	BinaryStdOut::write(input_length);

	// �� Huffman code ���������ļ�
	double percent = 1.0;
	cout << "����д������..." << endl;
	for (size_t i = 0; i < input_length; i++)
	{
		if (abs(100.0 * i / input_length - percent) < 1e-6)
		{
			cout << "��д�� " << percent << "%��\r";
			percent += 1.0;
		}


		unsigned char ch = BinaryStdIn::readChar();
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
	cout << "д�����            " << endl;
	BinaryStdOut::close();
	BinaryStdIn::close();
	cout << "ѹ�����" << endl;
}



void Huffman::decompress(string filename)
{
	if (filename == "")
	{
		cout << "���������ѹ���ļ�: ";
		cin >> filename;
	}
	BinaryStdIn::readFile(filename);
	cout << "��Ϊ��ѹ�ļ�����: ";
	cin >> filename;
	BinaryStdOut::writeFile(filename);

	// ��ȡ������
	cout << "���ڶ�ȡ������...";
	MinHeapNode* root = readTree();
	cout << "���" << endl;

	// ��ȡ�ļ���С
	cout << "���ڶ�ȡ�ļ���С...";
	size_t length = BinaryStdIn::readSize_t();
	cout << "���" << endl;

	// ���ݱ�������ѹ�ļ�
	double percent = 1.0;
	cout << "���ڸ��ݱ�������ѹ�ļ�..." << endl;
	for (size_t i = 0; i < length; i++)
	{
		if (abs(100.0 * i / length - percent) < 1e-6)
		{
			cout << "�ѽ�ѹ " << percent << "%��\r";
			percent += 1.0;
		}

		MinHeapNode* x = root;
		while (!IsLeaf(x))
			if (BinaryStdIn::readBool())
				x = x->right;
			else
				x = x->left;
		BinaryStdOut::write((char)x->symbol);
	}
	cout << "���            " << endl;
	BinaryStdOut::close();
	BinaryStdIn::close();
	cout << "��ѹ���" << endl;
}






