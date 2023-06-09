#include <iostream>

#include "parser.h"

using namespace std;

int main(int argc, char** argv) {
	ini_parser parser("file.ini");
	parser.show_data();
	parser.bad_syntax();

	auto value = parser.get_value<double>("section3.var2");
	cout << value << endl;

	return 0;
}