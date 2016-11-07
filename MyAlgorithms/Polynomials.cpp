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
#include<ctime>
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
const double EPS = 1e-11;
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
    const int M_PI = 3.141592653589;

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
		return ( d >= -EPS && d <= EPS );
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

// funkcja zwraca -1 jesli x < y, 0 jesli x == y oraz 1 jesli x < y
template<class _T>
int compare( const _T x, const _T y, _T _EPS = EPS ){
    if( abs(x-y) < 10*_EPS ) return 0;
    else if(x < y) return -1;
    else return 1;
}

class Poly;
ostream& operator<<( ostream& str, const Poly pol );

class Poly{
public:
    typedef double _T;
    typedef vector<_T> VT;
    explicit Poly( VT & V, bool roots=false ){
        if( roots ) createByRoots(V);
        else coef = V;
    }
    // konstruktor domyslny
    Poly() : coef(VT(0)) {}
    //konstruktor tworzy wielomian o stopniu N o wszystkich wszpolczynnikach rownych val(domyslnie 0)
    explicit Poly( int N, _T val = 0 ) : coef( VT(N+1,val) ) {}

    VT coef; // coef[i] to wspolczynnik przy wyraz x^i

    // funkcja zwraca wielomian  f(x) = ax+b
    static Poly getLinear( _T a, _T b ){
        Poly p(1,0);
        p.coef[1] = a;
        p.coef[0] = b;
        return p;
    }

    //tworzy wielomian o przesłanych jako parametr zerach
    void createByRoots( VT& V ){
        Poly p(0,1);
        REP(i,SIZE(V)) p = p*getLinear(1,-V[i]);
        coef = p.coef;
    }



    // funckja zwraca stopien wielomianu. UWAGA stopien wielomianu jest o 1 mniejszy niz rozmiar tablicy coef!! Dziala w czasie liniowym ze wzgledu na rozmiar wektora coef
    // jesli wielomian jest zerowy, zostanie zwrocona wartosc -INF
    int deg()const{
        FORD(i,SIZE(coef)-1,0){
            if( compare( coef[i],(_T)0 ) != 0 ) return i;
        }
        return -INF;
    }

    // funkcja obcina wielomian tak, aby zaszlo SIZE(coef) = deg, czyli usuwa wszystkie niepotrzebne zera...
    void truncate(){
        int p = SIZE(coef)-1;
        while( p > 0 && compare( coef[p--],(_T)0, 100*EPS ) == 0 ) coef.pop_back();
    }

    // funkcja zwraca pochodna N-tego rzedu danego wielomianu, dziala w czasie liniowym... ze wzgledu na deg-N wielomianu...
    Poly deriv( int N = 1 ){
        int deg;
        if( N == 0 ) return *this;
        else if( N > (deg = this->deg()) ) return Poly(0,0); // zwracam wielomian zerowy...
        Poly pol( deg-N,0 );
        int val = 1;
        FOR(i,1,N) val *= i;
        REP(i,deg-N+1){
            pol.coef[i] = coef[i+N]*val;
            val *= (i+N+1);
            if(i+1>0) val /= i+1;
        }

        pol.truncate();
        return pol;
    }

    // funkcja zwraca wartosc wielomianu w punkcie x, metoda hornera, w czasie O(N)
    _T horner( _T x ){
        if( compare(x,(_T)0) == 0 ) return coef[0];
        _T val = 0;
        FORD( i,SIZE(coef)-1,0 ){
            val *= x;
            val += coef[i];
        }
        return val;
    }

    // funkjca zwraca wielomian stopnia deg o losowych wspolczynnikach, jesli Integers == false, to to wwpolczynniki sa typu double
    static Poly getRandomPoly( int deg, _T scope, bool integers = true ){
        Poly p(deg,0);
       // cout << "getRandomPoly  ->  " << flush;
        REP( i, SIZE(p.coef) ){
            p.coef[i] = (_T) ( rand() % ((int)( scope+2 )) );
            if( i == SIZE(p.coef)-1 ) p.coef[i] += 1;
            else if( rand()%2 ) p.coef[i] = -p.coef[i];
            if( integers == false ) p.coef[i] /= ( _T ) ( (rand()%((int)(scope+2) + 1) ) );
        }
       // cout << "   exit getRandomPoly" << endl;
        return p;
    }

