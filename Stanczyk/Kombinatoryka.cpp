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

//*******************************************************************************
// Generowanie wszystkich permutacji danego ciagu w kolejnosci antyleksykograficznej... wersja rekurencyjna
namespace PermAntyLex{
	// Wskaznik na wektor liczb reprezentujacych dana permutacje
	VI *V;
	//Wskaznik na funkcje ktora jest wywolywana dla kazdej wygenerowanej permutacji
	void (*fun)( VI & );
	// funkcja rekurencyjna wyznaczajaca wszystkie m-elementowe permutacje
	void Perm( int m ){
	//	cout << "Wchodze do perm, moj wektor to: "; REP(i,SIZE((*V))) cout << (*V)[i] << " ";
	//	cout << endl;
	
		if( !m ) fun( *V );
		else{
			FOR( i, 0, m ){
				Perm( m-1 );
				if( i < m ){
					// zamiana miejscami i-tego elementu oraz m-1 -szego
				//	REP(k,4-m) cout << "\t";
				//	cout << "m = " << m << "  Zamieniam miejscami element " << i << " oraz " << m << "   a takze odwracam kolejnosc elementow od 0 do " << m-1 << endl;
					swap( (*V)[i], (*V)[ m ] );
					// odwrocenie kolejnosci wszystkich elementow na przedziale [0...m-1]
					reverse( &(*V)[0], &(*V)[m] );
				//	REP(k,4-m+2) cout << "\t";
				//	cout << "Teraz to jest permutacja  "; fun(*V);
				//	cout << endl;
				}
			}
		}
	}
	
	// wlasciwa funkcja wywolywana z zewnatrz przestrzeni nazwa PermAntyLex
	void Gen( VI & v, void (*f)(VI &) ){
		V = &v;
		fun = f;
		Perm( SIZE(v)-1 );
	}
	

};

void Display( VI & v ){
	static int calc = 0;
	if( !( calc++ % 6 ) ) cout << endl;
	FOREACH( it, v ) cout << *it << " ";
	cout << "\t";
}

//*****************************************************************************
/* // TO PO PROSTU NIE DZIAL, musze ogarnac, jak to wogole ma dzialac i poprawic kod w jakims miejscu

namespace PermMinTr{
	// wskaznik na wektor liczb reprezentujacych wygenerowana permutacje
	VI *V;
	// wskaznik na funkcje, ktora jest wywolywana dla kazdej wygenerowanej permtacji
	void (*fun)(VI &);
	// funkcjarekurencyjna wyznaczajaca wszystkie m-elementowe permutacje
	void Perm( int m ){
		if(m==1) fun(*V);
		else{
			REP(i,m){
				Perm(m-1);
				if( i < m-1 ){
					swap(  (*V)[ ( (!( m & 1 )) && m > 2) ?  (i < m-1) ? i : m-3  : m-2 ], (*V)[ m-1 ] );
					cout << "m = " << m << "   i = " << i << "   Zamieniam miejscami elementy nr "
						<< ( (!( m & 1 ) && m > 2) ? ( ( i < m-1) ? i : m-3 ) : m-2 ) << "  oraz " << m-1 << endl;
						cout << "\t\t\t\tTeraz to jest permutajca: "; FOREACH(it,(*V)) cout << *it << " ";
						cout << endl;
				}
				
			}
		}
		
	}
	
	// wlasciwa funkcja wywolywana z zewnatrz przestrzeni nazw PermMinTr
	void Gen( VI & v, void (*f)(VI &) ){
		V = &v;
		fun = f;
		Perm( SIZE(v)-1 );
	}	
};

void Disp( VI & v ){
	static int calc = 0;
	if( !(calc++%6) ) cout << endl;
	FOREACH(it,v) cout << *it << " ";
	cout << "\t";
}*/

