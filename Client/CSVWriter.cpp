#include "CSVWriter.h"

CSVWriter::CSVWriter(std::string _filename, std::string _splitter) {
	filename = _filename;
	separator = _splitter;
	line = 0;
}


CSVWriter::CSVWriter(std::string filename) {
	filename = filename;
	separator = ",";
	line = 0;
}

void CSVWriter::addDatainRow(std::vector<std::string> list)
{
	std::fstream filehandle;

	filehandle.open(filename.c_str(), std::ios::out | (line ? std::ios::app : std::ios::trunc));
	filehandle << list.at(0) << separator << list.at(1) << "\n";
	line++;

	filehandle.close();
};