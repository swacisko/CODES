//#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
//#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
//#include<time.h>
//#include<string.h>
//#include<fstream>
//#include<sstream>
#include<algorithm>

using namespace std;

#define REP( x,y ) for( int x=0; x<(y); x++ )
#define FORD( x,y,z ) for( int x=y; x>=(z); x-- )
#define FOR(x,b,e) for( int x = b; x <= (e); ++x )
#define SIZE(v) (int)v.size()
#define ALL(c) c.begin(),c.end()
#define VAR(v,n) __typeof(n) v=(n)
#define FOREACH(i,c) for( VAR(i,c.begin());i!=c.end();++i )
#define PB push_back
#define MP make_pair
#define ST first
#define ND second
#define WRITE( V ){ FOREACH(it,V) cout << *it << ", "; cout << endl; }
#define WRITE_ALL(V,s,t) { cout << s << endl;  REP( i,SIZE(V) ){ cout  << i+1 << " ---- ";  FOREACH(it,V[i]) cout << *it+t << ", "; cout << endl;     } }
#define WRP(p) p.ST << " " << p.ND
#define CLEAR( dst,quant ) memset( dst,0, (quant)*sizeof( __typeof(*dst) ) );
#define WAR if( show_help )
#define ENDL(x) REP(crow,(x)) cout << endl;

const bool show_help = 1;
const int INF = 1000000001;
int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;


// nazwa przestrzeni bierze sie od nazwy funkcji low sluzacej do wyznacznia mostow i punktow artykulacji
namespace LOW{
	
	VVI V; // wektor reprezentujacy graf
	VPII bridges; // wektor przechowujacy mosty(pary wierzcholkow)
	VI arts; // wektor przechowujacy numery wierzcholkow ktore sa punktami artykulacji
	VI preOrder; // numery preOrder wierzcholkow
	VI dfsSons; // ilosc synow podczas przeszukiwania grafu dfsem
	VI low; // wektor wyznaczajacy funkcje low
	
	// funkcja zwraca wszystkie mosty i punkty artykulacji w grafie V
	void getAll( int & dfsn, int num, int par ){
		preOrder[ num ] = dfsn++;
		low[ num ] = preOrder[ num ];
		dfsSons[ num ] = 0;
		
		bool isArt = false;
		REP(i,SIZE(V[num])){
			if( preOrder[ V[num][i] ] == 0 ){
				getAll( dfsn, V[num][i], num );
				low[num] = min( low[num], low[ V[num][i] ] );
				if( low[ V[num][i] ] >= preOrder[num] && par != -1 ) isArt = true;
				if( low[ V[num][i] ] == preOrder[ V[num][i] ] ) bridges.PB( MP( min(num,V[num][i]), max(num,V[num][i]) ) );
				dfsSons[num]++;		
			}
			else if( V[num][i] != par ) low[ num ] = min( low[num], preOrder[ V[num][i] ] );
		}
		
		if( isArt ) arts.PB(num);
	}
	
	// funkcja w wektorze bridges zapamietuje pary wierzcholkow wyznaczajace krawedzie, ktore sa mostami
	// a w wektorze arts nry wierzcholkow ktore sa punktami artykulacji
	void getBrAndArts(){
		bridges.clear();
		arts.clear();
		preOrder = VI(SIZE(V),0);
		dfsSons = VI(SIZE(V),0);
		low = VI(SIZE(V),0);
		int dfsn = 1;
		REP( i,SIZE(V) ) if( !preOrder[i] ){
			dfsn = dfsn; // dfsn = 1;   // uwaga, tutaj nie ma znaczenia co wpisze, to i tak sluzy tylko do powornywania kolejnosci wejsc do wierzcholkow
			getAll( dfsn,i,-1 ); // dla kazdej skladowej spojnosci wywoluje ta funkcje
			if( dfsSons[i] >= 2 ) arts.PB(i); // jesli korzen w drzewie przeszukiwania dfs ma conajmniej 2 synow, to jest artem
		}	
		sort( ALL(arts) ); // sortuje wszystkie punkty artykulacji
		sort( ALL(bridges) ); // sortuje wszystkie mosty
	}

}

using namespace LOW;


bool solve(){
	V.clear();
	cin >> N;
	if( N == 0 ) return false;
	if( l_zest > 1 ) cout << endl;
	
	V = VVI(N);
	string s;
	map<string,int> mapka;
	mapka.clear();
	vector<string> city(N);
	REP(i,N){
		cin >> s;
		city[i] = s;
		mapka[s] = i;
	}
	
	int R;
	string s1,s2;
	cin >> R;
	REP(i,R){
		cin >> s1 >> s2;
		a = mapka[s1];
		b = mapka[s2];
		V[a].PB(b);
		V[b].PB(a);
	}
	
/*	REP(i,SIZE(V)){
		cout << i << " -> ";
		WRITE(V[i]);
	}*/
	
	getBrAndArts();
	cout << "City map #" << l_zest <<": " << SIZE(arts) << " camera(s) found" << endl;
	vector<string> cities;
	REP(i,SIZE(arts)) cities.PB( city[arts[i]] );
	sort( ALL(cities) );
	REP(i,SIZE(cities)) cout << cities[i] << endl;
	
	return true;
}





int main(){
	ios_base::sync_with_stdio(0);
	
	l_zest = 0;
	while( ++l_zest && solve() );
	
	
	return 0;
}












