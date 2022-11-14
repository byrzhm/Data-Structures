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
	// ��׼������
	ifstream fin;

	// һ���ֽڵ�buffer
	Byte buffer;

	// buffer ��ʣ��ı���λ, Ĭ�ϳ�ʼ��Ϊ 0
	int n;

	// ָ���ļ�����ȡ�ļ�
	void readFile(string& filename);

	// �����ļ���ȡ
	void close();

	// �ļ���β�ж�
	bool feof();

	// װ�� buffer
	void fillBuffer();

	// ��ȡһ������λ
	bool readBool();

	// ��ȡһ���ֽ�
	char readChar();

	// ��ȡ size_t 
	size_t readSize_t();

	// ��ѡ�����ļ��Զ����Ʒ�ʽ���룬һ�ζ��� 1024 bytes
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
	// ʣ����������õ��� 8 bits
	if (n == 8) {
		Byte x = buffer;
		fillBuffer();
		return (char)x;
	}

	// ��ϵ�ǰ buffer �ĺ� n λ���� buffer ��ǰ 8-n λ
	Byte x = buffer;
	x <<= (8 - n);
	int oldN = n;
	fillBuffer();
	n = oldN;
	x |= (buffer >> n);
	return (char)x;
	// С�����һ���ַ�, �������ļ�β, buffer ���� 0xFF
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


