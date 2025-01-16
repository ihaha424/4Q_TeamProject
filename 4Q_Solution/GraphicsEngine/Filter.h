#pragma once

class Filter abstract
{
protected:
	explicit Filter();
	virtual ~Filter() = default;

public:
	virtual void InitializeOnce() = 0;
	virtual void Render(ID3D11ShaderResourceView* pSourceSRV) = 0;

protected:
	ID3D11DeviceContext* _pDeviceContext{ nullptr };
};