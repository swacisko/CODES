#include <iostream>
#include<cmath>

using namespace std;

#define MOD(a) (((a) >= 0) ? (a) : (-a))

void quickhull(int** A, int* &wyn, int size);
void quickhull_work(int** A, int* wyn, int* tab,int *iter, int size, int x, int y, int outside(int**,int,int,int,int,int*,int*) );
void quickhull_rek(int** A, int* wyn, int *tab, int size, int a, int b, int c, int x, int y, int(int**,int,int,int,int,int*,int*) );

void line( int x1, int y1, int x2, int y2, int& a, int& b, int& c);
int above( int** A, int size, int a, int b, int c, int* tab, int* newtab);
int under( int** A, int size, int a, int b, int c, int* tab, int* newtab);


void line( int x1, int y1, int x2, int y2, int& a, int& b, int& c)
{
	a = y1 - y2;
	b = x2 - x1;
	c = x1*y2 - x2*y1;	
	if( b < 0 )
	{	a = -a;
		b = -b;
		c = -c;		}
	else if( b == 0 && a > 0 )
	{	a = -a;
		c = -c;		}
}

int above( int** A, int size, int a, int b, int c, int* tab, int* newtab)
{
	int ile = 0;
	for(int i=0; i<size; i++)
		if( a*A[tab[i]][0] + b*A[tab[i]][1] + c > 0 )
			newtab[ile++] = tab[i];
	return ile;
}

int under( int** A, int size, int a, int b, int c, int* tab, int* newtab)
{
	int ile = 0;
	for(int i=0; i<size; i++)
		if( a*A[tab[i]][0] + b*A[tab[i]][1] + c < 0 )
			newtab[ile++] = tab[i];
	return ile;
}


void quickhull_work(int** A, int* wyn, int* tab,int *iter, int size, int x, int y, int outside(int**,int,int,int,int,int*,int*) )
{
	int a,b,c,tabsize;
	line( A[x][0], A[x][1], A[y][0], A[y][1], a, b, c);
	tabsize = outside(A,size,a,b,c,iter,tab);
	


	if( tabsize > 0 )
	{	if( tabsize == 1)
		{
			wyn[0]++;
			wyn[wyn[0]] = tab[0];
		}
		else
			quickhull_rek( A , wyn , tab, tabsize, a, b, c, x, y, outside);	// najpierw nizszy, potem wyzszy: maxx, maxy
	}
}

void quickhull(int** A, int* &wyn, int size)
{
	int rogi[8] = {};	// Nx - min(x), Xx - max(x);	// od 0 do 7 odpowiednio: XxXy, XyXx, XyNx, NxXy, NxNy, NyNx, NyXx, XxNy
	if( !size ) return;
	
	int *tab = new int[size];
	int *iter = new int[size];
	for(int i=0; i<size; i++)
		iter[i] = i;
		
	wyn = new int[size];
	wyn[0] = 0;
	
	for(int i=1; i<size; i++)
	{
		if( A[i][0] > A[rogi[0]][0] ) rogi[0] = rogi[7] = i;		// maxX
		else if( A[i][0] == A[rogi[0]][0] )
		{	 if( A[i][1] > A[rogi[0]][1] )  	rogi[0] = i;
			 else if( A[i][1] < A[rogi[7]][1] )	rogi[7] = i;		}
			 
		if( A[i][0] < A[rogi[3]][0] ) rogi[3] = rogi[4] = i;		// minX
		else if( A[i][0] == A[rogi[3]][0] )
		{	 if( A[i][1] > A[rogi[3]][1] )  	rogi[3] = i;
			 else if( A[i][1] < A[rogi[4]][1] )	rogi[4] = i;		}
			 
		if( A[i][1] > A[rogi[1]][1] ) rogi[1] = rogi[2] = i;		// maxY
		else if( A[i][1] == A[rogi[1]][1] )
		{	 if( A[i][0] > A[rogi[1]][0] )  	rogi[1] = i;
			 else if( A[i][0] < A[rogi[2]][0] )	rogi[2] = i;		}
			 
		if( A[i][1] < A[rogi[5]][1] ) rogi[5] = rogi[6] = i;		// minY
		else if( A[i][1] == A[rogi[5]][1] )
		{	 if( A[i][0] < A[rogi[5]][0] )  	rogi[5] = i;
			 else if( A[i][0] > A[rogi[6]][0] )	rogi[6] = i;		}
	}

	for(int i=0; i<8; i+=2 )
	{
		if( i == 0 || rogi[i] != rogi[i-1] )
			{	wyn[0] ++;
				wyn[wyn[0]] = rogi[i];				}
		if( rogi[i] != rogi[i+1] )
		{		
				if( i < 3 )		quickhull_work(A, wyn, tab, iter, size, rogi[i], rogi[i+1], above );
				else			quickhull_work(A, wyn, tab, iter, size, rogi[i], rogi[i+1], under );
				wyn[0]++;
				wyn[wyn[0]] = rogi[i+1];			}	
	}
	if( wyn[1] == wyn[wyn[0]] ) wyn[0]--;
	delete [] tab;
}

