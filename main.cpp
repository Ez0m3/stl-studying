#include<iostream>
#include<algorithm>
template<typename t,std::size_t N>
void bobblesort(t (&arr)[N])
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
int main()
{
    int arr[]{3,5,1,65,87,2,534};
    bobblesort(arr);
    for(auto x:arr)
    {
        std::cout<<x<<" ";
    }
}