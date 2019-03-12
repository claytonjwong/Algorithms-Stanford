/**
 *
 * Modern C++ implementation of 2-SAT solution via Kosaraju's algorithm
 * to find the strongly connected components of a directed graph
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/


#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <queue>


using namespace std;
using Vertex = int;
using AdjacencyList = unordered_set< Vertex >;
using Graph = unordered_map< Vertex, AdjacencyList >;
using Seen = unordered_set< Vertex >;
using ConnectedComponents = vector< vector< Vertex > >;
using OrderedList = deque< Vertex >;
using Stack = vector< Vertex >;
using Unique = unordered_set< Vertex >;


class Solution
{
public:

    ConnectedComponents getSCC( Graph& G, ConnectedComponents CC={}, Stack stack={}, Seen seen={} )
    {
        auto L = topo_sort( reverse( G ) );
        for( auto cur: L )
        {
            if( seen.insert( cur ).second )
                stack.push_back( cur );         // push unseen (cur)rent vertex onto the stack
            Stack path;
            while( ! stack.empty() )
            {
                auto start{ stack.back() }; stack.pop_back(); path.push_back( start );
                for( auto adj: G[ start ] )
                    if( seen.insert( adj ).second )
                        stack.push_back( adj ); // push unseen (adj)acent vertex onto the stack
            }
            if( ! path.empty() )
                CC.emplace_back( path );
        }
        return CC;
    }

private:

    Graph reverse( Graph& G )
    {
        Graph R;
        for( auto& pair: G )
        {
            auto u{ pair.first };
            for( auto v: G[ u ] )   // u -> v
            {
                if( R.find( v ) == R.end() )
                    R[ v ] = {};
                R[ v ].insert( u ); // v -> u
            }
        }
        return R;
    }

    OrderedList topo_sort( Graph&& G, Stack stack={}, Seen seen={} )
    {
        OrderedList L;
        for( auto& pair: G )
        {
            auto cur{ pair.first };
            if( seen.insert( cur ).second )
                stack.push_back( cur );         // push unseen (cur)rent vertex onto the stack
            Stack path;
            while( ! stack.empty() )
            {
                auto start{ stack.back() }; stack.pop_back(); path.push_back( start );
                for( auto adj: G[ start ] )
                    if( seen.insert( adj ).second )
                        stack.push_back( adj ); // push unseen (adj)acent vertex onto the stack
            }
            for(; ! path.empty(); L.push_front( path.back() ), path.pop_back() );
        }
        return L;
    }

};


Graph readInput( const string& filename )
{
    Graph G;
    fstream stream{ filename };
    auto N{ 0 };
    for( string line; getline( stream, line ); )
    {
        istringstream parser{ line };
        if( N > 0 )
        {
            auto u{ 0 }, v{ 0 };
            parser >> u >> v;
            if( G.find( -u ) == G.end() ) G[ -u ] = {}; G[ -u ].insert( v );
            if( G.find( -v ) == G.end() ) G[ -v ] = {}; G[ -v ].insert( u );
        }
        else
        {
            parser >> N;
        }
    }
    return G;
}


bool test( const string& filename )
{
    Solution s;
    auto G = readInput( filename ); // (G)raph
    auto CC = s.getSCC( G );        // (C)onnected (C)omponents
    for( auto& C: CC )
    {
        Unique unique{ C.begin(), C.end() };
        for( auto v: unique )
            if( unique.find( -v ) != unique.end() )
                return false;
    }
    return true;
}


int main()
{
    cout << "answer: ";
    for( auto& filename:{ "2sat1.txt", "2sat2.txt", "2sat3.txt", "2sat4.txt", "2sat5.txt", "2sat6.txt" })
        cout << test( filename ), flush( cout );
    cout << endl;

    return 0;
}

