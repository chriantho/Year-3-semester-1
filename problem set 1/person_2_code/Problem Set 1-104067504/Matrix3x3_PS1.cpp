#include "Matrix3x3.h"
#include <sstream>
#include <cassert>
#include <cmath>

// Matrix equivalence: Two matrices are equal if all their corresponding row vectors are equal.
bool Matrix3x3::operator==(const Matrix3x3& aOther) const noexcept {
    return (fRows[0] == aOther.fRows[0]) &&
           (fRows[1] == aOther.fRows[1]) &&
           (fRows[2] == aOther.fRows[2]);
}

// Matrix multiplication: Each element (i, j) in the result is the dot product of the i-th row of this matrix and the j-th column of aOther.
Matrix3x3 Matrix3x3::operator*(const Matrix3x3& aOther) const noexcept {
    const Matrix3x3& M = *this;
    return Matrix3x3(
        Vector3D( M[0].dot(aOther.column(0)), M[0].dot(aOther.column(1)), M[0].dot(aOther.column(2)) ),
        Vector3D( M[1].dot(aOther.column(0)), M[1].dot(aOther.column(1)), M[1].dot(aOther.column(2)) ),
        Vector3D( M[2].dot(aOther.column(0)), M[2].dot(aOther.column(1)), M[2].dot(aOther.column(2)) )
    );
}

// Transpose: Create a new matrix where each row is a column of the original matrix.
Matrix3x3 Matrix3x3::transpose() const noexcept {
    return Matrix3x3(
        column(0),
        column(1),
        column(2)
    );
}

// Determinant: Compute the determinant using the standard 3x3 formula.
float Matrix3x3::det() const noexcept {
    const Matrix3x3& M = *this;
    float M11 = M[0][0], M12 = M[0][1], M13 = M[0][2];
    float M21 = M[1][0], M22 = M[1][1], M23 = M[1][2];
    float M31 = M[2][0], M32 = M[2][1], M33 = M[2][2];
    return M11 * (M22 * M33 - M23 * M32)
         - M12 * (M21 * M33 - M23 * M31)
         + M13 * (M21 * M32 - M22 * M31);
}

// Invertibility check: A matrix is invertible if the absolute value of its determinant is greater than eps.
bool Matrix3x3::hasInverse() const noexcept {
    return std::fabs(det()) > eps;
}

// Inverse:
// First compute the cofactors
// Then form the transpose of the cofactor matrix
// After that multiply by 1/det.
Matrix3x3 Matrix3x3::inverse() const noexcept {
    const Matrix3x3& M = *this;
    float determinant = det();
    assert(std::fabs(determinant) > eps); // assert if the matrix is invertible.

    // Compute cofactors (with alternating signs)
    float c00 =  (M[1][1] * M[2][2] - M[1][2] * M[2][1]);
    float c01 = -(M[1][0] * M[2][2] - M[1][2] * M[2][0]);
    float c02 =  (M[1][0] * M[2][1] - M[1][1] * M[2][0]);

    float c10 = -(M[0][1] * M[2][2] - M[0][2] * M[2][1]);
    float c11 =  (M[0][0] * M[2][2] - M[0][2] * M[2][0]);
    float c12 = -(M[0][0] * M[2][1] - M[0][1] * M[2][0]);

    float c20 =  (M[0][1] * M[1][2] - M[0][2] * M[1][1]);
    float c21 = -(M[0][0] * M[1][2] - M[0][2] * M[1][0]);
    float c22 =  (M[0][0] * M[1][1] - M[0][1] * M[1][0]);

    // Adjugate is the transpose of the cofactor matrix.
    Matrix3x3 adjugate(
        Vector3D(c00, c10, c20),
        Vector3D(c01, c11, c21),
        Vector3D(c02, c12, c22)
    );

    return adjugate * (1.0f / determinant);
}

// Output operator: Format the matrix as [[row1],[row2],[row3]] using Vector3D's toString() method
std::ostream& operator<<(std::ostream& aOStream, const Matrix3x3& aMatrix) {
    aOStream << "["
             << aMatrix[0].toString() << ","
             << aMatrix[1].toString() << ","
             << aMatrix[2].toString() << "]";
    return aOStream;
}
