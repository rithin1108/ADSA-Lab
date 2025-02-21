#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left, *right;
    int ht;
} node;

node* insert(node*, int);
node* Delete(node*, int);
void inorder(node*);
int height(node*);
node* rotateright(node*);
node* rotateleft(node*);
node* RR(node*);
node* LL(node*);
node* LR(node*);
node* RL(node*);
int BF(node*);

int main() {
    node *root = NULL;
    int x, n, i, op;
    
    do {
        printf("\nAVL TREE OPERATIONS\n");
        printf("\n1) Create");
        printf("\n2) Insert");
        printf("\n3) Delete");
        printf("\n4) Display");
        printf("\n5) Quit");
        printf("\n\nEnter Your Choice: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("\nEnter number of elements: ");
                scanf("%d", &n);
                printf("\nEnter tree data: ");
                root = NULL;
                for (i = 0; i < n; i++) {
                    scanf("%d", &x);
                    root = insert(root, x);
                }
                printf("AVL Tree is created with %d elements\n", n);
                break;

            case 2:
                printf("\nEnter a data: ");
                scanf("%d", &x);
                root = insert(root, x);
                printf("\nThe element %d is inserted successfully\n", x);
                break;

            case 3:
                printf("\nEnter a data: ");
                scanf("%d", &x);
                root = Delete(root, x);
                printf("\nThe element %d is deleted successfully\n", x);
                break;

            case 4:
                printf("\n\nInorder sequence:\n");
                inorder(root);
                printf("\n");
                break;
        }
    } while (op != 5);

    return 0;
}

node* insert(node *T, int x) {
    if (T == NULL) {
        T = (node*)malloc(sizeof(node));
        T->data = x;
        T->left = NULL;
        T->right = NULL;
        T->ht = 1;
        return T;
    }
    
    if (x > T->data) {
        T->right = insert(T->right, x);
        if (BF(T) == -2) {
            if (x > T->right->data)
                T = RR(T);
            else
                T = RL(T);
        }
    } else if (x < T->data) {
        T->left = insert(T->left, x);
        if (BF(T) == 2) {
            if (x < T->left->data)
                T = LL(T);
            else
                T = LR(T);
        }
    }

    T->ht = height(T);
    return T;
}

node* Delete(node *T, int x) {
    if (T == NULL) {
        return NULL;
    }

    if (x > T->data) {
        T->right = Delete(T->right, x);
        if (BF(T) == 2) {
            if (BF(T->left) >= 0)
                T = LL(T);
            else
                T = LR(T);
        }
    } else if (x < T->data) {
        T->left = Delete(T->left, x);
        if (BF(T) == -2) {
            if (BF(T->right) <= 0)
                T = RR(T);
            else
                T = RL(T);
        }
    } else {
        if (T->right != NULL) {
            node *p = T->right;
            while (p->left != NULL)
                p = p->left;
            T->data = p->data;
            T->right = Delete(T->right, p->data);
            if (BF(T) == 2) {
                if (BF(T->left) >= 0)
                    T = LL(T);
                else
                    T = LR(T);
            }
        } else {
            node *temp = T;
            T = T->left;
            free(temp);
            return T;
        }
    }

    T->ht = height(T);
    return T;
}

int height(node *T) {
    if (T == NULL) return 0;
    int lh = (T->left) ? T->left->ht : 0;
    int rh = (T->right) ? T->right->ht : 0;
    return (lh > rh ? lh : rh) + 1;
}

node* rotateright(node *x) {
    node *y = x->left;
    x->left = y->right;
    y->right = x;
    x->ht = height(x);
    y->ht = height(y);
    return y;
}

node* rotateleft(node *x) {
    node *y = x->right;
    x->right = y->left;
    y->left = x;
    x->ht = height(x);
    y->ht = height(y);
    return y;
}

node* RR(node *T) {
    return rotateleft(T);
}

node* LL(node *T) {
    return rotateright(T);
}

node* LR(node *T) {
    T->left = rotateleft(T->left);
    return rotateright(T);
}

node* RL(node *T) {
    T->right = rotateright(T->right);
    return rotateleft(T);
}

int BF(node *T) {
    if (T == NULL) return 0;
    int lh = (T->left) ? T->left->ht : 0;
    int rh = (T->right) ? T->right->ht : 0;
    return lh - rh;
}

void inorder(node *T) {
    if (T != NULL) {
        inorder(T->left);
        printf("%d(Bf=%d) ", T->data, BF(T));
        inorder(T->right);
    }
}
