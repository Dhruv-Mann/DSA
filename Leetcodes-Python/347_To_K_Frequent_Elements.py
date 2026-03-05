from collections import Counter

class Solution(object):
    def topKFrequent(self, nums, k):
        # 1. Count the votes
        # Output: {1: 3, 2: 2, 3: 1}
        count_map = Counter(nums)
        
        # 2. Create the shelves (Buckets)
        # Index = Frequency (Vote Count)
        # Value = List of candidates with that vote count
        # We use len(nums) + 1 because a number can appear up to N times.
        freq = [[] for i in range(len(nums) + 1)]
        
        # 3. Fill the shelves
        for num, count in count_map.items():
            freq[count].append(num)
        
        # freq is now: [[], [3], [2], [1], [], [], ...]
        # Index 0: []
        # Index 1: [3] (Appeared 1 time)
        # Index 2: [2] (Appeared 2 times)
        # Index 3: [1] (Appeared 3 times)
            
        # 4. Walk down the shelves from Top to Bottom
        res = []
        # range parameters: (start_index, stop_before_index, step)
        # We start at the highest possible count and go down to 1.
        for i in range(len(freq) - 1, 0, -1):
            # i is the current shelf number (Frequency)
            for n in freq[i]:
                # n is the number on that shelf
                res.append(n)
                
                # Check if we have enough winners
                if len(res) == k:
                    return res