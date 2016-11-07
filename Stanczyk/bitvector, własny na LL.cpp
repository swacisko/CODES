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


// struktura wektora dzialajacego na bitach
struct bitv{
	typedef LL T;
	static const int s_of = sizeof(T)*8;
	int s; // zmienna reprezentujaca rozmiar - rowna zmiennej N z konstruktora
	static const T full = -1;// 0xFFFFFFFFFFFFFFFF; // wersja dla T = long long; // UWAGA, ta liczba wypisana w systemie dziesietnym jest ujemna!!!!
//	 static const int full = 0xFFFFFFFF; // wersja dla T = int;
	// konstruktor jako N przyjmuje ilosc bitow ktore chce posiadac
	bitv( int N = 0, bool val = false ) : s(N) {
		if( !(N%s_of) ) b = VLL( N / s_of, val?full:0 );
		else b = VLL( N / s_of + 1, val?full:0 );
	}	
	~bitv(){
		b.clear();
	}	
	bool set( int pos, bool val ){
		if( val ) b[ pos / s_of ] |= ( 1 << (pos%s_of) );
		else b[ pos / s_of ] ^= ( b[ pos / s_of ] & ( 1 << (pos%s_of) ) );
		return val;
	}	
	bool operator[]( int pos ){
		return b[ pos / s_of ] & ( 1 << (pos%s_of) );
	}	
	int size(){ return s;}
	int countOnes(){
		int r = 0;
		REP(i,SIZE(b)) r += __builtin_popcountl(b[i]);
		return r;
	}
	int countZeroes(){ return s - countOnes(); }
	VLL b;	
	
	#define OPER(op) bitv operator op( const bitv & a ) \
	{ bitv t = *this;\
	 REP(i,SIZE(b)) t.b[i]  = (*this).b[i] op a.b[i]; \
	 return t;\
	}
	
	OPER(|);
	OPER(^);
	OPER(&);	
	
	#define OPER3(op) bitv& operator op ## =( const bitv & a )\
	{ return (*this = ((*this) op a) );}
	OPER3(|);
	OPER3(^);
	OPER3(&);
	
/*	#define OPER2(op) bitv& operator op( const bitv & a )
	OPER2(^=){
		return (*this = *this ^ a);
	}
	OPER2(|=){
		return ( *this = *this | a );
	}
	OPER2(&=){
		return ( *this = *this & a );
	}*/
	
	bitv operator!(){
		bitv t = *this;
		REP(i,SIZE(b)) t.b[i] ^= full;
		return t;
	}	
};


int main(){
	srand( unsigned(time(0)) );
	int S = 67;
	bitv vec1( S,1 );
	bitv vec2(S,1);
//	REP(i,S) vec1.set( i, rand()&1 );
//	REP(i,S) vec2.set( i, rand()&1 );
	
	cout << "vec1:         ";
	REP(i,SIZE(vec1)) cout << vec1[i] << " ";
	cout << endl;
	cout << "vec2:         ";
	REP( i,SIZE(vec2) ) cout << vec2[i] << " ";
	cout << endl;
	cout << endl;
	
	bitv res;
	
	res = vec1 & vec2;
	cout << "vec1 & vec2:  ";
	REP(i,SIZE(res)) cout << res[i] << " ";
	cout << endl;
	
	res = vec1 | vec2;
	cout << "vec1 | vec2:  ";
	REP(i,SIZE(res)) cout << res[i] << " ";
	cout << endl;
	
	res = vec1 ^ vec2;
	cout << "vec1 ^ vec2:  ";
	REP(i,SIZE(res)) cout << res[i] << " ";
	cout << endl;
	
	res = !vec1;
	cout << "!vec1:        ";
	REP(i,SIZE(res)) cout << res[i] << " ";
	cout << endl;
	
	cout << "vec1 zawiera " << vec1.countOnes() << " jedynek oraz " << vec1.countZeroes() << " zer" << endl;
	cout << endl << "res zawiera " << res.countOnes() << " jedynek oraz " << res.countZeroes() << " zer" << endl;
	
	res = !res;
	cout << "Negacja res:  ";
	REP(i,SIZE(res)) cout << res[i] << " ";
	cout << endl;
	cout << "\tTeraz res zawiera " << res.countOnes() << " jedynek oraz " << res.countZeroes() << " zer" << endl;
	
	
//	cout << endl << endl << endl << "full = " << res.full << endl; for( LL i = res.full; i ; i /= 2 ) cout << (i&1)?1:0;
}










