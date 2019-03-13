##
#
# Python implementation of Merge Sort algorithm
# 
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

def merge_sort( A ):
    return go( A )

def go( A ):
    if len( A ) < 2:
        return A
    P = len( A ) // 2
    return merge( go( A[ :P ] ), go( A[ P: ] ) )

def merge( L, R ):
    A = []
    i = 0
    j = 0
    while i < len( L ) and j < len( R ):
        if L[ i ] < R[ j ]:
            A.append( L[ i ] )
            i += 1
        else:
            A.append( R[ j ] )
            j += 1
    A.extend( L[ i: ] )
    A.extend( R[ j: ] )
    return A

if __name__ == '__main__':
    A = [ 7, 9, 2, 4, 1, 3, 8, 5, 6, 0 ]
    A = merge_sort( A )
    print( "A: " )
    for x in A:
        print( x )

