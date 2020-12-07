
#ifndef ADDED_HASH_CUSTOM
#define ADDED_HASH_CUSTOM





namespace HashCustom
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

    static const unsigned int C1 = 97;
    static const unsigned int C2 = 101;


    unsigned int customHash(unsigned int h1, unsigned int h2,unsigned int i)
    {

        return h1 + i * h2 * C1 + i * i * C2 ;
    }

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
        unsigned int h1 = HashFunc(key);
        unsigned int h2 = auxHashFunc(key);

        for(int i=0; i<tableSize ; i++)
        {
            total_collision ++;
            total_prob ++;
            int index = customHash(h1,h2, i) % tableSize;
            if(entries[index] == 0 or entries[index]->deleted )
            {
                total_collision += i>0;
                if(entries[index])
                {
                    assert(entries[index]->deleted);
                    delete entries[index];
                }
                entries[index] = new Entry<keyType, valueType> (key, value);
                return 1;
            }

        }
        return 0;

    }

    bool Search(const keyType & key )
    {
        unsigned int h1 = HashFunc(key);
        unsigned int h2 = auxHashFunc(key);

        for(int i=0; i<tableSize ; i++)
        {
            total_prob ++;
            int index = customHash(h1,h2, i) % tableSize;
            if(entries[index] == 0)
                return 0;
            else if(entries[index]->deleted == 0 and entries[index]->key == key)
                return 1;
        }
        return 0;
    }



    void Delete(const keyType & key)
    {
        unsigned int h1 = HashFunc(key);
        unsigned int h2 = auxHashFunc(key);

        for(int i=0; i<tableSize ; i++)
        {
            total_prob ++;
            int index = customHash(h1,h2, i) % tableSize;
            if(entries[index] == 0)
                return ;
            else if(entries[index]->deleted == 0 and entries[index]->key == key)
            {
                entries[index]->deleted = 1;
                return ;
            }
        }
    }
};

}


#endif // ADDED_HASH_CUSTOM
