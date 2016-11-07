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


int binom( int N, int K ){
	if( N < K ) return 0;	
	LL n = 1;
	LL k = 1;
	int p = N;
	int q = 1;
	while( p >= N-K+1 && q <= K ){
		if( p <= N ) n *= p--;
		if( q <= K ) n /= q++;
	}
	return n;
}


//  ***************************************************************************** CWICZENIA NR 1




//  ***************************************************************************** CWICZENIA NR 2





//  ***************************************************************************** CWICZENIA NR 3 - GENEROWANIE WSZYSTKICH PODZBIOROW DANEGO ZBIORU,  MINIMALNE ZMIANY,  KOD GRAYA


// funkcja, ktora wywoluje algorytm GraySubsets, p oznacza element, ktory sie rozni od poprzedniego zbioru, added==1 jesli dodalismy p  oraz added==0 jesli usunelismy p
void fun_gray( int p, bool added ){
}

// funkcja dla zadanego N generuje wszystkie podzbiory zbioru {1,2,...,N} i dla kazdego z nich wywoluje funkcje fun_gray zgodnie ze specyfikacja podana przed ta funkcja
// dziala w czasie O( 2^N * lgN ), czyli w zasadzie O(2^N) bo lgN < 5,   set<int> zbior  mozna latwo zamienic na zwyklad tablice, ale wtedy trzeba by iterayjnie szukac maxymalnego elementu
void GraySubsets( int N ){
	set<int> zbior;
	zbior.insert(N);
	bool waga = true;
	cout << "Zbior pusty" << endl;
	WRITE(zbior);
	
	int P = 0;
	bool added = true;
	int el_max = N-1;
	while( el_max > 0 ){	
		
		if( waga ){
			if( zbior.count( el_max ) ){
				zbior.erase( el_max );
				added = false;
			}
			else {
				zbior.insert( el_max );
				added = true;
			}
			P = el_max;
		}
		else{
			if( zbior.count(N) ) {
				zbior.erase(N);
				added = false;
			}
			else{
				zbior.insert(N);
				added = true;
			}
			P = N;
		}
		
		//WRITE(zbior);
		fun_gray( P, added );
		
		waga = !waga;
		el_max = *zbior.rend()-1;
	}
	
	
}


//******************************************************************************

// funckja zwracajaca range przeslanego jako parametr podzbioru w uporzadkowaniu minimalnych zmian kodem Graya
int rank_grey( int N, VI & V ){
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

// funkcja dla zadanej rangi r zwraca podzbior ktorego ranga wynosi r, w uporzadkowaniu minimalnych zmian kodem Graya 
set<int> unrank_gray( int N, int r ){
	
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



//  ***************************************************************************** CWICZENIA NR 4 - GENEROWANIE K-ELEMENTOWYCH PODZBIOROW W KOLEJNOSCI LEXYKOGRAFICZNEJ

// funkcja wyznacza nastepnik zadanego jako parametr K-elementowego podzbioru zbioru {1,2,..,N} uporzadkowanego rosnaco
// dziala w czasie O(K)
VI nastepnik_lex( VI & V, int N, int K ){
	int ind = K;

	while( ind > 0 && V[ind] == N+ind-K ) ind--;
	if( ind == 0 ) return VI(0);
	V[ind]++;
	FOR(i,ind+1,K) V[i] = V[i-1] + 1;
	return V;
	
}

// funkcja zwraca range zadanego jako parametr K-elementowego podzbioru zbioru {1,2,..,N} w uporzadkowaniu lex
// podzbior ten musi byc posrotwany rosnaco, dzial w czasie O(K+N)
int rank_lex( VI & V, int N, int K ){
	int wyn = 0;
	FOR(i,1,K) FOR(j,V[i-1]+1, V[i]-1) wyn += binom( N-j, K-i );
	return wyn;
}


// funckja zwraca podzbior zbioru {1,2,...,N}, ktorego ranga wynosi r ( w uporzadkowaniu lex )
// dzial w czasie chyba okolo O(K)
VI unrank_lex( int N, int K, int r ){
	VI V(K+1,0);
	int x = 1;
	FOR(i,1,K){
		while( binom( N-x, K-i ) <= r ){
			r -= binom( N-x, K-i );
			x++;
		}

		V[i] = x;
		x++;
	}
	
	
	return V;
}





//  ***************************************************************************** CWICZENIA NR 5 - CIAGI K-ELEMENTOWE W KOLEJNOSCI  ANTYLEKSYKOGRAFICZNEJ

// funckja jako parametr przyjmuje liczby N, K oraz wektor liczb reprezentujacy k-elementowy ciag, dla ktorego mam wyznaczyc nastepnik
// uwaga, wektor V musi byc posortowany malejaco i zawierac dokladnie K liczb-czyli indeksowany od 0
// dzial w czasie O(K)
VI nastepnik_colex( VI V, int N, int K ){
	int ind = K;
	V.insert( V.begin(),N+1 );
	
	while( ind > 0 && V[ind-1] - V[ind] == 1 ) ind--;
	V.erase( V.begin() );
	
	if( ind == 0 ) return V;
	V[ind-1]++;
	FOR(i,ind,K-1) V[i] = K-i;
	return V;
}

// funkcja wyznacza range danego jako parametr  K-elementowego zbioru  w uporzadkowaniu colex(czyli antyleksykograficznym)
// V musi byc posortowane malejaco
int rank_colex( int N, int K, VI & V ){
	int r = 0;
	FOR( i,1,K ) r += binom( V[i-1]-1, K-i+1 );
	return r;
}


// funckja zwraca jako wynik k-elementowy zbior, ktorego ranga jest rowna zadanemu r
// dziala w czasie okolo O(K)
VI unrank_colex( int N, int K, int r ){
	VI V(K);
	int t = 0;
	int K2 = K;
	FOR(i,0,K2-1){
		t = K;
		while( binom(t,K) <= r ) t++;
		r -= binom(t-1,K);
		K--;
		V[i] = t;
		//cout << "t = " << t << "  K = " << K << "   r = " << r << endl;
	}
	return V;

}


//**********************************************************************************




int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);
	
	
	int N,K;
	
		
	
	
	return 0;
}












