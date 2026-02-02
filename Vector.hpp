#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <initializer_list>
using namespace std;

template <typename T>
class Vector
{
    int SIZE;
    int CAP;
    T *arr;

public:
    Vector(int s = 0, T val = 0)
    {
        if (s < 0)
        {
            throw runtime_error("Size cannot be Negative\n");
        }

        if (s == 0)
        {
            SIZE = 0;
            CAP = 1;
        }
        else
        {
            SIZE = s;
            CAP = s;
        }
        arr = new T[CAP];
        for (int i = 0; i < SIZE; i++)
        {
            arr[i] = val;
        }
    }

    Vector(initializer_list<T> list)
    {
        SIZE = list.size();

        if (SIZE > 0)
        {
            CAP = SIZE;
        }
        else
        {
            CAP = 1;
        }
        arr = new T[CAP];

        int i = 0;
        for (const T &item : list)
        {
            arr[i] = item;
            i++;
        }
    }

    int size() const
    {
        return SIZE;
    }
    int capacity() const
    {
        return CAP;
    }
    void resize(int r)
    {
        if (r < 0)
        {
            throw out_of_range("Size cannot be negative\n");
        }

        if (r <= SIZE)
        {
            SIZE = r;
        }
        else if (r <= CAP)
        {
            int old_s = SIZE;
            SIZE = r;
            for (int i = old_s; i < SIZE; i++)
            {
                arr[i] = 0;
            }
        }
        else // r > CAP
        {
            int old_s = SIZE;
            reserve(r);
            CAP = r;
            SIZE = r;
            for (int i = old_s; i < SIZE; i++)
            {
                arr[i] = 0;
            }
        }
    }
    void reserve(int r)
    {
        if (r <= CAP)
        {
            return;
        }
        T *temp = new T[r];
        for (int i = 0; i < SIZE; i++)
        {
            temp[i] = move(arr[i]);
        }
        delete[] arr;
        arr = temp;
        CAP = r;
    }

    void push_back(T val)
    {
        if (SIZE == CAP)
        {
            reserve(CAP * 2);
        }
        arr[SIZE] = val;
        SIZE++;
    }
    void pop_back()
    {
        if (SIZE <= 0)
        {
            throw out_of_range("Vector Empty\n");
        }
        arr[SIZE - 1] = 0;
        SIZE--;
    }

