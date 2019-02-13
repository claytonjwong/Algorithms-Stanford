# Merge Sort
https://en.wikipedia.org/wiki/Merge_sort

## Contents
* [Lecture Slides](#lecture-slides)
* [Solution](#solution)
* [Build Instructions](#build-instructions)
* [Dependencies](#dependencies)

## Lecture Slides
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_01.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_02.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_03.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_04.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_05.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_07.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_08.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_09.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_10.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_11.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_12.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_13.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_14.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_15.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_16.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_17.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_18.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_19.png)
---
![](https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_20.png)
---

## Solution
```cpp

    /**
     *
     * Modern C++ implementation of Merge Sort algorithm to sort a collection
     *
     * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
     *
     **/
    
    
    #include <iostream>
    #include <vector>
    #include <algorithm>
    
    
    using namespace std;
    
    
    template< typename T >
    class Solution
    {
    public:
    
        using Collection = vector< T >;
    
        Collection mergeSort( const Collection& A )
        {
            return go({ A.begin(), A.end() });
        }
    
    private:
    
        Collection go( Collection&& A )
        {
            if( A.size() < 2 )
                return A;
            auto pivot = A.begin() + A.size() / 2;
            return merge( go({ A.begin(), pivot }), go({ pivot, A.end() }) );
        }
    
        Collection merge( Collection&& lhs, Collection&& rhs, Collection res={} ) // merge (res)ult
        {
            auto L = lhs.begin(), R = rhs.begin();
            while( L != lhs.end() && R != rhs.end() )
                res.push_back( ( *L < *R )? *L++ : *R++ );
            res.insert( res.end(), L, lhs.end() ), res.insert( res.end(), R, rhs.end() ); // append left-overs ( if applicable )
            return res;
        }
    
    };
    
    
    int main()
    {
        using Type = int;
    
        const Solution< Type >::Collection
            A_unsorted{ 9,5,6,3,2,8,0,4,1,7 },
            B_unsorted{ 3,9,7,1,2,8,6,5,0,4 },
            C_unsorted{ 3,2,9,7,1,3,7,2,8,1,6,5,0,8,0,4 };
    
        Solution< Type > s;
        auto
            A{ s.mergeSort( A_unsorted ) },
            B{ s.mergeSort( B_unsorted ) },
            C{ s.mergeSort( C_unsorted ) };
    
        assert( is_sorted( A.begin(), A.end() ) );
        assert( is_sorted( B.begin(), B.end() ) );
        assert( is_sorted( C.begin(), C.end() ) );
    
        cout << "A: "; copy( A.begin(), A.end(), ostream_iterator< Type >( cout, " " ) ); cout << endl;
        cout << "B: "; copy( B.begin(), B.end(), ostream_iterator< Type >( cout, " " ) ); cout << endl;
        cout << "C: "; copy( C.begin(), C.end(), ostream_iterator< Type >( cout, " " ) ); cout << endl;
    
    //    A: 0 1 2 3 4 5 6 7 8 9
    //    B: 0 1 2 3 4 5 6 7 8 9
    //    C: 0 0 1 1 2 2 3 3 4 5 6 7 7 8 8 9
    
        return 0;
    }

```

## Build Instructions
Use ```cmake``` to build this project:

```
    cmake --build cmake-build-debug --target merge_sort -- -j 4
```

## Dependencies
* [cmake.org](https://cmake.org)
