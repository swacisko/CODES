//#include<stdio.h>
#include<iostream>
#include<vector>
//#include<string>
//#include<map>
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
typedef vector<VD> VVD;
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




namespace MATR{
	#define VT vector<_T>
	#define VVT vector<vector<_T> >
	
	// funkcja sluzaca do mnozenia dwoch macierzy   A  *  B
	// zwraca macierz A*B, lub VVT(0), jesli takie mnozenie nie jest mozliwe
	template<class _T>
	VVT multiply( VVT & A, VVT & B ){		
		VVT ans = VVT( SIZE(A), VT( SIZE(B[0]) ) ); // lepiej odnosic sie do indeksu 0 danej tablicy - zawsze szybciej czasowo, a skoro rozmiary sa te same to nie ma to znaczenia
		REP( i,SIZE(A) ) REP( k,SIZE( A[0] ) ) REP( j,SIZE( B[0] ) ) ans[i][j] += A[i][k] * B[k][j];
		return ans;
	}
	
	// funcka sluzaca do dodawania dwoch macierzy, zasada dzialania taka jak w multiply
	template<class _T>
	VVT add( VVT & A, VVT & B ){
		VVT ans = VVT( SIZE(A), VT( SIZE(A[0]) ) );
		REP( i,SIZE(A) ) REP( k,SIZE(A[0]) ) ans[i][k] = A[i][k] + B[i][k];
		return ans;
	}
	
	// funkcja podnoszaca macierz A do n-tej potegi, zasada jak w multiply
	// dziala w czasie O( k^3 * logn ), gdzie k to rozmiar macierzy A
	template<class _T>
	VVT power( VVT & A, int n ){
		VVT C = A, ans( SIZE(A), VT( SIZE(A[0]),0 ) );
		REP(i,SIZE(A)) ans[i][i] = 1;
		while( n > 0 ){			
			if( n&1 ) ans = multiply( ans,C );			
			C = multiply( C,C );
			n /= 2;			
		}
	//	ENDL(5);
		return ans;
	}
	
	// funkcja dodaje wiersz/kolumne nr a do wiersza/kolumny nr b
	// jesli parametr line == 0 to dodaje wiersz a do wiersza b
	//w przeciwnym razie dodaje kolumne a do kolumny b
	template<class _T>
	void add_to( VVT & A, int a, int b, int line  ){
		if( line == 0 ) REP( i, SIZE(A[0]) ) A[b][i] += A[a][i];
		else REP( i,SIZE(A) ) A[i][b] += A[i][a];
	}
	
	// funkcja mnozy dany wiersz lub dana kolumne przez parametr(liczbe?) X
	// jesli line == 0 to mnoze wiersz a, w przeciwnym razie mnoze kolumne
	template<class _T>
	void mult_by( VVT & A, int a, _T X, int line ){
		if( line == 0 ) REP( i,SIZE(A[0]) ) A[a][i] *= X;
		else REP( i,SIZE(A) ) A[i][a] *= X;
	}
	
	
	// funkcja zwraca wyznacznik macierzy, ktorej lewy gorny rog znajduje sie w p-tym wierzsu i p-tej kolumnie macierzy
	// UWAGA, funkcja modyfikuje macierz A - jesli nie chcesz jej zmieniac, stworz przed wywolaniem kopie!
	// dziala w czasie O( n^3 ), gdzie n = SIZE(A)
	template<class _T>
	_T det( VVT & A ){
		_T val = 1;
		int size = min( SIZE(A), SIZE(A[0]) );
		REP( p,size ){			
			int t = p;
			while( t < SIZE(A) && A[t][p] == 0 ) t++;
			if( t == SIZE(A) ){
				val = 0; // nie zwracam od razu zera, po to, by ta funkcja mogla sluzyc do uzycia funkcji diagonalize - czyli do wyznaczania zmiennych
				continue;
			}; // jesli w pozostalej kolumnie sa wszystkie elementy rowne 0 to wyznacznik jest zerowy
			FOR( i,t+1,SIZE(A)-1 ){ // dla kazdego elementu ponizej, usuwam mnozaz i dodajac wiersze do danego wiersza
				if( A[i][p] != 0 ){
					_T value = A[i][p] / A[t][p];
					FOR( k,p,SIZE(A)-1 ) A[i][k] -= A[t][k]*value; // zeruje elementy, tak, aby pozniej moz wywolac rekurencyjnie obliczanie tylko dla jednego
				}
			}
			
			if( t != p ){ // jesli musze zmienic dwa wiersze, to 
				swap( A[t], A[p] );
				val = -val;
			}
			val *= A[p][p];
		}
		return val;
	}
	
