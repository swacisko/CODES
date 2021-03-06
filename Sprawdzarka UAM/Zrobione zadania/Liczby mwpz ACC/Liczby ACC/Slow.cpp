//#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
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
typedef vector< VD > VVD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef long long LL;
typedef vector<LL> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;



// Implementacja struktury BigNum realizuj�cej arytmetyk� wielkich liczb
struct BigNum{
		//Makro s�u��ce do eliminowania wiod�cych zer
#define REDUCE() while( len>1 && !cyf[len-1] ) len--;
		// Podstawa, przy kt�rej wykonywane s� obliczenia oraz liczba zer w podstawie
	static const int BASE = 1000000000, BD = 9;
		// zmienna len reprezentuje aktualn� dlugosc liczby (liczbe cyfr), a al wielkosc
		// zaalokowanej pamieci do przechowywania cyfr liczby
	int len,al;
		// Wska�nik do tablicy cyfr liczby
	LL *cyf;
		//Konstruktor liczby o warto�ci v i zaalokowanej pami�ci dla l cyfr
	BigNum( int v = 0, int l = 2 ) : len(1),al(l),cyf( new LL[l] ){
		REP(x,al) cyf[x] = 0;
		if( (cyf[0] = v) >= BASE ) przen(1);
	}
		// Konstruktor przypisuj�c wartosc innej liczby typu BigNum
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
		// Funkcja dokonuje przenoszenia do starszych cyfr nadmiaru powsta�ego na skutek wykonywania operacji.
		// Jest to jedyne miejsce w ca�ej strukturze, gdziue wykonuje si� t� operaj�. Parametr okre�la liczb� cyfr,
		// do kt�rej nale�y wykona� przenoszenie nadmiaru
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
			else if( cyf[x] >= BASE ) { // lub wykonaj przeniesienie powsta�ego nadmiaru
				LL i = cyf[x] / BASE;
				cyf[x] -= i*BASE;
				cyf[x+1] += i;
			}
		}
		len = max( len, x+1 );
		REDUCE();
	}
		// Od tego miejsca rozpoczyna si� implementacja operator�w. Przepisywanie tej cz�sci kodu nie jest
		// wymagane, nale�y przepisywa� tylko te operatory, z kt�rych si� korzysta. Niekt�re operatory korzystaj�
		// z innych - w takich przypadkach, przy ka�dym operatorze napisane jest, omplementacji jakich operatorow
		// on wymaga
		// Poni�sze makro pozwala skrocic zapis
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
		// Poni�szy operator zwraca jako wynik reszte z dzielenia liczby typu BigNum przez liczbe typu int
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
		// Operacje wy�acznie na liczbach typu BigNum
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
		// Operatory s�u��ce do wczytywania i wypisywanie liczb
		// Funkcja przpisuje liczbie BigNum warto�� liczby z przekazanego wektora, zapisanej przy podstawie p
		// Operator ten wymaga implementacji +=(int), *=(int)
	void read( const VI & v, int p ){
		*this = 0;
		FORD( x, SIZE(v) ,0 ){
			*this *= p;
			*this += v[x];
		}
	}
		// Funkcja przypisuje liczbie BigNum warto�� liczby z napisu zapisanego przy podstawie 10
		// Operator ten wymaga implementeacji =(int)
	BigNum & operator=( string a ){
		int s = a.length();
		*this = 0;
		Res( len = s/BD + 1 );
		REP(x,s) cyf[ (s-x-1) / BD ] = 10 * cyf[ (s-x-1) / BD ] + a[x] - '0';
		REDUCE();
		return *this;
	}
		// Funkcja wypisuje warto��liczby BigNum zapisanej przy podstawie 10
	/*void write() const{
		printf( "%d",int (cyf[len-1]) );
		FORD( x,len-2,0 ) printf( "%0*d",BD,int(cyf[x]) );
	}*/
		// Funkcja wypisuje do przekazanego bufora warto�� liczby zapisanej przy podstawie 10
