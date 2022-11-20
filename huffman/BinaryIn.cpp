#include "BinaryIn.h"

// 标准输入流
ifstream BinaryStdIn::fin;

// 一个字节 buffer, 默认初始化为 0
int BinaryStdIn::buffer;

// buffer 中剩余的比特位, 默认初始化为 0
int BinaryStdIn::n;


void BinaryStdIn::readFile(string& filename)
{
	fin.open(filename, ios::in | ios::binary);
	if (fin.fail())
	{
		cerr << "Cannot open file: \"" << filename << "\"" << endl;
		exit(EXIT_FAILURE);
	}
}



void BinaryStdIn::close() {
	if (fin.is_open())
		fin.close();
}



bool BinaryStdIn::feof() { return fin.eof(); }



void BinaryStdIn::fillBuffer()
{
	if (!fin.eof())
	{
		fin.read((char*)&buffer, 1);
		n = 8;
	}
	else if (n == 0)
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
		int x = buffer;
		fillBuffer();
		return (char)x;
	}

	// 组合当前 buffer 的后 n 位与新 buffer 的前 8-n 位
	int x = buffer;
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
	size_t ret = 0;
	for (int i = 0; i < sizeof(size_t); i++)
	{
		unsigned char c = readChar();
		ret <<= 8;
		ret |= c;
	}
	return ret;
}



int BinaryStdIn::readKB(char content[])
{
	int count = 0;
	for (int i = 0; i < READ_SIZE && !fin.eof(); i++)
	{
		char ch = readChar();
		if (!fin.eof()) {
			content[i] = ch;
			count++;
		}
	}
	return count;
}