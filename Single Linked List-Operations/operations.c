#include <stdio.h>
#include <stdlib.h>

/*
 * Node structure for a singly linked list.
 * Each node holds:
 *   - 'data'  : the integer value stored in this node
 *   - 'next'  : a pointer to the next node in the list (NULL if this is the last node)
 */
struct Node {
    int data;
    struct Node* next;
};

/*
 * Global head pointer — always points to the FIRST node of the list.
 * When the list is empty, head is NULL.
 * Every operation reads or updates this pointer to access/modify the list.
 */
struct Node* head = NULL;

// Function prototypes
void createList();
void traverseList();
void insertAtBeginning();
void insertAtEnd();
void insertAtPosition();
void deleteAtBeginning();
void deleteAtEnd();
void deleteAtPosition();
void deleteByValue();
void searchElement();
void countNodes();
void reverseList();
void sortList();
void displayMenu();

/*
 * Helper: Allocates a new node on the heap and initialises it.
 * - malloc reserves memory for one Node.
 * - We check for NULL because malloc can fail if the system is out of memory.
 * - 'next' is set to NULL so the node is safely "disconnected" until we link it.
 */
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("\nMemory allocation failed!\n");
        return NULL;
    }
    newNode->data = value;
    newNode->next = NULL;   // new node doesn't point anywhere yet
    return newNode;
}

/*
 * Creates the linked list from scratch by asking the user for n values.
 *
 * 'temp' is a "tail tracker" — it always points to the LAST node we added.
 * Without it we'd have to walk the entire list every time we append a node
 * (O(n) per insert → O(n²) total). With temp we just do temp->next = newNode
 * and advance temp, keeping each insert O(1).
 */
void createList() {
    int n, value;
    struct Node* temp;      // will track the current tail of the list
    
    printf("\nEnter the number of nodes: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Invalid number of nodes!\n");
        return;
    }
    
    for (int i = 0; i < n; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &value);
        
        struct Node* newNode = createNode(value);
        if (newNode == NULL) return;
        
        if (head == NULL) {
            // First node — it becomes both head and tail
            head = newNode;
            temp = head;
        } else {
            // Link the new node after the current tail, then move tail forward
            temp->next = newNode;
            temp = temp->next;
        }
    }
    printf("\nList created successfully!\n");
}

/*
 * Traverses the list from head to the last node, printing each value.
 *
 * We use a temporary pointer 'temp' so we don't lose the head reference.
 * The while-loop keeps moving temp forward (temp = temp->next) until
 * temp becomes NULL, meaning we've gone past the last node.
 */
void traverseList() {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }
    
    struct Node* temp = head;       // start from the first node
    printf("\nLinked List: ");
    while (temp != NULL) {          // stop when we've passed the last node
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" -> ");         // arrow only between nodes, not after the last one
        }
        temp = temp->next;          // move to the next node
    }
    printf(" -> NULL\n");           // show the end of the list
}

/*
 * Inserts a new node at the BEGINNING of the list.
 *
 * Steps:
 *   1. Create the new node.
 *   2. Point newNode->next to the current head (so the old list hangs off the new node).
 *   3. Update head to the new node (it is now the first element).
 *
 * This is O(1) — no traversal needed because we always have direct access to head.
 */
void insertAtBeginning() {
    int value;
    printf("\nEnter the value to insert: ");
    scanf("%d", &value);
    
    struct Node* newNode = createNode(value);
    if (newNode == NULL) return;
    
    newNode->next = head;   // new node now points to the old first node
    head = newNode;          // head moves to the new node
    printf("\nNode inserted at the beginning successfully!\n");
}

/*
 * Inserts a new node at the END of the list.
 *
 * We need to find the last node first. The while-loop walks forward
 * until temp->next is NULL — that means temp IS the last node.
 * Then we simply set temp->next = newNode to attach it at the tail.
 *
 * Special case: if the list is empty (head == NULL), the new node
 * becomes the head itself — there's no "last node" to find.
 *
 * Time: O(n) because we must traverse the entire list to reach the end.
 */
void insertAtEnd() {
    int value;
    printf("\nEnter the value to insert: ");
    scanf("%d", &value);
    
    struct Node* newNode = createNode(value);
    if (newNode == NULL) return;
    
    if (head == NULL) {
        head = newNode;             // empty list — new node is the head
    } else {
        struct Node* temp = head;
        while (temp->next != NULL) {    // walk until we reach the last node
            temp = temp->next;
        }
        temp->next = newNode;           // attach new node after the last node
    }
    printf("\nNode inserted at the end successfully!\n");
}

