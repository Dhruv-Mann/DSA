from collections import Counter

class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        # Count character frequencies in both strings
        # Anagram if both have identical character counts
        return Counter(s) == Counter(t)