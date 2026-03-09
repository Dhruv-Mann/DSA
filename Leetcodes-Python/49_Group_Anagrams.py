from collections import defaultdict

class Solution(object):
    def groupAnagrams(self, strs):
        """
        :type strs: List[str]
        :rtype: List[List[str]]
        Time: O(n * k log k) - n strings, sorting each of length k
        Space: O(n * k) - storing all strings in hash map
        """
        # Use defaultdict to group strings with the same sorted characters
        # Anagrams will have identical sorted forms, so we use that as the key
        res = defaultdict(list)
        
        for s in strs:
            # Sort the string and use it as key (anagrams have same sorted form)
            key = tuple(sorted(s))
            # Append the original string to its anagram group
            res[key].append(s)
        
        # Return all groups as a list
        return list(res.values())

