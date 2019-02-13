# Karatsuba Multiplication ( trivial templates )
https://en.wikipedia.org/wiki/Karatsuba_algorithm

## Contents
* [Lecture Slides](#lecture-slides)
* [Solution](#solution)
* [Build Instructions](#build-instructions)
* [Dependencies](#dependencies)

## Lecture Slides
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karatsuba_multiplication/documentation/mult_01.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karatsuba_multiplication/documentation/mult_02.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karatsuba_multiplication/documentation/mult_03.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karatsuba_multiplication/documentation/mult_04.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karatsuba_multiplication/documentation/mult_05.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karatsuba_multiplication/documentation/mult_06.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karatsuba_multiplication/documentation/mult_07.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/karatsuba_multiplication/documentation/mult_08.png)
---

## Solution
```cpp

    /**
     *
     * Modern C++ implementation of Karatsuba algorithm to perform multiplication of two integers 
     *
     * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
     *
     **/
     
    
    #include <iostream>
    
    
    using namespace std;
    
    
    template< typename Type >
    class Solution
    {
    public:
    
        Type multiply( Type x, Type y )
        {
            return go( x,y );
        }
    
    private:
    
        Type pow( Type N ){ return( N == 0 )? 1 : 10 * pow( N - 1); }
        Type log( Type N ){ return( N == 0 )? 0 : 1 + log( N / 10); }
    
        Type go( Type x, Type y )
        {
            if( x < 10 || y < 10 ) return x * y;
            auto i{ log(x) }, j{ log(y) }, N{ min(i,j) }, p{ pow(N/2) }, // (p)ivot
                a{ x / p }, b{ x % p },
                c{ y / p }, d{ y % p },
                u{ go(a,c) }, v{ go(a+b,c+d) }, w{ go(b,d) };
            return( u * pow( N )  +  ( v -u -w ) * pow( N/2 )  +  w );
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

```

## Build Instructions
Use ```cmake``` to build this project:

```
    cmake --build cmake-build-debug --target karatsuba_multiplication -- -j 4
```

## Dependencies
* [cmake.org](https://cmake.org)
