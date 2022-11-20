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

// 密码表的大小为 256
const int table_size = 256;

// 打印 Huffman 编码
void PrintCodes(const MinHeapNode* root, string str)
{
	if (root == NULL)
		return;

	if (IsLeaf(root))
		cout << root->symbol << ": " << str << endl;

	PrintCodes(root->left, str + '0');
	PrintCodes(root->right, str + '1');
}



// 判断是否是叶子节点
bool IsLeaf(const MinHeapNode* root)
{
	return root->left == NULL && root->right == NULL;
}




// 构造 Huffman 树
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





// 在二进制文件中写入 Huffman 树
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



// 从二进制文件中读取 Huffman 树
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



// 构建 Huffman 树 并打印
void HuffmanCodes(char* symbols, size_t* freqs, int size)
{
	MinHeapNode* left, * right, * parent;

	// 用 priority_queue 构造一个最小堆
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

	for (int i = 0; i < size; i++)
		minHeap.push(new MinHeapNode(symbols[i], freqs[i]));

	// 当最小堆只有一个节点的时候, 即 Huffman 树构造完成时, 结束循环
	while (minHeap.size() != 1)
	{
		// 从最小堆里取出两个freq最小的节点
		left = minHeap.top();
		minHeap.pop();

		right = minHeap.top();
		minHeap.pop();


		// 合并取出的两个节点
		// 构造一个新的节点, 它的左右子树分别是取出的两个节点
		// 它的symbol是 '*', 它的freq是左右孩子的freq的和
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



// 构造 Huffman 编码
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
		cout << "输入你想压缩的文件: ";
		cin >> filename;
	}
	BinaryStdIn::readFile(filename);
	char content[READ_SIZE];
	size_t input_length = 0;
	vector<size_t> freqs(table_size);

	cout << "正在读取并分析文件...";
	while (!BinaryStdIn::feof())
	{	// 获取文件内容, 计算每个字节的频率
		
		int count;
		input_length += (count = BinaryStdIn::readKB(content));
		
		for (int i = 0; i < count; i++)
			freqs[(int)(unsigned char)content[i]]++;
	}
	cout << "完成" << endl;
	BinaryStdIn::close();

	// 统计完之后再次打开文件
	BinaryStdIn::readFile(filename);

	// 新建一个文件准备写入压缩后的文件
	filename += ".dat";
	BinaryStdOut::writeFile(filename);

	// 构建 Huffman 编码树
	cout << "正在建立哈夫曼树...";
	MinHeapNode* root = buildTree(freqs);
	cout << "完成" << endl;

	// 构建编码表
	cout << "正在构建编码表...";
	vector<string> st(table_size);
	buildCode(st, root);
	cout << "完成" << endl;


	// 在二进制文件中写入编码树
	cout << "正在写入编码树...";
	writeTree(root);
	cout << "完成" << endl;



	// 在二进制文件中写入编码的字节数
	BinaryStdOut::write(input_length);

	// 用 Huffman code 编码输入文件
	double percent = 1.0;
	cout << "正在写入数据..." << endl;
	for (size_t i = 0; i < input_length; i++)
	{
		if (abs(100.0 * i / input_length - percent) < 1e-6)
		{
			cout << "已写入 " << percent << "%。\r";
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
	cout << "写入完成            " << endl;
	BinaryStdOut::close();
	BinaryStdIn::close();
	cout << "压缩完成" << endl;
}



void Huffman::decompress(string filename)
{
	if (filename == "")
	{
		cout << "输入你想解压的文件: ";
		cin >> filename;
	}
	BinaryStdIn::readFile(filename);
	cout << "请为解压文件命名: ";
	cin >> filename;
	BinaryStdOut::writeFile(filename);

	// 读取编码树
	cout << "正在读取编码树...";
	MinHeapNode* root = readTree();
	cout << "完成" << endl;

	// 读取文件大小
	cout << "正在读取文件大小...";
	size_t length = BinaryStdIn::readSize_t();
	cout << "完成" << endl;

	// 根据编码树解压文件
	double percent = 1.0;
	cout << "正在根据编码树解压文件..." << endl;
	for (size_t i = 0; i < length; i++)
	{
		if (abs(100.0 * i / length - percent) < 1e-6)
		{
			cout << "已解压 " << percent << "%。\r";
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
	cout << "完成            " << endl;
	BinaryStdOut::close();
	BinaryStdIn::close();
	cout << "解压完成" << endl;
}






