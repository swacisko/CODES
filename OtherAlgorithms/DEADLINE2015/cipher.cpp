#include<stdio.h>
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
#include<conio.h>

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




// Implementacja struktury BigNum realizuj¹cej arytmetykê wielkich liczb
struct BigNum{
		//Makro s³u¿¹ce do eliminowania wiod¹cych zer
#define REDUCE() while( len>1 && !cyf[len-1] ) len--;
		// Podstawa, przy której wykonywane s¹ obliczenia oraz liczba zer w podstawie
	static const int BASE = 1000000000, BD = 9;
		// zmienna len reprezentuje aktualn¹ dlugosc liczby (liczbe cyfr), a al wielkosc
		// zaalokowanej pamieci do przechowywania cyfr liczby
	int len,al;
		// WskaŸnik do tablicy cyfr liczby
	LL *cyf;
		//Konstruktor liczby o wartoœci v i zaalokowanej pamiêci dla l cyfr
	BigNum( int v = 0, int l = 2 ) : len(1),al(l),cyf( new LL[l] ){
		REP(x,al) cyf[x] = 0;
		if( (cyf[0] = v) >= BASE ) przen(1);
	}
		// Konstruktor przypisuj¹c wartosc innej liczby typu BigNum
	BigNum( const BigNum &a ) : len(a.len), al(len), cyf( new LL[al] ){
		REP(x,al) cyf[x] = a.cyf[x];
	}
		// Destruktor
	~BigNum(){
		delete cyf;
	}
		// Funkcja przyjmuje jako parametr zapotrzebowanie na liczbe cyfr i jesli
		// zapotrzebowanie jest wieksze od aktualnego rozmiaru tablicy cyfr, to dokonuje realokacji
	void Res( int l ){
		if( l > al ){
			LL *n = new LL[ l = max(l,2*al) ];
			REP(x,l) n[x] = x >= al ? 0 : cyf[x];
			delete cyf;
			cyf = n;
			al = l;
		}
	}
		// Funkcja dokonuje przenoszenia do starszych cyfr nadmiaru powsta³ego na skutek wykonywania operacji.
		// Jest to jedyne miejsce w ca³ej strukturze, gdziue wykonuje siê t¹ operajê. Parametr okreœla liczbê cyfr,
		// do której nale¿y wykonaæ przenoszenie nadmiaru
	void przen(int p){
		int x = 0;
		for( ; x<p || cyf[x]<0 || cyf[x] >= BASE; x++ ){
			Res( x+2 );
				// W razoe [ptrzeby wykonaj zapozyczenie starszej cyfry
			if( cyf[x] < 0 ){
				LL i = ( -cyf[x] - 1 ) / BASE + 1;
				cyf[x] += i*BASE;
				cyf[x+1] -= i;
			}
			else if( cyf[x] >= BASE ) { // lub wykonaj przeniesienie powsta³ego nadmiaru
				LL i = cyf[x] / BASE;
				cyf[x] -= i*BASE;
				cyf[x+1] += i;
			}
		}
		len = max( len, x+1 );
		REDUCE();
	}
		// Od tego miejsca rozpoczyna siê implementacja operatorów. Przepisywanie tej czêsci kodu nie jest
		// wymagane, nale¿y przepisywaæ tylko te operatory, z których siê korzysta. Niektóre operatory korzystaj¹
		// z innych - w takich przypadkach, przy ka¿dym operatorze napisane jest, omplementacji jakich operatorow
		// on wymaga
		// Poni¿sze makro pozwala skrocic zapis
#define OPER1(op) bool operator op( const BigNum &a ) const
		// operatory porownawcze
	OPER1(==){
		if( a.len != len ) return 0;
		REP( x,len ) if( cyf[x] != a.cyf[x] ) return 0;
		return 1;
	}
	OPER1(<){
		if( len != a.len ) return len < a.len;
		int x = len-1;
		while( x && a.cyf[x] == cyf[x] ) x--;
		return cyf[x] < a.cyf[x];
	}
	OPER1(>){
		return a < *this;
	}
	OPER1(<=){
		return !( a < *this );
	}
	OPER1(>=){
		return !(*this < a);
	}
	OPER1(!=){
		return !(*this == a);
	}

	//operacje dla liczb typu int
	BigNum & operator=(int a){
		REP(x,len) cyf[x] = 0;
		len = 1;
		if( (cyf[0] = a) >= BASE ) przen(1);
		return *this;
	}
	void operator+=(int a){
		cyf[0] += a;
		przen(1);
	}
	void operator-=(int a){
		cyf[0] -= a;
		przen(1);
	}
	void operator*=(int a){
		REP(x,len) cyf[x] *= a;
		przen(len);
	}
		// Poni¿szy operator zwraca jako wynik reszte z dzielenia liczby typu BigNum przez liczbe typu int
	int operator/=( int a ){
		LL w = 0;
		FORD( p,len-1,0 ){
			w = w * BASE + cyf[p];
			cyf[p] = (w / a );
			w %= a;
		}
		REDUCE();
		return w;
	}
	int operator%(int a){
		LL w = 0;
		FORD( p,len-1,0 ) w = ( w * BASE + cyf[p] ) % a;
		return w;
	}
		// Operacje wy³acznie na liczbach typu BigNum
#define OPER2(op) BigNum& operator op( const BigNum &a )

