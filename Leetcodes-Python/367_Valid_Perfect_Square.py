class Solution:
    def isPerfectSquare(self, num: int) -> bool:
        # Time: O(log num) - binary search on range [0, num]
        # Space: O(1) - only using pointers
        # Binary search to find if num is a perfect square
        # Check if mid * mid equals num
        low = 0
        high = num
        
        while low <= high:
            mid = (low + high) // 2
            # Found exact square root
            if mid * mid == num:
                return True
            # Square is too small, search right half
            elif mid * mid < num:
                low = mid + 1
            # Square is too large, search left half
            else:
                high = mid - 1

        # No perfect square found
        return False
        