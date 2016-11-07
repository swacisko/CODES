#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;

typedef long long LL;
typedef pair<int,int> PII;
typedef pair<double, PII> PDPII;

double alpha( PDPII &points ) // points musi byc trzywymiarowa tablica lub wektorem typu double, w[1] = wpsolrzedna x, w[2] = wspolrzedna y
{
	double d = (double)( points.second.first>=0?points.second.first:-points.second.first ) + ( points.second.second>=0?points.second.second:-points.second.second );
	
	if( points.second.first>=0 && points.second.second>=0 ) points.first = (double)points.second.second/d;
	else if( points.second.first<0 && points.second.second>=0 ) points.first = (double)2 - points.second.second/d;
	else if( points.second.first<0 && points.second.second<0 ) points.first = (double) 2 + (points.second.second>=0?points.second.second:-points.second.second)/d;
	else if( points.second.first>=0 && points.second.second<0 ) points.first = (double) 4 - (points.second.second>=0?points.second.second:-points.second.second)/d;
	
	return points.first;
}

LL modul( LL a, LL b ){
	return a*a + b*b;
}

class wekt{
public:
	wekt( PDPII &p ){
		x = p.second.first;
		y = p.second.second;
	}
	wekt( LL a, LL b){
		x = a;
		y = b;
	}
	
	wekt operator+( wekt &other ){
		wekt C( x +other.x, y + other.y );
		return C;
	}
	
	wekt operator-( wekt &other ){
		wekt C( x - other.x, y - other.y );
		return C;
	}
	
	LL x;
	LL y;
};

LL square( wekt w ){
	return w.x * w.x + w.y * w.y;
}

vector< wekt > wektory;
int N;

void wypisz( wekt w ){
	cout << w.x << " " << w.y << endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	
	vector<PDPII> V;
	V.clear();
	
	int a,b;
	
	cin >> N;
	
	for( int i=0; i<N; i++ ){
		cin >> a >> b;
		
		if( a != 0  ||  b != 0 ) V.push_back( make_pair( 0, make_pair( a,b ) ) );
	}
	
	for( int i=0; i<V.size(); i++ ){
		alpha( V[i] );
	}
	
	sort( V.begin(), V.end() );
	for( int i=1;i <V.size(); i++ ){
		if( i > 0 ) if( V[i].first == V[i-1].first ){
			V[i-1].second.first += V[i].second.first;
			V[i-1].second.second += V[i].second.second;
			V.erase( V.begin() + i );
			i--;
		}
	}
	
/*	for( int i=0; i<V.size(); i++ ){
		cout << V[i].second.first << " " << V[i].second.second << endl;
	}*/
	
	wektory.clear();
	
	for( int i=0; i<V.size(); i++ ){
		wektory.push_back( wekt( V[i] ) );
	}
	
	if( wektory.size() == 1 ){
		cout << square( wektory[0] ) << endl;
		return 0;
	}
	else if( wektory.size() == 0 ){
		cout << 0 << endl;
		return 0;
		
	}
	
	LL maxL = 0;	
	
	wekt C(0,0), next(0,0), last(0,0);
	wekt current = wektory[0];
	
	int beg, end,petla;
	beg = 1;
	end = 0;
	int licznik = 0;
	bool ifWas, ifWas2;
	petla = 0;
	next = wektory[1];	
	last = wektory[0];
	
//	cout << "////////////////////////////" << endl;
//	for( int i=0; i<wektory.size(); i++ ) wypisz( wektory[i] );
//	cout << endl << "///////////////////////////" << endl;
	
	while( licznik++ <= 4*N ){		
		
		if( square( current + next ) >= square( current ) && ( beg != end || ( current.x == 0 && current.y == 0 ) ) ){
			beg++;
			beg%=wektory.size();
			current = current + next;
	//		cout << "Dodaje next   "; wypisz( next );
			next = wektory[beg];
		}
		else{
			end++;
			end%=wektory.size();
			current = current - last;
	//		cout << "Zabieram last   "; wypisz(last);
			last = wektory[end];
		}
	//	cout << "Current = "; wypisz(current); cout << endl;
		
		if( square( current ) >= maxL ) maxL = square( current );
	}
	

	
	cout << maxL << endl;
//	wypisz(W); 
	
	
}







