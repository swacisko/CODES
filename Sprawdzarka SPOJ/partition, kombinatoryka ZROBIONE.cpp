#include<cstdio>
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
#define REPt( x,y,z ) for( int x=y; x<z; x++ )
#define FORD( x,y ) for( int x=y; x>=0; x-- )
#define PB push_back
#define PH push_heap
#define POP pop_back
#define MP make_pair
#define ST first
#define ND second

long long N,M,a,b,c,x,y;
const long long infinity = 100000000;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<long long> VI;
typedef vector< VI > VVI;
typedef pair<long long,long long> PII;
typedef map< PII, bool > MPIIB;


int main(){
	long long **tab;
	VI V;
	long long l_zest;
	scanf("%lld",&l_zest);
	while(l_zest--){
		
		scanf("%lld %lld %lld",&M,&N,&c);
		
		V.clear();
		tab = new long long*[N+1];
		REP(i,N+1) tab[i] = new long long[M+1];
		
		REPt(i,1,M+1) tab[1][i] = 1;
		
		REPt(i,2,N+1){
			REPt( k,1,M+1 ) tab[i][k] = 0;
		//	if( i <= M ) tab[i][i] = 1;
			
			REPt( t,1,M+1 ){
				for( long long j=1; t - j - (j-1)*(i-1) > 0; j++ ){
					tab[i][t] += tab[i-1][t-j-(j-1)*(i-1)];
				}
			}
		}
		
	//	REP(i,N) printf( "tab[%lld][M] = %lld\n",i, tab[i][M] );
		
//		REPt(i,1,N+1) REPt(k,1,M+1)printf( "i = %d    k = %d    %d\n", i,k,tab[i][k] );
	//	printf("\n");
		
		long long t = c;
		long long q,w,e,r,j;
		j = 1;
		a = N;
		r = M-1;
		bool xtr = false;
		
		while( a > 1 ){
			if( r <= 0 ){
			//	printf("JAKAS SCIEMA, NIE POWINNO BYC r < 0   r = %d !!!\n",r); 
				V.PB(j);
				break;				
			}
			if( tab[a-1][r] >= t ){
			//	printf( "a = %d  r = %d  t = %d  j = %d  tab[%d][%d] = %d\n",a,r,t,j,a-1,r,tab[a-1][r] );
			//	printf( "Wstawiam element %d\n\n",j );
				
				V.PB(j);
				a--;
			//	r -= j;
				r--;
			}
			else{
			//	printf( "a = %d  r = %d  t = %d  j = %d  tab[%d][%d] = %d\n",a,r,t,j,a-1,r,tab[a-1][r] );
				t -= tab[a-1][r];
				j++;
				r-=a;				
			}			
		}
		
	//	V.PB(r);
		
	//	REP( i,V.size() ) printf( "%d ",V[i] ); 
	//	printf("\n");
	//	REP(i,V.size()-1) V[i+1] += V[i]-1;
		
	//	V[ V.size()-1 ] = M;
		V.PB(M);
		REP( i,V.size()-1 ) V[ V.size()-1 ] -= V[i];
		
	//	sort( V.begin(), V.end() );
		REP( i,V.size() ) printf( "%lld ",V[i] );
		printf("\n");
		
		
		REP(i,N+1) delete[]tab[i];
		delete[]tab;
	}
	
	
	
	
}
















