module;
#include <cmath>
#include <algorithm>
#include <type_traits>
export module engine.math.vec4;

import engine.core;

/**
 * @brief A simple 4D vector class.
 **/
template<typename T>
class Vec4 {
public:
    // Members
	T x, y, z, w;

    // Constructors
    Vec4(const Vec4& other) noexcept = default;
    Vec4(Vec4&& other) noexcept = default;
	Vec4() noexcept : x(0), y(0), z(0), w(0) {}
    Vec4(T x, T y, T z, T w) noexcept : x(x), y(y), z(z), w(w) { DebugAssert(!hasNaNs(), "Vec4 contains NaN"); }

    // Conversion constructors
    template<typename U>
    explicit Vec4(const Vec4<U>& other) noexcept :
        x(static_cast<T>(other.x)),
        y(static_cast<T>(other.y)),
        z(static_cast<T>(other.z)),
		w(static_cast<T>(other.w)) {}

    // Assignment operators
    Vec4& operator=(const Vec4& other) noexcept = default;
    Vec4& operator=(Vec4&& other) noexcept = default;

    // Logic operators
    bool operator==(const Vec4& other) const noexcept;
    bool operator!=(const Vec4& other) const noexcept;

    // Indexing operators
    T& operator[](int index) noexcept;
    const T& operator[](int index) const noexcept;

    // Arithmetic operators
    Vec4 operator+(const Vec4& other) const noexcept;
    Vec4& operator+=(const Vec4& other) noexcept;
    Vec4 operator-(const Vec4& other) const noexcept;
    Vec4& operator-=(const Vec4& other) noexcept;
    Vec4 operator*(const T& scalar) const noexcept;
    Vec4& operator*=(const T& scalar) noexcept;
    Vec4 operator/(const T& scalar) const noexcept;
    Vec4& operator/=(const T& scalar) noexcept;

    // Extra functions
    bool hasNaNs() const noexcept;
    T dot(const Vec4& other) const noexcept;
    T length() const noexcept;
    T lengthSquared() const noexcept;
    Vec4 normalized() const noexcept;
    Vec4& normalize() noexcept;
    T minComponent() const noexcept;
    T maxComponent() const noexcept;
    Vec4 negated() const noexcept;
    Vec4& negate() noexcept;

    // Common vectors
    static const Vec4<T> Zero;
    static const Vec4<T> One;
    static const Vec4<T> UnitX;
    static const Vec4<T> UnitY;
    static const Vec4<T> UnitZ;
	static const Vec4<T> UnitW;
};

export {

    // 
    // Type aliases
    // 

    using Vec4i8 = Vec4<i8>;
    using Vec4i16 = Vec4<i16>;
    using Vec4i32 = Vec4<i32>;
    using Vec4i64 = Vec4<i64>;

    using Vec4u8 = Vec4<u8>;
    using Vec4u16 = Vec4<u16>;
    using Vec4u32 = Vec4<u32>;
    using Vec4u64 = Vec4<u64>;

    using Vec4f32 = Vec4<f32>;
    using Vec4f64 = Vec4<f64>;

    // 
    // Default type alias
    // 

    using Vec4i = Vec4<i32>;
    using Vec4f = Vec4<f32>;

};

// 
// Implementation
// 

template<typename T>
T& Vec4<T>::operator[](int index) noexcept {
    DebugAssert(index >= 0 && index < 4, "Index out of bounds");
    switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
	case 3: return w;
    }
}

template<typename T>
const T& Vec4<T>::operator[](int index) const noexcept {
    DebugAssert(index >= 0 && index < 4, "Index out of bounds");
    switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
	case 3: return w;
    }
}

