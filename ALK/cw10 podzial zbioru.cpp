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
#include<iomanip>

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



int N[100]; // nastepny podzbior
int P[100]; // poprzedni podzbior
int B[100]; // ID podzbioru zawierajacego j
int PR[100]; // kierunek ruchu - 1 - w prawo ,   0 - w lewo

void pisz( int );

int ILE;
void generate( int aN ){
	FOR(i,1,aN) PR[i] = B[i] = 1;
	FOR( i,1,aN ) N[i] = P[i] = 0;
	N[1] = 0;
	
	
	pisz(aN);
	
	int j = 0;
	while( j != 1 ){
		j = aN;
		while( j != 1 ){
			if( PR[j] == 1 ){ // jesli element chce isc w prawo...
				if( B[j] != j ){ // jesli j nie jest najmniejsze w swoim bloku, to moze isc dalej				
					if( N[ B[j] ] == 0 ){ // jesli j jest w ostatnim istniejacym bloku, to tworze nowy i wrzucam tam j...
		//				cout << "j = " << j << "  chce isc w prawo, nie jestem najmniejszy w bloku, jestem w ostatnim isteniajcym bloku" << endl;
						P[j] = B[j];
						N[ B[j] ] = j;
						N[j] = 0;
						B[j] = j;
						break;				
					}
					else if( j > N[ B[j] ] ){ // w przeciwnym razie, jesli j jest wieksze od numeru nastepnego bloku to dodaje go do najblizszego bloku z prawej
		//				cout << "j = " << j << "  chce isc w prawo, nie jestem najmniejszy w bloku, jestem wiekszy od numeru nastepnego bloku ,B[j] = " << B[j] << "  N[B[j]]] = " << N[B[j]] << endl;
						B[j] = N[ B[j] ]; // tutaj nie zmieniam zadnych 'wskaznikow' bo one sa gotowe, tylko przynaleznosc elementu do zbioru	
						break;		
					}	
					else{ // tutaj trafilismy, jesli j jest mniejsze od numeru nastepego bloku, teraz tez trzeba stworzyc nowy blok...
		//				cout << "j = " << j << "  chce isc w prawo, nie jestem najmniejszy w bloku, jestem mniejszy od numeru nastepnego bloku" << endl;
						N[j] = N[ B[j] ];
						P[j] = B[j];
						P[ N[ B[j] ] ] = j;
						N[ B[j] ] = j;						
						B[j] = j;
						break;
					}				
				}
				else{ // jesli j jest najmniejsze w swoim nbloku to nie moze isc dalej...
		//			cout << "j = " << j << "  chce isc w prawo, JESTEM najmniejszy w bloku, zmieniam kierunek" << endl;					
					PR[j] = 1 - PR[j];
					j--;
				}				
			}
			else{ // jesli j chce isc w lewo...
				if( B[j] == 1 ){ // jesli jestem w pierwszym bloku to nie moge isc w lewo
		//			cout << "j = " << j << "  chce isc w lewo, ale JESTEM w pierwszym bloku, zmieniam kierunek" << endl;
					PR[j] = 1 - PR[j];
					j--;
				}
				else{ // jesli nie jestem w pierwszym bloku, to zawsze dolaczam do bloku po lewej...
		//			cout << "j = " << j << "   chce isc w lewo" << flush;
				/*	if( N[ B[j] ] == 0 ){ // jesli jestem w ostatnim bloku, to trzeba go usunac...
						cout << "   jestem w ostatnim bloku, wiec musze go usunac" << flush;
						N[ P[ B[j] ] ] = 0;						
					}
					else*/ if( B[j] == j ){
						P[ N[ B[j] ] ] = P[ B[j] ]; 
						N[ P[ B[j] ] ] = N[ B[j] ];			
					}
					
					B[j] = P[ B[j] ];
		//			cout << endl;
				
					
									
					break;
				}
			}
		//	ENDL(1);
			
		} // koniec while'a
		
		
		
		if( j != 1 ) pisz(aN);
	}
	
	
}

void pisz( int N ){
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




int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);
	
	while( true ){
		cout << "Podaj N:\t";
		int N;
		cin >> N;
		
		generate(N);
		
		
		
	}
	
	
	
	
	
	return 0;
}