/*
 * Inserts a new node at a specific 1-based position.
 *
 * To insert at position p (p > 1) we need a pointer to the node at
 * position (p-1) — the node just BEFORE the target slot — because we
 * must update its 'next' pointer to include the new node.
 *
 * The for-loop runs (position - 2) times, advancing temp from position 1
 * to position (p-1).  We also check temp != NULL so we don't walk off
 * the end of a short list.
 *
 * Linking:
 *   newNode->next = temp->next   →  new node takes over the rest of the list
 *   temp->next    = newNode      →  previous node now points to new node
 *
 * If position == 1 it's the same as insertAtBeginning.
 */
void insertAtPosition() {
    int value, position;
    printf("\nEnter the position (1-based): ");
    scanf("%d", &position);
    
    if (position < 1) {
        printf("\nInvalid position!\n");
        return;
    }
    
    printf("Enter the value to insert: ");
    scanf("%d", &value);
    
    struct Node* newNode = createNode(value);
    if (newNode == NULL) return;
    
    if (position == 1) {
        // Same as insert-at-beginning
        newNode->next = head;
        head = newNode;
    } else {
        struct Node* temp = head;
        // Move temp to the node just BEFORE the desired position
        for (int i = 1; i < position - 1 && temp != NULL; i++) {
            temp = temp->next;
        }
        
        if (temp == NULL) {
            // We ran out of nodes before reaching the position
            printf("\nPosition out of range!\n");
            free(newNode);      // don't leak the unused node
            return;
        }
        
        // Splice the new node into the chain
        newNode->next = temp->next;   // new node points to what was next
        temp->next = newNode;          // previous node now points to new node
    }
    printf("\nNode inserted at position %d successfully!\n", position);
}

/*
 * Deletes the FIRST node of the list.
 *
 * We save the current head in 'temp' so we can free its memory AFTER
 * we've moved head forward. If we freed head directly first, we'd
 * lose the ->next pointer and orphan the rest of the list.
 *
 * O(1) — no traversal required.
 */
void deleteAtBeginning() {
    if (head == NULL) {
        printf("\nList is empty! Nothing to delete.\n");
        return;
    }
    
    struct Node* temp = head;       // save current head so we can free it later
    head = head->next;              // move head to the second node (or NULL)
    printf("\nDeleted node with value: %d\n", temp->data);
    free(temp);                     // release the old head's memory
}

/*
 * Deletes the LAST node of the list.
 *
 * To remove the last node we need the SECOND-TO-LAST node, because
 * we must set its 'next' to NULL (making it the new tail).
 *
 * The while-loop condition  temp->next->next != NULL  stops when
 * temp is the second-to-last node:
 *   temp -> lastNode -> NULL   ← temp->next->next is NULL, so stop.
 *
 * Special case: if there's only one node (head->next == NULL), we just
 * free it and set head to NULL.
 *
 * O(n) — must traverse to find the second-to-last node.
 */
void deleteAtEnd() {
    if (head == NULL) {
        printf("\nList is empty! Nothing to delete.\n");
        return;
    }
    
    // Special case: only one node in the list
    if (head->next == NULL) {
        printf("\nDeleted node with value: %d\n", head->data);
        free(head);
        head = NULL;    // list is now empty
        return;
    }
    
    struct Node* temp = head;
    // Walk until temp is the SECOND-TO-LAST node
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    
    printf("\nDeleted node with value: %d\n", temp->next->data);
    free(temp->next);       // free the last node
    temp->next = NULL;      // second-to-last node is now the new tail
}

/*
 * Deletes the node at a specific 1-based position.
 *
 * Just like insertAtPosition, we need a pointer to the node BEFORE the
 * target (position - 1) so we can "bypass" the target node:
 *
 *   before -> target -> after
 *     becomes
 *   before ----------> after     (target is freed)
 *
 * The for-loop advances temp to position (p-1).  We also check
 * temp->next != NULL because that is the actual node we want to delete;
 * if it's NULL, the position is beyond the list length.
 *
 * Position 1 is a special case handled separately (same as deleteAtBeginning).
 */
