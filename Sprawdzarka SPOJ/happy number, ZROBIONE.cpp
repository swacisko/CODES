#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<cmath>
#include<queue>
#include<string.h>
#include<sstream>
#include<algorithm>

using namespace std;

#define REP( x,y ) for( int x=0; x<y; x++ )
#define FORD( x,y ) for( int x=y; x>=0; x-- )
#define PB push_back
#define PH push_heap
#define POP pop_back
#define MP make_pair
#define ST first
#define ND second

int N,M,a,b,c,x,y;
const int INF = 100000000;
typedef long long LL;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;


bool *was;
string liczba;

int main(){
	int n;
	was = new bool[900];
	REP(i,900) was[i] = false;
	cin >> liczba;
	a = 0;
	n = 0;
	REP( i,liczba.size() ) n+= ( (int) liczba[i] - 48 ) * ( (int) liczba[i] - 48 );
	
	while( was[ n ] == false ){
		was[n] = true;
		liczba = "";
		ostringstream strin( liczba );
		strin << n;
		liczba = strin.str();
		n = 0;
		REP( i,liczba.size() ) n+= ( (int) liczba[i] - 48 ) * ( (int) liczba[i] - 48 );
		a++;
	}
	
	if( n == 1 ) cout << a << endl;
	else cout << -1 << endl;
	
}






