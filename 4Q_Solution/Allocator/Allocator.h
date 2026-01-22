#pragma once
#include <memory>
#include <list>
#include <vector>

#define StreamInc(x, size) x = (x + 1) % size

class Allocator
{
	struct Block {
		size_t _useCount = 0;
		void* _memory = nullptr;
		unsigned short* _unUsedMemoryIndex = nullptr;
		size_t _pushIdx = 0;
		size_t _popIdx = 0;
	};

	//using MemoryChunk = std::list<Block>;
	using MemoryChunk = std::vector<Block>;

public:
	Allocator(size_t size, size_t count);
	virtual ~Allocator();

	void* Allocate();
	void DeAllocate(void* mem);

private:
	size_t _sizePerCount = 0;
	size_t _countPerChunk = 0;

	MemoryChunk _memoryChunk;
	size_t _chunkCount = 0;
	size_t _totalChunkCount = 0;

	Block& ExpandBlock();
};

