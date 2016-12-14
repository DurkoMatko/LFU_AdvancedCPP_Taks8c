#include "LinkedList.h"
#include <cstddef>
#include <iostream>


template <typename U>
std::ostream& operator<<(std::ostream& os,LinkedList<U>& list)
{
	list.rewindToHead();

	while(list.hasValue()){
    	os << list.getValue() << std::endl;
    	list.next();
    }
    os << std::endl;
}


//copy assign operator
template<typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T>& list) noexcept{
	//if they are not the same objects		
	if(head!=list.head){
		//delete previous contents
		rewindToHead();
		/*while(hasValue()){
			popValue();
		}*/

		//prepare linkedList to be copied
		list.rewindToHead();

		//first node = head
		std::shared_ptr<Node> n(new Node());
		head = n;
		cur=head;

		//if next exists
		while(list.cur->next != nullptr){
			n->x = list.cur->x;
			//create next one
			n->next.reset(new Node());

			//move to next one
			list.cur = list.cur->next;
			n = n->next;
		}
		//next one does not exist so just finish copying this node
		n->x = list.cur->x;
		n->next == nullptr;

		list.rewindToHead();
		rewindToHead();
	}
	return *this;
}



//default constructor
template<typename T>
LinkedList<T>::LinkedList(){
	head = nullptr;
	cur = nullptr;
}


//copy constructor
template<typename T>
LinkedList<T>::LinkedList(LinkedList& list) noexcept{
	list.rewindToHead();

	if(list.head==nullptr){
		head = nullptr;
		cur = nullptr;
	}
	else{
		//first node - head
		std::shared_ptr<Node> n(new Node());
		head = n;
		cur=head;

		//if next exists
		while(list.cur->next != nullptr){
			//copy current value
			n->x = list.cur->x;
			//reset next from nullptr to new node ("create next one")
			n->next.reset(new Node());

			//move to next one
			list.cur = list.cur->next;
			n = n->next;
		}
		//next one does not exist so just finish copying current node
		n->x = list.cur->x;
		n->next = nullptr;
	}
	list.rewindToHead();
}


// append a new value at the beginning of the list
template<typename T>
void LinkedList<T>::addHead(T val){
	//create new node
    std::shared_ptr<Node> n(new Node());
    n->x = val;             
    n->next = head;         
         
    //set head to new node                   
    head = n;   
    cur = head;
}


template<typename T>
void LinkedList<T>::addTail(T val){
	
	//if not empty
	if(hasValue())
		//make cursor point to tail of list
		rewindToTail();

	//create node for value
	std::shared_ptr<Node> n(new Node()); 
    n->x = val;
    n->next = nullptr;

    //check if not empty list
    if(hasValue()){
	    //add to tail
	    cur->next = n;
	}
	else{
		//if empty, create first node
		head = n;
		cur = head;
	}
}



template<typename T>
bool LinkedList<T>::hasValue() const{
	return ( cur != nullptr ? true : false );
}

template<typename T>
T LinkedList<T>::getValue() const{
	if(cur!=nullptr){
		return cur->x;
	}
	return 0;   //should be exception
}

template<typename T>
bool LinkedList<T>::next(){
	if(cur!=nullptr){
		cur = cur->next;
		return true;
	}
	return false;
}


template<typename T>
void LinkedList<T>::rewindToTail(){
	//just loop till not at the tail
	while(cur->next != nullptr){
		cur = cur->next;
	}
}


template<typename T>
void LinkedList<T>::rewindToHead(){
	cur = head;
}


// returns the first element in the list and deletes the Node.
template<typename T>
T LinkedList<T>::popValue(){
    T ret = head->x;

    //set head and cur to next node - so previous head deallocated
    head = head->next;
    cur=head;

    return ret;
}


template<typename T>
void LinkedList<T>::printAndDelete(){
	rewindToHead();
    while(hasValue()){
    	std::cout << popValue() << std::endl;	
    }
}




template<typename T>
LinkedList<T>::~LinkedList(){

}



template<typename T>
void LinkedList<T>::addList(LinkedList<T>& list){
	list.rewindToHead();
	while(list.hasValue()){
		addTail(list.popValue());
	}
}
