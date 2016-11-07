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

const bool show_help = 1;
const int INF = 1000000001;
int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef map< PII, bool > MPIIB;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

// Makro wyznacza wartosc iloczynu wektorowego (a -> b)*(a -> c)
#define Det(a,b,c) (LL(b.x-a.x)*LL(c.y-a.y)-LL(b.y-a.y)*(c.x-a.x))
#define PointInsideRect(p1,p2,p3) ((p1.x <? p2.x) < p3.x && \
(p1.y <? p2.y) < p3.y && (p1.x >? p2.x) > p3.x && (p1.y >? p2.y) > p3.y)

#define PointInRect(p1,p2,p3) ( min(p1.x, p2.x) <= p3.x && \
	min(p1.y, p2.y) <= p3.y && max(p1.x, p2.x) >= p3.x && max(p1.y, p2.y) >= p3.y)

#define PointInsideSegment(p1,p2,l) (Det(p1,p2,l)==0 && PointInsideRect(p1,p2,l))

#define PointInSegment(p1,p2,l) ( Det(p1,p2,l)==0 && PointInRect(p1,p2,l) )

#define PointInsideCircle(c,r,p) (sqr(c.x-p.x)+sqr(c.y-p.y) < sqr(r))

#define PointInCircle(c,r,p) (sqr(c.x-p.x)+sqr(c.y-p.y) <= sqr(r))

#define sqr(x) ( (x) * (x) )

// Struktura reprezentujaca punkt o wsp�rzednych ca�kowitoliczbowych
struct POINT {
	 int x, y;
	// Konstruktor punktu pozwalajacy na skr�cenie zapisu wielu funkcji
	// wykorzystujacych punkty - w szczeg�lnosci operacje wstawiania punkt�w do
	// struktur danych
	 POINT(int x = 0, int y = 0) : x(x), y(y) { }
	// Operator sprawdzajacy, czy dwa punkty sa sobie r�wne.
	 bool operator ==(POINT & a) {
	 return a.x == x && a.y == y;
	 }
};


// Operator uzywany przez przyk�adowe programy do wypisywania struktury punktu
ostream & operator<<(ostream & a, POINT & p) {
	a << "(" << p.x << ", " << p.y << ")";
	return a;
}

// Funkcja sprawdza, czy podana liczba jest dostatecznie bliska 0
inline bool IsZero(double x) {
	return x >= -EPS && x <= EPS;
}

// Struktura reprezentujaca punkt o wsp�rzednych rzeczywistych
struct POINTD {
	double x, y;
	// Konstruktor punktu
	POINTD(double wx = 0, double wy = 0) : x(wx), y(wy) { }
	// Konstruktor POINTD z typu POINT - jest on potrzebny w celu wykonywania
	// automatycznej konwersji miedzy POINT a POINTD.
	POINTD(const POINT & p) : x(p.x), y(p.y) { }
	// Operator sprawdzajacy, czy dwa punkty sa sobie r�wne. Ze wzgledu na
	// reprezentowanie wsp�rzednych punkt�w przy uzyciu zmiennych double,
	// operator por�wnuje wsp�rzedne punkt�w z pewna tolerancja
	bool operator ==(POINTD & a) {
		return IsZero(a.x - x) && IsZero(a.y - y);
	}
};
// Operator uzywany przez przyk�adowe programy do wypisywania struktury punktu
ostream & operator<<(ostream & a, POINTD & p) {
	a << "(" << p.x << ", " << p.y << ")";
	return a;
}


// Operator okreslajacy liniowy porzadek na zbiorze punkt�w po wsp�rzednych
// (x, y)
bool OrdXY(POINT * a, POINT * b) {
	return a->x == b->x ? a->y < b->y : a->x < b->x;
}

// Operator okreslajacy liniowy porzadek na zbiorze punkt�w po wsp�rzednych
// (y, x)
bool OrdYX(POINT * a, POINT * b) {
	return a->y == b->y ? a->x < b->x : a->y < b->y;
}


// Funkcja wyznacza odleg�osc punktu p od prostej (p1 -> p2)
double PointLineDist(POINTD p1, POINTD p2, POINTD p) {
	double A = p2.y - p1.y, B = p2.x - p1.x;
	return abs(A * (p1.x - p.x) + B * (p.y - p1.y)) / sqrt(A * A + B * B);
}

