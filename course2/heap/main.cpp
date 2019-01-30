#include <iostream>
#include <vector>


using namespace std;


//template< typename Type, typename Collection = vector< Type >, typename Compare = std::less<typename Collection::value_type> >
template< typename Type >
class Heap
{
public:

    using Collection = vector< Type >;
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
        for( auto i{ A.size()-1 }; 0 < i && 0 < parent( i ) && A[ i ] < A[ parent( i ) ]; i = parent( i ) )
            swap( A[ i ], A[ parent( i ) ] );
    }

    Type extractMin()
    {
        if( empty() )
            return max;
        auto result{ A[ 1 ] };
        swap( A[ 1 ], A.back() ), A.pop_back();
        bool isViolation{ true };
        for( auto i{ 1 }, min{ 1 }; isViolation; swap( A[ i ], A[ min ] ), i = min )
        {
            isViolation = false;
            auto L{ max }, R{ max };
            if( left( i ) < A.size() &&  A[ i ] > A[ left( i ) ] )
                L = A[ left( i ) ],
                isViolation = true;
            if( right( i ) < A.size() && A[ i ] > A[ right( i ) ] )
                R = A[ right( i ) ],
                isViolation = true;
            if( isViolation )
                min = ( L < R )? left( i ) : right( i );
        }
        return result;
    }

private:

    vector< Type > A{ max }; // sentinel for 1-based indexing ( easy to find parent and left/right children )

    size_t parent( size_t i ){ return i >> 1; }
    size_t left( size_t i ){ return i << 1; }
    size_t right( size_t i ){ return ( i << 1 ) + 1; }

};

template< typename Type >
typename Heap< Type >::Collection heap_sort( typename Heap< Type >::Collection&& C, Heap< Type > heap={}, typename Heap< Type >::Collection sorted={} )
{
    for( auto& element: C )
        heap.insert( element );
    for(; ! heap.empty(); sorted.emplace_back( heap.extractMin() ) );
    return sorted;
}


template< typename Type >
class MedianMaintainer
{
public:

    void insert( const Type& value )
    {
        if( lo_.size() == hi_.size() )
            lo_.insert( value );
        else
            hi_.insert( value );
    }

    Type getMedian() const
    {
        Type result;

        return result;
    }

private:

    Heap< Type > lo_, hi_;

};


int main()
{
    using Type = int;
    auto C = heap_sort< Type >({ 5,9,6,7,3,8,2,1,0,4 });
    assert( is_sorted( C.cbegin(), C.cend() ) );
    copy( C.cbegin(), C.cend(), ostream_iterator< Type >( cout, " " ) );
    return 0;
}