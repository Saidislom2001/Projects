# ifndef __H__VECTOR__
# define __H__VECTOR__

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
    Vector();

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
    Vector(size_t n);

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
    Vector(size_t n, T val);

    /**
     * @brief Vector - Destructor.
     *
     * Cleanup when an instance is deleted.
     *
     * @return N/A
     */
    ~Vector();

    /**
     * @brief Vector - Copy constructor.
     *
     * Create an instance from another instance.
     *
     * @param[in] obj: the other vector used for initialization
     *
     * @return N/A
     */
    Vector(const Vector& obj);

    /**
     * @brief Vector - Copy assignment.
     *
     * Assign another instance to this one.
     *
     * @param[in] obj: the other vector used for assignment
     *
     * @return a reference to itself
     */
    Vector& operator=(const Vector& obj);

    /**
     * @brief operator[] - Write/read a given value at a given index
     *
     * Write/read access to a value at a given index.
     *
     * @param[in] i:   Index
     *
     * @return reference to the value
     */
    T& operator[](size_t i);

    /**
     * @brief operator[] - Read a given value at a given index
     *
     * Read-only access to a value at a given index.
     *
     * @param[in] i:   Index
     *
     * @return const reference to the value
     */
    const T& operator[](size_t i) const;


private:
    // The vector size
    size_t size_;

    // The vector data
    T* vals_;
};




#include "07-vector_impl.h"

#endif



