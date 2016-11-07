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

int N;
VI upseq; // upper sequence
VI downseq; // lower sequence
//set<PII> signumPairs; // vector of pairs (a,b)  such that in function phase1Signum number of value a form upper seq must be swapped
bitset<2002> signumPairs[2002];

// with number of value b in lower seq... of course must occur a < 0  and b > 0

bool condition1( int j, int i ){
    return upseq[j] > downseq[N-1-i+j];
}

bool condition2( int j, int i ){
    return upseq[j] > downseq[j-i-1];
}


bool condition3( int up, int upind, int down, int downind ){
    if( up > 0 && up == downind+1 ) return true;
    else if( down < 0 && N+1+down == upind+1 ) return true;
    else if( up*down > 0 && up > down ) return true;
    return false;
}

void phase2ProperSort(){
    cout << "P" << endl; // i start next MOVE and therefore write out P

    bool isK = false;
    int howMany = 0;

    REP(i,N){ // here is the loop till sequences are "overlaping"
        cout << "K" << endl; // i start next step
     //   howMany++;
   //     isK = false;

        FOR( j,0,i ){
            if( /*condition1(j,i)*/ condition3( upseq[j], j, downseq[N-1-i+j], N-1-i+j ) ){ // if i should swap theese two values...
              /*  if( !isK ){
                    REP(o,howMany) cout << "K" << endl;
                    isK = true;
                    howMany = 0;
                }*/
                cout << "Z " << j+1 << endl;
                swap( upseq[j], downseq[ N-1-i+j ] );
            }
        }
    }

    howMany = 0;
    REP(i,N-1){ // here is the loop till sequences are "overlaping"
        cout << "K" << endl; // i start next step
    //    howMany++;
     //   isK = false;

        FOR( j, i+1, N-1 ){
            if( /*condition2(j,i)*/ condition3( upseq[j], j, downseq[j-i-1], j-i-1 )  ){
            /*    if( !isK ){
                    REP(o,howMany) cout << "K" << endl;
                    isK = true;
                    howMany = 0;
                }*/
                cout << "Z " << j+1 << endl;
                swap( upseq[j], downseq[j-i-1] );
            }
        }

    }

    cout << "Q" << endl; // i end all steps and MOVES....
}

// swaps all negative numbers from upper sequence with positive numbers from lower sequence
void phase1Signum(){
    cout << "P" << endl; // i start next MOVE and therefore write out P

  //  bool isK = false;
   // int howMany = 0;

    REP(i,N){ // here is the loop till sequences are "overlaping"
        cout << "K" << endl;
     //   howMany++;
      //  isK = false;
        FOR( j,0,i ){
            if( /*signumPairs.count( MP( upseq[j], downseq[N-1-i+j] ) ) > 0*/ signumPairs[ N+upseq[j] ][ N+downseq[N-1-i+j] ] ){ // if i should swap theese two values...
            /*    if( !isK ){
                    REP(o,howMany) cout << "K" << endl;
                    isK = true;
                    howMany = 0;
                }*/

                cout << "Z " << j+1 << endl;
               // signumPairs.erase( MP( upseq[j], downseq[N-1-i+j] ) );
               signumPairs[ N+upseq[j] ][ N+downseq[N-1-i+j] ] = false;
                swap( upseq[j], downseq[ N-1-i+j ] );
            }
        }
    }

//    howMany = 0;
    REP(i,N-1){ // here is the loop till sequences are "overlaping"
        cout << "K" << endl;
     //   howMany++;
     //   isK = false;
        FOR( j, i+1, N-1 ){
            if( /*signumPairs.count( MP( upseq[j], downseq[ j-i-1 ] ) ) > 0*/ signumPairs[ N+upseq[j] ][ N+downseq[j-i-1] ] ){
               /* if( !isK ){
                    REP(o,howMany) cout << "K" << endl;
                    isK = true;
                    howMany = 0;
                }*/

                cout << "Z " << j+1 << endl;
            //    signumPairs.erase( MP( upseq[j], downseq[ j-i-1 ] ) );
                signumPairs[ N+upseq[j] ][ N+downseq[j-i-1] ] = false;
                swap( upseq[j], downseq[j-i-1] );
            }
        }

    }

}

