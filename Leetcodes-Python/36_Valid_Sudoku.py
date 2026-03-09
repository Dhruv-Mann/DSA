from collections import defaultdict

class Solution(object):
    def isValidSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: bool
        Time: O(1) - fixed 9x9 board, 81 cells total
        Space: O(1) - at most 27 sets with max 9 elements each
        """
        # Track which numbers have been seen in each row, column, and 3x3 square
        rows = defaultdict(set)
        columns = defaultdict(set)
        squares = defaultdict(set)
        
        # Iterate through all cells in the 9x9 board
        for r in range(9):
            for c in range(9):
                # Skip empty cells
                if board[r][c] == ".":
                    continue
                
                val = board[r][c]
                
                # Check if number already exists in row, column, or 3x3 square
                # (r//3, c//3) gives the 3x3 square index
                if (val in rows[r] or
                    val in columns[c] or
                    val in squares[(r // 3, c // 3)]):
                    return False
                
                # Add number to row, column, and square sets
                rows[r].add(val)
                columns[c].add(val)
                squares[(r // 3, c // 3)].add(val)
        
        # All cells are valid
        return True



        