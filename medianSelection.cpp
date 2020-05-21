//use epsilons to compare doubles

#include<bits/stdc++.h>
using namespace std;

double median(vector<double> &nums);

double pick_pivot(vector<double> &nums){
    int len = nums.size();
    if(len <= 5){
        sort(nums.begin(), nums.end());
        int x = (nums[len/2]+nums[(len-1)/2])/2;
        return x;
    }
    int size = (len+4)/5;
    vector<vector<double>> divisions(size, vector<double>());
    for(int i=0; i<len; i++){
        int index = i/5;
        divisions[index].push_back(nums[i]);
    }
    vector<double> medians(size);
    for(int i=0; i<size; i++){
        medians[i] = pick_pivot(divisions[i]);
    }
    double median_of_medians = median(medians);
    return median_of_medians;
}

double select(vector<double> &nums, int k){
    int len = nums.size();
    if(len == 1){
        return nums[0];
    }
    double pivot = pick_pivot(nums);
    vector<double> lows, pivots, highs;
    for(int i=0; i<len; i++){
        if(nums[i] < pivot){
            lows.push_back(nums[i]);
        }
        else if(nums[i] == pivot){
            pivots.push_back(nums[i]);
        }
        else{
            highs.push_back(nums[i]);
        }
    }
    if(k < lows.size()){
        return select(lows, k);
    }
    else if(k < lows.size() + pivots.size()){
        return pivots[0];
    }
    else{
        return select(highs, k-lows.size()-pivots.size());
    }
}

double median(vector<double> &nums){
    int len = nums.size();
    if(len%2 == 1){
        return select(nums, len/2);
    }
    return 0.5*(select(nums, len/2)+select(nums, len/2 - 1));
}

int main(){
    int n;
    cin>>n;
    vector<double> nums(n);
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }
    double med = median(nums);
    cout<<med<<endl;
    return 0;
}