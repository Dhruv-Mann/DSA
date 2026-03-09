class Solution:
    def containsDuplicate(self, nums: List[int]) -> bool:
        # Time: O(n) - converting to set is O(n)
        # Space: O(n) - set stores up to n elements
        # Convert list to set to remove duplicates
        # If lengths differ, duplicates exist
        return len(nums) != len(set(nums))