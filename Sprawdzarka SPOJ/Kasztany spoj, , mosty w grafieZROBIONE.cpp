#include<stdio.h>
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
const int infinity = 100000000;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;
typedef vector<PII> VPII;

template<class typ>
typ maximum( typ a, typ b ){
	return a > b ? a : b;
}
template<class typ>
typ minimum( typ a, typ b ){
	return a < b ? a : b;
}

int *preOrder;
int *low;
VPII answer;
VVI V;
int sons;

void DFS( int my, int par, int &num ){
	preOrder[my] = num++;
	low[my] = preOrder[my];	
	
	REP( i,V[my].size() ){
		if( preOrder[ V[my][i] ] == 0 ){
			DFS( V[my][i],my,num );
			low[my] = minimum( low[my], low[ V[my][i]] );
			
			if( low[ V[my][i] ] == preOrder[ V[my][i] ] ){
				int a = my,b = V[my][i];
				if( a > b ) swap(a,b);
				answer.PB( MP(a+1,b+1) );
			}			
		}
		else if( V[my][i] != par ){
			low[ my ] = minimum( low[my], preOrder[ V[my][i] ] );
		}
	}	
	
//	printf( "Wracam z wierzcholka %d  preOrder = %d   low = %d\n",my,preOrder[my],low[my] );
}

void getBridges(){
	preOrder = new int[N];
	memset( preOrder,0,N*sizeof(int) );
	low = new int[N];
	memset( low,0,N*sizeof(int) );
	sons = 0;
	int num=1;
	
	REP( i,N ){
		if( preOrder[i] == 0 ) DFS( i,i,num );
	}
	
	
}

int main(){
	
	scanf( "%d %d",&N,&M );
	
	V = VVI(N);
	REP( i,M ){
		scanf( "%d %d",&x,&y );
		V[x-1].PB(y-1);
		V[y-1].PB(x-1);		
	}
	
	getBridges();
	sort( answer.begin(), answer.end() );
	
//	REP( i,N ){
//		printf( "i= %d   low[i] = %d   preOrder[i] = %d\n",i,low[i],preOrder[i] );
//	}
	
	REP(i,answer.size()){
		printf( "%d %d\n",answer[i].ST, answer[i].ND );
	}
	
	
	
}




