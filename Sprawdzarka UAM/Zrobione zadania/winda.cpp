#include<iostream>

using namespace std;

int main()
{
	int n,s, suma=0, liczba=0, liczba2=0;
	
	cin>>n>>s;
	
	for(int i=0; i<n; i++)
	{
		cin>>liczba;
		if(suma+liczba<=s)
		{		
		suma+=liczba;
	
		}
		else break;
	}
	cout<<suma;
}