// Funkcja liczy pole powierzchni wielokata, kt�rego wierzcho�ki wyznaczone sa
// przez wektor p
double PolygonArea(vector<POINT> &p) {
	double area = 0;
	int s = SIZE(p);
	REP(x, s) area += (p[x].x + p[(x + 1) % s].x) * (p[x].y - p[(x + 1) % s].y);
	return abs(area) / 2;
}

#define sgn(x) ( (x) < 0 ? -1 : ( (x) > 0 ? 1 : 0 )  )

inline int SegmentCross(POINT p1, POINT p2, POINT l1, POINT l2 ) {
	 int w1 = sgn(Det(p1, p2, l1)), w2 = sgn(Det(p1, p2, l2)),
	 v1 = sgn(Det(l1, l2, p1)), v2 = sgn(Det(l1, l2, p2));
	// Jesli punkty l1 i l2 znajduja sie po tej samej stronie prostej p1 -> p2
	// lub p1 i p2 znajduja sie po tej samej stronie prostej l1 -> l2,
	// to odcinki nie przecinaja sie
	 if (w1*w2 > 0 || v1*v2 > 0) return 0;
	// Jesli punkty l1 i l2 leza na prostej p1 -> p2, to odcinki
	// l1 -> l2 i p1 -> p2 sa wsp�liniowe
	 return 1;
}

// przynaleznosc punktu do wielokata
bool PointInsidePol(vector<POINT> &l, POINT p) {
	int v = 0, s = SIZE(l);
	POINT d(INF, p.y + 1);
	// Jesli punkt lezy na jednym z bok�w wielokata, to nie nalezy do wnetrza
	// wielokata
	REP(x, s) if ( PointInSegment(l[x], l[(x + 1) % s], p) ) return false;
	// Wyznacz liczbe przeciec obwodu wielokata z p�prosta (p -> d)
	REP(x, s) v += SegmentCross(p, d, l[x], l[(x + 1) % s]);
	// Jesli p�prosta przecina obw�d nieparzysta liczbe razy, to punkt nalezy do
	// wielokata
	return v & 1;
}


bool PointInPol(vector<POINT> &l, POINT p) {
	int v = 0, s = SIZE(l);
	POINT d(INF, p.y + 1);
	// Jesli punkt lezy na jednym z bok�w wielokata, to zwr�c prawde
	REP(x, s) if (PointInSegment(l[x], l[(x + 1) % s], p)) return true;
	// Wyznacz liczbe przeciec obwodu wielokata z p�prosta (p -> d)
	REP(x, s) v += SegmentCross(p, d, l[x], l[(x + 1) % s]);
	// Jesli p�prosta przecina obw�d nieparzysta liczbe razy, to punkt nalezy do
	// wielokata
	return v & 1;
}


// przynaleznosc punktu do wielokata wypuklego w czasie logarytmicznym
bool PointInsideConvexPol(vector<POINT> &l, POINT p) {
	int a = 1, b = SIZE(l) - 1, c;
	// Jesli odcinek (l[0] -> l[a]) lezy na prawo od odcinka (l[0] -> l[b]) to
	// nastepuje zamiana
	if (Det(l[0], l[a], l[b]) > 0) swap(a, b);
	// Jesli punkt p nie lezy po prawej stronie prostej (l[0] -> l[a]) lub po
	// lewej stronie (l[0] -> l[b]) to nie nalezy do wielokata
	if (Det(l[0], l[a], p) >= 0 || Det(l[0], l[b], p) <= 0) return false;
	// Wyszukiwanie binarne wycinka p�aszczyzny zawierajacego punkt p
	while (abs(a - b) > 1) {
		c = (a + b) / 2;
		if (Det(l[0], l[c], p) > 0) b = c;
		else a = c;
	}
	// Jesli punkt p lezy w tr�jkacie (l[0],l[a],l[b]), to nalezy do wielokata
	return Det(l[a], l[b], p) < 0;
}


