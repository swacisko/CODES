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
int N,M,K,a,b,c,y,t,w,S,l_zest;
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


const int hallway = 0;
int JED;
int bedroom;

int states[11]; // stany bitowe
VI switches[11]; // z wierzcholka nr i sa przyciski do pokoi nrswitches[i][0], switches[i][1], ...

VI V[10241]; // to jest wlasciwy graf

VI edges[11]; // edges[i] to zbior krawedzi wychodzacych z pokoju i
int pot;// to jest po prostu 2^N

const int MSIZE = 10241;



void clear_all(){
	REP(i,MSIZE) V[i].clear();
	REP(i,11) switches[i].clear();
	REP(i,11) edges[i].clear();
}


int par[10241]; // par[i] to numer ojca wierzcholka nr i w BFS'ie, potrzebne do wyznaczenia najkrotszej sciezki

// to jest ten chytry BFS
void BFS(){
	VI neigh( 1,hallway*pot + states[ hallway ] );
	bool *was = new bool[ MSIZE ]; // was[i] - czy juz bylem w wierzcholku i
	REP(i,MSIZE) was[i] = false;
	was[1] = true; // w hallway bylem
	REP(i,MSIZE) par[i] = INF;
	
	REP(i,SIZE(neigh)){ // to jest kolejka		
		int g = neigh[i];
		if( g == bedroom*pot + states[ bedroom ] ) break; // jesli doszedlem do sypialni to owroc
		REP( k,SIZE( V[g] ) ){ // dla kazdego sasiada wierzcholka neigh[i]
			if( !was[ V[g][k] ] ){ // jesli jeszcze nie bylem
				neigh.PB( V[g][k] ); // dodaje do kolejki
				was[ V[g][k] ] = true; // juz bylem
				par[ V[g][k] ] = g; // ustawiam rodzica
			}
		}
		
	}
	
	delete[]was;
	return;	
}

// funkcja zwraca numery wierzcholkow, przez ktore przechodze w njakrotszej sciezce z hallway do bedroom, ale z grafu V, trzeba je bedzie pozniej przetworzyc na stepy z zadania
VI getPath(){
	int last = bedroom * pot + states[ bedroom ];
	int first = hallway*pot + states[ hallway ];
	
	if( par[last] == INF ) return VI();
	
	VI v;
	while( last != first ){
		v.PB( last );
		last = par[ last ];
	}
	v.PB(first);
	reverse( ALL(v) );
	return v;
}

// funkcja zwraca numer pokoju, w ktorym zgaszono / zapalono swiatlo, czyli nr bitu na ktorym roznia sie te dwie liczby + 1
int getRoomNumber( int stan, int stan_prev ){
	int t = ( stan ^ stan_prev );
	int ile = 1;
	while( t > 1 ){
		ile++;
		t >>= 1;
	}
	return ile;
}

// przyjmuje sciezke i wypisuje odpowiedz
void writeAnswer( VI & v ){
//	cout << "pot = " << pot << endl;
//	cout << "A oto twoja droga:" << endl;
//	WRITE(v);
	
	
	
	if( !SIZE(v) ){ // jesli nie ma sciezki to nie ma rozwiazania :)
		cout << "The problem cannot be solved." << endl;
		return;
	}
	
	cout << "The problem can be solved in " << SIZE(v)-1 << " steps:" << endl;
	
	int room_nr, room_nr_prev; // numer pokoju i numer pokoju, w ktory mbylem przed chwila
	room_nr_prev = 0;
	int stan, stan_prev; // stan swiatla w pokojach
	stan_prev = 1; // na poczatku swiatlo jest tylko w hallway	
	FOR( i,1,SIZE(v)-1 ){ // pierwszy element to hallway i on nas nie interesuje, bo nic nie wnosi do naszej odpowiedzi
		room_nr = v[i] / pot;
		if( v[i] % pot == 0 ) room_nr--; // jesli przy dzieleniu daje reszte 0, to znaczy ze jest to pokoj o jeden mniejszy ale w stanie, gdzie wszystkie pokoje maja zapalona lampe
		
		stan = v[i] - room_nr*pot;
		if( room_nr != room_nr_prev ){ // jesli przeszedlem do innego pokoju
			cout << "- Move to room " << room_nr+1 << "." << endl;
		}
		else{
			if( stan > stan_prev ){ // jesli wlaczam swiatlo
				cout << "- Switch on light in room " << getRoomNumber( stan, stan_prev ) << "." << endl;
			}
			else{ // jesli wylaczam swiatlo
				cout << "- Switch off light in room " << getRoomNumber( stan, stan_prev ) << "." << endl;
			}
		}
		
		stan_prev = stan;
		room_nr_prev = room_nr;
	}
	
	
}


