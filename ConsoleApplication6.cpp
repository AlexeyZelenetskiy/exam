// ConsoleApplication6.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <algorithm>
#include <vector>
#include "locale.h"

using namespace std;

template<class T>
class Iterator;
 
template<class T>
class array
{
public:
   typedef Iterator<T> iterator;
   typedef size_t size_type;
   typedef T* pointer;
   typedef const T* const_pointer;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T value_type;
   
   array():arr_(new T[0]), sz_(0)
   {
   }
   array(size_t sz):sz_(sz), arr_(new T[sz])
   {
      std::fill(arr_, arr_ + sz_, T());
   }
   array(const array& arr)
   {
      delete arr_;
      sz_ = arr.sz;
      arr_ = new T[sz_];
      std::copy(arr.arr_, arr.arr_ + sz_, arr_);
   }
   array& operator =(const array& arr)
   {
      array tmp(arr);
      swap(tmp);
      return *this;
   }
   ~array()
   {
      delete[] arr_;
   }
   Iterator<T> begin()
   {
      return Iterator<T>(arr_);
   }
   Iterator<T> end()
   {
      return Iterator<T>(arr_ + sz_);
   }
   T& operator [](size_t idx)
   {
      return arr_[idx];
   }
   const T& operator [](size_t idx) const
   {
      return arr_[idx];
   }
   size_t size() const
   {
      return sz_;
   }
  
   void insert(T x, size_t index)
   {
	   arr_[index] = x;
   }
private:
   void swap(array& first, array& second)
   {
      std::swap(first.arr_, second.arr_);
      std::swap(first.sz_, second.sz_);
   }
   T* arr_;
   size_t sz_;
};
 
template<class T>
class Iterator
{
public:
   typedef T value_type;
   typedef T* pointer;
   typedef T& reference;
   typedef std::forward_iterator_tag iterator_category;
   typedef ptrdiff_t difference_type;
   
   Iterator(T* curr):current(curr)
   {
   }
   Iterator& operator =(const Iterator& other)
   {
       if (this != &other)
       {
           current = other.current;
       }
       return *this;
   }
   Iterator& operator ++()
   {
       ++current;
       return *this;
   }
   Iterator operator ++(int i)
   {
       Iterator tmp(current);
       ++current;
       return tmp;
   }
   T& operator *()
   {
      return *current;
   }
   T* operator ->()
   {
      return current;
   }
   bool operator ==(const Iterator& other)
   {
      return current == other.current;
   }
   bool operator !=(const Iterator& other)
   {
      return !(*this == other);
   }
private:
   T* current;
};
template<class T>
ostream & operator<<(ostream & stream , array<T> & obj)
{
	for(size_t i(0); i < obj.size() ; i++)
		stream << obj[i] << " ";
	return stream;
}

template<class T>
istream & operator>>(istream & stream , array<T> & obj)
{
	T x;
	for(size_t i(0); i < obj.size(); i++)
	{
		stream >> x;
		obj.insert( x , i );
	}

	return stream;

}

template<class T>
class Funktor
{
public:
	void operator()(T & x)
	{
		x*=x;
	}
};


void func(int & x)
{
	x = 0;
}

int main()
{
   array<int> arr(5);
   Funktor<int> f;

   int mass[] = {1,2,3,4,5};
   void (*pf)(int &) = &func;

   /*cin >> arr;
   cout << arr << endl;*/

   Iterator<int> i1(mass);
   Iterator<int> i2(mass);
   for(int i(0); i < 3; i++)
	   i2++;
   for_each(i1, i2 , pf);

   for(int i(0) ; i < 5 ; i++)
	   cout << mass[i] << " " ;

   system("pause");
   return 0;
}


