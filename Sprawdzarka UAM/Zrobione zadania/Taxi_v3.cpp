#include<iostream>
using namespace std;

int mod(int liczba)
{
	if(liczba>=0) return liczba;
	else return -liczba;
}

int main()
{
	int maxs=0, maxr=-1000000, mins=2000000, minr=1000000, xmaxs, xmins, xmaxr, xminr, ymaxs, ymins, ymaxr, yminr,
	D, N, X, Y, wspxs, wspys, wspxr, wspyr;
	
	cin>>D;
	
	for(int i=0; i<D; i++)
	{
		maxs=0; maxr=-1000000; mins=2000000; minr=1000000;
		cin>>N;
		
		for(int k=0; k<N; k++)
		{
			cin>>X>>Y;
			
			if( (X+Y) >= maxs )
			{
				maxs= X+Y;
				xmaxs=X;
				ymaxs=Y;
			}
			if((X+Y)<mins)
			{
				mins=X+Y;
				xmins=X;
				ymins=Y;
			}			
			if((X-Y)>=maxr)
			{
				maxr=X-Y;
				xmaxr=X;
				ymaxr=Y;
			}
			if((X-Y)<minr)
			{
				minr=X-Y;
				xminr=X;
				yminr=Y;
			}
			
			
			
		}
		
		wspxs= mod(xmaxs-xmins);
		wspys= mod(ymaxs-ymins);
		wspxr= mod(xmaxr-xminr);
		wspyr= mod(ymaxr-yminr);
		
		if((wspxs + wspys)>=(wspxr+wspyr)) cout<<wspxs + wspys<<endl;
		else cout<<wspxr+wspyr<<endl;
		
	}
	
	
	
	
}



