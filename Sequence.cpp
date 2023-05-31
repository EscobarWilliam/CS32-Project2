//
//  Sequence.cpp
//  CS32_Final_Project
//
//  Created by William  Escobar on 9/5/22.
//  Copyright © 2022 William  Escobar. All rights reserved.
//

#include <iostream>
#include "Sequence.h"

//***************************************************************
//                       Constructor
//  The constructor begins the doubley-linked list and needs to
//  initialize the head pointer to 'nullptr', prev to 'head'
//  (since no other nodes exist), and m_size to zero.
//***************************************************************
Sequence::Sequence()
{
    head = new Node;
    tail =  new Node;
    head->next = tail;// head
    head->prev = nullptr;
    tail->prev = head;
    tail->next = nullptr;//tail
    m_size = 0;
}
//***************************************************************
//                          Destructor
//***************************************************************
Sequence::~Sequence()
{
    Node* p = head;//start at the dummy node
    
    while(p!=nullptr)
    {
        Node* n = p->next;
        delete p;
        p = n;
    }
}
//***************************************************************
//                      Copy constructor
//***************************************************************
Sequence::Sequence(const Sequence& other)
{
    if(this != &other)//meaning that we aren't setting it equal to itself
    {
        //initial setup for 'this' sequence
        head = new Node;
        tail = new Node;
        head->next = tail;
        head->prev = nullptr;
        tail->prev = head;
        tail->next = nullptr;
        this->m_size = 0;
        
        int counter = 0;//starting at the first node of the "other" list
        for(Node* temp = other.head->next; temp != other.tail; temp = temp->next)
        {
            this->insert(counter, temp->value);
            counter++;
        }
    }
}
//***************************************************************
//              Overloaded assignment operator
//***************************************************************
Sequence& Sequence::operator= (const Sequence& other)
{
    if(this == &other)//check for aliasing
        return *this; //do nothing
    
    //code to delete the list if already has items
    if(m_size > 0)
    {
        Node* p = head->next;//start at the top of list
        for(int i=0; i<m_size && p!=tail; i++)
        {
            Node* n = p->next;
            delete p;
            p = n;
        }
            
        //code to reset to an empty list
        head->next = tail;
        tail->prev = head;
        m_size = 0;
    }
    
    Node* otherNode = other.head->next;//remember the head is a dummy node
                
    Node* track = head; //used to track the previously copied node
    for(int i=0; i<other.m_size && otherNode->next != tail; i++)
    {
        Node *copyNode = new Node;
        copyNode->value = otherNode->value;
        copyNode->next = tail;
        tail->prev = copyNode;
        copyNode->prev = track;
        track->next = copyNode; //old last node points to new last node
        m_size++;
        //code to get ready for next iteration
        otherNode = otherNode->next;
        track = track->next;
    }
    return *this;
}
//***************************************************************
//                  bool Sequence::empty() const

//      is a function that checks if the Sequence (A.K.A
//      Linked-List) is empty true if empty . . . false if not
//***************************************************************
bool Sequence::empty() const
{
    return (m_size == 0);//returns true if m_size equals zero
}
//***************************************************************
//              int Sequence::size() const
//
//      is a function that counts the number of items in the
//      sequence and returns the integer number
//***************************************************************
int Sequence::size() const
{
    return m_size; //returns the size of the sequence
}
//***************************************************************
//         int Sequence::insert(int pos, const ItemType& value)

//      is a function that adds an element to the sequence as
//      long as the position(integer) that is passed to the
//      function is a position in the list. If the integer passed
//      is above or below the bounds of the Linked-List, then
//      the function will return -1. If the item can be placed,
//      then the function returns the position integer
//
//      three cases: pos int can be > length of list(EXCEED)
//                   pos int can be < lenght of list(UNDERFLOW)
//                   pos int can be within the list(VALID)
//***************************************************************
int Sequence::insert(int pos, const ItemType& value)
{
   if(pos>size() || pos<0) //VERIFY POS IS VALID
   {
       return -1;
   }
    
   else if(pos == size())//CASE#1 ADD NODE TO END OF LIST OR IF LIST
                        //IS EMPTY AND WE WANT TO INSERT FIRST NODE
    {
        Node* oldEndNode;//temp pointer used to traverse linked-list
        oldEndNode = tail->prev;
        
        Node* newEndNode = new Node;
        newEndNode->value = value;
        newEndNode->prev = oldEndNode;
        newEndNode->next = tail;
        oldEndNode->next = newEndNode;
        tail->prev = newEndNode;
                              
        
        m_size++; //remember to increase the size of the linked list
        return pos;
    }
    
    else//CASE#2 ADD SOMEWHERE IN THE MIDDLE
    {
        Node* m = head->next;//the head is a dummy node so the first node
                            //is actually what the head node 'next' is
        
    //Traverse the list until we reach the position we want
        //No need to check if m->next != tail since it never will.
        //We already had a case to take care of when we wanted to add
        //a node the the end
        for(int i = 0; i<pos; m = m->next)
        {
            i++;
        }
    //We should be at the position we want to add the node.
        //Need to relink the surrounding nodes
        
        //NEW MIDDLE NODE LINKING
        Node *newMiddleNode = new Node;
        newMiddleNode->value = value;
        newMiddleNode->next = m;
        newMiddleNode->prev = m->prev;
        
        //LINKING THE OTHER TWO NODES TO NEW NODE
        m->prev = newMiddleNode;
        newMiddleNode->prev->next = newMiddleNode;
        
        m_size++; //NODE ADDED SO INCREMENT SIZE
        return pos;
    }
}

