<h1 id="array_inversions">Array Inversions</h1>
<a href="https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)">https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)</a>
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
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/array_inversions/documentation/inv_01.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/array_inversions/documentation/inv_02.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/array_inversions/documentation/inv_03.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/array_inversions/documentation/inv_04.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/array_inversions/documentation/inv_05.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/array_inversions/documentation/inv_06.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/array_inversions/documentation/inv_07.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/array_inversions/documentation/inv_08.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/array_inversions/documentation/inv_09.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/array_inversions/documentation/inv_10.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/array_inversions/documentation/inv_11.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/array_inversions/documentation/inv_12.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/array_inversions/documentation/inv_13.png" />
<hr/>
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course1/array_inversions/documentation/inv_14.png" />
<hr/>

<h2 id="solution">Solution</h2>
<pre>

    #include "input.hpp"
    #include <iostream>
    #include <vector>
    #include <sstream>
    
    
    using namespace std;
    
    
    template< typename Type >
    class Solution
    {
    public:
    
        using Collection = vector< Type >;
    
        size_t inversions( const Collection& A )
        {
            return go({ A.begin(), A.end() }).count;
        }
    
    private:
    
        struct Result
        {
            Collection A;
            size_t count{ 0 };
        };
    
        Result go( Collection&& A )
        {
            if( A.size() < 2 )
                return { A, 0 };
            auto pivot = A.begin() + A.size() / 2;
            return merge( go({ A.begin(), pivot }), go({ pivot, A.end() }) );
        }
    
        Result merge( Result&& lhs, Result&& rhs )
        {
            Result res{ {}, lhs.count + rhs.count }; // left + right inversions
            auto L = lhs.A.begin(), R = rhs.A.begin();
            while( L != lhs.A.end() && R != rhs.A.end() )
                if( *L < *R )
                    res.A.push_back( *L++ );
                else
                    res.A.push_back( *R++ ),
                    res.count += distance( L, lhs.A.end() ); // split inversions
            res.A.insert( res.A.end(), L, lhs.A.end() ), res.A.insert( res.A.end(), R, rhs.A.end() ); // append leftovers ( if applicable )
            return res;
        }
    
    };
    
    
    int main()
    {
        string line;
        stringstream stream{ Assignment::Input };
        Solution< size_t >::Collection A;
        for( size_t num{ 0 }; getline( stream, line ); A.push_back( num ) )
        {
            stringstream parser{ line };
            parser >> num;
        }
        Solution< size_t > s;
        cout << "answer: " << s.inversions( A ) << endl;
    
        // answer: 2407905288
    
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