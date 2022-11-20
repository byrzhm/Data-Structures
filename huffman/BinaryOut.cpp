#include "BinaryOut.h"

// ��׼������
ofstream BinaryStdOut::fout;

// һ���ֽڵ�buffer
int BinaryStdOut::buffer;

// buffer ��ʣ��ı���λ, Ĭ�ϳ�ʼ��Ϊ 0
int BinaryStdOut::n;

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
		cerr << "File Error! (Error Type = OUTFLUSH)" << endl;
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



void BinaryStdOut::writeByte(char x)
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
		bool bit = (((unsigned char)x >> (8 - i - 1)) & 1) == 1;
		writeBit(bit);
	}

}



void BinaryStdOut::write(bool x)
{
	writeBit(x);
}



void BinaryStdOut::write(char x)
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
		cerr << "File Error! (Error Type = OUTCLOSE)" << endl;
		exit(EXIT_FAILURE);
	}
}