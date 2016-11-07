#include<stdio.h>
//#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<queue>
#include<string.h>
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

VVI V;
map< string,int> miasta;
//map< PII,int> wagi;
VVI wagi;
string s,s1,s2;
VI v;



void Dijkstra( int beg, VI &v ){
	v = VI(N,infinity);
	priority_queue< PII > pq;
	pq.push( MP(0,beg) );
	
	v[beg] = 0;	
	
	int ind,dist,t;
	while( !pq.empty() ){
	//	PII p = pq.top();
	//	dist = -p.ST;
		dist = -pq.top().ST;
		ind = pq.top().ND;
		
		if( dist == v[ind] ){			
			if( ind == y ) break;
			
			REP( i,V[ind].size() ){
				if( dist + ( t = wagi[ind][i] ) < v[V[ind][i]] ){
					v[ V[ind][i] ] = dist + t;
					pq.push( MP( -dist-t, V[ind][i] ) );	
				}
			}
		}
		
		pq.pop();	
	}
}

char ch1[11],ch2[11];

int main(){
	//ios_base::sync_with_stdio(1);
	int l_zest;
	scanf( "%d",&l_zest );
	//cin >> l_zest;
	while(l_zest--){
	//	scanf( "%d",&N );
		//cin >> N;
		scanf( "%d",&N );
		V = VVI(N);
		miasta.clear();
		wagi = VVI(N);
		
		REP(i,N){
		//	cin >> s;
		scanf("%s",&ch1);
			miasta[ string(ch1) ] = i;
			
			scanf( "%d",&x );
			REP(k,x){
			//	cin >> y >> c;
				scanf( "%d %d",&y,&c );
				V[i].PB(y-1);
				wagi[i].PB(c);
			}			
		}
		
		int r;
	//	cin >> r;
		scanf( "%d",&r );
		REP(i,r){
		//	cin >> s1 >> s2;
			scanf( "%s %s",&ch1,&ch2 );
			
		
			x = miasta[ string(ch1) ];
			y = miasta[ string(ch2) ];
			
			Dijkstra( x, v );
			
		//	cout << v[y] << endl;
			printf( "%d\n",v[y] );
		}
		
		
	}
	
	
	
	
}









