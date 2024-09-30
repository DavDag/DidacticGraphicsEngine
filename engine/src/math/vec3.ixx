export module engine.math.vec3;

import engine.core;

/**
 * @brief A simple 3D vector class.
 **/
template<typename T>
class Vec3 {
public:
    // Members
    T x, y, z;

    // Constructors
    Vec3(const Vec3& other) noexcept = default;
    Vec3(Vec3&& other) noexcept = default;
    Vec3() noexcept : x(0), y(0), z(0) {}
    Vec3(T x, T y, T z) noexcept : x(x), y(y), z(z) { DebugAssert(!hasNaNs(), "Vec3 contains NaN"); }

    // Conversion constructors
    template<typename U>
    explicit Vec3(const Vec3<U>& other) noexcept :
        x(static_cast<T>(other.x)),
        y(static_cast<T>(other.y)),
        z(static_cast<T>(other.z)) {}

    // Assignment operators
    Vec3& operator=(const Vec3& other) noexcept = default;
    Vec3& operator=(Vec3&& other) noexcept = default;

    // Logic operators
    bool operator==(const Vec3& other) const noexcept;
    bool operator!=(const Vec3& other) const noexcept;

    // Indexing operators
    T& operator[](int index) noexcept;
    const T& operator[](int index) const noexcept;

    // Arithmetic operators
    Vec3 operator+(const Vec3& other) const noexcept;
    Vec3& operator+=(const Vec3& other) noexcept;
    Vec3 operator-(const Vec3& other) const noexcept;
    Vec3& operator-=(const Vec3& other) noexcept;
    Vec3 operator*(const T& scalar) const noexcept;
    Vec3& operator*=(const T& scalar) noexcept;
    Vec3 operator/(const T& scalar) const noexcept;
    Vec3& operator/=(const T& scalar) noexcept;

    // Extra functions
    bool hasNaNs() const noexcept;
    T dot(const Vec3& other) const noexcept;
    Vec3<T> cross(const Vec3& other) const noexcept;
    T length() const noexcept;
    T lengthSquared() const noexcept;
    Vec3 normalized() const noexcept;
    Vec3& normalize() noexcept;
    T minComponent() const noexcept;
    T maxComponent() const noexcept;
    Vec3 negated() const noexcept;
    Vec3& negate() noexcept;

    // Common vectors
    static const Vec3<T> Zero;
    static const Vec3<T> One;
    static const Vec3<T> UnitX;
    static const Vec3<T> UnitY;
    static const Vec3<T> UnitZ;
};

export {

    // 
    // Type aliases
    // 

    using Vec3i8 = Vec3<i8>;
    using Vec3i16 = Vec3<i16>;
    using Vec3i32 = Vec3<i32>;
    using Vec3i64 = Vec3<i64>;

    using Vec3u8 = Vec3<u8>;
    using Vec3u16 = Vec3<u16>;
    using Vec3u32 = Vec3<u32>;
    using Vec3u64 = Vec3<u64>;

    using Vec3f32 = Vec3<f32>;
    using Vec3f64 = Vec3<f64>;

    // 
    // Default type alias
    // 

    using Vec3i = Vec3<i32>;
    using Vec3f = Vec3<f32>;

};

// 
// Implementation
// 

template<typename T>
T& Vec3<T>::operator[](int index) noexcept {
    DebugAssert(index >= 0 && index < 3, "Index out of bounds");
    switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    }
}

template<typename T>
const T& Vec3<T>::operator[](int index) const noexcept {
    DebugAssert(index >= 0 && index < 3, "Index out of bounds");
    switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    }
}

template<typename T>
bool Vec3<T>::operator==(const Vec3& other) const noexcept {
    return x == other.x && y == other.y && z == other.z;
}

template<typename T>
bool Vec3<T>::operator!=(const Vec3& other) const noexcept {
    return !(*this == other);
}

// override for floating point types (since the equality operator is not precise)
template<>
bool Vec3<f32>::operator==(const Vec3& other) const noexcept {
    return std::fabs(x - other.x) < F32_EPSILON
        && std::fabs(y - other.y) < F32_EPSILON
        && std::fabs(z - other.z) < F32_EPSILON;
}

