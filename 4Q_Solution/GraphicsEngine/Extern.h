#pragma once

// Common
class ResourceManager;
class CameraSystem;
class LightSystem;
class PostProcessSystem;
extern ResourceManager*		g_pResourceMgr;
extern CameraSystem*		g_pCameraSystem;
extern LightSystem*			g_pLightSystem;
extern PostProcessSystem*	g_pPostProcessSystem;
extern std::wstring			g_shaderRootPath;
extern float				g_width;
extern float				g_height;

class GraphicDevice;
class ConstantBuffer;
class StructuredBuffer;
class Sampler;
class ViewManagement;
class Quad;
class RenderGroup;

extern GraphicDevice*		g_pGraphicDevice;
extern ConstantBuffer*		g_pConstantBuffer;
extern StructuredBuffer*	g_pStructuredBuffer;
extern Sampler*				g_pSampler;
extern ViewManagement*		g_pViewManagement;
extern Quad*				g_pQuad;
extern RenderGroup*			g_pRenderGroup;