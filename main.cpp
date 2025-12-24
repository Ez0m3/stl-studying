#include<iostream>
#include<algorithm>
template<typename T,std::size_t N>
void bubble_sort(T (&arr)[N])
{
    for(std::size_t i=0;i<N-1;++i)
    {
        bool isswap=false;
        for(std::size_t j=0;j<N-i-1;++j)
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
    for(std::size_t i=0;i<N-1;++i)
    {
        std::size_t minindex=i;
        for(std::size_t j=i+1;j<N;++j)
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