//***************************************************************
//            int Sequence::insert(const ItemType& value)
//
//  This function needs to determine where to add the item in
//  the sequence dependent on 'value'. Once the position is found
//  it sends the position and value to the 1st insert() function
//  to add the node.
//***************************************************************

int Sequence::insert(const ItemType& value)
{
    int p;// holds the position of where to add Node
    
    if(head->next == tail) //if list is empty we add Node at pos = 0
    {
        p=0;
        insert(p, value);
        return p;
    }
     
    else //list isn't empty and need determine where to insert node
    {

        Node* temp = head->next;//start at first non-dummy node in list
        p = 0; //we are starting at first item in list
        while(temp != tail && value >= temp->value)
        {
            
            //case when value is greater than all values in list
            if(temp == tail)
            {
                //then we enter the item at the end of the list
                insert(m_size, value);
                return (m_size-1);//we subtract one because the list grew
                                //when we added th node
            }
            
            temp = temp->next;
            p++;
               
        }
       
        insert(p, value);
        return p;
     }
}
//***************************************************************
//              bool Sequence::erase(int pos)

//      Takes in an argument which is an integer that is for the
//      position of an item in the linked-list. If the position
//      exists, delete it and return true. Else, return false.
//      Make sure that all other items in the list are adjusted
//      to reflect the new order.
//***************************************************************
bool Sequence::erase(int pos)
{
    //VALIDATE 'pos'
    if(pos < 0 || pos >size())
        return false;
           
    else if(pos == size())//Removing node at the end
    {
        Node* m = tail->prev;//temp node used to traverse linked-list
        
        tail->prev = m->prev;
        tail->prev->next = tail;
        delete m;
        m_size--; //Decrease the size of linked list
        return true;
    }
    
    else //this handles the case of removing the node from the middle
    {
        Node* m = head->next;
        for(int i=0; m->next != tail && i<pos; i++ )
        {
            m = m->next;
        }
        //after the for-loop, we should be at the position we want to delete the node
        Node* temp = m->prev;
        temp->next = m->next;
        m->next->prev = temp;
        delete m;
        
        m_size--;
        return true;
        
    }
}
//***************************************************************
//           int Sequence::remove(const str& value)
//
//      removes any items from the sequence that have a value
//      which is equal to 'value'. The function should return the
//      number of items that were removed.(returns 0 if none exist)
//***************************************************************
int Sequence::remove(const ItemType& value)
{
    if(empty())//true if empty false otherwise
    {
        return 0;
    }
    else
    {
        int p; //variable to hold the found node
        int counter = 0; //variable to hold the number of deletes
        
        p = find(value);
        while(p!=-1) //when p=-1 it means that the value couldn't be found
        {
            erase(p);
            counter++;
            p = find(value);
        }
        return counter;
    }
              
}
//***************************************************************
//          bool Sequence::get(int pos, ItemType& value)

//      If 0 <= pos < size(), copy into value the item at
//      position pos of the sequence and return true. Otherwise,
//      leave value unchanged and return false.
//
//***************************************************************
bool Sequence::get(int pos, ItemType& value) const
{
    if(pos >= m_size || pos < 0)
        return false;
    
    Node* temp = head->next; //start at first node
    int p = 0; //we are starting at first item in list
    while(temp != tail && p < pos)
    {
        temp = temp->next;
        p++;
    }
    value = temp->value;
    return true;
    
}
//***************************************************************
//          bool Sequence::set(int pos, const str& value)

//      If 0 <= pos < size(), replace the item at position pos
//      in the sequence with value and return true. Otherwise,
//      leave the sequence unchanged and return false.
//***************************************************************
bool Sequence::set(int pos, const ItemType& value)
{
    if(pos >= m_size || pos < 0)
        return false;
 
    Node* temp = head->next; //start at the first item in the list
    int p = 0;//we are starting at the first item in list
            
    while(temp != tail && p < pos)
    {
        temp = temp->next;
        p++;
    }
    temp->value = value;
    return true;
}
//***************************************************************
//          int Sequence::find(const ItemType& value) const

