class Solution:
    def search(self, nums: List[int], target: int) -> int:
        # Standard binary search on sorted array
        # Return index if found, -1 otherwise
        n = len(nums)
        low = 0
        high = n-1
        
        while low <= high:
            mid =(low+high)//2
            # Target found at mid
            if nums[mid] == target:
                return mid
            # Target is in right half
            elif nums[mid] < target:
                low = mid + 1
            # Target is in left half
            else:
                high = mid - 1

        # Target not found in array
        return -1