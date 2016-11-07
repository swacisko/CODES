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


VI gr; // gr[i] to najmniejsze takie j, i<j oraz cars[i].wys <= cars[j].wys, potrzebne do wyznaczania tablicy poz
VI poz; // poz[i] to najmniejsze takie j, ze  i<j oraz cars[i].wys + cars[j].wys > w
VPII results; // wektor par results przechowuje pary <p,q>, tzn samochod nr p nie moze byc po samochodzie nr q w ustawieniu wyjsciowym, czyli
				// samochod nr p MUSI byc PRZED samochodem nr q


struct car{
	car( int ax1, int ax2, int ay1, int ay2, int anum ) : x1(ax1), x2(ax2), y1(ay1), y2(ay2), num(anum) { wys = y2-y1; }
	int num; // numer samochodu
	int x1,x2,y1,y2;
	int wys; // oznacza wysokosc samochodu, czyli roznice we wspolrzednych y
/*	bool operator<( const car & oth )const{
		if( x1 < oth.x1 ) return true;
		else if( x1 == oth.x1 && y1 <= oth.y1 ) return true;
		return false;
	}*/
};

bool sortX( const car & c1, const car & c2 ){
	if( c1.x1 < c2.x1 ) return true;
	else if( c1.x1 == c2.x1 && c1.y1 <= c2.y1 ) return true;
	return false;
}


// signum przyjmuje dwie wartosci albo 0, albo 1 - jesli 0, tzn ze wywoluje solution po raz pierwszy, jesli 1 to znaczy ze wywoluje solution po owdroceniu vectora cars
void solution( vector<car> & cars, int signum ){
	gr = VI(SIZE(cars),INF);
	poz = VI(SIZE(cars),INF);
	
	int t = 0;
	FORD(i,SIZE(cars)-2,0){ // tutaj uzupelniam tablice gr
		t = i+1;
		while( t != INF ){
			if( cars[t].wys >= cars[i].wys ) break;
			t = gr[t];
		}
		if( t != INF ) gr[i] = t;
	}
	
	FORD(i,SIZE(cars)-2,0){ // tutaj wyznaczam tablice poz
		t = gr[i];
		while( t != INF ){
			if( cars[i].wys + cars[t].wys > w ) break;
			t = poz[t];
		}
		if( t != INF ) poz[i] = t;		
	}
	
	if( signum == 0 ){
		REP(i,SIZE(poz)){
			if( poz[i] != INF ) results.PB( MP( cars[i].num, cars[poz[i]].num ) );
		}
	}
	else{
		REP(i,SIZE(poz)){
			if( poz[i] != INF ) results.PB( MP( cars[poz[i]].num, cars[i].num ) ); // jesli wywoluje solution po raz drugi, w odwroconej kolejnosci musze tez dodawac numery
																					// samochodow do wyniku
		}
	}
}






int main(){
	
	ios_base::sync_with_stdio(0);
	
	vector<car> cars; // ulozenie poczatkowe samochodow
	vector<car> cars2; // wektor reprezentujacy koncowe ulozenie samochodow
	VI pozycje;
	
	cin >> l_zest;
	while( l_zest-- ){
		
		cin >> N >> w;
		
		results.clear();
		cars.clear(); // ZMIANA
		
		int x1,x2,y1,y2;
		REP(i,N){
			cin >> x1 >> y1 >> x2 >> y2;
			if( x1 > x2 ) swap( x1,x2 ); // jesli jest podane nie w kolejnosci, to zameniam tak aby x1 bylo lewym rogiem
			if( y1 > y2 ) swap(y1,y2);
			
			cars.PB( car( x1,x2,y1,y2,i ) );
		}
		
		sort( ALL(cars), sortX ); // sortuje po wspolrzednych y
		
		
		solution(cars,0);
		reverse( ALL(cars) );
		solution(cars,1);
		
		
		pozycje = VI( SIZE(cars) );
		
		cars2.clear(); // ZMIANA
		
		REP(i,N){
			cin >> x1 >> y1 >> x2 >> y2;
			if( x1 > x2 ) swap( x1,x2 ); // jesli jest podane nie w kolejnosci, to zameniam tak aby x1 bylo lewym rogiem
			if( y1 > y2 ) swap(y1,y2);
			
			cars2.PB( car( x1,x2,y1,y2,i ) );
		}
		
		sort( ALL(cars2), sortX );
		
		REP( i,SIZE(cars2) ) pozycje[ cars2[i].num ] = i; // samochod nr num jest na pozycji i
		
		bool can = true;
		REP( i,SIZE(results) ){
			a = results[i].ST;
			b = results[i].ND;
			if( pozycje[a] > pozycje[b] ){
				can = false;
				break;
			}
		}
		
		if( !can ) cout << "NIE" << endl;
		else cout << "TAK" << endl;
		
		
	}
	
	
	return 0;
}












