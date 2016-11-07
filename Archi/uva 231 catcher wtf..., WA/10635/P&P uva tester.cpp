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
#include<time.h>
//#include<string.h>
//#include<fstream>
//#include<sstream>
#include<algorithm>

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
int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;


// longest common subsequence w czasie O( N^2 )
namespace LCS{
	
	// funkcja zwracajaca jako wektor najdluzszy wspolny podciag dwoch wektorow przeslanych jako parametr
	// dziala w czasie kwadratowym
	VI lcs( VI & tab1, VI & tab2 ){
		int p = SIZE(tab1);
		int q = SIZE(tab2);
		tab1.insert( tab1.begin(),0 );
		tab2.insert( tab2.begin(),0 );
		int** tab = new int*[p+1];
		REP(i,p+1) tab[i] = new int[q+1];
		
		REP(i,p+1) tab[i][0] = 0;
		REP(i,q+1) tab[0][i] = 0;
		
		vector<VPII> help( p+1, VPII(q+1) );
		int ind = 0;
		
	//	cout << "jeszcze przed p = " << p << "  q = " << q << "  SZIE(tab1) = " << SIZE(tab1) << "   SZIE(tab2) = " << SIZE(tab2) << endl;
		
		FOR(i,1,p){
			FOR(j,1,q){
				if( tab1[i] == tab2[j] ){
					help[i][j] = MP( i-1,j-1 );
					tab[i][j] = tab[i-1][j-1] + 1;
				} 
				else{
					if( tab[i-1][j] > tab[i][j-1] )	help[i][j] = MP( i-1,j );
					else help[i][j] = MP( i,j-1 );
					
					tab[i][j] = max( tab[i-1][j], tab[i][j-1] );
				}
			}
		}
		
	//	cout << "Juz wiem tab[p][q] = tab["<< p <<"]["<< q <<"] = " << tab[p][q] << endl;
		
		VI ans( tab[p][q] );
		int ind2 = SIZE(ans)-1;
		while( p != 0 && q != 0 ){
			if( help[p][q] == MP( p-1,q-1 ) ){
				ans[ind2--] = tab1[p];
				p--;
				q--;
			}
			else if( help[p][q].ST == p-1 ) p--;
			else q--;
		}
			
		REP(i,p+1) delete[] tab[i];
		delete[] tab;
		
		return ans;
	}
	
	
	// funkcja zwraca najdluzszy wspolny podciag dwoch permutacji liczb od 0 do N-1    przeslanych jako parametr
	// dziala w czasie liniowym
	// to mozna stosowac nawet dla niepelnych permutacji, dla pewnych dwoch podciagow tej samej permutacji
	void lcsPerm( int N, VI & perm1, VI & perm2, VI & ans ){
		int p1 = SIZE(perm1), p2 = SIZE(perm2);
		
		int* renum1 = new int[N]; // renum[i] to index elementu i w permutacji perm1 lub INF jesli taki element nie istnieje
		fill( renum1, renum1+N-1, INF );
		REP( i, p1 ) renum1[ perm1[i] ] = i;
		
		cout << "renum1:  "; REP( i,N ) cout << renum1[i] << " "; ENDL(2);
		
		int* perm2cp = new int[ p2 ]; // to jest permutacja perm2 po przenumerowaniu tak, aby byla zgodna z perm1 po przenumerowaniu
		REP( i,p2 ) perm2cp[i] = renum1[ perm2[i] ];
		
		cout << "perm2cp:  "; REP(i,p2) cout << perm2cp[i] << " "; ENDL(2);
				
		int* left = new int[ p2 ]; // left[i] to najwiejszy taki index j < i, ze perm2cp[j] < perm2cp[i]
		fill( left, left+p2,INF );
		int t = 0;
		FOR(i,1, p2-1 ){
			t = i-1;
			while( t != INF && perm2cp[t] > perm2cp[i] ) t = left[t];
			left[i] = t;
		}
		REP( i,p2 ) if( perm2cp[i] == INF ) left[i] = INF;
		
		cout << "left:  "; REP(i,p2) cout << left[i] << " "; ENDL(2);	
		
		int* dyn = new int[ p2 ]; // to jest tablica dla dynamika
		fill( dyn, dyn+p2-1,1 );
		cout << "LALA" << endl;
		REP(i, p2 ) if( left[i] != INF ) dyn[i] = dyn[ left[i] ] + 1;
		
		cout << "dyn:  "; REP(i,p2) cout << dyn[i] << " "; ENDL(2);
		
		int ind = max_element( dyn, dyn+p2 ) - dyn; // ind to jest index maksymalnego elementu w tablicy dyn
				
		ans.clear();
		ans.resize( ind );
		t = ind-1;
		do{
			if( t > 0 )ans[t--] = ind;
			cout << "ind = " << ind << " left[ind] = " << left[ind] << endl;
			ind = left[ind];
		} while( ind != INF );
		
		cout << "za  SIZE(ans) = " << SIZE(ans) << endl;
		
		if( SIZE(ans) > 1 ) reverse( ALL(ans) ); // musze odwrocic kolejnosc bo dodawalem od tylca
		
		int *ansint = new int[ SIZE(ans)+1 ];
		copy( ALL(ans), ansint );
		
		cout << "wychodze z funkcji" << endl; 
	}
	
	
	

}


using namespace LCS;

int main(){
	ios_base::sync_with_stdio(0);
	srand( unsigned(time(0)) );
	
	int PR,p,q;
	cin >> PR;
	l_zest = 0;
	while( l_zest++ < PR ){
	//	cin >> N >> p >> q;
		N = rand()%2 + 2;
		N*=N;
		p = rand()%(N-1) + 1;
		q = rand()%(N-1) + 1;
		
		cout << "N = " << N << "   p = " << p << "   q = " << q << endl << endl;
		
		VI v1(p), v2(q);
		
		VI permutacja(N);
		REP(i,SIZE(permutacja)) permutacja[i] = i;
		
		REP(i,p){
			v1[i] = permutacja[ a = rand()%( N-i ) ];
			swap( permutacja[a], permutacja[ N-i-1] );
		}
		
		REP(i,q){
			v2[i] = permutacja[ a = rand()%( N-i ) ];
			swap( permutacja[a], permutacja[ N-i-1] );
		}
		
		cout << "v1:  "; WRITE(v1);
		ENDL(1);
		cout << "v2:  "; WRITE(v2);
		ENDL(1);
		
		VI ans1;
		lcsPerm( N+1, v1,v2, ans1 );
		cout << "Zwrocilem wartosc" << endl;
		cout << "SIZE(ans1) = " << SIZE(ans1) << endl; WRITE(ans1);
		
	//	VI ans2 = LCS::lcs( v1,v2 );		
	//	cout << "SIZE(ans2) = " << SIZE(ans2) << endl; WRITE(ans2);
		
		ENDL(5);
		
	/*	cout << "Dlugosc lcs to: " << SIZE(ans) << endl;
		cout << "A oto lcs: ";
		WRITE(ans);*/
		
	//	cout << "Case " << l_zest << ": " << SIZE(ans) << endl;
		
				
	}
	
	
	return 0;
}












