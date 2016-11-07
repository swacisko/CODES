#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<complex>
#include<stack>
#include<list>
#include<set>
#include<bitset>
#include<set>
#include<iterator>
#include<cmath>
#include<queue>
#include<time.h>
#include<string.h>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<iomanip>

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
#define WRITE( V ) FOREACH(it,V) cout << *it << ", "; cout << endl;
#define WRITE_ALL(V,s)  cout << s << endl;  REP( i,SIZE(V) ){ cout << "i = " << i << endl;  FOREACH(it,V[i]) cout << *it << ", "; cout << endl;     }
#define WRP(p) p.ST << " " << p.ND 
#define ENDL(x) REP(i,x) cout << endl;

const int INF = 1000000001;
int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<long double> VD;
typedef pair<long double,int> PDI;
typedef pair<long double, long double> PDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;


VLL V;

void wypisz( int n, int ind ){
		
//	cout << "n = " << n;
//	cout << "\tind("<<n<<") = " << ind << endl;
//	if( ind < SIZE(V) ) cout << "F(" << ind << ") = " << V[ind] << endl;
//	cout << "n^2 - 3n + 3 = " << n*n - 3*n + 3 << endl;
//	cout << "ind  <=  n^2 - 3n + 3 : " << boolalpha << ( ind <= n*n-3*n+3 ) << endl;
//	cout << "stosunek   n*n - 3n + 3 / ind = " << (double) ( n*n-3*n+3 ) / ind << endl;
	
//	ENDL(1);
	
}

// funkcja zwraca najmneijsze takie m, ze F(m) dzieli sie przez n
int getInd( int n ){
	if( n == 1 ) return 1;
	int a = 1, b = 1, c = 2, ind = 2;
	while( c%n ){
		a = b;
		b = c;
		c = (a+b)%n;
		ind++;
	}
	return ind;
	
}


int main(){
		
	
//	int N = 10;
//	cout << "Podaj N:\t";
//	cin >> N;
	
	
	N = 0;
	while( N < 100000 ){
		
		//if( N < 100 ) N += 10;
		//else if( N < 1000 ) N += 100;
		//else if( N < 10000 ) N += 1000;
				
	//	else if( N < 100000 )N += 10000;
	//	N += 100000;
		
		
	//	V.clear();
	//	V.PB(1); V.PB(1);
	//	LL restr = 1; REP(i,17) restr *= 10;
	//	while( V[ SIZE(V)-2 ] + V[ SIZE(V)-1 ] < restr    ) V.PB( V[ SIZE(V)-2 ] + V[ SIZE(V)-1 ] );
		
	//	cout << "Oto poczatkowe liczby fibonaciego:" << endl;
	//	REP(i,SIZE(V)) cout << left << setw(10) << i << flush << " --> " << setw(20) << right << V[i] << endl;
		
		
		
		int indmax = 0;
		int last_val;
		int t,ind;
		int ROZMIAR = 51;
		VI lasts( ROZMIAR,1 );
		
		int N2 = 0; //******
		N = 100000; //******
etykieta: // ********
	
	cout << "N = " << N << endl << endl;
	if( N > 500000 ) break;//**********
		FOR( n,N2+1,N ){
			wypisz( n, t = getInd(n) );	
			if( t > indmax ){
				indmax = t;
				ind = n;
			}
			
			FOR(i,0,SIZE(lasts)-1) if( (double)indmax >= (double)(1+ (double)i/(SIZE(lasts)-1) )*(double)n ) lasts[i] = n+1;
			
		}
		
		cout << "Dla poczatkowych " << N << " wartosci maximum( ind(n) ) zachodzi³o dla n = " << ind << "  a jego wartosc wynosila " << indmax << endl;
		
		FOR(i,1,SIZE(lasts)-1) cout << "Poczawszy od wartosci " << lasts[i] << " wszystkie wartosci ind(n) sa mniejsze niz " << 1+(double)i/(SIZE(lasts)-1) << " * n" << endl;
		
		N2 = N; //*****
		N += 100000; //****
		
		ENDL(3);
		goto etykieta;//******
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}













