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
pair< _T, PII > sumSubsequence( vector<_T>& V, int minLength = 1, bool maxSum = true, bool firstA = true, bool firstB = true, int maxLength = INF ){
    vector<_T> sums( SIZE(V) ); // sums[i] is the sum of first i elements in given vector V
    if( maxSum == false ) REP(i,SIZE(V)) V[i] = -V[i]; // if i want to find minimum, not maximum, i switch signs of numbers...

    sums[0] = V[0];
    FOR(i,1,SIZE(sums)-1) sums[i] = sums[i-1] + V[i];

    write( sums, "\nsums" );

    if( maxLength >= SIZE(V) ){ // if i have no constraint on maximum Length...  than the algorithm is O(N) time complexity...

        VI maxSuf( SIZE(V) ); // maxSuf[i] denotes the index of maximum value in vector sums in interval [i, SIZE(sums)-1 ]
        maxSuf.back() = SIZE(V)-1;

        FORD( i, SIZE(V)-2,0 ){
            if( sums[i] > sums[ maxSuf[i+1] ] ){ // if i find greater value, i remember it...
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

        write( maxSuf, "\nmaxSuf" );

        _T maxVal = sums[ maxSuf[ minLength-1 ] ];
        int begInd = 0, endInd = maxSuf[minLength-1];
        REP( i, SIZE(V) - minLength ){
            if( sums[ maxSuf[ minLength + i ] ] - sums[i] > maxVal ){
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


void testMe(){
    cout << "Enter the length of the sequence:\t";
    int N;
    cin >> N;
    VI seq(N);
    cout << "Enter values:" << endl;
    REP(i,N){
        cout << i << "-th value:\t";
        cin >> seq[i];
    }
    cout << "Enter minimal length:\t";
    int minLength;
    cin >> minLength;

    int maxLength = INF;
  /*  cout << "Enter maximal length:\t";
    cin >> maxLength;*/

    pair< int, PII > ans = sumSubsequence( seq, minLength, 1,0,0 );
    cout << "Maximal sum equals:\t" << ans.ST << endl;
    cout << "It is found in subsequence in bounds [" << ans.ND.ST << "," << ans.ND.ND << "] = ";
    FOR(i, ans.ND.ST, ans.ND.ND ) cout << seq[i] << " ";
    cout << endl;

}


int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);

	while( 1 ){
        testMe();

	}


	return 0;
}












