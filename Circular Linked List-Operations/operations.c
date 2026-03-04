#include <stdio.h>
#include <stdlib.h>

/*
 * ============================================================================
 *  CIRCULAR LINKED LIST — COMPLETE OPERATIONS
 * ============================================================================
 *
 *  A Circular Linked List (CLL) is a variation of a singly linked list where
 *  the LAST node's 'next' pointer points back to the FIRST node (head)
 *  instead of NULL.
 *
 *  Regular SLL:   head -> [10] -> [20] -> [30] -> NULL
 *  Circular SLL:  head -> [10] -> [20] -> [30] --+
 *                          ^                      |
 *                          +----------------------+
 *
 *  Key differences from a regular singly linked list:
 *    - There is NO NULL at the end. The list forms a loop.
 *    - Traversal must detect when we've come back to head (not check for NULL).
 *    - You can reach any node from any other node by keep going forward.
 *
 *  Key advantage:
 *    - Any node can be a starting point — useful for round-robin scheduling.
 *    - Reaching the last node from head still takes O(n), but once you're
 *      at the last node, getting back to head is O(1) (just follow next).
 *
 *  Key disadvantage:
 *    - If you're not careful, traversal loops forever (infinite loop bug).
 *    - Slightly more complex insert/delete logic due to maintaining the cycle.
 *
 * ============================================================================
 */

/*
 * Node structure — identical to a singly linked list node.
 * The "circular" part is in how we SET the last node's next pointer,
 * not in the structure itself.
 */
struct Node {
    int data;
    struct Node* next;
};

/*
 * Global head pointer — points to the FIRST node of the circular list.
 * When the list is empty, head is NULL.
 *
 * IMPORTANT: In a CLL, head->next eventually leads back to head.
 * The last node satisfies: lastNode->next == head.
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
void sortList();
void displayMenu();

/*
 * Helper: Allocates a new node on the heap and initialises it.
 */
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("\nMemory allocation failed!\n");
        return NULL;
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

/*
 * Helper: Returns the LAST node of the circular list.
 *
 * The last node is the one whose 'next' points back to 'head'.
 * We walk forward from head until we find it.
 *
 * MANY operations need the last node (insert at beginning, insert at end,
 * delete at beginning, etc.) because of the circular link that connects
 * the tail back to the head.
 *
 * Returns NULL if the list is empty.
 */
struct Node* getLastNode() {
    if (head == NULL) return NULL;

    struct Node* temp = head;
    while (temp->next != head) {    // stop when we've looped back
        temp = temp->next;
    }
    return temp;    // this node's next is head — it's the last node
}

/*
 * Creates the circular linked list from scratch.
 *
 * Building the list is similar to SLL, but with one crucial difference:
 * after adding all nodes, the LAST node's next must point to HEAD
 * (not NULL) to complete the circle.
 *
 * During construction:
 *   - First node: head = newNode, and newNode->next = head (points to itself)
 *     This makes even a single-node list circular.
 *   - Subsequent nodes: tail->next = newNode, then newNode->next = head
 *     (maintain the circular link at all times).
 */
void createList() {
    int n, value;
    struct Node* tail;

    printf("\nEnter the number of nodes: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of nodes!\n");
        return;
    }

    // Free any existing list
    if (head != NULL) {
        struct Node* last = getLastNode();
        last->next = NULL;      // break the circle first to avoid infinite loop
        while (head != NULL) {
            struct Node* temp = head;
            head = head->next;
            free(temp);
        }
    }

    for (int i = 0; i < n; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &value);

        struct Node* newNode = createNode(value);
        if (newNode == NULL) return;

        if (head == NULL) {
            // First node — points to itself (single-node circle)
            head = newNode;
            newNode->next = head;   // circular: points back to itself
            tail = head;
        } else {
            tail->next = newNode;   // old tail points to new node
            newNode->next = head;   // new node completes the circle back to head
            tail = newNode;         // move tail to the new last node
        }
    }
    printf("\nCircular linked list created successfully!\n");
}

