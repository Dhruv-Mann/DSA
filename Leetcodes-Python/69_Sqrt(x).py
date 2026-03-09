class Solution:
    def mySqrt(self, x: int) -> int:
        # Time: O(log x) - binary search on range [0, x]
        # Space: O(1) - only using pointers
        # Binary search to find floor of square root
        # Return 'high' since it's the largest value where mid*mid <= x
        low = 0
        high = x
        
        while low <= high:
            mid = (low+high)//2
            # Exact square root found
            if mid * mid == x:
                return mid
            # Mid is too small, search right half
            elif mid * mid < x:
                low = mid + 1
            # Mid is too large, search left half
            else:
                high = mid - 1

        # Return high: it's the largest value where mid*mid <= x (floor of sqrt)
        return high