bool PointInConvexPol(vector<POINT> &l, POINT p) {
	int a = 1, b = SIZE(l) - 1, c;
	// Jesli odcinek (l[0] -> l[a]) lezy na prawo od odcinka (l[0] -> l[b]) to
	// nastepuje zamiana
	if (Det(l[0], l[a], l[b]) > 0) swap(a, b);
	// Jesli punkt p lezy po lewej stronie prostej (l[0] -> l[a]) lub po
	// prawej stronie (l[0] -> l[b]) to nie nalezy do wielokata
	if (Det(l[0], l[a], p) > 0 || Det(l[0], l[b], p) < 0) return false;
	// Wyszukiwanie binarne wycinka p�aszczyzny zawierajacego punkt p
	while (abs(a - b) > 1) {
		c = (a + b) / 2;
		if (Det(l[0], l[c], p) > 0) b = c;
		else a = c;
	}
	// Jesli punkt p lezy w tr�jkacie (l[0],l[a],l[b]), to nalezy do wielokata
	return Det(l[a], l[b], p) <= 0;
}


// wyznaczanie punktow przeciecia dwoh prostych
int LineCrossPoint(POINTD p1, POINTD p2, POINTD l1, POINTD l2, POINTD & prz) {
	// Iloczyn wektorowy (p1 -> p2) i (l1 -> l2)
	 LL t = LL(p1.x - p2.x) * LL(l1.y - l2.y) - LL(p1.y - p2.y) * LL(l1.x - l2.x);
	// Iloczyn wektorowy (l2 -> p2) i (l1 -> l2)
	 LL s = LL(l2.x - p2.x) * LL(l1.y - l2.y) - LL(l2.y - p2.y) * LL(l1.x - l2.x);
	// Jesli proste sa r�wnoleg�e (t == 0), to istnieje nieskonczenie wiele
	// punkt�w wsp�lnych wtw. gdy proste sie pokrywaja (iloczyn wektorowy s == 0)
	 if (!t) return s ? 0 : 2;
	 double w = double (s) / double (t);
	// Istnieje jeden punkt wsp�lny - wyznacz jego wsp�rzedne
	 prz.x = w * p1.x + (1 - w) * p2.x;
	 prz.y = w * p1.y + (1 - w) * p2.y;
	 return 1;
}



// wyznaczanie punktu przeciecia sie dwoch odcinkow
inline bool SegmentCrossPoint(POINT p1, POINT p2, POINT l1, POINT l2,
	 vector<POINTD> &r) {
	 r.clear();
	 int w1 = sgn(Det(p1, p2, l1)), w2 = sgn(Det(p1, p2, l2)),
	 v1 = sgn(Det(l1, l2, p1)), v2 = sgn(Det(l1, l2, p2));
	// Jesli punkty l1 i l2 znajduja sie po tej samej stronie prostej p1 -> p2
	// lub p1 i p2 znajduja sie po tej samej stronie prostej l1 -> l2,
	// to odcinki nie przecinaja sie
	 if (w1*w2 > 0 || v1*v2 > 0) return false;
	// Jesli punkty l1 i l2 leza na prostej p1 -> p2, to odcinki
	// l1 -> l2 i p1 -> p2 sa wsp�liniowe
	 if (!w1 && !w2) {
		// Zamiana par punkt�w reprezentujacych odcinki, tak aby pierwsze punkty
		// w parach by�y mniejsze w porzadku po wsp�rzednych (x,y)
		 if (OrdXY(&p2, &p1)) swap(p1, p2);
		 if (OrdXY(&l2, &l1)) swap(l1, l2);
		// Jesli odcinki sa roz�aczne, to nie ma punkt�w przeciecia
		 if (OrdXY(&p2, &l1) || OrdXY(&l2,&p1)) return false;
		// Wyznacz krancowe punkty wsp�lne
		 if (p2 == l1) r.PB(POINTD(p2.x, p2.y));
		 else if (p1 == l2) r.PB(POINTD(l2.x, l2.y));
		 else {
			 r.PB(OrdXY(&p1, &l1) ? l1 : p1);
			 r.PB(OrdXY(&p2, &l2) ? p2 : l2);
		 }
	 }
	// Jesli jeden z odcink�w jest zdegenerowany, to jest on punktem przeciecia
	 else if (l1 == l2) r.PB(l1);
	 else if (p1 == p2) r.PB(p2);
	 else {
	// Wyznacz punkt przeciecia
		 double t = double(LL(l2.x - p2.x) * LL(l1.y - l2.y) - LL(l2.y - p2.y) * (l1.x - l2.x)) / double(LL(p1.x - p2.x) * LL(l1.y - l2.y) - LL(p1.y - p2.y) * LL(l1.x -l2.x));
		 r.PB(POINTD(t * p1.x + (1.0 - t) * p2.x, t * p1.y + (1.0 - t) * p2.y));
	 }
	 return true;
}


