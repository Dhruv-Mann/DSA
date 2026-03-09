class Solution:
    def removeElement(self, nums: List[int], val: int) -> int:
        # Time: O(n) - single pass through array
        # Space: O(1) - only using pointers, modifying in-place
        # Use two pointers: k tracks position to place non-val elements
        # Iterate through array and shift non-val elements forward
        k = 0
        for i in range(len(nums)):
            # If current element is not the target value
            if nums[i] != val:
                # Place it at position k
                nums[k] = nums[i]
                # Increment k for next placement
                k += 1

        # Return count of elements kept (k is the final insertion position)
        return k