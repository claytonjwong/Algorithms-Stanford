#include <iostream>
#include <vector>
#include <functional>


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

    Heap() = default;
    ~Heap() = default;
    Heap( const Heap& ) = default;
    Heap( Heap&& ) = default;
    Heap& operator=( const Heap& ) = default;
    Heap& operator=( Heap&& ) = default;

    bool empty() const { return A.size() == 1; } // heap is empty when it only contains the sentinel

    void insert( Type value )
    {
        A.push_back( value );
        for( auto i{ A.size()-1 }; 0 < i && 0 < parent( i ) && Compare()( A[ i ], A[ parent( i ) ] ); i = parent( i ) )
            swap( A[ i ], A[ parent( i ) ] );
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
            if( left( i ) < A.size() && Compare()( A[left(i)], A[i] ) )
                L = A[ left( i ) ],
                isViolation = true;
            if( right( i ) < A.size() && Compare()( A[right(i)], A[i] ) )
                R = A[ right( i ) ],
                isViolation = true;
            if( isViolation )
                next = ( Compare()( L, R ) )? left( i ) : right( i );
        }
        return result;
    }

private:

    vector< Type > A{ max }; // sentinel for 1-based indexing ( easy to find parent and left/right children )

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
        if( lo.empty() || value < lo.top() )
            lo.insert( value );
        else
            hi.insert( value );

        if( lo.size() + 1 < hi.size() ) lo.insert( hi.extract() );
        if( hi.size() + 1 < lo.size() ) hi.insert( lo.extract() );
    }

    Type getMedian() const // TODO: calculate median
    {
        if( lo.empty() && hi.empty() )
            throw out_of_range{ "empty collection" };
        else
        if( hi.empty() )
            return lo.top();

        Type result;

        return result;
    }

private:

    Heap< Type, Greater< Type > > lo;
    Heap< Type, Lesser< Type > > hi;

};


int main()
{
    using Type = int;
    using Collection = vector< Type >;
    using Compare = Lesser< Type >;
    auto C = heap_sort< Type, Compare >({ 5,9,6,7,3,8,2,1,0,4 });
    assert( is_sorted( C.cbegin(), C.cend(), Compare() ) );
    copy( C.cbegin(), C.cend(), ostream_iterator< Type >( cout, " " ) );
    return 0;
}