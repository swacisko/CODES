//#include<stdio.h>
#include<iostream>
#include<vector>
//#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
//#include<set>
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


//********************************************************************** zad1

void wypisz( VB & V, int N, int k ){
	int ile = 0;
	FOR(i,1,SIZE(V)-1){
		if( V[i] ) ile++;
	}
	if( ile != k ) return;
	FORD(i,SIZE(V)-1,0) if( V[i] ) cout << N-i+1 << " ";
	ENDL(1);
}

void zad1help( int N, int k ){	
	VB v(N+1,false);
		
	int ind = N;
	while( ind > 0 ){
		wypisz(v,N,k);
		
		ind = N;		
		while( ind > 0 && v[ind] == true ) v[ind--] = false;
		if( ind > 0 ) v[ind] = !v[ind];	
	}	
}


void zad1( int N ){
	FOR(k,1,N) zad1help( N,k ); 
}


//**********************************************************************  zad2

void zad2help( VI& ans, int N, int K ){
	if( SIZE(ans)==K ){
		WRITE(ans);
		ENDL(1);
		return;
	}
	
	FOR(i,1,N){
		ans.PB(i);
		zad2help( ans,N,K );
		ans.pop_back();
	}
	
}

void zad2( int N, int K ){
	VI ans;
	ans.clear();
	zad2help(ans,N,K);
}


//********************************************************************** zad3


int zad3( int N, VI & T ){
	int r = 0;	
	REP( i,SIZE(T) ) r += ( 1 << ( N-T[i] ) );	
	return r;
}

//**********************************************************************  zad 4


VI zad4( int N, int r ){
	VI ans;
	int t = 0;
	while( r > 0 ){
		if( r%2 ){
			ans.PB( N-t );
		}
		
		t++;
		r >>= 1;
	}
	reverse(ALL(ans));
	return ans;
	
}




//**********************************************************************




//**********************************************************************






int main(){
	ios_base::sync_with_stdio(0);
//	cout << fixed;
//	cout.precision(2);
	
	int N,K;
	
	while( true ){
		cout << "Podaj nr zadania:\t";
		int nr;
		cin >> nr;
		switch(nr){

			case 1:{
				cout << "Podaj wartosc N dla zadania 1:\t";
				cin >> N;
				zad1(N);
				ENDL(3);
				break;
			}
			
			case 2:{
				cout << "Podaj wartosci N oraz K dla zadania 2:\t";
				cin >> N >> K;
				zad2(N,K);
				ENDL(3);
				break;
			}
			
			
			
			case 3:{
				cout << "Podaj wartosc N zadania 3:\t";
				cin >> N;
				cout << "Podaj wartosc K - dlugosc podciagu, ktorego nr chcesz znalezc:\t";
				cin >> K;
				cout << "Podaj teraz te wartosci:\t";
				VI T(K);
				REP(i,K){
					cin >> T[i];
				}
				sort( ALL(T) );
				cout << zad3( N,T ) << endl;
				ENDL(3);
				break;
			}
			
			
			case 4:{
				cout << "Podaj N dla zadania 4:\t";
				cin >> N;
				cout << "Podaj r dla zadania 4:\t";
				int r;
				cin >> r;
				VI ans = zad4(N,r);
				WRITE(ans);
				ENDL(3);
				break;
			}
			default:{
				system("cls");
			}
		}
	}
	
	/*
	while(1){
		cout << "Podaj wartosc N dla zadania 1:\t";
		cin >> N;
		zad1(N);
		ENDL(3);
	}
	
	while(2){
		cout << "Podaj wartosci N oraz K dla zadania 2:\t";
		cin >> N >> K;
		zad2(N,K);
		ENDL(3);
	}
	
	
	
	while(3){
		cout << "Podaj wartosc N zadania 3:\t";
		cin >> N;
		cout << "Podaj wartosc K - dlugosc podciagu, ktorego nr chcesz znalezc:\t";
		cin >> K;
		cout << "Podaj teraz te wartosci:\t";
		VI T(K);
		REP(i,K){
			cin >> T[i];
		}
		sort( ALL(T) );
		cout << zad3( N,T ) << endl;
		ENDL(3);
	}
	
	
	while(4){
		cout << "Podaj N dla zadania 4:\t";
		cin >> N;
		cout << "Podaj r dla zadania 4:\t";
		int r;
		cin >> r;
		VI ans = zad4(N,r);
		WRITE(ans);
		ENDL(3);
	}*/
	
	
	
	return 0;
}












