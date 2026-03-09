from collections import Counter

class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        # Time: O(n) - counting characters in both strings
        # Space: O(1) - Counter stores at most 26 unique characters (English letters)
        # Count character frequencies in both strings
        # Anagram if both have identical character counts
        return Counter(s) == Counter(t)