#define STACK_H_

// Define maximum size of the stack (adjust as needed)
#define MAX_STACK_SIZE 50

// Stack structure
typedef struct {
    int top;
    int row[MAX_STACK_SIZE];
    int col[MAX_STACK_SIZE];
} Stack;

// Initialize the stack
void initStack(Stack *s) {
    s->top = -1;  // Initialize top to -1 (empty stack)
}

// Check if the stack is empty
int isEmpty(Stack *s) {
    return (s->top == -1);
}

// Push an element onto the stack
void push(Stack *s, int r, int c) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->top++;
        s->row[s->top] = r;
        s->col[s->top] = c;
    }
}

// Pop an element from the stack
void pop(Stack *s) {
    if (!isEmpty(s)) {
        s->top--;
    }
}

// Get the top element without popping it
void top(Stack *s, int *r, int *c) {
    if (!isEmpty(s)) {
        *r = s->row[s->top];
        *c = s->col[s->top];
    }
}
