##
#
# Python implementation of Karatsuba algorithm to perform multiplication of two integers 
# 
# (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
#
##

def pow10( N ):
    if N == 0:
        return 1
    return 10 * pow10( N-1 )

def log10( N ):
    if N == 0:
        return 0
    return 1 + log10( N/10 )

def go( x, y ):
    if x < 10 or y < 10:
        return x * y
    i = log10( x )     # number of digits in x
    j = log10( y )     # number of digits in y
    N = min( i, j )    # minimum number of digits between x, y
    p = pow10( N/2 )   # pivot position 
    a = x / p          # a is the first half of x
    b = x % p          # b is the second half of x
    c = y / p          # c is the first half of y
    d = y % p          # d is the second half of y
    u = go( a, c )
    v = go( a+b, c+d )
    w = go( b, d )
    return u * pow10( N ) + ( v -u -w ) * pow10( N/2 ) + w

def multiply( x, y ):
    return go( x, y )

if __name__ == '__main__':
    print( multiply( 3, 7 ) )       # 21
    print( multiply( 20, 20 ) )     # 400
    print( multiply( 1234, 5678 ) ) # 7006652
    print( multiply( -11, 11 ) )    # -121
    print( multiply( -69, 31 ) )    # -2139