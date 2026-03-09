class Solution(object):
    def isPalindrome(self, s):
        """
        :type s: str
        :rtype: bool
        Time: O(n) - traverse string from both ends
        Space: O(1) - only using pointers, no extra data structures
        """
        # Two-pointer check from both ends of the string.
        L = 0
        R = len(s) - 1
        while L < R:
            # Skip characters that are not letters/digits.
            while L < R and not s[L].isalnum():
                L += 1
            while L < R and not s[R].isalnum():
                R -= 1

            # Compare case-insensitively.
            if s[L].lower() != s[R].lower():
                return False

            L += 1
            R -= 1

        return True