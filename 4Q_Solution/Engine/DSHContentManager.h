#pragma once

namespace Engine::DSHContent
{
	class Manager final : public Content::Manager
	{
		void Finalize() override;
	};
}
