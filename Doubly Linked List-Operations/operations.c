#include <stdio.h>
#include <stdlib.h>

/*
 * ============================================================================
 *  DOUBLY LINKED LIST — COMPLETE OPERATIONS
 * ============================================================================
 *
 *  A doubly linked list (DLL) is a linear data structure where each node has:
 *    - 'data'  : the value stored
 *    - 'next'  : pointer to the NEXT node
 *    - 'prev'  : pointer to the PREVIOUS node
 *
 *  Unlike a singly linked list which only allows forward traversal, a DLL
 *  lets you move in BOTH directions (forward and backward).
 *
 *  Key advantage over singly linked list:
 *    - Deletion of a node when you have a pointer to it is O(1) because
 *      you can reach the previous node via node->prev (no traversal needed).
 *    - Backward traversal is possible.
 *
 *  Key disadvantage:
 *    - Extra memory for the 'prev' pointer in every node.
 *    - More pointer operations to maintain during insert/delete.
 *
 * ============================================================================
 */

/*
 * Node structure for a doubly linked list.
 * Each node holds:
 *   - 'data' : the integer value stored in this node
 *   - 'next' : pointer to the next node (NULL if this is the last node)
 *   - 'prev' : pointer to the previous node (NULL if this is the first node)
 */
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

/*
 * Global head pointer — always points to the FIRST node of the list.
 * When the list is empty, head is NULL.
 * Every operation reads or updates this pointer to access/modify the list.
 */
struct Node* head = NULL;

// Function prototypes
void createList();
void traverseForward();
void traverseBackward();
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
 * - Both 'next' and 'prev' are set to NULL so the node is safely
 *   "disconnected" until we link it into the list.
 */
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("\nMemory allocation failed!\n");
        return NULL;
    }
    newNode->data = value;
    newNode->next = NULL;   // new node doesn't point forward yet
    newNode->prev = NULL;   // new node doesn't point backward yet
    return newNode;
}
    
/*
 * Creates the doubly linked list from scratch by asking the user for n values.
 *
 *  'tail' tracks the LAST node we added. Without it, we'd have to walk the
 *  entire list every time we append a node (O(n) per insert → O(n²) total).
 *  With tail we simply:
 *    1. Set tail->next = newNode   (old tail points forward to new node)
 *    2. Set newNode->prev = tail   (new node points backward to old tail)
 *    3. Advance tail to newNode
 *  This keeps each append at O(1).
 *
 *  The TWO-WAY linking is the core difference from a singly linked list:
 *  every time we connect two nodes, we must update BOTH next and prev.
 */
void createList() {
    int n, value;
    struct Node* tail;      // will track the current last node

    printf("\nEnter the number of nodes: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of nodes!\n");
        return;
    }

    // Free any existing list first to avoid memory leaks
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }

    for (int i = 0; i < n; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &value);

        struct Node* newNode = createNode(value);
        if (newNode == NULL) return;

        if (head == NULL) {
            // First node — it becomes both head and tail
            // prev stays NULL because there's nothing before the first node
            head = newNode;
            tail = head;
        } else {
            // Link the new node after the current tail
            tail->next = newNode;   // old tail points forward to new node
            newNode->prev = tail;   // new node points backward to old tail
            tail = newNode;         // move tail pointer to the new last node
        }
    }
    printf("\nDoubly linked list created successfully!\n");
}

/*
 * Traverses the list from HEAD to the last node, printing each value.
 * (This is FORWARD traversal — same direction as a singly linked list.)
 *
 * We use a temporary pointer 'temp' so we don't lose the head reference.
 * The while-loop moves temp forward (temp = temp->next) until temp is NULL.
 */
void traverseForward() {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }

    struct Node* temp = head;       // start from the first node
    printf("\nForward:  NULL <-> ");
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" <-> ");        // double arrow shows bidirectional links
        }
        temp = temp->next;          // move to the next node
    }
    printf(" <-> NULL\n");
}

/*
 * Traverses the list from the LAST node back to HEAD, printing each value.
 * (This is BACKWARD traversal — only possible in a doubly linked list.)
 *
 * Step 1: Walk forward to find the LAST node (temp->next == NULL).
 * Step 2: Walk backward using temp->prev until temp is NULL.
 *
 * This is the main advantage of a DLL over a SLL — you can go backwards
 * without needing to reverse the list or use a stack.
 */
