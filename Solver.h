#ifndef SOLVER_H
#define SOLVER_H

#include "Parser.h"
#include<algorithm>
#include<vector>
#include<bits/stdc++.h>

class Solver {

    Parser *parser;

public:

    vector <tuple <double, int, int, int> > DATA; // v:w, v, w, index
    vector <tuple <double, int, int, int> > init_DATA;
    vector <int> INDEX;

    Solver(Parser *parser);
    ~Solver();

    void solve(Parser *parser, int N, int MAX_W);

};

Solver::Solver(Parser *parser) {

    vector<double> V = parser->get_X();
    vector<double> W = parser->get_Y();

    for (int i = 0; i < V.size(); i++)
    {
        DATA.push_back(make_tuple(V[i]/W[i],V[i],W[i],i));
        INDEX.push_back(0);
    }

    init_DATA = DATA;

}

Solver::~Solver() {

    DATA.clear();

}

void Solver::solve(Parser *parser, int N, int MAX_W) {

    int i, j, k, m;

    //greedy algorithm for initial solution

    sort(DATA.begin(),DATA.end(),
         [](auto&v1,auto&v2) {return v1 > v2;});

    /*for (i = 0; i < N; i++)
        cout << get<0>(DATA[i]) << ' ' << get<1>(DATA[i]) << ' ' << get<2>(DATA[i]) << ' ' << get<3>(DATA[i])<< endl;*/

    double current_weight = 0, current_sum = 0;
    i = 0;

    while (current_weight <= MAX_W - get<2>(DATA[i])) {

        INDEX[get<3>(DATA[i])] = 1;
        current_weight += get<2>(DATA[i]);
        current_sum += get<1>(DATA[i]);
        i++;

    }

    // initial solution

    /*for (i = 0; i < N; i++)
        cout << INDEX[i] << ' ';

    cout << "\n";

    cout << current_weight << ' ' << current_sum << endl;*/

    // local search

    vector<int> new_INDEX;
    double new_sum, new_weight;

    for (j = 0; j < N; j++)
    for (k = 0; k < N; k++)
    {
        new_INDEX.assign(INDEX.begin(),INDEX.end());
        new_INDEX[j] = 1-new_INDEX[j];
        new_INDEX[k] = 1-new_INDEX[k];

        new_weight = current_weight - get<2>(init_DATA[j])*INDEX[j]
            + get<2>(init_DATA[j])*new_INDEX[j];
        new_weight = new_weight - get<2>(init_DATA[k])*INDEX[k]
            + get<2>(init_DATA[k])*new_INDEX[k];

        new_sum = current_sum - get<1>(init_DATA[j])*INDEX[j]
            + get<1>(init_DATA[j])*new_INDEX[j];
        new_sum = new_sum - get<1>(init_DATA[k])*INDEX[k]
            + get<1>(init_DATA[k])*new_INDEX[k];

        if (new_weight <= MAX_W && new_sum >= current_sum) {

                current_sum = new_sum;
                current_weight = new_weight;
                INDEX = new_INDEX;

        }

    }

    cout << current_weight << ' ' << current_sum << endl;

    for (i = 0; i < INDEX.size(); i++)
        cout << INDEX[i] << " ";

    return;

}

#endif
