#pragma once

struct vertex {
	uint8_t x, y, z, u, v;
	vertex() : x(0), y(0), z(0), u(0), v(0) { }
	vertex(uint8_t x, uint8_t y, uint8_t z, uint8_t u, uint8_t v) : x(x), y(y), z(z), u(u), v(v) { }
};

#include <memory>

#ifdef MC_DEBUG
#define MC_ENABLE_ASSERTS
#endif

#ifdef MC_ENABLE_ASSERTS
#define MC_ASSERT(x, ...) { if(!(x)) { MC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define MC_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define MC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Minecraft {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}