    // return polynomial of form x^n, where n is given as a parameter
    static Poly getSinglePoly( int N ){
        Poly p( N,0 );
        p.coef[N] = 1;
    }


//*******************************************************************************   SEKCJA OPERATOROW...

    // operator przypisania, w zasadzie niepotrzebny, poniewaz nie mam tutaj zadnych wskaznikow ani referencji...
    Poly& operator=( const Poly& pol ){
        coef = pol.coef;
        return *this;
    }

    // funkcja zwraca sume dwoch wielomianow
    Poly operator+( const Poly & pol ) const{
        Poly pol2;
        if( SIZE(coef) > SIZE(pol.coef) ) pol2 = Poly(SIZE(coef));
        else pol2 = Poly(SIZE(pol.coef));

        REP( i,SIZE(coef) ) pol2.coef[i] += coef[i];
        REP(i,SIZE(pol.coef)) pol2.coef[i] += pol.coef[i];

        pol2.truncate();
        return pol2;
    }

    // funkcja zwraca roznice wielomianow moj_wielomian - pol
    Poly operator-( const Poly& pol ) const{
        Poly pol2;
        if( SIZE(coef) > SIZE(pol.coef) ) pol2 = Poly(SIZE(coef));
        else pol2 = Poly(SIZE(pol.coef));

        REP( i,SIZE(coef) ) pol2.coef[i] += coef[i];
        REP(i,SIZE(pol.coef)) pol2.coef[i] -= pol.coef[i];

        pol2.truncate();
        return pol2;
    }

    // funkcja zwraca przez referencje wartosc wspolczynnika przy potedze N
    _T& operator[]( int N ){
        if( N >= SIZE(coef) || N<0 ) {
            cout << "BLAD INDEKSOWANIA W OPERATORZE []" << endl;
            _T T = 0;
            return T;
        }
        return coef[N];
    }

    // zwraca true, jesli dwa wielomiany sa sobie rowne..., liniowy ze wzgledu na dlugosc dwoch wielomianow...
    bool operator==( const Poly& pol ) const{
        if( deg() != pol.deg() ) return false;
        REP( i, min( SIZE(coef), SIZE(pol.coef) ) ) if( compare( coef[i], pol.coef[i] ) != 0 ) return false;
        return true;
    }

    bool operator!=( const Poly& pol )const{
        return !((*this)==pol);
    }

    // operator porownania do intow, zwraca true, jesli coef[0] == N
    bool operator==( int N )const{
        if( SIZE(coef) == 0 ) return false;
        return compare( coef[0],(_T)N ) == 0;
    }

    bool operator!=( int N )const{
        return !((*this)==N);
    }

    // operator mnozenia, zwraca wynik mnozenia dwoch wielomianow. Dziala wolno w czasie O(N^2);
    Poly operator*( const Poly& pol ) const{
        Poly pol2( deg() + pol.deg() );
        REP( i,SIZE(coef) ) REP(k,SIZE(pol.coef)) pol2.coef[i+k] += coef[i]*pol.coef[k];
        return pol2;
    }

    //zwraca wynik mnozenia mnie przez skalar x - np (*this)*5
    Poly operator*( _T x ){
        Poly p( coef );
        REP(i,SIZE(p.coef)) p.coef[i] *= x;
        return p;
    }

    Poly operator<<( int N ){
        Poly p( coef );
        p.coef.resize( p.coef.size()+N );
        FORD( i, p.coef.size()-1,N ) p.coef[i] = p.coef[i-N];
        REP(i,N) p.coef[i] = 0;
        return p;
    }

