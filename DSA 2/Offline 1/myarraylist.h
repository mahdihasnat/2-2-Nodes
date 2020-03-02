#ifndef ADDED_ARRAYLIST
#define ADDED_ARRAYLIST 1

#include<string.h>

#define BLOCK_SIZE 3
template <typename T>
class ArrayList
{
    T *arr;
    int arr_size, size;
    typedef T *iterator;

public:
    ArrayList();
    ~ArrayList();
    int searchItem(T item);
    void insertItem(T item);
    void removeItem(T item);
    void removeItemAt(int position);
    T getItem(int position);
    int getLength();
    bool empty();
    void printList();

    iterator begin()
    {
        return arr;
    }

    iterator end()
    {
        return arr + size;
    }
};

template <typename T>
ArrayList<T>::ArrayList()
{
    arr_size = BLOCK_SIZE;
    arr = new T[arr_size];
    size = 0;
}
template <typename T>
ArrayList<T>::~ArrayList()
{
    delete[] arr;
    arr = 0;
}

template <typename T>
int ArrayList<T>::searchItem(T item)
{
    for (int i = 0; i < size; i++)
        if (arr[i] == item)
            return i;
    return -1;
}

template <typename T>
void ArrayList<T>::insertItem(T item)
{
    if (size + 1 > arr_size)
    {
        T *newarr = new T[arr_size * 2];
        memcpy(newarr, arr, sizeof(T) * arr_size);
        delete[] arr;
        arr = newarr;
        arr_size *= 2;
    }
    arr[size++] = item;
}

template <typename T>
void ArrayList<T>::removeItem(T item)
{
    int position = searchItem(item);
    if (position >= 0)
        removeItemAt(position);
}

template <typename T>
void ArrayList<T>::removeItemAt(int position)
{
    if (position < 0 or position >= size)
        return;
    for (int i = position; i < size - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    size--;
}

template <typename T>
T ArrayList<T>::getItem(int position)
{
    if (position < 0 or position >= size)
        return (T)NULL;
    return arr[position];
}

template <typename T>
int ArrayList<T>::getLength()
{
    return size;
}

template <typename T>
bool ArrayList<T>::empty()
{
    return size == 0;
}

template <typename T>
void ArrayList<T>::printList()
{
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << "\n";
}

#endif // ADDED_ARRAYLIST

/*

    ArrayList<int >  a;
    a.insertItem(10);
    a.insertItem(20);
    a.insertItem(30);
    for(int i=0;i<a.getLength();i++) cout<<a.getItem(i)<<' '; cout<<endl;

    a.removeItem(40);

    a.printList();

    a.removeItem(20);

    a.printList();

    copy( a.begin(), a.end(),  ostream_iterator<int>( cout, " " ) );



    cout<<a.searchItem(10)<<"\n";

    while(!a.empty())
        a.removeItemAt(0);
    a.printList();

    for(int i=0;i<100;i++) a.insertItem(i);
    a.printList();

*/
