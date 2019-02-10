<h1 id="merge_sort">Merge Sort</h1>
<a href="https://en.wikipedia.org/wiki/Merge_sort">https://en.wikipedia.org/wiki/Merge_sort</a>
<h2>Contents</h2>
<ul>
  <li>
      <a href="#slides">Lecture Slides</a>
  </li>
  <li>
    <a href="#solution">Solution</a>
  </li>
  <li>
    <a href="#build">Build Instructions</a>
  </li>
  <li>
    <a href="#dependencies">Dependencies</a>
  </li>
</ul>

<h2 id="slides">Lecture Slides</h2>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_01.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_02.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_03.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_04.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_05.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_07.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_08.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_09.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_10.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_11.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_12.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_13.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_14.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_15.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_16.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_17.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_18.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_19.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/merge_sort/documentation/merge_20.png" />
<hr/>

<h2 id="solution">Solution</h2>
<pre>

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

</pre>

<h2 id="build">Build Instructions</h2>
<p>Use <code>cmake</code> to build this project:</p>

<pre>
    cmake --build cmake-build-debug --target merge_sort -- -j 4
</pre>

<h2 id="dependencies">Dependencies</h2>
<ul>
  <li>
    <a href="https://cmake.org/">cmake.org</a>
  </li>
</ul>

</body>
</html>