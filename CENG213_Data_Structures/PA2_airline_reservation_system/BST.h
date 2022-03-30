#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan
{
    preorder,
    inorder,
    postorder
};

template <class T>
class BST
{
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp = inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;
    BSTNode<T> *copy_construct_helper(const BSTNode<T> *obj)
    {
        if (obj == NULL)
        {
            return NULL;
        }
        BSTNode<T> *newNode = new BSTNode<T>();
        newNode->data = obj->data;
        newNode->left = copy_construct_helper(obj->left);
        newNode->right = copy_construct_helper(obj->right);
        return newNode;
    }
    bool containsHelper(BSTNode<T> *r, BSTNode<T> *node) const
    {
        if (r == NULL)
        {
            return false;
        }
        else
        {
            if (node->data == r->data)
            {
                return true;
            }
            else if (node->data < r->data)
            {
                return containsHelper(r->left, node);
            }
            else
            {
                return containsHelper(r->right, node);
            }
        }
        return false;
    }
    BSTNode<T> *insertHelper(BSTNode<T> *r, const T &data)
    {
        if (r == NULL)
        {
            r = new BSTNode<T>(data, NULL, NULL);
            // if (r)
            //     std::cout << r->data << std::endl;
            return r;
        }
        else if (data < r->data)
        {
            r->left = insertHelper(r->left, data);
        }
        else if (data > r->data)
        {
            r->right = insertHelper(r->right, data);
        }
        return r;
    }
    BSTNode<T> *getMin(BSTNode<T> *r)
    {
        if (r->left == NULL)
        {
            return r;
        }
        else
        {
            return getMin(r->left);
        }
    }
    void remove(BSTNode<T> *&r, const T &data)
    {
        if (r == NULL)
        {
            return;
        }
        else if (data < r->data)
        {
            remove(r->left, data);
        }
        else if (data > r->data)
        {
            remove(r->right, data);
        }
        else
        {
            if (r->left != NULL && r->right != NULL) // two children
            {
                r->data = getMin(r->right)->data;
                remove(r->right, r->data);
            }
            else // 0 or 1 children
            {
                BSTNode<T> *oldNode = r;
                if (r->left != NULL)
                {
                    r = r->left;
                }

                else if (r->right != NULL)
                {
                    r = r->right;
                }
                else
                {
                    // std::cout << r->data << " HERE" << std::endl;
                    r = NULL;
                }
                delete oldNode;
            }
        }
    }
    BSTNode<T> *removeAllNodes(BSTNode<T> *r)
    {
        if (r == NULL)
        {
            return NULL;
        }
        removeAllNodes(r->left);
        removeAllNodes(r->right);
        BSTNode<T> *oldNode = r;
        delete oldNode;
        r = NULL;
        return NULL;
    }
    BSTNode<T> *searchHelper(BSTNode<T> *r, const T &data) const
    {
        if (r != NULL)
        {
            if (r->data == data)
            {
                return r;
            }
            else if (r->data > data)
            {
                return searchHelper(r->left, data);
            }
            else if (r->data < data)
            {
                return searchHelper(r->right, data);
            }
        }
        return NULL;
    }
    void getInorderSuccessor(BSTNode<T> *r, BSTNode<T> *node, BSTNode<T> &result, bool &isTraversed) const
    {
        if (r != NULL)
        {
            getInorderSuccessor(r->left, node, result, isTraversed);
            if (isTraversed && result.right == NULL)
            {
                result.right = r;
                return;
            }
            if (r == node)
            {
                isTraversed = true;
            }
            getInorderSuccessor(r->right, node, result, isTraversed);
        }
    }
    void getPreorderSuccessor(BSTNode<T> *r, BSTNode<T> *node, BSTNode<T> &result, bool &isTraversed) const
    {
        if (r != NULL)
        {
            if (isTraversed && result.right == NULL)
            {
                result.right = r;
                return;
            }
            if (r == node)
            {
                isTraversed = true;
            }
            getPreorderSuccessor(r->left, node, result, isTraversed);
            getPreorderSuccessor(r->right, node, result, isTraversed);
        }
    }
    void getPostorderSuccessor(BSTNode<T> *r, BSTNode<T> *node, BSTNode<T> &result, bool &isTraversed) const
    {
        if (r != NULL)
        {
            getPostorderSuccessor(r->left, node, result, isTraversed);
            getPostorderSuccessor(r->right, node, result, isTraversed);
            if (isTraversed && result.right == NULL)
            {
                result.right = r;
                return;
            }
            if (r == node)
            {
                isTraversed = true;
            }
        }
    }
    void assignmentHelper(BSTNode<T> *curr)
    {
        if (curr == NULL)
        {
            return;
        }
        this->insert(curr->data);
        assignmentHelper(curr->left);
        assignmentHelper(curr->right);
    }

private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif // BST_H

template <class T>
BST<T>::BST()
{
    /* TODO */
    root = NULL;
}

template <class T>
BST<T>::BST(const BST<T> &obj)
{
    /* TODO */
    this->root = copy_construct_helper(obj.root);
}

template <class T>
BST<T>::~BST()
{
    /* TODO */
    root = removeAllNodes(root);
}

template <class T>
BSTNode<T> *BST<T>::getRoot() const
{
    /* TODO */
    return root;
}

template <class T>
bool BST<T>::isEmpty() const
{
    /* TODO */
    return root == NULL;
}

template <class T>
bool BST<T>::contains(BSTNode<T> *node) const
{
    /* TODO */
    return containsHelper(root, node);
}

template <class T>
void BST<T>::insert(const T &data)
{
    /* TODO */
    root = insertHelper(root, data);
    // if (root)
    //     std::cout << root->data << std::endl;
}

template <class T>
void BST<T>::remove(const T &data)
{
    /* TODO */
    if (root == NULL)
    {
        return;
    }
    remove(root, data);
    // return;
}

template <class T>
void BST<T>::removeAllNodes()
{
    /* TODO */
    root = removeAllNodes(root);
}

template <class T>
BSTNode<T> *BST<T>::search(const T &data) const
{
    /* TODO */
    if (root == NULL)
    {
        return NULL;
    }
    return searchHelper(root, data);
}

template <class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const
{
    if (root == NULL)
    {
        return NULL;
    }
    if (search(node->data) == NULL)
    {
        return NULL;
    }
    if (node == root && !root->left && !root->right)
        return NULL;

    if (tp == inorder)
    {
        /* TODO */
        BSTNode<T> inorderResult;
        bool isTraversed = false;
        getInorderSuccessor(root, node, inorderResult, isTraversed);
        return inorderResult.right;
    }
    else if (tp == preorder)
    {
        /* TODO */
        if (node->left)
        {
            return node->left;
        }
        else if (node->right)
        {
            return node->right;
        }
        else
        {
            BSTNode<T> preorderResult;
            bool isTraversed = false;
            getPreorderSuccessor(root, node, preorderResult, isTraversed);
            return preorderResult.right;
        }
    }
    else if (tp == postorder)
    {
        /* TODO */
        if (node == root)
        {
            return NULL;
        }
        else
        {
            BSTNode<T> postorderResult;
            bool isTraversed = false;
            getPostorderSuccessor(root, node, postorderResult, isTraversed);
            return postorderResult.right;
        }
    }
    return NULL;
}

template <class T>
void BST<T>::print(TraversalPlan tp) const
{

    if (tp == inorder)
    {
        // check if the tree is empty?
        if (isEmpty())
        {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl
                  << "}" << std::endl;
    }
    else if (tp == preorder)
    {
        /* TODO */
        if (isEmpty())
        {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl
                  << "}" << std::endl;
    }
    else if (tp == postorder)
    {
        /* TODO */
        if (isEmpty())
        {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl
                  << "}" << std::endl;
    }
}

template <class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs)
{
    /* TODO */
    if (rhs.root == NULL)
    {
        this->root = NULL;
    }
    else
    {
        this->removeAllNodes();
        BSTNode<T> *curr = rhs.root;
        assignmentHelper(curr);
    }
    return *this;
}

template <class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const
{

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder)
    {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left)
        {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right)
        {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    }
    else if (tp == preorder)
    {
        /* TODO */
        std::cout << "\t" << node->data;
        if (node->left)
        {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
        if (node->right)
        {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
    }
    else if (tp == postorder)
    {
        /* TODO */
        print(node->left, postorder);
        if (node->left)
        {
            std::cout << "," << std::endl;
        }

        print(node->right, postorder);
        if (node->right)
        {
            std::cout << "," << std::endl;
        }
        std::cout << "\t" << node->data;
    }
}
