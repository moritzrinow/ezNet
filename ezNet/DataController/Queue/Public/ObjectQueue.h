// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#include <mutex>
#include "Data/Container/Public/TArray.h"

EZNET_BEGIN

template <typename T, uint32 maxSize>
class ObjectQueue;

/*
* Wrapper around a static array, to add and receive objects from multiple threads.
* Typical usecase is: one thread adds objects, another threads fetches them.
*/
template <typename T, uint32 maxSize>
class ObjectQueue {

public:

  ObjectQueue(std::mutex* arrayLock)
    : m_array(), m_mutex(arrayLock), m_stopQueue(false)
  {
  }

  ~ObjectQueue()
  {
  }

  /*
  * Enqueues an element.
  * This method is blocking until the queue has room for another object.
  */
  bool Add(T inObject)
  {
    while (true) { // Wait till the queue has room
      if (m_stopQueue) {
        return false;
      }

      if (m_array.Length() < maxSize) {
        break;
      }
    }

    m_mutex->lock();
    m_array.Add(inObject);
    m_mutex->unlock();
    return true;
  }

  /*
  * Fetches the next element from the queue.
  * This method is blocking until there is lined up object.
  */
  bool Next(T* outObject)
  {
    while (true) {
      if (m_stopQueue) {
        return false;
      }

      if (m_array.Length() == 0) {
        continue;
      }

      m_mutex->lock();
      *outObject = m_array[m_array.Length() - 1];
      m_array.Remove(m_array.Length() -1);
      m_mutex->unlock();
      break;
    }

    return true;
  }

  /*
  * Interrupts the queue, which leads into Next() and Add() always returning false instantly.
  * Usecase: This method can be called from a control thread to terminate threads, that are
  * currently blocked by Add() or Next().
  */
  void StopQueue()
  {
    m_stopQueue = true;
  }

  /*
  * Unpauses the queue, which leads into Next() and Add() working as usual again.
  */
  void StartQueue()
  {
    m_stopQueue = false;
  }

  /*
  * The amount of objects lined up in the queue.
  */
  int32 Length()
  {
    return m_array.Length();
  }

protected:

  bool m_stopQueue;
  std::mutex* m_mutex; // The mutex we lock when we modify the underlying array
  TArray<T, maxSize> m_array; // The underlying array
};

EZNET_END