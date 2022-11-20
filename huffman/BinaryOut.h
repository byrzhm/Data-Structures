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
	// ��׼������
	extern ofstream fout;

	// һ���ֽڵ�buffer
	extern int buffer;

	// buffer ��ʣ��ı���λ, Ĭ�ϳ�ʼ��Ϊ 0
	extern int n;

	// ָ���ļ���д���ļ�
	void writeFile(string& filename);

	// �� buffer ��ʣ��ı���λ���, ����б�Ҫ, ��Ҫ���� 0 
	void clearBuffer();

	// ��������, �����ĿǰΪֹ����ı���������8�ı���, ��ô��Ҫ�� 0 
	void flush();

	// һ������λд���ļ�
	void writeBit(bool x);

	// ��8λ�ֽ�д�������
	void writeByte(char x);

	// ��һ������λд�������
	void write(bool x);

	// ��һ���ֽ�д�������
	void write(char x);

	// ��һ�� size_t ( 8�ֽ� ) д�������
	void write(size_t x);

	// ��ղ��ر������
	// һ���ر�, �޷���д�����λ
	void close();
}

#endif