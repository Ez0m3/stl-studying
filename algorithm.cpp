#include<iostream>
#include<vector>
#include<algorithm>
class Solution {
public:
    int maxArea(std::vector<int>& height) {
        int l=0;
        int r=height.size()-1;
        int h=std::min(height[l],height[r]);
        int area=h*(r-l);
        while(l!=r){
            height[l]<height[r]?++l:--r;
            h=std::min(height[l],height[r]);
            int newarea=h*(r-l);
            area=std::max(newarea,area);
        }
        return area;
    }
};
int main(){
    
}
