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
	// 标准输入流
	ofstream fout;

	// 一个字节的buffer
	Byte buffer = 0;

	// buffer 中剩余的比特位, 默认初始化为 0
	int n = 0;

	// 指定文件名写入文件
	void writeFile(string& filename);

	// 将 buffer 中剩余的比特位输出, 如果有必要, 需要往后补 0 
	void clearBuffer();

	// 清空输出流, 如果到目前为止输出的比特数不是8的倍数, 那么需要补 0 
	void flush();

	// 一个比特位写入文件
	void writeBit(bool x);

	// 将8位字节写入输出流
	void writeByte(Byte x);

	// 将一个比特位写入输出流
	void write(bool x);

	// 将一个字节写入输出流
	void write(Byte x);

	// 将一个 size_t ( 8字节 ) 写入输出流
	void write(size_t x);

	// 清空并关闭输出流
	// 一旦关闭, 无法再写入比特位
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
	// 将 bit 加入 buffer
	buffer <<= 1;
	if (x)	
		buffer |= 1;

	// 如果 buffer 满了(n == 8), 以一个字节形式输出
	n++;
	if (n == 8)		
		clearBuffer();
}



void BinaryStdOut::writeByte(Byte x)
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
