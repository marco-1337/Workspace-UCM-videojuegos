 template<typename T>
class MyVector
{
private:
    T* array = new T[10];
    int s = 0;
    int capacity = 10;

public:

    ~MyVector()
    {
        delete [] array;
    }

    void push_back(T entry)
    {
        if (s == capacity)
        {
            T* nuevoArray = new T[capacity*2];

            for (size_t i = 0; i < capacity; ++i)
            {
                nuevoArray[i] = array[i];
            }

            delete [] array;

            array = nuevoArray;
            capacity *= 2;
        }
        
        array[s] = entry;
        ++s;
    }

    int size() const
    {
        return s;
    }

    T& operator[](int i)
    {
        return array[i];
    }

};