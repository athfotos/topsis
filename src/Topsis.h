/*
 * MyCalculator.h
 *
 *  Created on: Nov 14, 2017
 *      Author: user
 */

#ifndef TOPSIS_H_
#define TOPSIS_H_

class Topsis {
    static const std::string input_fileName;
    static const std::string weights_fileName;
    static const std::string evaluation_fileName;
public:
    std::string fileName;

    double **x;
    int x_lines;
    int x_columns;

    double *W;
    int W_lines;

    double Wsum;
    double *t_best;
    double *t_worst;
    double *w;
    double **r;
    double **t;
    double *sq_sum;
    double *tb_sum;
    double *tw_sum;
    double *d_best;
    double *d_worst;
    double *s_w;

    Topsis();

    virtual ~Topsis();

    void doCrazyMath();
};

#endif /* TOPSIS_H_ */
