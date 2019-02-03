#include <iostream>


using namespace std;


template< typename Type >
class Solution
{
public:

    Type multiply( const Type x, const Type y )
    {
        return go( x,y );
    }

private:

    Type POW_10( Type N ){ return( N == 0 )? 1 : 10 * POW_10( N - 1 ); }
    Type LOG_10( Type N ){ return( N == 0 )? 0 : 1 + LOG_10( N / 10 ); }

    Type go( const Type x, const Type y )
    {
        if( x < 10 || y < 10 ) return x * y;
        auto i{ LOG_10(x) }, j{ LOG_10(y) }, N{ min(i,j) }, p{ POW_10(N/2) }, // (p)ivot
            a{ x / p }, b{ x % p },
            c{ y / p }, d{ y % p },
            u{ go(a,c) }, v{ go(a+b,c+d) }, w{ go(b,d) };
        return( u * POW_10(N)  +  (v-u-w) * POW_10(N/2)  +  w );
    }

};


int main()
{
    Solution< int > s;
    cout << s.multiply( 3, 7 ) << endl;
    cout << s.multiply( 20, 20 ) << endl;
    cout << s.multiply( 1234, 5678 ) << endl;
    cout << s.multiply( -11, 11 ) << endl;
    cout << s.multiply( -69, -31 ) << endl;

//    21
//    400
//    7006652
//    -121
//    2139
    
    return 0;
}