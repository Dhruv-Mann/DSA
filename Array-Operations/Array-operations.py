# ============================================================
#  Array Operations in Python — C-to-Python Bridge Reference
# ============================================================
# Each operation maps directly to your C version so you can
# compare and learn the Python way of doing the same thing.
# ============================================================

import math

# In C you had:   int n;  int *arr = NULL;
# In Python, a list IS your dynamic array. No malloc needed.
arr = []

# -------------------------------------------------------
# 1. Creation / Initialization
# -------------------------------------------------------
# C:  malloc, scanf in a loop
# Python: just input() and list comprehension
def create():
    global arr
    n = int(input("Enter the size of the array: "))
    if n <= 0:
        print("Invalid Size!")
        return
    print("Enter the elements separated by spaces: ", end="")
    arr = list(map(int, input().split()))[:n]  # take only n elements
    # map(int, ...) converts each string token to int — like scanf("%d") in a loop

# -------------------------------------------------------
# 2. Traversal / Display
# -------------------------------------------------------
# C:  for loop with printf
# Python: print the list directly, or join elements
def traverse():
    if not arr:                    # replaces: if (n == 0)
        print("Array is Empty!")
        return
    print(" ".join(map(str, arr)))  # converts each int to str, joins with space

# -------------------------------------------------------
# 3. Insertion
# -------------------------------------------------------
# C:  realloc, shift elements manually
# Python: list.insert() does everything for you
def insert_element():
    if not arr:
        print("Create an array first!")
        return
    pos = int(input("Enter the position to insert at: "))
    if pos < 0 or pos > len(arr):  # len(arr) replaces your global n
        print("Invalid Position!")
        return
    elem = int(input("Enter the element to insert: "))
    arr.insert(pos, elem)          # ONE line replaces: realloc + shift loop + assign
    print("Element inserted successfully!")

# -------------------------------------------------------
# 4. Deletion
# -------------------------------------------------------
# C:  shift elements left, realloc
# Python: list.pop(index) or del arr[index]
def delete_element():
    if not arr:
        print("Array is empty!")
        return
    pos = int(input("Enter the position to delete: "))
    if pos < 0 or pos >= len(arr):
        print("Invalid position!")
        return
    removed = arr.pop(pos)         # removes and returns the element
    print(f"Element {removed} deleted successfully!")
    # f-strings (f"...{var}...") replace printf("%d", var)

# -------------------------------------------------------
# 5. Linear Search
# -------------------------------------------------------
# C:  for loop checking each element
# Python: 'in' keyword + .index() method
def search():
    if not arr:
        print("Array is empty!")
        return
    key = int(input("Enter the element to find: "))

    # Pythonic way:
    if key in arr:                         # 'in' checks membership — replaces your entire loop
        print(f"Element found at index: {arr.index(key)}")
    else:
        print("Element not found in the Array!")

    # If you want the manual C-style loop (for learning):
    # for i in range(len(arr)):            # range(len(arr)) = for(int i=0; i<n; i++)
    #     if arr[i] == key:
    #         print(f"Element found at index: {i}")
    #         return
    # print("Element not found!")

# -------------------------------------------------------
# 6. Update / Modify
# -------------------------------------------------------
# C:  arr[index] = element
# Python: exactly the same — arr[index] = element
def update():
    if not arr:
        print("Array is empty!")
        return
    index = int(input("Enter the position to update: "))
    if index < 0 or index >= len(arr):
        print("Invalid position!")
        return
    element = int(input("Enter the new element: "))
    arr[index] = element            # identical to C
    print("Element updated successfully!")

# -------------------------------------------------------
# 7. Sorting
# -------------------------------------------------------
# C:  manual bubble sort with nested loops
# Python: arr.sort() (Timsort, O(n log n)) — but here's both ways
def bubble_sort():
    if not arr:
        print("Array is empty!")
        return
    # Manual bubble sort (same logic as your C code):
    n = len(arr)
    for i in range(n):
        swapped = False              # bool instead of int 0/1
        for j in range(n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]  # Python swap — no temp variable!
                swapped = True
        if not swapped:
            break
    print("Array sorted successfully!")

