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
	cout << "����ģʽ(1:ѹ��ģʽ, 2:��ѹģʽ):\n";
	cin >> option;
	start = clock();
	if (option == 1)
		encode.compress("");
	else
		decode.decompress("");
	end = clock();
	cout << "��ʱ: " << (double)(end - start)/CLOCKS_PER_SEC << "s.\n";
	system("pause");
	return 0;
}