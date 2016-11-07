#include<iostream>
//#include<vector>
#include<cmath>
#include<algorithm>

#include<fstream>



using namespace std;

class Point2D{
public:
	double alpha;
	double x;
	double y;
/*	double& operator[]( int a ){
		if( a == 0 ) return alpha;
		if( a == 1 ) return x;
		if( a == 2 ) return y;
		cout << "SIEMANO, operator[]" << endl;
	}*/
};


int M;
//vector<Point2D> V( 1000010 );
Point2D V[100010];
Point2D* hull[100010];

int hull_size;
const int inf = ( 31 << 26 ) ;
/*
double alpha( Point2D &points ) // points musi byc trzywymiarowa tablica lub wektorem typu double, w[1] = wpsolrzedna x, w[2] = wspolrzedna y
{
	double d = ( points.x>=0?points.x:-points.x ) + ( points.y>=0?points.y:-points.y );
	
	if( points.x>=0 && points.y>=0 ) points.alpha = points.y/d;
	else if( points.x<0 && points.y>=0 ) points.alpha = 2 - points.y/d;
	else if( points.x<0 && points.y<0 ) points.alpha = 2 + (points.y>=0?points.y:-points.y)/d;
	else if( points.x>=0 && points.y<0 ) points.alpha = 4 - (points.y>=0?points.y:-points.y)/d;
	
	return points.alpha;
}
*/
inline void alpha( Point2D &points ) // points musi byc trzywymiarowa tablica lub wektorem typu double, w[1] = wpsolrzedna x, w[2] = wspolrzedna y
{
	if( points.y == 0 ){
		if( points.x >= 0 )points.alpha = (double)inf;
		else points.alpha;
		return;
	}
	else{
		points.alpha = -1 * points.x / points.y;
	}
}

inline double collinearity( Point2D *w1, Point2D *w2, Point2D &w3 ) // w1,w2,w3 musi byc trzywymiarowa tablica lub wektorem typu double, w[1] = wpsolrzedna x, w[2] = wspolrzedna y
{
//	cout << "Jestem w collinearity" << endl;
	double det = ( (w1->x)*(w2->y) ) + ( (w2->x)*(w3.y) ) + ( (w3.x)*(w1->y) )
	- (   ( (w2->y)*(w3.x) ) + ( (w3.y)*(w1->x) ) + ( (w1->y)*(w2->x) )       );
	
	return det;  // jesli det>0 to z znajduje sie po lewej stronie wektora xy	
}

inline bool myfun( Point2D a, Point2D b ){
	
	if( a.alpha < b.alpha ) return true;
	else if( a.alpha == b.alpha && a.x < b.x ) return true;
	else if( a.alpha == b.alpha && a.x == b.x && a.y < b.y ) return true;
	return false;
}


void createConvexHull(){ // typ to musi byc vector<vector<double> > lub vector< *double > , drugi wymiar musi byc 'tablica' trzyelementowa
	
	hull_size = 0;
	double miny=(double)inf, minx = (double)inf;
	double f1,f2;
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
//		for(int i=1; i<M; i++) cout<<V[i][1]<<"  "<<V[i][2]<<"  alpha: "<<V[i][0]<<endl;
		
	//	sort( V.begin()+1, V.begin()+M, myfun );
	sort( V, V+M, myfun );
	
//		cout<<"Twoj najdolniejszy i najlewszy punkt to: "<<V[0][1]<<"  "<<V[0][2];
//		cout<<endl<<"A to twoje pozostale punkty uporzadkowane wzgledem rosnacego alpha:" << endl;
//		for(int i=1; i<M; i++) cout<<V[i].x+f1<<"  "<<V[i].y+f2<<"  alpha: "<<V[i].alpha<<endl;
		
	//	cout << "WTF" << endl;
		hull[0] = &V[0];
		hull[1] = &V[1];
		hull_size = 2;
		
	//	cout << "WTF" << endl;
		
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
// zwroci ona vector< *double > zawierajacy tylko punkty otoczki wypuklej


inline double distanceFrom( double &x1, double &y1, double &x2, double &y2, double &xp, double &yp  ){ // odleglosc od prostej wyznaczonej przez punkty x1,y1 oraz x2,y2 punktu xp,yp
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
	
	ifstream strin( "Prosta_iny.txt" );
	ofstream strout( "Prosta_outy.txt" );
	
	
//	for( int i=0; i<100010; i++ ) V.push_back( Point2D() );
	
	strout.precision(2);
	strout << fixed;
	
	double c;
	int m;
//	double a[2];
	double b0,b1;
	
	double min;
	int k;
	double x,y;
	double h;
//	double xx, yy;
	
	int l_zest;		
	strin >> l_zest;	
	while( l_zest-- ){
		
		strin >> k;
		M = k;		
		
		for( int i=0; i<k; i++ ){
			strin >> V[i].x >> V[i].y;
		}
		
		if( k <= 2 ){
			h = 0.00;
			strout << h << endl;
			continue;
		}
		
		createConvexHull();
		
//		sort( hull, hull+hull_size, comp );
		
	/*	strout << "To punkty twojej otoczki wypuklej:" << endl;
		for( int i=0; i<hull_size; i++ ){
			strout << hull[i]->x << " " << hull[i]->y << endl;
		}*/
		
		
		
		min = inf;
		
	//	strout << "min = " << min << endl;
		int t = 1;
		
		if( hull_size <=2 ){
			h = 0.00;
			strout << h << endl;
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
			
			while( true ){
				m = t;
				t++;
				t %= hull_size;
				
				if(  distanceFrom( hull[i]->x,hull[i]->y,b0,b1, hull[t]->x, hull[t]->y )  
						< 	 (  c = distanceFrom( hull[i]->x,hull[i]->y,b0,b1, hull[m]->x, hull[m]->y ) ) ){
							
							
					t = m;
					if( min > c  ) min = c;
					if( t == i ){
						h = 0;
						strout << h << endl;
						goto koniec;
					}
			//		strout << "-----> " << min << " <-----" << endl;
					break;					
				}
				
			}
		}
		
		strout << min << endl;

koniec:;
	}
	
	
	
	
	
	
//	strin.close();
//	strout.close();
	
	
	
	
}
