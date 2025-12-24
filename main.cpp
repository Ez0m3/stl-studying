#include<iostream>
#include<algorithm>
template<typename T,std::size_t N>
void bubble_sort(T (&arr)[N])
{
    int size=static_cast<int>(N);
    for(int i=0;i<size-1;++i)
    {
        bool isswap=false;
        for(int j=0;j<size-i-1;++j)
        {
            if(arr[j]>arr[j+1])
            {
                std::swap(arr[j],arr[j+1]);
                isswap=true;
            }
        }
        if(!isswap)return;
    }
}
template<typename T,std::size_t N>
void selection_sort(T (&arr)[N])
{
    int size=static_cast<int>(N);
    for(int i=0;i<size-1;++i)
    {
        int minindex=i;
        for(int j=i+1;j<size;++j)
        {
            if(arr[j]<arr[minindex])
            minindex=j;
        }
        if(minindex!=i)
        {
            std::swap(arr[minindex],arr[i]);
        }
    }
}
int main()
{
    int arr[]{3,5,1,65,87,2,534};
    selection_sort(arr);
    for(auto x:arr)
    {
        std::cout<<x<<" ";
    }
}