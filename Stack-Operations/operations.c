#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * ============================================================================
 *  STACK — COMPLETE OPERATIONS (Array-Based + Linked-List-Based)
 * ============================================================================
 *
 *  A Stack is an abstract data type (ADT) that follows the LIFO principle:
 *  Last In, First Out.
 *
 *  Think of a stack of plates:
 *    - You can only ADD a plate on TOP (push).
 *    - You can only REMOVE the plate on TOP (pop).
 *    - You can only SEE the plate on TOP (peek).
 *
 *  The TWO fundamental operations:
 *    - push(x)  : add element x to the top
 *    - pop()    : remove and return the top element
 *
 *  Additional operations:
 *    - peek()   : return the top element WITHOUT removing it
 *    - isEmpty(): check if the stack has no elements
 *    - isFull() : check if the stack is at capacity (array-based only)
 *    - display(): show all elements
 *
 *  Why it matters:
 *    Stacks are EVERYWHERE in computer science:
 *    - Function call stack (how recursion works)
 *    - DFS (Depth-First Search) in trees and graphs
 *    - Expression evaluation (infix → postfix)
 *    - Undo operations
 *    - Balanced parentheses checking
 *    - Browser back button
 *
 *  Two implementations:
 *    1. ARRAY-BASED  — fixed size, O(1) push/pop, simple
 *    2. LINKED-LIST-BASED — dynamic size, O(1) push/pop, no overflow
 *
 *  This program demonstrates BOTH implementations plus 3 classic applications.
 *
 * ============================================================================
 */

/* ===========================
 *  PART 1: ARRAY-BASED STACK
 * =========================== */

/*
 * Array-based stack uses a fixed-size array and a 'top' variable.
 *
 * 'top' is the INDEX of the topmost element:
 *   - top = -1    → stack is empty
 *   - top = 0     → one element (at index 0)
 *   - top = MAX-1 → stack is full
 *
 * Push: increment top, then store the value at arr[top].
 * Pop:  read the value at arr[top], then decrement top.
 *
 * Advantages:
 *   - Very simple implementation
 *   - Cache-friendly (contiguous memory)
 *   - No malloc/free overhead
 *
 * Disadvantages:
 *   - Fixed size — must choose MAX upfront
 *   - Stack overflow if MAX is exceeded
 *   - Wasted memory if MAX is too large
 */

#define MAX_SIZE 100    // maximum capacity for the array-based stack

struct ArrayStack {
    int arr[MAX_SIZE];  // the underlying array
    int top;            // index of the top element (-1 = empty)
};

/*
 * Initialises the array stack.
 * Sets top to -1, meaning the stack starts empty.
 */
void initArrayStack(struct ArrayStack* stack) {
    stack->top = -1;
}

/*
 * Checks if the array stack is empty.
 * The stack is empty when top is -1 (no elements have been pushed,
 * or all pushed elements have been popped).
 */
int isEmptyArray(struct ArrayStack* stack) {
    return stack->top == -1;
}

/*
 * Checks if the array stack is full.
 * The stack is full when top reaches MAX_SIZE - 1 (the last valid index).
 * This check is needed BEFORE every push to prevent array overflow.
 */
int isFullArray(struct ArrayStack* stack) {
    return stack->top == MAX_SIZE - 1;
}

/*
 * Push: Adds an element to the top of the stack.
 *
 * Steps:
 *   1. Check if the stack is full (overflow condition).
 *   2. Increment top (move the "top" pointer up by one).
 *   3. Store the value at arr[top].
 *
 * Why increment BEFORE storing:
 *   top starts at -1 (empty). After increment, top = 0, and we store at arr[0].
 *   This way arr[top] always points to the actual top element.
 *
 * Time: O(1). Space: O(1).
 */
void pushArray(struct ArrayStack* stack, int value) {
    if (isFullArray(stack)) {
        printf("Stack Overflow! Cannot push %d.\n", value);
        return;
    }
    stack->top++;                   // move top up
    stack->arr[stack->top] = value; // store at the new top position
    printf("Pushed %d onto the stack.\n", value);
}

