#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Nod* newNode(char* team, float summary) {
    Nod* node = (Nod*)malloc(sizeof(Nod));
    node->team = (char*)malloc(50 * sizeof(char)); // Alocare dinamică pentru numele echipei

    strcpy(node->team, team);
    node->summary = summary;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Function to get the height of a node
int getHeight(Nod* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to calculate the balance factor of a node
int getBalance(Nod* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Function to perform a right rotation
Nod* rightRotate(Nod* y) {
    Nod* x = y->left;
    Nod* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Function to perform a left rotation
Nod* leftRotate(Nod* x) {
    Nod* y = x->right;
    Nod* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Function to insert a node into the AVL tree
Nod* insertNode(Nod* node, char* team, float summary) {
    if (node == NULL) {
        printf("Inserare nod nou: %s - %.2f\n", team, summary);
        return newNode(team, summary);
    }

    if (summary < node->summary) {
        node->left = insertNode(node->left, team, summary);
    } else if (summary > node->summary) {
        node->right = insertNode(node->right, team, summary);
    } else if(summary == node->summary) {
        int cmp = strcmp(node->team, team);
        if (cmp < 0) {
            node->left = insertNode(node->left, team, summary);
        } else if (cmp > 0) {
            node->right = insertNode(node->right, team, summary);
        }
        // Daca echipele au acelasi summary si numele sunt la fel nu facem nimic.
    }

    // Actualizează înălțimea nodului curent
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Calculează factorul de echilibrare al nodului curent
    int balance = getBalance(node);

    // Rotații pentru a menține arborele echilibrat
    if (balance > 1 && summary < node->left->summary) {
        return rightRotate(node);
    }

    if (balance < -1 && summary > node->right->summary) {
        return leftRotate(node);
    }

    if (balance > 1 && summary > node->left->summary) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && summary < node->right->summary) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Print nodes at level 2
void printLevel2Teams(Nod* root) {
    if (root == NULL) {
        return;
    }

    if (root->left != NULL && root->right != NULL) {
        printf("Level 2 Nodes:\n");
        printf("%s\n", root->left->team);
        printf("%s\n", root->right->team);
    } else {
        printf("The tree does not have enough nodes at level 2.\n");
    }
}

// Free memory allocated for the tree
void FreeTree(Nod* root) {
    if (root == NULL) {
        return;
    }
    FreeTree(root->left);
    FreeTree(root->right);
    free(root->team); // Free memory allocated for team name
    free(root);
}

// In-order traversal of the tree
void inOrderTraversal(Nod* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%s - %.2f\n", root->team, root->summary);
        inOrderTraversal(root->right);
    }
}

