#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <any>

class ini_parser {
public:
	ini_parser(const char filename[]);

	template<typename T>
	T get_value(std::string&& request) {
		if (request.find('.') == std::string::npos) throw std::logic_error("incorrect request");

		std::string requested_val = request.substr((request.find('.') + 1), request.length());
		request.erase(request.find('.'), request.length());

		if (data[request].contains(requested_val)) {
			return any_cast<T>(data[request][requested_val]);
		}
		else throw std::invalid_argument("there are no values matching the request");
	}

	void show_data() const;
	void bad_syntax() const;
private:
	std::unique_ptr<std::ifstream> config;
	std::map <std::string, std::map <std::string, std::any>> data;
	std::list<int> bad_syntax_lines;
};