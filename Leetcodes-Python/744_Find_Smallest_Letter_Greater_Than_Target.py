class Solution:
    def nextGreatestLetter(self, letters: List[str], target: str) -> str:
        # Handle wrap-around: if target >= largest letter, return first letter
        if target >= letters[-1]:
            return letters[0]
            
        # Binary search to find smallest letter greater than target
        # When not found, 'low' will point to the next greater position
        low = 0
        high = len(letters) - 1
        
        while low <= high:
            mid = (low + high) // 2
            
            # Current letter is <= target, search right
            if letters[mid] <= target:
                low = mid + 1
            # Current letter is > target, could be answer but search left for smaller
            else:
                high = mid - 1
                
        # 'low' now points to the smallest letter greater than target
        return letters[low]