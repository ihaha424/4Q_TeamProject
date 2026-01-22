#pragma once

namespace Engine::Utility
{
	struct HResultToString
	{
		std::string operator()(HRESULT result) const;
	};

	struct LastErrorToString
	{
		std::string operator()(DWORD error) const;
	};

	struct ThrowIfFailed
	{
		void operator()(HRESULT result) const;
		void operator()(HANDLE result, LPHANDLE pHandle) const;
		void operator()(HINSTANCE result, HINSTANCE* pInstance) const;
	};
}

