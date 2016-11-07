#include<stdio.h>
//#include<iostream>
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
//#include<algorithm>
//#include<conio.h>
//#include<iomanip>

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
//typedef vector<string> VS;
//typedef vector< VS > VVS;


int MODULO = 1000000;
int M,beg;

/*
VVI tab;
int shortest[5001];
int shk[5001];
int lgk[5001];

int M; // number of hiperlevers
int beg; // beginning number - denoting the base of the tower, initial amount of money
//int MODULO = 1000000;



void preproc(){
    VB was( MODULO+1, false );
    int ile = 0;
    int a,b;
    tab = VVI( 5001, VI(2,0) );
   // VI tab(2);

    FOR(i,1,5000){
     //   cout << "i = " << i << "    " << flush;
        tab[i][0] = 1;
        tab[i][1] = i;
      //  tab.clear();
      //  tab = VI(2);
      //  tab[0] = 1;
     //   tab[1] = i;

        fill( ALL(was), false );
        was[i] = true;
        was[1] = true;
        ile = 1;

      //  b = tab[i][1]*i;
        b = ((LL)tab[i][1]*i) % MODULO;
     //   cout << "Przed petla  " << flush;
        while( !was[b] ){
            was[b] = true;
            ile++;
            tab[i].PB(b);
            //tab.PB(b);
            b = ((LL)b*i)%MODULO;
        }

        int tr = 0;
    //    cout << "tr1  SIZE(tab) = " << SIZE(tab) << "    " << flush;
        while( tab[i][tr] != b ) tr++;
     //   while( tab[tr] != b ) tr++;
     //   cout << "tr = " << tr << "   ile = " << ile;
        shk[i] = tr;
        lgk[i] = ile;
        shortest[i] = lgk[i] - shk[i] + 1;
      //  cout << "   end of loop" << endl;
    }

}

void writeTables(){
    cout << "shk:" << endl;
    FOR(i,1,20) cout << "shk[" << i << "] = " << shk[i] << endl;

    cout << endl << "lgk:" << endl;
    FOR(i,1,20) cout << "lgk[" << i << "] = " << lgk[i] << endl;

  //  cout << "Tab:" << endl;
  //  FOR(i,1,9){
  //      cout << "i = " << i << "  ->  ";
   //     FOR( k,1,lgk[i] ) cout << tab[i][k] << " ";
   //     cout << endl;
   // }

}



// return answer to the task
int solve( VI & V ){
    int i,k;
    while( SIZE(V) >= 2 ){
        i = V[ SIZE(V)-2 ];
        k = V.back();

     //   cout << "i = " << i << "   k = " << k << endl;

        if( k <= lgk[i] ){
            V[ SIZE(V)-2 ] = tab[i][k];

        }
        else{
            int d = k - shk[i];
            int e = shk[i] + d%shortest[i];
        //    cout << "d = " << d << "   e = " << e << endl;
            V[ SIZE(V)-2 ] = tab[i][e];
        }


        V.pop_back();
     //   cout << "Zastepuje wyrazenie i^k wartoscia " << V.back() << endl << endl;
    }


    return V[0];
}


// return a^N % MODULO
int power( int a, int n ){
    int res = 1;
    int c = a;
    while( n >= 1 ){
        if( n&1 )  res = ( (LL)res*c )%MODULO;
        c = ( (LL)c*c )%MODULO;
        n /= 2;
    }

    return res%MODULO;

}

int solve2( VI & V ){
    while( SIZE(V) >= 2 ){
   //     cout << "Zamieniam " << V[ SIZE(V)-2 ] << "  na " << power( V[ SIZE(V)-2 ], V.back() ) << endl;
        V[ SIZE(V)-2 ] = power( V[ SIZE(V)-2 ], V.back() );
        V.pop_back();
    }
    return V[0];

}
*/

int MOD1 = 50000;

int power50000( int a, int n ){
    int res = 1;
    bool  red = false;
    if( (float)n * log(a) >= (float)log(MOD1) ) red = true;

    while( n != 0 ){
        if( n&1 )  res = ( (LL)res*a )%MOD1;
        a = ( (LL)a*a )%MOD1;

        n >>= 1;
    }

    if( red ) return MOD1 + res;
    else return res;
}



int power( int a, int n ){
    int res = 1;
    while( n != 0 ){
        if( n&1 )  res = ( (LL)res*a )%MODULO;
        a = ( (LL)a*a )%MODULO;
        n >>= 1;
    }

    return res%MODULO;
}

int V[200001];
int solve3(){
    int ile = min( 50,M-2 ), a=V[ile+1];
    while( ile >= 0 ){
   //     cout << "Zamieniam " << V[ SIZE(V)-2 ] << "  na " << power( V[ SIZE(V)-2 ], V.back() ) << endl;
        a = power50000( V[ ile ], a );
      //  V.pop_back();
      ile--;
    }
    return a;
}


int main(){
//	ios_base::sync_with_stdio(0);


//	preproc();

//	writeTables();

   // V = VI(200001);
	int l_zest;
//	cin >> l_zest;
    scanf("%d",&l_zest);
	while(l_zest--){

       // cin >> M;
      //  cin >> beg;
        scanf("%d %d",&M,&beg);

      //  int a;
      //  bool still = true;
      //  int M2;

        REP(i,M){
            //cin >> a;
            scanf("%d",&V[i]);

           /* if( still ){
                if( a == 1 ){
                    still = false;
                    M2 = i;
                }

            }*/
        }

     //   M = M2-1;

       /* if( beg == 1 ){
            cout << 1 << endl;
            continue;
        }*/

    //   cout << "Oto twoje wczytane liczby:" << endl;
    //    REP(i,SIZE(V)) cout << V[i] << " ";
    //    cout << endl;

     //   cout << power( beg, solve3( V ) ) << endl;

       // red = false;
        int res = power( beg, solve3() );
        printf( "%d\n",res );

     /*   int b;
        while( cin >> a >> b ){
            cout << power(a,b) << endl;
        }*/

	}


    return 0;
}












