#include<iostream>
#include<cmath>
using namespace std;

const double PI = 3.141592653;
double beta;

class punkt
{
public:
	double x,y;
	punkt(double wspx=0, double wspy=0) : x(wspx),y(wspy) {}

};

class prosta
{
	public:		
		double a,b;
	void write(void){ cout<<a<<"x + "<<b;	}
	prosta( punkt pierwszy, punkt drugi  );
	prosta( double A, double B ):a(A),b(B) {}
	double schneidet( prosta mirror, punkt &koniec );
	double Schneiden_Punkt( prosta &bisector );
	prosta vertical_symetry();
	prosta bisector_symetry( double wspx );
};

double prosta::Schneiden_Punkt( prosta &bisector ) // zwraca wartosc wspx dla punktu przeciecia dwoch prostych
{
	return ( ( b-bisector.b ) / ( bisector.a - a )  );		
}

prosta::prosta( punkt pierwszy, punkt drugi  )
	{
		if( pierwszy.x == drugi.x ) 
		{
			a=b=0;
		}
		else
		{
			a = ( pierwszy.y - drugi.y ) / ( pierwszy.x - drugi.x );
			b = pierwszy.y - a*pierwszy.x;
		}
	}

double prosta::schneidet( prosta mirror, punkt &koniec ) //jezeli przetnie zwierciadlo to zwraca wartosc true
{
	double x;
	if( a == mirror.a ) return 0;
	else
	{
		x = ( b-mirror.b ) / ( mirror.a - a );		
	}
	
	if( x<koniec.x && x>0 ) return x;
	else return 0;
	
}

prosta prosta::vertical_symetry() // zwraca parametry prostej symetrycznej do danej wzgledem prostej prostopadlej do zwierciadla poziomego w punkcie jego przeciecia
{
	return prosta( -a, -b );	
}

prosta prosta::bisector_symetry( double wspx )
{
	double e = tan( 2*beta + atan( -(this->a ) ) );
	
	return prosta(  e , ( this->a - e ) * wspx + this->b     );
	
}

int main()
{
	ios_base::sync_with_stdio(0);
	
	int l_zest, rebounds;
	double alpha, gamma, d;
	punkt begin( 0.0 , 0.0 );
	
	cin>>l_zest;
	
	while(l_zest--)
	{
		rebounds=0;  d=100000;
		
		cin>>alpha>>gamma;
		
		alpha = alpha * PI / 180;
		gamma = gamma * PI / 180;
		beta = alpha / 2;
		
		punkt end = punkt( d*cos(alpha),d*sin(alpha) );
		
		//cout<<"tan("<<alpha<<") = "<<tan(alpha)<<endl;
		//cout<<"tan("<<beta<<") = "<<tan(beta)<<endl;
		//cout<<"tan("<<gamma<<") = "<<tan(gamma)<<endl;		
		
		prosta wiazka( -tan( gamma ),tan( gamma )*d ); // prosta, ktora jest wiazka lasera
		//cout<<"wiazka: "; wiazka.write();
		prosta bisector( begin, punkt( cos(beta), sin(beta) ) );
		//cout<<endl<<"bisector: "; bisector.write();
		
		prosta horizontal(0.0, 0.0 );  // prosta dla poziomego zwierciadla
		//cout<<endl<<"horizontal: "; horizontal.write();
		prosta slant( begin , end );  // prosta dla ukoscnego zweierciadla
		//cout<<endl<<"slant:  "; slant.write();
		
		//cout<<endl<<"x coordinate of intersection point of slant and wiazka: "<<wiazka.schneidet( slant,end );
		
		while( wiazka.schneidet( slant, end  ) )
		{
			rebounds++;			
			
			wiazka = wiazka.bisector_symetry( wiazka.Schneiden_Punkt(bisector) ); // odbijam symetrycznie wiazka wzgledem dwusiecznej kata
			//cout<<endl<<"wiazka after bisector symetry:  "; wiazka.write();
			
			wiazka = wiazka.vertical_symetry(); // odbijam symetrycznie wzgledem osi Ox
			//cout<<endl<<"wiazka after vertical symetry:  "; wiazka.write();
			
			//cout<<"\tRebounds: "<<rebounds<<endl<<endl;
			
			//cout<<endl<<"x coordinate of intersection point of slant and wiazka: "<<wiazka.schneidet( slant,end );
		}
		
		cout<<rebounds<<endl;
		//cout<<endl<<endl;
	}
	
	
	
}
