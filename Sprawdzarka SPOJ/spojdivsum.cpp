#include<cstdio>
#include<vector>
#include<cmath>

using namespace std;



void preproc(){


}

// return prime factors of N
vector<int> factorize( int N ){
    vector<int> ans;
    while( N%2 == 0 ){ ans.push_back(2); N/=2; }

    int t = 3;
    while( t*t <= N ){
        if( N%t == 0 ){
            ans.push_back(t);
            N/=t;
        }
        else t += 2;
    }

    if( N != 1 ) ans.push_back(N);
    return ans;
}


// return the sum of the number given in the form of prime numbers
int getSum( vector<int> & V ){
    vector<int> pr;
    vector<int> mult;
    for(int i=0; i<V.size();i++){
        if( i > 0 && V[i-1] == V[i] ){
            mult.back()++;
        }
        else{
            pr.push_back( V[i] );
            mult.push_back(1);
        }
    }

   /* printf("Oto rozklad na pr i mult:\n");
    for(int i=0; i<pr.size(); i++){
        printf( "%d %d\n", pr[i], mult[i] );
    }*/

    int ans = 1;
    int potega, iloczyn=1;

    for( int i=0; i<pr.size(); i++ ){
        iloczyn *= (int) pow( pr[i], mult[i] );

        potega = round( pow( pr[i], mult[i]+1 ) );
        potega--;
      //  printf("pr[%d] = %d   potega = %d\n", i,pr[i],potega);
        potega /= (pr[i]-1);
        ans *= potega;

    }

   // printf("ans = %d   iloczyn = %d\n", ans, iloczyn);
    return ans-iloczyn;
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