// wyznaczanie punktow przeciecia okregu i prostej
vector<POINTD> LineCircleCross(POINTD p, double cr, POINTD p1, POINTD p2){
	 double a = sqr(p1.x) + sqr(p1.y) + sqr(p2.x) + sqr(p2.y) -	 2.0 * (p1.x * p2.x + p1.y * p2.y);
	 double b = 2.0 * (p.x * (p2.x - p1.x) + p.y * (p2.y - p1.y) +  p1.x * p2.x + p1.y * p2.y - sqr(p2.x)-sqr(p2.y));
	 double c = -sqr(cr) + sqr(p2.x) + sqr(p2.y) + sqr(p.x) + sqr(p.y) - 2.0 * (p.x * p2.x + p.y * p2.y);
	 double d = b * b - 4.0 * a * c;
	 vector<POINTD> r;
	// Jesli nie istnieje rozwiazanie r�wnania kwadratowego,
	// to brak punkt�w przeciecia
	 if (d < -EPS) return r;
	 double t = -b / (2.0 * a), e = sqrt(abs(d)) / (2.0 * a);
	 if (IsZero(d))
		// Istnieje tylko jeden punkt przeciecia...
	 	r.PB(POINTD(t * p1.x + (1.0 - t) * p2.x, t * p1.y + (1.0 - t) * p2.y));
	 else {
		// Istnieja dwa punkty przeciecia
		 r.PB(POINTD((t + e) * p1.x + (1.0 - t - e) * p2.x,	 (t + e) * p1.y + (1.0 - t - e) * p2.y));
		 r.PB(POINTD((t - e) * p1.x + (1.0 - t + e) * p2.x,	 (t - e) * p1.y + (1.0 - t + e) * p2.y));
	 }
	 return r;
}


// wyznaczenie przeciecia dwoch okregow
vector<POINTD> CirclesCross(POINTD c1, double c1r, POINTD c2, double c2r) {
	 vector<POINTD> r;
	 c2.x -= c1.x;
	 c2.y -= c1.y;
	// Jesli okregi sa wsp�srodkowe, to nie wyznaczamy punkt�w przeciecia
	 if (IsZero(c2.x) && IsZero(c2.y)) return r;
	 double A = (-sqr(c2r) + sqr(c1r) + sqr(c2.x) + sqr(c2.y)) / 2.0;
	// Jesli srodki okreg�w maja ta sama wsp�rzedna y...
	 if (IsZero(c2.y)) {
		 double x = A / c2.x;
		 double y2 = sqr(c1r) - sqr(x);
		 if (y2 < -EPS) return r;
		// Jesli okregi sa styczne...
		 if (IsZero(y2)) r.PB(POINTD(c1.x + x, c1.y));
		 else {
			// Okregi przecinaja sie
			 r.PB(POINTD(c1.x + x, c1.y + sqrt(y2)));
			 r.PB(POINTD(c1.x + x, c1.y - sqrt(y2)));
		 }
		 return r;
	 }
	 double a = sqr(c2.x) + sqr(c2.y);
	 double b = -2.0 * A * c2.x;
	 double c = A * A - sqr(c1r) * sqr(c2.y);
	 double d = b * b - 4.0 * a * c;
	 if (d < -EPS) return r;
	 double x = -b / (2.0 * a);
	// Jesli okregi sa styczne...
	 if (IsZero(d)) r.PB(POINTD(c1.x + x, c1.y + (A - c2.x * x) / c2.y));
	 else {
		// Okregi przecinaja sie
		 double e = sqrt(d) / (2.0 * a);
		 r.PB(POINTD(c1.x + x + e, c1.y + (A - c2.x * (x + e)) / c2.y));
		 r.PB(POINTD(c1.x + x - e, c1.y + (A - c2.x * (x - e)) / c2.y));
	 }
	 return r;
}