void deleteAtPosition() {
    if (head == NULL) {
        printf("\nList is empty! Nothing to delete.\n");
        return;
    }
    
    int position;
    printf("\nEnter the position to delete (1-based): ");
    scanf("%d", &position);
    
    if (position < 1) {
        printf("\nInvalid position!\n");
        return;
    }
    
    if (position == 1) {
        // Same as delete-at-beginning
        struct Node* temp = head;
        head = head->next;
        printf("\nDeleted node with value: %d\n", temp->data);
        free(temp);
        return;
    }
    
    struct Node* temp = head;
    // Move temp to the node just BEFORE the one we want to delete
    for (int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    
    if (temp == NULL || temp->next == NULL) {
        // Either we ran past the list, or the target node doesn't exist
        printf("\nPosition out of range!\n");
        return;
    }
    
    struct Node* nodeToDelete = temp->next;      // this is the target node
    temp->next = nodeToDelete->next;             // bypass the target in the chain
    printf("\nDeleted node with value: %d\n", nodeToDelete->data);
    free(nodeToDelete);                          // release target's memory
}

/*
 * Deletes the FIRST node that contains the given value.
 *
 * To unlink a node we need the node BEFORE it (so we can set
 * before->next = target->next). That's why the while-loop checks
 * temp->next->data instead of temp->data — we stay one step behind
 * the node we're looking for.
 *
 * Loop conditions explained:
 *   temp->next != NULL           → make sure there IS a next node to inspect
 *   temp->next->data != value    → stop when the next node holds our value
 *
 * If the value is in the HEAD node, we handle it separately because
 * there is no "previous node" — we just move head forward.
 */
void deleteByValue() {
    if (head == NULL) {
        printf("\nList is empty! Nothing to delete.\n");
        return;
    }
    
    int value;
    printf("\nEnter the value to delete: ");
    scanf("%d", &value);
    
    // Special case: the head node itself holds the value
    if (head->data == value) {
        struct Node* temp = head;
        head = head->next;      // move head forward
        printf("\nDeleted node with value: %d\n", temp->data);
        free(temp);
        return;
    }
    
    // Walk until temp->next is the node with the target value
    struct Node* temp = head;
    while (temp->next != NULL && temp->next->data != value) {
        temp = temp->next;
    }
    
    if (temp->next == NULL) {
        // Reached end without finding the value
        printf("\nValue %d not found in the list!\n", value);
        return;
    }
    
    struct Node* nodeToDelete = temp->next;      // node that contains the value
    temp->next = nodeToDelete->next;             // bypass it
    printf("\nDeleted node with value: %d\n", nodeToDelete->data);
    free(nodeToDelete);
}

/*
 * Searches for the first occurrence of a value and reports its 1-based position.
 *
 * We traverse node-by-node, incrementing a 'position' counter.
 * As soon as we find a match we print and return (early exit).
 * If the loop finishes (temp == NULL) without a match, the value isn't in the list.
 *
 * O(n) in the worst case (value at the end or not present).
 */
void searchElement() {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }
    
    int value, position = 1;    // position counter starts at 1 (first node)
    printf("\nEnter the value to search: ");
    scanf("%d", &value);
    
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == value) {
            printf("\nValue %d found at position %d\n", value, position);
            return;             // found — no need to keep searching
        }
        temp = temp->next;      // move to next node
        position++;             // keep the counter in sync
    }
    
    printf("\nValue %d not found in the list!\n", value);
}

/*
 * Counts the total number of nodes by traversing from head to the end.
 * Simple counter pattern: move forward and increment until temp is NULL.
 */
void countNodes() {
    int count = 0;
    struct Node* temp = head;
    
    while (temp != NULL) {  // visit every node exactly once
        count++;
        temp = temp->next;
    }
    
    printf("\nTotal number of nodes: %d\n", count);
}

/*
 * Reverses the list IN-PLACE using three pointers.
 *
 * Idea: walk through the list and flip each node's 'next' pointer
 * so it points to the previous node instead of the next one.
 *
 * Pointer roles:
 *   prev    — the node behind 'current' (starts as NULL because the
 *             new tail should point to NULL)
 *   current — the node we're currently processing
 *   next    — saved reference to current->next BEFORE we overwrite it
 *
 * Each iteration:
 *   1. next = current->next        → save the forward link
 *   2. current->next = prev        → flip the pointer backward
 *   3. prev = current              → advance prev one step
 *   4. current = next              → advance current one step
 *
 * When current becomes NULL, prev points to what was the last node
 * — that's our new head.
 *
 * O(n) time, O(1) extra space.
 */