//      Let p be the smallest integer such that value == the
//      item at position p in the sequence; if no such item
//      exists, let p be -1. Return p.
//***************************************************************
int Sequence::find(const ItemType& value) const
{
    if(empty())//i.e the list is empty
        return -1;
        
    Node* temp = head->next; //start at the first item in the list
    int p = 0; //we are starting at first item in list
    
    while(temp != tail && temp->value != value)
    {
        temp = temp->next;
        p++;
    }
        
    if(temp == tail)//if true, we didnt find a node with 'value'
        return -1;

    return p;
}
//***************************************************************
//           void Sequence::swap(Sequence& other)

//     Exchange the contents of this sequence with the other one.
//     The easiest way to do this is to just swap the head
//     Pointers of each sequence. This way we don't have to
//     Copy, delete, or allocate new memory.
//***************************************************************
void Sequence::swap(Sequence& other)
{
    //create a temp variable to hold the addresses of one sequence
    Node* temp = other.head;
    
    //now swap the head and tail pointers
    other.head = this->head;
    this->head = temp;
    
    temp = other.tail;
    other.tail =  this->tail;
    this->tail = temp;
}

//*********************NON CLASS MEMBER FUNCTIONS******************
//***************************************************************
//      int subsequence(const Sequence&, const Sequence&)

//  will take in two sequences(linked-lists) and check to see
//  if seq2 is a subsequence of sequence1. Meaning that seq1 has
//  seq2 within it. Once this is determined, the function returns
//  the position in seq1 where seq2 starts.
//***************************************************************
int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    //before we do anything, make sure sequences are not empty
    if(seq2.size() > seq1.size() || seq1.empty() || seq2.empty())
        return -1;
    
    ItemType val1;
    ItemType val2;
    int r = 0, start = 0, stop = 0;
    
    for(int i =0; i<seq2.size(); i++)
    {
        for( ; r<seq1.size(); r++)
        {
            seq1.get(r, val1);
            seq2.get(i,val2);
            
            if(val2 == val1)
            {
                //"stop" keeps track of the last position
                //where the two sequences were still equal
                stop = r;
                r++;
                break;
            }
            else
                start = r;
            //start keeps track of the last place where the
            //sequences were not equal
        }
    }

    //if stop is greater than start, then there was a consecutive
    //mutual sequence. Only if the length of the subsequence is the
    //same as sequence2, then seq2 is a subsequence
    if(stop > start && (stop-start) == seq2.size())
    {
        //we increment "start" because start kept track of the last place
        //where the sequences were not equal. So, if we increment once,
        //we get the place where the sequences began to be equal
        start ++;
        return start;
    }
    
    return -1;
}

//***************************************************************
//  void interleave(const Sequence&, const Sequence&, Sequence&)
//  is a function that takes in three sequences(linked-lists).
//  The function will take the items in sequcne1 & 2 and copy
//  their items into the third sequence. It starts with the
//  1st item in sequence1 and then the 1st item in sequnence2
//  and continues to do so in an alternating fashion. The
//  function will then return this third sequnce.
//***************************************************************
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    ItemType val1;
    ItemType val2;
    int pos;
    
    if(seq1.size() > seq2.size())
    {
        for(pos = 0; pos < seq2.size(); pos++)
        {
            seq1.get(pos, val1);
            result.insert((2*pos), val1);
            
            seq2.get(pos, val2);
            result.insert((2*pos + 1), val2);
            
        }
        
        while(pos < seq1.size())
        {
            seq1.get(pos, val1);
            result.insert(result.size(), val1);
            pos++;
        }
    }
    else
    {
        for(pos = 0; pos < seq1.size(); pos++)
        {
           seq1.get(pos, val1);
            result.insert((2*pos), val1);
            
            seq2.get(pos, val2);
            result.insert((2*pos+ 1), val2);
        }
        
        while(pos < seq2.size())
        {
            seq2.get(pos, val2);
            result.insert(result.size(), val2);
            pos++;
        }
    }
}
//***********************************************************
//      void concatReverse()
//  recieves the address of two sequences. The function then
//  places the values of seq1 into the result sequence in
//  reverse order then places seq2 values in reverse order.
//***********************************************************
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    ItemType value;
    int pos = (seq1.size() - 1);//i.e. we start from last node
   
    
    while(seq1.get(pos, value))
    {
        result.insert(result.size(), value);
        pos--;
        
    }
    
    pos = (seq2.size() - 1);
    while(seq2.get(pos, value))
    {
        result.insert(result.size(), value);
        pos--;
    }
    
}
//***************************************************************
//       dump() is just a function for test purposes which
//      outputs the data values present in the sequence
//***************************************************************
void Sequence::dump()
{
    Node* m = this->head->next;
    
    while(m != tail)
    {
       std::cerr << m->value << std::endl;
        m = m->next;
    }
    
}