// Funkcja znajduje okrag wyznaczony przez trzy punkty lub zwraca fa�sz,
// jesli taki okrag nie istnieje
bool ThreePointCircle(POINTD p1, POINTD p2, POINTD p3, POINTD &c, double &r){
	// Wyznacz punkt przeciecia symetralnych tr�jkata (p1, p2, p3)
	 if (LineCrossPoint(POINTD((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0), POINTD((p1.x + p2.x) / 2.0 + p2.y - p1.y, (p1.y + p2.y) / 2.0 + p1.x - p2.x), 
	 POINTD((p1.x + p3.x) / 2.0, (p1.y + p3.y) / 2.0),	 POINTD((p1.x + p2.x) / 2.0 + p3.y - p1.y,	 (p1.y + p3.y) / 2.0 + p1.x - p3.x) ,c) != 1 )	 return false;
	// Wylicz promien okregu o srodku w punkcie c
	 r = sqrt(sqr(p1.x - c.x) + sqr(p1.y - c.y));
	 return true;
}



// otoczka wypukla
#define XCAL {while(SIZE(w) > m && Det((*w[SIZE(w) - 2]), (*w[SIZE(w) - 1]), \
 (*s[x])) <= 0) w.pop_back(); w.PB(s[x]);}
// Funkcja wyznaczajaca wypuk�a otoczke dla zbioru punkt�w
vector<POINT*> ConvexHull(vector<POINT>& p) {
	 vector<POINT*> s, w;
	// Wype�nij wektor s wskaznikami do punkt�w, dla kt�rych konstruowana jest wypuk�aotoczka
	 FOREACH(it, p) s.PB(&*it);
	// Posortuj wskazniki punkt�w w kolejnosci (niemalejace wsp�rzedne x, niemalejace wsp�rzedne y)
	 sort(ALL(s), OrdXY);
	 int m = 1;
	// Wyznacz dolna czesc wypuk�ej otoczki - �aczaca najbardziej lewy - dolny punkt z najbardziej prawym - g�rnym punktem
	 REP(x, SIZE(s)) XCAL
	 m = SIZE(w);
	// Wyznacz g�rna czesc otoczki
	 FORD(x, SIZE(s) - 2, 0) XCAL
	// Usun ostatni punkt (zosta� on wstawiony do otoczki dwa razy)
	 w.pop_back();
	 return w;
}



// sortowanie katowe
// Wskaznik na punkt centralny (uzywane przez funkcje por�wnujaca)
POINT* RSK;
// Funkcja por�wnujaca punkty
bool Rcmp(POINT *a, POINT *b) {
	 LL w = Det((*RSK), (*a), (*b));
	 if (w == 0) return abs(RSK->x - a->x) + abs(RSK->y - a->y) < abs(RSK->x - b->x) + abs(RSK->y - b->y);
	 return w > 0;
}
// Funkcja sortuje po kacie odchylenia zbi�r punkt�w wzgledem punktu centralnego
// s zaczynajac od wektora s -> k
vector<POINT*> AngleSort(vector<POINT>& p, POINT s, POINT k) {
	 RSK = &s;
	 vector<POINT*> l, r;
	// Kazdy punkt, kt�ry podlega sortowaniu, zostaje wstawiony do jednego
	// z wektor�w l lub r, w zaleznosci od tego,
	// czy znajduje sie po lewej czy po prawej stronie prostej s -> k
	 FOREACH(it, p) {
		 LL d = Det(s, k, (*it));
		 (d > 0 || (d==0 &&	 (s.x == it->x ? s.y < it->y : s.x < it->x))) ? l.PB(&*it) : r.PB(&*it);
	 }
	// Posortuj niezaleznie punkty w obu wyznaczonych wektorach
	 sort(ALL(l), Rcmp);
	 sort(ALL(r), Rcmp);
	// Wstaw wszystkie punkty z wektora r na koniec wektora l
	 FOREACH(it, r) l.PB(*it);
	 return l;
}



