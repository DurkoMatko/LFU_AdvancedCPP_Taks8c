#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <memory>

template<typename T>
class LinkedList{

	struct Node {
        T x;
        std::shared_ptr<Node> next;
        //Node *next;
    };

	public:
		LinkedList();
		LinkedList(LinkedList<T>& list) noexcept;   //copy constructor
		~LinkedList();
		void addHead(T val);
		void addTail(T val);
		T popValue();
		void rewindToHead();
		void rewindToTail();
		bool next();
		T getValue() const;
		bool hasValue() const;
		void printAndDelete();
		void addList(LinkedList<T>& list);

		//template <typename V> static X<V> staticMember;

		//more options described in http://stackoverflow.com/questions/4660123/overloading-friend-operator-for-template-class/4661372#4661372
		//e.g inline declaration here
		//this option makes friend of whole template for << so LinkedList<double> can be printed from LinkedList<int> class
		template <typename U>
		friend std::ostream& operator<<(std::ostream& os, LinkedList<U>& list);
		LinkedList<T>& operator=(LinkedList<T>& list) noexcept;
	private:
		//Node *head;
		//Node *cur;
		std::shared_ptr<Node> head;
		std::shared_ptr<Node> cur;
};

#endif //LINKEDLIST_H