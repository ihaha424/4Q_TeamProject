#pragma once

class PixelShader;
class Filter abstract
{
public:
	explicit Filter();
	virtual ~Filter() = default;

public:
	virtual void Initialize() = 0;
	virtual void Render() = 0;

protected:
	ID3D11DeviceContext* _pDeviceContext{ nullptr };
};