def python_sort():
    """The Pythonic way — use this in interviews/LeetCode"""
    if not arr:
        print("Array is empty!")
        return
    arr.sort()                       # in-place sort, O(n log n)
    # sorted_arr = sorted(arr)       # returns NEW sorted list, original unchanged
    print("Array sorted successfully!")

# -------------------------------------------------------
# 8. Merging
# -------------------------------------------------------
# C:  realloc + copy loop
# Python: just use + operator or .extend()
def merge():
    global arr
    if not arr:
        print("First array is empty! Create it first!")
        return
    print("Enter elements of second array separated by spaces: ", end="")
    arr2 = list(map(int, input().split()))
    arr = arr + arr2                 # + concatenates lists (like your realloc + copy)
    # OR: arr.extend(arr2)           # modifies arr in-place
    print("Arrays merged successfully!")

# -------------------------------------------------------
# 9. Copying
# -------------------------------------------------------
# C:  malloc new array + copy loop
# Python: slicing or .copy()
def copy_array():
    if not arr:
        print("Empty Array cannot be copied!")
        return
    arr2 = arr.copy()                # or arr2 = arr[:] (slice copy)
    # IMPORTANT: arr2 = arr would NOT copy — it creates a reference (like a pointer)
    print(f"Array copied successfully! Copy: {arr2}")

# -------------------------------------------------------
# 10. Reversing
# -------------------------------------------------------
# C:  two-pointer swap loop
# Python: slicing or .reverse()
def reverse():
    if not arr:
        print("Empty Array cannot be reversed!")
        return
    arr.reverse()                    # in-place reverse
    # OR: reversed_arr = arr[::-1]   # creates new reversed list (slicing trick)
    print("Array reversed successfully!")

# -------------------------------------------------------
# 11. Count Elements
# -------------------------------------------------------
# C:  just print n
# Python: len()
def count_elements():
    print(f"Total number of elements: {len(arr)}")

# -------------------------------------------------------
# 12 & 13. Min and Max
# -------------------------------------------------------
# C:  manual loop tracking min/max
# Python: built-in min() and max()
def minimum():
    if not arr:
        print("Array is empty!")
        return
    print(f"Minimum element: {min(arr)}")   # one line replaces your entire loop

def maximum():
    if not arr:
        print("Array is empty!")
        return
    print(f"Maximum element: {max(arr)}")

# -------------------------------------------------------
# 14 & 15. Sum and Average
# -------------------------------------------------------
# C:  manual loop accumulating sum
# Python: built-in sum()
def sum_elements():
    if not arr:
        print("Array is empty!")
        return
    print(f"Sum of all elements: {sum(arr)}")

def average():
    if not arr:
        print("Array is empty!")
        return
    print(f"Average: {sum(arr) / len(arr):.2f}")   # :.2f = %.2f in C

# -------------------------------------------------------
# 16. Binary Search
# -------------------------------------------------------
# C:  manual while loop with left, right, mid
# Python: same logic, or use bisect module
def binary_search():
    if not arr:
        print("Array is empty!")
        return
    key = int(input("Enter the element to search: "))

    # Manual way (same as your C code):
    left, right = 0, len(arr) - 1   # multiple assignment — replaces two lines
    while left <= right:
        mid = left + (right - left) // 2   # // is integer division (like / in C for ints)
        if arr[mid] == key:
            print(f"Element found at index: {mid}")
            return
        elif arr[mid] < key:
            left = mid + 1
        else:
            right = mid - 1
    print("Element not found!")

    # Pythonic way:
    # import bisect
    # i = bisect.bisect_left(arr, key)
    # if i < len(arr) and arr[i] == key:
    #     print(f"Found at index {i}")

