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
    if (tree == NULL) return; // Asegúrate de que el árbol no sea nulo

    if (tree->root == NULL) // Si el árbol está vacío
    {
        tree->root = createTreeNode(key, value);
        tree->current = tree->root; // Apunta al nodo recién insertado
        return;
    }

    TreeNode * aux = tree->root; // Nodo auxiliar para recorrer el árbol

    while (aux != NULL) // Mientras no hayas llegado al final del árbol
    {
        if (is_equal(tree, key, aux->pair->key)) // Si el nodo ya existe
        {
            tree->current = aux; // Actualiza el current
            return; // No hagas nada más
        }

        if (tree->lower_than(key, aux->pair->key)) // Si la clave es menor, ve a la izquierda
        {
            if (aux->left == NULL) // Si no hay nodo a la izquierda
            {
                aux->left = createTreeNode(key, value); // Crea el nodo
                aux->left->parent = aux; // Establece el padre
                tree->current = aux->left; // Actualiza el current
                return;
            }
            else
            {
                aux = aux->left; // Sigue hacia la izquierda
            }
        }
        else // Si la clave es mayor, ve a la derecha
        {
            if (aux->right == NULL) // Si no hay nodo a la derecha
            {
                aux->right = createTreeNode(key, value); // Crea el nodo
                aux->right->parent = aux; // Establece el padre
                tree->current = aux->right; // Actualiza el current
                return;
            }
            else
            {
                aux = aux->right; // Sigue hacia la derecha
            }
        }
    }
}


TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

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