	// funkcja zwraca jako wynik macierz transponowaca do macierzy A
	template<class _T>
	VVT transpose( VVT & A ){
		VVT B( SIZE(A[0]), VT( SIZE(A) ) );
		REP( i,SIZE(A) ) REP( k,SIZE(A[0]) ) B[k][i] = A[i][k];
		return B;
	}
	
	// funkcja wylicza zmienne xi - czyli tak mnozy wiersze i kolumny i dodaje je do siebie, aby wyrazy niezerowe byly tylko na przekatnej
	// funkcja zwraca wartosc false, jezeli rownanie nie ma jednoznacznego rozwiazania- tzn, gdy A jest kwadratowa oraz det(A) == 0
	// funkcja diagonalizuje przeslana macierz, tzn tworzy macierz 'dolnotrojkatna' i 'gornotrojkatna' ( wprzypadku niekwadratowych macierzy jest to troche 'dziwne' :)  )
	template<class _T>
	bool diagonalize( VVT & A ){
		if( det( A ) == 0 && SIZE(A) == SIZE(A[0]) ) return false; // tworze macierz gornotrojkatna
		REP( i,SIZE(A) ) reverse( ALL(A[i]) );
		reverse( ALL(A) );
		det( A );
		REP( i,SIZE(A) ) reverse( ALL(A[i]) );
		reverse( ALL(A) );		
	}
	
	
	//***************************************** znajdowanie macierzy odwrotnej
	
	// funkcja pomocnicza do tworzenia macierzy odwrotnej
	// dziala w czasie O( n^3 )
	template<class _T>
	bool help_rev( VVT & A, VVT & rev ){
		if( SIZE(A)==0 || SIZE(A) != SIZE(A[0]) ) return 0;
		_T val = 1;		
		
		int size = min( SIZE(A), SIZE(A[0]) );
		REP( p,size ){			
			int t = p;
			while( t < SIZE(A) && A[t][p] == 0 ) t++;
			if( t == SIZE(A) ){
				val = 0; // nie zwracam od razu zera, po to, by ta funkcja mogla sluzyc do uzycia funkcji diagonalize - czyli do wyznaczania zmiennych
				continue;
			}; // jesli w pozostalej kolumnie sa wszystkie elementy rowne 0 to wyznacznik jest zerowy
			FOR( i,t+1,SIZE(A)-1 ){ // dla kazdego elementu ponizej, usuwam mnozaz i dodajac wiersze do danego wiersza
				if( A[i][p] != 0 ){
					_T value = A[i][p] / A[t][p];
					FOR( k,p,SIZE(A)-1 ) A[i][k] -= A[t][k]*value; // zeruje elementy, tak, aby pozniej moz wywolac rekurencyjnie obliczanie tylko dla jednego
					FOR( k,p,SIZE(A)-1 ) rev[i][k] -= rev[t][k]*value;
				}
			}
			
			if( t != p ){ // jesli musze zmienic dwa wiersze, to 
				swap( A[t], A[p] );
				swap( rev[t], rev[p] );
				val = -val;
			}
			val *= A[p][p];
		}
		REP( i,SIZE(A) ){
			reverse( ALL(A[i]) );
			reverse( ALL(rev[i]) );
		}
		reverse( ALL(A) );
		reverse( ALL(rev) );
		return val;
	}
	
	
	
	// funkcja tworzy i zwraca macierz odwrotna do macierzy A, lub macierz o wymiarach 0 x 0 jesli macierz A ni ejest odwracalna
	template<class _T>
	VVT rev_mat( VVT & A ){
		VVT cpy = A;
		VVT rev( SIZE(A), VT( SIZE(A),0 ) );
		REP( i,SIZE(A) ) rev[i][i] = 1; // tutaj jest stworzona macierz jednostkowa
		
		if( help_rev(cpy,rev) == 0 ) return VVT(0); // jesli wyznacznik naszej macierzy A jest rowny 00 to nie istnieje macierz odwrotna		
		help_rev(cpy,rev); // teraz obie macierze cpy i rev sa zdiagonalizowane
		
		REP( i,SIZE(cpy) ){
			mult_by( rev, i, 1 / cpy[i][i],0 );
			cpy[i][i] = 1;
		}		
		
		return rev;		
	}
	
