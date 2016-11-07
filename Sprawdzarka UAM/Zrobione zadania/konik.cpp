//#include<cstdio>
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

int N,M;
int STALA;

int board[52][52][71];
bool was[102][102];

int maxval[52][52];

void writeBoard(){
    FOR(i,1,N){
        FOR(j,1,M){
            if( was[i][j] ) cout << " ";
            else cout << "o";
        }
        cout << endl;
    }

    ENDL(2);

}



void preproc(){
    int N2 = (N+1)/2;
    int M2 = (M+1)/2;

    FOR(i,1,N2) {
         FOR(j,1, M2){
             FOR(k,1,70) board[i][j][k] = 0;
             board[i][j][0] = 1;
             was[i][j] = false;
         }
    }

    VPII places, newplaces;
    FOR(i,1,N2) {
        FOR(j,1, M2){
            places.clear();
            newplaces.clear();
            newplaces.PB( MP(i,j) );

            FOR(r,1,N) FOR(t,1,M) was[r][t] = false;
            was[i][j] = true;


            board[i][j][0] = 1;

            FOR( k,1,STALA ){
             //   if( i == 1 && j == 2 && k <= 5 ) writeBoard();

                swap( places, newplaces );
                newplaces.clear();
                REP( l,SIZE(places) ){
                    FOR( x,-2,2 ) {
                        FOR(y,-2,2){
                            if( x*y == 2 || x*y == -2 ){
                                if( places[l].ST + x >= 1 && places[l].ST + x <= N && places[l].ND+y >= 1 && places[l].ND+y <= M  ){
                                    if( !was[ places[l].ST+x ][ places[l].ND+y ] ){
                                        was[ places[l].ST+x ][ places[l].ND+y ] = true;
                                        newplaces.PB( MP(places[l].ST+x, places[l].ND+y ) );
                                    }
                                }
                            }

                        }
                    }
                }

                if( k >= 2 ) board[i][j][k] = board[i][j][k-2] + SIZE( newplaces );
                else board[i][j][k] = SIZE( newplaces );

             //   if( i == 1 && j == 2 && k <= 5 ) cout << "Board[" << i << "][" << j <<"][" << k <<"] = " << board[i][j][k] << endl;

            }
        }
    }

}




int main(){
	ios_base::sync_with_stdio(0);
//	cout << fixed;
	//cout.precision(2);

    cin >> N >> M;

    STALA = min( 70, max(N,M)+4 );
    preproc();

    int l_zest;
    cin >> l_zest;
	while( l_zest-- ){
        int a,b,K;
        cin >> a >> b >> K;


        if( K > STALA ){
            if( N == 2 || M == 2 ){
                if( a > (N+1)/2 ) a = N - a+1;
                if( b > (M+1)/2 ) b = M - b+1;

                if( (K-STALA)%2 == 0 ) { // if K and STALA are of the same parity, then...
                    cout << board[a][b][STALA-2];
                    continue;
                }
                else{ // otherwise...
                    cout << board[a][b][STALA-3];
                    continue;
                }



            }
            else if( (N*M)%2 == 0 ){
                cout << (N*M)/2 << endl;
                continue;
            }
            else{
                if( (a+b)%2 == 0 ){
                    cout << (N*M + 1)/2 << endl;
                    continue;
                }
                else{
                    cout << (N*M)/2 << endl;
                    continue;
                }
            }

        }

        if( a > (N+1)/2 ) a = N - a+1;
        if( b > (M+1)/2 ) b = M - b+1;

        cout << board[a][b][K] << endl;



	}

	return 0;
}












