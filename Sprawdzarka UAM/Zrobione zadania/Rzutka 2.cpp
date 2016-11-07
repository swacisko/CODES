#include<stdio.h>
#include<iostream>
int main()
{
    int x,y,n,i,liczba;
    
    scanf("%d %d",&x, &y);
    scanf("%d",&n);
    
    int suma_pkt=0;
    
    for(i=0; i<n; i++)
    {
             scanf("%d",&liczba);
             if(liczba<x) suma_pkt+=x-liczba;
             else if(liczba>y) suma_pkt+=liczba-y;
             else suma_pkt=0;
             
    }
    std::cout<<suma_pkt;
    
    
}

