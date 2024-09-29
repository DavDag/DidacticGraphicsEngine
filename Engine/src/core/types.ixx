export module core.types;

export import std;

// 
// Integer types
// 

export using i8  = std::int8_t;
export using i16 = std::int16_t;
export using i32 = std::int32_t;
export using i64 = std::int64_t;

static_assert(sizeof(i8) == 1);
static_assert(sizeof(i16) == 2);
static_assert(sizeof(i32) == 4);
static_assert(sizeof(i64) == 8);

export constexpr i8  I8_MIN  = std::numeric_limits<i8>::min();
export constexpr i16 I16_MIN = std::numeric_limits<i16>::min();
export constexpr i32 I32_MIN = std::numeric_limits<i32>::min();
export constexpr i64 I64_MIN = std::numeric_limits<i64>::min();
export constexpr i8  I8_MAX  = std::numeric_limits<i8>::max();
export constexpr i16 I16_MAX = std::numeric_limits<i16>::max();
export constexpr i32 I32_MAX = std::numeric_limits<i32>::max();
export constexpr i64 I64_MAX = std::numeric_limits<i64>::max();

// 
// Unsigned integer types
// 

export using u8  = std::uint8_t;
export using u16 = std::uint16_t;
export using u32 = std::uint32_t;
export using u64 = std::uint64_t;

static_assert(sizeof(u8)  == 1);
static_assert(sizeof(u16) == 2);
static_assert(sizeof(u32) == 4);
static_assert(sizeof(u64) == 8);

export constexpr u8  U8_MIN  = std::numeric_limits<u8>::min();
export constexpr u16 U16_MIN = std::numeric_limits<u16>::min();
export constexpr u32 U32_MIN = std::numeric_limits<u32>::min();
export constexpr u64 U64_MIN = std::numeric_limits<u64>::min();
export constexpr u8  U8_MAX  = std::numeric_limits<u8>::max();
export constexpr u16 U16_MAX = std::numeric_limits<u16>::max();
export constexpr u32 U32_MAX = std::numeric_limits<u32>::max();
export constexpr u64 U64_MAX = std::numeric_limits<u64>::max();

// 
// Floating point types
// 

export using f32 = float;
export using f64 = double;

static_assert(sizeof(f32) == 4);
static_assert(sizeof(f64) == 8);

export constexpr f32 F32_MIN = std::numeric_limits<f32>::min();
export constexpr f64 F64_MIN = std::numeric_limits<f64>::min();
export constexpr f32 F32_MAX = std::numeric_limits<f32>::max();
export constexpr f64 F64_MAX = std::numeric_limits<f64>::max();

export constexpr f32 F32_EPSILON = 1e-5f;
export constexpr f64 F64_EPSILON = 1e-8f;

// 
// Special types
// 

export using byte = u8;
export using size = std::size_t;