/*
 * Traverses the circular list, printing each value.
 *
 * CRITICAL DIFFERENCE from SLL traversal:
 *   - SLL: while (temp != NULL)         → stops at NULL
 *   - CLL: do { ... } while (temp != head)  → stops when we return to head
 *
 * We use a do-while loop because:
 *   - We start at head.
 *   - After processing head, we move forward.
 *   - We stop when we arrive back at head.
 *   A while-loop with condition (temp != head) would NEVER execute the body
 *   because temp starts AS head! The do-while ensures we process at least once.
 */
void traverseList() {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }

    struct Node* temp = head;
    printf("\nCircular List: ");
    do {
        printf("%d", temp->data);
        temp = temp->next;
        if (temp != head) {
            printf(" -> ");
        }
    } while (temp != head);     // stop when we've come full circle
    printf(" -> (back to head: %d)\n", head->data);
}

/*
 * Inserts a new node at the BEGINNING of the circular list.
 *
 * Steps:
 *   1. Create the new node.
 *   2. Find the LAST node (whose next points to current head).
 *   3. Set newNode->next = head  (new node points to old head).
 *   4. Set lastNode->next = newNode  (last node now points to new node
 *      instead of old head — maintaining the circle).
 *   5. Update head = newNode.
 *
 * Why we need the last node:
 *   In a regular SLL, inserting at the beginning only changes head.
 *   In a CLL, the last node's next must ALSO be updated to maintain the circle.
 *
 * Special case: empty list — the new node points to itself.
 *
 * Time: O(n) to find the last node. Can be O(1) if you maintain a tail pointer.
 */
void insertAtBeginning() {
    int value;
    printf("\nEnter the value to insert: ");
    scanf("%d", &value);

    struct Node* newNode = createNode(value);
    if (newNode == NULL) return;

    if (head == NULL) {
        // Empty list — new node points to itself
        head = newNode;
        newNode->next = head;
    } else {
        struct Node* last = getLastNode();  // need this to maintain circle
        newNode->next = head;               // new node points to old head
        last->next = newNode;               // last node now points to new node
        head = newNode;                     // update head
    }
    printf("\nNode inserted at the beginning successfully!\n");
}

/*
 * Inserts a new node at the END of the circular list.
 *
 * Steps:
 *   1. Create the new node.
 *   2. Find the last node.
 *   3. Set lastNode->next = newNode  (old last points to new node).
 *   4. Set newNode->next = head      (new node completes the circle).
 *
 * The new node becomes the new "last node" because its next points to head.
 *
 * Time: O(n) to find the last node.
 */
void insertAtEnd() {
    int value;
    printf("\nEnter the value to insert: ");
    scanf("%d", &value);

    struct Node* newNode = createNode(value);
    if (newNode == NULL) return;

    if (head == NULL) {
        head = newNode;
        newNode->next = head;
    } else {
        struct Node* last = getLastNode();
        last->next = newNode;           // old last points to new node
        newNode->next = head;           // new node points to head (circle)
    }
    printf("\nNode inserted at the end successfully!\n");
}

/*
 * Inserts a new node at a specific 1-based position.
 *
 * Position 1 = insert at beginning (special case — need to update last->next).
 * Position > 1 = walk to node at (position-1), splice in the new node.
 *
 * The splice logic is the same as SLL:
 *   newNode->next = temp->next
 *   temp->next = newNode
 *
 * No need to update the last node's circular link unless we're inserting
 * at position 1 (beginning) — the circle is maintained automatically
 * because we're inserting in the middle of existing links.
 *
 * If inserting after the last node, newNode->next will be 'head' (from
 * temp->next where temp is the last node), which correctly makes the
 * new node the new last node.
 */
void insertAtPosition() {
    int value, position;
    printf("\nEnter the position (1-based): ");
    scanf("%d", &position);

    if (position < 1) {
        printf("\nInvalid position!\n");
        return;
    }

    if (position == 1) {
        // Redirect to insert-at-beginning (handles circular link)
        printf("Enter the value to insert: ");
        scanf("%d", &value);

        struct Node* newNode = createNode(value);
        if (newNode == NULL) return;

        if (head == NULL) {
            head = newNode;
            newNode->next = head;
        } else {
            struct Node* last = getLastNode();
            newNode->next = head;
            last->next = newNode;
            head = newNode;
        }
    } else {
        printf("Enter the value to insert: ");
        scanf("%d", &value);

        struct Node* newNode = createNode(value);
        if (newNode == NULL) return;

        if (head == NULL) {
            printf("\nPosition out of range!\n");
            free(newNode);
            return;
        }

        struct Node* temp = head;
        // Walk to node at position (p-1)
        for (int i = 1; i < position - 1; i++) {
            temp = temp->next;
            if (temp == head) {
                // We've looped around — position is out of range
                printf("\nPosition out of range!\n");
                free(newNode);
                return;
            }
        }

        // Splice the new node in
        newNode->next = temp->next;     // new node takes over the chain
        temp->next = newNode;           // previous node points to new node
    }
    printf("\nNode inserted at position %d successfully!\n", position);
}

