#include<stdio.h>
//#include<iostream>
#include<vector>
#include<time.h>
#include<string>
#include<map>
#include<cmath>
#include<queue>
#include<fstream>
#include<string.h>
#include<sstream>
#include<algorithm>

using namespace std;

#define REP( x,y ) for( int x=0; x<(y); x++ )
#define FORD( x,y,z ) for( int x=y; x>=(z); x-- )
#define FOR(x,b,e) for( int x = b; x <= (e); ++x )
#define SIZE(v) (int)v.size()
#define PB push_back
#define PH push_heap
#define POP pop_back
#define MP make_pair
#define ST first
#define ND second

int N,K,a,b,c,y,d,t,w,l_zest;
const int INF = 1000000001;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;
typedef long long LL;


int main(){
	
	srand( unsigned(time(0)) );
	ofstream strout( "przykladowe_iny.txt" );
	
	N = 10000;
	strout << N << endl;
	REP(i,N){
		a = rand()%400;
		strout << a << " ";
	}
	
	c = N + rand()%N;
	strout << endl << c << endl;
	REP(i,c){
		a = rand()%(N-1) + 1;
		b = rand()%(N-1) + 1;
		if( a > b ) swap(a,b);
		strout << a << " " << b << endl;
	}
	
	
}





