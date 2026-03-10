class Solution(object):
    def maxProfit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        Time: O(n) - single pass through prices array
        Space: O(1) - only using constant extra space
        """
        # Two pointers: l = buy day, r = sell day
        l = 0
        r = 1
        Max_Profit = 0
        
        while r < len(prices):
            # If profitable (buy low, sell high)
            if prices[l] < prices[r]:
                profit = prices[r] - prices[l]
                Max_Profit = max(Max_Profit, profit)
            else:
                # Found a lower price, update buy day
                l = r
            
            # Move to next day
            r += 1
        
        return Max_Profit