/*	void write( char *buf ) const{
		int p = sprintf( buf,"%d",int(cyf[len-1]) );
		FORD(x,len-2,0) p += sprintf( buf+p, "%0*d",BD,int(cyf[x]) );  
	}*/
		// Funkcja ta zwraca wektor cyfr liczby zapisanej przy podstaiwe pod. Funkcja ta wymaga implementacji
		// /=(int), =(BigNum)
	VI write( int pod ){
		VI w;
		BigNum v;
		v = *this;
		while( v.len > 1 || v.cyf[0] ) w.PB( v/=pod );
		return w;
	}
		// Operator przesuni�cia w prawo o n cyfr
	BigNum & operator>>=( int n ){
		if( n >= len ) n = len;
		REP( x,len-n ) cyf[x] = cyf[ x + n ];
		FOR( x,len-n,n ) cyf[x] = 0;
		len -= n;
		if( len == 0 ) len = 1;
		return *this;
	}
		// Operator przesuni�cia w lewo o n cyfr
	BigNum & operator<<=( int n ){
		if( cyf[0] == 0 && len==1 ) return *this;
		Res( len + n );
		FORD( x,len-1,0 ) cyf[x+n] = cyf[x];
		REP( x,n ) cyf[x] = 0;
		len += n;
		return *this;
	}
	 	// Funkcja wyznaczaj�ca pierwiastek ca�kowity z liczby. Funkcja ta wymaga implementacju < (BigNum), +=(BigNum)
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
	 	// Makra pozwalaj�ce na skr�cenie zapisu nag��wk�w poni�szych operator�w
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





namespace MATR{
	#define VT vector<_T>
	#define VVT vector<vector<_T> >
	
	const LL MODULO = 1000000;
	
	// funkcja sluzaca do mnozenia dwoch macierzy   A  *  B
	// zwraca macierz A*B, lub VVT(0), jesli takie mnozenie nie jest mozliwe
	template<class _T>
	void multiply( VVT &A, VVT &B ){		
		VVT ans = VVT( SIZE(A), VT( SIZE(B[0]) ) ); // lepiej odnosic sie do indeksu 0 danej tablicy - zawsze szybciej czasowo, a skoro rozmiary sa te same to nie ma to znaczenia
		REP( i,SIZE(A) ) REP( k,SIZE( A[0] ) ) REP( j,SIZE( B[0] ) ) ans[i][j] += A[i][k] * B[k][j];
		REP(i,SIZE(ans)) REP(k,SIZE(ans[0])) ans[i][k] %= MODULO;
	//	swap(ans,A);
		A = ans;
	//	return ans;
	}
	
	template<class _T>
	void multiply2( VVT &A, VVT &B ){		
		VVT ans = VVT( SIZE(A), VT( SIZE(B[0]) ) ); // lepiej odnosic sie do indeksu 0 danej tablicy - zawsze szybciej czasowo, a skoro rozmiary sa te same to nie ma to znaczenia
		REP( i,SIZE(A) ) REP( k,SIZE( A[0] ) ) REP( j,SIZE( B[0] ) ) ans[i][j] += A[i][k] * B[k][j];
		REP(i,SIZE(ans)) REP(k,SIZE(ans[0])) ans[i][k] %= MODULO;
	//	swap(ans,B);
		B = ans;
	//	return ans;
	}
	
	// funcka sluzaca do dodawania dwoch macierzy, zasada dzialania taka jak w multiply
/*	template<class _T>
	VVT add( VVT A, VVT B ){
		VVT ans = VVT( SIZE(A), VT( SIZE(A[0]) ) );
		REP( i,SIZE(A) ) REP( k,SIZE(A[0]) ) ans[i][k] = A[i][k] + B[i][k];
		REP( i,SIZE(A) ) REP( k,SIZE(A[0]) ) ans[i][k] %= MODULO;
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
	*/
	template<class _T>
	void write( VVT A ){
		REP( i,SIZE(A) ){
			WRITE(A[i]);
			ENDL(1);
		}
		ENDL(2);
	}
	
}