void reverseList() {
    if (head == NULL || head->next == NULL) {
        printf("\nList is empty or has only one node!\n");
        return;
    }
    
    struct Node *prev = NULL, *current = head, *next = NULL;
    
    while (current != NULL) {
        next = current->next;       // 1. save next node
        current->next = prev;       // 2. reverse the link
        prev = current;             // 3. move prev forward
        current = next;             // 4. move current forward
    }
    
    head = prev;    // prev is now the first node of the reversed list
    printf("\nList reversed successfully!\n");
}

/*
 * Sorts the list in ascending order using BUBBLE SORT.
 *
 * Bubble sort compares adjacent elements and swaps them if they're
 * in the wrong order. One full pass "bubbles" the largest unsorted
 * value to its correct position at the end.
 *
 * Key variables:
 *   swapped — flag to detect if any swaps happened in a pass.
 *             If no swaps occur, the list is already sorted → stop early.
 *   lptr    — marks the boundary of the sorted portion at the tail.
 *             After each pass the last compared node is in its final
 *             position, so future passes don't need to go that far.
 *
 * Inner while-loop: walks ptr1 from head up to (but not including) lptr,
 * comparing ptr1->data with ptr1->next->data and swapping if needed.
 *
 * We only swap the DATA, not the nodes themselves — much simpler and
 * avoids relinking pointers.
 *
 * O(n²) worst/average case;  O(n) best case (already sorted, one pass).
 */
void sortList() {
    if (head == NULL || head->next == NULL) {
        printf("\nList is empty or has only one node!\n");
        return;
    }
    
    int swapped;
    struct Node *ptr1, *lptr = NULL;    // lptr = sorted boundary (starts at end)
    
    do {
        swapped = 0;        // assume no swaps will happen
        ptr1 = head;        // start each pass from the beginning
        
        // Walk adjacent pairs up to the sorted boundary
        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                // Adjacent elements are out of order — swap their data
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;    // a swap happened, so another pass may be needed
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;    // last node of this pass is now in its final position
    } while (swapped);      // repeat until a full pass has zero swaps
    
    printf("\nList sorted successfully!\n");
}

// Function to display menu
void displayMenu() {
    printf("\n========================================");
    printf("\n    LINKED LIST OPERATIONS MENU");
    printf("\n========================================");
    printf("\n1.  Create List");
    printf("\n2.  Traverse/Display List");
    printf("\n3.  Insert at Beginning");
    printf("\n4.  Insert at End");
    printf("\n5.  Insert at Position");
    printf("\n6.  Delete from Beginning");
    printf("\n7.  Delete from End");
    printf("\n8.  Delete from Position");
    printf("\n9.  Delete by Value");
    printf("\n10. Search Element");
    printf("\n11. Count Nodes");
    printf("\n12. Reverse List");
    printf("\n13. Sort List");
    printf("\n14. Exit");
    printf("\n========================================");
    printf("\nEnter your choice: ");
}

// ========================  MAIN  ========================
int main() {
    int choice;
    
    printf("\n*** LINKED LIST OPERATIONS PROGRAM ***\n");
    
    // Infinite loop keeps the menu running until the user picks "Exit"
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createList();
                break;
            case 2:
                traverseList();
                break;
            case 3:
                insertAtBeginning();
                break;
            case 4:
                insertAtEnd();
                break;
            case 5:
                insertAtPosition();
                break;
            case 6:
                deleteAtBeginning();
                break;
            case 7:
                deleteAtEnd();
                break;
            case 8:
                deleteAtPosition();
                break;
            case 9:
                deleteByValue();
                break;
            case 10:
                searchElement();
                break;
            case 11:
                countNodes();
                break;
            case 12:
                reverseList();
                break;
            case 13:
                sortList();
                break;
            case 14:
                printf("\nExiting program. Goodbye!\n");
                /*
                 * Free every remaining node to avoid memory leaks.
                 * We save head in temp, advance head, then free temp.
                 * The loop stops once head is NULL (all nodes freed).
                 */
                while (head != NULL) {
                    struct Node* temp = head;
                    head = head->next;
                    free(temp);
                }
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
