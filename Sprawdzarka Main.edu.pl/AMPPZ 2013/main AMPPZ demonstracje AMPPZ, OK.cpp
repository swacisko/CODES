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

int N,M,K,a,b,c,y,t,w,l_zest;
const int INF = 1000000001;
const double EPS = 10e-9;
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











int main(){
	
	cin >> N;
	VPII V(N);
	REP(i,N) cin >> V[i].ST >> V[i].ND;
	vector< pair<int,PII> > v;
	REP(i,N){
		v.PB( MP( V[i].ST, MP(0,i) ) );
		v.PB( MP( V[i].ND, MP(1,i) ) );
	}
	sort( ALL(v) );
	map<PII,int> dem;    dem.clear();   map<PII,int>::iterator itr; // dem.ST  to para oznaczjaca numery demonstracji, ktore wystepuja razem tylko we dwie, natomiast dem.ND to 
																	//dlugosc jakie one lacznie pokrywaja
	int prev = v[0].ST;
	int t = 0, k = t;
	map<int, bool> act;   act.clear();
	a = b = -1;
	VI solo(N,0);
	
	while( t < SIZE(v) ){
		//	cout << "\tSIZE(act) = " << SIZE(act) << "   act:    "; FOREACH(it,act) cout << it->ST << " ";
		//	cout << endl;
		a = b = -1;
		if( SIZE(act) <= 2 ){			
			if( SIZE(act) == 1 ){
				FOREACH(it,act) a = it->ST;
				solo[a] += v[t].ST - prev;
			}
			else if( SIZE(act) == 2 ){
				FOREACH(it,act) if( a == -1 ) a = it->ST;
								else b = it->ST;
				if( a > b ) swap(a,b);
				if( ( itr = dem.find( MP(a,b) ) ) == dem.end() ) dem.insert( MP( MP(a,b), v[t].ST - prev ) );
				else itr->ND += v[t].ST - prev;
			}			
		}
		k = t;
		
		while( k < SIZE(v) && v[k].ST == v[t].ST ){
			if( v[k].ND.ST == 0 ) act.insert( MP( v[k].ND.ND,1 ) );
			else act.erase( v[k].ND.ND );
			k++;
		}
		prev = v[t].ST;
		(k>t) ? t = k : t++;		
	}
	
	int MAX = 0;
	FOREACH(it,dem) MAX = max( MAX, it->ND + solo[ it->ST.ST ] + solo[ it->ST.ND ] );
	
	a = b = 0;
	REP(i,N) if( solo[i] >= a ){ b = a; a = solo[i];}
			else if( solo[i] > b ) b = solo[i];
		
	MAX = max( MAX,a+b );
	
	cout << MAX << endl;
	
/*	cout << endl << "solo:"<<endl;
	FOREACH( it,solo ) cout << *it << " ";
	cout << endl;
	
	cout << "dem:" << endl;
	FOREACH(it,dem) cout << it->ST.ST << " " << it->ST.ND << "    " << it->ND << endl;*/
	
	return 0;
	
}













