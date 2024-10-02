export module engine.math.vec2;

import engine.core;

/**
 * @brief A simple 2D vector class.
 **/
template<typename T>
class Vec2 {
public:
    // Members
    T x, y;

    // Constructors
    Vec2(const Vec2& other) noexcept = default;
    Vec2(Vec2&& other) noexcept = default;
    Vec2() noexcept : x(0), y(0) {}
    Vec2(T x, T y) noexcept : x(x), y(y) { DebugAssert(!hasNaNs(), "Vec2 contains NaN"); }

    // Conversion constructors
    template<typename U>
    explicit Vec2(const Vec2<U>& other) noexcept :
        x(static_cast<T>(other.x)),
        y(static_cast<T>(other.y)) {}

    // Assignment operators
    Vec2& operator=(const Vec2& other) noexcept = default;
    Vec2& operator=(Vec2&& other) noexcept = default;

    // Logic operators
    bool operator==(const Vec2& other) const noexcept;
    bool operator!=(const Vec2& other) const noexcept;

    // Indexing operators
    T& operator[](int index) noexcept;
    const T& operator[](int index) const noexcept;

    // Arithmetic operators
    Vec2 operator+(const Vec2& other) const noexcept;
    Vec2& operator+=(const Vec2& other) noexcept;
    Vec2 operator-(const Vec2& other) const noexcept;
    Vec2& operator-=(const Vec2& other) noexcept;
    Vec2 operator*(const T& scalar) const noexcept;
    Vec2& operator*=(const T& scalar) noexcept;
    Vec2 operator/(const T& scalar) const noexcept;
    Vec2& operator/=(const T& scalar) noexcept;

	// Extra functions
    bool hasNaNs() const noexcept;
    T dot(const Vec2& other) const noexcept;
	T length() const noexcept;
	T lengthSquared() const noexcept;
	Vec2 normalized() const noexcept;
	Vec2& normalize() noexcept;
	T minComponent() const noexcept;
	T maxComponent() const noexcept;
	Vec2 negated() const noexcept;
	Vec2& negate() noexcept;

	// Common vectors
	static const Vec2<T> Zero;
	static const Vec2<T> One;
	static const Vec2<T> Up;
	static const Vec2<T> Down;
	static const Vec2<T> Left;
	static const Vec2<T> Right;
	static const Vec2<T> UnitX;
	static const Vec2<T> UnitY;
};

export {

    // 
    // Type aliases
    // 

    using Vec2i8  = Vec2<i8>;
    using Vec2i16 = Vec2<i16>;
    using Vec2i32 = Vec2<i32>;
    using Vec2i64 = Vec2<i64>;
        
    using Vec2u8  = Vec2<u8>;
    using Vec2u16 = Vec2<u16>;
    using Vec2u32 = Vec2<u32>;
    using Vec2u64 = Vec2<u64>;

    using Vec2f32 = Vec2<f32>;
    using Vec2f64 = Vec2<f64>;
    
    // 
    // Default type alias
    // 

    using Vec2i = Vec2<i32>;
    using Vec2f = Vec2<f32>;

};

// 
// Implementation
// 

template<typename T>
T& Vec2<T>::operator[](int index) noexcept {
    DebugAssert(index >= 0 && index < 2, "Index out of bounds");
    switch (index) {
    case 0: return x;
    case 1: return y;
    }
    return x; // unreachable (debug)
}

template<typename T>
const T& Vec2<T>::operator[](int index) const noexcept {
    DebugAssert(index >= 0 && index < 2, "Index out of bounds");
    switch (index) {
    case 0: return x;
    case 1: return y;
    }
    return x; // unreachable (debug)
}

template<typename T>
bool Vec2<T>::operator==(const Vec2& other) const noexcept {
    return x == other.x && y == other.y;
}

template<typename T>
bool Vec2<T>::operator!=(const Vec2& other) const noexcept {
    return !(*this == other);
}

template<typename T>
Vec2<T> Vec2<T>::operator+(const Vec2& other) const noexcept {
	DebugAssert(!other.hasNaNs(), "Vec2 contains NaN");
    return Vec2(x + other.x, y + other.y);
}

template<typename T>
Vec2<T>& Vec2<T>::operator+=(const Vec2& other) noexcept {
    DebugAssert(!other.hasNaNs(), "Vec2 contains NaN");
    x += other.x;
    y += other.y;
    return *this;
}

