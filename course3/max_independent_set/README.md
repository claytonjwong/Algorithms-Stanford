<h1 id="knapsack">Knapsack</h1>
<a href="https://en.wikipedia.org/wiki/Maximal_independent_set">https://en.wikipedia.org/wiki/Maximal_independent_set</a>
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
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_01.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_02.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_03.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_04.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_05.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_06.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_07.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_08.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_09.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_10.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_11.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_12.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_13.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_14.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_15.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_16.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_17.png" />
<img src="https://github.com/claytonjwong/Algorithms-Stanford/blob/master/course3/max_independent_set/documentation/mis_18.png" />

<h2 id="solution">Solution</h2>
<pre>

    #include "input.hpp"
    #include <iostream>
    #include <iomanip>
    #include <sstream>
    #include <vector>
    #include <map>
    #include <numeric>
    
    
    using namespace std;
    using Type = size_t;
    using Cost = Type;
    using Vertex = Type;
    using Graph = vector< Cost >; // Vertex id is implicitly the index of the (G)raph
    using Iter = typename vector< Cost >::iterator;
    using Memo = map< Vertex, Cost >;
    
    
    Memo reconstruct( Graph& G, Memo& memo, Memo max={} )
    {
        auto N{ G.size() };
        for( auto i{ long(N) }; i > 0; )
            if( memo[ i-1 ] == memo[ i ] )
                i -= 1;
            else
                max[ i ] = memo[ i ],
                i -= 2;
        return max;
    }
    
    
    namespace TopDown
    {
        class Solution
        {
        public:
    
            Memo max_independent_set( Graph& G, Memo memo={} )
            {
                go( G, G.end(), memo );
                return memo;
            }
    
        private:
    
            Cost go( Graph& G, Iter end, Memo& memo )
            {
                auto n = distance( G.begin(), end );
                for( auto it{ memo.find(n) }; it != memo.end(); ) // if found, return memoized cost for Vn
                {
                    auto cost{ it->second };
                    return cost;
                }
                auto Vn = ( n == 0 )? end : end-1; // end is non-inclusive, when n > 0, Vn is the last element in the range [ G.begin() : end )
                if( n == 0 ) return memo[ n ] = 0;
                if( n == 1 ) return memo[ n ] = ( *Vn );
                auto S1 = go( G, Vn, memo ),
                     S2 = go( G, Vn-1, memo ) + ( *Vn );
                return memo[ n ] = ( S1 > S2 )? S1 : S2;
            }
    
        }; // class Solution
    
    } // namespace TopDown
    
    
    namespace BottomUp
    {
        class Solution
        {
        public:
    
            Memo max_independent_set( Graph& G, Memo memo={} )
            {
                auto N{ G.size() };
                if( N == 0 )
                    return {};
                auto Vn = G.begin();
                Graph dp( N + 1 );
                memo[ 0 ] = dp[ 0 ] = 0;
                memo[ 1 ] = dp[ 1 ] = ( *Vn++ );
                for( auto i{ 2 }; i <= N; ++i )
                    memo[ i ] = dp[ i ] = max( dp[ i-1 ], dp[ i-2 ] + ( *Vn++ ) ); // note: *Vn is the same as G[ i-1 ] ( the i-th entry of G in terms of dp's (i)ndex )
                return memo;
            }
    
        }; // class Solution
    
    } // namespace BottomUp
    
    
    int main()
    {
        //
        // Top Down
        //
        {
            TopDown::Solution solution;
            Graph G;
            istringstream stream{ Assignment::Input };
            for( string line; getline( stream, line ); )
            {
                istringstream parser{ line };
                Cost cost{ 0 };
                parser >> cost;
                G.push_back( cost );
            }
            auto memo = solution.max_independent_set( G );
            auto max = reconstruct( G, memo );
            cout << "TopDown answer:  ";
            for( auto vertex: { 1, 2, 3, 4, 17, 117, 517, 997 } )
                cout << ( max.find( vertex ) != max.end() );
            cout << endl << endl;
        }
    
        //
        // Bottom Up
        //
        {
            BottomUp::Solution solution;
            Graph G;
            istringstream stream{ Assignment::Input };
            for( string line; getline( stream, line ); )
            {
                istringstream parser{ line };
                Cost cost{ 0 };
                parser >> cost;
                G.push_back( cost );
            }
            auto memo = solution.max_independent_set( G );
            auto max = reconstruct( G, memo );
            cout << "BottomUp answer: ";
            for( auto vertex: { 1, 2, 3, 4, 17, 117, 517, 997 } )
                cout << ( max.find( vertex ) != max.end() );
            cout << endl << endl;
        }
    
    //    TopDown answer:  10100110
    
    //    BottomUp answer: 10100110
    
        return 0;
    }

</pre>

<h2 id="build">Build Instructions</h2>
<p>Use <code>cmake</code> to build this project:</p>

<pre>
    cmake --build cmake-build-debug --target max_independent_set -- -j 4
</pre>

<h2 id="dependencies">Dependencies</h2>
<ul>
  <li>
    <a href="https://cmake.org/" target="_blank">cmake.org</a>
  </li>
</ul>

</body>
</html>