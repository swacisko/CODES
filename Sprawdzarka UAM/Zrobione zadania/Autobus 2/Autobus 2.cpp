#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

const int inf = (31 << 26);

class Node{
public:
	Node( int d=0, int l=0, int p=0 ) : distance(d), lewy(l), prawy(p){}
	int distance;
	int lewy;
	int prawy;
	bool operator<( Node a );
};

ostream& operator<<( ostream& str, Node &a ){
	str << "  distance = " << a.distance << "  lewy = " << a.lewy << "  prawy = " << a.prawy;
	return str;
}

bool comp( Node a, Node b ){
	if( a.distance < b.distance -1 ) return true;
	else if( a.distance == 0 ) return true;
	else if( b.distance == 0 ) return false;
	else if( a.distance == b.distance && ( b.lewy == inf || ( a.lewy > b.lewy && a.lewy != inf ) ) ) return true;
	else if( a.distance == b.distance - 1 && a.distance%2 == 0 ) return true;
	else if( a.distance == b.distance - 1 && a.distance%2==1 && ( b.lewy == inf || ( a.lewy > b.lewy && a.lewy != inf ) ) ) return true;
	else if( a.distance == b.distance + 1 && a.distance%2==0 && ( b.lewy == inf || ( a.lewy > b.lewy && a.lewy != inf ) ) ) return true;
	else if( a.distance == b.distance - 1 && a.prawy == inf ) return true;
	
//	cout << "\t\tZADEN Z PRZYPADKOW" << endl;
	return false;
}

bool Node::operator<( Node a ){
	return comp( *this, a );
}

void wypisz( vector<Node> &V ){
	for( int i=0; i<V.size(); i++ ){
		cout << "\t" << V[i] << endl;
	}
}

int main(){
	
	ios_base::sync_with_stdio(0);
	
	int N,M,Y,x,y,X;
	vector<Node> V;
	
	int l_zest;
	cin >> l_zest;
	
	while( l_zest-- ){
	
		V.clear();
	//	V.push_back( Node( -100,1,1 ) );
		make_heap( V.begin(), V.end() );
		
		cin >> N >> M;
		
		cin >> X;
		V.push_back( Node( 2*(X-1), inf, X ) ); push_heap( V.begin(), V.end(), comp );
		V.push_back( Node( 2*(N-X), X, inf ) ); push_heap( V.begin(), V.end(), comp );
//		cout << "Wierzcholek z przodu to: " << endl << "\t\t" << V.front() << endl;
		
		cin >> Y;
		
		Node n;
		
		int ktory_element = 1;
		for( int i=0; i<Y; i++ ){
			cin >> y;
			if( y == 1 ){
				cout << X << " ";
				continue;
			}
			while( true ){
			//	cout << "\tWierzcholek z przodu to: " << endl << "\t\t" << V.front() << endl;
//			wypisz( V );
				ktory_element++;
		//		_sleep( 1000 );
				if( ktory_element == y ){
					Node s = V.front();
		//			cout << "\tUsuwam wierzcholek " << s << endl;					
					pop_heap( V.begin(), V.end() ); V.pop_back();
					
					int l = s.lewy;
					int p = s.prawy;
					int d = s.distance;
				
					if( l == inf ) {
						n = Node( (d-1)/2, 1, p );
						V.push_back( n );
						push_heap( V.begin(), V.end(), comp );						
//					cout << "\t\t\tWstawiam wierzcholek " << n << endl;
						cout << 1 << " ";
					}
					else if( p == inf ){
						n = Node( (d-1)/2, l,N );
//						cout << "\t\t\tWstawiam wierzcholek " << n << endl;
						V.push_back( n );
						push_heap( V.begin(), V.end(), comp );
						cout << N << " ";
					}
					else{
						cout << l + (d+1)/2 << " ";
						n = Node( (d-1)/2, l, l+(d+1)/2 );
						V.push_back( n );
						push_heap( V.begin(), V.end(), comp );
//						cout << "\t\t\tWstawiam wierzcholek " << n << endl;
						
						n = Node( p-l-(d+1)/2-1, l+(d+1)/2, p );
						V.push_back( n );
						push_heap( V.begin(), V.end(), comp );
//						cout << "\t\t\tWstawiam wierzcholek " << n << endl;
					}
					break;
				}
				
				
				Node s = V.front();
				pop_heap( V.begin(), V.end() ); V.pop_back();
		//		cout << "\tUsuwam wierzcholek " << s << endl;
				int l = s.lewy;
				int p = s.prawy;
				int d = s.distance;
				
				if( l == inf ){
					n = Node( (d-1)/2, 1, p );
					V.push_back( n );
//					cout << "\t\t\tWstawiam wierzcholek " << n << endl;
				} 
				else if( p == inf ) {
					n = Node( (d-1)/2, l,N );
					V.push_back( n );
//					cout << "\t\t\tWstawiam wierzcholek " << n << endl;
					
				}
				else{
					n = Node( (d-1)/2, l, l+(d+1)/2 );
					V.push_back( n );
					push_heap( V.begin(), V.end(), comp );
		//			cout << "\t\t\tWstawiam wierzcholek " << n << endl;
					
					n =  Node( p-l-(d+1)/2-1, l+(d+1)/2,p );
					V.push_back( n );
					push_heap( V.begin(), V.end(), comp );
//					cout << "\t\t\tWstawiam wierzcholek " << n << endl;
					
					continue;
				}
				
				push_heap( V.begin(), V.end(), comp );
			}
			
		}
		
		if( Y > 0 ) cout << endl;
		
	} // koniec whilea
	
	
	
}
