class Solution(object):
    def checkInclusion(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        Time: O(n) - sliding window over s2 with O(1) alphabet work
        Space: O(1) - two fixed-size frequency arrays (26 letters)
        """
        # If pattern is longer than text, permutation cannot exist.
        if len(s1) > len(s2):
            return False

        # Frequency arrays for lowercase English letters.
        s1Count, s2Count = [0] * 26, [0] * 26

        # Build initial window counts of size len(s1).
        for i in range(len(s1)):
            s1Count[ord(s1[i]) - ord('a')] += 1
            s2Count[ord(s2[i]) - ord('a')] += 1

        # matches = how many character buckets currently match exactly.
        matches = 0
        for i in range(26):
            matches += (1 if s1Count[i] == s2Count[i] else 0)

        l = 0
        for r in range(len(s1), len(s2)):
            # All 26 buckets matched => current window is a permutation.
            if matches == 26:
                return True

            # Add new right character into the window and update matches.
            index = ord(s2[r]) - ord('a')
            s2Count[index] += 1
            if s1Count[index] == s2Count[index]:
                matches += 1
            elif s1Count[index] + 1 == s2Count[index]:
                matches -= 1

            # Remove left character from the window and update matches.
            index = ord(s2[l]) - ord('a')
            s2Count[index] -= 1
            if s1Count[index] == s2Count[index]:
                matches += 1
            elif s1Count[index] - 1 == s2Count[index]:
                matches -= 1

            l += 1

        # Check final window after loop completes.
        return matches == 26