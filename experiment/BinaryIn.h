#ifndef BINARYIN_H
#define BINARYIN_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

const int READ_SIZE = 1024;

#ifndef DATASTTTRUCTURE
#define DATASTTTRUCTURE

typedef std::vector<char> StringVector;
struct Input {
	StringVector content;
	size_t length;
	Input() :length(0) {};
};
typedef unsigned char Byte;

#endif // !DATASTTTRUCTURE


using namespace std;


namespace BinaryStdIn
{
	// 标准输入流
	ifstream fin;

	// 一个字节的buffer
	Byte buffer;

	// buffer 中剩余的比特位, 默认初始化为 0
	int n;

	// 指定文件名读取文件
	void readFile(string& filename);

	// 结束文件读取
	void close();

	// 文件结尾判断
	bool feof();

	// 装载 buffer
	void fillBuffer();

	// 读取一个比特位
	bool readBool();

	// 读取一个字节
	char readChar();

	// 读取 size_t 
	size_t readSize_t();

	// 对选定的文件以二进制方式读入，一次读入 1024 bytes
	void readKB(StringVector& content);
};



void BinaryStdIn::readFile(string& filename)
{
	fin.open(filename, ios::in | ios::binary);
	if (fin.fail())
	{
		cerr << "Cannot open file: \"" << filename << "\"" << endl;
		exit(EXIT_FAILURE);
	}
}



void BinaryStdIn::close() 
{
	fin.close();
	if (fin.fail())
	{
		cerr << "File Error!"  << endl;
		exit(EXIT_FAILURE);
	}
}



bool BinaryStdIn::feof()
{
	return fin.eof();
}



void BinaryStdIn::fillBuffer()
{
	if (!fin.eof())
	{
		fin.read((char*)&buffer, 1);
		n = 8;
	}
	else
	{
		cerr << "EOF" << endl;
		buffer = -1;
	}
}



bool BinaryStdIn::readBool()
{
	if (n == 0)
		fillBuffer();
	if (n != 0)
		n--;
	return	((buffer >> n) & 1) == 1;
}



char BinaryStdIn::readChar()
{
	// 剩余比特数正好等于 8 bits
	if (n == 8) {
		Byte x = buffer;
		fillBuffer();
		return (char)x;
	}

	// 组合当前 buffer 的后 n 位与新 buffer 的前 8-n 位
	Byte x = buffer;
	x <<= (8 - n);
	int oldN = n;
	fillBuffer();
	n = oldN;
	x |= (buffer >> n);
	return (char)x;
	// 小心最后一个字符, 当读到文件尾, buffer 会变成 0xFF
}



size_t BinaryStdIn::readSize_t()
{
	size_t x = 0;
	for (int i = 0; i < sizeof(size_t); i++)
	{
		char c = readChar();
		x <<= 8;
		x |= c;
	}
	return x;
}



void BinaryStdIn::readKB(StringVector& content)
{
	content.clear();
	for (int i = 0; i < READ_SIZE && !fin.eof(); i++)
	{
		char ch = readChar();
		if (!fin.eof())
			content.push_back(ch);
	}
}
#endif // !BINARYIN_H


