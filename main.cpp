#include <iostream>

#include "parser.h"

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
	ini_parser parser("C:/Users/oo43/Documents/file.ini");
	parser.info();	

	auto value = parser.get_value<double>("section3.var2");
	cout << value << endl;

	ini_parser parser2("C:/Users/oo43/Documents/file2.ini");
	parser = parser2;
	parser.info();

	return 0;
}