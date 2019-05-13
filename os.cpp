#include <iostream>
#include "os.h"
using namespace std;

//Dynmically allocates Mlist for the root data as well as pushes the newly created data objmect pointer to wd and dataStack from the top
OS::OS(){
    root_data = new Data;
    root_data->isFolder = true;
    root_data->name = "root";
    MList* direc = new MList();
    root_data->childList = direc;
    wd.push_top(root_data);
    dataStack.push_top(root_data);
}

//Destructor aka cleans up the memoryyyyy
OS::~OS(){

    while (!dataStack.isEmpty()){

        Data* temp = dataStack.top()->nodeData;
        if(temp->childList != NULL){
            delete temp->childList;
        }
        delete temp;
        dataStack.pop_top();
    }
}

//searches if a node is in the current directory
//if so, return a pointer to that node else returns NULL
Node* OS::search_item(string fname){
   return wd.top()->nodeData->childList->search(wd.top()->nodeData->childList->top(),fname);
}

//Deletes a node in the current directory
void OS::del(string fname){
    Node* temp = search_item(fname);
    if(temp!=NULL){
        wd.top()->nodeData->childList->deleteNode(temp);
    }
    else{
        cout<<"Error: cannot find file or directory '"<<fname<<"'"<<endl;
    }
}

//creates a file or a folder
void OS::create_item(string fname, bool isFolder){
    if(search_item(fname)==NULL){
        Data* newItem = new Data(); //zero initialize = all fields to zero
        newItem->isFolder = isFolder;
        newItem->name = fname;
        //check if folder, if it is, create a list of children for it
        if(isFolder){
            MList* direc = new MList();
            newItem->childList = direc;
        }
        dataStack.push_top(newItem);
        wd.top()->nodeData->childList->push_bottom(newItem);
        wd.top()->nodeData->childList->sortByNameSelection();
    }
    else{
        cout<<"Directory or file name '"<<fname<<"' already exists"<<endl;
    }
}

//Reads or writes a file according 
void OS::file(string fname, bool isRead){
    Node* temp = search_item(fname);
    if(temp != NULL){
        //if it is not a folder
        if(!temp->nodeData->isFolder){
            if(isRead){
                cout<<temp->nodeData->text<<endl;
            }
            else{
                cout<<"$> ";
                string command;
                getline(cin,command);
                temp->nodeData->text = command;
                temp->nodeData->size = command.length();
            }
        }
        else{
            cout<<"Error: '"<<fname<<"'"<<endl;
        }
    }
    else{
        cout<<"Error: cannot find file '"<<fname<<"'"<<endl;
    }
}

//Change directory
void OS::cd_dir(string fname){
    if(fname == ".."){
        //this option takes you up one directory (move the directory back one directory)
        if(wd.top()->next != NULL){
            wd.pop_top();
        }
    }else if(fname == "~"){
        //this option takes you directly to the home directory aka the root
        while(wd.top()->next != NULL){
            wd.pop_top();
        }

    }else{
        Node* temp = search_item(fname);
        if(temp != NULL){
            if(temp->nodeData->isFolder){
                wd.push_top(temp->nodeData);
            }
            else{
                cout<<"Error: '"<<fname<<"' is not a directory"<<endl;
            }
        }
        else{
            cout<<"Error: cannot find directory '"<<fname<<"'"<<endl;
        }
    }
}

//Print list of item in the current directory
void OS::ls(string option){
    if(option == "-d"){
        //The default option - print the list of items in the current directory from top to bottom.
        wd.top()->nodeData->childList->printTtB(" ");
    }
    else if(option == "-sort=name"){
        //Uses InsertionSosrt() to sort items in the current director and print from the top to the bottom aka alphabetically.
        wd.top()->nodeData->childList->sortByNameInsertion();
        wd.top()->nodeData->childList->printTtB(" ");


    }else if(option == "-r"){
        //Reverses the and printslist of items in the current directory
        wd.top()->nodeData->childList->printBtT(" ");


    }else if(option == "-sort=size"){
        //Sorts the list by size and print the list of items in the current directory from top to bottom.
        wd.top()->nodeData->childList->sortBySizeSelection();
        wd.top()->nodeData->childList->printTtB(" ");

    }
    else{
        cout<<"usage: ls [optional: -r for reverse list, -sort=size to sort list by file size, -sort=name to soft list by name]";
    }
}

//Priting path from root to your current directory.
void OS::present_working_dir(){
    wd.printBtT("/");
}