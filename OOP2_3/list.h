#pragma once
#include <memory>
#include <iostream>
#include "iterator.h"

template <class T>
class List{

    struct ListNode{
        T data;
        std::shared_ptr<ListNode> next;

        ListNode()
            :next{} , data{}{}
        explicit ListNode(const T& dat )
                :data{dat} , next{}{}

        void Print(){
            std:: cout << data << '\n';
        }

    };

public:
    using NodePtr =  std::shared_ptr<ListNode> ;
    using iterator = _iterator<ListNode> ;
    //constructors / destructors
    List() = default;
    List(size_t number , const T& value);
    ~List() = default;

    //methods
    iterator begin();//Returns an iterator addressing the first element
    iterator end();//Returns an iterator that addresses the location
    //succeeding the last element


    void clear();//Erases all the elements of a list.
    bool empty() const noexcept ;//Tests if a list is empty.

    iterator find(const T & val);//Returns an iterator to the
// first element in a list that
//match a specified value.

    void pop_front();//Deletes the element at the beginning of a list.

    void push_front( const T& val);//Adds an element to the beginning
    //of a list.
    void remove(const T& val);//Erases first element in a list that
    //match a specified value.


    int size();//Returns the number of elements in a list.

    void splice( iterator _Where, List<T>& _Right);//Removes element from //the target list and inserts it in first
// position of the argument list.
    void	print();//Dumps list into the screen
private:
    void push(NodePtr& head , const T& value);
    void swap(NodePtr& right , NodePtr& left) noexcept;
    bool isCorrectIterator(const iterator& ) noexcept ;
private:
    NodePtr head;

};
template <typename T>
List<T>::List(size_t number, const T &value)
        :head{}{
    for(size_t i = 0 ;i < number ; ++i)  push(head , value);
}
template <typename T>
void List<T>::push(List::NodePtr &head, const T &value) {
    if(head == nullptr){
        head = std::make_shared<ListNode>(value);
    } else {
        push(head->next , value);
    }
}

template <typename T>
typename List<T>::iterator List<T>::begin() {
    return iterator{head.get()};
}
template <typename T>
typename List<T>::iterator List<T>::end() {
    auto tmp = head;
    while (tmp) tmp = tmp->next;
    return iterator{tmp.get()};
}

template <typename T>
void List<T>::print() {
    for( auto it = this->begin() ; it != this->end() ; ++it){
        (*it).Print();
    }
}
template <typename T>
bool List<T>::empty() const noexcept {
    return head == nullptr;
}

template <typename T>
void List<T>::push_front(const T& val) {
    NodePtr tmp = std::make_shared<typename List<T>::ListNode>(val);
    swap(tmp->next , head);
    swap(tmp , head);
}
template <typename T>
void List<T>::swap(List::NodePtr &right, List::NodePtr &left) noexcept {
    auto tmp = std::move(right);
    right = std::move(left);
    left = std::move(tmp);
}
template <typename T>
void List<T>::pop_front() {
    if(head == nullptr){
        throw std::logic_error("List is empty");
    } else {
        head = std::move(head->next);
    }
}
template <typename T>
typename List<T>::iterator List<T>::find(const T &val) {
    for(auto it = begin() ; it != end() ; ++it){
        if((*it).data == val){
            return it;
        }
    }
    return end();
}
template <typename T>
int List<T>::size() {
    size_t size{};
    for(auto it = begin() ; it != end() ; ++it , ++size);
    return static_cast<int>(size);
}
template <typename T>
void List<T>::clear() {
    head.reset();
}
template <typename T>
void List<T>::remove(const T &val) {
    List<T> tmp;
    auto it = begin();
    for(; it != end() ; ++it){
        if( (*it).data ==val){
            ++it;
            break;
        }
        tmp.push(tmp.head , (*it).data );
    }
    for(; it != end() ; ++it){
        tmp.push(tmp.head , (*it).data );

    }
    swap(tmp.head , head);
}
template <typename T>
void List<T>::splice(typename List<T>::iterator _Where, List<T> &_Right) {
        if(!isCorrectIterator(_Where)){
            throw std::logic_error("Incorrect iterator");
        }
        List<T> tmp;
        _Right.push_front((*_Where).data);
        for(auto it = begin() ; it != end() ; ++it){
            if(it != _Where ){
                tmp.push(tmp.head , (*it).data);
            }
        }
        swap(head , tmp.head);
}
template <typename T>
bool List<T>::isCorrectIterator(const typename List<T>::iterator &tmp) noexcept {
    for(auto it = begin() ; it != end() ; ++it){
        if(tmp == it) {
            return true;
        }
    }
    return false;
}