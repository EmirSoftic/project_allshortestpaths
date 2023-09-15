#include "graf.h"
#include <unordered_set>

graf::graf(int n){
    broj_cvorova = n;
    matricaSusjedstva.resize(n, vector<double>(n,numeric_limits<double>::max()));
    //ovakvo definisanje beskonacnosti sam pronasao na sljedecem linku:
    //https:en.cppreference.com/w/cpp/types/numeric_limits/max
}
void graf::dodajGranu(int i, int j, double w){
    matricaSusjedstva[i][j] = w;
}
double graf::dajTezinu(int i, int j){
    return matricaSusjedstva[i][j];
}
void graf::ispisiMatricu(){
    for(int i = 0; i < broj_cvorova; i++){
        for(int j = 0; j < broj_cvorova; j++){
            if(matricaSusjedstva[i][j] == numeric_limits<double>::max())
                cout << setw(5) << "/" << " ";
            else
                cout << setw(5) << matricaSusjedstva[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<double>> graf::najkraci_putevi_rekr(vector<vector<double>> &DP, vector<vector<double>> &G){
    int broj_redova_dinam = DP.size();
    vector<vector<double>> najkrace_trenutni(broj_redova_dinam, vector<double>(broj_redova_dinam,numeric_limits<double>::max()));
    for(int i = 0; i < broj_redova_dinam; i++){
        for(int j = 0; j < broj_redova_dinam; j++){
            for(int k = 0; k < broj_redova_dinam; k++){
                //3 for petlje podsjecaju na mnozenje matrica pa je ovo razlog sto se
                //alg tako zove
                //trazimo minimum izmedju trenutno najmanje(matrica postavljena sva na
                // plus beskonacno na pocetku i zbira svih puteva od
                //i do k plus put od k do j iz grafa.
                //vrijeme n^3.
                najkrace_trenutni[i][j] = min(najkrace_trenutni[i][j], DP[i][k] + this->matricaSusjedstva[k][j]);
            }
        }
    }
    return najkrace_trenutni;
}

vector<vector<double>> graf::najkraci_put_mnozenje_matrica_sporo(){
    int broj_redova = this->broj_cvorova;
    vector<vector<double>> DP = this->matricaSusjedstva;
    for(int i = 2; i < broj_redova; i++){
        //prolazak kroz ovu for petlju je vremena n, a poziva rekurzivno
        //funkciju koja traje n^3 vremena sto je ukupno n^4. Mozemo bolje.
        DP = najkraci_putevi_rekr(DP, this->matricaSusjedstva);
    }
    return DP;
}

vector<vector<double>> graf::najkraci_put_mnozenje_matrica_brzo(){
    int brojac = 1;
    vector<vector<double>> DP = this->matricaSusjedstva;
    while(brojac < this->broj_cvorova - 1){
        DP = najkraci_putevi_rekr(DP, DP);
        brojac *= 2;
    }
    return DP;
}

vector<vector<double>> graf::najkraci_put_floyd_warshall(){
    vector<vector<double>> DP = this->matricaSusjedstva;

    for(int k = 0; k < this->broj_cvorova; k++){
        /*
        Provjera da li se promjena desava korektno
        cout << "Matrica fw koja koristi preko cvora: " << k << endl;
        for(int u = 0; u < this->broj_cvorova; u++){
            for(int v = 0; v < this->broj_cvorova; v++){
                if(DP[u][v] == numeric_limits<double>::max()){
                    cout << "/ ";
                }
                else
                    cout << DP[u][v] << " ";
            }
            cout << endl;
        }
        */
        for(int i = 0; i < this->broj_cvorova; i++){
            for(int j = 0; j < this->broj_cvorova; j++){
                DP[i][j] = min(DP[i][j], DP[i][k] + DP[k][j]);
            }
        }
    }
    return DP;
}

vector<vector<double>> graf::najkraci_put_johnson(){
    int n = this->broj_cvorova;
    //Novi graf G', koji uz sve cvorove naseg grama i s cvor.
    graf NG(n+1);
    for(int u = 0; u < n; u++){
        for(int v = 0; v < n; v++){
            if(this->dajTezinu(u,v) != numeric_limits<double>::max()){
                NG.dodajGranu(u,v,this->dajTezinu(u,v));
            }
        }
    }
    //usmjereni, iz s u ostale s tezinom 0;
    for(int v = 0; v < n; v++){
        NG.dodajGranu(n,v,0);
    }
    //BellmanFord algoritam za novi graf G' koji racuna h(v) = delta(s,v)
    vector<double> udaljenosti(n+1, numeric_limits<double>::max());
    udaljenosti[n] = 0;
    for(int i = 0; i < n; i++){
        for(int u = 0; u < n + 1; u++){
                cout << "Udaljenosti: " << endl;
            for(int v = 0; v < n + 1; v++){
                if(udaljenosti[u] != numeric_limits<double>::max() && udaljenosti[u] + NG.dajTezinu(u,v) < udaljenosti[v]){
                    udaljenosti[v] = udaljenosti[u] + NG.dajTezinu(u,v);
                }
        cout << udaljenosti[v] << " ";
            }
            cout << endl;
        }
    }
    //Provjera negativnog ciklusa
    for(int u = 0; u < n + 1; u++){
        for(int v = 0; v < n + 1; v++){
            if(udaljenosti[u] != numeric_limits<double>::max() && udaljenosti[u] + NG.dajTezinu(u,v) < udaljenosti[v]){
                cout << "negativni ciklus imate u grafu i nije moguce naci najkrace puteve" << endl;
                return vector<vector<double>>();
            }
        }
    }
    //pravilo w'(u,v) = w(u,v) + h(u) - h(v) daje nenegativne ivice
    for(int u = 0; u < n + 1; u++){
        for(int v = 0; v <= n; v++){
            double w = NG.dajTezinu(u,v);
            NG.dodajGranu(u,v,w+udaljenosti[u]-udaljenosti[v]);
        }
    }
    vector<vector<double>> D(n,vector<double>(n));
    //Dijkstra algoritam na G' koji racuna delta(u,v)
    for(int u = 0; u < n; u++){
        vector<double> udaljenosti(n+1, numeric_limits<double>::max());
        udaljenosti[u] = 0;
        priority_queue<pair<double,int>> q;
        //prvi element je udaljenost od pocetnog do datog cvora, a drugi
        //element je taj drugi cvor
        //priority_queue sortia po prvom, tj udaljenosti
        q.push({0,u});
        while(!q.empty()){
            int v = q.top().second;
            q.pop();
            for(int i = 0; i < n + 1; i++){
                double w = NG.dajTezinu(v,i);
                if(udaljenosti[v] + w < udaljenosti[i]){
                    //gledamo da li do i-tog cvora ima brzi put, ako ima, stavljamo
                    //negativna vrijednost jer priority queue spasava od najmanjih ka vecem,
                    //te je tako najmanji uvijek na vrhu
                    udaljenosti[i] = udaljenosti[v] + w;
                    q.push({-udaljenosti[i],i});
                }
            }
        }
        for(int v = 0; v < n; v++){
            //udaljenost od u do v je kao udaljenost od u do s, pa od s do v, i od v do s plus od s do u
            //obzirom da do n idemo 2 puta vise nego treba, oduzimamo ga dva puta.
            D[u][v] = udaljenosti[v] + udaljenosti[u] - 2 * udaljenosti[n];
        }
    }
    return D;
}

vector<vector<bool>> graf::zatvorenost(){
    vector<vector<bool>> T(broj_cvorova,vector<bool>(broj_cvorova));
    for(int i = 0; i < broj_cvorova; i++){
        for(int j = 0; j < broj_cvorova; j++){
            T[i][j] = (matricaSusjedstva[i][j] != numeric_limits<double>::max());
        }
        //posto je u knjizi iz nekog razloga na diagonalama 1, i u knjizi tako opisan pseudokod, rijesio bih ovako
        //licno ne vidim razlog zasto bi svaki cvor morao biti povezan sa sobom.
        T[i][i] = true;
    }
    for(int k = 0; k < broj_cvorova; k++){
        for(int i = 0; i < broj_cvorova; i++){
            for(int j = 0; j < broj_cvorova; j++){
                T[i][j] = T[i][j] || (T[i][k]&&T[k][j]);
            }
        }
    }
    return T;
}





