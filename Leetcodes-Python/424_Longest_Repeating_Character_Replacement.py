class Solution(object):
    def characterReplacement(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        Time: O(n) - sliding window with each pointer moving at most n times
        Space: O(1) - at most 26 uppercase character counts
        """
        # Sliding window + frequency map.
        # Keep the window valid such that:
        # window_size - max_frequency_in_window <= k
        count = {}
        l = 0
        maxFreq = 0
        result = 0

        for r in range(len(s)):
            # Expand window by including s[r].
            count[s[r]] = 1 + count.get(s[r], 0)
            maxFreq = max(maxFreq, count[s[r]])

            # Shrink window until replacements needed are within k.
            while (r - l + 1) - maxFreq > k:
                count[s[l]] -= 1
                l += 1

            # Track longest valid window length.
            result = max(result, r - l + 1)

        return result
        