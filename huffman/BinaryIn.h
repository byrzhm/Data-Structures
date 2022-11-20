#ifndef BINARYIN_H
#define BINARYIN_H

#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::ifstream;
using std::ios;
using std::cout;
using std::cerr;
using std::endl;

const int READ_SIZE = 1024;

namespace BinaryStdIn
{
	// 标准输入流
	extern ifstream fin;

	// 一个字节 buffer
	extern int buffer;

	// buffer 中剩余的比特位, 默认初始化为 0
	extern int n;

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
	int readKB(char content[]);
};






#endif