// para najblizszych punktow
struct NearestPoints {
	 vector<POINT *> l;
	// Wskazniki na dwa punkty, stanowiace znaleziona pare najblizszych punkt�w
	 POINT *p1, *p2;
	// Odleg�osc miedzy punktami p1 i p2
	 double dist;
	// Funkcja usuwa z listy l wszystkie punkty, kt�rych odleg�osc od prostej
	// x=p jest wieksza od odleg�osci miedzy para aktualnie znalezionych
	// najblizszych punkt�w
	 void Filter(vector<POINT *> &l, double p) {
		 int s = 0;
		 REP(x, SIZE(l)) if (sqr(l[x]->x - p) <= dist) l[s++] = l[x];
		 l.resize(s);
	 }
	// Funkcja realizuje faze dziel i rzadz dla zbioru punkt�w z wektora l od
	// pozycji p do k. Wektor ys zawiera punkty z przetwarzanego zbioru
	// posortowane w kolejnosci niemalejacych wsp�rzednych y
	 void Calc(int p, int k, vector<POINT *> &ys) {
		// Jesli zbi�r zawiera wiecej niz jeden punkt, to nastepuje faza podzia�u
		 if (k - p > 1) {
			 vector<POINT *> lp, rp;
			// Wyznacz punkt podzia�u zbioru
			 int c = (k + p - 1) / 2;
			// Podziel wektor ys na dwa zawierajace odpowiednio punkty na lewo oraz
			// na prawo od punktu l[c]
			 FOREACH(it, ys) if (OrdXY(l[c], *it)) rp.PB(*it);
			 			else lp.PB(*it);
			// Wykonaj faze podzia��w
			 Calc(p, c + 1, lp);
			 Calc(c + 1, k, rp);
			// Nastepuje faza scalania. Najpierw z wektor�w l i r usuwane sa
			// punkty po�ozone zbyt daleko od prostej wyznaczajacej podzia� zbior�w
			 Filter(lp, l[c]->x);
			 Filter(rp, l[c]->x);
			 int p = 0;
			 double k;
			// Nastepuje faza wyznaczania odleg�osci pomiedzy kolejnymi parami punkt�w,
			// kt�re moga polepszyc aktualny wynik
			 FOREACH(it, lp) {
			 	while(p < SIZE(rp) - 1 && rp[p + 1]->y < (*it)->y) p++;
			 	FOR(x, max(0, p - 2), min(SIZE(rp) - 1, p + 1))
			// Jesli odleg�osc miedzy para przetwarzanych punkt�w jest mniejsza od
			// aktualnego wyniku, to zaktualizuj wynik
			 		if (dist > (k = sqr((*it)->x - rp[x]->x) + sqr((*it)->y - rp[x]->y))){
						 dist = k;
						 p1 = (*it);
						 p2 = rp[x];
					}
			 }
		 }
	 }
	// Konstruktor struktury NearestPoints wyznaczajacy pare najblizszych punkt�w
	 NearestPoints(vector<POINT> &p) {
		// Wype�nij wektor l wskaznikami do punkt�w z wektora p oraz posortuj te
		// wskazniki w kolejnosci niemalejacych wsp�rzednych x
		 FOREACH(it, p) l.PB(&(*it));
		 sort(ALL(l), OrdXY);
		// Jesli w zbiorze istnieja dwa punkty o tych samych wsp�rzednych, to punkty
		// te sa poszukiwanym wynikiem
		 FOR(x, 1, SIZE(l) - 1)
			 if (l[x - 1]->x == l[x]->x && l[x - 1]->y == l[x]->y) {
				 dist = 0;
				 p1 = l[x - 1];
				 p2 = l[x];
				 return;
			 }
		 dist = double (INF) * double (INF);
		// Skonstruuj kopie wektora wskaznik�w do punkt�w i posortuj go w kolejnosci
		// niemalejacych wsp�rzednych y
		 vector<POINT *> v = l;
		 sort(ALL(v), OrdYX);
		// Wykonaj faze dziel i rzadz dla wszystkich punkt�w ze zbioru
		 Calc(0, SIZE(l), v);
		 dist = sqrt(dist);
	 }
};






