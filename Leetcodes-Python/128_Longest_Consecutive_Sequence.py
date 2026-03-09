class Solution(object):
    def longestConsecutive(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        Time: O(n) - each number is visited at most twice (once in set conversion, once in while loop)
        Space: O(n) - storing all numbers in a set
        """
        # Convert list to set for O(1) lookup
        numSet = set(nums)
        longest = 0
        
        for n in numSet:
            # Only start counting from sequence beginnings
            # (numbers where n-1 does not exist)
            if (n - 1) not in numSet:
                length = 0
                # Count consecutive numbers from this starting point
                while (n + length) in numSet:
                    length += 1
                # Update longest sequence found so far
                longest = max(length, longest)
        
        return longest