#ifndef ADDED_HASH_FUNCTIONS
#define ADDED_HASH_FUNCTIONS


template <class keyType >
class Hash1
{
public:
    unsigned int operator()( const string & key ) const
    {
        unsigned int computed_hash = 0;
        for(const char & character: key)
        {
            computed_hash =computed_hash * 131 +  character ;
        }
        static unsigned int FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return computed_hash^FIXED_RANDOM;
        //return computed_hash;
    }

};

template <class keyType >
class Hash2
{


public:

    unsigned int operator()( const string & key ) const
    {
        static const unsigned int FIXED_RANDOM1 = chrono::steady_clock::now().time_since_epoch().count();
        static const unsigned int FIXED_RANDOM2 = chrono::steady_clock::now().time_since_epoch().count();

        unsigned int computed_hash = FIXED_RANDOM1;
        for(const char & character: key)
        {
            computed_hash = (computed_hash * FIXED_RANDOM2) ^  character ;
        }
        return computed_hash;
    }
};




#endif // ADDED_HASH_FUNCTIONS