# -------------------------------------------------------
# 17. Find All Occurrences
# -------------------------------------------------------
# C:  loop and check each element
# Python: list comprehension
def find_all_occurrences():
    if not arr:
        print("Array is empty!")
        return
    key = int(input("Enter element to find all occurrences: "))
    # List comprehension — this is the #1 Python pattern you need to master:
    indices = [i for i in range(len(arr)) if arr[i] == key]
    # Reads as: "give me every i where arr[i] equals key"
    if indices:
        print(f"Element {key} found at indices: {indices}")
    else:
        print("Not found")

# -------------------------------------------------------
# 18 & 19. Rotate Left / Right
# -------------------------------------------------------
# C:  three-reverse technique with manual loops
# Python: slicing makes this trivial
def rotate_left():
    global arr
    if not arr:
        print("Array is empty!")
        return
    k = int(input("Enter positions to rotate left: "))
    k = k % len(arr)
    arr = arr[k:] + arr[:k]          # slice from k to end + start to k
    print(f"Array rotated left by {k} positions!")

def rotate_right():
    global arr
    if not arr:
        print("Array is empty!")
        return
    k = int(input("Enter positions to rotate right: "))
    k = k % len(arr)
    arr = arr[-k:] + arr[:-k]        # last k elements + everything before them
    print(f"Array rotated right by {k} positions!")

# -------------------------------------------------------
# 20. Remove Duplicates
# -------------------------------------------------------
# C:  nested loop with visited array, realloc
# Python: convert to set (or use dict.fromkeys to preserve order)
def remove_duplicates():
    global arr
    if not arr:
        print("Array is empty!")
        return
    arr = list(dict.fromkeys(arr))   # removes dupes, PRESERVES order
    # set(arr) removes dupes but does NOT preserve order
    print(f"Duplicates removed! New size: {len(arr)}")

# -------------------------------------------------------
# 21 & 22. Second Largest / Smallest
# -------------------------------------------------------
# C:  manual tracking with INT_MIN/INT_MAX
# Python: sort + index, or same manual logic
def second_largest():
    if len(arr) < 2:
        print("Need at least 2 elements!")
        return
    unique = list(set(arr))          # remove duplicates
    if len(unique) < 2:
        print("No second largest (all elements same)!")
        return
    unique.sort()
    print(f"Second largest: {unique[-2]}")   # -1 is last, -2 is second last

def second_smallest():
    if len(arr) < 2:
        print("Need at least 2 elements!")
        return
    unique = list(set(arr))
    if len(unique) < 2:
        print("No second smallest (all elements same)!")
        return
    unique.sort()
    print(f"Second smallest: {unique[1]}")

# -------------------------------------------------------
# 23. Check if Sorted
# -------------------------------------------------------
# C:  loop comparing adjacent elements
# Python: compare with sorted version, or use all()
def check_sorted():
    if not arr:
        print("Array is empty!")
        return
    if arr == sorted(arr):
        print("Array is sorted in ascending order.")
    elif arr == sorted(arr, reverse=True):
        print("Array is sorted in descending order.")
    else:
        print("Array is not sorted.")
    # LeetCode style with all():
    # all(arr[i] <= arr[i+1] for i in range(len(arr)-1))

# -------------------------------------------------------
# 24. Frequency Count
# -------------------------------------------------------
# C:  nested loop with visited array
# Python: collections.Counter or dict
def frequency_count():
    if not arr:
        print("Array is empty!")
        return
    from collections import Counter
    freq = Counter(arr)              # Counter({element: count, ...})
    print("Element Frequency:")
    for elem, count in freq.items():
        print(f"{elem} -> {count} times")

# -------------------------------------------------------
# 25. Find Missing Number
# -------------------------------------------------------
# C:  expected_sum - actual_sum
# Python: same math, cleaner syntax
def find_missing_number():
    if not arr:
        print("Array is empty!")
        return
    n = len(arr)
    expected = (n + 1) * (n + 2) // 2
    actual = sum(arr)
    print(f"Missing number: {expected - actual}")

