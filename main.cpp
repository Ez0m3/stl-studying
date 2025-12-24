#include<iostream>
#include<algorithm>
template<typename T,std::size_t N>
void bubble_sort(T (&arr)[N])
{
    const int n=static_cast<int>(N);
    for(int i=0;i<n-1;++i)
    {
        bool swapped=false;
        for(int j=0;j<n-i-1;++j)
        {
            if(arr[j]>arr[j+1])
            {
                std::swap(arr[j],arr[j+1]);
                swapped=true;
            }
        }
        if(!swapped)return;
    }
}
template<typename T,std::size_t N>
void selection_sort(T (&arr)[N])
{
    const int n=static_cast<int>(N);
    for(int i=0;i<n-1;++i)
    {
        int minindex=i;
        for(int j=i+1;j<n;++j)
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
template<typename T,std::size_t N>
void insertion_sort(T (&arr)[N])
{
    const int n=static_cast<int>(N);
    for(int i=1;i<n;++i)
    {
        T temp=arr[i];
        int j=i-1;
        while(j>=0&&arr[j]>temp)
        {
            arr[j+1]=std::move(arr[j]);
            --j;
        }
        arr[j+1]=temp;
    }
}
int main()
{
    int arr[]{142,7,23,99,3,5,1,65,0,7,2,534,11};
    insertion_sort(arr);
    for(auto x:arr)
    {
        std::cout<<x<<" ";
    }
}