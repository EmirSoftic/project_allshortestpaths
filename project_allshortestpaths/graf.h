#ifndef GRAF_H
#define GRAF_H
#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <queue>
#include <algorithm>
using namespace std;

class graf{
    int broj_cvorova;
    vector<vector<double>> matricaSusjedstva;
    vector<vector<double>> najkraci_putevi_rekr(vector<vector<double>> &DP, vector<vector<double>> &G);
public:
    graf(int n);
    void dodajGranu(int i, int j, double w);
    double dajTezinu(int i, int v);
    void ispisiMatricu();
    int& operator[](int);
    vector<vector<double>> najkraci_put_mnozenje_matrica_sporo();
    vector<vector<double>> najkraci_put_mnozenje_matrica_brzo();
    vector<vector<double>> najkraci_put_floyd_warshall();
    vector<vector<double>> najkraci_put_johnson();
    vector<vector<bool>> zatvorenost();
};


#endif // GRAF_H