/*
 * Deletes the FIRST node of the circular list.
 *
 * Steps:
 *   1. If only one node: free it, set head = NULL.
 *   2. Otherwise:
 *      a. Find the last node.
 *      b. Save head in temp.
 *      c. Move head to head->next.
 *      d. Set last->next = new head (maintain circle).
 *      e. Free temp.
 *
 * Why we need the last node:
 *   The last node's next currently points to the old head. After deletion,
 *   it must point to the NEW head. Without this update, the circle breaks.
 *
 * Time: O(n) to find the last node.
 */
void deleteAtBeginning() {
    if (head == NULL) {
        printf("\nList is empty! Nothing to delete.\n");
        return;
    }

    struct Node* temp = head;

    if (head->next == head) {
        // Only one node — list becomes empty
        printf("\nDeleted node with value: %d\n", head->data);
        free(head);
        head = NULL;
        return;
    }

    struct Node* last = getLastNode();
    head = head->next;              // move head forward
    last->next = head;              // last node points to new head (circle)

    printf("\nDeleted node with value: %d\n", temp->data);
    free(temp);
}

/*
 * Deletes the LAST node of the circular list.
 *
 * We need the SECOND-TO-LAST node (the node before the last) because:
 *   - It must become the new last node.
 *   - Its next must be updated to point to head (maintain circle).
 *
 * Finding the second-to-last node:
 *   Walk forward until temp->next->next == head.
 *   At that point, temp is second-to-last, temp->next is last.
 *
 * Special case: only one node — head->next == head.
 */
void deleteAtEnd() {
    if (head == NULL) {
        printf("\nList is empty! Nothing to delete.\n");
        return;
    }

    if (head->next == head) {
        // Only one node
        printf("\nDeleted node with value: %d\n", head->data);
        free(head);
        head = NULL;
        return;
    }

    struct Node* temp = head;
    // Walk to the second-to-last node
    while (temp->next->next != head) {
        temp = temp->next;
    }

    // temp is now second-to-last; temp->next is the last node
    printf("\nDeleted node with value: %d\n", temp->next->data);
    free(temp->next);
    temp->next = head;              // second-to-last is now the new last
}

/*
 * Deletes the node at a specific 1-based position.
 *
 * Position 1 = delete at beginning (special case — update last->next).
 * Position > 1 = walk to node at (position-1), bypass the target.
 *
 * The bypass is the same as SLL:
 *   nodeToDelete = temp->next
 *   temp->next = nodeToDelete->next
 *   free(nodeToDelete)
 *
 * If we delete the last node, temp->next becomes head (correct — circle maintained).
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
        // Delete at beginning
        deleteAtBeginning();
        return;
    }

    struct Node* temp = head;
    // Walk to the node just BEFORE the target
    for (int i = 1; i < position - 1; i++) {
        temp = temp->next;
        if (temp->next == head) {
            // We've reached the end — position is out of range
            printf("\nPosition out of range!\n");
            return;
        }
    }

    if (temp->next == head && position != 1) {
        // This would try to delete head from a non-position-1 call
        // Actually this means position is exactly at the end + 1
        printf("\nPosition out of range!\n");
        return;
    }

    struct Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;    // bypass the target
    printf("\nDeleted node with value: %d\n", nodeToDelete->data);
    free(nodeToDelete);
}

/*
 * Deletes the FIRST node that contains the given value.
 *
 * Two cases:
 *   1. Value is in the head node — same as deleteAtBeginning.
 *   2. Value is elsewhere — walk forward until temp->next->data == value.
 *      Then bypass temp->next.
 *
 * We must be careful about the stopping condition:
 *   - Don't check temp->next == head in the loop condition — that would
 *     prevent finding the last node's value.
 *   - Instead, detect when we've looped all the way around.
 */
