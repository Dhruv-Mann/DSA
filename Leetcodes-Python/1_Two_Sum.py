class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        # Hash map to store number -> index mapping
        prevMap = {}
        
        for i, n in enumerate(nums):
            # Calculate the complement needed to reach target
            diff = target - n
            
            # If complement exists in map, we found the pair
            if diff in prevMap:
                return [prevMap[diff], i]
            # Otherwise, store current number and its index
            else:
                prevMap[n] = i