//********************************************************************************
// generowanie wszystkich permutacji wzgledem minimalnych transpozycji sasiednich - kazda nowa permutacja powstaje poprzez zamiane w starej dokladnie dwoch
// elementow
void PermMinTrAdj( VI & p, void (*fun)(VI &, int) ){
	int x,k,i = 0, s = p.size();
	VI c(s,1);
	VB pr(s,1);
	c[s-1] = 0;
	fun(p,-1);
	while( i < s-1 ){
		i = x = 0;
		while( c[i] == s-i ){
			if( pr[i] = !pr[i] ) x++;
			c[i++] = 1;
		}
		if( i < s-1 ){
			k = pr[i] ? c[i] + x : s - i - c[i] + x;
			// zamien miejscami k-ty i k-1-ty element w permutacji
			swap( p[k-1], p[k] );
			fun( p,k-1 );
			c[i]++;			
		}
	}
}
// funkcja ta przyjmuje dwa parametry - wektor reprezentujacy permutacje, drugi to liczba naturalna k wyznaczajaca pare elementow (k oraz k+1), ktore
// zostaly zamienione miejscami w celu uzyskania nowej permutacji (k = -1 w przypadku pierwszej permtacji)
void DisplayAdj( VI & v, int k ){
	if( k!= -1 ) cout << "Zamiana elementow " << k << " i " << k+1 << endl;
	cout << "Permutacja: ";
	FOREACH( it,v ) cout << *it << " ";
	cout << endl << endl;
}
//**********************************************************************************


/*  // TO TEZ NIE DZIALA :(  :(  :(
// funkcja wyznaczjaca wszystkie mozliwe podzbiory zbioru n-elementoweg, n - liczba elementow
// VB w wywolywanej funkcji fun to:  jesli V[k] == true to k-ty element nalezy do zbioru
// drugi parametr oznacza numer elementu, ktory zostal dodany lub usuniety w procesie generowania kolejnego podzbioru
void SubsetMin( int n, void (*fun)( VB &, int ) ){
	VB B(n,0);
	fun(B,-1);
	for( int i=0, p=0,j;  p < n; ){
		for( p = 0, j = ++i; j & 1; p++ ){
			j >>= 1;
			if( p < n ){
				// zmien przynaleznosc do podzbioru elementu p
				B[p] = !B[p];
				fun( B,p );
			}
		}
	}	
}

void DisplaySubset( VB & v, int k ){
	if( k != -1 ){
		if( v[k] ) cout << "Do zbioru zostal dodany element " << k << endl;
		else cout << "Ze zbioru zostal usuniety element " << k << endl;
	}
	cout << "Podzbior: ";
	FOREACH(it,v) cout << *it << " ";
	cout << endl;
}*/

// MOJA NIETANCZYKOWA przestrzen do generowania wszystkich mozliwych podzbiorow danego zbioru, po kolei sa generowane wszystkie mozliwe podzbiory mocy M dla M = 1,2,3...
namespace Subsets{
	VB B; // B[i] = true, gdy i-ty element nalezy do podzbioru, UWAGA, elementy liczone od 0 do n-1	
	void f(){
		REP( i, B.size() ) cout << B[i] << " ";
		cout << endl;
	}
	// i - ilosc elementow ile ma byc w danym podzbiorze, k - ilosc elementow ile jest aktualnie w danym podzbiorze, ind - nr elementu, ktory dodaje lub usuwam
	// funkcja generator jest wywolywana lacznie 2^(N+2) raza, czyli 4 * 2^N, zatem na szczescie wykladniczo
	void Generator( int i, int k, int ind ){
		if( ind + i - k > SIZE(B) ) return; // nie mamy juz szans na i elementow w podzbiorze
		if( k == i ){
			f();
			return;
		}		
		B[ind] = true;
		Generator( i,k+1,ind+1 );
		B[ind] = false;
		Generator( i, k, ind+1 );	
	}
	
	void Generate( int N ){
		B = VB(N,false);		
		REP(i,N+1) Generator( i,0,0 );
	}	
};

//*********************************************************************************
// Podzbiory k-elementowe w kolejnosci leksykograficznej
//funkcja wyznacza wszystkie k-elementowe podzbioty zbior n-elementowego
void SubsetKLex( int k, int n, void (*fun)(VI &) ){ // UWAGA UWAGA UWAGA,              NIE DZIALA DLA k == n
	int i, p=k;
	VI A(k);
	REP( x,k ) A[x] = x;
	while( p ){
		fun(A);
		( A[k-1] == n-1 ) ? p--: p = k;
		if( p ) FORD( i,k,p ) A[i-1] = A[p-1] + i - p + 1;
	}	
}

void DisplaySubsetKLex( VI & v ){
	static int calc = 0;
	if( !(calc++%6) ) cout << endl;
	FOREACH(it,v) cout << *it << " ";
	cout << "\t";
}
//**********************************************************************************

