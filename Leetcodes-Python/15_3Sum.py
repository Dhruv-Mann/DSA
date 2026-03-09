class Solution(object):
    def threeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        Time: O(n^2) - sorting O(n log n), then nested loops O(n^2)
        Space: O(1) or O(n) - depending on sorting algorithm (excluding output)
        """
        res = []
        # Sort array to enable two-pointer approach and skip duplicates
        nums.sort()
        
        # Fix the first number and find two numbers that sum to -first
        for i, a in enumerate(nums):
            # Skip duplicate first numbers to avoid duplicate triplets
            if i > 0 and a == nums[i - 1]:
                continue
            
            # Two-pointer approach for the remaining two numbers
            l, r = i + 1, len(nums) - 1
            while l < r:
                currentSum = a + nums[l] + nums[r]
                
                # Adjust pointers based on sum comparison
                if currentSum > 0:
                    r -= 1
                elif currentSum < 0:
                    l += 1
                else:
                    # Found a valid triplet
                    res.append([a, nums[l], nums[r]])
                    l += 1
                    
                    # Skip duplicate second numbers
                    while nums[l] == nums[l - 1] and l < r:
                        l += 1
        
        return res

           
       

        