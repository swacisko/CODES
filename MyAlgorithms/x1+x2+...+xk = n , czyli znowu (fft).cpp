#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
//#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
//#include<time.h>
//#include<string.h>
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
typedef vector<VD> VVD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<PDD> VPDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;





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
		int N = 1;
		while( N <= M ) N <<= 1;
		N <<= 1;
		//cout << "N = " << N << endl;
		
		a = vector< _T > ( N );
		y2 = vector<_T>(N);
		y = vector<_T>(N);
		REP( i,SIZE(pol1) ) a[i] = _T( pol1[i],0 );
		
		//88888888888888
		//cout << "Wielomian a dla wielomianu pol1" << endl;
		//WRITE(a);
		//ENDL(2);
		//888888888888888
		
		fft( N,1 );
		
		vector<_T> save1; // tutaj jest wyznaczony przez fft pierwszy wektor wspolczynnikiw
		swap( save1,y );
		
		//8888888888
	//	cout << "Wielomian save1, czyli wielomian y wartosci w pierwiastkach z jedynki dla pol1" << endl;
	//	WRITE(save1);
	//	ENDL(2);
		//8888888888
		
		a = vector< _T > ( N );
		y2 = vector<_T>(N);
		y = vector<_T>(N);
		REP( i,SIZE(pol2) ) a[i] = _T( pol2[i],0 );
		
		//8888888888888
		//cout << "Wielomian a dla wielomianu pol2" << endl;
		//WRITE(a);
		//ENDL(2);
		//7777777777777
		
		
		fft( N,1 );
		
		vector<_T> save2;
		swap( save2, y );
		
		//8888888888
		//cout << "Wielomian save2, czyli wielomian y wartosci w pierwiastkach z jedynki dla pol2" << endl;
		//WRITE(save1);
		//ENDL(2);
		//8888888888
		
		vector<_T>ans2(N);
		REP(i,SIZE(save1)) ans2[i] = save1[i]*save2[i];
		
		//8888888888
		//cout << "Oto wymnozone save1*save2" << endl;
		//WRITE(ans2);
		//ENDL(2);
		//8888888888
		
		y2 = vector<_T>(N);
		y = vector<_T>(N);
		swap( ans2,a );
		
		//888
		//cout << "Tuz przed odwracajacym fft mamy tablice a:" << endl;
		//WRITE(a);
		//ENDL(2);
		//888
		
		fft( N,-1 );
		
		//88888
	//	cout << "A teraz wynik odwracania ans2" << endl;
	//	WRITE(y);
	//	ENDL(2);
		//88888
		
		ans = VD( SIZE(y) );
		REP( i,SIZE(y) ) ans[i] = real( y[i] );
		
		int t = SIZE(ans)-1;
		while( t >= 0 && isZero( ans[t--] ) ) ans.pop_back();
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
	
		
}


// funkcja solve_equations
// funkcja wyznacza ilosc rozwiazan rownania x1+x2+...+xk = n w liczbach calkowitych, z ograniczeniami ti <= xi <= Ti dla wszystkich s <= n
// liczby ti oraz Ti moga byc ujemne!
// tutaj k = SIZE(restr)
// funkcja ktora jako parametry przyjmuje ograniczenia na zmienne xi w wektorze restr, oraz wartosc n, do ktorej ma obliczyc ilosci rozwiazan
void solve_eqs( VPII & restr, int n, VI & ans  ){
	int T = 0;
	REP(i,SIZE(restr)) if( restr[i].ST < 0 ){ // jezeli ograniczenia sa liczbami ujemnymi, to dodajemy do n wartosci i zmieniamy ograniczenia na nieujemne
		n -= restr[i].ST;
		T -= restr[i].ST;
		restr[i].ND -= restr[i].ST;
		restr[i].ST = 0;
	}
	
	REP(i,SIZE(restr)) if( restr[i].ND > n ) restr[i].ND = n; // nie ma sensu, aby Ti bylo wieksze od n, bo to i tak bedziemy obcinac
	
	VVD pols(SIZE(restr)); // to sa wielomiany, wielomian k-ty odnosi sie do k-tej zmiennej czyli xk
	REP( i,SIZE(restr) ){ // w tej petli tworze wszystkie wielomiany, tak aby reprezentowaly ograniczenia
		pols[i] = VD( restr[i].ND+1,0 );
		FOR( k,restr[i].ST, restr[i].ND ) pols[i][k] = 1;
	}
	
/*	REP(i,SIZE(pols)){
		cout << "Wielomian pols["<<i<<"] to:   ";
		POL::writePol( pols[i] );
		ENDL(2);
	}*/
	
	
	VD ans2 = pols[0], ans3; // w wektorze ans2 po wymnozeniu wszystkich k wielomianow
	FOR( i,1,SIZE(pols)-1 ){
		ans3.clear();
		
	//	cout << "Jestem przed mnozeniem, wielomian ans2 to:   ";
	//	POL::writePol( ans2 );
	//	ENDL(1);
	//	cout << "Wielomian pols["<<i<<"] to:   ";
	//	POL::writePol( pols[i] );
	//	ENDL(1);		
		
		POL::multiply( ans2,pols[i],ans3 );
		
	//	cout << "\tJestem po mnozeniu, wielomian bedacy ich iloczynem to:   ";
	//	POL::writePol( ans3 );
	//	ENDL(3);
		
		swap( ans2,ans3 );
		ans2.resize( n+1 );
	}
	
	ans = VI( SIZE(ans2) );
	REP(i,SIZE(ans2)) ans[i] = (int) round( ans2[i] );
	
	ans.erase( ans.begin(), ans.begin()+T ); // usuwam pierwsze T wyrazow, bo one reprezentuja ilosc rozwiazan dla n ujemnych
}








int main(){
	ios_base::sync_with_stdio(0);
	cout << fixed;
	cout.precision(1);
	
	cout << "Podaj prosze wartosc n:  ";
	int n;
	cin >> n;
	
	ENDL(1);
	cout << "Podaj teraz prosze wartosc k:  ";
	int k;
	cin >> k;
	
	ENDL(1);
	VPII restr(k);
	REP(i,k){
		cout << "Podaj prosze ograniczenia dla zmiennej x" << i << ":  ";
		cin >> restr[i].ST >> restr[i].ND;
	}
	
	VI ans;
	solve_eqs( restr, n, ans );
	
	cout << "n = " << n << endl;
	REP(i,SIZE(ans)){
		cout << "Ilosc rozwiazan rownania x1 + ... + x" << k << " = " << i << " wynosi: " << ans[i] << endl;
	}
	
	
	return 0;
}