/*
 * Pop: Removes and returns the top element.
 *
 * Steps:
 *   1. Check if the stack is empty (underflow condition).
 *   2. Read the value at arr[top].
 *   3. Decrement top (the element is logically removed).
 *
 * We don't need to actually erase arr[top] — decrementing top means
 * that index is now outside the "valid" portion of the stack.
 * Future pushes will overwrite it.
 *
 * Time: O(1). Space: O(1).
 */
int popArray(struct ArrayStack* stack) {
    if (isEmptyArray(stack)) {
        printf("Stack Underflow! Cannot pop.\n");
        return -1;      // sentinel value indicating error
    }
    int value = stack->arr[stack->top];     // read top element
    stack->top--;                           // logically remove it
    return value;
}

/*
 * Peek: Returns the top element WITHOUT removing it.
 *
 * Same as pop but without decrementing top. The stack remains unchanged.
 * Useful when you need to inspect the top without modifying the stack.
 */
int peekArray(struct ArrayStack* stack) {
    if (isEmptyArray(stack)) {
        printf("Stack is empty! Nothing to peek.\n");
        return -1;
    }
    return stack->arr[stack->top];
}

/*
 * Display: Prints all elements from top to bottom.
 *
 * We iterate from top down to 0 because the topmost element
 * is at index 'top' and the bottom is at index 0.
 *
 * This shows the stack in the order you'd see it physically:
 *   TOP → bottom.
 */
void displayArray(struct ArrayStack* stack) {
    if (isEmptyArray(stack)) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack (top → bottom): ");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d", stack->arr[i]);
        if (i > 0) printf(" | ");
    }
    printf("\n");
    printf("Size: %d / %d\n", stack->top + 1, MAX_SIZE);
}


/* ==================================
 *  PART 2: LINKED-LIST-BASED STACK
 * ================================== */

/*
 * Linked-list-based stack uses a singly linked list where the HEAD
 * of the list is the TOP of the stack.
 *
 * Why head = top?
 *   - Push = insert at beginning → O(1)
 *   - Pop = delete from beginning → O(1)
 *   If we used the tail as top, pop would be O(n) because SLL can't
 *   access the second-to-last node without traversal.
 *
 * Advantages:
 *   - No fixed size — grows/shrinks dynamically
 *   - No overflow (unless the system runs out of memory)
 *   - No wasted space
 *
 * Disadvantages:
 *   - Extra memory for pointers in each node
 *   - Not cache-friendly (nodes may be scattered in memory)
 *   - malloc/free overhead per push/pop
 */

struct StackNode {
    int data;
    struct StackNode* next;
};

/*
 * The 'top' pointer for the linked-list stack.
 * This is the HEAD of the linked list.
 * When the stack is empty, top is NULL.
 */
struct StackNode* top = NULL;

/*
 * Checks if the linked-list stack is empty.
 * Empty when the top pointer is NULL (no nodes in the list).
 */
int isEmptyLL() {
    return top == NULL;
}

/*
 * Push: Adds an element to the top (front of the linked list).
 *
 * Steps:
 *   1. Create a new node.
 *   2. Set newNode->next = top  (new node points to the current top).
 *   3. Update top = newNode     (new node becomes the new top).
 *
 * This is exactly the same as "insert at beginning" in a singly linked list!
 * The stack abstraction is just a restricted interface over a linked list.
 *
 * Time: O(1). Space: O(1) per push.
 */
void pushLL(int value) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed! Cannot push.\n");
        return;
    }
    newNode->data = value;
    newNode->next = top;    // point to old top
    top = newNode;          // new node is now the top
    printf("Pushed %d onto the stack.\n", value);
}

/*
 * Pop: Removes and returns the top element (front of the linked list).
 *
 * Steps:
 *   1. Save top in temp.
 *   2. Read temp->data.
 *   3. Move top to top->next (second node becomes new top).
 *   4. Free temp.
 *
 * This is exactly "delete at beginning" in a singly linked list!
 *
 * Time: O(1). Space: O(1).
 */