void traverseBackward() {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }

    // Step 1: Find the last node
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Step 2: Walk backward from last node to head
    printf("\nBackward: NULL <-> ");
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->prev != NULL) {
            printf(" <-> ");
        }
        temp = temp->prev;          // move to the previous node
    }
    printf(" <-> NULL\n");
}

/*
 * Inserts a new node at the BEGINNING of the list.
 *
 * Steps:
 *   1. Create the new node.
 *   2. Set newNode->next = head  (new node points forward to old first node).
 *   3. If the list isn't empty, set head->prev = newNode (old first node
 *      points backward to new node).
 *   4. Update head = newNode (new node is now the first element).
 *
 * Compared to SLL insert-at-beginning:
 *   - SLL only needs step 2 and 4.
 *   - DLL additionally needs step 3 (setting the old head's prev pointer).
 *
 * O(1) — no traversal needed.
 */
void insertAtBeginning() {
    int value;
    printf("\nEnter the value to insert: ");
    scanf("%d", &value);

    struct Node* newNode = createNode(value);
    if (newNode == NULL) return;

    newNode->next = head;           // new node points forward to old head
    // newNode->prev is already NULL (correct — nothing before the first node)

    if (head != NULL) {
        head->prev = newNode;       // old head points backward to new node
    }

    head = newNode;                 // head moves to the new node
    printf("\nNode inserted at the beginning successfully!\n");
}

/*
 * Inserts a new node at the END of the list.
 *
 * We walk to the last node (temp->next == NULL) then:
 *   1. Set temp->next = newNode   (old last points forward to new node)
 *   2. Set newNode->prev = temp   (new node points backward to old last)
 *
 * Special case: if the list is empty (head == NULL), the new node becomes head.
 *
 * Time: O(n) — we must traverse to the end.
 * (This can be made O(1) if we maintain a global tail pointer.)
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
        while (temp->next != NULL) {    // walk until the last node
            temp = temp->next;
        }
        temp->next = newNode;           // old last points forward to new node
        newNode->prev = temp;           // new node points backward to old last
    }
    printf("\nNode inserted at the end successfully!\n");
}

/*
 * Inserts a new node at a specific 1-based position.
 *
 * To insert at position p, we need the node at position (p-1). Then:
 *   1. newNode->next = temp->next       (new node takes over the rest of the list)
 *   2. newNode->prev = temp             (new node points back to (p-1)th node)
 *   3. If temp->next exists, set temp->next->prev = newNode
 *      (the node that was at position p now points back to the new node)
 *   4. temp->next = newNode             (previous node points forward to new node)
 *
 * Four pointer updates instead of two (SLL only needs steps 1 and 4).
 * This is the main cost of a DLL — more bookkeeping per operation.
 *
 * Position 1 is handled separately (same as insertAtBeginning).
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
        if (head != NULL) {
            head->prev = newNode;
        }
        head = newNode;
    } else {
        struct Node* temp = head;
        // Move temp to the node just BEFORE the desired position
        for (int i = 1; i < position - 1 && temp != NULL; i++) {
            temp = temp->next;
        }

        if (temp == NULL) {
            printf("\nPosition out of range!\n");
            free(newNode);          // don't leak the unused node
            return;
        }

        // Splice the new node into the chain (4 pointer updates)
        newNode->next = temp->next;     // 1. new node points forward
        newNode->prev = temp;           // 2. new node points backward
        if (temp->next != NULL) {
            temp->next->prev = newNode; // 3. next node points back to new node
        }
        temp->next = newNode;           // 4. previous node points forward to new node
    }
    printf("\nNode inserted at position %d successfully!\n", position);
}

/*
 * Deletes the FIRST node of the list.
 *
 * Steps:
 *   1. Save head in temp (so we can free it later).
 *   2. Move head to head->next.
 *   3. If the new head isn't NULL, set head->prev = NULL
 *      (the new first node should have no previous node).
 *   4. Free temp.
 *
 * Compared to SLL:
 *   - SLL skips step 3. DLL must clear the new head's prev pointer.
 *
 * O(1) — no traversal required.
 */