# -------------------------------------------------------
# 26. Find Duplicates
# -------------------------------------------------------
# C:  nested loop with visited array
# Python: Counter or set logic
def find_duplicates():
    if not arr:
        print("Array is empty!")
        return
    from collections import Counter
    dupes = [item for item, count in Counter(arr).items() if count > 1]
    print(f"Duplicate elements: {dupes if dupes else 'None'}")

# -------------------------------------------------------
# 27. Product
# -------------------------------------------------------
# C:  loop multiplying
# Python: math.prod() or functools.reduce
def product():
    if not arr:
        print("Array is empty!")
        return
    print(f"Product of all elements: {math.prod(arr)}")

# -------------------------------------------------------
# 28. Median
# -------------------------------------------------------
# C:  copy, sort, pick middle
# Python: statistics module or manual
def find_median():
    if not arr:
        print("Array is empty!")
        return
    import statistics
    print(f"Median: {statistics.median(arr)}")
    # Manual way:
    # s = sorted(arr)
    # n = len(s)
    # median = s[n//2] if n % 2 else (s[n//2 - 1] + s[n//2]) / 2

# -------------------------------------------------------
# 29. Standard Deviation
# -------------------------------------------------------
# C:  manual mean, variance, sqrt
# Python: statistics module
def standard_deviation():
    if not arr:
        print("Array is empty!")
        return
    import statistics
    print(f"Standard Deviation: {statistics.pstdev(arr):.2f}")
    # pstdev = population std dev (divides by n, like your C code)
    # stdev  = sample std dev (divides by n-1)

# -------------------------------------------------------
# MAIN MENU
# -------------------------------------------------------
# C:  while(1) + switch-case
# Python: while True + if-elif (Python has match-case from 3.10+)
def main():
    while True:
        print("\n============== ARRAY OPERATIONS MENU ==============")
        print("1.  Create Array          16. Binary Search")
        print("2.  Display Array         17. Find All Occurrences")
        print("3.  Insert Element        18. Rotate Left")
        print("4.  Delete Element        19. Rotate Right")
        print("5.  Search (Linear)       20. Remove Duplicates")
        print("6.  Update Element        21. Second Largest")
        print("7.  Bubble Sort           22. Second Smallest")
        print("8.  Python Sort           23. Check if Sorted")
        print("9.  Merge Arrays          24. Frequency Count")
        print("10. Copy Array            25. Find Missing Number")
        print("11. Reverse Array         26. Find Duplicates")
        print("12. Count Elements        27. Product")
        print("13. Find Minimum          28. Median")
        print("14. Find Maximum          29. Std Deviation")
        print("15. Sum / Average          0. Exit")
        print("===================================================")

        choice = int(input("Enter your choice: "))

        # Python dict dispatch — cleaner than if-elif chain:
        actions = {
            1: create,        2: traverse,       3: insert_element,
            4: delete_element, 5: search,         6: update,
            7: bubble_sort,    8: python_sort,    9: merge,
            10: copy_array,   11: reverse,       12: count_elements,
            13: minimum,      14: maximum,       15: lambda: (sum_elements(), average()),
            16: binary_search, 17: find_all_occurrences,
            18: rotate_left,  19: rotate_right,  20: remove_duplicates,
            21: second_largest, 22: second_smallest, 23: check_sorted,
            24: frequency_count, 25: find_missing_number, 26: find_duplicates,
            27: product,      28: find_median,   29: standard_deviation,
        }

        if choice == 0:
            print("\nExiting... Thank you!")
            break                        # break exits the while loop — same as your exit(0)
        elif choice in actions:
            actions[choice]()            # calls the function from the dict
        else:
            print("Invalid choice!")
        print()

# This is Python's equivalent of int main() — it runs only when you execute this file directly
if __name__ == "__main__":
    main()
