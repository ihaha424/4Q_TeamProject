#include "pch.h"
#include "Allocator.h"
#include <cassert>

Allocator::Allocator(size_t size, size_t count) : _sizePerCount(size), _countPerChunk(count)
{
	_totalChunkCount = 10;
	_memoryChunk.resize(_totalChunkCount);
	ExpandBlock();
}

Allocator::~Allocator()
{
	for (auto& [useCount, memory, unUseContainer, push, pop] : _memoryChunk) {
		if (memory != nullptr) {
			free(memory);
		}
		if (unUseContainer != nullptr) {
			free(unUseContainer);
		}
	}
	_memoryChunk.clear();
}

void* Allocator::Allocate()
{
	void* returnMemory = nullptr;

	for (auto& [useCount, memory, unUseIdx, push, pop] : _memoryChunk) {
		if (memory == nullptr) break;
		if (useCount == _countPerChunk) continue;

		size_t memIdx = unUseIdx[pop] * _sizePerCount;
		StreamInc(pop, _countPerChunk);
		returnMemory = &((char*)(memory))[memIdx];
		useCount++;

		return returnMemory;
	}
	auto& [useCount, memory, unUseIdx, push, pop] = ExpandBlock();
	returnMemory = memory;
	useCount++;
	StreamInc(pop, _countPerChunk);

	return returnMemory;
}

void Allocator::DeAllocate(void* mem)
{
	memset(mem, 0, _sizePerCount);
	for (auto i = _memoryChunk.begin(); i != _memoryChunk.end(); i++) {
		void* curMem = (*i)._memory;
		void* nextMem = (char*)curMem + (_sizePerCount * _countPerChunk);
		if (mem >= curMem && mem < nextMem) {
			(*i)._useCount--;

			size_t idx = ((size_t)curMem - (size_t)mem) / _sizePerCount;
			(*i)._unUsedMemoryIndex[(*i)._pushIdx] = idx;
			StreamInc((*i)._pushIdx, _countPerChunk);

			return;
		}
	}
}

Allocator::Block& Allocator::ExpandBlock()
{
	size_t blockSize = _sizePerCount * _countPerChunk;
	void* memory = malloc(blockSize);
	memset(memory, 0, blockSize);

	unsigned short* idxMem = (unsigned short*)malloc(sizeof(unsigned short) * _countPerChunk);
	for (size_t i = 0; i < _countPerChunk; i++) {
		idxMem[i] = i;
	}

	if (_chunkCount == _totalChunkCount) {
		_totalChunkCount += _totalChunkCount / 2;
		_memoryChunk.resize(_totalChunkCount);
	}

	auto block = std::next(_memoryChunk.begin(), _chunkCount);
	(*block)._memory = memory;
	(*block)._unUsedMemoryIndex = idxMem;
	_chunkCount++;

	return *block;
}
