#include <iostream>
#include <thread>

#include <ProtocolEx.h>

//Global allocator implementation
namespace MemEx {
	ptr_t GAllocate(size_t BlockSize, size_t BlockAlignment) noexcept {
		return _aligned_malloc(BlockSize, BlockAlignment);
	}

	void GFree(ptr_t BlockPtr) noexcept {
		_aligned_free(BlockPtr);
	}
}

int main(int argc, const char** argv)
{
	if (MemEx::MemoryManager::Initialize()) {
		std::cout << "MemoryManager::Initialize() -> Failed";
		std::cin.get();
		return 1;
	}

	MemEx::MemoryManager::PrintStatistics();

	return 0;
}