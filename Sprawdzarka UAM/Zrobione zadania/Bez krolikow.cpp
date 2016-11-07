#include<iostream>
using namespace std;

int main()
{
    int liczba_zestawow, liczba;
    
    
    cin>>liczba_zestawow;
   
    int A[100]={0};
    A[0]=4; A[1]=7; 
  
for(int k=0; k<liczba_zestawow; k++)
{  
	 cin>>liczba;
	 
    for(int i=2; i<=liczba; i++)
    {
            A[i]= 2*A[i-1]%2011 + 5*A[i-2]%2011;
            
            
    }
    cout<<A[liczba]%2011;
} 
    
   
}
