class Solution(object):
    def trap(self, height):
        """
        :type height: List[int]
        :rtype: int
        Time: O(n) - single pass with two pointers
        Space: O(1) - only using constant extra space
        """
        # Edge case: no bars means no water can be trapped
        if not height:
            return 0
        
        res = 0
        # Two-pointer approach: start from both ends
        l, r = 0, len(height) - 1
        # Track maximum height seen from left and right
        leftMax, rightMax = height[l], height[r]

        while l < r:
            # Move from the side with smaller max height
            # Water level is determined by min(leftMax, rightMax)
            if leftMax < rightMax:
                l += 1
                # Update max height from left
                leftMax = max(leftMax, height[l])
                # Water trapped = max height - current height
                res += leftMax - height[l]
            else:
                r -= 1
                # Update max height from right
                rightMax = max(rightMax, height[r])
                # Water trapped = max height - current height
                res += rightMax - height[r]
        
        return res
        