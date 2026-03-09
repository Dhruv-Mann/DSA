class Solution(object):
    def twoSum(self, numbers, target):
        """
        :type numbers: List[int]
        :type target: int
        :rtype: List[int]
        Time: O(n) - two pointers traverse array once
        Space: O(1) - only using constant extra space
        """
        # Two-pointer approach because input array is sorted.
        l = 0
        r = len(numbers) - 1

        while l < r:
            currentSum = numbers[l] + numbers[r]

            # If sum is too large, move right pointer left to reduce sum.
            if currentSum > target:
                r -= 1
            # If sum is too small, move left pointer right to increase sum.
            elif currentSum < target:
                l += 1
            else:
                # Problem expects 1-based indices.
                return [l + 1, r + 1]