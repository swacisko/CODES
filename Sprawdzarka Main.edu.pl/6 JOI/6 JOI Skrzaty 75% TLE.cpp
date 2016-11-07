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
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;



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
	_T* _min; // tablica par oznaczajacych mimimum na danych przedziale oraz index tego minimum
	int size; // rozmiar tablicy tab(i innych jesli beda)
	int p,k; // liczby p oraz k oznaczaja poczatek i koniec przedzialu, ktory chcemy dodac
	_T l; // l oznacza ilosc 'przedzialow' jakie chcemy dodac 
	
	
	
	// tworzenie drzewa dla danej tablicy liczb w czasie liniowym, a nie liniowo-logarytmicznym
	// uwaga, do elementow tablic reprezentujacych element i przypisany zostanie element vac[i]
	CTree( const vector<_T> & vec ) : N(SIZE(vec)), s(1){
		while( s <= N ) s <<= 1;
		size = (s << 1 );
		el = new _T[size];
		_min = new _T[size];
		REP(i,size){ 
			el[i] = 0;
			_min[i] = INF;
		}
		
		REP(i,SIZE(vec)){
			_min[s+i] = vec[i]; // wartosc w lisciach
		}
		
		FORD( i,s-1,1 ){
			_min[i] = ( _min[(i<<1)] <= _min[(i<<1)+1] ? _min[(i<<1)] : _min[(i<<1)+1] ); // UWAGA, tutaj od znokow zalezy, index ktorego z elementow o tej samej wartosci zostanie zwrocony!!
		}
	}
	
	~CTree(){
		delete[] el; el = 0;
		delete[] _min; _min = 0;
	}
	
	// p1 - poczatek przedzialu reprezentowanego przez wezel,  k1 - koniec przedzialu repr.przez wezel,  g - numer wezla
	void help_add( int p1, int k1, int g ){
		if( p1 > k || k1 < p ) return; // jesli przedzialy sa rozlaczne, to nic nie robie
		if( p1 >= p && k1 <= k ){ // jesli wstawiany przedzal zawiera w calosci przedzial reprezentowany przez wezel to...
			el[g] += l;
			_min[g] += l;
			return;
		}
		
		// w przeciwnym razie rozbijam wezel na 2 podwezly
		help_add( p1, NR, (g<<1) );
		help_add( NR + 1, k1, (g<<1)+1 );
		
		_min[g] = ( _min[(g<<1)] <= _min[(g<<1)+1] ? _min[(g<<1)] : _min[(g<<1)+1] ); // UWAGA, tutaj od znokow zalezy, index ktorego z elementow o tej samej wartosci zostanie zwrocony!!
	}
	
	// funkcja dodaje l1 przedzialow p1, p1+1, ..., k1
	void Add( int p1, int k1, int l1 ){
		p = p1;		k = k1;		l = l1;
		help_add( 0,s-1,1 );
	}
	
	
	// p1 - poczatek przedzialu reprezentowanego przez wezel,  k1 - koniec przedzialu repr.przez wezel,  g - numer wezla
	_T help_min( int p1, int k1, int g ){
		if( p1 > k || k1 < p ) return INF; // jesli przedzialy sa rozlaczne to zwracam cos co jest wieksze od wszystkiego
		if( p1 >= p && k1 <= k ) return _min[g]; // jesli caly przedzial jest zawarty, to zwracam minimum reprezentowane przez dany wezel
		int minpair = min( help_min( p1,NR,(g<<1) ), help_min( NR + 1, k1, (g<<1)+1 ) ); // biore minimum z podwezlow
		minpair += el[g];
		return minpair;
	}
	
	// funkcja zwraca wartosc oraz index minimum na przedziale p1-k1
	_T FindMin( int p1, int k1 ){
		p = p1;		k = k1;
		return help_min(0,s-1,1);
	}
	
};



int main(){
	ios_base::sync_with_stdio(0);
	
	int N,M;
	cin >> N >> M;
	
	VI V( N+1,INF );
	CTree<int> tree( V );
	
	bool can = false;
	int K;
	int ind = M;
	int czas;
	VI G;
	int para;
	int t,p;
	for(czas=0; czas<M; czas++){
		
		cin >> K;
		if( can ){
			REP(i,K) cin >> para;
			continue;
		}
		
		G.resize(K);
		REP(i,K) cin >> G[i];
		
		if( can ) continue;
		if( G[0] != 1 && G[ K-1 ] != N ){
			ind = min( ind,czas );
			can = true;
			continue;
		}
		
		bool layer = false;
		if( G[0] != 1 ) layer = true;
		
		t = 0;
		p = 1;
		while( t < K ){ // dla kazdego spojnego przedzialu...
			if( p < G[t] ){
			//	cout << "Rozwazam przedzial [" << p << " , " << G[t]-1 << "]" << endl;
				para = tree.FindMin( p,G[t]-1 );
			//	cout << "\tMinimum na tym przedziale jest mniejsze od INF:  " << (para.ST < INF) << endl;
				if( para < INF ){
					if( G[ K-1 ] != N ){
						can = true;
						break;
					}					
					layer = true;				
				}				
			}
			
			p = G[t]+1;
			t++;
		}
		
		if( p <= N ){
		//	cout << "Rozwazam przedzial [" << p << " , " << N << "]" << endl;
			para = tree.FindMin( p,N );
		//	cout << "\tMinimum na tym przedziale jest mniejsze od INF:  " << (para.ST < INF) << endl;
			if( para < INF ){
				if( G[ K-1 ] != N ){
					can = true;
				}				
				layer = true;				
			}
		}
		
		if( can ) ind = czas;
		
		if( layer ){ // jesli jestem w stanie wejsc na dana warstwe, to dodaje ja do grafu przeszukiwan
		//	cout << "Jestem w dodawaniu przedzialow do warstw ( layer == true )" << endl;
			t = 0, p = 1;
			while( t < K ){
				if( p < G[t] ){
					tree.Add( p,G[t]-1,-1 );					
				}				
				p = G[t]+1;
				t++;
			}
			
			if( p <= N ){
				tree.Add( p,N,-1 );
			}
			
		}
		
		
	}
	
	
	cout << ind << endl;
	
	
	
}