int popLL() {
    if (isEmptyLL()) {
        printf("Stack Underflow! Cannot pop.\n");
        return -1;
    }
    struct StackNode* temp = top;
    int value = temp->data;
    top = top->next;        // move top down
    free(temp);             // free the old top node
    return value;
}

/*
 * Peek: Returns the top element without removing it.
 */
int peekLL() {
    if (isEmptyLL()) {
        printf("Stack is empty! Nothing to peek.\n");
        return -1;
    }
    return top->data;
}

/*
 * Display: Prints all elements from top to bottom.
 * Simply traverse the linked list from head (top) to NULL (bottom).
 */
void displayLL() {
    if (isEmptyLL()) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack (top → bottom): ");
    struct StackNode* temp = top;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) printf(" | ");
        temp = temp->next;
    }
    printf("\n");
}


/* ============================================
 *  PART 3: APPLICATIONS OF STACKS
 * ============================================ */

/*
 * APPLICATION 1: Balanced Parentheses Checker
 *
 * Given a string of brackets like "({[]})", determine if every opening
 * bracket has a matching closing bracket in the correct order.
 *
 * Algorithm:
 *   - For each character:
 *     - If it's an OPENING bracket ( '(', '{', '[' ), push it onto the stack.
 *     - If it's a CLOSING bracket ( ')', '}', ']' ):
 *       1. If the stack is empty → UNBALANCED (no matching opener).
 *       2. Pop the top. If it doesn't match the closer → UNBALANCED.
 *   - After processing all characters:
 *     - If the stack is empty → BALANCED.
 *     - If not empty → UNBALANCED (unclosed openers remain).
 *
 * Why a stack?
 *   Brackets are NESTED — the most recent opener must match the next closer.
 *   That's LIFO behavior, which is exactly what a stack provides.
 *
 * Examples:
 *   "({[]})"   → Balanced ✓   (each closer matches its nearest opener)
 *   "({[}])"   → Unbalanced ✗ ('[' should close before '{' but doesn't)
 *   "((())"    → Unbalanced ✗ (extra opener '(' without a closer)
 */
void checkBalancedParentheses() {
    char expr[256];
    printf("\nEnter an expression with brackets: ");
    scanf("%s", expr);

    // Use a simple array-based stack for characters
    char stack[256];
    int stackTop = -1;

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        // Push opening brackets
        if (ch == '(' || ch == '{' || ch == '[') {
            stack[++stackTop] = ch;
        }
        // Check closing brackets
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (stackTop == -1) {
                // No opener to match — unbalanced
                printf("\nResult: UNBALANCED (extra closing '%c' at position %d)\n", ch, i);
                return;
            }

            char topChar = stack[stackTop--];   // pop

            // Check if the popped opener matches the closer
            if ((ch == ')' && topChar != '(') ||
                (ch == '}' && topChar != '{') ||
                (ch == ']' && topChar != '[')) {
                printf("\nResult: UNBALANCED (mismatched '%c' and '%c')\n", topChar, ch);
                return;
            }
        }
    }

    if (stackTop == -1) {
        printf("\nResult: BALANCED ✓\n");
    } else {
        printf("\nResult: UNBALANCED (unclosed openers remain)\n");
    }
}