	//*************************************
	
	template<class _T>
	void write( VVT A ){
		REP( i,SIZE(A) ){
			WRITE(A[i]);
			ENDL(1);
		}
		ENDL(2);
	}
	
	
	
	//************************************************
	// funkcja sluzy do wyznacznia wartosci a(n) w ciagu zadanym rekurencja   an(x) = a1(n-1) + a2(n-2) + ... + ak(n-k) + d
	// dziala w czasie O( (k^3) * logn ) )
	// funkcja tez wyznacza sume wartosci a1 + a2 + ... + an
	// jako parametr przyjmuje wektor X = ( d, a1, a2, ..., ak )  - nie wiem czemu zrobilem w takiej kolejnosci, bo to nie ma sensu, ale dziala :)
	// jako wynik zwraca wektor V, w ktorym V[0] = a(n), V[1] = a(n-1), .... ( chyba ze n < SIZE(X), to zwraca tylko wektor, w ktorym V[0] = a(n) ), oraz V[ V.size()-1] = a(1)+a(2)+...+a(n-1)
	// w wektorze beg musza zostac przeslane warunki poczatkowe na a1,a2,...,ak	 w postaci takiej:   beg[i] to wartosc poczatkowa wspolczynnika a(i+1), czyli 'od dolu'
	// jest to innymi slowy mnozenie wektora x przez macierz A, czyli Ax = y
	template<class _T>
	VT solve_eq( VT & X, VT & beg, int n ){
		int K = SIZE(X)-1;
		VT y( K+2 ), x( K+2 );
		VVT A( K+2, VT( K+2,0 ) );
		REP( i,K ) A[0][i] = X[i+1];
		A[0][K] = A[K][K] = A[K+1][K+1] = A[K+1][0] = 1;
		FOR( i,1,K-1 ) A[i][i-1] = 1; // po tej instrukcji jest juz calkowicie stworzona macierz A, ktora bedziemy potegowac
				
		REP( i,K ) x[i] = beg[ K-i-1 ];
		x[K] = X[0];
		_T suma = 0;
		REP(i,SIZE(beg)-1) suma += beg[i];
		x[K+1] = suma; // tutaj juz jest stworzona calkowicie macierz x, czyli wektor poczatkowy
		
		A = power( A,n-K );
		VVT mac( SIZE(x), VT(1) );
		REP( i,SIZE(x) )  mac[i][0] = x[i];
				
		mac = multiply( A,mac );
		REP( i,SIZE(x) ) x[i] = mac[i][0];
		return x;		
	}
	
	
	
}



using namespace MATR;


int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(7);
	
	double tab[] = {
		0, 0.75f, 0, 0.25f, 0, 0, 0, 0, 0, 0,		
		1,0,0,0,0,0,0,0,0,0,
		0,0,0,0.75f,0,0.25f,0,0,0,0,
		0.25f,0,0.75f,0,0,0,0,0,0,0,
		0,0,0,0,0,0.75f,0,0.25f,0,0		
	};
	
	
	
	VVD transition( 10, VD(10) );
	
	REP( w, 10 ){
		REP(h,5){
			transition[h][w] = transition[ 9-h ][9-w] = tab[10*h + w];			
		}
	}
	
	//cout << "Transition" << endl;
	//write(transition);
	
	VVD rozklad(1,VD(10));
	REP( i,5){
		
		fill( ALL(rozklad[0]),0 );
		rozklad[0][2*i] = 1;
		
		
		cout << "Stan poczatkowy:\t";
		write(rozklad);
		
		VVD T = power( transition,730 );
		VVD roz = multiply( rozklad,T );
		
		//cout << "MAcierz T:\t";
		//write(T);
		
		T = power( transition,731 );
		VVD roz2 = multiply( rozklad,T );
		
		cout << "Rozklad po 730 krokach:\t";
		write(roz);
		
		cout << "Rozklad po 731 krokach:\t";
		write(roz2);		
		
		
		
	}
	
	
	return 0;
}












