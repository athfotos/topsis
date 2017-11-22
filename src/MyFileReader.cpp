#include <iostream>
#include <fstream>
#include <sstream>

#include "MyFileReader.h"

using namespace std;

MyFileReader::MyFileReader(string _fileName, int _dumpedLines) :
        fileName(_fileName), dumpedLines(_dumpedLines), values(0), linesRead(0), columnsRead(0) {
    cout << "constructed - " << fileName << endl;
}

MyFileReader::~MyFileReader() {
}

double **MyFileReader::read() {

    double **values;
    double tempArray[128][128];

    string line;
    ifstream myfile(fileName.c_str());

    // bypass [dump_lines] lines
    for (int i = 0; i < dumpedLines; i++)
        getline(myfile, line);

    while (getline(myfile, line)) {
        columnsRead = -1;

        istringstream iss(line);
        while (iss >> tempArray[linesRead][++columnsRead]);

        linesRead++;
    }

    myfile.close();

    // initialise with the right sizes
    values = new double *[linesRead];
    for (int i = 0; i < linesRead; i++)
        values[i] = new double[columnsRead];

    // initialise with the right values
    for (int i = 0; i < linesRead; i++)
        for (int j = 0; j < columnsRead; j++)
            values[i][j] = tempArray[i][j];

    return values;
}
