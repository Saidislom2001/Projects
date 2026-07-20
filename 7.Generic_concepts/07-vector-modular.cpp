/**
 * Modular Programming for Templates
 * 
 * Tasks:
 *
 *  - separate the implementation (main, class, ...) into units which are included
 *  - add exception handling where appropriate
 */

#include <iostream>
#include <stddef.h>  // for type: size_t

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


private:
    // The vector size
    size_t size_;

    // The vector data
    T* vals_;
};


int main(){

    // test the implementation
    Vector<int> x;
    Vector<double> y(5.0, 12.0);

}