void deleteAtBeginning() {
    if (head == NULL) {
        printf("\nList is empty! Nothing to delete.\n");
        return;
    }

    struct Node* temp = head;           // save current head
    head = head->next;                  // move head forward

    if (head != NULL) {
        head->prev = NULL;              // new head has no previous node
    }

    printf("\nDeleted node with value: %d\n", temp->data);
    free(temp);                         // release old head's memory
}

/*
 * Deletes the LAST node of the list.
 *
 * Walk to the last node, then use its 'prev' pointer to reach the
 * second-to-last node. This is SIMPLER than in a SLL:
 *   - SLL needs temp->next->next != NULL to stop one before the end.
 *   - DLL can go all the way to the end and use temp->prev.
 *
 * Steps:
 *   1. Walk to the last node (temp->next == NULL).
 *   2. If temp->prev exists: set temp->prev->next = NULL
 *      (the second-to-last node becomes the new tail).
 *   3. If temp->prev is NULL, this was the only node — set head = NULL.
 *   4. Free temp.
 *
 * O(n) — must traverse to find the last node.
 * (Could be O(1) with a global tail pointer.)
 */
void deleteAtEnd() {
    if (head == NULL) {
        printf("\nList is empty! Nothing to delete.\n");
        return;
    }

    struct Node* temp = head;

    // Walk to the very last node
    while (temp->next != NULL) {
        temp = temp->next;
    }

    if (temp->prev != NULL) {
        // There are other nodes — unlink the last one
        temp->prev->next = NULL;        // second-to-last becomes the new tail
    } else {
        // This was the only node in the list
        head = NULL;
    }

    printf("\nDeleted node with value: %d\n", temp->data);
    free(temp);
}

/*
 * Deletes the node at a specific 1-based position.
 *
 * We walk to the TARGET node directly (not the one before it, unlike SLL)
 * because in a DLL we can access both neighbours via temp->prev and temp->next.
 *
 * Once we're at the target node:
 *   1. If temp->prev exists: temp->prev->next = temp->next
 *      (skip over temp in the forward direction)
 *   2. If temp->next exists: temp->next->prev = temp->prev
 *      (skip over temp in the backward direction)
 *   3. If temp is head, update head.
 *   4. Free temp.
 *
 * This is a KEY advantage of DLL: given a pointer to any node, deletion is O(1)
 * because you don't need to find the previous node — you already have it.
 * (The O(n) here is only because we don't have a direct pointer; we traverse.)
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

    struct Node* temp = head;
    // Walk to the target position directly
    for (int i = 1; i < position && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\nPosition out of range!\n");
        return;
    }

    // Unlink temp from both directions
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;  // previous node skips over temp
    } else {
        head = temp->next;              // temp was the head — move head forward
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;  // next node skips over temp
    }

    printf("\nDeleted node with value: %d\n", temp->data);
    free(temp);
}

/*
 * Deletes the FIRST node that contains the given value.
 *
 * We walk forward until we find the node with the target value.
 * Then we unlink it using the same prev/next technique as deleteAtPosition.
 *
 * In a SLL we had to track the previous node separately. In a DLL we
 * just use temp->prev — much cleaner and less error-prone.
 */
void deleteByValue() {
    if (head == NULL) {
        printf("\nList is empty! Nothing to delete.\n");
        return;
    }

    int value;
    printf("\nEnter the value to delete: ");
    scanf("%d", &value);

    struct Node* temp = head;

    // Walk to the node with the target value
    while (temp != NULL && temp->data != value) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\nValue %d not found in the list!\n", value);
        return;
    }

    // Unlink temp from both directions
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        head = temp->next;              // deleting the head node
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    printf("\nDeleted node with value: %d\n", temp->data);
    free(temp);
}

/*
 * Searches for the first occurrence of a value and reports its 1-based position.
 * (Identical logic to SLL — we only traverse forward.)
 */
void searchElement() {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }

    int value, position = 1;
    printf("\nEnter the value to search: ");
    scanf("%d", &value);

    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == value) {
            printf("\nValue %d found at position %d\n", value, position);
            return;
        }
        temp = temp->next;
        position++;
    }

    printf("\nValue %d not found in the list!\n", value);
}

/*
 * Counts the total number of nodes by traversing from head to the end.
 */
void countNodes() {
    int count = 0;
    struct Node* temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    printf("\nTotal number of nodes: %d\n", count);
}

