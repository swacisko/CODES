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
const int no_pos = -1;
int N;

int getIndex( wekt current, int beg, int end, wekt &C ){
	C = wekt(0,0);
	int licznik = 0;
	for( int i=beg; i!=end; i = (i+1)%wektory.size() ){
		C = C + wektory[i];
		if( square( current + C ) >= square( current ) ) return i;
		licznik++;
		if( licznik >= 100 ) return no_pos;
	}
	
	return no_pos;;
}

void wypisz( wekt w ){
	cout << endl << w.x << " " << w.y << endl;
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
	
	LL maxL = 0;	
	
	wekt C(0,0);
	wekt current = wektory[0];
	
	int beg, end,T,ind;
	LL size;
	int licznik = 0, licznik2;
	wekt W(0,0);
	
	end = T = 0;
	beg = 1;
	
	for( int i=0; i<wektory.size(); i++ ){
	//	cout << "i = " << i << endl;
		licznik2 = 0;
		current = wekt( wektory[i] );
		beg = (i+1)%wektory.size();
		if( square( current ) > maxL ) maxL = square( current );
		
		while( ( ind = getIndex( current, beg, i, C ) )!= no_pos  ){
			current = current + C;
			if( square( current ) > maxL ) maxL = square( current );
			beg = ind;
			beg++;
			beg %= wektory.size();
			
			licznik2++;
			if( licznik2 > 2*N ) cout << "ZLA ODP" << endl;
		//	wypisz(current);
		}
		
		if( square( current ) > maxL ) maxL = square( current );
	}
	
	cout << maxL << endl;
//	wypisz(W); 
	
	
}




