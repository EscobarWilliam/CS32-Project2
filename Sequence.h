//
//  Sequence.h
//  CS32_Final_Project
//
//  Created by William  Escobar on 9/5/22.
//  Copyright © 2022 William  Escobar. All rights reserved.
//

#ifndef Sequence_h
#define Sequence_h
#include <string>

using ItemType = std::string;
//using ItemType = unsigned long;

class Sequence//this class is basically the LinkedList class
{
    public:
        //Default constructor
        Sequence();
        //Copy Constructor
        Sequence (const Sequence& other);
        //operator overload function
        Sequence& operator=(const Sequence& other);
        //destructor
        ~Sequence();
    
        //ACCESSORS
        bool empty() const;
        int size() const;
        bool get(int pos, ItemType& value) const;
        int find(const ItemType& value) const;
        void dump();
    
        //MUTATORS
        int insert(int pos, const ItemType& value);
        int insert(const ItemType& value);
        bool erase(int pos);
        int remove(const ItemType& value);
        bool set(int pos, const ItemType& value);
        void swap(Sequence& other);
        
    
    private:
    
    //because we don't want any other function to create a node besides
    //the sequence itself, we MUST define the structure within the private
    //section of the Sequence class
    struct Node//Declaration of our Node structure
    {
        //for doubly-linked list we need both a prev and next pointers
        ItemType value;
        Node *prev;
        Node *next;
    };
    
    Node *head;
    Node *tail;//we may or may not use this
    int m_size;
    
};

//other algorithm functions
int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);
//I need to implement another function and omit the interleave function
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result);
#endif /* Sequence_h */
