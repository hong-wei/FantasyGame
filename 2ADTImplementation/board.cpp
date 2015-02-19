// board.h: interface for the board class.
//
// 
//
// author:	Jian Gao
// date:	15.11.2013
//////////////////////////////////////////////

#include <iostream>
#include <exception>
#include <string.h>
#include <cstdlib>
#include "board.h"

using namespace std;

//static double a=10;
//////////////////////////////////////////////////////////////////
// Construction
/////////////////////////// constructor
// board()
// constructor to create the default vector.
//
// parameter:	none
// return : the default: vector(0)
//////////////////////////////////////////////////////////////////////
board::board()
{
  // set size to newsize and allocate memory
  x = 0;
  y = 0;
  try {
        CurrentState = new unsigned int*[x];
    } catch (bad_alloc &ex) {
        // report error to cerr and rethrow exception
        cerr << "Error when allocation memory in constructor"
             << "board() \n";
        throw ex;
	}
}
/////////////////////////////////////////////////////////////////
// generic constructor
// board(int newsize,double element[])
//
// constructor to create vector  with size newsize  and newelement
// if memory cannot be allocated, exception is thrown
//
// parameter:	newsize - size of vector
//              newelement - the content of the vector
//////////////////////////////////////////////////////////////////////
board::board(unsigned int NewX,unsigned int NewY)
    : x(NewX), y(NewY), CurrentState(NULL)
{
    try {
        // allocate memory for row pointer (double pointer)
        CurrentState = new unsigned int*[x];

        for (unsigned i = 0; i < x; i++)
            // NULL all pointer to support failure detection
            CurrentState[i] = NULL;

        // allocate memory for each column
        for (unsigned int i = 0; i < x; i++) {
            CurrentState[i] = new  unsigned int[y];
        }
    } catch (bad_alloc ex) {
        // clean up
        // test for allocated columns
        for (unsigned int i = 0; i < x; i++) {
            if (CurrentState[i] != NULL)
                delete CurrentState[i];
            else
                break;
        }
        if (CurrentState != NULL) delete[] CurrentState;

        throw "allocation failure in board  constructor";

    }
}


//////////////////////////////////////////////////////////////////////
// copy constructor
// copy constructor to create copy of dynamic array with its own
// memory. if memory cannot be allocated, exception is thrown
// parameter:	orig - reference to original 
//////////////////////////////////////////////////////////////////////

board::board(board &orig){
    
    try {
        unsigned int i, j;
        x = orig.x;
        y = orig.y;

        // allocate memory for row pointer (double pointer)
        CurrentState = new  unsigned int*[x];
        for (i = 0; i < x; i++)
            // NULL all pointer to support failure detection
            CurrentState[i] = NULL;

        // allocate memory for each column
        for (i = 0; i < x; i++)
            CurrentState[i] = new  unsigned int[y];

        // copy all elements from orig to new object
        for (i = 0; i < x; i++)
            for (j = 0; j < y; j++)
                *(CurrentState+ i)[j] = *(orig.CurrentState + i)[j];

    } catch (bad_alloc ex) {
        // clean up
        // test for allocated columns
        for (unsigned int i = 0; i < x; i++) {
            if (CurrentState[i] != NULL) delete CurrentState[i];
            else break;
        }
        if (CurrentState != NULL) delete[] CurrentState;

        throw "allocation failure in board copy constructor";

    }

}    
  

/////////////////////////////////////////////////////////////////////
// destructor
// ~vector()
// destructor for class - frees up dynamically allocated
// memory
//
// parameter:	none
//////////////////////////////////////////////////////////////////////
board::~board()
{
    unsigned int i;
    // deallocation is reverse order as allocation
    // first deallocate y
    for (i = 0; i < x; i++)
        delete[] CurrentState[i];
    // now deallocate rows
    delete[] CurrentState;
}



//////////////////////////////////////////////////////////////////////
// member method definition
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// accessElem(index)
// provides access (both reading and writing) to elements of the
// vector. if index is out of range (index<0 || index >=size)
// index is set to nearest value (0/size-1)
// 
// parameter:	index - index of element to be accessed
//////////////////////////////////////////////////////////////////////
// double &vector::accessElem(int index) 
// {
//   if (index < 0 || index >=size) {
//     // throw exception
//       throw runtime_error( "index out of range in accessElement(index)");
//   }
//   // return reference to allow read/write access
//   return element[index]; // return *(data + index);
// }

//////////////////////////////////////////////////////////////////////
// operator=(cinst vector &orig)
// assignment operator requried as dynamic memory is used
//
// parameter: orig - const reference to original matrix
// return: reference to lhs operand
//////////////////////////////////////////////////////////////////////
board &board::operator=(const board &orig) {
    try {
        unsigned int i, j;
        // always check for assignment to self
        if (this == &orig);
        else {
            // check for equal sizes
            if (x != orig.x || y != orig.y) {

                // deallocate memory, columns first
                for (i = 0; i < x; i++)
                    delete[] CurrentState[i];
                // now deallocate rows
                delete[] CurrentState;
                CurrentState = NULL;

                // align number of rows, columns
                x  = orig.x;
                y  = orig.y;

                // now allocate new memory
                CurrentState = new unsigned int*[x];
                for (i = 0; i < x; i++)
                    // NULL all pointer to support failure detection
                    CurrentState[i] = NULL;

                // allocate memory for each column
                for (i = 0; i < x; i++) {
                    CurrentState[i] = new unsigned int[y];
                }
            }
            // copy over elements
            for (i = 0; i < x; i++)
                for (j = 0; j < y; j++)
                    *(CurrentState + i)[j] = *(orig.CurrentState + i)[j];
        }

    } catch (bad_alloc ex) {
        // clean up
        // test for allocated columns
        for (unsigned int i = 0; i < x; i++) {
            if (CurrentState[i] != NULL) delete CurrentState[i];
            else break;
        }
        if (CurrentState != NULL) delete CurrentState;

        throw "allocation failure in board assignment";
    }

    return *this;
}


//initiallization the board
void board::BoardInitialization() {
    unsigned int RandNumbers;
    for (unsigned int i = 0; i < x; i++)
        for (unsigned int j = 0; j < y; j++){
            RandNumbers  = rand() % 15  + 1;
            //  *(CurrentState + i)[j] = RandNumbers;
            CurrentState[i][j] = RandNumbers;
        }
    //start from the [0][0]
    x = 0;
    y = 0;           
}

