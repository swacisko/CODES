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

// funckja dla zadanego podzialu zbioru tworzy funkcje RGF
VI create_RGF( VVI G ){
	VI RGF(SIZE(G),INF);
	FOR( i,1,SIZE(G)-1 ) FOR(k,1,SIZE(G[i])-1) RGF[ G[i][k] ] = i;
	int ile = RGF[1]-1;
	RGF[1] = 1;
	FOR( i,2,SIZE(RGF)-1 ) RGF[i] -= ile;
	return RGF;		
}

bool funcomp( const VI & v1, const VI & v2 ){
	return v1[1] < v2[1];
}

void pisz( int N, VI B ){
	VI ktore;
	FOR( i,1,N ){
		ktore.clear();
		FOR( k,1,N ) if( B[k] == i ) ktore.PB( k );
		
		if( !ktore.empty() ){ // jesli istnieje element nalezacy do bloku nr i, to wypisuje ten blok
			cout << "{";
			REP( t, SIZE(ktore) ){
				cout << ktore[t];
				if( t != SIZE(ktore)-1 ) cout << ",";
			}
			cout << "}" << "  " << flush;
		}
		
	}
	
	cout << endl;	
}

// funkcja dla zadanego podzialu RGF tworzy podzial zbioru
void create_Partition( VI RGF ){
	pisz( SIZE(RGF), RGF );	
}



void generate( int N ){
	VI F(N+1,2);
	VI f(N+1,1);
	
	int ILE = 0;
	int j;
	while( 1 ){
		ILE++;
		cout << "{";
		FOR(i,1,N) cout << f[i] << " ";
		cout << "}" << endl;
		
		j = N;
		while( f[j] == F[j] ) j--;
		if( j == 1 ) break;
		
		f[j]++;
		FOR(i,j+1,N) {				
			f[i] = 1;
			if( f[j] == F[j] ) F[i] = F[j]+1;
			else F[i] = F[j];
		}
	}
	
	cout << "LACZNIE " << ILE << " elementow" << endl;
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
				cout << "Poadaj rozmiar(N):\t";
				int N;
				cin >> N;
				if( N <= 0 ){
					cout << "NIE WIEKSZE NIZ ZERO?? CHYBA ZART..." << endl;
					break;
				}
				
				cout << "Podaj podzial:" << endl;
				
				
				VVI G(N+1);;
				FOR( i,1,N ){
					cout << "Ile elementow w " << i << "-tym podziale? " << flush;
					int t;
					cin >> t;
					if( t > 0 ) cout << "\tPodaj te elementy:\t";
					VI V(t+1,INF);
					FOR(k,1,t) cin >> V[k];
					G[i] = V;					
					
				}
				
				FOR( i,1,N ) sort( G[i].begin()+1, G[i].end() );
				sort( G.begin()+1, G.end(), funcomp );
				
			/*	FOR(i,1,N){
					FOR(k,1,SIZE(G[i])-1) cout << G[i][k] << " ";
					cout << endl;
					
				}*/
				
				
								
				VI RGF = create_RGF(G);
				cout << "RGF: ";
				FOR(i,1,N) cout << RGF[i] << " ";
				ENDL(2);
				
				
				break;
			}
			
			case 2:{
				cout << "Podaj N:\t" << endl;
				int N;
				cin >> N;
				cout << "Podaj teraz RGF:\t";
				VI RGF(N+1);
				FOR(i,1,N) cin >> RGF[i];
				create_Partition(RGF);
				ENDL(2);				
				
				break;
			}
			
			
			
			case 3:{
				
				cout << "Podaj N:\t";
				int N;
				cin >> N;
				generate(N);
				
				break;
			}
			
			default:{
				system("cls");
			}
			
		}
	}
	
	
	
	
	
	
	
	return 0;
}