template<typename T>
Vec2<T> Vec2<T>::operator-(const Vec2& other) const noexcept {
    DebugAssert(!other.hasNaNs(), "Vec2 contains NaN");
    return Vec2(x - other.x, y - other.y);
}

template<typename T>
Vec2<T>& Vec2<T>::operator-=(const Vec2& other) noexcept {
    DebugAssert(!other.hasNaNs(), "Vec2 contains NaN");
    x -= other.x;
    y -= other.y;
    return *this;
}

template<typename T>
Vec2<T> Vec2<T>::operator*(const T& scalar) const noexcept {
	DebugAssert(!IsNan(scalar), "scalar is NaN");
    return Vec2(x * scalar, y * scalar);
}

template<typename T>
Vec2<T>& Vec2<T>::operator*=(const T& scalar) noexcept {
	DebugAssert(!IsNan(scalar), "scalar is NaN");
    x *= scalar;
    y *= scalar;
    return *this;
}

template<typename T>
Vec2<T> Vec2<T>::operator/(const T& scalar) const noexcept {
    DebugAssert(!IsNan(scalar), "scalar is NaN");
    DebugAssert(scalar != static_cast<T>(0), "Division by zero");
    // override for f64 (otherwise the precision is lost)
    if constexpr (std::is_same_v<T, f64>) {
        f64 inv = 1 / scalar;
        return Vec2(x * inv, y * inv);
    }
    else {
        f32 inv = 1 / scalar;
        return Vec2(x * inv, y * inv);
    }
}

template<typename T>
Vec2<T>& Vec2<T>::operator/=(const T& scalar) noexcept {
	DebugAssert(!IsNan(scalar), "scalar is NaN");
    DebugAssert(scalar != static_cast<T>(0), "Division by zero");
    // override for f64 (otherwise the precision is lost)
    if constexpr (std::is_same_v<T, f64>) {
        f64 inv = 1 / scalar;
        x *= inv;
        y *= inv;
    }
    else {
        f32 inv = 1 / scalar;
        x *= inv;
        y *= inv;
    }
    return *this;
}

template<typename T>
bool Vec2<T>::hasNaNs() const noexcept {
    return IsNan(x) || IsNan(y);
}

template<typename T>
T Vec2<T>::dot(const Vec2& other) const noexcept {
	DebugAssert(!other.hasNaNs(), "Vec2 contains NaN");
	return x * other.x + y * other.y;
}

template<typename T>
T Vec2<T>::length() const noexcept {
	return std::sqrt(lengthSquared());
}

template<typename T>
T Vec2<T>::lengthSquared() const noexcept {
	return x * x + y * y;
}

template<typename T>
Vec2<T> Vec2<T>::normalized() const noexcept {
    return (*this) / length();
}

template<typename T>
Vec2<T>& Vec2<T>::normalize() noexcept {
	*this /= length();
	return *this;
}

template<typename T>
T Vec2<T>::minComponent() const noexcept {
	return std::min(x, y);
}

template<typename T>
T Vec2<T>::maxComponent() const noexcept {
	return std::max(x, y);
}

template<typename T>
Vec2<T> Vec2<T>::negated() const noexcept {
    // override for unsigned types
    if constexpr (std::is_unsigned_v<T>) {
        return Vec2(x, y);
    }
	return Vec2(-x, -y);
}

template<typename T>
Vec2<T>& Vec2<T>::negate() noexcept {
	// override for unsigned types
	if constexpr (std::is_unsigned_v<T>) {
		return *this;
	}
	x = -x;
	y = -y;
	return *this;
}

// 
// Common vectors (implementation)
// 

template<typename T>
const Vec2<T> Vec2<T>::Zero = Vec2<T>(0, 0);
template<typename T>
const Vec2<T> Vec2<T>::One = Vec2<T>(1, 1);
template<typename T>
const Vec2<T> Vec2<T>::Up = Vec2<T>(0, 1);
template<typename T>
const Vec2<T> Vec2<T>::Down = Vec2<T>(0, -1);
template<typename T>
const Vec2<T> Vec2<T>::Left = Vec2<T>(-1, 0);
template<typename T>
const Vec2<T> Vec2<T>::Right = Vec2<T>(1, 0);
template<typename T>
const Vec2<T> Vec2<T>::UnitX = Vec2<T>(1, 0);
template<typename T>
const Vec2<T> Vec2<T>::UnitY = Vec2<T>(0, 1);
