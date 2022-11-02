
#include <iostream> // Provides cout
#include "graph.h"
#include "linkList.h"
#include <cassert> // Provides assert function
using namespace std; // Allows all standard library items to be used


//constructor for link list
linkedList::node::node(){
	val.id = 0;
	next = NULL;
} 

linkedList::node::node(vID x){
 val = x;
 next = NULL;
}

linkedList::node::node(vID x, node *p){
 val = x;
 next = p;
}

//CONSTRUCTOR 
linkedList::linkedList(){
	root = last = NULL;
	count = 0;
}

//DESTRUCTOR
linkedList::~linkedList(){
	clear(root);
}

//This method takes in value and insert at the end of the list
void linkedList::add(vID value){

	//create tempoary pointer with the value stored
	node *p;
	p = new node(value);
	
	if (root == NULL){
		root = p;
	} else {
	
			last->next = p;
		}
	//Reset the pointer of last and accumulate at count
	last = p;
	count++;	
	
}

//This method takes in value and insert at the front of the list
UINT64 linkedList::insert(vID value){

	node *p;
	p = new node(value, root);

	if (root == NULL){
		
		last = p;
	}
	
	root = p;
	count++;

	return 0;
}

//This method call private printIt starting at index 0 of root pointer.
void linkedList::printIt(){

	printIt(root, 0); //call on the private method of printIt
	cout << "Count: " << count << endl;
	
}

//This method takes in a pointer and a starting index; using a recursion algorithem, it loops through the list and print the value and index. If pointer is empty then do nothing.
void linkedList::printIt(node *p, UINT64 index){
	
	//check for p!= NULL; if it meets the condition then print the index, value and call itself for recursion
	if (p){	
		printIt(p->next, index+1); 															
		cout << "At pos = " << index << "\tvalue = " << p->val.id << endl; 
		
	}
}

//This method call private clear with a starting point at root
void linkedList::clear(){

	clear(root); //call private method clear
	
	//reset the pointer of the root and last to NULL
	root = NULL;
	last = NULL;
	count = 0;
}

//This method takes in a pointer and check if the pointer is empty or not, then use a recursion algorithem to loop through the list and delete that pointer. If pointer is empty then do nothing
void linkedList::clear(node *toClear){
	
	//Condtion pointer null or not
	while (toClear) {
	    node *del = toClear;
		toClear = toClear->next;

		delete del;
	}
}

//This method return the number of entries
UINT64 linkedList::countReturn(){
	return count;
}

//This method call the private find of a given value
UINT64 linkedList::find(vID value){
	UINT64 x = (find(value, 0, root)); //call private find()
	return x;
}

//This method takes in a given value and starting index and pointer; Check if the pointer is empty or not then use a recursion algorithem to loop through the list and return the index.
UINT64 linkedList::find(vID value, UINT64 index, node *p){
	
	//A variable that keep track of return value.
	UINT64 temp;

	if (p){
		if ((p->val.id) == value.id){
			temp = index;
		} else {
			p = p->next;
			index++;
			temp = find(value, index, p);
		}
	} else {
		temp = -1;
	}

	return temp;
}

vID linkedList::readAt(UINT64 index){
	vID rc;
	node *current = new node;
	node *previous = new node;
	current = root;
	if (index > count-1){
		rc.id= -1;
	} else {
	for (UINT64 i = 0; i < index; i++){
		previous = current;
		current = current->next;
	}
	rc = current->val;
	}
	return rc;	
}

//This method takes in an index; then check if the index is less than the number of entries.
void linkedList::deleteAt(UINT64 index){
	
	node *cur = new node;
	node *del = new node;

	if (index < count){
		if (count == 1){
			//delete the only one node inside the list
			delete root;
			root = last = NULL;
		} else if (index == 0){
			//deleting the first node on the list if the list is greater than 1
			del = root;
			root = root->next;
			delete del;
		} else {

			cur = root;
			for (int i = 0; i < index-1; i++){
				cur = cur->next;
			}
				del = cur->next;
				cur->next = del->next;
				delete del;
				if (index == count-1){
					last = cur;
				}
		}
		count--;
	}
	
}

//This delete the node at 0 index and decrement count
void linkedList::deletePop(){
	if(root){
		node *del = root;
		root = root->next;
		delete del;
		count--;
	}
	

}

//add a copy of another list at the end of the current list
void linkedList::addLinkList(linkedList *list){

	//if given list is not empty
	if (list -> root){

		//if the current list is not empty
		if(root){

			last->next = list->root;
			last = list->last;
			
		//if the current list is empty
		}else{

			root = list->root;
			last = list->last;
		}

		//update the count 
		count += list->count;

		//reset the given list
		list->root = NULL;
		list->last = NULL;
		list->count = 0;
	}
}

//replace current list with given list
void linkedList::setLinkList(linkedList *list){
	
	//clear current list
	clear();
	
	//set given list to curr list
	root = list->root;
	last = list->last;
	count = list->count;

	//reset the given list
	list->root = NULL;
	list->last = NULL;
	list->count = 0;
}