#include<iostream>
using namespace std;

long int kroliki(int);

int main()
{
    int liczba_zestawow, liczba;
    cin>>liczba_zestawow;
    
    for(int i=0; i<liczba_zestawow; i++)
    {
            cin>>liczba;
            cout<<kroliki(liczba)<<" ";
            
            
    }
    
}
long int kroliki(int N)
{
     
    if(N==0 || N==1 || N==2) return 1;
    else return ( kroliki(N-1) + 2*kroliki(N-3) );
    
    
    
}
