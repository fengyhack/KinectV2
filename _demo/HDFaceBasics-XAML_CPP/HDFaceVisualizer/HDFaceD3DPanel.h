//------------------------------------------------------------------------------
// <copyright file="HDFaceD3DPanel.h" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

//	This control is based on the following article: http://msdn.microsoft.com/en-us/library/windows/apps/hh825871.aspx
//	And the code here: http://code.msdn.microsoft.com/windowsapps/XAML-SwapChainPanel-00cb688b

#pragma once
#include "pch.h"
#include "DirectXPanelBase.h"
#include "StepTimer.h"
#include "ShaderStructures.h"
#include "pch.h"
#include "DirectXHelper.h"
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <math.h>
#include <ppltasks.h>
#include <windows.ui.xaml.media.dxinterop.h>

using namespace DirectX;
using namespace Concurrency;

namespace HDFaceVisualizer
{
	public value struct Vector3
	{
	public:
		float X;
		float Y;
		float Z;
	};

	public value struct DrawingVertex
	{
	public:
		Vector3 Location;
	};

    // Hosts a DirectX rendering surface that draws a spinning 3D cube using Direct3D.
    [Windows::Foundation::Metadata::WebHostHidden]
	public ref class HDFaceD3DPanel sealed : public HDFaceVisualizer::DirectXPanelBase
    {
    public:
		HDFaceD3DPanel();
		//~HDFaceD3DPanel();

        void StartRenderLoop();
        void StopRenderLoop();
		
		void UpdateMesh(Windows::Foundation::Collections::IVectorView<WindowsPreview::Kinect::CameraSpacePoint>^ newVertices, Windows::Foundation::Collections::IVectorView<UINT>^ newIndices);

    private protected:

        virtual void Render() override;
        virtual void CreateDeviceResources() override;
        virtual void CreateSizeDependentResources() override;

        Microsoft::WRL::ComPtr<IDXGIOutput>                 m_dxgiOutput;

        Microsoft::WRL::ComPtr<ID3D11RenderTargetView>      m_renderTargetView;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView>      m_depthStencilView;
        Microsoft::WRL::ComPtr<ID3D11VertexShader>          m_vertexShader;
        Microsoft::WRL::ComPtr<ID3D11PixelShader>           m_pixelShader;
        Microsoft::WRL::ComPtr<ID3D11InputLayout>           m_inputLayout;
        Microsoft::WRL::ComPtr<ID3D11Buffer>                m_vertexBuffer;
        Microsoft::WRL::ComPtr<ID3D11Buffer>                m_indexBuffer;
        Microsoft::WRL::ComPtr<ID3D11Buffer>                m_constantBuffer;

        DX::ModelViewProjectionConstantBuffer               m_constantBufferData;

		float	                                            m_degreesPerSecond;
	
        Windows::Foundation::IAsyncAction^					m_renderLoopWorker;
        // Rendering loop timer.
        DX::StepTimer                                       m_timer;

		

    private:
		~HDFaceD3DPanel();

		void CreateDXBuffers();
		void UpdateDXBuffers();

		UINT modelVerticesCount;
		DX::VertexPositionColorNormal* modelVertices;

		UINT modelIndicesCount;
		unsigned int *modelIndices;

		critical_section buffersLock;

		XMVECTOR* faceNormalsCalculationData = nullptr;
		int faceNormalsCalculationDataLength = 0;
		bool faceNormalsCalculationDataCalculated = false;
		void CalculateNormals(DX::VertexPositionColorNormal* vertices, unsigned int verticesCount, unsigned int* indices, unsigned int indicesCount);
    };
}
