class Solution(object):
    def maxArea(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        # Two-pointer approach: start from widest container
        res = 0
        l, r = 0, len(height) - 1
        
        while l < r:
            # Area = width * minimum height
            # (The shorter wall limits how much water can be held)
            area = (r - l) * min(height[l], height[r])
            res = max(res, area)
            
            # Move the pointer pointing to shorter height inward
            # This is greedy: moving the taller one can only decrease area
            if height[l] < height[r]:
                l += 1
            else:
                r -= 1
        
        return res
        