#pragma once
#include "Base.h"
#include "includes/ITextSystem.h"

namespace DirectX
{
	inline namespace DX11
	{
		class SpriteBatch;
		class SpriteFont;
	}
}

class TextRenderer;
class TextSystem : public Base, public GE::ITextSystem
{
public:
	explicit TextSystem() = default;
	virtual ~TextSystem() = default;

public:
	SpriteFont* GetSpriteFont(const wchar_t* name);

public:
	// ITextSystem을(를) 통해 상속됨
	void RegisterFont(const wchar_t* name, const wchar_t* filePath) override;
	void CreateTextRenderer(GE::ITextRenderer** ppTextRenderer) override;
	void RegisterRenderQueue(GE::ITextRenderer* pTextRenderer) override;
	void UnRegisterRenderQueue(GE::ITextRenderer* pTextRenderer) override;

public:
	void Initialize();
	void Render();

private:
	void Free() override;

private:
	std::unordered_map<std::wstring, SpriteFont*> _fonts;
	std::vector<TextRenderer*> _components;
	SpriteBatch* _pSpriteBatch{ nullptr };
};