using namespace MATR;
/*
void write_full( int b, int K, VVI C, VVI D ){
	VVI res( b*(K-1), VI( b*(K-1) ) ); // to jest koncowa macierz, przez ktora bede mnozyl wektor beg;	
	
	REP( i,SIZE(res) ) REP(k,SIZE(res[i])) res[i][k] = D[ i%(K-1) ][ k%(K-1) ];
		
	
	REP(i,SIZE(C)) REP(k,SIZE(D)){ // teraz wypelniam pzekatna zgodnie ze wzorem
		for( int t = 0; t < SIZE(res); t+=K-1 ) res[ t+i ][ t+k ] = C[i][k];
	}
	
	write(res);
}

*/
VVI power( VVI A, BigNum n ){
	VVI jeden( SIZE(A), VI( SIZE(A),0 ) );
	REP(i,SIZE(A)) jeden[i][i] = 1;
	
	VVI C = A;
	while( n >= 1 ){
		
		if( n % 2 == 1 ){
		//	jeden = 
			multiply( jeden, C );
		}
		
		//C = 
		multiply( C,C );
		
		n /= 2;
	}
	
	return jeden;
}




LL solve( string N, int b, int K ){
	
	VVI beg( b*(K-1)+1,VI(1,0) );
	for( int i=K-1; i<SIZE(beg); i+=K-1 ) beg[i][0] = 1;
	beg[ SIZE(beg)-1 ][0] = 0;

	VVI X( K-1, VI(K-1) );
	VVI Y = X;
	
	REP( i, SIZE(Y[0]) ) Y[0][i] = 1;
	FOR( i,1, SIZE(X)-1 ) X[i][i-1] = 1;
	
//	cout << "Jestem przed res" << endl;
	
	VVI res( b*(K-1)+1, VI( b*(K-1)+1 ) ); // to jest koncowa macierz, przez ktora bede mnozyl wektor beg;	
	
	REP( i,SIZE(res)-1 ) REP(k,SIZE(res[i])-1) res[i][k] = Y[ i%(K-1) ][ k%(K-1) ];
	
//	cout << "chyba tutaj jest blad" << endl;
	REP(i,SIZE(X)) REP(k,SIZE(Y)){ // teraz wypelniam pzekatna zgodnie ze wzorem
		for( int t = 0; t < SIZE(res)-1; t+=K-1 ) res[ t+i ][ t+k ] = X[i][k];
	}
//	cout << "...albo nie" << endl;
	
	REP( i,SIZE(res) ) res[ SIZE(res)-1 ][i] = 1;
	
//	cout << "JEstem prezd power" << endl;
	BigNum big;
	big = N;
//	big += 1;
	res = power( res,big );
//	cout << "JEstem po power" << endl;
	
	//beg = 
	multiply2( res,beg );
	
//	cout << "Ostatnie wartosci to:" << endl;
//	REP(i,SIZE(res)) WRITE(beg[i]);
	
	int val = beg[ SIZE(beg)-1 ][0];
	//REP(i,SIZE(beg)) val += beg[i][0];
	
	return val % MODULO;	
}







int main(){
	ios_base::sync_with_stdio(0);
	
	int l_zest;
	cin >> l_zest;
	while( l_zest-- ){
		string N;
		cin >> N;
		int B,K;
		cin >> B >> K;
		
		int val = 0;
		BigNum big;
		big = N;
		big-=1;
		
		//for( int c = 0; big >= c; c+=1 ) val += solve( c,B,K );
		val = solve( N,B,K );
		
		cout << (val+1)%MODULO << endl;
		
	}
	
	
	
	return 0;
}












