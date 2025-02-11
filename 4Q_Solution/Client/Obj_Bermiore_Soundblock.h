#pragma once

class Obj_Bermiore_Soundblock : public InteractObject
{
public:
	Obj_Bermiore_Soundblock(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);

	void Interact() override;
	void DataChangeCallBack(const std::wstring& name, const std::any& value) override;
};