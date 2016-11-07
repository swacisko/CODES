//#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
#include<bitset>
#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
//#include<time.h>
//#include<string.h>
#include<fstream>
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


bool checkMe( int a, int c, VI & ile, int ind, int *tab, int d1, int d2, int mis1, int mis2 ){
  /*  cout << "\tcheckMe,   ";
    REP(i,SIZE(ile)) cout << "ile[" << i << "]=" << ile[i] << "  ";
    cout << endl;*/

    int b = tab[ind];
    int dif1 = abs( b-a );
    int dif2 = abs( c-b );
 //   cout << "\t\t  tab[ind] = " << tab[ind] << "   dif1 = " << dif1 << "      dif2 = " << dif2 << "   d1 = " << d1 << "  d2 = " << d2 << "   mis1 = " << mis1 << "   mis2 = " << mis2 << endl;
 //   cout << endl;

    if( dif1 < SIZE(ile) ) ile[dif1]++;
    if( dif2 < SIZE(ile) ) ile[dif2]++;

    if( ile[mis1] <= 0 || (d1 > 0 && d1 < SIZE(ile) && ile[d1] <= 0) || (d2 > 0 && d2 < SIZE(ile) && ile[d2] <= 0) ){
        if( dif1 < SIZE(ile) ) ile[dif1]--;
        if( dif2 < SIZE(ile) ) ile[dif2]--;
        return false;
    }

    if( mis2 != -1 ){
        if( ile[mis2] <= 0 ||  (d1 > 0 && d1 < SIZE(ile) && ile[d1] <= 0) || (d2 > 0 && d2 < SIZE(ile) && ile[d2] <= 0) ){
            if( dif1 < SIZE(ile) ) ile[dif1]--;
            if( dif2 < SIZE(ile) ) ile[dif2]--;
            return false;
        }
    }

    if( dif1 < SIZE(ile) ) ile[dif1]--;
    if( dif2 < SIZE(ile) ) ile[dif2]--;
   // cout << "\tZwracam TRUE!" << endl;
    return true;
}

void myAdd( int a, int b, int c, int mis1, VPII & ans, VI & ile, int ind ){
    int dif1 = abs( b-a );
    int dif2 = abs( c-b );
 //   cout << "myAdd1  a = " << a << "  b = " << b << "  c = " << c << "  mis1 = " << mis1 << "  dif1 = " << dif1 << "   dif2 = " << dif2 << endl;

    int tab[] = {
        a-mis1, a+mis1, c-mis1,c+mis1
    };

   if( dif1 < SIZE(ile) )  ile[dif1]--;
    if( dif2 < SIZE(ile) ) ile[dif2]--;

    REP(i,4){
        if( checkMe(a,c,ile, i,tab,dif1,dif2,mis1,-1) ){
            ans.PB( MP( ind,tab[i] ) );
        }
    }

    if( dif1 < SIZE(ile) ) ile[dif1]++;
    if( dif2 < SIZE(ile) ) ile[dif2]++;

}


void myAdd( int a, int b, int c, int mis1, int mis2, VPII & ans, VI & ile, int ind ){
    int dif1 = abs( b-a );
    int dif2 = abs( c-b );

  //   cout << "myAdd2  a = " << a << "  b = " << b << "  c = " << c << "  mis1 = " << mis1 << "  mis2 = " << mis2 << "  dif1 = " << dif1 << "   dif2 = " << dif2 << endl;

    int tab[] = {
        a - mis1, a - mis2, c - mis1, c - mis2,
        a + mis1, a + mis2, c + mis1, c + mis2
    };

    if( dif1 < SIZE(ile) ) ile[dif1]--;
    if( dif2 < SIZE(ile) ) ile[dif2]--;

    REP(i,8){
        if( checkMe(a,c,ile,i,tab,dif1,dif2,mis1,mis2) ){
            ans.PB( MP( ind,tab[i] ) );
        }
    }

   if( dif1 < SIZE(ile) )  ile[dif1]++;
    if( dif2 < SIZE(ile) ) ile[dif2]++;
}

int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);

    int N;
    cin >> N;

    VI V(N+1);
    REP(i,N) cin >> V[i+1];

    VI ile(N,0); // was[i] = true if the difference i occurs...
    FOR(i,1,SIZE(V)-2) if( abs(V[i+1] - V[i]) <= N-1 && V[i+1] != V[i] ) ile[ abs(V[i+1] - V[i]) ]++;

  //  REP(i,SIZE(ile)) cout << "ile[" << i << "]=" << ile[i] << "  ";
 //   cout << endl;

    int ile2 = 0;
    FOR(i,1,SIZE(ile)-1) if( ile[i] > 0 ) ile2++;


    if( ile2 < N-3 ){
        cout << 0 << endl;
    }
    else{
        int mis1=-1, mis2=-1;

        FOR( i,1,SIZE(ile)-1 ) if( ile[i] == 0 ){
            mis2 = mis1;
            mis1 = i;
        }

     //   cout << "mis1 = " << mis1 << "   mis2 = " << mis2 << endl;

        VPII ans;
        int val;
        int dif,dif1,dif2;

        if( mis2 == -1 ){
            FOR(i,1,SIZE(V)-1){
                if( i == 1 ){
                    dif = abs( V[2] - V[1] );
                //    cout << "i == 1   dif = " << dif << endl;
                     if( dif == 0 || dif > SIZE(ile) || ile[ dif ] > 1 ){
                        ans.PB( MP( 1, V[2] + mis1) );
                        ans.PB( MP( 1,V[2] - mis1 ) );

                    }
                }
                else if( i == N ){
                    dif = abs( V[N] - V[N-1] );
                //    cout << "i == N    dif = " << dif << endl;
                    if( dif == 0 || dif > SIZE(ile) || ile[dif] > 1 ){
                        ans.PB( MP( N, V[N-1] + mis1 ) );
                        ans.PB( MP( N, V[N-1] - mis1 ) );
                    }
                }
                else{
                //    cout << "Teraz tu..." << endl;
                    myAdd( V[i-1], V[i], V[i+1], mis1, ans,ile,i );
                }
            }

        }
        else{
            FOR(i,2,SIZE(V)-2){ // jesli sa dwie roznice, to po brzegach i tak ich nie zmienie...
             //   cout << "FOR od 2 do N-2" << endl;
                myAdd( V[i-1],V[i],V[i+1],mis1,mis2,ans,ile,i );
            }

        }


      //  cout << "wyszedlem, przed unique" << endl;
        if( SIZE(ans) > 0 )sort( ALL(ans) );
        if( SIZE(ans) > 0 )ans.resize( unique( ALL(ans) ) - ans.begin() );
     //   cout << "Po resize" << endl;

        cout << SIZE(ans) << endl;
        REP(i,SIZE(ans)){
            cout << ans[i].ST << " " << ans[i].ND << endl;
        }

    }




	return 0;
}












