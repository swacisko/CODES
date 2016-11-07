#include<iostream>
#include<stdio.h>
#include<cmath>
using namespace std;

double module(double value);

int main()
{
	int l_zest,a,b,c,d,e,f,x,y,z;
	double A[3]={},B[3]={},P[3]={};
	double odl, mian, AP, AB, PB, cosi, sini;
	float wynik;
	cin>>l_zest;
	
	while(l_zest--)
	{
		cin>>a>>b>>c>>d>>e>>f>>x>>y>>z;
		
		P[0]=x; P[1]=y; P[2]=z;
		A[0]=a; A[1]=c; A[2]=e;
		B[0]=0; B[1]=(  ((double)(-a*d)) /(double)b +(double)c ); B[2]=(  ((double)(-a*f)) /(double)b + (double)e );
		
		AP = sqrt( pow(P[0]-A[0],2) + pow(P[1]-A[1],2) + pow(P[2]-A[2],2) );
		AB = sqrt( pow(B[0]-A[0],2) + pow(B[1]-A[1],2) + pow(B[2]-A[2],2) );
		PB = sqrt( pow(P[0]-B[0],2) + pow(P[1]-B[1],2) + pow(P[2]-B[2],2) );
		
		if(AP==0 || PB==0)
		{
			cout<<"0.000"<<endl;
			continue;
		}
		cosi = ( pow(AP,2) + pow(AB,2) - pow(PB,2) ) / (2 * AP*AB ) ;
		sini = sqrt( 1 - pow(cosi,2) );
	
		odl = AP * module(sini) ;
		
		wynik = static_cast<float>(odl);
		
		printf("%.3f\n",odl);
		
		
	}
	
	
	
	
	
}

double module(double value)
{
	if(value>=0) return value;
	else return -value;

}
