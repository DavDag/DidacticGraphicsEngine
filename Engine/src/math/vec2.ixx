export module math.vec2;

import core;

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
    Vec2(T x, T y) noexcept : x(x), y(y) {}

    // Conversion constructors
    template<typename U>
    explicit Vec2(const Vec2<U>& other) noexcept : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

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
}

template<typename T>
const T& Vec2<T>::operator[](int index) const noexcept {
    DebugAssert(index >= 0 && index < 2, "Index out of bounds");
    switch (index) {
    case 0: return x;
    case 1: return y;
    }
}

template<typename T>
bool Vec2<T>::operator==(const Vec2& other) const noexcept {
    return x == other.x && y == other.y;
}

template<typename T>
bool Vec2<T>::operator!=(const Vec2& other) const noexcept {
    return !(*this == other);
}

// override for floating point types
template<>
bool Vec2<f32>::operator==(const Vec2& other) const noexcept {
    return std::abs(x - other.x) < 1e-5 && std::abs(y - other.y) < 1e-5;
}

template<typename T>
Vec2<T> Vec2<T>::operator+(const Vec2& other) const noexcept {
    return Vec2(x + other.x, y + other.y);
}

template<typename T>
Vec2<T>& Vec2<T>::operator+=(const Vec2& other) noexcept {
    x += other.x;
    y += other.y;
    return *this;
}

template<typename T>
Vec2<T> Vec2<T>::operator-(const Vec2& other) const noexcept {
    return Vec2(x - other.x, y - other.y);
}

template<typename T>
Vec2<T>& Vec2<T>::operator-=(const Vec2& other) noexcept {
    x -= other.x;
    y -= other.y;
    return *this;
}

template<typename T>
Vec2<T> Vec2<T>::operator*(const T& scalar) const noexcept {
    return Vec2(x * scalar, y * scalar);
}

template<typename T>
Vec2<T>& Vec2<T>::operator*=(const T& scalar) noexcept {
    x *= scalar;
    y *= scalar;
    return *this;
}

template<typename T>
Vec2<T> Vec2<T>::operator/(const T& scalar) const noexcept {
    T inv = 1 / scalar;
    return Vec2(x * inv, y * inv);
}

template<typename T>
Vec2<T>& Vec2<T>::operator/=(const T& scalar) noexcept {
    T inv = 1 / scalar;
    x *= inv;
    y *= inv;
    return *this;
}
