//======== Copyright (c) 2020, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Slavomir Svorada <xsvora02@stud.fit.vutbr.cz>
// $Date:       $2020-03-03
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Slavomir Svorada
 *
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
  head = NULL;
}

PriorityQueue::~PriorityQueue()
{
  Element_t *value = GetHead();
  while (value != NULL)
  {
    Element_t *current;
    current = value;
    free(current);
    value = value->pNext;
  }
}

void PriorityQueue::Insert(int value)
{
  Element_t *NewValue;
  NewValue = (Element_t*)malloc(sizeof(Element_t));
  Element_t *MyValue = GetHead();
  while (MyValue != NULL)
  {
    if ((MyValue->value <= value) && (MyValue->pNext == NULL) && (MyValue->pPrev == NULL))
    {
      NewValue->value = value;
      NewValue->pNext = NULL;
      MyValue->pNext = NewValue;
      NewValue->pPrev = MyValue;
      return;
    }
    else if ((MyValue->value > value) && (MyValue->pPrev == NULL))
    {
      head = NewValue;
      NewValue->value = value;
      NewValue->pPrev = NULL;
      NewValue->pNext = MyValue;
      MyValue->pPrev = NewValue;
      return;
    }
    else if ((MyValue->value > value) && (MyValue->pNext == NULL) && (MyValue->pPrev != NULL))
    {
      NewValue->pPrev = MyValue->pPrev;
      NewValue->pNext = MyValue;
      NewValue->value = value;
      MyValue->pPrev->pNext = NewValue;
      MyValue->pPrev = NewValue;
      return;
    }
    else if ((MyValue->value <= value) && (MyValue->pNext == NULL) && (MyValue->pPrev != NULL))
    {
      NewValue->value = value;
      NewValue->pPrev = MyValue;
      NewValue->pNext = NULL;
      MyValue->pNext = NewValue;
      return;
    }
    else if ((MyValue->value >= value) && (MyValue->pPrev->value <= value))
    {
      NewValue->value = value;
      MyValue->pPrev->pNext = NewValue;
      NewValue->pPrev = MyValue->pPrev;
      NewValue->pNext = MyValue;
      MyValue->pPrev = NewValue;
      return;
    }
    MyValue = MyValue->pNext;
  }

  NewValue->value = value;
  NewValue->pNext = NULL;
  NewValue->pPrev = NULL;
  head = NewValue;
}

bool PriorityQueue::Remove(int value)
{
  Element_t *NewValue;
  Element_t *MyValue;
  NewValue = GetHead();
  while (NewValue != NULL)
  {
    if (NewValue->value == value)
    {
      if ((NewValue->pPrev == NULL) && (NewValue->pNext != NULL))
      {
        NewValue->pNext->pPrev = NULL;
        head = NewValue->pNext;
        free(NewValue);
        return true;
      }
      else if ((NewValue->pPrev != NULL) && (NewValue->pNext == NULL))
      {
        NewValue->pPrev->pNext = NULL;
        free(NewValue);
        return true;
      }
      else if ((NewValue->pPrev != NULL) && (NewValue->pNext != NULL))
      {
        NewValue->pPrev->pNext = NewValue->pNext;
        NewValue->pNext->pPrev = NewValue->pPrev;
        free(NewValue);
        return true;
      }
      else
      {
      head = NULL;
      return true;
      }
      free(NewValue);
      return true;
    }
    NewValue = NewValue->pNext;
  }
    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
  Element_t *NewValue;
  NewValue = GetHead();

  while (NewValue != NULL)
  {
    if (NewValue->value == value)
    {
      return NewValue;
    }
    NewValue = NewValue->pNext;
  }
    return NULL;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return head;
}


/*** Konec souboru tdd_code.cpp ***/
