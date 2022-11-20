#include <iostream>
#include <ctime>
#include "huffman.h"

using std::cout;
using std::cin;
using std::endl;


int main(void)
{
	int option;
	clock_t start, end;
	Huffman encode, decode;
	cout << "输入模式(1:压缩模式, 2:解压模式):\n";
	cin >> option;
	start = clock();
	if (option == 1)
		encode.compress("");
	else
		decode.decompress("");
	end = clock();
	cout << "用时: " << (double)(end - start)/CLOCKS_PER_SEC << "s.\n";
	system("pause");
	return 0;
}