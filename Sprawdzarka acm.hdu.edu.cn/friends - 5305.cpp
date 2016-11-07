#include<iostream>

using namespace std;

#define REP( x,y ) for( int x=0; x<(y); x++ )

int N,M,a,b;
typedef long long LL;

int V[8][8]; // to jest graf przyjacielstwa
int friends[8]; // friends[i] to liczba przyjacio³ osoby i-tej
int real[8]; // to jest liczba realnych przyjaciol danej osoby
int virt[8]; // liczba wirtualnych przyjaciol danej osoby

void clearAll(){
    REP(i,8) REP(k,8) V[i][k] = real[i] = friends[i] = virt[i] = 0;

}

void readData(){
    cin >> N >> M;
    REP(i,M){
        cin >>a >> b;
        V[a-1][b-1] = V[b-1][a-1] = 1;
        friends[a-1]++;
        friends[b-1]++;
    }
}

// sprawdzam czy graf jest grafem eulera
bool checkEuler(){
    int ile = 0;
    REP(i,N){
        ile = 0;
        REP(k,N) ile += V[i][k];
        if( ile % 2 == 1 ) return false;
    }
    return true;
}

// obliczam wartosc z zadania
LL calculate(){
    LL res = 0;
    bool found = false;
    REP(i,N){
        REP(k,N){
            if( V[i][k] == 1 ){ // szukam dowolnej krawedzi w grafie...
                if( 2*real[i] < friends[i] && 2*real[k] < friends[k] ){
                    real[i]++;
                    real[k]++;
                    V[i][k] = V[k][i] = 0;
                    res += calculate();
                    V[i][k] = V[k][i] = 1;
                    real[i]--;
                    real[k]--;
                }

                if( 2*virt[i] < friends[i] && 2*virt[k] < friends[k] ){
                    virt[i]++;
                    virt[k]++;
                    V[i][k] = V[k][i] = 0;
                    res += calculate();
                    V[i][k] = V[k][i] = 1;
                    virt[i]--;
                    virt[k]--;
                }

                found = true;
            }

            if( found ) break;
        }

        if( found ) break;
    }

    if( found == false ) return 1; // jesli ne ma zadnej krawedzi, to zwracam 1
    else return res;
}

void solve(){
    clearAll();
    readData();

    if( checkEuler() == false ){
        cout << 0 << endl;
    }
    else{
        LL t = calculate();
        cout << t << endl;
    }
}

int main(){
	ios_base::sync_with_stdio(0);

    int l_zest;
    cin >> l_zest;
	while( l_zest-- ){
        solve();
	}

	return 0;
}












