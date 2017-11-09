#pragma once
#include <fstream>
#include <vector>
#include <string>

class CSVWriter
{
private:
	std::string filnavn;
	std::string dele;
	int linje;
public:
	CSVWriter(std::string, std::string);
	CSVWriter(std::string);

	void addDatainRow(std::vector<std::string>);
};
