//============================================================================
// Name        : Project 2 Main
// Author      : Parker Harb
// Version     : 1.0
// Description : Project 2 for cs300
//============================================================================

#include <iostream>
#include <time.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class Course{//course class to hold content
    public:
        Course();//constructor
        string name;
        string id;
        vector<string> prereq;

};

Course::Course(){//left empty
    
}

struct Node {
    Course course;//basic node structure for tree
    Node *left;
    Node *right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Course course) :
    Node() {
        course = course;
    }
};




class BinarySearchTree {//Basic binary search tree

private:
    Node* root;

    void addNode(Node* node, Course course);//can only add
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Course course);
    Course Search(string id);
};


BinarySearchTree::BinarySearchTree() {
    root = nullptr;///init root to nullptr
}


BinarySearchTree::~BinarySearchTree() {//deconstructor
    delete root;
}


void BinarySearchTree::InOrder() {
   
    if (root == nullptr) {
      return;
    }
    inOrder(root);///will output all in order

}


void BinarySearchTree::PostOrder() {

    if(root == nullptr){
        return;
    }

    postOrder(root->left);
    postOrder(root->right);
 
}


void BinarySearchTree::PreOrder() {

    if(root == nullptr){
        return;
    }

    preOrder(root->left);
    preOrder(root->right);
}


void BinarySearchTree::Insert(Course course) {

    if(root == nullptr){
            root = new Node;//attempts to fill root if empty
            root-> course = course;
            root->left = nullptr;
            root->right = nullptr;
    }
    else{
        addNode(root, course);//otherwise adds course in place
    }
}
Course BinarySearchTree::Search(string id) {

    Node* node = root;
    while(node != nullptr){///goes down tree until it finds node
        if(id == node->course.id){
            return node->course;
        }
        else if(id < node->course.id){
            node = node->left;
        }
        else{
            node = node->right;
        }
    }

    Course course;//if no node found outputs empty course


    return course;
}


void BinarySearchTree::addNode(Node* node, Course course) {

    if(node->course.id > course.id ){///figures out what side to add the node
        if(node->left == nullptr){
            node->left = new Node;
            node->left-> course = course;
            node->left->left = nullptr;
            node->left->right = nullptr;
        }
        else{
            addNode((node->left), course);
        }
    }
    else{
        if(node->right == nullptr){
            node->right = new Node;
            node->right-> course = course;
            node->right->left = nullptr;
            node->right->right = nullptr;
        }
        else{
            addNode((node->right), course);
        }
    }
}
void BinarySearchTree::inOrder(Node* node) {

    if (node == nullptr) {
      return;
    }
    inOrder(node->left);
    cout << "Course ID: " << node->course.id << " - Course Name: " << node->course.name << " - Course PreReqs: ";
    for(int i = 0; i < node->course.prereq.size(); i++){
        cout << node->course.prereq[i] << ", ";
    }
    cout << endl;
    inOrder(node->right);
}
void BinarySearchTree::postOrder(Node* node) {

    if(node == nullptr){
        return;
    }

    postOrder(node->left);
 
    postOrder(node->right);
    cout << "Course ID: " << node->course.id << " - Course Name: " << node->course.name << " - Course PreReqs: ";
    for(int i = 0; i < node->course.prereq.size(); i++){
        cout << node->course.prereq[i] << ", ";
    }
    cout << endl;
}

void BinarySearchTree::preOrder(Node* node) {

    if(node == nullptr){
        return;
    }

    cout << "Course ID: " << node->course.id << " - Course Name: " << node->course.name << " - Course PreReqs: ";
    for(int i = 0; i < node->course.prereq.size(); i++){
        cout << node->course.prereq[i] << ", ";
    }
    cout << endl;
    postOrder(node->left);
 
    postOrder(node->right);
}


void loadFile(BinarySearchTree* bst){
    string line;
    ifstream myfile ("input.txt");///init ifstream object
    vector<string> lines;///init placeholder vector
    string state = "id"; 
    string temp = "";// init placeholder strings
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )//while there is content in buffer, add to placeholder vector of strings
        {
            lines.push_back(line);
        }
        myfile.close();//close ifstream object when done
    }
    else cout << "Unable to open file"; ///if file not found
    for(int i = 0; i < lines.size(); i++){/// go through entire vector
        Course course; 
        state = "id";
        temp = "";//reinit placeholder variables
        for(int j = 0; j < lines[i].size(); j++){//go character by character across string vector
            if(lines[i].at(j) == ','){//on comma, change state of object mutator
                if(state == "id"){
                    state = "name";
                    course.id = temp;
                    temp = "";
                }
                else if(state == "name"){
                    state = "prereq";
                    course.name = temp;
                    temp = "";
                }
                else{
                    course.prereq.push_back(temp);//n number of pre reqs, until line is ended
                    temp = "";
                }
            }
            else{
                temp += lines[i].at(j);//add to temp
            }
        }
        if(state == "id"){///extra , needed to add final temp variables before reinit. Maybe better way to do this, but this is a highy intuitive solution.
            state = "name";
            course.id = temp;
            temp = "";
        }
        else if(state == "name"){
            state = "prereq";
            course.name = temp;
            temp = "";
        }
        else{
            course.prereq.push_back(temp);
            temp = "";
        }
        bst->Insert(course);
    }
    return;
}

void displayCourse(Course course){
    cout << "Course ID: " << course.id << " - Course Name: " << course.name << " - Course PreReqs: ";
    for(int i = 0; i < course.prereq.size(); i++){//output all prereqs, even if n
        cout << course.prereq[i] << ", ";
    }
    cout << endl;
}



int main() {

    BinarySearchTree* bst;
    bst = new BinarySearchTree();

    int answer;
    string key = "CSCI300";/// id to search for
    while(answer != 9){
        cout << "COURSE SYSTEM ACCESS - PLEASE CHOOSE AN ACTION-" << endl;///Menu using if statements
        cout << "1. Load Data" << endl;
        cout << "2. Output all courses" << endl;
        cout << "3. Search Course" << endl;
        cout << "9. Exit" << endl;//breaks out of loop
        cin >> answer;
        if(answer == 1){
            loadFile(bst);
        }
        else if(answer == 2){
            bst->InOrder();
        }
        else if(answer == 3){
            displayCourse(bst->Search(key));
        }
    }
    return 0;
}