/*
 * APPLICATION 2: Infix to Postfix Conversion
 *
 * Infix:   operators between operands     →  A + B
 * Postfix: operators after operands       →  A B +
 * Prefix:  operators before operands      →  + A B
 *
 * Why convert?
 *   Computers evaluate POSTFIX expressions much more easily than infix.
 *   Postfix has no ambiguity — no need for parentheses or precedence rules
 *   during evaluation. Compilers convert infix → postfix as a first step.
 *
 * Algorithm (Shunting-Yard by Dijkstra):
 *   For each token in the infix expression:
 *     - If OPERAND (letter/digit): add directly to output.
 *     - If '(': push onto stack.
 *     - If ')': pop from stack to output until '(' is found. Discard '('.
 *     - If OPERATOR (+, -, *, /, ^):
 *       While the stack has an operator on top with HIGHER or EQUAL precedence
 *       (except ^ which is right-associative), pop it to output.
 *       Then push the current operator.
 *   After all tokens: pop remaining operators to output.
 *
 * Precedence: ^ (highest) > * / > + - (lowest)
 *
 * Example:  A + B * C  →  A B C * +
 *   Step 1: A → output = "A"
 *   Step 2: + → push. Stack: [+]
 *   Step 3: B → output = "A B"
 *   Step 4: * → higher precedence than +, push. Stack: [+, *]
 *   Step 5: C → output = "A B C"
 *   Step 6: end → pop all. output = "A B C * +"
 */
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;   // for '(' or unknown
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

void infixToPostfix() {
    char infix[256], postfix[256];
    char stack[256];
    int stackTop = -1;
    int j = 0;     // index for postfix output

    printf("\nEnter an infix expression (single chars, e.g., A+B*C): ");
    scanf("%s", infix);

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ||
            (ch >= '0' && ch <= '9')) {
            // Operand — add directly to output
            postfix[j++] = ch;
        }
        else if (ch == '(') {
            // Left parenthesis — push onto stack
            stack[++stackTop] = ch;
        }
        else if (ch == ')') {
            // Right parenthesis — pop until matching '('
            while (stackTop >= 0 && stack[stackTop] != '(') {
                postfix[j++] = stack[stackTop--];
            }
            if (stackTop >= 0) stackTop--;  // discard '('
        }
        else if (isOperator(ch)) {
            // Operator — pop operators with >= precedence (left-to-right)
            // Exception: ^ is right-associative, so only pop if STRICTLY greater
            while (stackTop >= 0 && isOperator(stack[stackTop]) &&
                   ((ch != '^' && precedence(stack[stackTop]) >= precedence(ch)) ||
                    (ch == '^' && precedence(stack[stackTop]) > precedence(ch)))) {
                postfix[j++] = stack[stackTop--];
            }
            stack[++stackTop] = ch;
        }
    }

    // Pop remaining operators
    while (stackTop >= 0) {
        postfix[j++] = stack[stackTop--];
    }
    postfix[j] = '\0';     // null-terminate the string

    printf("Postfix: %s\n", postfix);
}

/*
 * APPLICATION 3: Postfix Expression Evaluation
 *
 * Given a postfix expression like "23*54*+", evaluate it.
 *
 * Algorithm:
 *   For each token:
 *     - If OPERAND (digit): push its numeric value onto the stack.
 *     - If OPERATOR: pop two operands (right first, then left),
 *       apply the operator, push the result.
 *   After all tokens: the stack contains exactly one element — the result.
 *
 * Why pop right FIRST?
 *   The second operand was pushed LAST (it's on top). For non-commutative
 *   operators like subtraction and division, order matters:
 *     "53-" means 5 - 3, not 3 - 5.
 *   So we pop 3 (right), then 5 (left), compute left OP right = 5 - 3 = 2.
 *
 * Example: "23*54*+"
 *   Push 2     Stack: [2]
 *   Push 3     Stack: [2, 3]
 *   *: pop 3,2 → 2*3=6.  Stack: [6]
 *   Push 5     Stack: [6, 5]
 *   Push 4     Stack: [6, 5, 4]
 *   *: pop 4,5 → 5*4=20. Stack: [6, 20]
 *   +: pop 20,6 → 6+20=26. Stack: [26]
 *   Result: 26
 */
