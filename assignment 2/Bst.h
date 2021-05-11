#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include <iostream>

using namespace std;
/**
* @struct nodeType
* template node for bst
*/
template <class T>
struct nodeType
{
    T data;
    nodeType<T> * LeftLink;
    nodeType<T> * RightLink;
};

/**
 * @class Bst
 * @brief Bst for int values
 * Binary search tree for integers
 *
 * @author Seow Wei Cheng
 * @version 01
 * @date 12/3/2021
 *
 * @version 02
 * @date 12/4/2021
 * added copy function, copy constructor and operator = overload
 */
template <class T>
class Bst
{
public:
    /**
    * Default constructor
    */
    Bst();
    /**
    *
    *copy constructor
    */
    Bst(const Bst<T>& otherTree);
    /**
    * destructor
    */
    ~Bst();
    /**
    * @brief check if bst is empty
    *
    * Check if Bst is empty
    * @return bool
    */
    bool isEmpty() const;
    /**
    * @brief insert function
    *
    * insert an element into the Bst
    *
    * @param T insertItem
    * @return void
    */
    void Insert(T insertItem);
    /**
    * @brief Destroy function
    *
    * Delete the whole Bst
    *
    * @param nodeType<T>* &p
    * @return void
    */
    void Destroy(nodeType<T>* &p);
    /**
    * @brief delete whole tree
    *
    * Function that calls Destroy and deletes the whole tree
    *
    * @return void
    */
    void DeleteTree();
    /**
    * @brief search function
    *
    * Search the whole tree for the input element
    *
    * @param T insertItem
    * @return bool
    */
    bool Search(T searchItem);
    /**
    * @brief in order traversal
    *
    * Function that does in order traversal in the Bst
    * using function point
    *
    * @param void(*visit) (T& item)
    * @return void
    */
    void inOrderTraversal(void(*visit) (T& item)) const;
    /**
    * @brief pre order traversal
    *
    * Function that does pre order traversal in the Bst
    * using function point
    *
    * @param void(*visit) (T& item)
    * @return void
    */
    void preOrderTraversal(void(*visit) (T& item)) const;
    /**
    * @brief post order traversal
    *
    * Function that does post order traversal in the Bst
    * using function point
    *
    * @param void(*visit) (T& item)
    * @return void
    */
    void postOrderTraversal(void(*visit) (T& item)) const;
    /**
    * @brief delete node from tree using a pointer
    *
    * Function that does deletes a node from the tree using a pointer
    *
    * @param nodeType<T>* &p
    * @return void
    */
    void deleteFromTree(nodeType<T>* &p);
    /**
    * @brief delete node from tree
    *
    * Function that does deletes a node from the tree using a key item
    *
    * @param T&
    * @return void
    */
    void deleteNode(const T& deleteItem);
    /**
    * @brief copy tree
    *
    * Function that does copy a tree, node by node
    *
    * @param nodetype *
    * @return void
    */
    void copyTree(nodeType<T>* &copiedTreeRoot, nodeType<T>* otherTreeRoot);
    /**
    * @brief copy tree
    *
    * overloaded = operator
    *
    * @param bst<T> &
    * @return bst<T> &
    */
    const Bst<T>& operator = (const Bst<T>& otherTree);
private:
    ///Contains the root node of the tree
    nodeType<T>* root;
    /**
    * @brief in order traversal algorithm
    *
    * algorithm that does in order traversal in the Bst
    * using function point
    *
    * @param nodeType<T> *p, void(*visit) (T& item)
    * @return void
    */
    void inOrder(nodeType<T> *p, void(*visit) (T& item)) const;
    /**
    * @brief pre order traversal algorithm
    *
    * algorithm that does pre order traversal in the Bst
    * using function point
    *
    * @param nodeType<T> *p, void(*visit) (T& item)
    * @return void
    */
    void preOrder(nodeType<T> *p, void(*visit) (T& item)) const;
    /**
    * @brief post order traversal algorithm
    *
    * algorithm that does post order traversal in the Bst
    * using function point
    *
    * @param nodeType<T> *p, void(*visit) (T& item)
    * @return void
    */
    void postOrder(nodeType<T> *p, void(*visit) (T& item)) const;
};

template <class T>
Bst<T>::Bst()
{
    root = nullptr;
}
template <class T>
Bst<T>::Bst(const Bst<T>& otherTree)
{
    if(otherTree.root == nullptr)
    {
        root = nullptr;
    }
    else
    {
        copyTree(root,otherTree.root);
    }
}
template <class T>
Bst<T>::~Bst()
{
    Destroy(root);
}

template <class T>
bool Bst<T>::isEmpty() const
{
    return (root == nullptr);
}

template <class T>
void Bst<T>::Insert(T insertItem)
{
    nodeType<T>* NewNode = new nodeType<T>;
    nodeType<T>* trailCurrent = nullptr;
    nodeType<T>* current;

    NewNode->data = insertItem;
    NewNode->LeftLink = NULL;
    NewNode->RightLink = NULL;
    if(root == NULL)
    {
        root = NewNode;
        //cout << NewNode->data << " Inserted" << endl;
    }
    else
    {
        current = root;

        while(current != nullptr)
        {
            trailCurrent = current;
            if(insertItem == current->data)
            {
                //cout << "item already inserted, No duplicates allowed." << endl;
                return;
            }
            else if(insertItem > current->data)
            {
                current = current->RightLink;
            }
            else
            {
                current = current->LeftLink;
            }
        }//endwhile

        if(insertItem > trailCurrent->data)
        {
            trailCurrent->RightLink = NewNode;
            //cout << NewNode->data << " Inserted" << endl;
        }
        else
        {
            trailCurrent->LeftLink = NewNode;
            //cout << NewNode->data << " Inserted" << endl;
        }
    }
}
//Delete tree function
template <class T>
void Bst<T>::Destroy(nodeType<T> * &p)
{
    if(p != NULL)
    {
        Destroy(p->LeftLink);
        Destroy(p->RightLink);
        delete p;
        p = NULL;
    }
}

