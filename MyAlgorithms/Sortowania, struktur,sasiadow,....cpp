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
typedef map< PII, bool > MPIIB;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;


// moja struktura, przedstawiajaca, jak sortowac struktury wzgledem danych pol
struct my_s{
	my_s( PII p, int a, string s ) : p(p), a(a), s(s) {}
	PII p;
	int a;
	string s;
	
	bool operator<( const my_s & ms ) const{
		return s < ms.s; // sortowanie po stringu
	}
};

typedef vector<my_s> VMS;
typedef vector<VMS> VVMS;

ostream & operator<<( ostream& strin, const my_s & s ){
	strin << WRP(s.p) << ",  " << s.a << ",  " << s.s << endl;
	return strin;
}

bool sortPair( my_s a, my_s b ){
	return a.p < b.p;
}

bool sortA( my_s a, my_s b ){
	return a.a < b.a;
}

bool sortS( my_s a, my_s b ){
	return a.s < b.s;
}


//******************************************************************************

// funkcja s³u¿y do sortowania list s¹siedztwa wszystkich wierzcholkow danego grafu w czasie liniowym
void sortNeigh( VVI & V ){
	VVI w(SIZE(V));
	REP(i,SIZE(V)) REP(k,SIZE(V[i])) w[ V[i][k] ].PB(i);
	V.clear(); V = VVI(SIZE(w));
	REP(i,SIZE(w)) REP(k,SIZE(w[i])) V[ w[i][k] ].PB(i);
}

//******************************************************************************

// funkcja jako parametr przyjmuje tablice intow, sortuje ta tablice
// sortowanie przez zliaczanie, w czasie liniowym, ale potrzebne jest O( max( V[i] ) - min( 0, min( V[i] ) ) ) pamieci, czyli zakres danych w zadaniu musi byc stosunkowo niewielki, aby sie oplacalo tak sortowac
void countSort( VI & V ){
	int M = 0, m = 0;
	REP(i,SIZE(V)) {
		if( V[i] < m ) m = V[i];
		if( V[i] > M ) M = V[i];
	}
	if( m < 0 ) REP(i,SIZE(V)) V[i] -= m;
	M -= m;
	VI ile(M+1,0);
	REP(i,SIZE(V)) ile[ V[i] ]++;
	int p = 0;
	REP( i,SIZE(ile) ) while( ile[i]-- ) V[p++] = i;
	if( m < 0 ) REP(i,SIZE(V)) V[i] += m;
}

// funkcja countSort, wersja prawid³owa z Cormena, jest to sortowanie stabilne, czyli kolejnosc elementow rownych nie ulega zmianie, mozna sortowac dowolne struktury, tylko musza miec operator [] zwracajacy int
// oraz musza to byc liczby nieujemne
template<class typ>
void CountSort( vector<typ> & A ){
	vector<typ> C(SIZE(A));
	int M = 0;
	REP(i,SIZE(A))	if( A[i] > M ) M = A[i];
	VI B(M+1,0);
	REP(i,SIZE(A)) B[ A[i] ]++;
	FOR(i,1,M) B[i] += B[i-1];
	FORD( i,SIZE(A)-1,0 ) C[ --B[ A[i] ] ] = A[i];
	swap(A,C);
}


//******************************************************************************

// quicksort
template<class typ>
int podzial( typ & V, int p, int q ){
	int l = p;
	FOR(i,p,q-1) if( V[i] < V[q] ) swap( V[i], V[l++] );
	swap( V[l], V[q] );
	return l;
}

template<class typ>
void quicksort( typ & V, int p, int q ){
	if( p < q ){
		int k = podzial( V,p,q );
		quicksort( V, p,k-1 );
		quicksort( V,k+1,q );
	}
}

//******************************************************************************

// sortowanie wskaznikowe, patrz przyklad, po sortowainu liczb, wykonujac na nich operacje nadal mozemy modyfikowac dane zapisane wczesniej w tabelach, przez to ze dzialamy na wskaznikach

