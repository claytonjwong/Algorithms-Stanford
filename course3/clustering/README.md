# Clustering
[https://en.wikipedia.org/wiki/Cluster_analysis](https://en.wikipedia.org/wiki/Cluster_analysis)

## Contents
* [Lecture](#lecture)
* [Lecture Slides](#lecture-slides)
* [Solution](#solution)
* [Build Instructions](#build-instructions)
* [Dependencies](#dependencies)

# Lecture
* [Video](https://www.coursera.org/lecture/algorithms-greedy/application-to-clustering-QWubN)

## Lecture Slides
![](documentation/clustering_01.png)
---
![](documentation/clustering_02.png)
---
![](documentation/clustering_03.png)
---
![](documentation/clustering_04.png)
---
![](documentation/clustering_05.png)
---
![](documentation/clustering_06.png)
---
![](documentation/clustering_07.png)
---
![](documentation/clustering_08.png)
---

## Solution
```cpp

    /**
     *
     * Modern C++ implementation of K-clustering algorithm with Union-Find data structure
     *
     * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
     *
     **/
    
    
    #include "input.hpp"
    #include <iostream>
    #include <iomanip>
    #include <sstream>
    #include <fstream>
    #include <unordered_set>
    #include <unordered_map>
    #include <map>
    #include <set>
    #include <vector>
    
    
    using namespace std;
    
    
    template< typename Type >
    class Solution
    {
    public:
    
        using Vertex = Type;
        using Cost = Type;
        struct Edge
        {
            Vertex tail{ 0 }, head{ 0 };
            bool operator==( const Edge& rhs ) const { return tail == rhs.tail && head == rhs.head; }
        };
        struct Hash{ size_t operator()( const Edge& e ) const { return e.tail << 16 + e.head; } };
        using Edges = unordered_map< Edge, Cost, Hash >;
        using AdjacencyList = unordered_set< Vertex >;
        using Graph = unordered_map< Vertex, AdjacencyList >;
        using EdgeCost = pair< Edge, Cost >;
        using Buckets = unordered_map< size_t, size_t >;
        using Leads = unordered_set< Type >;
        using Hammed = bitset< 24 >;
    
        Cost maxSpacingKClusters( const string& input, size_t K )
        {
            Graph G;
            Edges E;
            istringstream stream{ input };
            for( string line; getline( stream, line ); )
            {
                stringstream parser{ line };
                Type u{ 0 }, v{ 0 }, cost{ 0 };
                parser >> u >> v >> cost;
                if( G.find( u ) == G.end() ) G[ u ] = {};
                if( G.find( v ) == G.end() ) G[ v ] = {};
                G[ u ].insert( v );
                G[ v ].insert( u );
                E.insert({ {u,v}, cost });
                E.insert({ {v,u}, cost });
            }
            auto Compare = []( const EdgeCost& lhs, const EdgeCost& rhs ){ return lhs.second < rhs.second; };
            multiset< EdgeCost, decltype( Compare )> edges{ E.begin(), E.end(), Compare };
            Leads leads;
            transform( G.begin(), G.end(), inserter( leads, leads.end() ), []( auto& pair )
            {
                auto vertex{ pair.first };
                return vertex;
            });
            Clusters clusters{ leads };
            Cost cost{ 0 };
            for( auto& edge: edges )
            {
                auto u{ edge.first.tail },
                     v{ edge.first.head };
                auto lu{ clusters.Find( u ) },
                     lv{ clusters.Find( v ) };
                if( lu == lv )
                    continue;
                if( clusters.size() <= K )
                {
                    cost = edge.second;
                    break;
                }
                clusters.Union( lu, lv );
            }
            return cost;
        }
    
        size_t maxClusters()
        {
            Buckets buckets;
            Leads leads;
            string line;
            for( fstream stream{ "hamming.txt" }; getline( stream, line ); )
            {
                line.erase( remove( line.begin(), line.end(), ' ' ), line.end() );
                Hammed hammed{ line };
                auto num{ hammed.to_ulong() };
                ++buckets[ num ];
                leads.insert( num );
            }
            Clusters clusters{ leads };
            for( auto& pair: buckets )
            {
                auto num{ pair.first };
                for( auto i{ 0 }; i < 24; ++i )
                {
                    Hammed alt{ num }; // (alt)ernative number to be manipulated as "hamming distance" away from (num)ber
                    alt.flip( i );
                    auto match = alt.to_ulong();
                    if( buckets.find( match ) != buckets.end() )
                        clusters.Union( num, match );
                    for( auto j{ i+1 }; j < 24; ++j )
                    {
                        alt.flip( j );
                        match = alt.to_ulong();
                        if( buckets.find( match ) != buckets.end() )
                            clusters.Union( num, match );
                        alt.flip( j );
                    }
                }
            }
            return clusters.size();
        }
    
    private:
    
        class Clusters
        {
        public:
    
            Clusters( Leads& leads ) : N_{ leads.size() }
            {
                for( auto x: leads )
                    lead_[ x ] = x;
            }
    
            void Union( Type u, Type v )
            {
                auto lu{ Find( u ) },
                     lv{ Find( v ) };
                if( lu == lv )
                    return;
                lead_[ lu ] = lv, --N_; // arbitrary lead choice and decrement N
            }
    
            Type Find( Type x )
            {
                if( lead_[ x ] == x )
                    return x;
                else
                    return lead_[ x ] = Find( lead_[ x ] );
            }
    
            size_t size()
            {
                return N_;
            }
    
        private:
    
            size_t N_;
            using Leader = unordered_map< Type, Type >;
            Leader lead_;
    
        };
    
    };
    
    
    int main()
    {
        using Type = size_t;
        Solution< Type > s;
    
        //
        // part 1
        //
        auto K{ 4 };
        auto answer_part1 = s.maxSpacingKClusters( Assignment1::Input, K );
        cout << "answer ( part 1 ): " << answer_part1 << endl << endl;
    
        //
        // part 2
        //
        auto answer_part2 = s.maxClusters();
        cout << "answer ( part 2 ): " << answer_part2 << endl << endl;
    
        return 0;
    }

```

## Build Instructions
Use ```cmake``` to build this project:

```
    cmake --build cmake-build-debug --target clustering -- -j 4
```

## Dependencies
* [cmake.org](https://cmake.org)
