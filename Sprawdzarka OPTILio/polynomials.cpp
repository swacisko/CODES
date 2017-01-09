#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<algorithm>


using namespace std;


typedef double data_type;
typedef pair<data_type,data_type> PDT;


const long double INF = 1e10;
const long double EPS = 1e-8;

const data_type step = 0.0005;	
const data_type boundary = 10;
data_type left_boundary = -boundary;
data_type right_boundary = boundary;



/*
 * Function writes to the output (in this problem to the file) final answer to the problem.
 */ 
void writeFinalAnswer( data_type res, char* filename ){
	ofstream myfile;
	myfile.open(filename);
	myfile << res << endl;
	myfile.close();	
}

/*
 * Function reads and return data pf the polynomial in given point
 */ 
data_type getValueInPoint( data_type x ){
	cout << x << endl;
	data_type res;
	cin >> res;
	return res;	
}

/*
 * Creates and returns a pair (point, value_in_point) with lower value from given two possibilities.
 */ 
PDT getMinimalPair( data_type left, data_type left_value, data_type right, data_type right_value ){
	if( left_value < right_value ){
		return make_pair( left, left_value );
	}else return make_pair( right,right_value );
}

/*
 * Returns the pair with lower.
 */ 
PDT getLowerPair( PDT p, PDT q ){
	if( p.second < q.second ) return p;
	else return q;
}

/*
 * For given 3 points function finds local minimum. Of course this function does not work properly for all input data :) but is easy...
 */ 
PDT getLocalMinimum( data_type left, data_type left_value, data_type right, data_type right_value ){
	PDT local_min = getMinimalPair( left, left_value, right, right_value );
	
	if( abs( right - left ) < EPS ){ // if interval is really small, i return minimum of boundaries of the inrterval.
		return local_min;
	}
	
	data_type center = (left + right) / 2;
	data_type center_value = getValueInPoint( center );
	
	
	
	if( left_value < center_value && center_value < right_value ){	
		local_min = getLowerPair( local_min, getLocalMinimum( left, left_value, center, center_value ) );
		
	}else if( left_value > center_value && center_value > right_value ){
		local_min = getLowerPair( local_min, getLocalMinimum( center, center_value, right, right_value ) );
		
	}else if( left_value > center_value && right_value > center_value ){
		local_min = getLowerPair( local_min, getLocalMinimum( left, left_value, center, center_value ) );
		local_min = getLowerPair( local_min, getLocalMinimum( center, center_value, right, right_value ) );		
	}
	
	return local_min;
	
}



/**
 * Function responsible for calculating answer to the problem.
 * 
 */
data_type solve(){
	PDT total_min = make_pair( INF, INF );
	
	data_type left = -boundary - step;;
	data_type left_value = getValueInPoint(left);
	data_type right, right_value;
	
	for( data_type x = -boundary; x <= boundary; x += step ){
		right = x;
		right_value = getValueInPoint(right);
		total_min = getLowerPair( total_min, getLocalMinimum( left,left_value, right, right_value ) );	
		left = right;
		left_value = right_value;	
	}
	
	
	return total_min.first;
}

int main( int argc, char** argv ){

	cout << INF << endl;
	data_type finalAnswer = solve();
	writeFinalAnswer( finalAnswer, argv[1] );
	return 0;
}
