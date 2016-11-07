#include<cstdio>
#include<vector>
#include<cmath>

using namespace std;

int suma[500001];

vector<int> getPrimes( int N ){
    bool* tab = new int[N+1];
    for(int i=0; i<=N; i++) tab[i] = true;
    tab[0] = tab[1] = false;
    for( int i=2; i*i <= N; i++ ){
        if( tab[i] == false ) continue;
        for( int k=i+i; k<=N; k+=i ) tab[k] = false;
    }

    vector<int> primes;
    for(int i=2; i<=N; i++) if( tab[i] ) primes.push_back(i);
    return primes;
}

void preproc(){
    for( int i=0; i<=500000; i++ ) suma[i] = 0;
    vector<int> primes = getPrimes(500000);
    for( int i=0; i<primes.size(); i++ ) suma[ primes[i] ] = 1;







}



int main(){


    int l_zest;
    scanf("%d", &l_zest);

    preproc();

    while(l_zest--){
        int N;
        scanf("%d",&N);
        if( N == 0 ){
            printf("0\n");
            continue;
        }

       // printf("To twoj rozklad na czynniki pierwsze:\t");
        vector<int> nfact = factorize(N);
       // for(int i=0; i<nfact.size(); i++) printf("%d ", nfact[i]);

       int suma = getSum(nfact);

       printf( "%d\n",suma );







    }

    return 0;
}
