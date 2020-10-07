#ifndef PAIR_ADDED
#define PAIR_ADDED

template < class T1 , class T2 >
class Pair
{
public :
    T1 first;
    T2 second;
    Pair( const T1 & first =0,const  T2 & second =0) : first(first) , second ( second) {}
};

#endif // PAIR_ADDED