// PODZIALY zbioru minimalna liczba zmian
// kolejne dwa podzialy roznia sie przynaleznosci do roznych podzbiorow dokladnie jednego elementu, mozna latwo zupgradowac funkcje, tak, aby wyznaczyc ktory to element
// to jest podzial zbioru, czyli jezeli 1,2,3 naleza do zbioru nr 1, a 4,5 do zbioru nr 2 to to jest ten sam podzial co, gdyby 1,2,3 nalezaly do zbioru nr 17, 
// a 4,5 do zbioru 9891
// funkcja wyznacza wszystkie podzialy n-elementowego zbioru
void SetPartition( int n, void (*fun)(VI &) ){ // czas dzialania to okolo EN SILNIA ( N! ) :)
	VI B(n,1), N(n+1), P(n+1);
	VB Pr(n+1,1);
	N[1] = 0;
	fun(B);
	for( int i,k,j = n; j > 1; ){
		k = B[j-1];
		if( Pr[j] ){
			if( !N[k] ) P[ N[k] = j + ( N[j]=0 ) ] = k;
			if( N[k] > j ) N[ P[j] = k ] = P[ N[j] = N[k] ] = j;
			// w tym miejscu nastêpuje przydzielenie elementu j do zbioru o numerze N[k]
			B[j-1] = N[k];
		}
		else{
			// w tym miejscu nastepuje przydzielenie elementu j do zbioru o numerze P[k]
			B[j-1] = P[k];
			if( k == j ) N[k] ? P[ N[ P[k] ] = N[k] ] = P[k] : N[ P[k] ] = 0;
		}
		fun(B);
		j = n;
		while( j > 1 && (( Pr[j] && ( B[j-1] == j ))
			|| ( !Pr[j] && (B[j-1] == 1) ) ) ) Pr[j--] = !Pr[j];
	}
}

void DisplayPartition( VI & v ){
	static int calc = 0;
//	if( !(calc++%6) ) cout << endl;
//	FOREACH( it,v ) cout << *it << " ";
//	cout << "\t";
}

//***********************************************************************************

// PODZIALY liczby w kolejnosci antyleksykograficznej
// 10 = 5 + 5 = 5 + 3 + 2 = 4 + 3 + 3 = ...
// funkcja przesy³ana jakos wskaznik do funkcji enerujacej otrzymuje dwa rownoliczne wektory jako parametr - s oraz r;
// k-ta para tych wektorow (sk,rk) reprezentuje k-ty skladnik sumy - sk razy wystepuje liczba rk

// funkcja generuje wszystkie podzialy liczby n
void NumPart( int n, void(*fun)( VI &, VI &,int ) ){
	VI S(n+1), R(N+1);
	int d, sum, l;
	S[0] = n;
	R[0] = d = 1;
	while( true ){
		int summ = 0, x, s;
		fun( R,S,d );
		if( S[0] == 1 ) break;
		sum = 0;
		if( S[d-1] == 1 ) sum += R[--d];
		sum += S[d-1];
		R[d-1]--;
		l = S[d-1] - 1;
		if( R[d-1] ) d++;
		S[d-1] = l;
		R[d-1] = sum / l;
		l = sum % l;
		if( l ){
			S[d] = l;
			R[d++] = 1;
		}
	}	
}

void DisplayNumPart( VI & s, VI & r, int n ){
	bool ch = 0;
	REP(x,n) REP(y,s[x]){
		if(ch) cout << " + ";
		cout << r[x];
		ch = 1;
	}
	cout << endl;	
}

int main(){
	
/*	// Permutacje w kolejnosci antyleksykograifcznej
	VI p;
	FOR(x,1,4) p.PB(5-x);
	PermAntyLex::Gen( p,&Display );
	return 0;*/
	
/*	// Permutacje wedlug minimalnych transpozycji   NIE DZIALA NIE DZIALA NIE DZIALA
	VI p;
	FOR(x,1,4) p.PB(x);
	PermMinTr::Gen( p,&Disp );*/
	
/*	// Minimalne permutacjce sasiednie
	VI p;
	FOR(x,1,4) p.PB(x);
	PermMinTrAdj( p,DisplayAdj );*/
	
	// Generowanie podzbiorow, NIE DZIALA, NIE DZIALA, NIE DZIALA...
//	SubsetMin( 4, &DisplaySubset );
	
//	Subsets::Generate(8);

	
//	SubsetKLex( 4,7,&DisplaySubsetKLex );
	
//	SetPartition( 13,&DisplayPartition );

//	NumPart( 10,&DisplayNumPart );
	
	
}









