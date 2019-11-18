#pragma once

// include this library to use NULL, otherwise use nullptr instead
#include <cstddef>
#include <iostream>
#include "node.hpp"
using namespace std;

template<class T>
class BST{
public:
    // Constructor for the BST class, creates an empty tree
    BST(void);
    // Destructor for the BST class, destroys the tree
    ~BST(void);
    // Inserts data into the tree
    // param: The data to be inserted into the tree
    void insert(T);
    // Removes data from the tree
    // param: The data to be removed from the tree
    void remove(T);
    // Performs an inorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *inorder(void);
    // Performs an postorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *postorder(void);
    // Performs an preorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *preorder(void);
    // Searches the tree for a given value
    // param: the data to search for
    // returns: a pointer to the node containing the data or NULL if the data
    //          was not found
    Node<T> *search(T);
    // Gets the current number of nodes in the tree
    // returns: the number of nodes in the tree
    int get_size(void);
private:
    // the root node of the tree
    Node<T> *root;
    // the number of nodes in the tree
    int nodeCounter;
    void inorderUtil(std::vector<T>*, Node<T>*);
    void preorderUtil(std::vector<T>*, Node<T>*);
    void postorderUtil(std::vector<T>*, Node<T>*);
    Node<T>*searchUtil(int, Node<T>*);
    Node<T>*inHelpers(int, Node<T>*); 
};

template<class T>
BST<T>::BST()
{
    root = NULL;
    nodeCounter = 0;
}

template<class T>
BST<T>::~BST()
{
    root = NULL;
    while(root != NULL)
    {
        remove(root->get_data());
    }
}


template<class T>
void BST<T>::inorderUtil(std::vector<T>* vec, Node<T>* Node)
{
    if(Node == NULL)
    {
        return;
    }
    inorderUtil(vec, Node->get_left());
    vec->push_back( Node->get_data());
    inorderUtil(vec, Node->get_right());   
  
}
template<class T>
std::vector<T> * BST<T>::inorder()
{
    std::vector<T> *vec = new std::vector<T>;
    inorderUtil(vec, root);
    return vec;
}

template<class T>
void BST<T>::preorderUtil(std::vector<T>* vec, Node<T>* Node)
{
    if(Node == NULL)
    {
        return;
    }
    vec->push_back(Node->get_data());
    preorderUtil(vec,Node->get_left());
    preorderUtil(vec,Node->get_right());
}   
    
template<class T>
std::vector<T> * BST<T>::preorder()
{
    std::vector<T> *vec = new std::vector<T>;
    preorderUtil(vec, root);
    return vec;
}

template<class T>
void BST<T>::postorderUtil(std::vector<T>* vec, Node<T>* Node)
{
    if(Node == NULL)
    {
        return;
    }
    postorderUtil(vec,Node->get_left());
    postorderUtil(vec,Node->get_right());
    vec->push_back(Node->get_data());  
}

template<class T>
std::vector<T> * BST<T>::postorder()
{
    std::vector<T> *vec = new std::vector<T>;
    postorderUtil(vec, root);
    return vec;
}

template<class T>
void BST<T>::insert(T new_data)
{
    root=inHelpers(new_data,root);
}

template<class T>
Node<T>* BST<T>::inHelpers(int data, Node<T>* currentNode)
{
    
    if(currentNode == NULL)
    {
        Node<T>* temp = new Node<T>;
        temp->set_data(data);
        temp->set_left(NULL);
        temp->set_right(NULL);
        nodeCounter++;
        return temp;
    }
    else
        if(data < currentNode->get_data())
        {
            currentNode->set_left(inHelpers(data, currentNode->get_left()));
        }
        else
        {
            currentNode->set_right(inHelpers(data, currentNode->get_right()));
        }
    return currentNode;    
}

template<class T>
Node<T>* BST<T>::search(T val)
{
    return searchUtil(val, root);
}
template<class T>
Node<T>* BST<T>::searchUtil(int findValue, Node<T>* currNode)
{
    if(currNode == NULL)
    {
        return currNode;
    }
    else if(findValue < currNode->get_data())
        {
            return searchUtil(findValue, currNode->get_left());
        }   
        else if(findValue > currNode->get_data())
        {
            return searchUtil(findValue, currNode->get_right());
        }
    return currNode;
}

template<class T>
void BST<T>::remove(T val)
{
    Node<T>* top = NULL;
    Node<T>* currentNode = root;
    while(currentNode != NULL)
    {   
        if(val == currentNode->get_data())
        {  
            if((currentNode->get_left() == NULL) && (currentNode->get_right() == NULL))
            {  
                if(top == NULL)
                {
                    root = NULL;
                }
                else if(top->get_left() == currentNode)
                {
                    
                    top->set_left(NULL);
                }
                else if(top->get_right() == currentNode)
                {
                    
                    top->set_right(NULL);
                }
                delete(currentNode);
                nodeCounter--;
            }
            else if(currentNode->get_left() == NULL)
                {   
                    if(top == NULL)
                        {
                            root = currentNode->get_right();
                        }
                    else if(top->get_left() == currentNode)
                    {
                        top->set_left(currentNode->get_right());
                    }
                    else
                    {
                        top->set_right(currentNode->get_right());
                    }
                    delete(currentNode);
                    nodeCounter--;
                }
                else if(currentNode->get_right() == NULL)
                    {  
                        if(top == NULL)
                        {
                            root = currentNode->get_left();
                        }
                        else if(top->get_left() == currentNode)
                        {
                            top->set_left(currentNode->get_left());
                        }
                        else
                        {
                            top->set_right(currentNode->get_left());
                        }
                        delete(currentNode);
                        nodeCounter--;
                    }
                    else
                    {   
                        Node<T>* repeatNode = currentNode->get_right();
                        while(repeatNode->get_left() != NULL)
                        {
                            repeatNode = repeatNode->get_left();
                        }
                        T repeatData = repeatNode->get_data();
                        remove(repeatData);
                        currentNode->set_data(repeatData);
                    }
        }
        else if(val > currentNode->get_data())
            { 
                top = currentNode;
                currentNode = currentNode->get_right();
            }
            else 
            { 
                top = currentNode;
                currentNode = currentNode->get_left();
            }
    }
}

template<class T>
int BST<T>::get_size()
{
    return nodeCounter;
}