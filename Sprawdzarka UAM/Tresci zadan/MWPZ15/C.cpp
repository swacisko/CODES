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

#define MYR for
#define REP( x,y ) MYR( int x=0; x<(y); x++ )
#define QUEST ?
//#define AND &&
//#define OR ||
#define MYF if




//#define FORD( x,y,z ) for( int x=y; x>=(z); x-- )
//#define FOR(x,b,e) for( int x = b; x <= (e); ++x )
#define SIZE(v) (int)v.size()

/*#define ALL(c) c.begin(),c.end()
#define VAR(v,n) __typeof(n) v=(n)
//#define FOREACH(i,c) for( VAR(i,c.begin());i!=c.end();++i )
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
typedef vector< PDD > VPDD;
typedef vector<bool> VB;
typedef unsigned long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;*/


void deleteSpaces( string & s ){
	REP(i,SIZE(s)){
		MYF( s[i] == ' ' ){
			s.erase( s.begin()+i );
			i--;			
		}
	}	
}


void deleteQuotes( string & s ){
	int p = -1;
	REP( i, SIZE(s) ){
		MYF( s[i] == '"' ){
			MYF( p == -1 ){
				p = i;
			}
			else{
				s.erase( s.begin() + p, s.begin() + i + 1 );
				i--;
			}
			
		}		
	}	
}

// zlicza liczbe wystapien slowa t w slowie s
int howMany( string s, string t ){
	int res = 0;
	REP(i,SIZE(s)){
		MYF( s[i] == t[0] ){
			bool differs = false;
			MYR( int k=1; k < SIZE(t) && i+k < SIZE(s); k++ ){
				
				MYF( s[i+k] != t[k] ) differs = true;				
			}
			
			MYF( differs == false ) res++;			
		}		
	}
	
	return res;	
}


int countValue(string s){
	int res = 0;
	res += howMany( s, "for(" );
	res += howMany( s, "while(" );
	res += howMany( s, "if(" );
	res += howMany( s, "switch(" );
	
	return res;
}



int main(){
	
	
	int L;
	cin >> L;
	cin.ignore();
	
	string s,temp;
	
	REP(i,L){
		//cin >> temp;
		getline( cin,temp );
		
		deleteSpaces(temp);
		deleteQuotes(temp);
		
		s += temp;		
	}
	
	//cout << "s = " << s << endl;
	
	int res = 1 + countValue(s);
	
	
	res <= 10 QUEST cout << "POPRAWNY" : (  res <= 20 QUEST cout << "UJDZIE" : cout << "MASAKRA"   );
	cout << endl << res << endl;
	
	
	
	
	
	return 0;
}


/*


19
#include<iostream>
using namespace std;
int main ()
{

int a = 100;

if( a < 20 )
{
cout << "a is less than 20;" << endl;
}
else
{
cout << "a is not less than 20;" << endl;
}
cout << "value of a is : " << a << endl;

return 0;
}


*/

