#include<iostream>
#include<cmath>
#include<algorithm>




using namespace std;

class Point2D{
public:
	double alpha;
	int x;
	int y;

};


int M;
Point2D V[100010];
Point2D* hull[100010];

int hull_size;
const int inf = ( 31 << 26 ) ;
/*
int alpha( Point2D &points ) // points musi byc trzywymiarowa tablica lub wektorem typu int, w[1] = wpsolrzedna x, w[2] = wspolrzedna y
{
	int d = ( points.x>=0?points.x:-points.x ) + ( points.y>=0?points.y:-points.y );
	
	if( points.x>=0 && points.y>=0 ) points.alpha = points.y/d;
	else if( points.x<0 && points.y>=0 ) points.alpha = 2 - points.y/d;
	else if( points.x<0 && points.y<0 ) points.alpha = 2 + (points.y>=0?points.y:-points.y)/d;
	else if( points.x>=0 && points.y<0 ) points.alpha = 4 - (points.y>=0?points.y:-points.y)/d;
	
	return points.alpha;
}*/

inline void alpha( Point2D &points ) // points musi byc trzywymiarowa tablica lub wektorem typu int, w[1] = wpsolrzedna x, w[2] = wspolrzedna y
{
	if( points.y == 0 ){
		if( points.x < 0 )points.alpha = 2000000000;
		else points.alpha = (double)-inf;
		return;
	}
	else{
		points.alpha = -1 * points.x / points.y;
	}
}

inline int collinearity( Point2D *w1, Point2D *w2, Point2D &w3 ) // w1,w2,w3 musi byc trzywymiarowa tablica lub wektorem typu int, w[1] = wpsolrzedna x, w[2] = wspolrzedna y
{
//	cout << "Jestem w collinearity" << endl;
	int det = ( (w1->x)*(w2->y) ) + ( (w2->x)*(w3.y) ) + ( (w3.x)*(w1->y) )
	- (   ( (w2->y)*(w3.x) ) + ( (w3.y)*(w1->x) ) + ( (w1->y)*(w2->x) )       );
	
	return det;  // jesli det>0 to z znajduje sie po lewej stronie wektora xy	
}

inline bool myfun( Point2D a, Point2D b ){
	
	if( a.alpha < b.alpha ) return true;
	else if( a.alpha == b.alpha && a.x < b.x ) return true;
	else if( a.alpha == b.alpha && a.x == b.x && a.y < b.y ) return true;
	return false;
}


void createConvexHull(){ // typ to musi byc vector<vector<int> > lub vector< *int > , drugi wymiar musi byc 'tablica' trzyelementowa
	
	hull_size = 0;
	int miny=(int)inf, minx = (int)inf;
	int f1=0,f2=0;
	int min = 0;
//	int M = V.size(); // UWAGA UWAGA UWAGA, jesli typ nie bedzie wektorem, to trzeba bedzie dodac M do parametrow wywolan funkcji
	
	for(int i=0; i<M; i++) //znajdujemy najnizszy,  i wsrod najnizszych najbardziej lewy punkt
	{
		if( V[i].y < miny ) { miny = V[i].y; minx = V[i].x; min = i; }
		else if( V[i].y == miny && V[i].x < minx ) { minx = V[i].x; min = i;		}
	}
	
	swap( V[0], V[min]  );
	
	f1 = V[0].x;
	f2 = V[0].y;
	
	for(int i=0; i<M; i++) { V[i].x-=f1; V[i].y-=f2;	}		// przesuwamy o dany wektor, aby najnizszy, najlewszy punkt byl w 0,0
	for(int i=1; i<M; i++) 	alpha( V[i] ); // wpisujemy wartosci alpha dla danych punktow;
	
	
	//	cout<<"Przed sortowaniem:\tTwoj najdolniejszy i najlewszy punkt to: "<<V[0][1]<<"  "<<V[0][2];
//		cout<<endl<<"A to twoje pozostale punkty i ich alpha:"<<endl;
	//	for(int i=1; i<M; i++) cout<<V[i].x<<"  "<<V[i].y<<"  alpha: "<<V[i].alpha<<endl;
		
	//	sort( V.begin()+1, V.begin()+M, myfun );
	sort( V+1, V+M, myfun );
	
//		cout<<"Twoj najdolniejszy i najlewszy punkt to: "<<V[0][1]<<"  "<<V[0][2];
//		cout<<endl<<"A to twoje pozostale punkty uporzadkowane wzgledem rosnacego alpha:" << endl;
//		for(int i=1; i<M; i++) cout<<V[i].x+f1<<"  "<<V[i].y+f2<<"  alpha: "<<V[i].alpha<<endl;
		
	//	cout << "WTF" << endl;
		hull[0] = &V[0];
		hull[1] = &V[1];
		hull_size = 2;
		
//		cout << "WTF" << endl;
		
		for(int i=2; i<M; i++)  // wybieram punkty ktore beda tworzyly otoczke wypukla
		{
	/*		for( int k=0; k<hull_size; k++ ){
				cout << hull[k]->alpha << " " << hull[k]->x << " " << hull[k]->y << endl;;
			}*/
			while( hull_size >=2 && collinearity( hull[hull_size-2], hull[hull_size-1], V[i] ) < 0 )
			{
	//			cout << "JEstem w whilu" << endl;
				
	//			cout << endl << V[i][0] << " " << V[i][1] << " " << V[i][2] << endl;
	//			cout << "Zaraz popbackuje, hull_size = " << hull_size << endl;
				hull_size--;
			}
	//		cout << "Jestem w petli, hull_size = " << hull_size << endl;
			hull_size++;
			hull[ hull_size-1 ] = &V[i];
		}
		
	//	for(int i=0; i<M; i++) { V[i][1]+=f1; V[i][2]+=f2;	}		// przesuwamy spowrotem o dany wektor, aby wrocic do satnu poczatkowego
		for(int i=0; i<hull_size; i++) { hull[i]->x+=f1; hull[i]->y+=f2;	}		// przesuwamy o dany wektor, aby wrocic do stanu poczatkowego
		
		/*
		cout<<endl<<"Punkty tworzace twoja otoczke wypukla to:"<<endl;
		
		for(int i=0; i<hull_size; i++)
		{
			cout<<hull[i][1]+f1<<"  "<<hull[i][2]+f2<<endl;
		}
		*/
		
}


