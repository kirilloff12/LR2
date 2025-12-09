#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void verifyPushFunctionality() {
    Stack testStack;
    initStack(&testStack);

    push(&testStack, 15);
    push(&testStack, 25);
    push(&testStack, 35);

    const Node* topNode = getTop(&testStack);
    assert(topNode && topNode->data == 35);

    destroyStack(&testStack);
    printf("verifyPushFunctionality: PASSED\n");
}

void verifyPopFunctionality() {
    Stack testStack;
    initStack(&testStack);

    push(&testStack, 5);
    push(&testStack, 15);
    push(&testStack, 25);

    pop(&testStack);
    const Node* topNode = getTop(&testStack);
    assert(topNode && topNode->data == 15);

    pop(&testStack);
    topNode = getTop(&testStack);
    assert(topNode && topNode->data == 5);

    pop(&testStack);
    assert(isEmpty(&testStack));

    destroyStack(&testStack);
    printf("verifyPopFunctionality: PASSED\n");
}

void verifyEmptyStackBehavior() {
    Stack testStack;
    initStack(&testStack);

    assert(isEmpty(&testStack));

    push(&testStack, 100);
    assert(!isEmpty(&testStack));

    pop(&testStack);
    assert(isEmpty(&testStack));

    destroyStack(&testStack);
    printf("verifyEmptyStackBehavior: PASSED\n");
}

void verifyValueSearch() {
    Stack testStack;
    initStack(&testStack);

    push(&testStack, 10);
    push(&testStack, 20);
    push(&testStack, 30);

    const Node* foundNode = searchByValue(&testStack, 20);
    assert(foundNode && foundNode->data == 20);

    foundNode = searchByValue(&testStack, 40);
    assert(foundNode == NULL);

    destroyStack(&testStack);
    printf("verifyValueSearch: PASSED\n");
}

void verifyIndexSearch() {
    Stack testStack;
    initStack(&testStack);

    push(&testStack, 10);
    push(&testStack, 20);
    push(&testStack, 30);

    const Node* foundNode = searchByIndex(&testStack, 0);
    assert(foundNode && foundNode->data == 30);

    foundNode = searchByIndex(&testStack, 2);
    assert(foundNode && foundNode->data == 10);

    foundNode = searchByIndex(&testStack, 3);
    assert(foundNode == NULL);

    destroyStack(&testStack);
    printf("verifyIndexSearch: PASSED\n");
}

void verifyTopRetrieval() {
    Stack testStack;
    initStack(&testStack);

    push(&testStack, 10);
    push(&testStack, 15);

    const Node* topNode = getTop(&testStack);
    assert(topNode && topNode->data == 15);

    pop(&testStack);
    topNode = getTop(&testStack);
    assert(topNode && topNode->data == 10);

    pop(&testStack);
    topNode = getTop(&testStack);
    assert(topNode == NULL);

    destroyStack(&testStack);
    printf("verifyTopRetrieval: PASSED\n");
}

void verifyStackDestruction() {
    Stack testStack;
    initStack(&testStack);

    push(&testStack, 10);
    push(&testStack, 20);
    push(&testStack, 30);

    destroyStack(&testStack);
    assert(getTop(&testStack) == NULL);

    printf("verifyStackDestruction: PASSED\n");
}

void verifyNodeCreation() {
    Node* newNode = createNode(50);
    assert(newNode && newNode->data == 50 && newNode->next == NULL);
    free(newNode);
    printf("verifyNodeCreation: PASSED\n");
}

void verifyStackInitialization() {
    Stack testStack;
    initStack(&testStack);
    assert(testStack.top == NULL);
    printf("verifyStackInitialization: PASSED\n");
}

void verifyStackTraversal() {
    Stack testStack;
    initStack(&testStack);

    push(&testStack, 15);
    push(&testStack, 25);
    push(&testStack, 35);

    printf("Expected output: Stack contents: 35 25 15\n");
    printf("Actual output:   ");
    traverseStack(&testStack);

    destroyStack(&testStack);
    printf("verifyStackTraversal: PASSED\n");
}

int main() {
    printf("Executing test suite...\n");

    verifyNodeCreation();
    verifyStackInitialization();
    verifyStackDestruction();
    verifyPushFunctionality();
    verifyPopFunctionality();
    verifyValueSearch();
    verifyIndexSearch();
    verifyTopRetrieval();
    verifyStackTraversal();
    verifyEmptyStackBehavior();

    printf("All tests completed successfully.\n");

    //return 0;
}
