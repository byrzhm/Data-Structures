#ifndef BINARYOUT_H
#define BINARYOUT_H

#include <iostream>
#include <fstream>
#include <string>

using std::ofstream;
using std::string;
using std::ios;
using std::cout;
using std::cerr;
using std::endl;

namespace BinaryStdOut
{
	// 标准输入流
	extern ofstream fout;

	// 一个字节的buffer
	extern int buffer;

	// buffer 中剩余的比特位, 默认初始化为 0
	extern int n;

	// 指定文件名写入文件
	void writeFile(string& filename);

	// 将 buffer 中剩余的比特位输出, 如果有必要, 需要往后补 0 
	void clearBuffer();

	// 清空输出流, 如果到目前为止输出的比特数不是8的倍数, 那么需要补 0 
	void flush();

	// 一个比特位写入文件
	void writeBit(bool x);

	// 将8位字节写入输出流
	void writeByte(char x);

	// 将一个比特位写入输出流
	void write(bool x);

	// 将一个字节写入输出流
	void write(char x);

	// 将一个 size_t ( 8字节 ) 写入输出流
	void write(size_t x);

	// 清空并关闭输出流
	// 一旦关闭, 无法再写入比特位
	void close();
}

#endif