template<typename T>
bool Vec4<T>::operator==(const Vec4& other) const noexcept {
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

template<typename T>
bool Vec4<T>::operator!=(const Vec4& other) const noexcept {
    return !(*this == other);
}

// override for floating point types (since the equality operator is not precise)
template<>
bool Vec4<f32>::operator==(const Vec4& other) const noexcept {
    return std::fabs(x - other.x) < F32_EPSILON
        && std::fabs(y - other.y) < F32_EPSILON
        && std::fabs(z - other.z) < F32_EPSILON
		&& std::fabs(w - other.w) < F32_EPSILON;
}

template<>
bool Vec4<f64>::operator==(const Vec4& other) const noexcept {
    return std::abs(x - other.x) < F64_EPSILON
        && std::abs(y - other.y) < F64_EPSILON
        && std::abs(z - other.z) < F64_EPSILON
		&& std::abs(w - other.w) < F64_EPSILON;
}

template<typename T>
Vec4<T> Vec4<T>::operator+(const Vec4& other) const noexcept {
	return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
}

template<typename T>
Vec4<T>& Vec4<T>::operator+=(const Vec4& other) noexcept {
    x += other.x;
    y += other.y;
    z += other.z;
	w += other.w;
    return *this;
}

template<typename T>
Vec4<T> Vec4<T>::operator-(const Vec4& other) const noexcept {
	return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
}

template<typename T>
Vec4<T>& Vec4<T>::operator-=(const Vec4& other) noexcept {
    x -= other.x;
    y -= other.y;
    z -= other.z;
	w -= other.w;
    return *this;
}

template<typename T>
Vec4<T> Vec4<T>::operator*(const T& scalar) const noexcept {
	return Vec4(x * scalar, y * scalar, z * scalar, w * scalar);
}

template<typename T>
Vec4<T>& Vec4<T>::operator*=(const T& scalar) noexcept {
    x *= scalar;
    y *= scalar;
    z *= scalar;
	w *= scalar;
    return *this;
}

template<typename T>
Vec4<T> Vec4<T>::operator/(const T& scalar) const noexcept {
    DebugAssert(scalar != 0, "Division by zero");
    f32 inv = 1 / scalar;
	return Vec4(x * inv, y * inv, z * inv, w * inv);
}

// override for f64 (otherwise the precision is lost)
template<>
Vec4<f64> Vec4<f64>::operator/(const f64& scalar) const noexcept {
    DebugAssert(scalar != 0, "Division by zero");
    f64 inv = 1 / scalar;
	return Vec4(x * inv, y * inv, z * inv, w * inv);
}

template<typename T>
Vec4<T>& Vec4<T>::operator/=(const T& scalar) noexcept {
    DebugAssert(scalar != 0, "Division by zero");
    f32 inv = 1 / scalar;
    x *= inv;
    y *= inv;
    z *= inv;
	w *= inv;
    return *this;
}

// override for f64 (otherwise the precision is lost)
template<>
Vec4<f64>& Vec4<f64>::operator/=(const f64& scalar) noexcept {
    DebugAssert(scalar != 0, "Division by zero");
    f64 inv = 1 / scalar;
    x *= inv;
    y *= inv;
    z *= inv;
	w *= inv;
    return *this;
}

template<typename T>
bool Vec4<T>::hasNaNs() const noexcept {
	return std::isnan(x) || std::isnan(y) || std::isnan(z) || std::isnan(w);
}

template<typename T>
T Vec4<T>::dot(const Vec4& other) const noexcept {
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

template<typename T>
T Vec4<T>::length() const noexcept {
    return std::sqrt(lengthSquared());
}

template<typename T>
T Vec4<T>::lengthSquared() const noexcept {
	return x * x + y * y + z * z + w * w;
}

template<typename T>
Vec4<T> Vec4<T>::normalized() const noexcept {
    return (*this) / length();
}

template<typename T>
Vec4<T>& Vec4<T>::normalize() noexcept {
    *this /= length();
    return *this;
}

template<typename T>
T Vec4<T>::minComponent() const noexcept {
	return std::min(x, y, z, w);
}

template<typename T>
T Vec4<T>::maxComponent() const noexcept {
	return std::max(x, y, z, w);
}

template<typename T>
Vec4<T> Vec4<T>::negated() const noexcept {
	return Vec4(-x, -y, -z, -w);
}

template<typename T>
Vec4<T>& Vec4<T>::negate() noexcept {
    x = -x;
    y = -y;
    z = -z;
	w = -w;
    return *this;
}

// 
// Common vectors (implementation)
// 

template<typename T>
const Vec4<T> Vec4<T>::Zero = Vec4<T>(0, 0, 0, 0);
template<typename T>
const Vec4<T> Vec4<T>::UnitX = Vec4<T>(1, 0, 0, 0);
template<typename T>
const Vec4<T> Vec4<T>::UnitY = Vec4<T>(0, 1, 0, 0);
template<typename T>
const Vec4<T> Vec4<T>::UnitZ = Vec4<T>(0, 0, 1, 0);
template<typename T>
const Vec4<T> Vec4<T>::UnitW = Vec4<T>(0, 0, 0, 1);
