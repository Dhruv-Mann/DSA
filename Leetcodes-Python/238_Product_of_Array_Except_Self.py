class Solution(object):
    def productExceptSelf(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        # Initialize result array with all 1s
        res = [1] * len(nums)
        
        # First pass: fill result with product of all elements to the left
        # For each position i, res[i] = product of all nums[0] to nums[i-1]
        prefix = 1
        for i in range(len(nums)):
            res[i] = prefix
            # Update prefix for next iteration
            prefix *= nums[i]
        
        # Second pass: multiply result by product of all elements to the right
        # For each position i, res[i] *= product of all nums[i+1] to nums[n-1]
        postfix = 1
        for i in range(len(nums) - 1, -1, -1):
            # Multiply by postfix (product of all elements to the right)
            res[i] *= postfix
            # Update postfix for next iteration (going right to left)
            postfix *= nums[i]
        
        # Result now contains product of all elements except self at each index
        return res