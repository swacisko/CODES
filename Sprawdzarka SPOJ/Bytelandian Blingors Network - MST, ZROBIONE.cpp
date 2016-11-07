#include<stdio.h>
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

int N,M,K,a,b,c,y,t,w,l_zest;
const int INF = 1000000001;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;
typedef long long LL;

template<class typ> inline typ maximum( typ a, typ b ){ return a > b ? a : b; }
template<class typ> inline typ minimum( typ a, typ b ){ return a < b ? a : b; }


struct FAU{
	int *p,*w;
	FAU( int n ) : p(new int[n]), w(new int[n]) {
		REP(x,n) p[x] = w[x] = -1;
	}
	~FAU(){
		delete[] p;
		delete[] w;
	}
	
	int Find( int x ){
		return ( p[x]<0 ) ? x : p[x] = Find( p[x] );
	}
	
	void Union( int x, int y ){
		if( (x = Find(x)) == (y = Find(y)) ) return;
		if( w[x] > w[y] ) p[y] = x;
		else p[x] = y;
		if( w[x] == w[y] ) w[y]++;
	}
	
};

char name[20];

vector< pair<int,PII> > V;

int main(){
	
	scanf("%d",&l_zest);
	while(l_zest--){
		scanf("%d",&N);
		
		V.clear();
		FAU fau(N);
		
		REP( i,N ){
			scanf("%s",name);
			scanf("%d",&a);
			REP(k,a){
				scanf("%d %d",&b,&c);
				V.PB( MP( c, MP( i,b-1 ) ) );
			}
		}
		
		sort( V.begin(), V.end() );
		
		int cost = 0;
		REP( i,V.size() ){
			if( fau.Find( V[i].ND.ST ) != fau.Find( V[i].ND.ND ) ){
			//	printf( "a = %d  b = %d\n", V[i].ND.ST, V[i].ND.ND );
				cost += V[i].ST;
				fau.Union( V[i].ND.ST, V[i].ND.ND );
			}			
		}
		
		printf( "%d\n",cost );
		
		
	}
	
}

















