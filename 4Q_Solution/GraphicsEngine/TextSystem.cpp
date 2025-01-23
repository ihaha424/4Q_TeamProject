#include "pch.h"
#include "TextSystem.h"
#include "TextRenderer.h"

#include <directxtk/SpriteFont.h>
#include <directxtk/SpriteBatch.h>

SpriteFont* TextSystem::GetSpriteFont(const wchar_t* filePath)
{
	auto iter = _fonts.find(filePath);

	if (iter == _fonts.end())
	{
		RegisterFont(filePath);
	}

	return _fonts[filePath];
}

void TextSystem::RegisterFont(const wchar_t* filePath)
{
	SpriteFont* pFont = new SpriteFont(g_pGraphicDevice->GetDevice(), filePath);

	if (nullptr == pFont)
	{
		ASSERT(false, L"해당 Font를 로드할 수 없습니다.");
		return;
	}

	_fonts[filePath] = pFont;
}

void TextSystem::CreateTextRenderer(GE::ITextRenderer** ppTextRenderer)
{
	(*ppTextRenderer) = new TextRenderer(this);
}

void TextSystem::RegisterRenderQueue(GE::ITextRenderer* pTextRenderer)
{
	auto compare = [pTextRenderer](const auto* pComponent)
		{ return static_cast<TextRenderer*>(pTextRenderer)->GetID() == pComponent->GetID();};

	if (std::ranges::any_of(_components, compare))
	{
		ASSERT(false, L"이미 등록된 TextRenderer 입니다.");
		return;
	}

	_components.push_back(static_cast<TextRenderer*>(pTextRenderer));
}

void TextSystem::UnRegisterRenderQueue(GE::ITextRenderer* pTextRenderer)
{
	std::erase_if(_components, [pTextRenderer](const auto* pComponent)
		{ return static_cast<TextRenderer*>(pTextRenderer)->GetID() == pComponent->GetID(); });
}

void TextSystem::Initialize()
{
	_pSpriteBatch = new SpriteBatch(g_pGraphicDevice->GetDeviceContext());
}

void TextSystem::Render()
{
	_pSpriteBatch->Begin(/*SpriteSortMode_Deferred, nullptr, nullptr, nullptr, nullptr, nullptr, XMMatrixIdentity()*/);

	for (auto& component : _components)
	{
		component->Render(_pSpriteBatch);
	}

	_pSpriteBatch->End();
}

void TextSystem::Free()
{
	for (auto& font : _fonts)
		delete font.second;

	delete _pSpriteBatch;
}