    // szybkie mnozenie algorytmem FFT w czasie O(NlgN)
    Poly fast_multiplication( const Poly& pol ) const{
        VD pol1( deg()+1 );
        VD pol2( pol.deg()+1 );
        REP(i,SIZE(coef)) pol1[i] = (double) coef[i];
        REP(i,SIZE(pol.coef)) pol2[i] = (double) pol.coef[i];
        VD ans;
      //  cout << "\t\tJESTEM PRZED FFT" << endl;
       // POL::writePol(pol1); cout << endl; POL::writePol(pol2); cout << endl;
        POL::multiply( pol1,pol2,ans );
      //  cout << "\t\tJESTEM PO FFT   ans = "; FORD(i,SIZE(ans)-1,0) cout << ans[i] << " ";
       // ENDL(2);

        Poly res(SIZE(ans)-1);
        REP(i,SIZE(ans) ) res[i] = ans[i];
        return res;
    }

    // niech f - to moj wielomian. Chce go podzielic przez pol, czyli znalezc takie g, ze f = h*pol +r, gdzie deg(r) < deg(pol)
    // niestety dzia³a w czasie O(n^2) ze wzgledu na sume dlugosci dlugosci wielomianow
    // wspolczynnik jest okolo 1/4
    Poly operator/( const Poly& pol ) const{
        int n = deg(), m = pol.deg();
        if( n <= m ) return Poly(1);
        Poly res( deg() - pol.deg() );
        _T val = 0;
        REP( i,n-m+1 ){
            val = coef[n-i];
          //  cout << "m-n-i = " << m-n-i << "   val = " << val << endl;
            FOR(k,1, min(i,m) ) val -= res.coef[n-m-i+k]*pol.coef[m-k];
          //  cout << "val = " << val << endl;
            res.coef[n-m-i] = val / pol.coef[m];
          //  cout << "res.coef[" << m-n-i << "] = " << res.coef[n-m-i] << endl;
        }
        res.truncate();
        return res;
    }

    // funkcja zwraca reszte z dzielenia przez pol, czyli r takie, ze f = h*pol + r oraz deg(r) < deg(pol)
    // dzia³a w czasie O(N^2), ze wspolczynnikiem okolo 1/4
    Poly operator%( const Poly& pol )const{
        Poly pol2 = *this/pol;
        pol2 = *this - pol2*pol;
        return pol2;
    }

    //******************  KARATSUBA MULTIPLICATION

    // when you represent a polynomiual inf the form of A*BASIS^d + B, the function  return polynomial A
    // polynomial must be truncated!
    static Poly getFirstPoly( VT & coef, int d ){
        VT v( d+1,0 );
        int p = d;
        while( p < SIZE(coef) ){
            v[p-d] = coef[p++];
        }
        return Poly(v);
    }
    // when you represent a polynomiual inf the form of A*BASIS^d + B, the function  return polynomial B
    // polynomial must be truncated!
    static Poly getSecondPoly( VT & coef, int d ){
        VT v( d+1,0 );
        int p = 0;
        while( p < d && p < SIZE(coef) ){
            v[p] = coef[p++];
        }
        return Poly(v);
    }

    // multiplies two polynomials using Karatsuba algorithm in asymptotic time of O( n^(3/2) )
    static Poly Karatsuba( Poly st, Poly nd ){
     //   cout << "\t\tKARATSUBA" << endl;
        st.truncate();
        nd.truncate();
        int d1 = st.deg();
        int d2 = nd.deg();
        if( d1 == -INF || d2 == -INF ) return Poly::getLinear(0,0);

        int d = max(d1,d2);
        const int thresholdPoint = 10000;// jesli iloczyn stopni dwóch wielomianów jest nie większy niż to, to mnożę na pałę


        if( d1*d2 <= thresholdPoint ){
            return st*nd;
        }
        else{
            Poly A,B,C,D;
            d = (d+1)/2;

       //     cout << "d = " << d << endl;
       //     cout << endl << "st = " << st << endl;
        //    cout << endl << "nd = " << nd << endl;

            A = getFirstPoly( st.coef,d );
            B = getSecondPoly( st.coef,d );

            C = getFirstPoly( nd.coef,d );
            D = getSecondPoly( nd.coef,d );



        //    cout << endl << "A = " << A << endl;
        //    cout << endl << "B = " << B << endl;

        //    cout << endl << "C = " << C << endl;
        //    cout << endl << "D = " << D << endl;

            Poly AC = Karatsuba( A,C );
            Poly BD = Karatsuba( B,D );
            Poly ABCD = Karatsuba( A+B, C+D ) - AC - BD;


          //  reverse( ALL(AC.coef) );
          //  REP(i,2*d) AC.coef.PB(0);
          //  reverse( ALL(AC.coef) );
          AC.coef.insert( AC.coef.begin(), 2*d, 0 );

         //   reverse( ALL( ABCD.coef ) );
         //   REP(i,d) ABCD.coef.PB(0);
          //  reverse( ALL(ABCD.coef) );
          ABCD.coef.insert( ABCD.coef.begin(), d, 0 );

            return AC + ABCD + BD;

        }



    }


//*****************************************************  LOKALIZACJA ZER - ilosc zer na danym przedziale

