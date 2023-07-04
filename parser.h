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
	~ini_parser() = default;
	ini_parser(const ini_parser& other_parser) : 
		config(other_parser.config), data(other_parser.data), bad_syntax_lines(other_parser.bad_syntax_lines) {}
	ini_parser(ini_parser&& other_parser) noexcept :
		config(std::move(other_parser.config)), data(std::move(other_parser.data)), 
		bad_syntax_lines(std::move(other_parser.bad_syntax_lines)) {}

	ini_parser& operator=(const ini_parser& other_parser);
	ini_parser& operator=(ini_parser&& other_parser) noexcept;

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

	void info() const;
private:
	std::shared_ptr<std::ifstream> config;
	std::map <std::string, std::map <std::string, std::any>> data;
	std::list<int> bad_syntax_lines;
};