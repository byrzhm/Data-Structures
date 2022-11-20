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
	// ��׼������
	extern ifstream fin;

	// һ���ֽ� buffer
	extern int buffer;

	// buffer ��ʣ��ı���λ, Ĭ�ϳ�ʼ��Ϊ 0
	extern int n;

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
	int readKB(char content[]);
};






#endif