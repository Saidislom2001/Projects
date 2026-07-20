/**
 * Iterators
 * 
 * Tasks:
 *
 *  - add const and non-const iterators types to the implementation below
 *  - add begin()/end() methods providing appropriate iterators
 * 
 *  - test the implementation by using it in main
 * 
 */

#include <iostream>
#include <stddef.h>  // for type: size_t

using namespace std;

template <typename T>


/**
 * @brief Vector - A vector class (dynamic array).
 *
 * The data will be stored in a dynamically allocated memory.
 */
template <typename T>
class Vector
{
public:
    /**
     * @brief Vector - Constructor.
     *
     * Create a new Vector instance.
     * The length of the vector will be zero.
     *
     * @return N/A
     */

    // 1 add const and non-const iterators types to the implementation below
    class Iterator
{
public:
    bool operator==(const Iterator<T>& i) const {return ptr_ == i.ptr_;};
    bool operator!=(const Iterator<T>& i) const {return ptr_ != i.ptr_;};
    Iterator<T>& operator++() {++ptr_; return *this;}; // prefix increment
    Iterator<T> operator++(int) {Iterator<T> tmp(*this); ++(*this); return tmp;}; // postfix increment
    T& operator*() const {return *ptr_;}; // dereference operator
    T* operator->() const {return ptr_;}; // member access operator
private:
    T* ptr_; // pointer to the current element
};

    Vector() : size_(0), vals_(nullptr) {}

    /**
     * @brief Vector - Constructor.
     *
     * Create a new vector instance with a given length.
     * The vector values are NOT initialized.
     *
     * @param[in] n: The vector length.
     *
     * @return N/A
     */
    Vector(size_t n) : size_(n), vals_(new T[n]) {}

    /**
     * @brief Vector - Constructor.
     *
     * Create a new vector instance with a given length and initial value.
     * Creates a vector of given length with all values equal to the initial.
     *
     * @param[in] n:   The vector length.
     * @param[in] val: The initial value
     *
     * @return N/A
     */
    Vector(size_t n, T val) : size_(n), vals_(new T[n]) {
        for(size_t i = 0; i < size_; ++i)
            vals_[i] = val;
    }

    /**
     * @brief Vector - Destructor.
     *
     * Cleanup when an instance is deleted.
     *
     * @return N/A
     */
    ~Vector() {
        if(vals_ != nullptr)
            delete[] vals_;
    }

    /**
     * @brief Vector - Copy constructor.
     *
     * Create an instance from another instance.
     *
     * @param[in] obj: the other vector used for initialization
     *
     * @return N/A
     */
    Vector(const Vector& obj) {
        size_ = obj.size_;
        vals_ = new T[size_];
        for(size_t i = 0; i < size_; ++i)
            vals_[i] = (obj.vals_)[i];        
    }

    /**
     * @brief Vector - Copy assignment.
     *
     * Assign another instance to this one.
     *
     * @param[in] obj: the other vector used for assignment
     *
     * @return a reference to itself
     */
    Vector& operator=(const Vector& obj) {
        size_ = obj.size_;
        if(vals_ != nullptr)
            delete[] vals_;
        vals_ = new T[size_];
        for(size_t i = 0; i < size_; ++i)
            vals_[i] = (obj.vals_)[i];    

        return *this;    
    }

    /**
     * @brief operator[] - Write/read a given value at a given index
     *
     * Write/read access to a value at a given index.
     *
     * @param[in] i:   Index
     *
     * @return reference to the value
     */
    T& operator[](size_t i) {return vals_[i];}

    /**
     * @brief operator[] - Read a given value at a given index
     *
     * Read-only access to a value at a given index.
     *
     * @param[in] i:   Index
     *
     * @return const reference to the value
     */
    const T& operator[](size_t i) const {return vals_[i];}

    // 2 add begin()/end() methods providing appropriate iterators
    Iterator begin() { return Iterator(vals_); }
    Iterator end() { return Iterator(vals_ + size_); }
    const Iterator begin() const { return Iterator(vals_); }
    const Iterator end() const { return Iterator(vals_ + size_); }

    size_t size() const { return size_; }


private:
    // The vector size
    size_t size_;

    // The vector data
    T* vals_;
};


int main(){

    // test the implementation
    cout << "Testing the implementation of the Vector class with iterators" << endl;
    Vector<int> x;
    Vector<double> y(5.0, 10.0);

    for (auto it = y.begin(); it != y.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    for (const auto& val : y) {
        cout << val << " ";
    }
    cout << endl;

    for (auto it = x.begin(); it != x.end(); ++it) {
        cout << *it << " ";
    } // This will not print anything since x is empty

    
    return 0;
    }












