#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int value;
    struct node *next;
    struct node *prev;
}thunderstruct;

void push_last(thunderstruct *head_node, int value) {
    if (head_node->next == NULL) {
        // First node with data
        head_node->next = malloc(sizeof(thunderstruct));
        head_node->next->value = value;
        head_node->next->next = NULL;
        head_node->next->prev = NULL;
    } else {
        // Second or later node with data
        thunderstruct *current = head_node->next;

        if (current->next == NULL) { //adding the second node with data
            current->next = malloc(sizeof(thunderstruct));
            current->next->value = value;
            current->next->next = current;
            current->next->prev = current;
        }
        else { //adding the third or another node
            while (current->next != head_node->next) {
                current = current->next;
            }
            current->next = malloc(sizeof(thunderstruct));
            current->next->value = value;
            current->next->next = head_node->next;
            current->next->prev = current;
        }
    }
}

/*void push_fr_start(thunderstruct *head_node, int value, int n) {   // n-ty rekord do przeniesienia
    if (head_node->next == NULL)
        return 1;


    for (int i=0; i<=n; i++){

    }
*/


//}





int pop(thunderstruct *current) {
    int value = current->value;
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
    return value;
}

/*void clean(thunderstruct *head_node) {
// TODO
}*/

void printall(thunderstruct *head_node) {
    if (head_node->next == NULL) {
        return;
    } else {
        thunderstruct *current = head_node->next;

        if (current->next == NULL) {
            printf("%d", current->value);
            return;
        }
        else {
            while (current->next != head_node->next) {
                printf("%d ", current->value);
                current = current->next;
            }
            printf("%d", current->value);
        }
    }
}





int main(){
// head_node is not the 1st node in the list
    thunderstruct *head_node = NULL;
    head_node = malloc(sizeof(thunderstruct));

    // malloc test
    if (head_node == NULL)
        return 1;

    head_node->next = NULL;
    head_node->prev = NULL;

    // Randomize
    srand(time(NULL));
    int max = 25;
    int n = 5;
    //printf("Enter nodes number: ");
    //scanf("%d", &n);

    // Create nodes with random values
    for(int i=0; i<n;i++)
        push_last(head_node, (rand() % max+1));

    printf("\nList:\n");
    printall(head_node);

    return 0;
}