	OPER2(+=){
		Res(a.len);
		REP(x,a.len) cyf[x] += a.cyf[x];
		przen(a.len);
		return *this;
	}
	OPER2(-=){
		REP(x,a.len) cyf[x] -= a.cyf[x];
		przen(a.len);
		return *this;
	}
	OPER2(*=){
		BigNum c( 0,len + a.len );
		REP(x,a.len){
			REP(y,len) c.cyf[ y+x ] += cyf[y] * a.cyf[x];
			c.przen( len+x );
		}
		*this = c;
		return *this;
	}

		// Operator ten wymaga implementacji nastepujacych operatorow: <(BigNum), +=(BigNum),
		// *=(BigNum), +(BigNum), *(BigNum), <<(int), <<=(int)
	OPER2(/=){
		int n = max(len-a.len+1,1);
		BigNum d(0,n), prod;
		FORD( i,n-1,0 ){
			int l = 0, r = BASE - 1;
			while( l < r ){
				int m = ( l+r+1 ) / 2;
				if( *this < prod + (a * m << i) ) r = m-1; // czy tutaj nie uzyjemy prod niezainicjalizowanego?
				else l = m;
			}
			prod += a * l << i;
			d.cyf[i] = l;
			if(l) d.len = max( d.len,i+1 );
		}
		*this = d;
		return *this;
	}
		// Operator ten wymaga implementacji operatorow: <(BigNum), +=(BigNum), *=(BigNum), +(BigNum),
		// *(BigNum), <<(BigNum), <<=(BigNum)
	OPER2(%=){
		BigNum v = *this;
		v /= a;
		v *= a;
		*this -= v;
		return *this;
	}
	OPER2(=){
		Res(a.len);
		FORD( x,len-1,a.len ) cyf[x] = 0;
		REP( x,a.len ) cyf[x] = a.cyf[x];
		len = a.len;
		return *this;
	}
		// Operatory s³u¿¹ce do wczytywania i wypisywanie liczb
		// Funkcja przpisuje liczbie BigNum wartoœæ liczby z przekazanego wektora, zapisanej przy podstawie p
		// Operator ten wymaga implementacji +=(int), *=(int)
	void read( const VI & v, int p ){
		*this = 0;
		FORD( x, SIZE(v) ,0 ){
			*this *= p;
			*this += v[x];
		}
	}
		// Funkcja przypisuje liczbie BigNum wartoœæ liczby z napisu zapisanego przy podstawie 10
		// Operator ten wymaga implementeacji =(int)
	BigNum & operator=( string a ){
		int s = a.length();
		*this = 0;
		Res( len = s/BD + 1 );
		REP(x,s) cyf[ (s-x-1) / BD ] = 10 * cyf[ (s-x-1) / BD ] + a[x] - '0';
		REDUCE();
		return *this;
	}
		// Funkcja wypisuje wartoœæliczby BigNum zapisanej przy podstawie 10
	void write() const{
		printf( "%d",int (cyf[len-1]) );
		FORD( x,len-2,0 ) printf( "%0*d",BD,int(cyf[x]) );
	}
		// Funkcja wypisuje do przekazanego bufora wartoœæ liczby zapisanej przy podstawie 10
	void write( char *buf ) const{
		int p = sprintf( buf,"%d",int(cyf[len-1]) );
		FORD(x,len-2,0) p += sprintf( buf+p, "%0*d",BD,int(cyf[x]) );
	}
		// Funkcja ta zwraca wektor cyfr liczby zapisanej przy podstaiwe pod. Funkcja ta wymaga implementacji
		// /=(int), =(BigNum)
	VI write( int pod ){
		VI w;
		BigNum v;
		v = *this;
		while( v.len > 1 || v.cyf[0] ) w.PB( v/=pod );
		return w;
	}
		// Operator przesuniêcia w prawo o n cyfr
	BigNum & operator>>=( int n ){
		if( n >= len ) n = len;
		REP( x,len-n ) cyf[x] = cyf[ x + n ];
		FOR( x,len-n,n ) cyf[x] = 0;
		len -= n;
		if( len == 0 ) len = 1;
		return *this;
	}
		// Operator przesuniêcia w lewo o n cyfr
	BigNum & operator<<=( int n ){
		if( cyf[0] == 0 && len==1 ) return *this;
		Res( len + n );
		FORD( x,len-1,0 ) cyf[x+n] = cyf[x];
		REP( x,n ) cyf[x] = 0;
		len += n;
		return *this;
	}
	 	// Funkcja wyznaczaj¹ca pierwiastek ca³kowity z liczby. Funkcja ta wymaga implementacju < (BigNum), +=(BigNum)
	 	// *=(BigNum), <<=(BigNum), +(BigNum), *(BigNum), <<(int)
	 BigNum sqrt(){
			int n = (len+1)/2;
			BigNum a(0,n),sq;
			FORD( i,n-1,0 ){
				int l =0, r = BASE - 1;
				 while(l<r){
						int m = (l+r+1)/2;
						if( *this < sq + ( a * 2 * m << i ) + ( BigNum(m) * m << 2 * i ) ) r = m - 1;
						else l = m;
				 }
				 sq += ( a * 2 * l << i ) + ( BigNum(l) * l << 2 << i );
				 a.cyf[i] = l;
				 a.len = n;
			}
			return a;
	 }
	 	// Makra pozwalaj¹ce na skrócenie zapisu nag³ówków poni¿szych operatorów
#define OPER3(op) BigNum operator op( const BigNum &a ) \
const { BigNum w=*this; w op ## = a; return w; }
#define OPER4(op) BigNum operator op( int a ) \
{ BigNum w = *this; w op ## = a; return w; }

		// Operator wymaga implementacji +=(BigNum)
	OPER3(+);
		// Operator wymaga implementacji -=(BigNum)
	OPER3(-);
		// Operator wymaga implementacji *=(BigNum)
	OPER3(*);
		// Operator wymaga implementacji <(bigNum), += (BigNum), *=(BigNum). /=(BigNum),
		// +(BigNum), *(BigNum), <<(int)
	OPER3(/);
		// Operator wymaga chyba wszystkiego :)
	OPER3(%);
		// Operator ymaga <<=(int)
	OPER4(<<);
		// Operator wymaga >>=(int)
	OPER4(>>);
};
// ***************************************   KONIEC BIG_NUMA



BigNum M,C;



namespace MATR{
	#define VT vector<_T>
	#define VVT vector<vector<_T> >

	// funkcja sluzaca do mnozenia dwoch macierzy   A  *  B
	// zwraca macierz A*B, lub VVT(0), jesli takie mnozenie nie jest mozliwe
	template<class _T>
	VVT multiply( VVT & A, VVT & B ){
		VVT ans = VVT( SIZE(A), VT( SIZE(B[0]) ) ); // lepiej odnosic sie do indeksu 0 danej tablicy - zawsze szybciej czasowo, a skoro rozmiary sa te same to nie ma to znaczenia
		REP( i,SIZE(A) ) REP( k,SIZE( A[0] ) ) REP( j,SIZE( B[0] ) ) ans[i][j] += A[i][k] * B[k][j];
		REP( i,SIZE(A) ) REP( j, SIZE(B[0]) ) ans[i][j] %= M;

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
	VVT power( VVT & A, _T n ){
		VVT C = A, ans( SIZE(A), VT( SIZE(A[0]),0 ) );
		REP(i,SIZE(A)) ans[i][i] = 1;
		while( n > 0 ){
			if( n%2 == 1 ) ans = multiply( ans,C );
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
	bool mult_by( VVT & A, int a, _T X, int line ){
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
	VT solve_eq( VT & X, VT & beg, _T n ){
		int K = SIZE(X)-1;
		VT y( K+2 ), x( K+2 );
		VVT A( K+2, VT( K+2,_T(0) ) );
		REP( i,K ) A[0][i] = X[i+1];
		A[0][K] = A[K][K] = A[K+1][K+1] = A[K+1][0] = 1;
		FOR( i,1,K-1 ) A[i][i-1] = 1; // po tej instrukcji jest juz calkowicie stworzona macierz A, ktora bedziemy potegowac

		REP( i,K ) x[i] = beg[ K-i-1 ];
		x[K] = X[0];
		_T suma = 0;
		REP(i,SIZE(beg)-1) suma += beg[i];
		x[K+1] = suma   ; // tutaj juz jest stworzona calkowicie macierz x, czyli wektor poczatkowy

        _T kk = K;
		A = power( A,n-kk );
		VVT mac( SIZE(x), VT(1) );
		REP( i,SIZE(x) )  mac[i][0] = x[i];

		mac = multiply( A,mac );
		REP( i,SIZE(x) ) x[i] = mac[i][0];
		return x;
	}



}






using namespace MATR;



BigNum solve( string x ){
    vector<BigNum> V,beg;
  //  beg.PB( BigNum(0) );
    beg.PB( BigNum(1) );
    beg.PB( BigNum(1) );
    V.PB( 0 );
    V.PB( C );
    V.PB( BigNum(1) );

    BigNum xx;
    xx = x;
    xx = xx+1;

    vector<BigNum> res;
    res = solve_eq( V,beg,xx );

    return res[ SIZE(res)-1 ] % M;
}


int main(){
//	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);

	string c,m;
	cin >> c >> m;

	LL T;
	cin >> T;

	C = c;
	M = m;

	C = C%M;


    string x;
	REP(i,T){
        cin >> x;

        BigNum b = solve( x );

        b.write();
        cout << endl;

	}







	return 0;
}












