/* author: David Ryan-Lynch, 115310721 */

#define MAXSTACKSIZE 256

float stack[MAXSTACKSIZE];  // only takes floats
int current_size = 0;

int is_empty() {
    /* input: none
     * action: check if stack is empty
     * return: 1 if empty, else 0 */
    return current_size == 0 ? 1 : 0;
}

int is_full() {
    /* input: none
     * action: check if stack is full
     * return: 1 if full, else 0 */
    return current_size == MAXSTACKSIZE ? 1 : 0;
}

float pop() {
    /* input: none
     * action: remove and return item on top of stack
     * return: top item on stack, or -0 if no items to pop */
    if (!is_empty()) {
        float num = stack[current_size];
        current_size -= 1;
        return num;
    }
    return -0;
}

void push(float number) {
    /* input: number to push to stack
     * action: push number to top of stack
     * return: top item on stack, or -0 if no items to pop */
    if (!is_full()) {
        current_size += 1;
        stack[current_size] = number;
    }
}
