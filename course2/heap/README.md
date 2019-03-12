# Heap ( data structure )
https://en.wikipedia.org/wiki/Heap_(data_structure)

## Contents
* [Lecture](#lecture)
* [Lecture Slides](#lecture-slides)
* [Solution](#solution)
* [Build Instructions](#build-instructions)
* [Dependencies](#dependencies)

# Lecture
* [Video](https://www.coursera.org/lecture/algorithms-graphs-data-structures/data-structures-overview-WHOPA)

## Lecture Slides
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/heap/documentation/heap_01.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/heap/documentation/heap_02.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/heap/documentation/heap_03.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/heap/documentation/heap_04.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/heap/documentation/heap_05.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/heap/documentation/heap_06.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/heap/documentation/heap_07.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/heap/documentation/heap_08.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/heap/documentation/heap_09.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/heap/documentation/heap_10.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/heap/documentation/heap_11.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/heap/documentation/heap_12.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/heap/documentation/heap_13.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/heap/documentation/heap_14.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course2/heap/documentation/heap_15.png)
---

## Solution
```cpp

    /**
     *
     * Modern C++ implementation of a Heap data structure
     *
     * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
     *
     **/
    
    
    #include "input.hpp"
    #include <iostream>
    #include <sstream>
    #include <vector>
    #include <functional>
    #include <numeric>
    
    
    using namespace std;
    
    
    template< typename Type >
    struct Lesser{ bool operator()( const Type& lhs, const Type& rhs ) const { return lhs < rhs; } };
    
    template< typename Type >
    struct Greater{ bool operator()( const Type& lhs, const Type& rhs ) const { return lhs > rhs; } };
    
    
    template< typename Type, typename Compare >
    class Heap
    {
    public:
    
        using Collection = vector< Type >;
        static const Type min{ numeric_limits< Type >::min() };
        static const Type max{ numeric_limits< Type >::max() };
    
        size_t size() const { return A.size() - 1; } // sentinel exists at A[ 0 ], so subtracting by one is OK
        bool empty() const { return A.size() == 1; } // heap is empty when it only contains the sentinel
    
        void insert( Type value )
        {
            A.push_back( value );
            for( auto i{ A.size()-1 }; 0 < i && 0 < parent( i ) && Compare()( A[ i ], A[parent( i )] ); i = parent( i ) )
                swap( A[ i ], A[parent( i )] );
        }
    
        Type top() const
        {
            if( empty() )
                throw out_of_range{ "heap is empty" };
            return A[ 1 ];
        }
    
        Type extract()
        {
            if( empty() )
                throw out_of_range{ "heap is empty" };
            auto result{ A[ 1 ] };
            swap( A[ 1 ], A.back() ), A.pop_back();
            bool isViolation{ true };
            for( auto i{ 1 }, next{ 1 }; isViolation; swap( A[ i ], A[ next ] ), i = next )
            {
                isViolation = false;
                Type L = { Compare()(0,1)? max : min }, R{ Compare()(0,1)? max : min };
                if( left( i ) < A.size() && Compare()( A[left( i )], A[ i ] ) )
                    L = A[left( i )],
                    isViolation = true;
                if( right( i ) < A.size() && Compare()( A[right( i )], A[ i ] ) )
                    R = A[right( i )],
                    isViolation = true;
                if( isViolation )
                    next = ( Compare()( L, R ) )? left( i ) : right( i );
            }
            return result;
        }
    
    private:
    
        vector< Type > A{ Compare()(0,1)? max : min }; // sentinel for 1-based indexing ( easy to find parent and left/right children )
    
        size_t parent( size_t i ){ return i >> 1; }
        size_t left( size_t i ){ return i << 1; }
        size_t right( size_t i ){ return ( i << 1 ) + 1; }
    
    };
    
    template< typename Type, typename Compare >
    typename Heap< Type, Compare >::Collection heap_sort(
        typename Heap< Type, Compare >::Collection&& C, Heap< Type, Compare > heap={},
        typename Heap< Type, Compare >::Collection sorted={} )
    {
        for( auto& element: C )
            heap.insert( element );
        for(; ! heap.empty(); sorted.emplace_back( heap.extract() ) );
        return sorted;
    }
    
    
    template< typename Type >
    class MedianMaintainer
    {
    public:
    
        using Collection = vector< Type >;
    
        void insert( const Type& value )
        {
            ( lo.empty() || value < lo.top() )? lo.insert( value ) : hi.insert( value ); // use lo.top() as insertion pivot
            if( lo.size()     < hi.size() ) lo.insert( hi.extract() ); // Note: balance lo/hi heaps, such that
            if( hi.size() + 1 < lo.size() ) hi.insert( lo.extract() ); //       median is always lo.top()
        }
    
        Type getMedian() const // always extract median from lo ( insert() ensures lo.top() is always the median )
        {
            if( lo.empty() )
                throw out_of_range{ "empty collection" };
    
            return lo.top();
        }
    
    private:
    
        Heap< Type, Greater< Type > > lo;
        Heap< Type, Lesser< Type > > hi;
    
    };
    
    
    int main()
    {
        //
        // heap sort
        //
        using Type = int;
        using Collection = vector< Type >;
        using Compare = Lesser< Type >;
        auto C = heap_sort< Type, Compare >({ 5,9,6,7,3,8,2,1,0,4 });
        assert( is_sorted( C.cbegin(), C.cend(), Compare() ) );
        copy( C.cbegin(), C.cend(), ostream_iterator< Type >( cout, " " ) );
        cout << endl << endl;
    
        //
        // median maintenance
        //
        MedianMaintainer< Type > MM;
        Collection medians;
        stringstream stream{ INPUT };
        for( string line; getline( stream, line ); )
        {
            Type value;
            stringstream parser{ line };
            parser >> value;
            MM.insert( value );
            medians.push_back( MM.getMedian() );
        }
        auto answer = accumulate( medians.cbegin(), medians.cend(), 0 ) % 10000;
        cout << "answer: " << answer << endl;
        
        return 0;
    }

```

## Build Instructions
Use ```cmake``` to build this project:

```
    cmake --build cmake-build-debug --target heap -- -j 4
```

## Dependencies
* [cmake.org](https://cmake.org)