int main(){
	ios_base::sync_with_stdio(0);
	states[0] = 1;
//	states[1] = 1;
	FOR(i,1,10) states[i] = (states[i-1] << 1); // ustawiam stany pokoi
//	JED = 0;
//	REP(i,11) JED += states[i];
//	REP(i,11) cout << (JED ^ states[i]) << endl;
	
	l_zest = 1;
	int r,d,s;
	while( 1 ){
		cin >> r >> d >> s ;
		if( r == 0 && d == 0 && s == 0 ) break;
		if( l_zest > 1 ) cout << endl;
		
		clear_all();
		
		N = r; // ilosc wierzcholkow
		M = d; // ilosc krawedzi
		S = s; // ilosc przelacznikow
		bedroom = r-1; // numer sypialni to r-1		
		pot = (int)(pow(2,N)+0.1);
		
		REP(i,M){
			cin >> a >> b;
			if( a == b ) continue;
			edges[a-1].PB(b-1);
			edges[b-1].PB(a-1);
		}
		
		REP(i,S){
			cin >> a >> b;
			if( a == b ) continue; // nie ma sensu dodawac przelacznikow do samego siebie, bo nigdy sie ich nie uzyje
			switches[a-1].PB(b-1);
		}
		
		if( hallway == bedroom ){
			cout << "Villa #" << l_zest++ << endl;
			cout << "The problem can be solved in 0 steps:" << endl;
			continue;
		}
		
		
		REP( i,N ){ // dla kazdego pokoju
			REP(j,SIZE(switches[i])){ // dla kazdego przelacznika
				FOR( k, i*pot+1, i*pot + pot-1 ){ // dla kazdego z mozliwych stanow...
					int stan = k - i*pot; // aktualny stan, ktory rozwazam
					if( (stan & states[ switches[i][j] ] ) == 0 ){ // jeslijestem jestem w stanie przelaczyc stan to...
						V[ k ].PB( i*pot + ( stan | states[ switches[i][j] ] ) );
						V[ i*pot + ( stan | states[ switches[i][j] ] ) ].PB(k);
						
					/*	if( ( k == 5 && ( i*pot + ( stan | states[ switches[i][j] ] ) ) == 13 )   || ( k == 13 && ( i*pot + ( stan | states[ switches[i][j] ] ) ) == 5 ) ){
							cout << "!!!!!   Dodaje pare 5, 13" << endl;
							cout << "Stan = " << stan << "  edges["<<i<<"]["<<j<<"] = " << edges[i][j] << "    states["<< switches[i][j] << "] = " << states[ switches[i][j] ] << endl;
						}*/
					}
				}
			}
			
			// teraz trzeba polaczyc te wierzcholki, ktore sa polaczone 'drzwiami'
			REP(j,SIZE(edges[i])){ // dla kazdych drzwi do innego pokoju
				FOR( k, i*pot+1, i*pot + pot-1 ){ // dla kazdego z mozliwych stanow...
					int stan = k - i*pot; // aktualny stan, ktory rozwazam
					if( (stan & states[i]) == 0 ) continue; // jesli jestem w zgaszonym pokoju to nie moge isc nigdzie...
					if( (stan &  states[ edges[i][j] ]  ) == 0 ) continue; // jesli stan jest wylaczony, to nie dodaje krawedzi, bo nie moge wejsc do pokoju ze zgaszonym swiatlem
					V[ k ].PB( edges[i][j]*pot + stan );
					V[ edges[i][j]*pot + stan ].PB( k );
					
				/*	if( ( k == 5 && (edges[i][j]*pot + stan == 13) )   || ( k == 13 && (edges[i][j]*pot + stan == 5) ) ){
						cout << "###### Dodaje pare 5, 13   i = " << i << endl;
						cout << "Stan = " << stan << "  edges["<<i<<"]["<<j<<"] = " << edges[i][j] <<"   states["<<edges[i][j] << "] = " << states[ edges[i][j] ] << endl;
					}*/
				}
			}
		}
		
		
		//***********
	/*	cout << "Oto twoj graf" << endl;
		REP(i,25){
			cout << "i = " << i << endl << "\t";
			REP(k,SIZE(V[i])) cout << V[i][k] << " ";
			cout << endl;
		}*/
		
		BFS();
		
		VI v = getPath(); // wektor, ktory zawierac sciezke z hallway do bedroom
		
		cout << "Villa #" << l_zest++ << endl;
		writeAnswer( v );
	//	cout << endl;
		
	}
	
	
	
	
	
	return 0;
}












