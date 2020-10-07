#ifndef QUEUE_ADDED
#define QUEUE_ADDED
template < class T >
class Queue
{
    T * arr;
    int arr_size,start,end;
public :
    Queue()
    {
        arr_size=10;
        arr = new T[10];
        start=end=0;
    }
    T & front() /// ###  returns referance  + check empty() :: be carefull
    {
        return  arr[start];
    }
    T & rear() /// ###  returns referance  + check empty() :: be carefull
    {
        return  arr[(end-1+arr_size)%arr_size];
    }
    void enqueue(const T &x)
    {
        if(size()+1 >= arr_size)
        {
//            cout<<" memory overload\n";
            T  * newarr = new T[arr_size+10];
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
            delete arr;
            arr= newarr;
            arr_size+=10;
        }
        arr[end]=x;
        end= (end+1)%arr_size;
    }
    void dequeue()
    {
        start=(start+1)%arr_size;
    }
    bool empty()
    {
        return start==end;
    }
    int size()
    {
        return start <= end ? end - start : arr_size  - start + end;
    }
};
#endif
