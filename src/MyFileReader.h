/*
 * MyFileReader.h
 *
 *  Created on: Nov 14, 2017
 *      Author: user
 */

#ifndef MYFILEREADER_H_
#define MYFILEREADER_H_

class MyFileReader {
public:
    std::string fileName;
    int dumpedLines;
    double **values;

    int linesRead;
    int columnsRead;

    MyFileReader(std::string filename, int = 0);

    ~MyFileReader();

    double **read();

};

#endif /* MYFILEREADER_H_ */
