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
const int INF = 100000000;
typedef long long LL;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;


template<class typ>
typ maximum( typ a, typ b ){
	return a > b ? a : b;
}
template<class typ>
typ minimum( typ a, typ b ){
	return a < b ? a : b;
}

VVI wagi;
VVI nodes;
int *dist;

void Dijkstra( int beg ){
	priority_queue< PII > pq;
	pq.push( MP(0,beg) );
	REP(i,N) dist[i] = INF;
//	REP(i,N) printf( "%d  ", dist[i] );
	dist[beg] = 0;
	
	int a,b,c,d;
	while( ! pq.empty() ){
		a = -pq.top().ST;
		b = pq.top().ND;
		
	//	printf( "a = %d  b = %d\n",a,b );
		
		if( dist[b] == a ){
			REP( i,nodes[b].size() ){
			//	printf( "b = %d  nodes[%d][%d] = %d  dist[%d] = %d   dist[%d] = %d  wagi[%d][%d] = %d\n",b,b,i,nodes[b][i],nodes[b][i],dist[nodes[b][i]],b,dist[b],b,i,wagi[b][i] );
				if( dist[ nodes[b][i] ] > dist[b] + wagi[b][i] ){
					dist[ nodes[b][i] ] = dist[b] + wagi[b][i];
					pq.push( MP( -dist[nodes[b][i]], nodes[b][i] ) );
				}
			}			
		}
		
		pq.pop();		
	}	
}


int main(){
	
	int l_zest;
	scanf("%d",&l_zest);
	while(l_zest--){
		
		scanf( "%d %d",&N,&M );
		
		nodes = VVI(N);
		wagi = VVI(N);
		dist = new int[N];
		
		REP( i,M ){
			scanf( "%d %d %d",&a,&b, &c );
			nodes[a-1].PB(b-1);
			wagi[a-1].PB(c);
		}
		
/*		REP( i,N ){
			REP(k,nodes[i].size()){
				printf( "%d %d %d\n",i,nodes[i][k], wagi[i][k] );
			}
		}*/
		
		Dijkstra( 0 );
//		REP(i,N) printf( "dist[%d]=%d  ",i,dist[i] ); printf("\n");
		int suma = 0;
		REP(i,N) suma += dist[i];
		
		delete[]dist;
		dist = new int[N];
		// transponuje graf
		
		VVI nod(N);
		VVI wag(N);
		
		REP( i,N ){
			REP( k,nodes[i].size() ){
				nod[ nodes[i][k] ].PB( i );
				wag[ nodes[i][k] ].PB( wagi[i][k] );
			}
		}
		
		nodes = nod;
		wagi = wag;
		
/*		REP( i,N ){
			REP(k,nodes[i].size()){
				printf( "%d %d %d\n",i,nodes[i][k], wagi[i][k] );
			}
		}*/
		
		
		
		Dijkstra( 0 );
		REP(i,N) suma += dist[i];
	//	REP(i,N) printf( "dist[%d]=%d  ",i,dist[i] ); printf("\n");
		
		printf( "%d\n",suma );
		
		delete[]dist;
	}
	
	
}




















