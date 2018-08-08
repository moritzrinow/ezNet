// This code is mostly inspired by https://github.com/etodd/lasercrabs

#pragma once

#include "Common/Public/Types.h"
#include "Common/Public/Defines.h"
#include "Common/Public/Assert.h"

EZNET_BEGIN

/*
* Array with a fixed size(capacity).
*/
template <typename T, uint32 size>
struct TArray {

  TArray()
    : u_bytes(), m_length(0)
  {
  }

  TArray(int32 length)
    : u_bytes(), m_length(length)
  {
  }

  int32 Capacity() const
  {
    return size;
  }

  int32 Length() const
  {
    return m_length;
  }

  const TArray& operator =(const TArray* other)
  {
    Memcpy(u_bytes, other->u_bytes, sizeof(u_bytes));
    m_length = other->m_length;
    return *this;
  }

  TArray(const TArray& other)
    : m_length(other.m_length)
  {
    Memcpy(u_bytes, other.u_bytes, sizeof(u_bytes));
  }

  inline void Resize(int32 length)
  {
    assert(length <= size);
    m_length = length;
  }

  inline const T& operator [](int32 index) const
  {
    assert(index >= 0 && index < m_length);
    return u_data[index];
  }

  inline T& operator [](int32 index)
  {
    assert(index >= 0 && index < m_length);
    return u_data[index];
  }

  void Remove(int32 index)
  {
    assert(index >= 0 && index < m_length);
    if (index != m_length - 1) {
      u_data[index] = u_data[m_length - 1];
    }
    m_length--;
  }

  void RemoveOrdered(int32 index)
  {
    assert(index >= 0 && index <= m_length);
    Memmove(&u_data[index], &u_data[index + 1], sizeof(T) * (m_length - (index + 1)));
    m_length--;
  }

  T* Insert(int32 index)
  {
    assert(index >= 0 && index <= m_length);
    assert(m_length + 1 <= size);
    Memmove(&u_data[index], &u_data[index], sizeof(T) * (m_length - index));
    m_length++;
    return &u_data[index];
  }

  T* Insert(int32 index, const T& value)
  {
    T* ptr = Insert(index);
    *ptr = value;
    return ptr;
  }

  T* Add()
  {
    assert(m_length + 1 <= size);
    m_length++;
    return &u_data[m_length - 1];
  }

  T* Add(const T& value)
  {
    T* ptr = Add();
    *ptr = value;
    return ptr;
  }

  T* GetArray()
  {
    return m_data;
  }

private:

  union {

    char u_bytes[size * sizeof(T)];
    T u_data[size];
  };

  uint32 m_length;
};

#define ARRAY_GROWTH_FACTOR 1.5
#define ARRAY_INITIAL_RESERVATION 1

/*
* Array with a dynamic size.
* The memory is always allocated on the heap.
*/
template <typename T>
struct TDynArray {

  TDynArray(int32 reserve = 0, int32 length = 0)
    : m_reserved(0), m_length(length)
  {
    assert(reserve >= 0 && m_length >= 0 && m_length <= reserve);
    if (reserve > 0) {
      Reserve(reserve);
    }
    else {
      m_data = nullptr;
    }
  }

  TDynArray(T* array, int32 length)
    : m_data(array), m_length(length), m_reserved(length)
  {
  }

  ~TDynArray()
  {
    if (m_data) {
      Free(m_data);
    }
  }

  inline const T& operator [](int32 index) const
  {
    assert(index >= 0 && index < m_length);
    return *(m_data + index);
  }

  inline T& operator [](int32 index)
  {
    assert(index >= 0 && index < m_length);
    return *(m_data + index);
  }

  void Reserve(int32 size)
  {
    assert(size >= 0);
    if (size <= m_reserved) { // No need to reserve memory.
      return;
    }

    int32 nextSize = scast<uint32>(pow(ARRAY_GROWTH_FACTOR, scast<int32>(log(size) / log(ARRAY_GROWTH_FACTOR)) + 1));
    if (!m_reserved) {
      nextSize = nextSize > ARRAY_INITIAL_RESERVATION ? nextSize : ARRAY_INITIAL_RESERVATION;
      m_data = scast<T*>(Calloc(nextSize, sizeof(T)));
      assert(m_data);
    }
    else {
      m_data = scast<T*>(Realloc(m_data, nextSize * sizeof(T)));
      assert(m_data);
      Memset((void*)&m_data[m_reserved], 0, (nextSize - m_reserved) * sizeof(T));
    }

    m_reserved = nextSize;
  }

  void Resize(int32 size)
  {
    Reserve(size);
    m_length = size;
  }

  void Remove(int32 index)
  {
    assert(index >= 0 && index < m_length);
    if (index != m_length - 1) {
      m_data[index] = m_data[m_length - 1];
    }
    m_length--;
  }

  void RemoveOrdered(int32 index)
  {
    assert(index >= 0 && index < m_length);
    Memmove(&m_data[index], &m_data[index + 1], sizeof(T) * (m_length - (index + 1)));
    m_length++;
  }

  T* Insert(int32 index)
  {
    assert(index >= 0 && index <= m_length);
    Resize(m_length + 1);
    Memmove(&m_data[index + 1], &m_data[index], sizeof(T) * (m_length - index - 1));
    return &m_data[index];
  }

  T* Insert(int32 index, const T& value)
  {
    T* ptr = Insert(index);
    *ptr = value;
    return ptr;
  }

  T* Add()
  {
    Reserve(++m_length);
    return &m_data[m_length - 1];
  }

  T* Add(const T& value)
  {
    T* ptr = Add();
    *ptr = value;
    return ptr;
  }

  int32 Length()
  {
    return m_length;
  }

  int32 Capacity()
  {
    return m_reserved;
  }

  T* GetArray()
  {
    return m_data;
  }

private:

  T* m_data;
  int32 m_length;
  int32 m_reserved;
};

EZNET_END