    int signChange( vector<Poly> & f, _T a );
    int Sturm( _T, _T );
    int Fourier( _T, _T );
    int Laguerre( _T );


//***************************************************** znajdowanie zer - nie tylko dla wielomianow !!! ale dla innych funkcji trzeba napisac osobna funkcje _T deriv();

    // funkcja zwraca jakies miejsce zerowe danej  funkcji - nie tylko wielomianu(u nas akurat dla wielomianu) - na przedziale (a,b), jesli a*b < 0 i funkcja ta jest ciagla
    // jesli a*b > 0, to funkcja zwraca (double)INF
    // funkcja dziła tak długo, aż b-a < _EPS
    _T bisect( _T a, _T b, _T _EPS = EPS ){
        if( a > b ) swap(a,b);
        _T p = horner(a), q = horner(b);
        if( p*q > 0 ) return (double)INF;
        _T k,val;
        while( b-a > _EPS ){
            k = (a+b)/2;
            if( !compare( (val = horner(k) ),(_T)0, 10*_EPS ) ) return k;
            if( p*k > 0 ){
                p = val;
                a = k;
            }
            else{
                q = val;
                b = k;
            }
        }
        return k;
    }


    // funkcja znajduje najwieksze ( gdy greatest == 1 ) lub najmnijesze ( greatest == false ) miejsce zerowe dla mojego wielomianu, z dokladnoscia do _EPS
    // dziala w czasie O(C*N), gdzie C to ilosc krokow potrzebna na znalezienie miejsca z zadana dokladnoscia... z reguly C jest dosc male, np 10
    // UWAGA, jesli jest bardzo duzy pierwiastek o wartosci X, oraz stopien wielomianu to N, to potrzebuje miec pesymistycznie liczbe, ktora jest zakresu X^N, czyli BigInt
    // dlatego dla nieduzych wielomianow i nieduzych miejsc zerowych (np < 100 ) powinno nawet ladnie dzialac...
    _T newtonsMethod( bool greatest = 1, _T _EPS = EPS ){
        _T INFLOCAL = greatest?100:-100;
        _T k = INFLOCAL, t=INFLOCAL;
        _T val;
        do{
            k = t;
            t = k - ( horner(k) / deriv().horner(k) );
        }while( abs(t-k) > _EPS );
        return t;
    }

    // funkcja znajduje wszystkie zera danego wielomianu... robi to w czasie O( M*N^3 ), gdzie M to liczba miejsc zerowych, a C to średni czas potrzebny na znalezienie miejsca
    // mozna to zredukowac na M*N^3 optymalizujac metode Sturma...
    // zerowego metoda newtona, podobno srednio jest staly...
    VT roots(){
        Poly p = *this;
        _T INFLOCAL = 100; // zmienna taka jak w NewtonsMethod
        VT rts; rts.clear();
        _T rt;
        while( p.Sturm( -INFLOCAL, INFLOCAL ) > 0 ){
            rt = p.newtonsMethod();
         //   cout << "Najwiekszym pierwiastkiem wielomianu " << p << "  jest " << rt << endl;
            rts.PB(rt);
         //   cout << "\tZaraz podziele p przez wielomian " << getLinear(1,-rt) << endl;
         //   cout << "\tTeraz rt = " << rt << endl;
            p = ( p / getLinear(1, -rt ) );
        }
        sort( ALL(rts) );
        return rts;
    }


};

