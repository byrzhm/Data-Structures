#ifndef BINARYOUT_H
#define BINARYOUT_H


#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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


namespace BinaryStdOut
{
	// ��׼������
	ofstream fout;

	// һ���ֽڵ�buffer
	Byte buffer = 0;

	// buffer ��ʣ��ı���λ, Ĭ�ϳ�ʼ��Ϊ 0
	int n = 0;

	// ָ���ļ���д���ļ�
	void writeFile(string& filename);

	// �� buffer ��ʣ��ı���λ���, ����б�Ҫ, ��Ҫ���� 0 
	void clearBuffer();

	// ��������, �����ĿǰΪֹ����ı���������8�ı���, ��ô��Ҫ�� 0 
	void flush();

	// һ������λд���ļ�
	void writeBit(bool x);

	// ��8λ�ֽ�д�������
	void writeByte(Byte x);

	// ��һ������λд�������
	void write(bool x);

	// ��һ���ֽ�д�������
	void write(Byte x);

	// ��һ�� size_t ( 8�ֽ� ) д�������
	void write(size_t x);

	// ��ղ��ر������
	// һ���ر�, �޷���д�����λ
	void close();
}



void BinaryStdOut::writeFile(string& filename)
{
	fout.open(filename, ios::out | ios::binary);
	if (fout.fail())
	{
		cerr << "Cannot open file: \"" << filename << "\"!" << endl;
		exit(EXIT_FAILURE);
	}
}



void BinaryStdOut::clearBuffer()
{
	if (n == 0)
		return;
	if (n > 0)
		buffer <<= (8 - n);
	fout.write((char*)&buffer, 1);
	n = 0;
	buffer = 0;
}



void BinaryStdOut::flush()
{
	clearBuffer();
	fout.flush();
	if (fout.fail())
	{
		cerr << "File Error!" << endl;
		exit(EXIT_FAILURE);
	}
}



void BinaryStdOut::writeBit(bool x)
{
	// �� bit ���� buffer
	buffer <<= 1;
	if (x)	
		buffer |= 1;

	// ��� buffer ����(n == 8), ��һ���ֽ���ʽ���
	n++;
	if (n == 8)		
		clearBuffer();
}



void BinaryStdOut::writeByte(Byte x)
{
	// ��� buffer Ϊ��
	if (n == 0)
	{
		fout.write((char*)&x, 1);
		return;
	}
		
	// ����һ������һ���������
	for (int i = 0; i < 8; i++)
	{
		bool bit = ((x >> (8 - i + 1)) & 1) == 1;
		writeBit(bit);
	}

}



void BinaryStdOut::write(bool x)
{
	writeBit(x);
}



void BinaryStdOut::write(Byte x)
{
	writeByte(x & 0xff);
}


void BinaryStdOut::write(size_t x)
{
	for (int i = 0; i < sizeof(size_t); i++)
	{
		writeByte((x >> (8 * (sizeof(size_t) - i - 1))) & 0xff);
	}
}



void BinaryStdOut::close()
{
	flush();
	fout.close();
	if (fout.fail())
	{
		cerr << "File Error!" << endl;
		exit(EXIT_FAILURE);
	}
}





#endif // !BINARYOUT_H
