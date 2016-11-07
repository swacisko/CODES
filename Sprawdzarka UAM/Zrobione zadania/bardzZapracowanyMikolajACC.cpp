//#include<cstdio>
#include<iostream>
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
long long INF = 1000000001;
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
typedef long double LD;
typedef vector< LD > VLD;

const int MAXSIZE = 1000001;
LD V[MAXSIZE];
LD VAL;
LD sums[MAXSIZE];
int maxSuf[MAXSIZE];

int N;
int L;

template<class _T>
void write( vector<_T> V, string label = "" ){
    cout << label << endl;
    REP(i,SIZE(V)) cout << V[i] << " ";
    ENDL(1);
}


template< class _T>
bool equals( _T a, _T b ){
    return abs( a-b ) <= EPS;
}

// function return the sum and indexes of a subsequence meeting following conditions.
// if maxSum == true then  the found subsequence maximalizes the sum of its elements, otherwise the sum of its elements is minimalized...
// if subsequences given by indexes (a,b), (a,c) ( d,e ),  (d,f), ...  b<c,   e<f   are given, then if firstA == true it will return (a,b) (if firstB ==true)
// or (a,c) in case firstB == false  ( in other words it will return first or last occurences of endpoints of corresponding segments...
// function will consider only these subsequences, which length belongs to interval [minLength, maxLength]

template<class _T>
pair< _T, PII > sumSubsequence( vector<_T> kr, int minLength = 1, bool maxSum = true, bool firstA = true, bool firstB = true, int maxLength = INF ){
 //   vector<_T> sums( N ); // sums[i] is the sum of first i elements in given vector V
    if( maxSum == false ) REP(i,N) V[i] = -V[i]; // if i want to find minimum, not maximum, i switch signs of numbers...

    sums[0] = V[0] - VAL;
    FOR(i,1,N-1) sums[i] = sums[i-1] + V[i] - VAL;

 //   write( sums, "\nsums" );

    if( maxLength >= N ){ // if i have no constraint on maximum Length...  than the algorithm is O(N) time complexity...

      //  VI maxSuf( N ); // maxSuf[i] denotes the index of maximum value in vector sums in interval [i, SIZE(sums)-1 ]
        maxSuf[N-1] = N-1;

        FORD( i, N-2,0 ){
            if( sums[i] > sums[ maxSuf[i+1] ]+EPS ){ // if i find greater value, i remember it...
                maxSuf[i] = i;
            }
            else if( equals ( sums[i], sums[ maxSuf[i+1] ] ) ){ // here i remember first or last index of maximum value...
                if( firstB == true ) maxSuf[i] = i;
                else maxSuf[i] = maxSuf[i+1];
            }
            else{
                maxSuf[i] = maxSuf[i+1];
            }
        } // after this loop maxSuf should have determined indexes...

     //   write( maxSuf, "\nmaxSuf" );

        _T maxVal = sums[ maxSuf[ minLength-1 ] ];
        int begInd = 0, endInd = maxSuf[minLength-1];
        REP( i, N - minLength ){
            if( sums[ maxSuf[ minLength + i ] ] - sums[i] > maxVal+EPS ){
                maxVal = sums[ maxSuf[ minLength + i ] ] - sums[i];
                begInd = i+1;
                endInd = maxSuf[ minLength+i ];
            }
            else if( equals ( sums[ maxSuf[ minLength + i ] ] - sums[i], maxVal ) ){
                if( firstA == false ){
                    begInd = i+1;
                    endInd = maxSuf[ minLength+i ];
                }
            }
        } // after this loop i should have found the maximum value and boundaries of found subsequence...

        return MP( maxVal, PII( begInd, endInd ) );

    }
    else{ // else it is O( N * lg( maxLength - minLength )  ) time complexity because of the map consumption

    }



}






void clearAll(){
  //  V.clear();
}

void initializeAll(){
}

void readData(){
    cin >> N >> L;
//    V = VLD(N);
    REP(i,N) cin >> V[i];
}

void solve(){
    clearAll();
    readData();

    pair< LD, PII > ans;
    int ile = 0;
    VAL = 0;
    do{
        ans = sumSubsequence( vector<LD>(0), L,1,1,0 );
        LD val = ans.ST;
        val /= LD( ans.ND.ND - ans.ND.ST + 1 );
        VAL += val;

      /*  cout << "VAL = " << VAL << endl;
        REP(i,SIZE(V)) V[i] -= val;
        cout << "val = " << val << endl;
        cout << "tab:" << endl;
        WRITE(V);
        ENDL(1);
        REP(i,500000000);*/

        if( ile++ > 10000 ){
            int tab[3];
            REP(i,1000000) cout << V[i] << endl;
        }

    }while( !equals( ans.ST, (LD)0 ) && ile < 50 );

    cout << ans.ND.ST+1 << " " << ans.ND.ND + 1 << endl;



}





int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);

	REP(i,5) INF *= 10;

    int l_zest;
    const int l_zest2 = l_zest; // this is only to remember, how many testcases there were at the beginning
    cin >> l_zest;
	while( l_zest-- ){
        solve();

	}


	return 0;
}












