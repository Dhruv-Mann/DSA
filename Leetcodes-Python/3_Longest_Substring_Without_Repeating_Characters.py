class Solution(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        Time: O(n) - each character visited at most twice (once by r, once removed by l)
        Space: O(min(n, m)) - set stores unique characters (n = string length, m = charset size)
        """
        # Sliding window approach with set to track unique characters
        l = 0
        set1 = set()
        result = 0
        
        # Expand window with right pointer
        for r in range(len(s)):
            # Shrink window from left while duplicate exists
            while s[r] in set1:
                set1.remove(s[l])
                l += 1
            
            # Add current character to window
            set1.add(s[r])
            # Update max length found
            result = max(result, r - l + 1)
        
        return result