int searchInsert(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;
    //用<=因為要考量單一元素:0 <= 0
    while(left <= right){
        int mid = left + (right -left) / 2;
        if(target == nums[mid]){
            return mid;
        }
        else if(target > nums[mid]){
            left = mid + 1;
        }else{
            right = mid - 1;
        }
    }return left;
    
}