template<>
bool Vec3<f64>::operator==(const Vec3& other) const noexcept {
    return std::abs(x - other.x) < F64_EPSILON
        && std::abs(y - other.y) < F64_EPSILON
        && std::abs(z - other.z) < F64_EPSILON;
}

template<typename T>
Vec3<T> Vec3<T>::operator+(const Vec3& other) const noexcept {
    return Vec3(x + other.x, y + other.y, z + other.z);
}

template<typename T>
Vec3<T>& Vec3<T>::operator+=(const Vec3& other) noexcept {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

template<typename T>
Vec3<T> Vec3<T>::operator-(const Vec3& other) const noexcept {
    return Vec3(x - other.x, y - other.y, z - other.z);
}

template<typename T>
Vec3<T>& Vec3<T>::operator-=(const Vec3& other) noexcept {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

template<typename T>
Vec3<T> Vec3<T>::operator*(const T& scalar) const noexcept {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

template<typename T>
Vec3<T>& Vec3<T>::operator*=(const T& scalar) noexcept {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

template<typename T>
Vec3<T> Vec3<T>::operator/(const T& scalar) const noexcept {
    DebugAssert(scalar != 0, "Division by zero");
    f32 inv = 1 / scalar;
    return Vec3(x * inv, y * inv, z * inv);
}

// override for f64 (otherwise the precision is lost)
template<>
Vec3<f64> Vec3<f64>::operator/(const f64& scalar) const noexcept {
    DebugAssert(scalar != 0, "Division by zero");
    f64 inv = 1 / scalar;
    return Vec3(x * inv, y * inv, z * inv);
}

template<typename T>
Vec3<T>& Vec3<T>::operator/=(const T& scalar) noexcept {
    DebugAssert(scalar != 0, "Division by zero");
    f32 inv = 1 / scalar;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
}

// override for f64 (otherwise the precision is lost)
template<>
Vec3<f64>& Vec3<f64>::operator/=(const f64& scalar) noexcept {
    DebugAssert(scalar != 0, "Division by zero");
    f64 inv = 1 / scalar;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
}

template<typename T>
bool Vec3<T>::hasNaNs() const noexcept {
    return std::isnan(x) || std::isnan(y) || std::isnan(z);
}

template<typename T>
T Vec3<T>::dot(const Vec3& other) const noexcept {
    return x * other.x + y * other.y + z * other.z;
}

template<typename T>
Vec3<T> Vec3<T>::cross(const Vec3& other) const noexcept {
    f64 ax = x, ay = y, az = z;
    f64 bx = other.x, by = other.y, bz = other.z;
    return static_cast<Vec3<T>>(Vec3(
        ay * bz - az * by,
        az * bx - ax * bz,
        ax * by - ay * bx
    ));
}

template<typename T>
T Vec3<T>::length() const noexcept {
    return std::sqrt(lengthSquared());
}

template<typename T>
T Vec3<T>::lengthSquared() const noexcept {
    return x * x + y * y + z * z;
}

template<typename T>
Vec3<T> Vec3<T>::normalized() const noexcept {
    return (*this) / length();
}

template<typename T>
Vec3<T>& Vec3<T>::normalize() noexcept {
    *this /= length();
    return *this;
}

template<typename T>
T Vec3<T>::minComponent() const noexcept {
    return std::min(x, y, z);
}

template<typename T>
T Vec3<T>::maxComponent() const noexcept {
    return std::max(x, y, z);
}

template<typename T>
Vec3<T> Vec3<T>::negated() const noexcept {
    return Vec3(-x, -y, -z);
}

template<typename T>
Vec3<T>& Vec3<T>::negate() noexcept {
    x = -x;
    y = -y;
    z = -z;
    return *this;
}

// 
// Common vectors (implementation)
// 

template<typename T>
const Vec3<T> Vec3<T>::Zero = Vec3<T>(0, 0, 0);
template<typename T>
const Vec3<T> Vec3<T>::UnitX = Vec3<T>(1, 0, 0);
template<typename T>
const Vec3<T> Vec3<T>::UnitY = Vec3<T>(0, 1, 0);
template<typename T>
const Vec3<T> Vec3<T>::UnitZ = Vec3<T>(0, 0, 1);
