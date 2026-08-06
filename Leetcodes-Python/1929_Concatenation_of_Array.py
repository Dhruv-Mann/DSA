class Solution(object):
    def getConcatenation(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        n = len(nums)     # find the length of the array
        ans = [0] * (2 * n)  # init a new array of size 2n with filling zero at all places
        for i, num in enumerate(nums):  # loop through the array
            ans[i] = ans[i + n] = num   # add the same value(num) at ans[i] and ans[i+1]
        return ans  # return the answer