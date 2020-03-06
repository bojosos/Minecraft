#pragma once

namespace Minecraft
{
	class Memory
	{
	public:
		static void* Allocate(size_t size);

		static void Free(void* memory, size_t size);

		static size_t GetAllocated();

	private:
		Memory();
		static Memory& Get()
		{
			static Memory instance;
			return instance;
		}

		size_t m_Allocated, m_Freed;
	};
}

