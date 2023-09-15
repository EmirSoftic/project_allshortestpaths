#include<iostream>
#include "graf.h"
using namespace std;

int main(){
    graf g(7);
    g.dodajGranu(0,0,0);
    g.dodajGranu(0,1,3);
    g.dodajGranu(0,2,6);
    g.dodajGranu(1,0,3);
    g.dodajGranu(1,1,0);
    g.dodajGranu(1,2,2);
    g.dodajGranu(1,3,1);
    g.dodajGranu(2,0,6);
    g.dodajGranu(2,1,2);
    g.dodajGranu(2,2,0);
    g.dodajGranu(2,3,1);
    g.dodajGranu(2,4,4);
    g.dodajGranu(2,5,2);
    g.dodajGranu(3,1,1);
    g.dodajGranu(3,2,1);
    g.dodajGranu(3,3,0);
    g.dodajGranu(3,4,2);
    g.dodajGranu(3,6,4);
    g.dodajGranu(4,2,4);
    g.dodajGranu(4,3,2);
    g.dodajGranu(4,4,0);
    g.dodajGranu(4,5,2);
    g.dodajGranu(4,6,1);
    g.dodajGranu(5,2,2);
    g.dodajGranu(5,4,2);
    g.dodajGranu(5,5,0);
    g.dodajGranu(5,6,1);
    g.dodajGranu(6,3,4);
    g.dodajGranu(6,4,1);
    g.dodajGranu(6,5,1);
    g.dodajGranu(6,6,0);
    g.ispisiMatricu();
    cout << endl << endl << endl;
    vector<vector<double>> matr = g.najkraci_put_mnozenje_matrica_brzo();
    cout << "  OVO JE RJESENJE KOJE JE SIG TACNO;" << endl;
    for(int i = 0; i < matr.size(); i++){
        for(int j = 0; j < matr.size(); j++){
            if(matr[i][j] == numeric_limits<double>::max())
                cout << setw(5) << "/" << " ";
            else
                cout << setw(5) << matr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl <<" MOZDA TACNO:" << endl;
    vector<vector<double>> testna = g.najkraci_put_floyd_warshall();
    for(int i = 0; i < testna.size(); i++){
        for(int j = 0; j < testna.size(); j++){
            if(testna[i][j] == numeric_limits<double>::max())
                cout << setw(5) << "/" << " ";
            else
                cout << setw(5) << testna[i][j] << " ";
        }
        cout << endl;
    }

    cout << "OV JE TRANZITIVNA ZAVORENOST:" << endl;

    graf z(4);
    z.dodajGranu(1,2,1);
    z.dodajGranu(2,1,1);
    z.dodajGranu(1,3,1);
    z.dodajGranu(3,2,1);
    z.dodajGranu(3,0,1);

    vector<vector<bool>> zatvorenost = z.zatvorenost();
    for(int i = 0; i < zatvorenost.size(); i++){
        for(int j = 0; j < zatvorenost.size(); j++){
            cout << setw(5) << zatvorenost[i][j] << " ";
        }
        cout << endl;
    }
}