void deleteByValue() {
    if (head == NULL) {
        printf("\nList is empty! Nothing to delete.\n");
        return;
    }

    int value;
    printf("\nEnter the value to delete: ");
    scanf("%d", &value);

    // Case 1: head node has the value
    if (head->data == value) {
        if (head->next == head) {
            // Only one node
            printf("\nDeleted node with value: %d\n", head->data);
            free(head);
            head = NULL;
        } else {
            struct Node* last = getLastNode();
            struct Node* temp = head;
            head = head->next;
            last->next = head;
            printf("\nDeleted node with value: %d\n", temp->data);
            free(temp);
        }
        return;
    }

    // Case 2: value is in a non-head node
    struct Node* temp = head;
    while (temp->next != head && temp->next->data != value) {
        temp = temp->next;
    }

    if (temp->next == head) {
        // We've looped all the way around without finding the value
        printf("\nValue %d not found in the list!\n", value);
        return;
    }

    struct Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    printf("\nDeleted node with value: %d\n", nodeToDelete->data);
    free(nodeToDelete);
}

/*
 * Searches for a value and reports its 1-based position.
 *
 * Uses the same do-while pattern as traversal to handle the circular structure.
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
    do {
        if (temp->data == value) {
            printf("\nValue %d found at position %d\n", value, position);
            return;
        }
        temp = temp->next;
        position++;
    } while (temp != head);

    printf("\nValue %d not found in the list!\n", value);
}

/*
 * Counts the total number of nodes.
 * Uses do-while to handle circular structure.
 */
void countNodes() {
    if (head == NULL) {
        printf("\nList is empty! Node count: 0\n");
        return;
    }

    int count = 0;
    struct Node* temp = head;
    do {
        count++;
        temp = temp->next;
    } while (temp != head);

    printf("\nTotal number of nodes: %d\n", count);
}

/*
 * Sorts the circular list using BUBBLE SORT (data swap approach).
 *
 * Same logic as SLL bubble sort, but the inner loop's boundary check
 * uses the circular structure: we stop when we reach 'lptr' (last pointer)
 * which starts as 'head' (end of the unsorted region).
 *
 * IMPORTANT: In a circular list, we can't use temp->next != NULL as a stop
 * condition (there's no NULL!). Instead we use temp->next != lptr.
 */
void sortList() {
    if (head == NULL || head->next == head) {
        printf("\nList is empty or has only one node!\n");
        return;
    }

    int swapped;
    struct Node *ptr1, *lptr = head;    // lptr = sorted boundary

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;    // shrink the unsorted region
    } while (swapped);

    printf("\nList sorted successfully!\n");
}

// Display menu
void displayMenu() {
    printf("\n==========================================");
    printf("\n  CIRCULAR LINKED LIST OPERATIONS MENU");
    printf("\n==========================================");
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
    printf("\n12. Sort List");
    printf("\n13. Exit");
    printf("\n==========================================");
    printf("\nEnter your choice: ");
}

// ========================  MAIN  ========================
int main() {
    int choice;

    printf("\n*** CIRCULAR LINKED LIST OPERATIONS PROGRAM ***\n");

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:  createList();        break;
            case 2:  traverseList();      break;
            case 3:  insertAtBeginning(); break;
            case 4:  insertAtEnd();       break;
            case 5:  insertAtPosition();  break;
            case 6:  deleteAtBeginning(); break;
            case 7:  deleteAtEnd();       break;
            case 8:  deleteAtPosition();  break;
            case 9:  deleteByValue();     break;
            case 10: searchElement();     break;
            case 11: countNodes();        break;
            case 12: sortList();          break;
            case 13:
                printf("\nExiting program. Goodbye!\n");
                // Free all nodes — break the circle first
                if (head != NULL) {
                    struct Node* last = getLastNode();
                    last->next = NULL;  // break the circle
                    while (head != NULL) {
                        struct Node* temp = head;
                        head = head->next;
                        free(temp);
                    }
                }
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}
