# Quick Sort
https://en.wikipedia.org/wiki/Quicksort

## Contents
* [Lecture](#lecture)
* [Lecture Slides](#lecture-slides)
* [Probability](#probability)
* [Solution](#solution)
* [Build Instructions](#build-instructions)
* [Dependencies](#dependencies)

# Lecture
* [Video](https://www.coursera.org/lecture/algorithms-divide-conquer/quicksort-overview-Zt0Ti)

## Lecture Slides
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_01.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_02.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_03.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_04.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_05.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_06.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_07.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_08.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_09.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_10.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_11.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_12.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_13.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_14.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_15.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_16.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_17.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_18.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_19.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_20.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_21.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_22.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_23.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_24.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_25.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_26.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_27.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_28.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_29.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_30.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_31.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_32.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_33.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_34.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_35.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_36.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_37.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_38.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_39.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_40.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_41.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_42.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_43.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/quick_44.png)

## Probability
* [Probability ( part 1 )](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/probability.pdf)
* [Probability ( part 2 )](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/quick_sort/documentation/probability2.pdf)

## Solution
```cpp

    /**
     *
     * Modern C++ implementation of Quick Sort algorithm to sort a collection
     *
     * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
     *
     **/
     
    
    #include "input.hpp"
    #include <iostream>
    #include <vector>
    #include <random>
    #include <sstream>
    
    
    using namespace std;
    
    
    enum class PivotChoice{ Left, Median, Right, Random };
    
    
    template< typename Type >
    class Solution
    {
    public:
    
        using Collection = vector< Type >;
        using Iter = typename Collection::iterator;
    
        size_t quickSort( Collection& A, const PivotChoice pivotChoice = PivotChoice::Random  )
        {
            return go( A, A.begin(), A.end(), pivotChoice );
        }
    
    private:
    
        size_t go( Collection& A, Iter L, Iter R, const PivotChoice PC ) // go() sorts from [ L : R ),
        {                                                                // that is, from L (inclusive) to R (non-inclusive)
            if( L >= R )
                return 0; // base case, 0 comparisons performed
    
            choosePivot( L, R, PC );
            auto P = partition( A, L, R ); // (P)ivot
            auto M = distance( L, R );     // Note: M is the distance from L to R, add ( M - 1 ) to the running total
            return ( M - 1 )               //       ( subtract one to NOT include the pivot as a comparison )
                 + go( A, L, P, PC )
                 + go( A, P+1, R, PC );
        }
    
        Iter partition( Collection& A, Iter L, Iter R )
        {
            auto threshold{ L }, less{ L+1 };
            for( auto more{ less }; more != R; ++more )
                if( *more < *threshold )
                    iter_swap( less++, more );
            auto pivot{ less-1 };
            iter_swap( L, pivot );
            return pivot;
        }
    
        void choosePivot( Iter& L, Iter& R, const PivotChoice PC )
        {
            if( PC == PivotChoice::Left )
            {
                //
                // question #1: always use left-most [ L : R ) as pivot ( no-op: by default L is used as pivot )
                //
                iter_swap( L, L );
            }
            else if( PC == PivotChoice::Right )
            {
                //
                // question #2: always use right-most [ L : R ) as pivot ( note: this is R-1 since R is non-inclusive )
                //
                iter_swap( L, R-1 );
            }
            else if( PC == PivotChoice::Median )
            {
                //
                // question #3: use median from [ L : R ) as pivot ( note: the right-most value is at R-1 since R is non-inclusive )
                //
                auto M = L + ceil( distance( L, R ) / 2.0 ) - 1;                 // (M)iddle
                Collection C{ *L, *M, *( R-1 ) };                                // Three pivot (C)andidates: (L)eft-most, (M)iddle, (R)ight-most element in [ L : R )
                sort( C.begin(), C.end() );                                      // median is the middle element C[ 1 ] for the sorted array C of size 3
                auto median = ( C[ 1 ] == *L )? L  : ( C[ 1 ] == *M )? M  : R-1; // find corresponding iterator
                iter_swap( L, median );                                          // use median as pivot
            }
            else if( PC == PivotChoice::Random )
            {
                //
                // extra credit: use random value from [ L : R ) for pivot
                //
                iter_swap( L, random( L, R ) );
            }
        }
    
        using RandomDevice = random_device;
        using Generator = mt19937;
        using Distribution = uniform_int_distribution< int >;
    
        Iter random( Iter L, Iter R, RandomDevice randomDevice=RandomDevice() )
        {
            Generator randomGenerator{ randomDevice() };
            int size = distance( L, R-1 );        // R-1 since R is non-inclusive
            Distribution distribution{ 0, size }; // distribution from [ 0 : size ], that is 0 ( inclusive ) to size ( inclusive )
            return L + distribution( randomGenerator );
        }
    
    };
    
    
    int main()
    {
        using Type = size_t;
        Solution< Type > s;
        Solution< Type >::Collection A;
        stringstream stream{ INPUT };
        for( string line; getline( stream, line ); )
        {
            stringstream parser{ line };
            Type number{ 0 };
            parser >> number;
            A.push_back( number );
        }
    
        Solution< Type >::Collection Q1{ A };
        cout << "Question #1 ( Pivot is Left ):   " << s.quickSort( Q1, PivotChoice::Left ) << endl;
        assert( is_sorted( Q1.cbegin(), Q1.cend() ) );
    
        Solution< Type >::Collection Q2{ A };
        cout << "Question #2 ( Pivot is Right ):  " << s.quickSort( Q2, PivotChoice::Right ) << endl;
        assert( is_sorted( Q2.cbegin(), Q2.cend() ) );
    
        Solution< Type >::Collection Q3{ A };
        cout << "Question #3 ( Pivot is Median ): " << s.quickSort( Q3, PivotChoice::Median ) << endl;
        assert( is_sorted( Q3.cbegin(), Q3.cend() ) );
    
        Solution< Type >::Collection Q4{ A };
        cout << "Question #4 ( Pivot is Random ): " << s.quickSort( Q4, PivotChoice::Random ) << endl;
        assert( is_sorted( Q4.cbegin(), Q4.cend() ) );
    
        return 0;
    }

```

## Build Instructions
Use ```cmake``` to build this project:

```
    cmake --build cmake-build-debug --target quick_sort -- -j 4
```

## Dependencies
* [cmake.org](https://cmake.org)
