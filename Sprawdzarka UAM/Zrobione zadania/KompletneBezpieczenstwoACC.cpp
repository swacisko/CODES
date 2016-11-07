//#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
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
typedef long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

LL N,K;

VVI tab1, tab2;
VI f;

/*
LL getVal2(int,int);

LL getVal1( int up, int down ){
    if( up == 0 ) return 0;
    else if( down == 0 ) return f[up];
    else{
        if( tab1[up][down] != -1 ) return tab1[up][down]; // jesli juz znam ta wartosc, to ja przypisuje, bez wywolywania rekurencyjnego...
        else{
            LL val = 0;
            FOR( j,1,up ){
                val +=  ( (  ( f[j] * getVal2( up-j, down ) )%K )  *  ( up+1-j ) ) ;

            }
            if( val >= K ) val %= K;


         //   cout << "getVal1, up = " << up << "   down = " << down << "   val = " << val << endl;
            tab1[up][down] = val;
            return val;
        }
    }

}

LL getVal2( int up, int down ){
    if( down == 0 ) return 0;
    else if( up == 0 ) return f[down];
    else{
        if( tab2[up][down] != -1 ) return tab2[up][down]; // jesli juz znam ta wartosc, to ja przypisuje, bez wywolywania rekurencyjnego...
        else{
            LL val = 0;
            FOR( j,1,down ){
                val += ( ( ( f[j] * getVal1( up, down-j )  ) % K ) * ( down+1-j ) );

            }
            if( val >= K ) val %= K;


        //    cout << "\tgetVal2, up = " << up << "   down = " << down << "   val = " << val << endl;
            tab2[up][down] = val;
            return val;
        }
    }
}*/


int solve( int N ){

    LL val1 = 0;
    LL val2 = 0;

    FOR(i,2,N){
        FOR( k,1,i ){

            val1 = val2 = 0;

            FORD( j,i,1 ){
                if( tab2[i-j][k] == -1 ){
                    cout << endl << "\t\t-1 w tablicy tab2[" << i-j << "][" << k << "]   i = " << i << "   j = " << j << "    k = " << k << endl;
                }
                val1 += ( (LL)( tab2[i-j][k] * f[j] ) % K ) * (i-j+1);
               // val1 += ( (LL)( tab1[k][i-j] * f[j] ) % K ) * (i-j+1);
            }

            if( val1 >= K ) val1 %= K;
            tab1[i][k] = val1;
            tab2[k][i] = val1;


           /* FORD(j,i,1){
                if( tab1[k][i-j] == -1 ){
                    cout << "-1 w tablicy tab1[" << k << "]["<<i-j<<"]   i = " << i << "   j = " << j << "    k = " << k << endl;
                }
                val2 += ( (LL)( tab1[k][i-j] * f[j] ) % K ) * (i-j+1);
            }

            if( val2 >= K ) val2 %= K;
            tab2[k][i] = val2;*/

          /*   cout << "Oto tablica tab1:" << endl;
            WRITE_ALL(tab1);

            cout << "Oto tablica tab2:" << endl;
            WRITE_ALL(tab2);*/
            cout << "i = " << i << "    k = " << k << "  tab1[" << i << "][" << k << "] = " << tab1[i][k] << "   tab2["<<k<<"]["<<i<<"] = " << tab2[k][i] << endl;
          //  ENDL(3);
        }

        ENDL(1);

    }

    return ( 2* tab1[N][N] ) % K;
}



int solve2( int N ){

    LL val1 = 0;

    FOR(t,3,2*N){
        FOR( i,1,min(t,N) ){
            int a,b;
            a = i;
            b = t-i;
            if( b > N ) b = N;

          //  cout << "t = " << t << "   a = " << a << "   b = " << b;

            val1 = 0;

            FOR( j,1,a ){
                val1 += ( ( (LL)f[j] * tab1[ b ][a-j]  ) %K ) * (a-j+1);
            }

            if( val1 >= K ) val1 %= K;
            tab1[a][b] = val1;

         //   cout << "   tab1[" << a << "][" << b << "] = " << tab1[a][b] << endl;


        }

    //    ENDL(2);

    }

    return ( 2* tab1[N][N] ) % K;
}





void setF( int N ){
    fill(ALL(f),1);

    FOR(i,2,N){
       f[i] = ( 2*f[i-1] ) % K;
    }
}

void setZeroAndOneTabs(int N){
    REP(i,N+1) tab1[0][i] = tab2[i][0] = 0;
    REP(i,N+1) tab1[i][0] = tab2[0][i] = f[i];
    REP(i,N+1) tab1[1][i] = tab2[i][1] = f[i];
}


int main(){
	ios_base::sync_with_stdio(0);

	cin >> N >> K;

	tab1 = tab2 = VVI( N+1, VI(N+1,-1) );
    f = VI( N+1,0 );

    setF(N);
    setZeroAndOneTabs(N);

 //   cout << "Oto f" << endl;
   // WRITE(f);


	//LL res = 2*getVal1(N,N);
	LL res = solve2(N);
	res %= K;
	if( res == 0 ) res = K;

	cout << res << endl;

  /*  cout << "Oto tablica tab1:" << endl;
    WRITE_ALL(tab1);

    cout << "Oto tablica tab2:" << endl;
    WRITE_ALL(tab2);*/





	return 0;
}












