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
	return 0;
}