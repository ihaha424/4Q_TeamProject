#pragma once
#include "PuzzleManager.h"

class MainPuzzleManager
	: public PuzzleManager
{
public:
	explicit MainPuzzleManager() : PuzzleManager() {}
	virtual ~MainPuzzleManager() = default;
	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;

	// PuzzleManager을(를) 통해 상속됨
	void SetStart(const PlayMsg::PuzzleStart* msg) override;
	void SetFinish(const PlayMsg::PuzzleStart* msg) override;
	void SetInteract(const PlayMsg::InteractObject* msg) override;
	void DataChangeCallBack(const std::wstring& name, const std::any& value) override;
};