// Aby optrzymac otoczke wypukla dla
// punktow zapisanych w tablicy lub wektorze tab[M][3]
// trzba wywolac funkcje createConvecHull( tab );
// zwroci ona vector< *int > zawierajacy tylko punkty otoczki wypuklej


inline double distanceFrom( int &x11, int &y11, int &x22, int &y22, int &xpp, int &ypp  ){ // odleglosc od prostej wyznaczonej przez punkty x1,y1 oraz x2,y2 punktu xp,yp
	double x1 = (double)x11, x2 = (double)x22, y1 = (double)y11, y2 = (double)y22, xp = (double)xpp, yp = (double)ypp;

	double d = sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
	double c = ( x1-xp )*( x1-x2 )/d + ( y1-yp )*( y1-y2 )/d;
	
	double e1 = c * ( x1-x2 )/d;
	double e2 = c * ( y1-y2 )/d;
	
	double f1 = x1-xp-e1;
	double f2 = y1-yp-e2;
	
	return sqrt( f1*f1 + f2*f2 );
}


int main(){
	
	ios_base::sync_with_stdio(0);
	
//	ifstream strin( "Prosta_iny.txt" );
//	ofstream strout( "Prosta_outy.txt" );
	
	
//	for( int i=0; i<100010; i++ ) V.push_back( Point2D() );
	
	cout.precision(2);
	cout << fixed;
	
	double c=0;
	int m=0;
//	int a[2];
	int b0=0,b1=0;
	
	double min=0;
	int k=0;
	int x=0,y=0;
	double h = 0;
//	int xx, yy;
	
	int l_zest;		
	cin >> l_zest;	
	while( l_zest-- ){
		
		cin >> k;
		M = k;		
		
		for( int i=0; i<k; i++ ){
			cin >> V[i].x >> V[i].y;
		}
		
		if( k <= 2 ){
			h = 0.00;
			cout << h << endl;
			continue;
		}
		
		createConvexHull();
		
//		sort( hull, hull+hull_size, comp );
		
	/*	cout << "To punkty twojej otoczki wypuklej:" << endl;
		for( int i=0; i<hull_size; i++ ){
			cout << hull[i]->x << " " << hull[i]->y << endl;
		}*/
		
		
		
		min = inf;
		
	//	cout << "min = " << min << endl;
		int t = 2;
		
		if( hull_size <=2 ){
			h = 0.00;
			cout << h << endl;
			continue;
		}
		
		for( int i=0; i<hull_size; i++ ){			

			
			if( i == hull_size-1 ){
				b0 = hull[0]->x;
				b1 = hull[0]->y;
			}
			else{
				b0 = hull[i+1]->x;
				b1 = hull[i+1]->y;				
			}
			
			t++;
			t %= hull_size;
			if( t == 0 ) m = hull_size-1;
			else m = t-1;
			while( true ){								
		//		cout << "t = "<< t << " m = "<< m << endl;
				if(  distanceFrom( hull[i]->x,hull[i]->y,b0,b1, hull[t]->x, hull[t]->y )  
						< 	 (  c = distanceFrom( hull[i]->x,hull[i]->y,b0,b1, hull[m]->x, hull[m]->y ) ) ){							
							
					t = m-1;
					if( min > c  ) min = c;
					
			//		cout << "-----> " << min << " <-----" << endl;
					break;					
				}
			/*	if( t == i ){
						h = 0;
						cout << h << endl;
						goto koniec;
				}*/
			//	cout << "petla"<< endl;
				m = t;
				t++;
				t %= hull_size;
				
			}
		//	cout << endl;
		}
		
		cout << min << endl;

koniec:;
	}
	
	
	
	
}
