/* ==================== (i) VECTOR: REALLOC AT EACH UPDATE */

typedef struct Stack {
  int top;                      /* size of the stack */
  int* array;                   /* stack elements */
} Stack;

struct Stack* createStack() 
{
    Stack* stack;
    stack = malloc(sizeof(Stack));
    stack->top = 0;
    stack->array = (int*)malloc(stack->top * sizeof(int));
    return stack;
}

int isEmpty(struct Stack* stack){
    if(stack->top) {
        return 0;
    }
    else {
        return 1;
    }
}

void push(struct Stack* stack, int item){
    stack->top++;
    stack->array = (int*)realloc(stack->array, stack->top * sizeof(int));
    stack->array[stack->top-1] = item;
    return;
}

int pop(struct Stack* stack){
    if(stack->top == 0) {
        exit(1);
    }
    int temp = stack->array[stack->top-1];
    stack->top--;
    stack->array = (int*)realloc(stack->array, stack->top * sizeof(int));
    return temp;
}


/* ==================== (ii) VECTOR: REALLOC AT POWERS OF 2 */

typedef struct StackFast {
  int top;                      /* size of the stack */
  int* array;                   /* stack elements */
  int current_power;
} StackFast;

struct StackFast* createStackFast() 
{ 
    StackFast* stack;
    stack = malloc(sizeof(Stack));
    stack->top = 0;
    stack->array = (int*)malloc(stack->top * sizeof(int));
    stack->current_power = 0;
    // stack->powers = (int *)malloc(3 * sizeof(int));
    // for(int i = 0; i < 3; i++) {
    //     stack->powers[i] = 0;
    // }
    return stack;
}

int isEmptyFast(struct StackFast* stack){
    if(stack->top) {
        return 0;
    }
    else {
        return 1;
    }
}

void pushFast(struct StackFast* stack, int item){
    if(stack->current_power == 0) {
        stack->current_power = 1;
        stack->top = 1;
        stack->array = (int*)realloc(stack->array,stack->current_power * sizeof(int));
        stack->array[stack->top-1] = item;
    }
    else if(stack->top++ > stack->current_power) {
        stack->current_power = stack->current_power * 2;
        stack->array = (int*)realloc(stack->array, stack->current_power * sizeof(int));
        stack->array[stack->top-1] = item;
    }
    else {
        stack->array[stack->top-1] = item;
    }
}

int popFast(struct StackFast* stack){
    if(stack->current_power == 0) {
        exit(1);
    }
    else {
        int temp = stack->array[stack->top-1];
        if(stack->top-- <= stack->current_power / 2) {
            stack->current_power = stack->current_power / 2;
            stack->array = (int*)realloc(stack->array, stack->current_power * sizeof(int));
            return temp;
        }
        else
        {
            return temp;
        }
        
    }
}

