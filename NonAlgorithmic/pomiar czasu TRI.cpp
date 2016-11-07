//#include<stdio.h>
//#include<cstdio>
#include<iostream>
#include<conio.h>
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



int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);
	
	while(1){
		
		cout << "Podaj dystans w km:  ";
		double dist;
		cin >> dist;
		
		double speed1, speed2;
		cout << "Podaj pierwsza predkosc w km/h:  ";
		cin >> speed1;
		cout << "Podaj druga predkosc w km/h:  ";
		cin >> speed2;
		
		speed1 /= 3.6; // teraz jest w metrach na sekunde
		speed2 /= 3.6;
		dist *= 1000; // dystans w metrach
		
		double time1 = dist / speed1;
		double time2 = dist / speed2;
		
		int t1, t2;
		ENDL(2);
		cout << "Czas pierwszej osoby to:  " << ( t1 = (int)( time1 / 3600 ) ) << " godzin, " << flush;
		cout << ( t2 = (int)( ( time1 - (double)t1*3600 )/60 ) ) << " minut, " << flush;
		cout << ( time1 - t1*3600 - t2*60 ) << " sekund" << endl;
		
		cout << "Czas drugiej osoby to:  " <<( t1 = (int)( time2 / 3600 ) )<< " godzin, " << flush;
		cout << ( t2 = (int)( ( time2 - (double)t1*3600 )/60 ) ) << " minut, " << flush;
		cout << ( time2 - t1*3600 - t2*60 ) << " sekund" << endl;
		
		ENDL(2);
		double diff = abs( time1 - time2 );
		cout << "Roznica czasowa to:" << endl << "\t" << diff << "  sekund" << endl << "\t" << (int)( diff/60 ) << " minut i " << diff - (double) ( 60*(int)( diff/60 ) ) << " sekund" << endl;
		
		ENDL(3);
		
		double h1,h2,m1,m2,s1,s2;
		
		cout << "Podaj pierwszy szacowany czas trasy:" << endl;
		cout << "\tPodaj godziny: ";
		cin >> h1;
		cout << "\tPodaj minuty: ";
		cin >> m1;
		cout << "\tPodaj sekundy: ";
		cin >> s1;		
		time1 = 3600*h1 + 60*m1 + s1;
		
		ENDL(2);
		
		cout << "Podaj drugi szacowany czas trasy:" << endl;
		cout << "\tPodaj godziny: ";
		cin >> h2;
		cout << "\tPodaj minuty: ";
		cin >> m2;
		cout << "\tPodaj sekundy: ";
		cin >> s2;		
		time2 = 3600*h2 + 60*m2 + s2;
		
		double min_per_km1 = ( time1/60 ) / ( dist / 1000 );
		double min_per_km2 = ( time2/60 ) / ( dist / 1000 );
		
		ENDL(2);
		cout << "Pierwszy czas to   ( " << (int)min_per_km1 << " min " << ( min_per_km1 - (double)( (int)min_per_km1 ) )*60 << " sek ) / km" << endl;
		cout << "Drugi czas to      ( " << (int)min_per_km2 << " min " << ( min_per_km2 - (double)( (int)min_per_km2 ) )*60 << " sek ) / km" << endl;
		
		double avs1 = 60 / ( min_per_km1 );
		double avs2 = 60 / ( min_per_km2 );
		
		ENDL(2);
		cout << "Srednia predkosc pierwszej osoby to:  " << avs1 << " km/h" << endl;
		cout << "Srednia predkosc drugiej osoby to:    " << avs2 << " km/h" << endl;
		
		ENDL(2);
		
		cout << "Podaj pierwsza predkosc w min/km:" << endl;
		cout << "\tPodaj minuty:  ";
		cin >> m1;
		cout << "\tPodaj sekundy:  ";
		cin >> s1;
		min_per_km1 = m1 + s1/60;
		
		cout << "Podaj druga predkosc w min/km:" << endl;
		cout << "\tPodaj minuty:  ";
		cin >> m2;
		cout << "\tPodaj sekundy:  ";
		cin >> s2;
		min_per_km2 = m2 + s2/60;
		
		time1 = (dist/1000) * ( 60 * min_per_km1 ); // czas w sekundach na calej trasie
		time2 = (dist/1000) * ( 60 * min_per_km2 );
		
		cout << "Czas pierwszej osoby to:  " << ( t1 = (int)( time1 / 3600 ) ) << " godzin, " << flush;
		cout << ( t2 = (int)( ( time1 - (double)t1*3600 )/60 ) ) << " minut, " << flush;
		cout << ( time1 - t1*3600 - t2*60 ) << " sekund" << endl;
		
		cout << "Czas drugiej osoby to:  " <<( t1 = (int)( time2 / 3600 ) )<< " godzin, " << flush;
		cout << ( t2 = (int)( ( time2 - (double)t1*3600 )/60 ) ) << " minut, " << flush;
		cout << ( time2 - t1*3600 - t2*60 ) << " sekund" << endl;
		
		
		ENDL(5);
		cout << "Press any key" << endl;
		getch();
		system("cls");
	}
	
	
	return 0;
}