template<class _T>
Poly operator*( _T x, const Poly& pol ){
    return pol*x;
}


ostream& operator<<( ostream& str, const Poly pol ){
    int deg = pol.deg();
    FORD(i,deg,0){
        if( compare( pol.coef[i],(double)0 ) < 0 ) str << " - ";
        else if( i != deg ) str << " + ";
        str << abs( pol.coef[i] );
        if( i > 0 )str << "x^" << i;
    }
    return str;
}







// funkcja potrzebna do algorytmow Sturma, Fouriera oraz KArtezjusza i Laguerre'a
// zwraca ilosc zmian znaku w ciagu f[0],f[1],... w punkcie a
int Poly::signChange( vector<Poly> & f, _T a ){
    int Na=0;
    _T val1 = f[0].horner(a), val2;
    int p = 1;
    while( p < SIZE(f) ){
        val2 = f[p].horner(a);
        if( val1*val2 < -EPS ) Na++;
        if( p < SIZE(f)-1 ){
            if( compare( val2, (_T)0 ) )val1 = val2;
            val2 = f[p+1].horner(a);
        }
        p++;
    }
    return Na;
}

// funkcja zwraca liczbe miejsc zerowych danego wielomianu na przedziale (a,infinity), DLA A > 0 !! lub wartosc od niej mniejsza o parzysta liczbe razy...
// czasowo wychodzi to rzedu O(N^2)
int Poly::Laguerre( _T a ){
    vector<Poly> f; f.clear();
    int k = SIZE(coef)-1;
    f.PB( Poly(0,coef[k--]) );
    FOR(i,1,deg()){
        f.PB( (f.back() << 1 ) + Poly(0, coef[k--] ) );
    }
    return signChange(f,a);


}

// funkcja zwraca liczbe miejsc zerowych danego wielomianu na przedziale (a,b)  lub wartosc od niej mniejsza o parzysta liczbe razy
// działa w czasie O(N^2)
int Poly::Fourier( _T a, _T b ){
    vector<Poly> f; f.clear();
    f.PB(*this);
    REP(i,deg()) f.PB( f[ SIZE(f)-1 ].deriv() );
    return signChange(f,a) - signChange(f,b);
}



// funkcja zwraca liczbe zer danego wielomianu w przedziale (a,b) - dokładną wartosc!!. Algorytm metoda Sturma
// dziala w czasie O(N^3)...   ale mozna zmienic na O(N^2), gdyby tylko sie zamienilo operacje % dzialajaca w czasie O(N^2) na szybciej dzialajaca
// operacje modulo, ktora dzialalaby tak, ze od f[p] odejmowala by  ( 1/f[p].coef.back() ) * f[p+1];
// powinno dzialac, poniewaz bierze sie tutaj tylko znaki liczb...
int Poly::Sturm( _T a, _T b ){
    if( a > b ) swap(a,b);
    vector< Poly > f;
    f.PB( *this );
    Poly rest = (*this).deriv();
    int p = 0;
    while( rest != 0 ){
   //   cout << "rest = " << rest << endl;
        f.PB(rest);
        rest = ( f[p] % f[p+1] )*(-1);
        p++;
    }

  //  cout << "Oto tablica reszt f:" << endl;
  //  REP(i,SIZE(f)) cout << f[i] << endl;

    return signChange(f,a) - signChange(f,b);
}


