#include<iostream>
#include "Parser.h"
#include "Solver.h"

int main() {


    Parser parser("ks_1000_0");
    parser.set_data();
    vector<double> new_vector_X, new_vector_Y;
    parser.Parse(new_vector_X,new_vector_Y);

    Solver solver(&parser);
    solver.solve(&parser,parser.get_N(),parser.get_max_weight());

    return 0;
}