// if checIfSemiOrderedSequences return false, it means, that i have to at first push all negative elements to the bottom sequence and in phase 2 swap all afterwards...
// this function determines, whic elements musst be swapped and how...
void createSignumPartition(){
    int p = 0, q = 0;
    while( p < SIZE( upseq ) && q < SIZE( downseq ) ){
        if( upseq[p] > 0 ) p++; // i search for subsequent negative numbers in upper sequence to transfer it to lower...
        if( downseq[q] < 0 ) q++; // i search fo subsequent positiove number in lower seq. to transef to upper

        if( p >= SIZE(upseq) || q >= SIZE( downseq ) ) return;

        if( upseq[p] < 0 && downseq[q] > 0 ){
          //  signumPairs.insert( MP( upseq[p], downseq[q] ) );
            signumPairs[ N+upseq[p] ][ N+downseq[q] ] = true;
            p++;
            q++;
        }
     //   cout << "SignumPartition" << endl;
    }
    return;
}

// checks if sequences are semi ordered, it return true if in lower sequence there is no index i such that  downseq[i] > i+1  and parallel to upper sequnce...
bool checkIfSemiOrderedSequences(){
    REP( i, SIZE(downseq) ) if( downseq[i] > i+1 ) return false;
    REP( i, SIZE(upseq) ) if( upseq[i] < -N + i ) return false;
    return true;
}


// reutrnes true if sequences are ordered  upper: -n, -n+1, -n+2, ..., -1,      lower:  1, 2, ... , n
bool checkIfOrderedSequences(){
    REP(i,SIZE(upseq)) if( upseq[i] != -N + i ) return false;
    REP( i, SIZE( downseq ) ) if( downseq[i] != i+1 ) return false;
    return true;
}

// inverser negative numbers, makes -n from -1, -n+1 form -2 etc   makes -n-1+i from -i...
void inverseNegatives(){
    REP( i, SIZE(upseq) ) if( upseq[i] < 0 ) upseq[i] = -N-1-upseq[i];
    REP( i, SIZE(downseq) ) if( downseq[i] < 0 ) downseq[i] = -N-1-downseq[i];
}

void clearAll(){
    upseq.clear();
    downseq.clear();
  //  signumPairs.clear();
    REP(i, 2*N+2 ) signumPairs[i].reset();

}

void initializeAll(){
    upseq = VI(N);
    downseq = VI(N);
}

void readData(){
    cin >> N;
    initializeAll();
    REP(i,N) cin >> upseq[i];
    REP(i,N) cin >> downseq[i];
}

void writeSequences(){
    cout << "N = " << N << endl;
    REP(i,N) cout << upseq[i] << " "; cout << endl;
    REP(i,N) cout << downseq[i] << " "; cout << endl << endl;
}
/*
void generateRandom(){
    int MAXSIZE = 1000;
    N = 10 + rand()%MAXSIZE;

    VI seq(2*N);
    REP(i,N) seq[i] = -i-1;
    REP(i,N) seq[N+i] = i+1;
    REP(i,MAXSIZE) random_shuffle( ALL(seq) );
    REP(i,N) upseq.PB( seq[i] );
    REP(i,N) downseq.PB( seq[N+i] );

  //  writeSequences();
}

void wait(int seconds)
{
    clock_t end = clock() + (seconds * CLOCKS_PER_SEC);
    while ( clock() < end);
}*/


void solve(){
    clearAll();
    readData();
   // generateRandom();


    inverseNegatives();
    if( checkIfOrderedSequences() ){ // if sequences are ordered properly form the start...
        cout << 0 << endl << "Q" << endl;
       // return;
    }
    else if( checkIfSemiOrderedSequences() ){ // if i need only one MOVE
        cout << 1 << endl;
        phase2ProperSort();
       // return;
    }
    else{ // if i need 2 MOVES...
        cout << 2 << endl;
        createSignumPartition();

        phase1Signum();
        phase2ProperSort();
      //  return;
    }




}


int main(){
 //   srand( unsigned( time(0) ) );
	ios_base::sync_with_stdio(0);
//	cout << fixed;
//	cout.precision(2);

    int l_zest;
    cin >> l_zest;
    int T = l_zest;

    int ILEZLE = 0;
	while( l_zest-- ){
        solve();

     //   cout << "POPRAWNOSC KONCOWA:   " << ( checkIfOrderedSequences() ? 1 : 0 ) << endl;
     //   if( !checkIfOrderedSequences() ) ILEZLE++;
        //    writeSequences();

        //   wait(1);
	}

  // cout << "Out of " << T << " tests " << ILEZLE << " were false..." << endl;

	return 0;
}












