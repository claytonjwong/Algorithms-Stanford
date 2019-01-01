#include <iostream>
#include <cmath>


using namespace std;


template< typename T >
T POW_10( const T N ){ return static_cast< T >( pow( 10, N ) ); }

template< typename T >
T LOG_10( const T X ){ auto N{ 1 }; while( POW_10( N ) <= X ){ ++N; }; return N; }


template< typename T >
class Solution
{
    T go( const T x, const T y )
    {
        if( x < 10 || y < 10 ) return x * y;
        auto i{ LOG_10(x) }, j{ LOG_10(y) }, N{ min(i,j) }, p{ POW_10(N/2) }, // (p)ivot
             a{ x / p }, b{ x % p },
             c{ y / p }, d{ y % p },
             u{ go(a,c) }, v{ go(a+b,c+d) }, w{ go(b,d) };
        return( u * POW_10(N)  +  (v-u-w) * POW_10(N/2)  +  w );
    }

public:

    T multiply( const T x, const T y )
    {
        return go( x,y );
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

    return 0;
}