//#include<stdio.h>
#include<iostream>
#include<vector>
//#include<string>
//#include<map>
#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
#include<time.h>
//#include<string.h>
//#include<fstream>
//#include<sstream>
#include<algorithm>
#include<conio.h>
#include<iomanip>

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


/*
Przestrzen nazw, w ktorej znajduja sie rozne algorytmy dla wielomianow - np wartosc w punkcie hornerem, czy FFT

*/

namespace POL{
	typedef complex<double> _T;
	vector< _T > a,y,y2; // to sa wektory pomocnicze
	int N; // to jest rozmiar, jaki musza miec wektory, aby moc jes wymnazac metoda fft, czyli musi to byc potega dwojki, wieksza conajmniej 2 razy od max SIZE(pol)

	// to jest
	void fft( int n, double znak, int p=0, int s=1, int q=0  ){
		if( n == 1 ){
			y[q] = a[p];
			return;
		}

		_T en = exp( _T( 0, 2*M_PI*znak/n ) ), e=1;

		fft( n/2, znak, p, s*2, q);
		fft( n/2, znak, p+s, s*2, q+n/2 );

		REP(k,n/2){
			y2[k] = y[q+k] + e*y[ q + n/2 + k ];
			y2[ n/2+k ] = y[q+k] - e*y[ q + n/2 + k ];
			e *= en;
		}

		REP(k,n) y[q+k] = y2[k];
	}


	void writePol( VD & pol ){
		cout << showpos;
		REP(i,SIZE(pol)){
			if( i > 0 ) cout << " ";
			cout << pol[i];
			if( i > 0 ) cout << "(x^"<<i <<")";
		}
		cout << noshowpos;
	}

	bool isZero( double d ){
		return ( d > -EPS && d < EPS );
	}


	// funkcja zapisuje w wektorze ans wynik mnozenia dwoch wielomianow przeslanych jako parametry
	void multiply( VD & pol1, VD & pol2, VD & ans ){
		int M = max( SIZE(pol1), SIZE(pol2) );
		N = 1;
		while( N <= M ) N <<= 1;
		N <<= 1;

		a = vector< _T > ( N );
		y2 = vector<_T>(N);
		y = vector<_T>(N);
		REP( i,SIZE(pol1) ) a[i] = _T( pol1[i],0 );

		fft( N,1 );

		vector<_T> save1; // tutaj jest wyznaczony przez fft pierwszy wektor wspolczynnikiw
		swap( save1,y );

		a = vector< _T > ( N );
		y2 = vector<_T>(N);
		y = vector<_T>(N);
		REP( i,SIZE(pol2) ) a[i] = _T( pol2[i],0 );

		fft( N,1 );

		vector<_T> save2;
		swap( save2, y );

		vector<_T>ans2(N);
		REP(i,SIZE(save1)) ans2[i] = save1[i]*save2[i];

		y2 = vector<_T>(N);
		y = vector<_T>(N);
		swap( ans2,a );

		fft( N,-1 );

		ans = VD( SIZE(y) );
		REP( i,SIZE(y) ) ans[i] = real( y[i] );

		int t = SIZE(ans)-1;
		while( isZero( ans[t--] ) ) ans.pop_back();
		REP(i,SIZE(ans)) ans[i] /= N;
	}


	// funkcja zwraca wartosc wielomianu pol w punkcie p - w czasie liniowym
	template<class typ>
	typ horner( vector<typ> & pol, typ p ){
		typ val = pol[ SIZE(pol)-1 ];
		FORD( i, SIZE(pol)-2,0 ){
			val *= p;
			val += pol[i];
		}
		return val;
	}


	void add( VD & pol1, VD & pol2, VD & ans ){
		ans = VD( max( SIZE(pol1), SIZE(pol2) ) );
		int p=0,k=0;
		while( p < SIZE(pol1) || k < SIZE(pol2) ){
			if( p < SIZE(pol1) ) ans[p] += pol1[p++];
			if( k < SIZE(pol2) ) ans[k] += pol2[k++];
		}
	}


	// funkcja sluzaca do szybkiego mnozenia duzych liczb - w czasie O(nlgn)
	// jako parametry przyjmuje liczby w postaci stringow, jako rezultat zwraca liczbe w postaci wektora intow
	VI fast_multiplication( string & s1, string & s2 ){
		VD pol1 = VD( SIZE(s1) );
		VD pol2 = VD( SIZE(s2) );

		if( s1 == "0" || s2 == "0" ) return VI(1,0);

		int t1 = SIZE(s1), t2 = SIZE(s2);
		REP( i,SIZE(s1) ) pol1[i] = (double)( (int)s1[ t1-1-i ] - 48 );
		REP( i,SIZE(s2) ) pol2[i] = (double)( (int)s2[ t2-1-i ] - 48 );

		VD ans;
		POL::multiply( pol1,pol2,ans );

		VI polin( SIZE(ans) );
		if( !SIZE(polin) ) polin = VI( 1, 0 );
		REP( i,SIZE(polin) ) polin[i] = (int) round( ans[i] );

		REP( i,SIZE(polin) ){
			int t = i;
			LL T = polin[i];
			polin[i] %= 10;
			while( T > 0 ){
				if( t >= SIZE(polin) )	polin.PB(0);
				if( t > i ) polin[t] += T%10;
				T /= 10;
				t++;
			}
		}
		int t = SIZE(polin)-1;
		while( polin[t--] == 0 ) polin.pop_back();
		reverse( ALL(polin) );
		return polin;
	}



}







int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(2);

	while( 1 ){
		VD pol1, pol2;

		cout << "Podaj rozmiar pierwszego wielomianu:  ";
		int n1;
		cin >> n1;
		REP(i,n1){
			cout << "Podaj wartosc wspolczynnika przy " << i << "-tej potedze: ";
			double d;
			cin >> d;
			pol1.PB(d);
		}

		ENDL(2);

		cout << "Podaj rozmiar drugiego wielomianu:  ";
		int n2;
		cin >> n2;
		REP(i,n2){
			cout << "Podaj wartosc wspolczynnika przy " << i << "-tej potedze: ";
			double d;
			cin >> d;
			pol2.PB(d);
		}


		cout << "Wielomian pierwszy to:" << endl;
		POL::writePol( pol1 );
		ENDL(2);

		cout << "Wielomian drugi to:" << endl;
		POL::writePol( pol2 );
		ENDL(2);



		VD ans;

		POL::multiply( pol1,pol2,ans );

		cout << "A oto wynik mnozenia tych dwoch wielomianow:" << endl;
		POL::writePol( ans );
		ENDL(2);


		cout << "Podaj jakis punkt:  ";
		double d;
		cin >> d;

		cout << "Wartosc wymnozonego wielomianu w punkcie d to:  " << POL::horner( ans,d ) << endl;


		ENDL(3);
		cout << "Press any key" << endl;
		getch();
		system("cls");

	}


	return 0;
}












