#include<stdio.h>
#include<vector>
using namespace std;
int main( )
{
int t, n; 
scanf( "%d", &t );
float k;

for( int i=0; i<t; i++)
{
	vector<float> tab(501);

	scanf( "%d", &n );

	for( int j=0; j<n; j++)
	{

	scanf( "%f", &k ); k *= 10.0f;
	
	int kk = (int)k;
	for( int x=kk; x>=0; --x )
	{
		tab[x]+=1;
	}
	
	printf( "%0.f ", tab[kk] );
	}
	printf( "\n" );
	}

return 0;
}

