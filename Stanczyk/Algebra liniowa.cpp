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
#define WRP(p) p.ST << " " << p.ND 

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
const int INF = 1000000001;


// funkcje potrzebne do Gauusa w Zp
int GCDW( int a, int b, LL & l, LL & k ){
	if(!a){
		l = 0;
		k = 1;
		return b;
	}
	int d = GCDW( b%a,a,k,l );
	l -= ( b/a )*k;
	return d;
}
int RevMod( int a, int m ){
	LL x,y;
	if( GCDW(a,m,x,y)!= 1 ) return -1;
	x %= m;
	if( x<0 ) x+=m;
	return x;
}
//********************************************************




// ****************************************************************************  ELIMINACJE GAUSSA W Z2
// Chcemy rozwiazac rownanie macierzowe   A * x = b, gdzie x to niewiadome
// funkcja rozwiazuje uklad rownan w ciele Z2
// jako macierz przesylamy wektor equ, gdzie wierszami sa bitsety, kazdy po s wartosci ( s oznacza ilosc niewiadomych )
// funkcja zwraca wartosc -1, gdy uklad nie ma rozwiazania lub wartosc > 0 gdy jest niejednoznaczny - wwartosc ta jest rowna wymiarowi przestrzeni
// w wektore res zostaje umieszczone przykladowe rozwiazanie
template<const int s> int GaussZ2( vector< bitset<s> >equ, VI vals, VI & res ){
	int n = SIZE(equ), a=0, b=0, c;
	// ustaw odpowiednia wielkosc wektora wynikowego
	res.resize(s,0);
	// dla kolejnej niewiadomej xb...
	for( ; a < n && b < s; b++ ){
		//wyznacz pierwsze rownanie sposrod rownan [a...n-1], w ktorym wspolczynnik przy zmiennej xb jest niezerowy
		for( c = a; c < n && !equ[c][b]; c++ );
		// jesli znaleziono takie rownanie
		if( c < n ){
			//jesli w rownaniu nr a wsp przy xb jest rowny 0, to dodaj(mod 2) rownanie c do a
			if( a != c ){
				equ[a] ^= equ[c];
				vals[a] ^= vals[c];
			}
			
			//dla wszystkich roznych rownac od a, wyeliminuj z nich wspolczynnik przy xb
			REP(y,n) if( a != y && equ[y][b] ){
				equ[y] ^= equ[a];
				vals[y] ^= vals[a];
			}
			// zapamietaj nr rownania, w ktorym wspolczynnik przy zmiennej xb jest rozny od 0
			res[b] = ++a;
		}
	}
	// dla kazdej niewiadomej, jesli istnieje dla niej rownania z niezerowym wspolczynnikiem, to wyznacz wartosc z tego rownania
	REP(x,b) if( res[x] ) res[x] = vals[res[x]-1];
	// sprawdz czy wyznaczone rozwiazanie spelnia uklad rownan
	REP(x,n){
		c = 0;
		REP(z,s) if( equ[x][z] ) c ^= res[z];
		if( c != vals[x] ) return -1;
	}
	// zwroc wymiar przestrzeni rozwiazan
	return s-a;
}

// ******************************************************************************** eliminacje gaussa w Zp

//funkcja przyjmuje jako parametry tablice reprezentujaca uklad rownan A, wektor wartosci b, wektor x(rozwiazanie) oraz liczbe PIERWSZA P
// funkcja zwraca -1 gdy podany uklad nie ma rozwiazan, w przeciwnym razie zwraca wymiar przestrzeni rozwiazan oraz przykladowy wynik umieszcza w wektorze x
int Gauss( VVI &a, VI & b, VI & x, int P ){
	int m = SIZE(a), n = SIZE(a[0]),k,r;
	VI q;
	for( k=0; k < min(m,n); k++ ){
		int i,j;
		for( j=k; j<n; j++ )
		for( i=k; i<m; i++ )
		if( a[i][j] != 0 ) goto found;
		break;
		found:
		if( j != k ) REP(t,m) swap( a[t][j], a[t][k] );
		q.PB(j);
		if( i != k ){
			swap( a[i], a[k] );
			swap( b[i], b[k] );
		}
		FOR( j,k+1, m-1 ) if( a[j][k] != 0 ){
			int l = ( a[j][k] * RevMod( a[k][k],P ) ) % P;
			FOR( i,k+1,n-1 ) a[j][i] = ( P + a[j][i] - ( l*a[k][i] )%P ) % P;
			b[j] = ( P + b[j] - ( l*b[k] )%P ) % P;
		}
	}
	r = k;
	x.clear();
	x.resize( n,0 );
	FOR( k,r,m-1 ) if( b[k] != 0 ) return -1;
	FORD( k,r-1,0 ){
		int s = b[k];
		FOR( j,k+1,r-1 ) s = ( P + s - ( a[k][j] * x[j] )%P ) % P;
		x[k] = ( s * RevMod( a[k][k],P ) ) % P;
	}
	FORD( k,r-1,0 ) swap( x[k], x[q[k]] );
	return n-r;
}


