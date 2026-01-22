#pragma once

namespace Engine::Component
{
	class BitFlag : public Component
	{	
	public:
		BitFlag() = default;

	public:
		inline void OnFlag(const unsigned long long flag) { _flag |= flag; }
		inline void OffFlag(const unsigned long long flag) { _flag &= ~flag; }
		inline void ToggleFlag(const unsigned long long flag) { _flag ^= flag; }
		inline void ResetFlag() { _flag = 0; }
		inline void SetFlag(const unsigned long long flag) { _flag = flag; }
		inline const unsigned long long IsOnFlag(const unsigned long long flag) const { return _flag & flag; }
		inline const unsigned long long GetCurrentFlag() const { return _flag; }

	private:
		unsigned long long _flag = 0;
	};
}