// pointerQuicksort
template<class typ>
int podzial2( typ & V, int p, int q ){
	int l = p;
	FOR(i,p,q-1) if( *V[i] < *V[q] ) swap( V[i], V[l++] );
	swap( V[l], V[q] );
	return l;
}

template<class typ>
void pointerQuicksort( typ & V, int p, int q ){
	if( p < q ){
		int k = podzial2( V,p,q );
		pointerQuicksort( V, p,k-1 );
		pointerQuicksort( V,k+1,q );
	}
}

//******************************************************************************


template< class _T>
void IntSort( vector<_T> &V ){
	typedef vector<_T> VT;
	typedef vector< VT > VVT;
	int N = SIZE(V);
	
	int lgn = (int) log2(N);
	int trans = 0;
	REP(i,lgn){ trans<<=1; trans++; }	
	
	int M = -INF, m = INF, p = 0, q = 0;
	VVT ile;			
	REP(i,SIZE(V)) {
		if( V[i] < m ) m = V[i];
		if( V[i] > M ) M = V[i];
	}
	REP(i,SIZE(V)) V[i] -= m;
	
	while( trans != 0 ){	
		int M = -INF, m = INF;				
		REP(i,SIZE(V)) {
			if( V[i] < m ) m = V[i];
			if( V[i] > M ) M = V[i];
		}
		ile = VVT(N);
		REP(i,SIZE(V)) ile[ (V[i]&trans) >> p ].PB( V[i] );
		q = 0;
		REP( i, SIZE(ile) ){
			REP(k,SIZE(ile[i])){
				V[q++] = ile[i][k];
			}
		}
		
		cout << "p = " << p << endl;
		p+=lgn;
		trans <<= lgn;
	}
	
	REP(i,SIZE(V)) V[i] += m;
	
}



void testIntSort(){
	
	VI V;	
	const int ILE = 100000, U = 2000000000;
	REP(i,ILE) V.PB( rand()%U - U/2 );
	
	VI V2 = V;
	
	IntSort( V );
	sort( ALL(V2) );
	
	cout << SIZE(V) << endl;
	
	cout << "Checking, whether vector is sorted correctly" << endl;
	bool same = true;
	REP( i,SIZE(V) ) {
		if( V[i] != V2[i] ){
			cout << "Sorted vectors differ on " << i << "-th position" << endl;
			same = false;
			break;
		}		
	}
	
	if( same ) cout << "Well sorted!" << endl;
	
	
	ENDL(3);
	cout << "Now real time check" << endl;
	
	double timeIntSort = 0;
	double timeLibSort = 0;
	double t1 = 0, t0 = 0;
	
	
	for( int i=1000; i<= 1000; i+= 10000 ){
		V.clear();
		REP(k,i) V.PB( rand()%U - U/2 );
		V2 = V;
		
		t0 = clock();
		IntSort(V);
		t1 = clock();
		timeIntSort += ( t1 - t0 );
		
		t0 = clock();
		sort( ALL(V2) );
		t1 = clock();
		timeLibSort += ( t1 - t0 );		
	}
	
	timeIntSort /=  CLOCKS_PER_SEC;
	timeLibSort /= CLOCKS_PER_SEC;
	
	cout << "Sorting using IntSort took " << timeIntSort << " seconds   whereas" << endl
		 << "Sorting using LibSort took " << timeLibSort << " seconds" << endl;
		 
	cout << endl << "IntSort works " << (double) timeLibSort / timeIntSort << " times faster!" << endl;
	
}


