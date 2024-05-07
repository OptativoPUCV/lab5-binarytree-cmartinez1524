#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;
    //new->lower_than = lower_than;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
    if (tree == NULL) return; 

    if (tree->root == NULL) 
    {
        tree->root = createTreeNode(key, value);
        tree->current = tree->root;
        return;
    }

    TreeNode * aux = tree->root;

    while (aux != NULL) 
    {
        if (is_equal(tree, key, aux->pair->key)) 
        {
            tree->current = aux; 
            return; 
        }

        if (tree->lower_than(key, aux->pair->key)) 
        {
            if (aux->left == NULL) 
            {
                aux->left = createTreeNode(key, value); 
                aux->left->parent = aux; 
                tree->current = aux->left; 
                return;
            }
            else
            {
                aux = aux->left; 
            }
        }
        else 
        {
            if (aux->right == NULL)
            {
                aux->right = createTreeNode(key, value);
                aux->right->parent = aux; 
                tree->current = aux->right;
                return;
            }
            else
            {
                aux = aux->right;
            }
        }
    }
}


TreeNode * minimum(TreeNode * x)
{
    while (x->left != NULL) 
    {
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
    if (tree == NULL || node == NULL) return; // Verifica que ni el árbol ni el nodo sean nulos

    if (node->left == NULL && node->right == NULL) { // Nodo sin hijos
        // Desconecta el nodo de su padre
        if (node->parent == NULL) {
            tree->root = NULL; // Si el nodo era la raíz
        } else {
            if (node->parent->left == node) {
                node->parent->left = NULL; // Elimina del padre izquierdo
            } else {
                node->parent->right = NULL; // Elimina del padre derecho
            }
        }
    } else if (node->left != NULL && node->right != NULL) { // Nodo con dos hijos
        // Encuentra el mínimo del subárbol derecho
        TreeNode * min = minimum(node->right);

        // Guarda el `pair` del nodo a eliminar
        Pair * temp = node->pair; 

        // Reemplaza el `pair` con el `pair` del mínimo
        node->pair = min->pair; 

        // Elimina el nodo mínimo
        removeNode(tree, min); 

        // Libera el `pair` antiguo
        free(temp->key); 
        free(temp); 

    } else { // Nodo con un hijo
        // Encuentra el único hijo
        TreeNode * child = node->left != NULL ? node->left : node->right; 

        // Conecta el hijo con el padre del nodo a eliminar
        child->parent = node->parent; 

        if (node->parent == NULL) {
            tree->root = child; // Si el nodo era la raíz
        } else {
            if (node == node->parent->left) {
                node->parent->left = child; // Conecta al padre izquierdo
            } else {
                node->parent->right = child; // Conecta al padre derecho
            }
        }
    }

    // Libera el nodo y su `pair`
    free(node->pair->key);
    free(node->pair);

}


void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) 
{
    if (tree == NULL || tree->root == NULL) return NULL;
    TreeNode * aux = tree->root;
    while (aux != NULL)
        {
            if (is_equal(tree, key, aux->pair->key))
            {
                tree->current = aux;
                return aux->pair;
            }
            if (tree->lower_than(key, aux->pair->key))
            {
                aux = aux->left;
            }
            else
            {
                aux = aux->right;
            } 
        }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
