
#ifndef ADDED_HASH_DOUBLE
#define ADDED_HASH_DOUBLE





namespace HashDouble
{

template < class keyType, class valueType>
class Entry
{
public :
    keyType key ;
    valueType value ;
    bool deleted ;
    Entry(keyType key, valueType value) : key(key), value(value), deleted(0)
    {

    }

};

template < class keyType, class valueType, class HashFuncType = hash<keyType>, class auxHashFuncType = hash<keyType> >
class HashTable
{
private:
    unsigned int tableSize ;
    Entry < keyType, valueType > * * entries;

    HashFuncType HashFunc;
    auxHashFuncType auxHashFunc;
public :

    int total_collision= 0 ;
    int total_prob = 0;

    HashTable(int tableSize) : tableSize(tableSize)
    {
        entries = new Entry < keyType, valueType > * [ tableSize ];

        for(int i=0; i<tableSize ; i++)
            entries[i] = 0;
    }
    ~HashTable()
    {
        delete [] entries ;
    }

    bool Insert(const keyType & key,const valueType  & value)
    {
        int index = HashFunc(key) % tableSize;
        int offset =max(auxHashFunc(key) % tableSize, 1U);

//        DBG(index);
//        DBG(offset);

        int loop_counter = 0;
        while(entries[index] and entries[index]->deleted == 0 )
        {
            total_collision++;
            total_prob++;
            index = (index + offset) % tableSize;


            if( ++loop_counter > tableSize)
            {
                return 0;
            }
        }


        if(entries[index])
        {
            assert(entries[index]->deleted);
            delete entries[index];
        }
        entries[index] = new Entry<keyType, valueType> (key, value);

        return 1;

    }

    bool Search(const keyType & key )
    {
        int index = HashFunc(key) % tableSize;
        int offset =max(auxHashFunc(key) % tableSize, 1U);

        int loop_counter = 0;

        while(entries[index])
        {
            total_prob++;

            if(entries[index]->deleted == 0 and entries[index]->key == key)
                return 1;

            index = (index + offset) % tableSize;

            if( ++loop_counter > tableSize )
            {
                return 0;
            }

        }
        return 0;

    }
    void Delete(const keyType & key)
    {
        int index = HashFunc(key) % tableSize;
        int offset =max(auxHashFunc(key) % tableSize, 1U);

        int loop_counter = 0;

        while(entries[index])
        {
            total_prob++;

            if(entries[index]->deleted == 0 and entries[index]->key == key)
            {
                entries[index]->deleted = 1;
                return ;
            }

            if( ++loop_counter > tableSize )
            {
                return ;
            }
        }


    }
};

}


#endif // ADDED_HASH_DOUBLE