// *******************************************************************************  Programowanie liniowe, Simplex
// dana jest macierz liczb rzeczywistych A, wektor liczb b, wektor liczb c. Chcemy wyznaczyc talki wektor x, ktory maxymalizuje wartosc
//  b*x, spelniajacy nierownosc A*x <= c (tzn, kazdy wymnozony element i jest mniejszy od ci)
// problem maxymalizjac na minimalizacje mozna bardzo latwo zamienic poprzez zamiane znakow wspolczynnikow wektora b na prezciwne - wektor b zamieniamy na wetkor -b
// podobnie mozna zmienic warunki ograniczajace, tzn jesli chcemy aby bylo A*x >= c wystarczy zmienic macierz A na -A oraz wektor c na -c
// pesymistyczna zlozonosc - wykladnicza   - srednia zlozonosc - n^3 albo n^4
namespace Simplex{
	// typ wykorzystywany do wykonywania obliczen, domyslnie jest to long double - ale czesto na kompie LD nie dziala :(
	typedef double T; // musi byc double, bo LD nie dziala...
	typedef vector<T> VT;
	vector<VT> A;
	VT b,c,res;
	VI kt,N;
	int m;
	inline void pivot( int k, int l, int e ){
		int x = kt[l];
		T p = A[l][e];
		REP(i,k) A[l][i] /= p;
		b[l] /= p;
		N[e] = 0;
		REP(i,m) if( i != l )
			b[i] -= A[i][e] * b[l], A[i][x] = A[i][e] * -A[l][x];
		REP(j,k) if( N[j] ){
			c[j] -= c[e] * A[l][j];
			REP(i,m) if( i != l ) A[i][j] -= A[i][e] * A[l][j];
		}
		kt[l] = e;
		N[x] = 1;
		c[x] = c[e] * -A[l][x];		
	}
	VT doit( int k ){
		VT res;
		T best;
		while(1){
			int e = -1, l = -1;
			REP(i,k) if( N[i] && c[i] > EPS ){
				e = i;
				break;
			}
			if( e == -1 ) break;
			REP(i,m) if( A[i][e] > EPS && ( l == -1 || best > b[i] / A[i][e] ) )
				best = b[ l = i ] / A[i][e];
				if( l == -1 ) return VT();
				pivot( k,l,e );
		}
		res.resize(k,0);
		REP(i,m) res[kt[i]] = b[i];
		return res;
	}
	VT simplex( vector<VT> &AA, VT & bb, VT & cc ){
		int n = AA[0].size(),k;
		m = AA.size();
		k = n + m + 1;
		kt.resize(m);
		b = bb;
		c = cc;
		c.resize(n+m);
		A = AA;
		REP(i,m){
			A[i].resize(k);
			A[i][n+i] = 1;
			A[i][k-1] = -1;
			kt[i] = n+i;
		}
		N = VI(k,1);
		REP(i,m) N[kt[i]] = 0;
		int pos = min_element( ALL(b) ) - b.begin();
		if( b[pos] < -EPS ){
			c = VT(k,0);
			c[k-1] = -1;
			pivot( k,pos,k-1 );
			res = doit(k);
			if( res[k-1] > EPS ) return VT();
			REP(i,m) if( kt[i] == k-1 )
				REP( j,k-1 ) if( N[j] && ( A[i][j] < -EPS || EPS < A[i][j] ) ){
					pivot(k,i,j);
					break;
				}
			c = cc;
			c.resize(k,0);
			REP(i,m) REP(j,k) if( N[j] ) c[j] -= c[kt[i]] * A[i][j];
		}
		res = doit( k-1 );
		if( !res.empty() ) res.resize(n);
		return res;
	}	
};




typedef double LD;
int main(){
	
	// Gauss w Z2
/*	vector< bitset<5> > equ(5);
	VI vals(5),res;
	equ[0][1] = equ[0][2] = 1;
	vals[0] = 0;
	equ[1][1] = equ[1][3] = 1;
	vals[1] = 1;
	equ[2][1] = equ[2][3] = equ[2][4] = 1;
	vals[2] = 0;
	cout << "Wymiar przestrzeni rozwiazan: " << GaussZ2<5>( equ, vals, res ) << endl;
	REP(z,SIZE(res)) cout << "x" << z << " = " << res[z] << endl;
	return 0;*/
	
	
/*	// Gauss w Zp
	VVI a(3,VI(3));
	VI b(3),x;
	a[0][0] = 1, a[0][1] = 3, a[0][2] = 7;
	b[0] = 0;
	a[1][0] = 4, a[1][1] = 0, a[1][2] = 14;
	b[1] = 1;
	a[2][0] = 2, a[2][1] = 6, a[2][2] = 8;
	b[2] = 2;
	cout << "Wymiar przestrzeni rozwiazan: " << Gauss( a,b,x,19 ) << endl;
	REP(i,SIZE(x)) cout << "x" << i << " = " << x[i] << endl;
	return 0;*/
	
	
	vector< vector<LD> > A( 2, vector<LD>(3) );
	vector<LD> b(2), c(3), res;
	A[0][0] = -0.5, A[0][1] = -1, A[0][2] = 2, b[0] = -2;
	A[1][0] = 1, A[1][1] = 2, A[1][2] = 0, b[1] = 100;
	c[0] = 5, c[1] = -1.5, c[2] = 0.1;
	res = Simplex::simplex( A,b,c );
	cout << "Najlepsze rowziazanie: ";
	REP(i,SIZE(res)) cout << "x" << i << " = " << res[i] << "\t";
	cout << endl;
	LD acc = 0;
	REP(i,SIZE(res)) acc += res[i] * c[i];
	cout << "Wartosc funkcji = " << acc << endl;
	return 0;
	
	
	
}








