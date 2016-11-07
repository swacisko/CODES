#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;

const int infinity = ( 31 << 26 );
const double oneLimit = 1.000000000001;

typedef pair<int,int> PII;
typedef pair< double, PII> PDPII;
typedef vector<PII> VPII;
typedef vector <PDPII> VPDPII;



class Line{
public:
	Line(){}
	Line( PII &p1, PII &p2 ){
		if( p1.first == p2.first ){
			B = 0;
			A = 1;
			C = - (double) p1.first;
		}
		else{
			B = 1;
			A = (double) ( p1.second - p2.second ) / ( p2.first - p1.first );
			C = (double) -A*p1.first - p1.second;		
		}
		
		denominator = sqrt( A*A + B*B );
	}
	
	double getDistanceFromPoint( PII &p ){
		return abs( A*p.first + B*p.second + C ) / denominator;
	}
	
	double A;
	double B;
	double C;
	double denominator; // sqrt( A*A + B*B ); 
	
};

double alpha( PDPII &points ) // points musi byc trzywymiarowa tablica lub wektorem typu double, w[1] = wpsolrzedna x, w[2] = wspolrzedna y
{
	double d = (double)( points.second.first>=0?points.second.first:-points.second.first ) + ( points.second.second>=0?points.second.second:-points.second.second );
	
	if( points.second.first==0 && points.second.second==0 ) points.first = oneLimit; // czy to dobrze ?
	else if( points.second.first>=0 && points.second.second>=0 ) points.first = (double)points.second.second/d;
	else if( points.second.first<0 && points.second.second>=0 ) points.first = (double)2 - points.second.second/d;
	else if( points.second.first<0 && points.second.second<0 ) points.first = (double) 2 + (points.second.second>=0?points.second.second:-points.second.second)/d;
	else if( points.second.first>=0 && points.second.second<0 ) points.first = (double) 4 - (points.second.second>=0?points.second.second:-points.second.second)/d;
	
	return points.first;
}

double collinearity( PII &w1, PII &w2, PII &w3 ) // w1,w2,w3 musi byc trzywymiarowa tablica lub wektorem typu double, w[1] = wpsolrzedna x, w[2] = wspolrzedna y
{
//	cout << "Jestem w collinearity" << endl;
	double det = (double) ( (w1.first)*(w2.second) ) + ( (w2.first)*(w3.second) ) + ( (w3.first)*(w1.second) )
	- (   ( (w2.second)*(w3.first) ) + ( (w3.second)*(w1.first) ) + ( (w1.second)*(w2.first) )       );
	
	return det;  // jesli det>0 to z znajduje sie po lewej stronie wektora w1-w2->	
}

void getConvexHull( VPDPII &V, VPII &stack ){
	
	int f1 = infinity, f2 = infinity, index = 0;
	for( int i=0; i<V.size(); i++ ){
		if( V[i].second.second < f2 ){
			f1 = V[i].second.first;
			f2 = V[i].second.second;
			index = i;
		}
		else if( V[i].second.second == f2 && V[i].second.first < f1 ){
			f1 = V[i].second.first;
			index = i;
		}
		
	}
	
	for( int i=0; i<V.size(); i++ ){
		V[i].second.first -= f1;
		V[i].second.second -= f2;
	}
	
	swap( V[0], V[index] );
	
	for( int i=1; i<V.size(); i++ ) alpha( V[i] );
	
	sort( V.begin()+1, V.end() );
	
/*	cout << "To posortowane punkty wzgledem alpha:" << endl;
	for( int i=0; i<V.size(); i++ ){
		cout << "Alpha = " << V[i].first << "  x = " << V[i].second.first << "   y = " << V[i].second.second << endl;
	}*/
	
	stack.clear();
	stack.push_back( V[0].second );
	stack.push_back( V[1].second );
	
	int w = 2;
	while( w > 0 ){
		
		while( stack.size() > 1 && collinearity( stack[stack.size()-2], stack[ stack.size()-1 ], V[w].second ) <= 0 ){
			stack.pop_back();
		}
		
		stack.push_back( V[w].second );
		w++;
		w %= V.size();
	}
		
	
}

int main(){
	
	ios_base::sync_with_stdio(false);
	
	VPDPII V;
	int N;
	int a,b;
	double min_odl,c;
	int t;
	VPII hull;
	Line prosta;
	
	cout << fixed;
	cout.precision(2);
	
	int l_zest;
	cin >> l_zest;
	while( l_zest-- ){
		cin >> N;
		V.clear();
		
		for( int i=0; i<N; i++ ){
			cin >> a >> b;
			V.push_back( make_pair( (double)0, make_pair( a, b ) ) );
		}
		
		getConvexHull( V, hull );		
		
//		cout << "To twoja otoczka wypukla:" << endl;
//		for( int i=0; i<hull.size(); i++ ) cout << "\t" << hull[i].first << " " << hull[i].second << endl;
		
		if( hull.size() <=2 ){
			cout << (double)0 << endl;
			continue;
		}
		
		min_odl = (double) infinity, c;
		t = 2;
		
		int M = hull.size();
		for( int i=0; i<M; i++ ){
			
			prosta = Line( hull[ i ], hull[ (i+1)%M ] );
			
			while( true ){
				
				if( prosta.getDistanceFromPoint( hull[ (t+1)%M ] ) < ( c = prosta.getDistanceFromPoint( hull[t] ) ) ){
					if( min_odl > c ) min_odl = c;
					break;
				}
				
				t++;
				t%=M;
			}
			
			
		}
		
		cout << min_odl << endl;
		
	}
	
	
}



