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



VI zad1( VI & V, int N, int K ){
	int ind = K;

	while( ind > 0 && V[ind] == N+ind-K ) ind--;
	if( ind == 0 ) return VI(0);
	V[ind]++;
	FOR(i,ind+1,K) V[i] = V[i-1] + 1;
	return V;
	
}



int binom2( int N, int K ){
	LL n=1, k=1;
	FOR(i,1,N) n *= i;
	FOR(i,1,K) k *= i;
	LL nk = 1;
	FOR(i,2,N-K) nk *= i;
	return n/(k*nk);
}


int binom( int N, int K ){
	LL n = 1;
	LL k = 1;
	FOR( i,N-K+1, N ) n*=i;
	FOR( i,1,K ) k*=i;
	return n/k;

}

  
int binom3( int N, int K ){
	LL n = 1;
	LL k = 1;
	int p = N-k+1;
	int q = 1;
	while( p <= N && q <= K ){
		if( p <= N ) n *= p++;
		if( q <= K ) n /= q++;
	}
	return n;
}




int rank( VI & V, int N, int K ){
	int wyn = 0;
	FOR(i,1,K) FOR(j,V[i-1]+1, V[i]-1) wyn += binom( N-j, K-i );
	return wyn;
}



VI unrank( int N, int K, int r ){
	VI V(K+1,0);
	int x = 1;
	FOR(i,1,K){
		while( binom( N-x, K-i ) <= r ){
			r -= binom( N-x, K-i );
			x++;
		}

		V[i] = x;
		x++;
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
				cout << "Podaj teraz k elementow zbioru:\t";
				VI V(K+1);
				V[0] = -1;
				FOR(i,1,K) cin >> V[i];
				sort( ALL(V) );
				V = zad1(V,N,K);
				if( SIZE(V) == 0 ) cout << "brak nastepnika" << endl;
				else FOR(i,1,K) cout << V[i] << " ";
				ENDL(2);

				break;
			}
			
			case 2:{
				cout << "Podaj N:\t";
				cin >> N;
				cout << "Podaj K:\t";
				cin >> K;
				if( K == 0 ){
					cout << "0" << endl;
					break;				
				}
				cout << "Podaj teraz k elementow zbioru:\t";
				VI V(K+1);
				V[0] = 0;
				FOR(i,1,K) cin >> V[i];
				sort( ALL(V) );
				cout << rank( V,N,K ) << endl;
				ENDL(2);
				break;
			}
			
			
			
			case 3:{
				cout << "Podaj wartosc N:\t";
				cin >> N;
				cout << "Podaj wartosc K:\t";
				cin >> K;
				if( K == 0 ){
					cout << "Jedynym podzbiorem jest zbior pusty" << endl;
					break;				
				}
				int r;
				cout << "Podaj range:\t";
				cin >> r;
				VI V = unrank( N,K,r );
				FOR(i,1,K) cout << V[i] << " ";
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












