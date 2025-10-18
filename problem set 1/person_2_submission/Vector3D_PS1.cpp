#include "Vector3D.h"
#include <sstream>
#include <cmath>

// == operator for Vector3D: compares each component using epsilon
bool Vector3D::operator==(const Vector3D& aOther) const noexcept {
    return (std::fabs(x() - aOther.x()) < eps) &&
           (std::fabs(y() - aOther.y()) < eps) &&
           (std::fabs(w() - aOther.w()) < eps);
}

// toString(): returns a textual representation in the format "[x,y,w]"
std::string Vector3D::toString() const noexcept {
    std::stringstream ss;
    ss << "[" << x() << "," << y() << "," << w() << "]";
    return ss.str();
}
