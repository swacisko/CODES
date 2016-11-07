#include <iostream>

using namespace std;


int main()
{
	
	int D, a1,a2,a3,a4,a5, suma;
	bool czy_sto=false;
	
	cin>>D;
	
	while(D--)
	{
		cin>>a1>>a2>>a3>>a4>>a5>>suma;		
		
		
	if(suma%100)
	{
			for(int i=0; i<=a1; i++)
			{
				if(i*10 == suma%100)
				{
					a1-=i;
					suma-= (suma%100);					
					break;
				}
			}
		if(suma%100)	
		{
		
				for(int i=0; i<=a1; i++)
				{
					for(int k=0; k<=a2; k++ )
					{
						if( 10*i + 20*k == suma%100 )
						{
							a1-=i;
							a2-=k;
							suma-=(suma%100);					
							i=k=a1+a2+1;
						}
					}
					
				}
			
		}
		
		if(suma%100)
		{
			if(a3!=0)
			{
				suma-=50;
				a3-=1;
				
				for(int i=0; i<=a1; i++)
				{
					for(int k=0; k<=a2; k++ )
					{
						if( 10*i + 20*k == suma%100 )
						{
							a1-=i;
							a2-=k;
							suma-= (suma%100);							
							i=k=a1+a2+1;
						}
					}
					
				}
				
				
			}
		}		
		
	}	// if suma%100
		
		
		if(! (suma%100) )
		{
			
		a2+= a1 / 2;
		a1-= 2 * (a1 / 2);
		a4+= a2 / 5;
		a4+= a3 / 2;
		a2-= 5 * (a2 / 5);
		a3-= 2 * (a3 / 2);
		if(a1>0 && a2>1 && a3>0) a4+=1;
		
		for(int i=0; i<=a4; i++)
		{
			for(int k=0; k<=a5; k++)
			{
				if( 100*i + 200*k <suma);
				else if( 100*i + 200*k == suma)
				{					  
					suma=0;
					goto koniec;
				}
				
			}
		}
	koniec:
		
		if(suma==0) cout<<"TAK"<<endl;
		else cout<<"NIE"<<endl;
			
			
		}
		else
		{
			cout<<"NIE"<<endl;
					
		}
		
	} // while
	
	
	
}

