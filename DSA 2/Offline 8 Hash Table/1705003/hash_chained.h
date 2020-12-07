#ifndef ADDED_HASH
#define ADDED_HASH
namespace HashChained
{

template < class keyType, class valueType >
class HashNode
{
public :

    keyType key ;
    valueType value;
    HashNode<keyType, valueType > * nextHashNode;

    HashNode(keyType key, valueType value, HashNode<keyType, valueType > * nextHashNode = 0 ):
        key(key), value(value), nextHashNode(nextHashNode)
    {

    }

    ~HashNode()
    {
        if(nextHashNode)
            delete nextHashNode;
    }

    friend ostream & operator << (ostream & os, HashNode < keyType, valueType > hn )
    {
        return os<<"{"<<hn.key <<":"<<hn.value<<"}";
    }
};



template < class keyType, class valueType, class HashFuncType = hash<keyType> >
class HashTable
{
private:
    unsigned int tableSize ;
    HashNode <keyType, valueType > * * tableOfPointer;
    HashFuncType HashFunc;

public :
    int total_collision = 0;
    int total_prob = 0;
    HashTable(unsigned int tableSize) : tableSize(tableSize)
    {
        tableOfPointer = new HashNode <keyType, valueType > * [ tableSize ];
        for(int i =0; i<tableSize ; i++)
        {
            tableOfPointer[i] = 0;
        }
    }
    ~HashTable()
    {
        for(int i=0; i<tableSize; i++)
            delete tableOfPointer[i];
    }

    bool Insert(const keyType & key,const valueType  & value)
    {

        unsigned int hashValue = HashFunc(key);
        unsigned int index = hashValue % tableSize;

        total_collision+= tableOfPointer[index] != 0 ;

        HashNode<keyType, valueType > *  newHashNode = new HashNode<keyType, valueType > (key, value);
        newHashNode->nextHashNode = tableOfPointer[index] ;
        tableOfPointer[index] = newHashNode;

        return 1;
    }

    bool Search(const keyType & key)
    {
        unsigned int hashValue = HashFunc(key);
        unsigned int index = hashValue % tableSize;

        HashNode<keyType, valueType > * entry = tableOfPointer[index];

        while(entry != 0 and entry-> key != key)
        {
            total_prob++;
            entry = entry->nextHashNode;
        }

        if(entry)
            return 1;
        else
            return 0;
    }
    void Delete(const keyType & key)
    {
        unsigned int hashValue = HashFunc(key);
        unsigned int index = hashValue % tableSize;

        HashNode<keyType, valueType > * prev = 0;
        HashNode<keyType, valueType > * entry = tableOfPointer[index];

        while(entry != 0 and entry-> key != key)
        {
            total_prob++;
            prev = entry;
            entry = entry->nextHashNode;
        }

        if(entry)
        {
            if(prev )
            {
                prev->nextHashNode = entry->nextHashNode;
            }
            else
            {
                tableOfPointer[index] = entry->nextHashNode;
            }

            entry->nextHashNode = 0;
            delete entry;
        }

    }

    int maximum_chain_length()
    {
        int ret = 0;
        for(int i=0; i<tableSize ; i++)
        {
            int length = 0;
            auto entry = tableOfPointer[i];
            while(entry!=0)
            {
                length++;
                entry=entry->nextHashNode;
            }
            ret = max(ret, length);
        }
        return ret;
    }


};

}


#endif // ADDED_HASH