void quickhull_rek(int **A, int* wyn, int *tab, int size, int a, int b, int c, int x, int y, int outside(int**,int,int,int,int,int*,int*))
{
	int temp, tabsize;
	int maxi = 0, max = MOD ((a*A[tab[0]][0] + b*A[tab[0]][1] + c));
	for(int i=1; i<size; i++)
	{
		temp = MOD ((a*A[tab[i]][0] + b*A[tab[i]][1] + c));
		if( temp > max )
		{	max = temp;
			maxi = i;		}
	}
	
	int *newtab = new int[size];

	quickhull_work( A , wyn, newtab, tab, size, x, tab[maxi], outside );
	
	wyn[0] ++;
	wyn[wyn[0]] = tab[maxi];
	
	quickhull_work( A , wyn, newtab, tab, size, tab[maxi], y, outside );
	
	delete [] newtab;
}

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

	cout.precision(2);
	cout << fixed;
	
	int **V = new int*[100001];
	for( int i=0; i<100001; i++) V[i] = new int[2];
	int *wyn = new int[100001];	
	int k;
	double h;
	
	int l_zest;		
	cin >> l_zest;	
	while( l_zest-- ){
		
		cin >> k;		
		
		for( int i=0; i<k; i++ ){
			cin >> V[i][0] >> V[i][1];
		}
		
		if( k <= 2 ){
			h = 0.00;
			cout << h << endl;
			continue;
		}
		
		quickhull( V,wyn,k );	
		
		double min = ( 31<<26 );
		
		double c;
		int m;
		int t = 3;
		int a0,a1,b0,b1;
		
		if( wyn[0] <=2 ){
			h = 0.00;
			cout << h << endl;
			continue;
		}
		
		a0 = V[wyn[1]][0];
		a1 = V[wyn[1]][1];
		for( int i=1; i<=wyn[0]; i++ ){			
			if( i == wyn[0] ){
				b0 = V[wyn[1]][0];
				b1 = V[wyn[1]][1];
			}
			else{
				b0 = V[wyn[i+1]][0];
				b1 = V[wyn[i+1]][1];
			}
			
			while( true ){
				m = t;
				t++;
				t %= (wyn[0]+1);
				
				if(  distanceFrom( a0, a1, b0, b1, V[wyn[t]][0], V[wyn[t]][1]   )  
						< ( c = distanceFrom( a0, a1, b0, b1, V[wyn[m]][0], V[wyn[m]][1] ) ) ){						
							
					t = m;
					if( min > c  ) min = c;
					if( t == i ){
						h = 0;
						cout << h << endl;
						goto koniec;
					}
			//		cout << "-----> " << min << " <-----" << endl;
					break;					
				}
				
			}
			
			a0 = b0;
			a1 = b1;
		}
		
		cout << min << endl;

koniec:;
	}
	
	
	
	
	
	
//	cin.close();
//	cout.close();
	
	
	
	
}
