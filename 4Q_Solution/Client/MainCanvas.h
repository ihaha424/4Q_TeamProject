#pragma once

class MainCanvas : public Engine::Canvas
{
public:
	MainCanvas();
	explicit MainCanvas(const Engine::Math::Size& viewportSize);
};