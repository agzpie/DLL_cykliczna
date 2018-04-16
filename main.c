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
            current->prev = current->next;
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
            head_node->next->prev = current->next;
        }
    }
}

void move(thunderstruct* head_node, int n, int k, char kier) {
    thunderstruct* current;
    if (kier == 'p') {
        current = head_node->next;
        while (n>0) {
            current = current->next;
            n--;
        }
        thunderstruct* moved_node = current;
        current->prev->next = current->next;
        current->next->prev = current->prev;

        while (k>0) {
            current = current->next;
            k--;
        }
        moved_node->prev = current;
        moved_node->next = current->next;
        current->next->prev = moved_node;
        current->next = moved_node;
    }
    else {
        current = head_node->next->prev;
        while (n>0) {
            current = current->prev;
            n--;
        }
        thunderstruct* moved_node = current;
        current->prev->next = current->next;
        current->next->prev = current->prev;

        while (k>0) {
            current = current->prev;
            k--;
        }
        moved_node->next = current;
        moved_node->prev = current->prev;
        current->prev->next = moved_node;
        current->prev = moved_node;
    }
}

/*int pop(thunderstruct *current) {
    int value = current->value;
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
    return value;
}*/

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

/*void push_after(thunderstruct* node, int value) { // value - value added to the list
}*/





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
    int max = 99;
    int m, n, k;
    char kier;
    printf("Ilosc node'ow:\n");
    scanf("%d", &m);
    printf("Ktory node przeniesc?\n");
    scanf("%d", &n);
    if (n<0 || m<=0) {
        printf("Program nie zadziala poprawnie. Podaj odpowiednie liczby.\n");
        return 1;
    }
    printf("O ile pozycji node ma byc przeniesiony?\n");
    scanf("%d", &k);
    printf("Podaj kierunek poruszania, gdzie k - od konca, p - od poczaktu:\n");
    scanf(" %c", &kier);
    //if (k<=0 || (kier != 'k' && kier != 'p')) {
     //   printf("Zle parametry.\n");
      //  return 1;
    //}
    // Create nodes with random values
    for (int i=0; i<m; i++)
        push_last(head_node, (rand() % max+1));

    printf("\nLista:\n");
    printall(head_node);

    move(head_node, n, k, kier);

    printf("\nZmieniona lista:\n");
    printall(head_node);

    return 0;
}