    void shrinktofit()
    {
        if (SIZE == CAP)
        {
            return;
        }

        if (SIZE == 0)
        {
            delete[] arr;
            CAP = 1;
            arr = new T[CAP];
            arr[0] = 0;
            return;
        }
        T *temp = new T[SIZE];
        for (int i = 0; i < SIZE; i++)
        {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
        CAP = SIZE;
    }
    void clear()
    {
        SIZE = 0;
    }

    // We need to have both functions for at() and [] , const and non-const
    // const allows the binding of const vector reference
    // non-const allows that we can change the vector's value by at() or []
    T &at(int x)
    {
        if (x < 0 || x >= SIZE)
            throw out_of_range("...");
        return arr[x];
    }

    const T &at(int x) const
    {
        if (x < 0 || x >= SIZE)
        {
            throw out_of_range("Out of Range (Not Possible)\n");
        }
        return arr[x];
    }

    T &operator[](int x)
    {
        return arr[x];
    }

    const T &operator[](T x) const
    {
        return arr[x];
    }
    const T &front() const
    {
        if (SIZE <= 0)
        {
            throw out_of_range("Vector is empty already\n");
        }
        return arr[0];
    }
    const T &back() const
    {
        return arr[SIZE - 1];
    }

    Vector(const Vector &other)
    {
        SIZE = other.SIZE;
        CAP = other.CAP;
        arr = new T[CAP];
        for (int i = 0; i < SIZE; i++)
        {
            arr[i] = other.arr[i];
        }
    }

    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            delete[] arr;
            SIZE = other.SIZE;
            CAP = other.CAP;
            arr = new T[CAP];
            for (int i = 0; i < SIZE; i++)
            {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    Vector(Vector &&other) noexcept
    {
        SIZE = other.SIZE;
        CAP = other.CAP;
        arr = other.arr;

        other.arr = nullptr;
        other.SIZE = 0;
        other.CAP = 0;
    }

    Vector &operator=(Vector &&other) noexcept
    {
        if (this != &other)
        {
            delete[] arr;

            SIZE = other.SIZE;
            CAP = other.CAP;
            arr = other.arr;

            other.arr = nullptr;
            other.SIZE = 0;
            other.CAP = 0;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Vector &other)
    {
        // Can use vector's display() function as well
        for (int i = 0; i < other.SIZE; i++)
        {
            out << other.arr[i] << " ";
        }
        out << endl;
        return out;
    }

    bool empty() const
    {
        if (SIZE == 0)
        {
            return 1;
        }
        return 0;
    }

    void swap(Vector &other)
    {
        T *temp = arr;
        arr = other.arr;
        other.arr = temp;

        int temp_s = SIZE;
        SIZE = other.SIZE;
        other.SIZE = temp_s;

        temp_s = CAP;
        CAP = other.CAP;
        other.CAP = temp_s;
    }

    bool operator==(const Vector &other) const
    {
        if (this->SIZE != other.SIZE)
        {
            return 0;
        }

        for (int i = 0; i < SIZE; i++)
        {
            if (this->arr[i] != other.arr[i])
            {
                return 0;
            }
        }
        return 1;
    }

    bool operator!=(const Vector &other) const
    {
        return !(*this == other);
    }

    
    void selectionSort()
    {
        for (int i = 0; i < SIZE - 1; i++)
        {
            int minIdx = i;
            for (int j = i + 1; j < SIZE; j++)
            {
                if (arr[j] < arr[minIdx])
                {
                    minIdx = j;
                }
            }
            if (minIdx != i)
            {
                int temp = arr[i];
                arr[i] = arr[minIdx];
                arr[minIdx] = temp;
            }
        }
    }
     
    
    void reverse_selectionSort()
    {
        for (int i = 0; i < SIZE - 1; i++)
        {
            int minIdx = i;
            for (int j = i + 1; j < SIZE; j++)
            {
                if (arr[j] > arr[minIdx])
                {
                    minIdx = j;
                }
            }
            if (minIdx != i)
            {
                std::swap(arr[i], arr[minIdx]);
            }
        }
    }

    void reverse() 
    {
        if (SIZE <= 1)
        {
            return;
        }

        int start = 0;
        int end = SIZE - 1;

        while (start < end) 
        {   
            //std::swap(arr[start], arr[end]);
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;

            start++;
            end--;
        }
    }

    // To use std::algorithm sort you need :
    // std::sort(&v1[0], &v1[0] + v1.size());    //Don't use v1.begin() or v1.end()

    int linearSearch(T target)
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (arr[i] == target)
            {
                return i;
            }
        }
        return -1;
    }

    bool is_sorted() const
    {
        for (int i = 0; i < SIZE - 1; i++)
        {
            if (arr[i] > arr[i + 1])
                return false;
        }
        return true;
    }

    int binarySearch(T target)
    {
        if (!is_sorted())
        {
            throw runtime_error("Binary Search requires a sorted vector! Run selectionSort() first.");
        }
        int low = 0;
        int high = SIZE - 1;

        while (low <= high)
        {
            int mid = low + (high - low) / 2;

            if (arr[mid] == target)
            {
                return mid;
            }
            if (arr[mid] < target)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return -1;
    }

    void display() const
    {
        for (int i = 0; i < SIZE; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    ~Vector()
    {
        delete[] arr;
    }

    class Iterator
    {
        T *ptr; // Current Value Pointer
        T *begin_ptr;
        T *end_ptr;

    public:
        Iterator(T *p, T *first, T *last)
        {
            ptr = p;
            begin_ptr = first;
            end_ptr = last;
        }
        T &operator*()
        {
            if (ptr < begin_ptr || ptr > end_ptr)
            {
                throw out_of_range("Iterator Out of Range (Not Possible)\n");
            }
            return *ptr;
        }
        Iterator &operator=(const Iterator &other)
        {
            if (this != &other)
            {
                ptr = other.ptr;
                begin_ptr = other.begin_ptr;
                end_ptr = other.end_ptr;
            }
            return *this;
        }
        Iterator operator+(int n) const
        {
            if (ptr + n < begin_ptr || ptr + n > end_ptr)
            {
                throw out_of_range("Iterator Out of Range (Not Possible)\n");
            }
            return Iterator(ptr + n, begin_ptr, end_ptr);
        }
        Iterator &operator++()
        {
            if (ptr >= end_ptr)
            {
                throw out_of_range("Incrementing past end\n");
            }
            ptr++;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator temp = *this;
            if (ptr >= end_ptr)
            {
                throw out_of_range("Incrementing past end\n");
            }
            ptr++;
            return temp;
        }

        Iterator &operator--()
        {
            if (ptr <= begin_ptr)
            {
                throw out_of_range("Decrementing Before beginning\n");
            }
            ptr--;
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator temp = *this;
            if (ptr <= begin_ptr)
            {
                throw out_of_range("Decrementing past beginning\n");
            }
            ptr--;
            return temp;
        }

        Iterator operator-(int n)
        {
            if (ptr - n < begin_ptr)
            {
                throw out_of_range("Iterator Out of Range (Not Possible)\n");
            }
            return Iterator(ptr - n, begin_ptr, end_ptr);
        }

        int operator-(const Iterator &other)
        {
            if (this->begin_ptr != other.begin_ptr)
            {
                throw invalid_argument("Iterators belong to different vectors\n");
                // You need to write another function that accepts other vectors as well
                // For that you will need to check SIZES of both vectors as well
            }
            return this->ptr - other.ptr;
            // C++ actually divides the pointers after subtracting their memory address to give distance between two pointers
        }

        T &operator[](int ind)
        {
            if (ptr + ind < begin_ptr || ptr + ind >= end_ptr)
            {
                throw out_of_range("Iterator Out of Range (Not Possible)\n");
            }
            return *(ptr + ind);
        }
        bool operator==(const Iterator &other)
        {
            if (this->ptr == other.ptr)
            {
                return 1;
            }
            return 0;
        }

        bool operator!=(const Iterator &other)
        {
            if (this->ptr != other.ptr)
            {
                return 1;
            }
            return 0;
        }
    };

    Iterator begin()
    {
        return Iterator(arr, arr, arr + SIZE);
    }
    Iterator end() // Will Point to one after last element
    {
        return Iterator(arr + SIZE, arr, arr + SIZE);
    }

    // Integer Based :
    void insert(int value, int ind)
    {
        if (ind < 0 || ind > SIZE)
        {
            throw out_of_range("Index Out of Range (Not Possible)\n");
        }

        if (SIZE == CAP)
        {
            reserve(CAP * 2);
        }

        for (int i = SIZE; i > ind; i--)
        {
            arr[i] = arr[i - 1];
        }

        arr[ind] = value;
        SIZE++;
    }

    // Iterator Based (Single Value):
    Iterator insert(Iterator i, T val)
    {
        int ind = i - begin();
        insert(ind, val); // Index is checked in insert as well
        return Iterator(arr + ind, arr, arr + SIZE);
    }

    // Iterator Based (Fill n values) :
    void insert(Iterator i, int n, T val)
    {
        int ind = i - begin();
        if (SIZE + n > CAP)
        {
            reserve((SIZE + n) * 2);
        }

        for (int i = SIZE + n - 1; i >= ind + n; i--)
        {
            arr[i] = arr[i - n];
        }

        for (int i = 0; i < n; i++)
        {
            arr[ind + i] = val;
        }

        SIZE += n;
    }

    // Iterator Based (Range) :
    void insert(Iterator i, Iterator first, Iterator last)
    {
        int n = last - first;
        int ind = i - begin();

        if (SIZE + n > CAP)
        {
            reserve((SIZE + n) * 2);
        }

        for (int i = SIZE + n - 1; i >= ind + n; i--)
        {
            arr[i] = arr[i - n];
        }

        for (int i = 0; i < n; i++)
        {
            arr[ind + i] = first[i];
        }

        SIZE += n;
        return Iterator(arr + ind, arr, arr + SIZE);
    }

    // Integer based (single element) :
    void erase(int ind)
    {
        if (ind < 0 || ind >= SIZE)
        {
            throw out_of_range("Index Out of Range (Not Possible)\n");
        }

        for (int i = ind; i < SIZE - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        SIZE--;
    }

    // Iterator based (single element) :
    Iterator erase(Iterator i)
    {
        int ind = i - begin();
        erase(ind);
        return Iterator(arr + ind, arr, arr + SIZE);
    }

    // Iterator based (range) :
    Iterator erase(Iterator first, Iterator last)
    {
        int start_ind = first - begin();
        int nums = last - first;

        if (nums <= 0)
        {
            return first;
        }

        for (int i = start_ind; i < SIZE - nums; i++)
        {
            arr[i] = arr[i + nums];
        }

        SIZE -= nums;

        return Iterator(arr + start_ind, arr, arr + SIZE);
    }

    // set(int , int ) and get(int) are already implemented above in the form of .at() and [] functions
    void set(int index, T val) // Like Insert but it overwrites , not shifts
    {
        if (index < 0 || index >= SIZE)
        {
            throw out_of_range("Index Out of Range (Not Possible)\n");
        }
        arr[index] = val;
    }

    T &get(int index) // Works for non-const vector objects only , but can modify the value as we only want that
    {
        if (index < 0 || index >= SIZE)
        {
            throw out_of_range("Index Out of Range (Not Possible)\n");
        }
        return arr[index];
    }

    const T &get(int index) const // Allows to work with const vector also (or non-const if above is not present) , read only version
    {
        if (index < 0 || index >= SIZE)
        {
            throw out_of_range("Index Out of Range (Not Possible)\n");
        }
        return arr[index];
    }
};
