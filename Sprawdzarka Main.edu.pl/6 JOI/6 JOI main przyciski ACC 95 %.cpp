#include<stdio.h>
//#include<iostream>
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
typedef vector< VD > VVD;
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


int N, M;
int a,lastmax;

/*
JEst to wlasne drzewo przedzialowe, w ktorym wszystkie operacje wykonywane sa od gory
Nie jest wiec to najszybsze drzewo, ale operacje wstawiania i znajdywania sa logarytmiczne
Tutaj pokrywa sie liczby od 0 do N, a nie przedzialy   -   jesli chcesz pokryc przedzialy musisz utozsamic liczbe 0 z przedzialem 0-1, liczbe 1 z przedzialem 1-2,  itd.

*/
template<class _T>
class CTree{
public:
	#define NR (p1+k1)/2
//	typedef int _T; // to co ma byc przechowywane w wezlach
	typedef pair<_T, int> PTT;
	int N; // ilosc liczb, na ktorych chcemy operowac, tzn jesli chcemy operowac na 5 liczbach, to potrzebujemy stworzyc tablice rozmiarow 2 * 8
	int s; // jest to liczba bedaca najmniejsza potega dwojki, nie mniejsza niz N, UWAGA - liczba   L do ktorej chcemy sie odniesc jest w tablicy tab na miejscu s + L
	_T* el; // tabllica reprezentujaca ilosc przedzialow pokrywajacych dany wezel
	_T* _max; // ---|--- maksimum ---|---
	int size; // rozmiar tablicy tab(i innych jesli beda)
	int p,k; // liczby p oraz k oznaczaja poczatek i koniec przedzialu, ktory chcemy dodac
	_T l; // l oznacza ilosc 'przedzialow' jakie chcemy dodac 
	
	
	
	// konstruktor przyjmujacy jako wartosc maksymalna liczbe, na ktorej bedziemy wykonywac operacje, tzn tab bedzie reprezentowac liczby 0,1,2,...,N-1   !!!
	CTree( int aN ) : N(aN), s(1) {
		while( s <= N ) s <<= 1;
		size = (s << 1 );
				
		el = new _T[size];	
		_max = new _T[size];
		REP(i,size){ 
			el[i] = 0;
			_max[i] = 0; 
		}
	}
	
	
	~CTree(){
		delete[] el; el = 0;
		delete[] _max; _max = 0;
	}
	
	// p1 - poczatek przedzialu reprezentowanego przez wezel,  k1 - koniec przedzialu repr.przez wezel,  g - numer wezla
	void help_add( int p1, int k1, int g ){
		if( p1 > k || k1 < p ) return; // jesli przedzialy sa rozlaczne, to nic nie robie
		if( p1 >= p && k1 <= k ){ // jesli wstawiany przedzal zawiera w calosci przedzial reprezentowany przez wezel to...
			el[g] += l;
			_max[g] += l;
			return;
		}
		
		// w przeciwnym razie rozbijam wezel na 2 podwezly
		help_add( p1, NR, g<<1 );
		help_add( NR + 1, k1, (g<<1)+1 );
		
		_max[g] = ( _max[g<<1] >= _max[(g<<1)+1] ? _max[g<<1] : _max[(g<<1)+1] ); // jelsi jest <= lub >= to zostanie zwrocony najmniejszy index danewgo ekstremum
	}
	
	// funkcja dodaje l1 przedzialow p1, p1+1, ..., k1
	void Add( int p1, int k1, int l1 ){
		p = p1;		k = k1;		l = l1;
		help_add( 0,s-1,1 );
	}
	
	
	_T help_max( int p1, int k1, int g ){
		if( p1 > k || k1 < p ) return -INF; // jesli przedzialy sa rozlaczne to zwracam cos co jest wieksze od wszystkiego
		if( p1 >= p && k1 <= k ) return _max[g]; // jesli caly przedzial jest zawarty, to zwracam minimum reprezentowane przez dany wezel
		_T maxpair = max( help_max( p1,NR,g<<1 ), help_max( NR + 1, k1, (g<<1)+1 ) ); // biore minimum z podwezlow
		maxpair += el[g];
		return maxpair;
	}
	
	// funkcja zwraca wartosc oraz index maksimum na przedziale p1-k1
	_T FindMax( int p1, int k1 ){
		p = p1;		k = k1;
		return help_max(0,s-1,1);
	}
	
	// funkcja ustawiajaca wartosc danego elementu o indeksie ind na okreslona wartosc val
	void set( int ind, _T val ){
		_T s = FindMax( ind, ind );
		Add( ind, ind, val - s );
	}
	
	// funkcja zwracajaca dana wartosc elementu o indeksie ind
	_T get( int ind ){
		return FindMax( ind, ind );
	}
	
	void writeAll( int g, int value ){
		if( g == s || g > s + ::N ) return;
		value += el[g];
		if( g > s && ( g <= ( s + (::N) ) ) ){
		//	cout << "g = " << g << "  lastmax = " << lastmax << "   value = " << value << endl;
			if( lastmax > value ) printf( "%d ", lastmax );
			else printf( "%d ",value );
			return;
		}
		
		writeAll( 2*g, value );
		writeAll( 2*g+1, value );
		
	}
	
};




int main(){
//	ios_base::sync_with_stdio(0);
//	cout << fixed;
//	cout.precision(2);
	
	
//	int N,M;
//	cin >> N >> M;
	scanf("%d %d",&N,&M);
	
	CTree<int> tree( N+2 );

	lastmax = 0;
	REP( i,M ){
	//	cin >> a;
		scanf("%d",&a);
	//	cout << "a = " << a << endl;
		if( a == N+1 ){
			lastmax = tree.FindMax( 1,N );
		//	cout << "lastmax = " << lastmax << endl;
		}else{
			int b = tree.get( a );
		//	cout << "\tb = " << b << endl;
			if( b < lastmax ) tree.set( a, lastmax+1 );
			else tree.Add( a,a,1 );
		}		
	}
	
	
	tree.writeAll( 1,0 );
/*	FOR(i,1,N){
		if( ( a = tree.get(i) ) < lastmax ) printf("%d ",lastmax);  // cout << lastmax << " ";
		else printf( "%d ",a );   //cout << a << " ";
	}*/
	//cout << endl;
	printf( "\n" );
	
	
	
	
	
	
	return 0;
}