int main(){
	/*
	// odleglosc punktu od prostej
	POINT l1, l2, p;
	// Wczytaj pozycje punk�w wyznaczajacych prosta
	 cin >> l1.x >> l1.y >> l2.x >> l2.y;
	// Dla wszystkich punkt�w wyznacz odleg�osc od prostej
	 while(cin >> p.x >> p.y)
	 cout << "Odleglosc punktu " << p << " od prostej (" <<	 l1 << "," << l2 << ") wynosi " << PointLineDist(l1, l2, p) << endl;
	 return 0;
	*/
	
	/*
	// pole powierzchni wielokata
	 int n;
	 vector<POINT> l;
	 POINT p;
	// Wczytaj liczbe wierzcho�k�w wielokata
	 cin >> n;
	// Dodaj wszystkie wierzcho�ki wielokata do wektora punkt�w
	 REP(x, n) {
		 cin >> p.x >> p.y;
		 l.PB(p);
	 }
	// Wyznacz pole powierzchni wielokata
	 cout << "Pole powierzchni wielokata: " << PolygonArea(l) << endl;
	 return 0;
	*/
	
	/*
	// przynaleznosc punktu do prostaokata i kola
	 POINT r1,r2,c,s1,s2,p;
	 int r;
	// Wczytaj wsp�rzedne wierzcho�k�w wyznaczajacych prostokat
	 cin >> r1.x >> r1.y >> r2.x >> r2.y;
	// Wczytaj wsp�rzedne punkt�w wyznaczajacych odcinek
	 cin >> s1.x >> s1.y >> s2.x >> s2.y;
	// Wczytaj srodek oraz promien okregu
	 cin >> c.x >> c.y >> r;
	 cout << "\t\t\t Rectangle\t\t Segment\t\t Circle" << endl;
	 cout << "\t\t\tInside\t In\t Inside\t In\t Inside\t In" << endl;
	// Dla wszystkich punkt�w wyznacz wynik dzia�ania poszczeg�lnych makr
	 while(cin >> p.x >> p.y) {
		 cout << p << "\t\t" << PointInsideRect(r1, r2, p) << "\t\t" <<
		 PointInRect(r1, r2, p) << "\t\t" <<
		 PointInsideSegment(s1, s2, p) << "\t\t" <<
		 PointInSegment(s1, s2, p) << "\t\t" <<
		 PointInsideCircle(c, r, p) << "\t\t" <<
		 PointInCircle(c, r, p) << endl;
	 }
	 return 0;
	*/
	
	/*
	// przynaleznosc punktu do wielokata
	 vector<POINT> pol;
	 POINT p;
	 int n;
	// Wczytaj liczbe wierzcho�k�w wielokata
	 cin >> n;
	// Wczytaj kolejne wierzcho�ki wielokata oraz dodaj je do wektora
	 REP(x, n) {
		 cin >> p.x >> p.y;
		 pol.PB(p);
	 }
	 cout << "\t\t\t\t Polygon\t\t\t\t Convex Polygon" << endl;
	 cout << "\t\t Inside\t\t In\t\t Inside\t\t In" << endl;
	// Dla kolejnych punkt�w wyznacz ich przynaleznosc do wielokata przy uzyciu
	// poszczeg�lnych funkcji
	 while(cin >> p.x >> p.y) cout << p << "\t\t" <<
		 PointInsidePol(pol, p) << "\t\t\t" <<
		 PointInPol(pol, p) << "\t\t\t" <<
		 PointInsideConvexPol(pol, p) << "\t\t\t" <<
		 PointInConvexPol(pol, p) << endl;
		 return 0;
	 }
	*/
	
	/*
	// przeciecie prostych i odcinkow
	 vector<POINT> b, e;
	 vector<POINTD> l;
	 int res;
	 POINT p1, p2;
	 POINTD p;
	// Wczytaj wszystkie pary punkt�w wyznaczajace proste i odcinki
	 while(cin >> p1.x >> p1.y >> p2.x >> p2.y) {
		 b.PB(p1); e.PB(p2);
	 }
	// Dla kazdej pary punkt�w wykonaj funkcje LineCrossPoint oraz SegmentCrossPoint
	 REP(x, SIZE(b)) REP(y, x) {
		 cout << b[x] << " - " << e[x] << " oraz " << b[y] << " - " << e[y] << endl;
		 cout << "Punkt przeciecia prostych: " << (res = LineCrossPoint(b[x], e[x], b[y], e[y], p));
		 if (res == 1) cout << " " << p;
		 cout << endl;
		 cout << "Punkt przeciecia odcinkow: " << SegmentCrossPoint(b[x], e[x], b[y], e[y], l);
		 FOREACH(it, l) cout << " " << (*it);
		 cout << endl;
	 }
	 return 0;
	*/
	
	/*
	// punkty przeciecia prostej i okregu, okregow
	 vector<POINT> cCen;
	 VI cR;
	 vector<POINTD> res;
	 POINT l1, l2, p; int r;
	// Wczytaj wsp�rzedne punkt�w wyznaczajacych prosta
	 cin >> l1.x >> l1.y >> l2.x >> l2.y;
	// Wczytaj opisy kolejnych okreg�w
	 while(cin >> p.x >> p.y >> r) {
		 cR.PB(r); cCen.PB(p);
	 }
	// Wyznacz punkty przeciecia prostej i okregu
	 cout << "Przeciecie prostej " << l1 << " - " << l2 << " i okregu:" << endl;
	 REP(x, SIZE(cCen)) {
		 res = LineCircleCross(cCen[x], cR[x], l1, l2);
		 cout << "\t(" << cCen[x].x << ", " << cCen[x].y <<	 ", " << cR[x] << ") - ";
		 if (!SIZE(res)) cout << "brak punktow przeciecia";
		 FOREACH(it, res) cout << " " << (*it);
		 cout << endl;
	 }
	// Wyznacz punkty przeciecia dw�ch okreg�w
	 cout << "Przeciecie okregow:" << endl;
	 REP(x, SIZE(cCen)) REP(y, x) {
		 res = CirclesCross(cCen[x], cR[x], cCen[y], cR[y]);
		 cout << "\t(" << cCen[x].x << ", " << cCen[x].y << ", " << cR[x] << ") oraz (" <<	 cCen[y].x << ", " << cCen[y].y << ", " << cR[y] << ") - ";
		 if (!SIZE(res)) cout << "brak punktow przeciecia";
		 FOREACH(it, res) cout << " " << *(it);
		 cout << endl;
	 }
	 return 0;
	*/
	
	/*
	// znajdowanie okregu wycznaczonego przez 3 punkty
	 vector<POINT> l;
	 POINT p;
	 POINTD po;
	 double r;
	 bool res;
	// Wczytaj liste punkt�w
	 while (cin >> p.x >> p.y) l.PB(p);
	// Dla kazdej tr�jki punkt�w, wyznacz okrag na nich opisany
	 REP(x, SIZE(l)) REP(y, x) REP(z, y) {
		 cout << "Punkty: " << l[x] << ", " << l[y] << ", " << l[z] << endl;
		 if (!ThreePointCircle(l[x], l[y], l[z], po, r)) 	 cout << "Punkty sa wspolliniowe" << endl;
		 else cout << "Srodek okregu = " << po << ", promien = " << r << endl;
	 }
	 return 0;
	*/
	
	/*
	// wyznaczanie otoczki wypuklej
	 int n;
	 vector<POINT> l;
	 POINT p;
	// Wczytaj liczbe punkt�w
	 cin >> n;
	// Wczytaj wszystkie punkty
	 REP(x, n) {
	 	cin >> p.x >> p.y;
		l.PB(p);
	 }
	// Wyznacz wypuk�a otoczke
	 vector<POINT *> res = ConvexHull(l);
	 FOREACH(it, res)
	 cout << " " << (**it);
	 return 0;
	*/
	
	/*
	// sortowanie katowe
	 POINT c, k;
	 int n;
	// Wczytaj liczbe punkt�w oraz wsp�rzedne wektora, wzgledem kt�rego wykonywane
	// bedzie sortowanie
	 cin >> n >> c.x >> c.y >> k.x >> k.y;
	 vector<POINT> l(n);
	// Wczytaj wszystkie punkty
	 REP(x, n) cin >> l[x].x >> l[x].y;
	// Posortuj punkty
	 vector<POINT *> res = AngleSort(l, c, k);
	 FOREACH(it, res) cout << " " << *(*it);
	 return 0;
	*/
	
	/*
	// para najblizszych punktow
	 int n;
	 vector<POINT> l;
	 POINT p;
	// Wczytaj liczbe punkt�w
	 cin >> n;
	// Wczytaj kolejne punkty
	 REP(x, n) {
	 	cin >> p.x >> p.y;
		l.PB(p);
	 }
	// Wyznacz pare najblizszych punkt�w oraz wypisz wynik
	 NearestPoints str(l);
	 cout << "Wyznaczona odleglosc: " << str.dist << endl;
	 cout << "Znaleziona para najblizszych punktow:" << endl;
	 cout << *(str.p1) << " " << *(str.p2) << endl;
	 return 0;
	*/
}












