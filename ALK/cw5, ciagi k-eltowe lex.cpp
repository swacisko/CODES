//#include<stdio.h>
#include<iostream>
#include<vector>
//#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
//#include<time.h>
//#include<string.h>
//#include<fstream>
//#include<sstream>
#include<algorithm>
//#include<conio.h>

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
//int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef vector< VD > VVD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;



VI nastepnik( VI V, int N, int K ){
	int ind = K;
	V.insert( V.begin(),N+1 );
	
	while( ind > 0 && V[ind-1] - V[ind] == 1 ) ind--;
	V.erase( V.begin() );
	
	if( ind == 0 ) return V;
	V[ind-1]++;
	FOR(i,ind,K-1) V[i] = K-i;
	return V;
}


  
int binom( int N, int K ){
	if( N < K ) return 0;	
	LL n = 1;
	LL k = 1;
	int p = N;
	int q = 1;
	while( p >= N-K+1 && q <= K ){
		if( p <= N ) n *= p--;
		if( q <= K ) n /= q++;
	}
	return n;
}




int rank( int N, int K, VI & V ){
	int r = 0;
	FOR( i,1,K ) r += binom( V[i-1]-1, K-i+1 );
	return r;
}



VI unrank( int N, int K, int r ){
	VI V(K);
	int t = 0;
	int K2 = K;
	FOR(i,0,K2-1){
		t = K;
		while( binom(t,K) <= r ) t++;
		r -= binom(t-1,K);
		K--;
		V[i] = t;
		//cout << "t = " << t << "  K = " << K << "   r = " << r << endl;
	}
	return V;

}







int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);
	
	
	int N,K;
	
	while( true ){
		cout << "Podaj nr zadania:\t";
		int nr;
		cin >> nr;
		switch(nr){

			case 1:{
				cout << "Podaj N:\t";
				cin >> N;
				
				cout << "Podaj K:\t";
				cin >> K;
				VI V(K);
				if( K == 0 ){
					cout << "Nie ma nastepnika zbioru pustego" << endl;
					break;
				}
				
				cout << "Podaj te elementy:\t";
				FOR(i,0,K-1) cin >> V[i];
		
				sort( V.rbegin(), V.rend() );
				VI G = nastepnik( V, N, K );
				
				if( equal( ALL(V), G.begin() ) ) cout << "Nie ma nastepnika" << endl;
				else WRITE(G);
	
				ENDL(2);

				break;
			}
			
			case 2:{
				cout << "Podaj N:\t";
				cin >> N;
				
				cout << "Podaj K:\t";
				cin >> K;
				VI V(K);
				if( K == 0 ){
					cout << "ranga zbioru pustego to 0" << endl;
					break;
				}
				
				cout << "Podaj te elementy:\t";
				FOR(i,0,K-1) cin >> V[i];

				sort( V.rbegin(), V.rend() );
				int r = rank( N,K,V );
				cout << "ranga = " << r << endl;



				break;
			}
			
			
			
			case 3:{
				cout << "Podaj N:\t";
				cin >> N;
				
				cout << "Podaj K:\t";
				cin >> K;
				VI V(K);
				if( K == 0 ){
					cout << "???" << endl;
					break;
				}

				cout << "Podaj range:\t";
				int r;
				cin >> r;
				
				VI G = unrank( N,K,r );
				WRITE(G);
				ENDL(2);

				break;
			}
			
			default:{
				system("clear");
			}
			
		}
	}
	
	
	
	
	
	
	
	return 0;
}












