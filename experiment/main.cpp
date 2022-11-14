#include "BinaryIO.h"
#include "BinaryIn.h"
#include "BinaryOut.h"
#include "Huffman.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <assert.h>

using namespace std;



int main(int argc, char const *argv[])
{
	string filename = "student.dat";
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
	return 0;
}