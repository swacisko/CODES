#include<cstdio>
//#include<iostream>
#include<vector>
#include<string>
#include<map>
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
#define WRITE( V ){ REP(trx,SIZE(V)) cout << V[trx] << " "; cout << endl; }
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

typedef double _T;
typedef vector< _T > VT;
typedef vector< VT > VVT;
typedef pair<_T,_T> PTT;
typedef vector< PTT > VPTT;

int N,K,C;
VI kond;
VVI kondrev;
VVI kondtour;
VVI kondrev2; // to jest przyszly kondrev - w nastepnej chwilo
VI kond2; // to jest przyszly kond - w nastepnej chwili

/*
void writeKond(){
	cout << "Kond" << endl;
	WRITE(kond);
	ENDL(1);
}

void writeKond2(){
	cout << "Kond2" << endl;
	WRITE(kond2);
	ENDL(1);
}

void writeKondrev(){
	cout << "kondrev" << endl;
	WRITE(kondrev);
	ENDL(1);	
}

void writeKondrev2(){
	cout << "kondrev2" << endl;
	WRITE(kondrev2);
	ENDL(1);	
}
*/

bool canMoveLeft( int car, int c ){
	//cout << "Jestem w canMoveLEFT" << endl;
	REP( i, SIZE(kondrev[car-1]) ) if( kondrev[car-1].size() != 0 && kondtour[ kondrev[car-1][i] ][c] == 1 ) return false;
	return true;	
}  

bool canMoveRight( int car, int c ){
	//cout << "Jestem w canMoveRIGHT" << endl;
	REP( i, SIZE(kondrev[car+1]) ) if( kondrev[car+1].size() != 0 && kondtour[ kondrev[car+1][i] ][c] == -1 ) return false;
	return true;
}


void solve(){
	
//	cin >> N >> K >> C;
	scanf( "%d %d %d",&N,&K,&C );

	
	// UWAGA ZAROWNO NUMERY KONDUKTOROW JAK I WAGONOW LICZE OD ZERA!!	
	
	kond = VI(K,0); // kond[i] to numer wagonu w ktorym jest konduktor nr i
	kondrev = VVI(N); // kondrev to nr konduktora, ktory jest w wagonie nr i, lub -1 jesli w tym wagonie nie ma konduktora
	kondtour = VVI( K, VI(C-1) );
	kondrev2 = kondrev;
	kond2 = kond;
	
	int w0;
	char znak;
	string s;
	
	char *tab = new char[C];
	
	REP(i,K){
		scanf( "%d",&w0 );
		//cin >> w0;
		
		kond[i] = w0-1;
		kondrev[w0-1].PB(i);
		
		//scanf( "%c",&znak ); // wczytanie spacji po w0
		
		//cin >> s;
		scanf( "%s",tab );
		s = string(tab);
		
		//printf( "s = %s\n", s.c_str() );
		
		REP(k,C-1){
		//	scanf( "%c",&znak );
			znak = s[k];
			if( znak == '-' ) kondtour[i][k] = -1;
			else if( znak == '+' ) kondtour[i][k] = 1;
			else kondtour[i][k] = 0;
		}	
	}
	
	
	VI freecars;
	REP(i,N){
		if( kondrev[i].size() == 0 ){
			freecars.PB(i);
		}
	}
	
	VI freecars2; // to jest terazniejszy kond - freeecars natomiast to bedzie przyszly kond
	
	bool can = true;
	
	REP( c,C-1 ){
		swap( freecars, freecars2 );
		freecars.clear();
		
	//	cout << "freecars2.size() = " << SIZE(freecars2) << endl;
		
		if( freecars2.empty() ){
			can = false;
			break;
		}
		
		REP( i, SIZE(kondrev2) ) kondrev2[i].clear();
		REP(i,K){
			kondrev2[ kond[i] + kondtour[i][c] ].PB(i);
			kond2[i] = kond[i] + kondtour[i][c];			
		}
		
	
		//writeKond();
		//writeKond2();
		//writeKondrev();
		//writeKondrev2();
		
		
		REP( k, SIZE(freecars2) ){
			int a = freecars2[k];
			//if( k % 1000 == 0 ) cout << "\ta = " << a << endl;
				
			if( kondrev2[a].size() == 0 ) freecars.PB(a);
			
			if( a > 0 ){
				if( kondrev2[a-1].size() == 0 && canMoveLeft( a,c ) ) freecars.PB(a-1);
			}
			if( a < N-1 ){
				if( kondrev2[a+1].size() == 0 && canMoveRight(a,c) ) freecars.PB(a+1);
			}
			
				
		}
		
	//	cout << "Jestem po" << endl;
		
		if( freecars.empty() ){
			can = false;
			break;
		}
		
		sort( ALL(freecars) );
		freecars.resize( unique( ALL(freecars) ) - freecars.begin() );
		
		//cout << "freecars" << endl;
		//WRITE(freecars);
		
		swap( kond,kond2 );
		swap( kondrev, kondrev2 );
	}
	
	
	if( can == true ){
		printf( "TAK\n" );
		//cout << "TAK" << endl;
	}
	else{
		printf( "NIE\n" );
		//cout << "NIE" << endl;
	}
	
	
}




int main(){
	//ios_base::sync_with_stdio(0);
	//cout << fixed;
	//cout.precision(2);

    int l_zest;    
    //cin >> l_zest;
    scanf( "%d",&l_zest );
    
	while( l_zest-- ){
        solve();


	}


	return 0;
}












