#include "Huffman.h"


//class Huffman
//{
//public:
//	// 压缩文件
//	void compress(string& filename);
//	// 解压缩文件
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
		// 获取文件内容, 计算每个字节的频率
		BinaryStdIn::readKB(input.content);
		input.length += input.content.size();

		for (int i = 0; i < input.content.size(); i++)
			freqs[(unsigned char)input.content[i]]++;
	}
	BinaryStdIn::close();

	// 统计完之后再次打开文件
	BinaryStdIn::readFile(filename);

	// 新建一个文件准备写入压缩后的文件
	filename += ".z";
	BinaryStdOut::writeFile(filename);

	// 构建 Huffman 编码树
	MinHeapNode* root = buildTree(freqs);

	// 构建编码表
	vector<string> st(table_size);
	buildCode(st, root, "");

	// 在二进制文件中写入编码树
	writeTree(root);

	// 在二进制文件中写入编码的字节数
	BinaryStdOut::write(input.length);

	// 用 Huffman code 编码输入文件
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


// 构造 Huffman 编码
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



// 在二进制文件中写入 Huffman 树
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



// 从二进制文件中读取 Huffman 树
MinHeapNode* readTree()
{
	if (BinaryStdIn::readBool())
		return new MinHeapNode(BinaryStdIn::readChar(), 0, nullptr, nullptr);
	return new MinHeapNode('*', 0, readTree(), readTree());
}
