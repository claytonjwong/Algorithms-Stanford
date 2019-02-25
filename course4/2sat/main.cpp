/**
 *
 * Modern C++ implementation of 2-constraint satisfaction problem solved in polynomial asymptotic runtime
 * via randomized Papadimitriou local search algorithm
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/


#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <random>
#include <unordered_map>
#include <unordered_set>


using namespace std;
using Type = int;
struct Literal
{
    Type value{ 0 };
    bool assignment{ true }, constraint{ true };
};
struct Clause
{
    Literal first, second;
    bool isSatisfied(){ return( first.assignment == first.constraint ) || ( second.assignment == second.constraint ); }
};
using ClauseList = vector< Clause >;
using HClauseList = vector< shared_ptr< Clause > >;
using ValueClauseMap = unordered_map< Type, HClauseList >;
using ClauseSet = unordered_set< Clause >;


class Solution
{
public:

    bool isSatisfiable( ClauseList& clauseList )
    {
        auto N{ clauseList.size() };
        auto logN{ 0 }; for( auto n{ N }; n > 1; n >>= 1, ++logN );
        while( logN-- > 0 )
        {
            randomInitialAssignment( clauseList );
            for( auto i{ 0 }; i < 2 * N * N; ++i )
            {
                bool ok{ true };
                for( auto& clause: clauseList ) if( ! clause.isSatisfied() ) // arbitrarily choose first unsatisfied assignment to randomly flip
                {
                    ok = false;
                    flipRandomAssignment( clause );
                    break;
                }
                if( ok ) return ok;
            }
        }
        return false;
    }

private:

    using RandomDevice = random_device;
    using Generator = mt19937;
    using Distribution = uniform_int_distribution< int >;

    bool randomAssignment( RandomDevice randomDevice=RandomDevice() )
    {
        Generator randomGenerator{ randomDevice() };
        Distribution distribution{ 0, 1 };
        return distribution( randomGenerator );
    }

    void randomInitialAssignment( ClauseList& clauseList )
    {
        for( auto& clause: clauseList )
            clause.first.assignment = randomAssignment(),
            clause.second.assignment = randomAssignment();
    }

    void flipRandomAssignment( Clause& clause, RandomDevice randomDevice=RandomDevice() )
    {
        Generator randomGenerator{ randomDevice() };
        Distribution distribution{ 0, 1 };
        auto first = distribution( randomGenerator ); // randomly flip the value of the first xor second literal assignment
        if( first )
            clause.first.assignment ^= 1;
        else
            clause.second.assignment ^= 1;
    }

}; // class Solution


ClauseList readInput( const string& filename, ClauseList clauseList={} )
{
    fstream stream{ filename };
    auto N{ 0 };
    for( string line; getline( stream, line ); )
    {
        istringstream parser{ line };
        if( N > 0 )
        {
            Clause clause{ {0,true}, {0,true} };
            parser >> clause.first.value >> clause.second.value;
            if( clause.first.value < 0 )
                clause.first.value *= -1,
                clause.first.constraint = false;
            if( clause.second.value < 0 )
                clause.second.value *= -1,
                clause.second.constraint = false;
            clauseList.push_back( clause );
            continue;
        }
        parser >> N;
    }
    return clauseList;
}


int main()
{
    Solution solution;
    string ans;
    for( auto& filename: { "2sat1.txt", "2sat2.txt", "2sat3.txt", "2sat4.txt", "2sat5.txt", "2sat6.txt" } )
    {
        auto clauseList = readInput( filename );
        auto ok = solution.isSatisfiable( clauseList );
        ans.push_back( ok? '1': '0' );
    }
    cout << "answer: " << ans << endl; // answer: 111111


    return 0;
}
