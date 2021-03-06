// numbersForMLP.cpp : Defines the entry point for the console application.
//

// Include Headers
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

using namespace std;

//Global Variables
char filename[MAX_PATH];
string fname;


// Get file name function
string  GetFileName(const string & prompt) {
	cout << prompt;
	string name;
	getline(cin, name);
	return name;
}

int main()
{
	int counter;

	OPENFILENAMEA ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
	ofn.lpstrFilter = "Data files\0*.test;*.train;*.csv\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Choose train or test file";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn))
	{
		std::cout << "You chose the file \"" << filename << "\"\n\n";
	}
	else
	{
		// All this stuff below is to tell you exactly how you messed up above. 
		// Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
		switch (CommDlgExtendedError())
		{
		case CDERR_DIALOGFAILURE: std::cout << "CDERR_DIALOGFAILURE\n";   break;
		case CDERR_FINDRESFAILURE: std::cout << "CDERR_FINDRESFAILURE\n";  break;
		case CDERR_INITIALIZATION: std::cout << "CDERR_INITIALIZATION\n";  break;
		case CDERR_LOADRESFAILURE: std::cout << "CDERR_LOADRESFAILURE\n";  break;
		case CDERR_LOADSTRFAILURE: std::cout << "CDERR_LOADSTRFAILURE\n";  break;
		case CDERR_LOCKRESFAILURE: std::cout << "CDERR_LOCKRESFAILURE\n";  break;
		case CDERR_MEMALLOCFAILURE: std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
		case CDERR_MEMLOCKFAILURE: std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
		case CDERR_NOHINSTANCE: std::cout << "CDERR_NOHINSTANCE\n";     break;
		case CDERR_NOHOOK: std::cout << "CDERR_NOHOOK\n";          break;
		case CDERR_NOTEMPLATE: std::cout << "CDERR_NOTEMPLATE\n";      break;
		case CDERR_STRUCTSIZE: std::cout << "CDERR_STRUCTSIZE\n";      break;
		case FNERR_BUFFERTOOSMALL: std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
		case FNERR_INVALIDFILENAME: std::cout << "FNERR_INVALIDFILENAME\n"; break;
		case FNERR_SUBCLASSFAILURE: std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
		default: std::cout << "You cancelled.\n";
		}
	}



	fname = GetFileName("Output file : \n\n>> ");
	fname = fname + ".arff";
	std::cout << "\nOutput file : " << fname << "\nPress anything to continue\n";


	std::cout << "Writing \n";
	std::ofstream outfile;
	outfile.open(fname, std::ios_base::app);

	// comments
	outfile << "% 1. Title : Numbers for MLP\n% 2. Publisher : Nikolaos Anastasopoulos\n%" << std::endl;
	outfile << "% 3. Source files : http://statweb.stanford.edu/~tibs/ElemStatLearn.1stEd/datasets/zip.digits/" <<
		std::endl;

	// set names
	outfile << "\n\n@RELATION numbers\n" << std::endl;
	for (counter = 0; counter < 256; counter++) {
		outfile << "@ATTRIBUTE r" << (counter / 16) / 10 << (counter / 16) % 10 << "c" << (counter % 16) / 10 <<
			(counter % 16) % 10 << "\tNUMERIC" << std::endl;
	}
	outfile << "@ATTRIBUTE class\t" << "{0,1,2,3,4,5,6,7,8,9}\n" << std::endl;
	outfile << "@DATA" << std::endl;
	ifstream ifs(filename);
	string line;
	float classOfnum;
	int lineno = 1;
	while (getline(ifs, line)) {
		replace(line.begin(), line.end(), ' ', ',');
		sscanf_s(line.c_str(), "%f", &classOfnum);
		std::size_t pos = line.find(",");
		line = line.substr(pos+1);
		replace(line.begin(), line.end(), ' ', ',');
		if (line[line.length()] != ',') {
			line = line + ',';
		}
		outfile << line << classOfnum << std::endl;
	}

	std::getchar();
	std::cout << "\nPress anything to exit\n" << std::endl;
	std::getchar();
}


