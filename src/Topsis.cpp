/*
 * MyCalculator.cpp
 *
 *  Created on: Nov 14, 2017
 *      Author: user
 */

#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

#include "MyFileReader.h"
#include "Topsis.h"

#define _USE_MATH_DEFINES

using namespace std;

const string Topsis::input_fileName = "../resources/myfile.dat";
const string Topsis::weights_fileName = "../resources/weights.dat";
const string Topsis::evaluation_fileName = "../resources/evaluation.dat";

Topsis::Topsis() {

    ///////// file reading ///////////
    MyFileReader *fileReader;

    fileReader = new MyFileReader(input_fileName);
    x = fileReader->read();
    x_lines = fileReader->linesRead;
    x_columns = fileReader->columnsRead;
    delete fileReader;

    fileReader = new MyFileReader(weights_fileName);

    double **weightsFromDisk = fileReader->read();

    int wLinesRead = fileReader->linesRead;
    int wColumnsRead = fileReader->columnsRead;

    delete fileReader;

    W_lines = 0;
    if (wLinesRead > 1 && wColumnsRead == 1)
        W_lines = wLinesRead;
    else if (wLinesRead == 1 && wColumnsRead > 1)
        W_lines = wColumnsRead;
    else {
        cout << "Not expecting format for weights.txt>" << endl;
        return;
    }

    W = new double[W_lines];
    for (int i = 0; i < wLinesRead; i++)
        for (int j = 0; j < wColumnsRead; j++)
            W[i] = weightsFromDisk[i][j];

    for (int i = 0; i < wLinesRead; i++)
        delete[] weightsFromDisk[i];
    delete[] weightsFromDisk;

    ///////// file reading END ///////////

    ///////// rest initialization ///////////

    w = new double[W_lines];

    r = new double *[x_lines];
    t = new double *[x_lines];
    for (int i = 0; i < x_lines; i++) {
        r[i] = new double[x_columns];
        t[i] = new double[x_columns];
    }

    t_best = new double[x_columns];
    t_worst = new double[x_columns];
    sq_sum = new double[x_lines];
    tb_sum = new double[x_lines];
    tw_sum = new double[x_lines];
    d_best = new double[x_lines];
    d_worst = new double[x_lines];
    s_w = new double[x_lines];

    ///////// rest initialization end ///////////

}

Topsis::~Topsis() {
    delete[] w;
    delete[] W;

    for (int i = 0; i < x_lines; i++) {
        delete[] x[i];

        delete[] r[i];
        delete[] t[i];
    }
    delete[] x;

    delete[] r;
    delete[] t;

    delete[] t_best;
    delete[] t_worst;
    delete[] sq_sum;
    delete[] tb_sum;
    delete[] tw_sum;
    delete[] d_best;
    delete[] d_worst;
    delete[] s_w;
}

void Topsis::doCrazyMath() {

    int i, j;
    double temp1 = 0;
    double temp2 = 0;
    double temp3 = 0;
    double temp4 = 0;
    double temp5 = 0;
    double temp6 = 0;

    for (i = 0; i < x_lines; i++) {
        sq_sum[i] = 0;
    }

    Wsum = 0;
    for (i = 0; i < W_lines; i++) {
        Wsum = Wsum + W[i];
    }
    for (i = 0; i < W_lines; i++) {
        w[i] = W[i] / Wsum;
    }

    for (i = 0; i < x_lines; i++) {
        for (j = 0; j < x_columns; j++) {
            temp1 = x[i][j];
            sq_sum[i] = sq_sum[i] + pow(temp1, 2);
        }
    }

    for (i = 0; i < x_lines; i++) {
        for (j = 0; j < x_columns; j++) {
            r[i][j] = 0;
            t[i][j] = 0;
        }
    }

    for (i = 0; i < x_lines; i++) {
        for (j = 0; j < x_columns; j++) {
            temp4 = sq_sum[i];
            r[i][j] = x[i][j] / sqrt(temp4);
            t[i][j] = r[i][j] * w[j];
        }
    }

    for (j = 0; j < x_columns; j++) {
        t_best[j] = t[0][j];
        t_worst[j] = t[0][j];
        for (i = 0; i < x_lines; i++) {
            if (t[i][j] > t_best[j]) {
                t_best[j] = t[i][j];
            }
            if (t[i][j] < t_worst[j]) {
                t_worst[j] = t[i][j];
            }
        }
    }

    for (i = 0; i < x_lines; i++) {
        tb_sum[i] = 0;
        tw_sum[i] = 0;
    }

    for (i = 0; i < x_lines; i++) {
        for (j = 0; j < x_columns; j++) {
            temp2 = t[i][j] - t_best[j];
            temp3 = t[i][j] - t_worst[j];
            tb_sum[i] = tb_sum[i] + pow(temp2, 2);
            tw_sum[i] = tw_sum[i] + pow(temp3, 2);
        }
    }

    for (i = 0; i < x_lines; i++) {
        temp5 = tb_sum[i];
        temp6 = tw_sum[i];
        d_best[i] = sqrt(temp5);
        d_worst[i] = sqrt(temp6);
        s_w[i] = d_worst[i] / (d_worst[i] + d_best[i]);
    }

    for (i = 0; i < x_lines; i++) {
        cout << s_w[i] << endl;
    }

    ofstream evaluation(evaluation_fileName.c_str());
    for (i = 0; i < x_lines; i++) {
        evaluation << fixed << setprecision(5) << s_w[i] << endl;
    }
    evaluation.close();
    //sort(s_w, s_w + x_lines, greater<double>());

}
