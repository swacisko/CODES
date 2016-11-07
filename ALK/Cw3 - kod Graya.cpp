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



void zad1( int N ){
	set<int> zbior;
	zbior.insert(N);
	bool waga = true;
	cout << "Zbior pusty" << endl;
	WRITE(zbior);
	
	int el_max = N-1;
	while( el_max > 0 ){	
		
		if( waga ){
			if( zbior.find( el_max ) != zbior.end() ) zbior.erase( el_max );
			else zbior.insert( el_max );
		}
		else{
			if( zbior.find( N ) != zbior.end() ) zbior.erase(N);
			else zbior.insert(N);
		}
		
		WRITE(zbior);
		
		waga = !waga;
		el_max = *max_element( ALL(zbior) )-1;
	}
	
	
}


//******************************************************************************


int zad2( int N, VI & V ){
	set<int> zbior( ALL(V) );
	int r = 0;
	bool b = 0;
	FORD(i,N-1,0){
		if( zbior.count( N-i ) > 0 ) b = !b;
		if( b ) r += (int) pow( 2,i );
	}
	
	return r;
	
}




//******************************************************************************


set<int> zad3( int N, int r ){
	
	VI b;
	int r2 = r;
	while( r2 > 0 ){
		if( r2 & 1 ) b.PB(1);
		else b.PB(0);
		r2 >>= 1;
	}
	while( SIZE(b) <= N ) b.PB(0);
	reverse( ALL(b) ); // teraz jest gotowy wektor bitow liczby r b
	
//	WRITE(b);
	
	set<int> zbior;
	FORD(i,N-1,0){
		if( (b[i+1] + b[i] ) & 1 ) zbior.insert( i+1 );
	}
	
	return zbior;	
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
				cout << "Podaj wartosc N dla zadania 1:\t";
				cin >> N;
				zad1(N);
				ENDL(3);
				break;
			}
			
			case 2:{
				cout << "Podaj wartosc N dla zadania 2:\t";
				cin >> N;
				cout << "Podaj ilosc elementow zbioru T:\t";
				int K;
				cin >> K;
				cout << "Podaj te elementy:\t";
				VI V(K);
				REP(i,K) cin >> V[i];
				int res;
				if( ( res = zad2(N,V) ) == 0 ) cout << "Zbior pusty" << endl;
				else cout << res << endl;
				ENDL(3);
				break;
			}
			
			
			
			case 3:{
				cout << "Podaj wartosci N oraz r dla zadania 3:\t";
				int r;
				cin >> N >> r;
				set<int> zbior = zad3( N,r );
				if( zbior.empty() ) cout << "Zbior pusty" << endl;
				else WRITE(zbior);
				ENDL(3);
				break;
			}
			
			default:{
				system("cls");
			}
			
		}
	}
	
	
	
	
	
	
	
	return 0;
}












