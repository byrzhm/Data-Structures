#ifndef _BINARYIO_H_
#define _BINARYIO_H_

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


#endif // _BINARYIO_H_
