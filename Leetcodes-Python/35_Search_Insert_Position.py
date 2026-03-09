class Solution:
    def searchInsert(self, nums: List[int], target: int) -> int:
        # Time: O(log n) - binary search
        # Space: O(1) - only using pointers
        # Binary search to find target or its insertion position
        # When target not found, 'low' points to the insertion position
        n = len(nums)
        low = 0
        high = n-1
        
        # Continue searching while search space is valid
        while low <= high:
            mid = (low+high)//2
            
            # Found target at mid position
            if nums[mid] == target:
                return mid
            # Target is in right half
            elif nums[mid] < target:
                low = mid + 1
            # Target is in left half
            else:
                high = mid - 1
            
        # If not found, 'low' is the insertion position
        return low
