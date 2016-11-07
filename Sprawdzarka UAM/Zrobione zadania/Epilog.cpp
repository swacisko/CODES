#include<iostream>
#include<string>
#include<cstring>

using namespace std;

int main()
{
	string zdanie;
	int i=0;
	getline(cin,zdanie);
	i = zdanie.size();
	for(int j = i-1; j >=0;j--)     cout<<zdanie[j];

    cout << endl << zdanie;
    return 0;
}
