#include "BinaryOut.h"

// 标准输入流
ofstream BinaryStdOut::fout;

// 一个字节的buffer
int BinaryStdOut::buffer;

// buffer 中剩余的比特位, 默认初始化为 0
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
	// 将 bit 加入 buffer
	buffer <<= 1;
	if (x)
		buffer |= 1;

	// 如果 buffer 满了(n == 8), 以一个字节形式输出
	n++;
	if (n == 8)
		clearBuffer();
}



void BinaryStdOut::writeByte(char x)
{
	// 如果 buffer 为空
	if (n == 0)
	{
		fout.write((char*)&x, 1);
		return;
	}

	// 否则一个比特一个比特输出
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