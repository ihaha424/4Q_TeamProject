#include <memory>
#include "StreamBuffer.h"
#include "../GlobalDef.h"
//#include "Pools/BufferPool.h"

//StreamBuffer::StreamBuffer() : _bufferSize(bufferSize)
//{
//	//BufferPool::GetInstance()->AllocBuffer(_buffer);
//	//_bufferSize = BufferPool::GetInstance()->GetBufferSize();
//	_buffer = new char[bufferSize];
//}

StreamBuffer::StreamBuffer(unsigned long long size) : _bufferSize(size)
{
	_buffer = new char[size];
}

StreamBuffer::~StreamBuffer()
{
	//BufferPool::GetInstance()->ReleaseBuffer(_buffer);
	delete[] _buffer;
}

int StreamBuffer::Size() const
{
	return _dataSize;
}

int StreamBuffer::Space() const
{
	return _bufferSize - Size();
}

bool StreamBuffer::Empty()
{
	return _dataSize == 0;
}

bool StreamBuffer::Full()
{
	return _dataSize == _bufferSize;
}

bool StreamBuffer::Peek(char* buffer, int len) const
{
	// TODO: buffer가 가져갈 길이가 충분하면 넘겨주고, 부족하면 스킵합니다.
	if (len > Size()) return false;

	if (_readIdx < _writeIdx) {
		memcpy(buffer, &_buffer[_readIdx], len);
	}
	else {
		if (_readIdx + len < _bufferSize) {
			memcpy(buffer, &_buffer[_readIdx], len);
		}
		else {
			int back = _bufferSize - _readIdx;
			int front = len - back;
			memcpy(buffer, &_buffer[_readIdx], back);
			memcpy(&buffer[back], _buffer, front);
		}
	}
	return true;
}

int StreamBuffer::Read(char* buffer, int len)
{
	// TODO: size가 충분하면 size만큼 읽고 size를 반환합니다. 부족할 시 읽은 사이즈 만큼만 반환합니다.
	// TODO: 비어있을 시 수행하지 않습니다.
	if (Empty()) return 0;

	int readLen = (std::min)(len, Size());
	if (_readIdx < _writeIdx) {
		memcpy(buffer, &_buffer[_readIdx], readLen);
		//_readIdx += readLen;
	}
	else {
		if (_readIdx + readLen < _bufferSize) {
			memcpy(buffer, &_buffer[_readIdx], readLen);
			//_readIdx = (_readIdx + readLen) % _bufferSize;
		}
		else {
			int back = _bufferSize - _readIdx;
			int front = readLen - back;
			memcpy(buffer, &_buffer[_readIdx], back);
			memcpy(&buffer[back], _buffer, front);
			//_readIdx = front;
		}
	}

	_readIdx = (_readIdx + readLen) % _bufferSize;
	_dataSize -= readLen;

	return readLen;
}

int StreamBuffer::Write(const char* data, int len)
{
	// TODO: 공간이 부족하면 남은 공간만큼 쓰고, 쓴 길이를 반환합니다. 꽉차면 수행하지 않습니다.
	if (Full()) return 0;
	int writeSpace = Space();
	int writeLen = (std::min)(len, writeSpace);

	if (_writeIdx < _readIdx) {
		memcpy(&_buffer[_writeIdx], data, writeLen);
		//_writeIdx += writeLen;
	}
	else {
		if (_writeIdx + writeLen < _bufferSize) {
			memcpy(&_buffer[_writeIdx], data, writeLen);
			//_writeIdx = (_writeIdx + writeLen) % _bufferSize;
		}
		else {
			int back = _bufferSize - _writeIdx;
			int front = writeLen - back;
			memcpy(&_buffer[_writeIdx], data, back);
			memcpy(_buffer, &data[back], front);
			//_writeIdx = front;
		}
	}
	_writeIdx = (_writeIdx + writeLen) % _bufferSize;
	_dataSize += writeLen;

	return writeLen;
}

void StreamBuffer::BufferClear()
{
	_readIdx = _writeIdx = 0;
	_dataSize = 0;
	memset(_buffer, 0, sizeof(_buffer));
}