/*
 * Reverses the list IN-PLACE by swapping prev and next pointers on every node.
 *
 * In a SLL, reversal requires three pointers (prev, current, next).
 * In a DLL, reversal is conceptually simpler — each node already has both
 * prev and next, so we just SWAP them:
 *
 *   Each iteration:
 *     1. temp = current->prev        → save the prev pointer
 *     2. current->prev = current->next  → what was "next" becomes "prev"
 *     3. current->next = temp           → what was "prev" becomes "next"
 *     4. current = current->prev        → move forward (which is now in prev!)
 *
 * After the loop, the old head's prev pointer (which now holds what used to
 * be the previous node before the swap at the last step) holds the new head.
 * We need to be careful: at the end of the loop, 'current' is NULL but 'temp'
 * holds the prev of the last processed node — that's our new head.
 *
 * O(n) time, O(1) extra space.
 */
void reverseList() {
    if (head == NULL || head->next == NULL) {
        printf("\nList is empty or has only one node!\n");
        return;
    }

    struct Node* current = head;
    struct Node* temp = NULL;

    // Swap prev and next for every node
    while (current != NULL) {
        temp = current->prev;           // save prev
        current->prev = current->next;  // next becomes prev
        current->next = temp;           // prev becomes next

        // Move to the next node in the ORIGINAL order
        // After swapping, current->prev holds the ORIGINAL next
        current = current->prev;
    }

    // After the loop, temp points to the prev of the last processed node.
    // The new head is temp->prev (one step back in the swapped list).
    // But since the last node processed set temp = old_prev (which is now next),
    // and current became NULL, the new head is actually at temp->prev.
    if (temp != NULL) {
        head = temp->prev;
    }

    printf("\nList reversed successfully!\n");
}

/*
 * Sorts the list in ascending order using BUBBLE SORT.
 *
 * Same data-swap approach as in SLL — we only swap the DATA values,
 * not the nodes/pointers. This avoids the complexity of relinking
 * both prev and next pointers.
 *
 * The sorting algorithm is identical to SLL's bubble sort:
 *   - Outer loop repeats passes until no swaps occur.
 *   - Inner loop compares adjacent pairs and swaps if out of order.
 *   - 'lptr' (last pointer) shrinks the unsorted boundary after each pass.
 *
 * O(n²) worst/average;  O(n) best case (already sorted).
 */
void sortList() {
    if (head == NULL || head->next == NULL) {
        printf("\nList is empty or has only one node!\n");
        return;
    }

    int swapped;
    struct Node *ptr1, *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                // Swap data between adjacent nodes
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    printf("\nList sorted successfully!\n");
}

// Display menu
void displayMenu() {
    printf("\n========================================");
    printf("\n  DOUBLY LINKED LIST OPERATIONS MENU");
    printf("\n========================================");
    printf("\n1.  Create List");
    printf("\n2.  Traverse Forward");
    printf("\n3.  Traverse Backward");
    printf("\n4.  Insert at Beginning");
    printf("\n5.  Insert at End");
    printf("\n6.  Insert at Position");
    printf("\n7.  Delete from Beginning");
    printf("\n8.  Delete from End");
    printf("\n9.  Delete from Position");
    printf("\n10. Delete by Value");
    printf("\n11. Search Element");
    printf("\n12. Count Nodes");
    printf("\n13. Reverse List");
    printf("\n14. Sort List");
    printf("\n15. Exit");
    printf("\n========================================");
    printf("\nEnter your choice: ");
}

// ========================  MAIN  ========================
int main() {
    int choice;

    printf("\n*** DOUBLY LINKED LIST OPERATIONS PROGRAM ***\n");

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:  createList();        break;
            case 2:  traverseForward();   break;
            case 3:  traverseBackward();  break;
            case 4:  insertAtBeginning(); break;
            case 5:  insertAtEnd();       break;
            case 6:  insertAtPosition();  break;
            case 7:  deleteAtBeginning(); break;
            case 8:  deleteAtEnd();       break;
            case 9:  deleteAtPosition();  break;
            case 10: deleteByValue();     break;
            case 11: searchElement();     break;
            case 12: countNodes();        break;
            case 13: reverseList();       break;
            case 14: sortList();          break;
            case 15:
                printf("\nExiting program. Goodbye!\n");
                // Free every remaining node
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
