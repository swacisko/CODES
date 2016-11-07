#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<complex>
#include<stack>
#include<list>
#include<set>
#include<bitset>
#include<set>
#include<iterator>
#include<cmath>
#include<queue>
#include<time.h>
#include<string.h>
#include<fstream>
#include<sstream>
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
#define WRITE( V ) FOREACH(it,V) cout << *it << ", "; cout << endl;
#define WRITE_ALL(V,s)  cout << s << endl;  REP( i,SIZE(V) ){ cout << "i = " << i << endl;  FOREACH(it,V[i]) cout << *it << ", "; cout << endl;     }
#define WRP(p) p.ST << " " << p.ND
#define CLEAR( dst,quant ) memset( dst,0, (quant)*sizeof( __typeof(*dst) ) );
#define WAR if( show_help )
#define ENDL(x) REP(crow,(x)) cout << endl;

bool show_help = 0;
const int INF = 1000000001;
typedef long long LL;
LL N,M,K,b,c,y,t,w,l_zest,X;
const long double EPS = 1e-11;
typedef vector<long double> VD;
typedef pair<long double,int> PDI;
typedef pair<long double, long double> PDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

VLL a;
VLL num;

struct inter{
	LL beg, num;
	inter( LL b, LL n ) : beg(b), num(n) {}
	bool operator<( const inter & v ) const{
		if( beg < v.beg ) return true;
		if( beg == v.beg && num < v.num ) return true;
		return false;
	}
	bool operator>( const inter & v ) const{
		if( beg > v.beg ) return true;
		if( beg == v.beg && num > v.num ) return true;
		return false;
	}	
};

ostream & operator<<( ostream & str, const inter & v ){
	str << "beg = " << v.beg << "   num = " << v.num << endl;
	return str;
}

bool check( LL t ){
	LL suma = 0;
	REP(i,K) suma += (LL) ceil( (long double)t / (long double)a[i] );
//	cout << "\tt = " << t << "   suma = " << suma << endl;
	return suma >= N;
}

LL getX(){
	LL pr = 300000000;
	LL p = 1, q = pr*pr, k;
	while( p!=q ){
WAR		cout << "p = " << p << "   q = " << q << endl;
		if( check( k = ((p+q)/2) ) ) q = k;
		else p = k+1;
	}
	return p;
}




int main(){
	
	cin >> N >> K;
	a = VLL(K,0);
	num = VLL(K,0);
	REP( i,K ) cin >> a[i];
	
WAR	cout << "Dane:" << endl;
WAR	cout << N << " " << K << endl;
WAR	REP(i,K) cout << a[i] << " ";
WAR	cout << endl << endl;
	
	LL n = N;
	X = getX();
WAR	cout << "N = " << N << "  X = " << X << endl;
	
WAR	cout << "check(X-1 = " << X-1 << ") = " << check(X-1) << endl;
//	LL MAX = 0;
//	REP(i,K) MAX = max( MAX, a[i] );

/*	if( X <= MAX ){
		REP(i,K) num[i] = i+1;
		REP(i,K) cout << num[i] << " ";
		cout << endl;
		return 0;
	}*/
	LL x = 0;
	REP(i,K) x += (LL) ceil( (long double)(X-1) / (long double)( a[i] ) );
WAR	cout << "x = " << x << endl;
	x = N - x;
	x--;
WAR	cout << "x = " << x << endl;
	LL ile = x+1;
	
WAR	REP(i,K) cout << "X="<<X<<" % a["<<i<<"]="<<a[i]<<" = " << X % a[i] << endl;
	
	REP(k,K) if( ( X % a[k] ) == 1 || a[k] == 1 ){
		num[k] = n - x;
	//	n--;
WAR		cout << "num["<<k<<"] = " << num[k] << endl;
		if( x == 0 ) break;
		x--;
	}
	
	priority_queue<inter> pq;
	REP(i,K) if( ( X % a[i] ) == 1 || a[i] == 1 ) pq.push( inter( X - a[i],i ) );
			else pq.push( inter( ( (LL)( (X-1) / a[i] ) ) * a[i] + ( (a[i] == 1) ? 0 : 1 ), i  ) );
	
	n-=ile;
WAR	cout << "n = " << n << "   ile = " << ile << endl;
	
	while( ile < K ){
		inter Q = pq.top();
WAR		cout << "Kolejny inter to:   " << Q << endl;
		pq.pop();
		LL c = Q.beg, d = Q.num;
		pq.push( inter( c - a[d], d ) );
		if( num[d] == 0 ){
			num[d] = n;
			ile++;
		}
	//	cout << "\tn = " << n << endl;
		n--;
	}
	
WAR	cout << endl << "A oto pozostale intery:" << endl;
WAR	while( ! pq.empty() ){
		cout << pq.top();
		pq.pop();
	}
	
	REP(i,K) cout << num[i] << " ";
	cout << endl;
	return 0;
}












