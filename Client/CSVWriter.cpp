#include "CSVWriter.h"

CSVWriter::CSVWriter(std::string filename, std::string splitter) {
	filnavn = filename;
	dele = splitter;
	linje = 0;
}


CSVWriter::CSVWriter(std::string filename) {
	filnavn = filename;
	dele = ",";
	linje = 0;
}

void CSVWriter::addDatainRow(std::vector<std::string> list)
{
	std::fstream fil;

	fil.open(filnavn, std::ios::out | (linje ? std::ios::app : std::ios::trunc));
	fil << list.at(0) << dele << list.at(1) << "\n";
	linje++;

	fil.close();
};