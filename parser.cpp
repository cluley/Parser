#include "parser.h"

ini_parser::ini_parser(const char filename[]) {
	config = std::make_shared<std::ifstream>(filename);
	if (!config->is_open()) throw std::logic_error("configuration file is couldn't be open");
	config->seekg(0);

	std::string captured{ "default" };
	std::string section{ "default" };
	std::string value{ "default" };
	int line_cntr(0);

	while (std::getline(*config, captured))
	{
		line_cntr++;

		if (captured.find(';') != std::string::npos)	captured.erase(captured.find(';'), captured.length());
		if (!captured.length()) continue;

		if (captured.starts_with('[') && captured.ends_with(']')) {
			captured.erase(0, 1);
			captured.pop_back();
			section = captured;
			
			data.try_emplace(section);
		}
		else if (captured.find('=') != std::string::npos) {
			if (data.empty()) {
				bad_syntax_lines.push_back(line_cntr);
				continue;
			}

			if (captured.find(';') != std::string::npos)	captured.erase(captured.find(';'), captured.length());

			value = captured.substr((captured.find('=') + 1), captured.length());
			captured.erase(captured.find('='), captured.length());
			
			if (!value.size()) continue;

			if (value.find('.') != std::string::npos && atof(value.c_str())) {
				double var = atof(value.c_str());
				if (data[section].contains(captured)) {
					data[section].at(captured) = var;
				}
				else {
					data[section].emplace(std::make_pair(captured, var));
				}
			}
			else if (atoi(value.c_str())) {
				int var = atoi(value.c_str());
				if (data[section].contains(captured)) {
					data[section].at(captured) = var;
				}
				else {
					data[section].emplace(std::make_pair(captured, var));
				}
			}
			else {
				if (data[section].contains(captured)) {
					data[section].at(captured) = value;
				}
				else {
					data[section].emplace(std::make_pair(captured, value));
				}
			}
		}
		else {
			if (captured.find(';') != std::string::npos) {
				continue;
			}
			else {
				bad_syntax_lines.push_back(line_cntr);
				continue;
			}
		}
	}
}

ini_parser& ini_parser::operator=(const ini_parser& other_parser) {
	config = other_parser.config;
	data = other_parser.data;
	bad_syntax_lines = other_parser.bad_syntax_lines;

	return *this;
}

ini_parser& ini_parser::operator=(ini_parser&& other_parser) noexcept {
	config = std::move(other_parser.config);
	data = std::move(other_parser.data);
	bad_syntax_lines = std::move(other_parser.bad_syntax_lines);

	return *this;
}

void ini_parser::info() const {
	std::cout << "#####\nData:" << std::endl;
	
	for (const auto& sec : data) {
		std::cout << '[' << sec.first << "]\n";
		for (const auto& val : sec.second) {
			std::cout << val.first << " = ";

			if (val.second.type() == typeid(int))
			{
				std::cout << std::any_cast<int>(val.second) << std::endl;
			}
			else if (val.second.type() == typeid(double))
			{
				std::cout << std::any_cast<double>(val.second) << std::endl;
			}
			else
			{
				std::cout << std::any_cast<std::string>(val.second) << std::endl;
			}
		}
	}

	std::cout << "#######################\nLines, with bad syntax: ";
	std::cout << *bad_syntax_lines.begin();
	for (auto itr = ++bad_syntax_lines.begin(); itr != bad_syntax_lines.end(); ++itr) {
		std::cout << ", " << *itr;
	}
	std::cout << std::endl;
}