int main(){
	
	srand(unsigned(time(0)));
	
	testIntSort();
	
	
/*	// sortowanie po strukturze
	vector<my_s> V;
	V.PB( my_s( MP( 1,3 ), 5, "aabb") );
	V.PB( my_s(MP( 1,4 ), 4, "aaba") );
	V.PB( my_s(MP( 17,2 ),4, "cedryk") );
	V.PB( my_s(MP( 5,-1 ), 1, "a") );
	V.PB( my_s(MP( 5,4 ), 7, "beczka") );
	
	WRITE(V);
	
	cout << "Sortowane po parach:" << endl;
	sort( ALL(V),sortPair );
	WRITE(V);
	
	sort( ALL(V), sortA );
	cout << "Sortowane po a:" << endl;
	WRITE(V);
	
	sort( ALL(V), sortS );
	cout << "Sortowane po s:" << endl;
	WRITE(V);
	*/
	
/*	// countSort i w³asny quicksort	
	cout << "Podaj liczby do tablicy, element -131 konczy podawanie:" << endl;
	VI G;
	while( cin >> a ){
		if( a == -131 ) break;
		G.PB( a );
	}
	
	system("cls");
	cout << "Oto twoje liczby:" << endl;
	WRITE(G);
	ENDL(3);
	
	VI G1 = G;
	
	cout << "A oto twoje posortowane liczby algorytmem countSort:" << endl;
	countSort( G1 ); 
	WRITE(G1);
	ENDL(3);
	
	cout << "A oto twoje posortowane liczby algorytmem CountSort z Cormena:" << endl;
	CountSort( G1 ); 
	WRITE(G1);
	ENDL(3);
	
	G1 = G;
	cout << "A oto twoje posortowane liczby algorytmem quicksort:" << endl;
	quicksort( G1,0,SIZE(G1)-1 );
	WRITE(G1);
	*/
	
	
	
/*	// sortowanie wskaznikowe, sortuje elementy tablicy, z ktorymi pozniej mozna robic cos wedle uznania, a przez to ze dziala na wskaznikach, to w innych tablicach te zmiany tez sa dokonywane
	// patrz przyklad ponizej
	cout << "Podaj liczby do tablicy, element -131 konczy podawanie:" << endl;
	vector<int*> G;
	while( cin >> a ){
		if( a == -131 ) break;
		G.PB( new int(a) );
	}
	
	
	cout << "Oto twoje liczby:" << endl;
	REP(i,SIZE(G)) cout << *G[i] << " ";	
	ENDL(3);
	
	vector<int*> G1 = G;
	
	cout << "Oto posortowane liczby:" << endl;
	pointerQuicksort( G1,0,SIZE(G1)-1 );
	REP(i,SIZE(G1)) cout << *G1[i] << " ";*/
	
	
	
/*	// sortowanie wskaznikowe dla struktury, moze wiec byc przydatne	
	vector<my_s*> V;
	V.PB( new my_s( MP( 1,3 ), 5, "aabb") );
	V.PB( new my_s(MP( 1,4 ), 4, "aaba") );
	V.PB( new my_s(MP( 17,2 ),4, "cedryk") );
	V.PB( new my_s(MP( 5,-1 ), 1, "a") );
	V.PB( new my_s(MP( 5,4 ), 7, "beczka") );
	
	system("cls");
	vector<my_s*> G = V; // tworze kopie
	cout << "Twoja struktura:" << endl;
	REP(i,SIZE(V)) cout << *V[i] << endl;
	ENDL(3);
	
	pointerQuicksort( V,0,SIZE(V)-1 );	
	cout << "Oto posortowana struktura:" << endl;
	REP(i,SIZE(V)) cout << *V[i] << endl;
	ENDL(2);

	cout << "Dla kazdego elementu zwiekszam mu wartosc pola a o i, gdzie i to numer danego elementu po posortowaniu\nTeraz posortowana struktura ma postac:" << endl;
	REP( i,SIZE(V) ) (*V[i]).a += i;
	REP(i,SIZE(V)) cout << *V[i] << endl;
	ENDL(2);
	
	cout << "Mimo, ze na wektorze G nie wykonywalem zadnej operacji, to wartosci pola  -> a <-  w nim tez ulegly zmianie:" << endl;
	REP(i,SIZE(G)) cout << *G[i] << endl;
	ENDL(2);*/
	
	
	
	
	
	
	
}









