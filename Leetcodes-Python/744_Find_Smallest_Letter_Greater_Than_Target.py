class Solution:
    def nextGreatestLetter(self, letters: List[str], target: str) -> str:
        # 1. The Wrap Around Rule
        # If target is bigger than the biggest letter, answer is the first letter.
        if target >= letters[-1]:
            return letters[0]
            
        # 2. Standard Binary Search (Same as Insert Position)
        low = 0
        high = len(letters) - 1
        
        while low <= high:
            mid = (low + high) // 2
            
            if letters[mid] <= target:
                low = mid + 1
            else:
                high = mid - 1
                
        # 3. Return the letter at the 'low' index
        return letters[low]