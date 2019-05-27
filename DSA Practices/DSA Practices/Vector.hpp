//
//  Vector.hpp
//  SDP Practs
//

#include <iostream>
#ifndef Vector_hpp
#define Vector_hpp



const unsigned short STARTING_CAPACITY = 2;

template <typename T>
class Vector
{
public:
    Vector();
    Vector(T const&);
    Vector(const Vector&);
    Vector& operator=(const Vector&);
    const T& operator[](unsigned) const;
    T& operator[](unsigned);
    ~Vector();
    
public:
    void addElement(const T&);
    void removeElement(const T&);
    int findElement(const T&);
    void shrinkToFit();
    bool includes(const Vector<T>&) const;
    unsigned getSize() const;
    
    
    
private:
    void free();
    void resize();
    void copy(const Vector<T>& obj);
    int binarySearch(T);
    void selectionSort(Vector<T>&);
    int linearSearch(T);
    void swapByIndex(unsigned i, unsigned j);
    
private:
    T* vector;
    unsigned size;
    unsigned capacity;
    bool isSorted;
    
    
    
};

template <typename T>
Vector<T>::Vector()
{
    try {
        vector = new T[STARTING_CAPACITY];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Bad alloc caught: " << ba.what() << '\n';
        throw;
    }
    capacity = STARTING_CAPACITY;
    size = 0;
}

template <typename T>
Vector<T>::Vector(T const& element)
{
    try {
        vector = new T[STARTING_CAPACITY];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Bad alloc caught: " << ba.what() << '\n';
        throw;
    }
    addElement(element);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& newVector)
{
    copy(newVector);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& newVector)
{
    if(this != &newVector)
    {
        copy(newVector);
    }
    return *this;
}

template <typename T>
Vector<T>::~Vector()
{
    free();
}

template <typename T>
void Vector<T>::resize()
{
    T* p;
    try {
        p = new T[capacity * STARTING_CAPACITY];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Bad alloc caught: " << ba.what() << '\n';
        throw;
    }
    capacity*= STARTING_CAPACITY;
    for(unsigned i = 0; i < size; ++i)
    {
        p[i] = vector[i];
    }
    
    delete[] vector;
    vector = p;
}

template <typename T>
void Vector<T>::free()
{
    delete[] vector;
}

template <typename T>
void Vector<T>::copy(const Vector<T>& obj)
{
    T* temp = nullptr;
    try {
        temp = new T[obj.capacity];
    } catch (const std::bad_alloc& ba) {
        std::cerr << "Bad alloc caught: " << ba.what() << '\n';
        throw;
    }
    
    for (size_t i = 0; i < size; ++i)
    {
        temp[i] = obj.vector[i];
    }
    
    vector = temp;
    capacity = obj.capacity;
    size = obj.size;
}

template <typename T>
void Vector<T>::addElement(const T& element)
{
    if (size == capacity)
    {
        resize();
    }
    vector[size] = element;
    size++;
}

template <typename T>
void Vector<T>::removeElement(const T& element)
{
    int pos = findElement(element);
    if(pos != -1)
    {
        for(int i = pos; pos < size-1; ++pos)
        {
            vector[i] = vector[i+1];
        }
        size--;
    }
}

template <typename T>
int Vector<T>::findElement(const T& element)
{
    if(isSorted)
    {
       return binarySearch(element);
    }
    else
    {
      return  linearSearch(element);
    }
}

template <typename T>
int Vector<T>::binarySearch(T element)
{
    int r = 0;
    int l = size-1;
    
    while (r < l)
    {
        int m = (l+r)/2;
        if(vector[m] == element)
        {
            return m;
        }
        else if(vector[m] < element)
        {
            r = m + 1;
        }
        else
        {
            l = r - 1;
        }
    }
    return -1;
}

template <typename T>
int Vector<T>::linearSearch(T element)
{
    for(unsigned i = 0; i < size; ++i)
    {
        if(vector[i] == element)
        {
            return i;
        }
    }
    return -1;
}

template <typename T>
void selectionSort(Vector<T>& vector)
{
    for(unsigned i = 0; i < vector.size; ++i)
    {
        T minIndex = i;
        for(unsigned j = i+1; j < vector.size; ++j)
        {
            if(vector[j] < vector[minIndex])
            {
                minIndex = j;
            }
        }
        swapByIndex(i, minIndex);
    }
    vector.isSorted = true;
}

template <typename T>
void Vector<T>::swapByIndex(unsigned i, unsigned j)
{
    T temp = vector[i];
    vector[i] = vector[j];
    vector[j] = temp;
    
}

template <typename T>
const T& Vector<T>::operator[](unsigned pos) const
{
    try {
        pos < 0 || pos > size - 1;
    } catch (const std::out_of_range& exc)
    {
        std::cerr << "Invalid index" << exc.what() << '\n';
        throw;
    }
    return vector[pos];
}

template <typename T>
T& Vector<T>::operator[](unsigned pos)
{
    try {
        if(pos < 0 || pos > size - 1)
            throw;
    } catch (const std::out_of_range& exc)
    {
        std::cerr << "Invalid index" << exc.what() << '\n';
        throw;
    }
    return vector[pos];
}

template <typename T>
const Vector<T> reverse(const Vector<T>& source)
{
   Vector<T> destination = Vector<T>(source[source.size-1]);
    for(unsigned i = source.size - 2; i >= 0; --i)
    {
        destination.addElement(source[i]);
    }
    return destination;
}

template <typename T>
const Vector<T> merge(const Vector<T>& arr1, const Vector<T>& arr2)
{
    Vector<T> newArr = Vector<T>(arr1);
    for(unsigned i = 0; i < arr2.size; ++i)
    {
        newArr.addElement(arr2[i]);
    }
    return newArr;
}

template <typename T>
void Vector<T>::shrinkToFit()
{
    T* temp = nullptr;
    try
    {
        T* temp = new T[size];
    }
    catch (const std::bad_alloc& ba)
    {
        std::cerr << "Cannot allocate memory to shrink.\n";
        throw;
    }
    
    for(unsigned i = 0; i < size; ++i)
    {
        temp[i] = vector[i];
    }
    delete[] vector;
    vector = temp;
    temp = nullptr;
    capacity = 0;
}

template <typename T>
bool Vector<T>::includes(const Vector<T>& arr) const
{
    if(arr.size > size)
    {
        return false;
    }
    unsigned counter = size - arr.size;
    for(unsigned i = 0; i <= counter; ++i)
        {
            bool flag = false;
            for(unsigned j = i; j < arr.size; j++)
            {
                if(vector[j] != arr[j])
                {
                    flag = false;
                    break;
                }
                flag = true;
            }
            if(flag)
            {
                return true;
            }
        }
    return false;
}

template <typename T>
unsigned Vector<T>::getSize() const
{
    return size;
}

#endif
