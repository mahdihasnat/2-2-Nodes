#ifndef ADDED_QUEUE
#define ADDED_QUEUE 1

#include<string.h>
#define BLOCK_SIZE 3
template < class T >
class Queue
{

    T *arr;
    int arr_size,start,end;
public :
    Queue()
    {
        arr_size=BLOCK_SIZE;
        arr = new T[arr_size];
        start=end=0;
    }
    void enqueue(T x)
    {
        if(size()+1 >= arr_size)
        {
//            cout<<" memory overload\n";

            T  * newarr = new T[arr_size*2];
            if(start==0)
            {
                memcpy(newarr,arr,sizeof (T) * (arr_size));
            }
            else
            {
                for(int i=start; i<arr_size; i++)
                    newarr[i-start]=arr[i];
                for(int i=0; i<=end; i++)
                    newarr[arr_size-start + i] = arr[i];
                start=0;
                end= arr_size-1;
            }
            delete [] arr;
            arr= newarr;
            arr_size*=2;
        }
        arr[end]=x;
        end= (end+1)%arr_size;
    }
    T dequeue()
    {
        if(!empty())
        {
            start=(start+1)%arr_size;
            return arr [ (start -1 +arr_size )%arr_size];
        }
        else return (T)NULL;
    }
    bool empty()
    {
        return start==end;
    }
    int size()
    {
        return start <= end ? end - start : arr_size  - start + end;
    }
    ~Queue()
    {
        delete [] arr;
        arr = 0;
    }
};


#endif // ADDED_QUEUE