// szablon funkcji, ktora zwraca wielomian interpolacyjny dla danych danych
// nodes - wektor typu xs, okreslajacy w jakis punktach badamy wartosci
// values[i] - wartosc funkcji w punkcie nodes[i]
template<class xs, class _T>
Poly interpolationNewton( vector<xs> &nodes, vector<_T> values ){
    typedef vector<_T> VT;
    typedef vector< VT > VVT;
    if( nodes.size() == 1 ) return Poly(0,values[0]);

    VVT bcoef( SIZE(nodes), VT( SIZE(nodes)+1 ,0) );
    REP(i,SIZE(nodes)) bcoef[i][0] = nodes[i];
    REP(i,SIZE(values)) bcoef[i][1] = values[i];

    int N = SIZE(nodes);
    FOR( i,2,N ){
        REP( k,N-i+1 ){
            bcoef[k][i] = ( bcoef[k+1][i-1] - bcoef[k][i-1] ) / ( bcoef[k+i-1][0] - bcoef[k][0] );
        }
    }

  /*  cout << "Oto tablica bcoef:" << endl;
    REP(i,SIZE(bcoef)){
        REP(k,SIZE(bcoef[i])) cout << setw(5) << bcoef[i][k] << " ";
        cout << endl;
    }*/

    Poly p(0,1), ans(0,0);
    FOR(i,1,N){
    //    cout << "wielomian p to " << p << endl;
        ans = ans + p*bcoef[0][i];
        p = p*(Poly::getLinear( 1, -bcoef[i-1][0] ) );
    }

    return ans;
}






