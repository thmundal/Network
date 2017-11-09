#pragma once
#include <fstream>
#include <vector>
#include <string>

class CSVWriter
{
private:
	std::string filename;
	std::string separator;
	int line;
public:
	CSVWriter(std::string, std::string);
	CSVWriter(std::string);

	void addDatainRow(std::vector<std::string>);
};
