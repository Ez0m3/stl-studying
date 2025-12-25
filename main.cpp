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
        arr[j+1]=std::move(temp);
    }
}
template<typename T,std::size_t N>
void shell_sort(T (&arr)[N])
{
    const int n=static_cast<int>(N);
    for(int gap=n/2;gap>0;gap/=2)
    {
        for(int i=0;i<gap;++i)         //相同gap组距的不同组循环
        {
            for(int j=i+gap;j<n;j+=gap)   //同一个组的组内循环,起始arr[i]，每一次循环后有序区整体增加一个arr[j+gap]
            {
                T temp=std::move(arr[j]);
                int k=j-gap;
                while(k>=i&&arr[k]>temp)   //arr[j]前面都是有序的
                {
                    arr[k+gap]=std::move(arr[k]);
                    k-=gap;
                }
                arr[k+gap]=std::move(temp);
            }
        }
    }
}
template<typename T,std::size_t N>
void counting_sort(T (&arr)[N])
{
    const int n=static_cast<int>(N);
    int min{arr[0]};
    int max{arr[0]};
    for(int i=1;i<n;++i)
    {
        if(arr[i]>max)max=arr[i];
        if(arr[i]<min)min=arr[i];
    }
    int count[max-min+1]{};
    for(int i=0;i<n;++i)
    {
        ++count[arr[i]-min];
    }
    int index=0;
    for(int i=0;i<=max-min;++i)
    {
        while(count[i]>0)
        {
            arr[index++]=min+i;
            --count[i];
        }
    }
}
int main()
{
    int arr[]{142,7,23,99,3,5,1,65,0,7,2,534,11};
    counting_sort(arr);
    for(auto x:arr)
    {
        std::cout<<x<<" ";
    }
}