int main(){
	ios_base::sync_with_stdio(0);
	srand( unsigned (time(0)) );
	cout << fixed;
	cout.precision(2);

	/*while( 1 ){
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

	}*/

//******************************************  TESTOWANIE KLASY POLY

   /* while( 1 ){
		Poly pol1, pol2;

		cout << "Podaj stopien pierwszego wielomianu:  ";
		int n1;
		cin >> n1;
		REP(i,n1+1){
			cout << "\tPodaj wartosc wspolczynnika przy " << i << "-tej potedze: ";
			double d;
			cin >> d;
			pol1.coef.PB(d);
		}

		ENDL(2);

		cout << "Podaj stopien drugiego wielomianu:  ";
		int n2;
		cin >> n2;
		REP(i,n2+1){
			cout << "\tPodaj wartosc wspolczynnika przy " << i << "-tej potedze: ";
			double d;
			cin >> d;
			pol2.coef.PB(d);
		}

        ENDL(2);
		cout << "Wielomian pierwszy to: " << pol1 << endl;

		cout << "Wielomian drugi to: " << pol2 << endl;


		cout << "suma wielomianow to: " << pol1+pol2 << endl;
		cout << endl << "roznica wielomianow to: " << (pol1-pol2) << endl;

        ENDL(2);
        Poly res;
		cout << "A oto wynik mnozenia tych dwoch wielomianow: " << (res = pol1*pol2) << endl;

		cout << "A oto wielomian bedacy wynikiem mnozenia FFT: " << (res = pol1.fast_multiplication(pol2) ) << endl;

        Poly pol3;
        cout << "A oto wielomian pol3, ktorego pierwiastkami sa wspolczynniki wielomianu pol1:\t" << (pol3 = Poly( pol1.coef,1 ) )<< endl;
        cout << "Oto pochodna tego wielomianu:\t" << pol3.deriv() << endl;
        cout << "Podaj dwa punkty a oraz b dla badania liczby miejsc zerowych:\t";
        double a,b;
        cin >> a >> b;
        cout << "Liczba miejsc zerowych metoda Sturma     wielomianu pol3 na przedziale (" << a << "," << b << ") wynosi " << pol3.Sturm(a,b) << endl;
        cout << "Liczba miejsc zerowych metoda Fouriera   wielomianu pol3 na przedziale (" << a << "," << b << ") wynosi " << pol3.Fourier(a,b) << endl;
        cout << "Liczba miejsc zerowych metoda Laguerre'a wielomianu pol3 na przedziale (" << a << ",infinity) wynosi " << pol3.Laguerre(a) << endl;

        cout << "A oto miejsca zerowe Twojego wielomianu pol3:\t" << flush;
        VD roots = pol3.roots();
        REP(i,SIZE(roots)) cout << roots[i] << "  ";
        cout << endl;


        ENDL(2);
		cout << "Podaj jakis punkt:  ";
		double d;
		cin >> d;

		cout << "Wartosc wymnozonego wielomianu w punkcie d to:  " << res.horner(d);

        ENDL(2);
        cout << "Wielomian bedacy wynikiem dzielenia wielomianu pol1 przez pol2 to: " << ( res = (pol1/pol2)) << endl;

        ENDL(2);
        cout << "A to reszta z dzielenia pol1 przez pol2:\t" << pol1%pol2 << endl;*/




       /* cout << "TERAZ INTERPOLACJA NEWTONA\nPodaj ile punktow chcesz interpolowac:\t";
        int N;
        cin >> N;
        cout << "Podawaj teraz po kolei pary ( x, f(x) )" << endl;
        double a,b;
        VD nodes, values;
        REP(i,N){
            cout << "Podaj " << i+1 << " pare:\t";
            cin >> a >> b;
            nodes.PB(a);
            values.PB(b);
        }

        ENDL(3);
        cout << "Oto wielomian interpolacyjny:" << endl;
        Poly interp = interpolationNewton( nodes, values );
        cout << interp << endl;
        cout << "A teraz sprawdzenie:" << endl;
        REP(i,N){
            double val = interp.horner( nodes[i] );
            cout << "Wartosc wielomianu interpolacyjnego w punkcie " << nodes[i] << "  wynosi " << setw(10) << val << flush;
            if( compare( val,values[i], 1000*EPS )==0 ) cout << "   Zgadza sie!!" << endl;
            else cout << "   BLAD!!!" << endl;
        }*/
//******************************************************************

    /*
    cout << "TESTOWANIE CZASU DZIALANIA" << endl;
    vector< Poly > polys;
    int ILE = 3;
    REP(i,ILE) polys.PB( Poly::getRandomPoly( 10*i,10,false ) );

    double time1=0, time2=0, t;
    cout << "Stworzylem losowe wielomiany" << endl;
    vector<Poly> ans1,ans2;
    t=clock();
    REP( i,SIZE(polys)-1 ){
        if( i%10 == 0 ) cout << "Mnozenie nr " << i << endl;
        ans1.PB( polys[i]*polys[i+1] );
    }

    time1 = (clock()-t) / CLOCKS_PER_SEC;
     cout << "Algorytmem naiwnym zajelo to czas " << time1 << endl;

    t=clock();
    REP( i,SIZE(polys)-1 ){
        if( i%10 == 0 ) cout << "Mnozenie nr " << i << endl;
        ans2.PB( polys[i].fast_multiplication( polys[i+1] ) );
    }

    time2 = ( clock()-t ) / CLOCKS_PER_SEC;

    cout << "Algorytmem FFT zajelo to czas " << time2 << endl;

    ENDL(2);
    cout << "Teraz zbadam poprawnosc:" << endl;
    REP( i,SIZE(ans1) ) if( ans1[i] != ans2[i] ) cout << "Wielomiany " << ans1[i] << endl << endl << endl << "   oraz   " << ans2[i] << endl; */


	/*	ENDL(3);
		cout << "Press any key" << endl;
		getch();
		system("cls");
	}*/



    //*********************  SPRAWDZANIE MNOŻENIA KARATSUBY

    int ZESTAWY = 10000;
    int WYMIAR = 10000;
    int ZAKRES = 10;
    while( ZESTAWY-- ){
        Poly P = Poly::getRandomPoly( rand()%WYMIAR + 5, ZAKRES );
        Poly Q = Poly::getRandomPoly( rand()%WYMIAR + 5, ZAKRES );

       // cout << "Oto twoje dwa losowe wielomiany P oraz Q:" << endl;
     //   cout << "P = " << endl << P << endl << "Q = " << endl << Q << endl;
      //  ENDL(2);

        Poly PQ = P*Q;
        cout << "A" << flush;
        Poly K = Poly::Karatsuba(P,Q);
        cout << "B " << flush;


        if( PQ != K ){
            cout << "Roznice przy mnożeniu!!" << endl;

         //   cout << "Oto wynik mnozenia metoda N^2:" << endl << PQ << endl;
         //   cout << endl << "A teraz wynik mnozenia Karatsuba:" << endl << K << endl;
        }

    }






    //********************


	return 0;
}












