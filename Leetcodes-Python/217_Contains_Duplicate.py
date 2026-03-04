class Solution:
    def containsDuplicate(self, nums: List[int]) -> bool:
        # Convert list to set to remove duplicates
        # If lengths differ, duplicates exist
        return len(nums) != len(set(nums))