void evaluatePostfix() {
    char expr[256];
    printf("\nEnter a postfix expression (single-digit operands, e.g., 23*54*+): ");
    scanf("%s", expr);

    int stack[256];
    int stackTop = -1;

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        if (ch >= '0' && ch <= '9') {
            // Operand — push its numeric value
            stack[++stackTop] = ch - '0';   // convert char to int
        }
        else if (isOperator(ch)) {
            if (stackTop < 1) {
                printf("Invalid expression!\n");
                return;
            }
            int right = stack[stackTop--];  // pop right operand (top)
            int left  = stack[stackTop--];  // pop left operand (below top)
            int result;

            switch (ch) {
                case '+': result = left + right; break;
                case '-': result = left - right; break;
                case '*': result = left * right; break;
                case '/':
                    if (right == 0) {
                        printf("Division by zero error!\n");
                        return;
                    }
                    result = left / right;
                    break;
                case '^': {
                    result = 1;
                    for (int p = 0; p < right; p++) result *= left;
                    break;
                }
                default:
                    printf("Unknown operator: %c\n", ch);
                    return;
            }

            stack[++stackTop] = result;     // push result back
        }
    }

    if (stackTop == 0) {
        printf("Result: %d\n", stack[0]);
    } else {
        printf("Invalid expression! (too many operands)\n");
    }
}


/* ============================================
 *  PART 4: MAIN MENU
 * ============================================ */

void displayMenu() {
    printf("\n=============================================");
    printf("\n           STACK OPERATIONS MENU");
    printf("\n=============================================");
    printf("\n --- Array-Based Stack ---");
    printf("\n1.  Push (Array)");
    printf("\n2.  Pop (Array)");
    printf("\n3.  Peek (Array)");
    printf("\n4.  Display (Array)");
    printf("\n5.  Check Empty (Array)");
    printf("\n6.  Check Full (Array)");
    printf("\n --- Linked-List-Based Stack ---");
    printf("\n7.  Push (Linked List)");
    printf("\n8.  Pop (Linked List)");
    printf("\n9.  Peek (Linked List)");
    printf("\n10. Display (Linked List)");
    printf("\n11. Check Empty (Linked List)");
    printf("\n --- Applications ---");
    printf("\n12. Check Balanced Parentheses");
    printf("\n13. Infix to Postfix Conversion");
    printf("\n14. Evaluate Postfix Expression");
    printf("\n15. Exit");
    printf("\n=============================================");
    printf("\nEnter your choice: ");
}

int main() {
    int choice, value;
    struct ArrayStack arrStack;
    initArrayStack(&arrStack);

    printf("\n*** STACK OPERATIONS PROGRAM ***\n");

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            // Array-based stack operations
            case 1:
                printf("\nEnter value to push: ");
                scanf("%d", &value);
                pushArray(&arrStack, value);
                break;
            case 2:
                value = popArray(&arrStack);
                if (value != -1) printf("Popped: %d\n", value);
                break;
            case 3:
                value = peekArray(&arrStack);
                if (value != -1) printf("Top element: %d\n", value);
                break;
            case 4:
                displayArray(&arrStack);
                break;
            case 5:
                printf("Array stack is %s.\n", isEmptyArray(&arrStack) ? "empty" : "not empty");
                break;
            case 6:
                printf("Array stack is %s.\n", isFullArray(&arrStack) ? "full" : "not full");
                break;

            // Linked-list-based stack operations
            case 7:
                printf("\nEnter value to push: ");
                scanf("%d", &value);
                pushLL(value);
                break;
            case 8:
                value = popLL();
                if (value != -1) printf("Popped: %d\n", value);
                break;
            case 9:
                value = peekLL();
                if (value != -1) printf("Top element: %d\n", value);
                break;
            case 10:
                displayLL();
                break;
            case 11:
                printf("Linked list stack is %s.\n", isEmptyLL() ? "empty" : "not empty");
                break;

            // Applications
            case 12:
                checkBalancedParentheses();
                break;
            case 13:
                infixToPostfix();
                break;
            case 14:
                evaluatePostfix();
                break;

            case 15:
                printf("\nExiting program. Goodbye!\n");
                // Free linked list stack
                while (top != NULL) {
                    struct StackNode* temp = top;
                    top = top->next;
                    free(temp);
                }
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}
