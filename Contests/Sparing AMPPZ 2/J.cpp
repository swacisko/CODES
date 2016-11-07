//#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
#include<bitset>
#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
#include<time.h>
//#include<string.h>
//#include<fstream>
//#include<sstream>
#include<algorithm>
//#include<conio.h>

using namespace std;

#define REP( x,y ) for( int x=0; x<(y); ++x )
#define FORD( x,y,z ) for( int x=y; x>=(z); --x )
#define FOR(x,b,e) for( int x = b; x <= (e); ++x )
#define SIZE(v) (int)v.size()
#define ALL(c) c.begin(),c.end()
#define VAR(v,n) __typeof(n) v=(n)
#define FOREACH(i,c) for( VAR(i,c.begin());i!=c.end();++i )
#define PB push_back
#define MP make_pair
#define ST first
#define ND second
#define WRITE( V ){ REP(trx,SIZE(V)) printf( "%d ",V[trx] ); printf("\n"); }
#define WRITE_ALL(V) {  REP( i,SIZE(V) ){ cout  << i << " ---- ";  FOREACH(it,V[i]) cout << *it << ", "; cout << endl;     } }
#define WRP(p) p.ST << " " << p.ND
#define CLEAR( dst,quant ) memset( dst,0, (quant)*sizeof( __typeof(*dst) ) );
#define WAR if( show_help )
#define ENDL(x) REP(crow,(x)) cout << endl;

const bool show_help = 1;
const int INF = 1000000001;
//int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef vector< VD > VVD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef vector< VB > VVB;
typedef long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;


char tab[20];
int N;
string s;
//VPII buy, sell;

//VI buy,sell;

/*
void updateTable( VPII table ){
	int p = SIZE(table)-1;
	
	int q;
	while( p >= 0 ){
		q = p-1;
		while( q >= 0 && table[q].ST == table[p].ST ){
			table[q].ND += table[q+1].ND;
			table.erase( table.begin() + p );
			p = q;
			q--;
		}
		
		if( q >= 0 &&  )
		
		
	}
	
}*/

int buy[1001], sell[1001];

void solve(){
	
	scanf( "%d",&N );
	
	
	int how_many;
	int price;
	
	
	REP(i,1001) buy[i] = sell[i] = 0;
	
	//buy = VI(1001,0);
	//sell = VI(1001,0);
	
	int bid,ask, deal,d;
	
	string s2,s3;
	
	REP(i,N){
		//scanf( "%s",tab );
		cin >> s;
		//s = string(tab);
		//scanf( "%d %s %s %d", &how_many,tab,tab,&price );
		cin >> how_many >> s2 >> s3 >> price;
			
		
		if( s == "buy" || s == "Buy" ){
			//buy.PB( MP( price, how_many ) );			
			//updateTable(buy);
			buy[ price ] += how_many;			
		}
		else{
			//sell.PB( MP( price,how_many ) );
			//updateTable(sell);	
			sell[price] += how_many;					
		}
		
		bid = 1000;
		ask = 1;
		deal = 0;
		d = 0;
		
		while( ask <= bid ){
			while( ask <= 1000 ){
				if( sell[ask] > 0 ) break;
				ask++;
			}
			
			while( bid >= 1 ){
				if( buy[bid] > 0 ) break;
				bid--;
			}
			
		//	printf( "ask = %d    bid = %d\n",ask,bid );
			
			
			if( ask <= bid ){
				d = min( buy[bid], sell[ask] );
				deal = ask;
				buy[bid] -= d;
				sell[ask] -= d;
			}			
		} 
		
		if( ask <= 1000 ){
			printf( "%d ", ask );			
		}
		else{
			printf( "- " );
		}
		
		if( bid >= 1 ){
			printf( "%d ", bid );
		}
		else printf( "- " );
		
		if( deal > 0 ){
			printf( "%d\n",deal );
		}
		else printf( "-\n" );
		
	}
	
	
	
	//printf( "\n" );
	
	

}

int main(){
	int l_zest;
	scanf( "%d",&l_zest );  

    while( l_zest-- ){
		
		solve();
		
	}

	return 0;
}












