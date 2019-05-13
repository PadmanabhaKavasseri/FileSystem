#include <iostream>
#include "mlist.h"
using namespace std;

//Constructor, construct an empty doubly linked list.
MList::MList(){
    ntop=NULL;
    nbottom=NULL;
}

//Destructor, properly clears and deallocates everything of current list.
MList::~MList(){
    clear();
}

//this function properly clears and deallocates everything of current list.k
void MList::clear(){
    if(ntop==NULL){
        return;
    }
    Node* hold = ntop->next;
    deleteNode(ntop);
    ntop=hold;
    clear();
}

//returns a boolean true if the list is empty, false if otherwise.
bool MList::isEmpty(){
    if((ntop == NULL) && (nbottom == NULL)){
        return true;
    }
    else{
        return false;
    }
}
	
//Add or insert a new node with d_item as its data at the top of the list
void MList::push_top(Data* d_item){
    Node* new_node = new Node;
    new_node->nodeData = d_item;
    new_node->prev= NULL;
    new_node->next = ntop;

    if(isEmpty()) {
        new_node->next = NULL;
        ntop=new_node;
        nbottom=new_node;
        return;
    }
    ntop->prev = new_node;
    ntop = new_node;
}

//Add or insert a new node with d_item as its data at the bottom of the list.
void MList::push_bottom(Data* d_item){
    Node* new_node = new Node;
    new_node->nodeData = d_item;
    new_node->next = NULL;
    //if list is empty
    if(ntop == NULL){
        new_node->prev=NULL;
        ntop=new_node;
        nbottom=new_node;
        return;
    }
    nbottom->next=new_node;
    new_node->prev = nbottom;
    nbottom=new_node;
}

//Delete or remove the top node of the list.
void MList::pop_top(){
    if(isEmpty()){
        return;
    }
    else if(ntop==nbottom){
        delete ntop;
        ntop=NULL;
        nbottom=NULL;

    }
    else {
        Node *temp = ntop;
        ntop = ntop->next;
        ntop->prev = NULL;
        delete temp;
    }
}

//Delete or remove the bottom node of the list. 
void MList::pop_bottom(){
    if(isEmpty()){
        return;
    }
    else if(ntop==nbottom){
        delete nbottom;
        ntop=NULL;
        nbottom=NULL;
    }
    else {

        Node *temp = nbottom;

        nbottom = nbottom->prev;
        if (nbottom == NULL) {
            //cout << "tail is null" << endl;
        }
        nbottom->next = NULL;

        delete temp;
    }
}

//	Search a node in the list that has data with the same name as the parameter.
//	If one is found, return the pointer to the node.
//	If one is not found, return NULL.
Node* MList::search(Node* start, string name){
    //for loop through start, if you encounter a folder, recursively search on that folder.
    if(start==NULL){
        return NULL;
    }
    if(start->nodeData->name == name) {
        return start;
    }
    return search(start->next,name);
}


//Swapping node a with node b.
void MList::swapNode(Node* a, Node*b){
    //if they are the same do nothing
    if(a==b) {
        return;
    }
    //if a is left beightbos of b
    else if(a->next == b){
        removeNode(a);
        insertAfter(a,b);
    }

    //if b is left neighbors of a
    else if(b->next == a){
        removeNode(b);
        insertAfter(b,a);
    }
    //anywehre else
    else{
        Node* aplc = a->prev;
        Node* bplc = b->prev;
        removeNode(a);
        removeNode(b);
        insertAfter(a,bplc);
        insertAfter(b,aplc);
    }
}

//Permanently deletes a node from the list given a pointer to that node.
void MList::deleteNode(Node* a){

// delete the memory
    removeNode(a);
    delete a;


}

//Doesn't delete the node but just removes it from the list. 
void MList::removeNode(Node* a){

    //if there is only one element in the list
    if((a->next == NULL) && (a->prev == NULL) ){
        ntop = NULL;
        nbottom = NULL;
    }


        //if a is the head
    else if(a->prev == NULL) {
        a->next->prev = NULL;
        ntop = a->next;
    }
        //if a is the tail
    else if(a->next == NULL) {
        a->prev->next = NULL;
        nbottom = a->prev;
    }
    //update the list
    else {
       // if (a->next != NULL) {
            a->next->prev = a->prev;

        //if (a->prev != NULL) {
            a->prev->next = a->next;

    }
        a->prev = NULL;
        a->next = NULL;

}