template <class T>
void Bst<T>::DeleteTree()
{
    Destroy(root);
}

template <class T>
bool Bst<T>::Search(T searchItem)
{
    nodeType<T>* current;
    bool found = false;
    if(root == nullptr)
    {
        cout << "cannot search in an empty tree" << endl;
    }
    else
    {
        current = root;
        while(current != nullptr && !found)
        {
            if(current->data == searchItem)
            {
                found = true;
            }
            else if(current->data > searchItem)
            {
                current = current->LeftLink;
            }
            else
                current = current->RightLink;
        }
    }
    return found;
}

//in order
template <class T>
void Bst<T>::inOrderTraversal(void(*visit) (T& item)) const
{
    inOrder(root, *visit);
}

template <class T>
void Bst<T>::inOrder(nodeType<T> *p, void(*visit) (T& item)) const
{
    if(p != nullptr)
    {
        inOrder(p->LeftLink, *visit);
        (*visit)(p->data);
        inOrder(p->RightLink, *visit);
    }
}
//pre Order
template <class T>
void Bst<T>::preOrderTraversal(void(*visit) (T& item)) const
{
    preOrder(root, *visit);
}

template <class T>
void Bst<T>::preOrder(nodeType<T> *p, void(*visit) (T& item)) const
{
    if(p != nullptr)
    {
        (*visit) (p->data);
        preOrder(p->LeftLink, *visit);
        preOrder(p->RightLink, *visit);
    }
}
//post order
template <class T>
void Bst<T>::postOrderTraversal(void(*visit) (T& item)) const
{
    postOrder(root, *visit);
}

template <class T>
void Bst<T>::postOrder(nodeType<T> *p,void (*visit) (T& item)) const
{
    if(p != nullptr)
    {
        postOrder(p->LeftLink, *visit);
        postOrder(p->RightLink, *visit);
        (*visit) (p->data);
    }
}

template <class T>
void Bst<T>::deleteFromTree(nodeType<T>* &p)
{
    nodeType<T> *current; //pointer to traverse the tree
    nodeType<T> *trailCurrent; //pointer behind current
    nodeType<T> *temp; //pointer to delete node

    if(p == nullptr)
    {
        cout << "Error: The node to be deleted does not exist.\n";
    }
    else if (p->LeftLink == nullptr && p->RightLink == nullptr)
    {
        temp = p;
        p = nullptr;
        delete temp;
    }
    else if(p->LeftLink == nullptr)
    {
        temp = p;
        p = temp->RightLink;
        delete temp;
    }
    else if(p->RightLink == nullptr)
    {
        temp = p;
        p = temp->LeftLink;
        delete temp;
    }
    else
    {
        current = p->LeftLink;
        trailCurrent = nullptr;

        while(current->RightLink != nullptr)
        {
            trailCurrent = current;
            current = current->RightLink;
        }
        p->data = current->data;

        if(trailCurrent == nullptr)
        {
            p->LeftLink = current->LeftLink;
        }
        else
        {
            trailCurrent->RightLink = current->LeftLink;
        }
        delete current;
    }
}

template <class T>
void Bst<T>::deleteNode (const T& deleteItem)
{
    nodeType<T> *current; //pointer to traverse the tree
    nodeType<T> *trailCurrent; //pointer behind current
    bool found = false;
    if (root == nullptr)
    {
        cout << "Cannot delete from an empty tree.\n";
    }
    else
    {
        current = root;
        trailCurrent = root;
        while (current != nullptr && !found)
        {
            if (current->data == deleteItem)
                found = true;
            else
            {
                trailCurrent = current;
                if (current->data > deleteItem)
                    current = current->LeftLink;
                else
                    current = current->RightLink;
            }
        }
        if (current == nullptr)
        {
            cout << "The item to be deleted is not in the tree.\n";
        }
        else if (found)
        {
            if (current == root)
            {
                deleteFromTree(root);
            }
            else if (trailCurrent->data > deleteItem)
            {
                deleteFromTree(trailCurrent->LeftLink);
            }
            else
                deleteFromTree(trailCurrent->RightLink);
        }
        else
            cout << "The item to be deleted is not in the tree.\n";
        }
}

template <class T>
void Bst<T>::copyTree(nodeType<T>* &copiedTreeRoot, nodeType<T>* otherTreeRoot)
{
    if(otherTreeRoot == nullptr)
    {
        copiedTreeRoot == nullptr;
    }
    else
    {
        copiedTreeRoot = new nodeType<T>;
        copiedTreeRoot->data = otherTreeRoot->data;
        copyTree(copiedTreeRoot->LeftLink, otherTreeRoot->LeftLink);
        copyTree(copiedTreeRoot->RightLink, copiedTreeRoot->RightLink);
    }
}

template <class T>
const Bst<T>& Bst<T>::operator = (const Bst<T>& otherTree)
{
    if(this != &otherTree)
    {
        if(root != nullptr)
        {
            destroy(root);
        }
        if(otherTree.root == nullptr)
        {
            root = nullptr;
        }
        else
        {
            copyTree(root,otherTree.root);
        }
    }
    return *this;
}
#endif // BST_H_INCLUDED
