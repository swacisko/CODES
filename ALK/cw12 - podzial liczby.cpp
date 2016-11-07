//#include<stdio.h>
#include<iostream>
#include<vector>
//#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
//#include<time.h>
//#include<string.h>
//#include<fstream>
//#include<sstream>
#include<algorithm>
//#include<conio.h>

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
//int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef vector< VD > VVD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

LL part( int N, int K ){
	VVLL P(N+1, VLL(K+1,0) );
	P[0][0] = 1;
	FOR( n,1,N ) for( int k=1; k<=K && n-k >= 0;  k++ ) P[n][k] = P[n-1][k-1] + P[n-k][k];
	return P[N][K];	
}


// funkcja zwraca podzial sprzezony dla zadanego podzialu w postaci wektora liczb nierosnacych
VI conjugate( VI V ){
	VI G( V[0] );
	REP(i,SIZE(V)) REP( k,V[i] ) G[k]++;
	return G;	
}

int ILE;
void wypisz(VI & V){
	ILE++;
	REP( i,SIZE(V) ) cout << V[i] << " ";
	cout << endl;
}

void Partition( int n, int b, VI & V, int zad ){
	if( n == 0 ){
		if( zad == 4 ){
			VI G = conjugate(V);
			wypisz(G);
		}
		else if( zad == 3 ) wypisz(V);
		return;
	}
	
	FOR(i,1,min(b,n)){
		V.PB(i);
		Partition( n-i,i,V,zad );
		V.pop_back();
	}
}


int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);
	
	
	int N,K;
	
	while( true ){
		cout << "Podaj nr zadania:\t";
		int nr;
		cin >> nr;
		switch(nr){

			case 1:{
				cout << "Podaj N oraz K\t";
				int N,K;
				cin >> N >> K;
				cout << "P("<<N<<","<<K<<") = " << part(N,K) << endl;
				ENDL(2);
				break;
			}
			
			case 2:{
				cout << "Podaj liczbe:\t";
				int N;
				cin >> N;
				cout << "Podaj jej podzial:\nile elementow?\t";
				int K;
				cin >> K;
				cout << "Podaj te elementy:\t";
				VI V(K);
				REP(i,K) cin >> V[i];
				
				ENDL(2);
				cout << "Oto Twoj podzial:" << endl;
				
				REP( i, SIZE(V) ){
					REP(k,V[i]) cout << "*";
					cout << " ("<<V[i]<<")" << endl;
				}
				ENDL(2);
				cout << "Oto podzial sprzezony:" << endl;
				VI G = conjugate(V);
				
				REP( i, SIZE(G) ){
					REP(k,G[i]) cout << "*";
					cout << " ("<<G[i]<<")" << endl;
				}
				
								
				break;
			}
			
			
			
			case 3:{
				
				cout << "Podaj N:\t";
				int N;
				cin >> N;
				
				VI V;
				ILE = 0;
				Partition( N,N,V,3 );
				cout << endl << "Lacznie " << ILE << " podzialow" << endl;
				ENDL(2);
			
				break;
			}
			
			case 4:{
				cout << "Podaj N oraz K:\t";
				int N,K;
				cin >> N >> K;
				
				ILE = 0;
				VI V(1,K);
				Partition( N-K,K,V,4 );
				cout << endl << "Lacznie " << ILE << " podzialow" << endl;
				 
				ENDL(2);				
				
				break;
			}
			
			default:{
				system("cls");
			}
			
		}
	}
	
	
	
	
	
	
	
	return 0;
}