//Inserts node a after node b.
void MList::insertAfter(Node *a, Node* b){
    if (b==NULL){
        if(isEmpty()){
            a->prev = NULL;
            a->next = NULL;
            ntop = a;
            nbottom = a;
        }

        else {
            a->prev=NULL;
            a->next = ntop;
            ntop->prev=a;
            ntop = a;
        }
    }
    //if b is at the end of the list.
    else if(b == nbottom){
        b->next = a;
        a->next = NULL;
        a->prev = b;
        nbottom = a;
    }
    else {
        a->next = b->next;
        a->next->prev = a;
        b->next = a;
        a->prev = b;
        
    }


}

//Implements a selection sort algorithm using recursion
void MList::sortSelection(Node* start, bool mode) {
    if (isEmpty()) {
        return;
    }
    if (start == NULL){
        return;
    }
    Node* head = start;
    Node* min = start;
    Node* advnc = start->next;
    while(advnc!=NULL){
        if(mode){
            if( min->nodeData->name > advnc->nodeData->name) {
                min = advnc;
            }
        }
        else{
            if( min->nodeData->size > advnc->nodeData->size) {
                min = advnc;
            }
        }
        advnc = advnc->next;
        
    }
    
    swapNode(start,min);
    if(min->next != NULL){
        sortSelection(min->next,mode);
    }
}

//Implements insertion sort algorithm using recursion. 
void MList::sortInsertion(Node* start){
    if (isEmpty()) {
        return;
    }
    if (start == NULL){
        return;
    }
    sortInsertion(start->next);
    Node* current = start;
    Node* rightSide = start->next;
    Node* minBefore = start->prev;
    while(rightSide != NULL && current->nodeData->name > rightSide->nodeData->name){
        minBefore = rightSide;
        rightSide = rightSide->next;

        }
    removeNode(current);
    insertAfter(current,minBefore);
}

//Traverse and print the list from node n to to the top of the list
void MList::traverseToTop(Node* n, string delim){
    if(n == NULL){
        return;
    }
    else{
        if(n->nodeData->isFolder) {
            cout << n->nodeData->name << delim;
        }
        else{
            cout << n->nodeData->name << "("<<n->nodeData->size<<")" << delim;
        }
    }
    traverseToTop(n->prev,delim);

}

//Traverse and print the list from node n to the bottom.
void MList::traverseToBottom(Node* n,string delim){
    if(n == NULL){
        return;
    }
    else{
        if(n->nodeData->isFolder) {
            cout << n->nodeData->name << delim;
        }
        else{
            cout << n->nodeData->name << "("<<n->nodeData->size<<")" << delim;
        }
    }
    traverseToBottom(n->next,delim);
}

//getting the pointer to the top node.
Node* MList::top(){
    return ntop;
}

//getting the pointer to the bottom node.
Node* MList::bottom(){
    return nbottom;
}

//call traverseToBottom to print all item in the list from bottom node to top node
//the list of items is separated by a given delimiter
void MList::printBtT(string delim){
    //create a temp pointer to hold bottom
    Node* tmp = nbottom;
    traverseToTop(tmp,delim);
}

//call traverseToBottom to print all item in the list from top node to bottom node
//the list of items is separated by a given delimiter
void MList::printTtB(string delim){
    Node* tmp = ntop;
    traverseToBottom(tmp,delim);
}

//call sortSelection function, mode = true = sort by name
//public member
void MList::sortByNameSelection(){
    bool mode = true;
    Node *tmp = ntop;
    sortSelection(tmp,mode);
}

//call sortSelection function, mode = false = sort by size
//public member
void MList::sortBySizeSelection(){
    bool mode = false;
    Node *tmp = ntop;
    sortSelection(tmp,mode);
}

//call sortInsertion function
//public member
void MList::sortByNameInsertion(){
    Node *tmp = ntop;
    sortInsertion(tmp);
}