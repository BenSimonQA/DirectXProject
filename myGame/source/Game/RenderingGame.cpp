#include "RenderingGame.h"
#include "GameException.h"
#include "FirstPersonCamera.h"
#include "TriangleDemo.h"

#include "Keyboard.h"
#include "Mouse.h"
#include "ModelFromFile.h"
#include "FpsComponent.h"
#include "RenderStateHelper.h"
#include "ObjectDiffuseLight.h"
#include "SamplerStates.h"
#include "RasterizerStates.h"

//display score
#include <SpriteFont.h>
#include <sstream>

namespace Rendering
{;

	const XMFLOAT4 RenderingGame::BackgroundColor = { 0.75f, 0.75f, 0.75f, 1.0f };

	RenderingGame::RenderingGame(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand)
		: Game(instance, windowClass, windowTitle, showCommand),
		mDemo(nullptr), mDirectInput(nullptr), mKeyboard(nullptr), mMouse(nullptr), mModel1(nullptr),
		mFpsComponent(nullptr), mRenderStateHelper(nullptr), mObjectDiffuseLight(nullptr), mModel2(nullptr), mSpriteFont(nullptr), mSpriteBatch(nullptr), mModel3(nullptr), mModel4(nullptr), mModel5(nullptr), mModel6(nullptr), mModel7(nullptr), mModel8(nullptr), mModel9(nullptr), mModel10(nullptr), mModel11(nullptr), mModel12(nullptr), mModel13(nullptr)
    {
        mDepthStencilBufferEnabled = true;
        mMultiSamplingEnabled = true;
    }

    RenderingGame::~RenderingGame()
    {
    }

    void RenderingGame::Initialize()
    {
		
        mCamera = new FirstPersonCamera(*this);
        mComponents.push_back(mCamera);
        mServices.AddService(Camera::TypeIdClass(), mCamera);
    
        mDemo = new TriangleDemo(*this, *mCamera);
        mComponents.push_back(mDemo);

		//Remember that the component is a management class for all objects in the D3D rendering engine. 
		//It provides a centralized place to create and release objects. 
	    //NB: In C++ and other similar languages, to instantiate a class is to create an object.
		if (FAILED(DirectInput8Create(mInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&mDirectInput, nullptr)))
		{
			throw GameException("DirectInput8Create() failed");
		}

		mKeyboard = new Keyboard(*this, mDirectInput);
		mComponents.push_back(mKeyboard);
		mServices.AddService(Keyboard::TypeIdClass(), mKeyboard);

		mMouse = new Mouse(*this, mDirectInput);
		mComponents.push_back(mMouse);
		mServices.AddService(Mouse::TypeIdClass(), mMouse);

     
		
		mModel1 = new ModelFromFile(*this, *mCamera, "Content\\Models\\bench.3ds", L"A Bench",20, L"Content\\Textures\\bench.jpg");
		mModel1->SetPosition(-1.57f, -0.0f, -0.0f, 0.005f, 0.0f, 0.4f, -0.8f);
		mComponents.push_back(mModel1);

		mModel2 = new ModelFromFile(*this, *mCamera, "Content\\Models\\clock.3ds", L"A Gold Ring", 20, L"Content\\Textures\\gold.jpg");
		mModel2->SetPosition(-1.57f, -0.0f, -0.0f, 0.05f, -2.5f, 0.6f, -1.25f);
		mComponents.push_back(mModel2);

		mModel4 = new ModelFromFile(*this, *mCamera, "Content\\Models\\couch.3ds", L"A Couch", 20, L"Content\\Textures\\leather.jpg"); // couch but is using texture from bench. 
		mModel4->SetPosition(-1.57f, -0.0f, -0.0f, 0.02f, -1.5f, 0.15f, -3.0f);
		mComponents.push_back(mModel4);

		mModel5 = new ModelFromFile(*this, *mCamera, "Content\\Models\\hdtv.3ds", L"A TV", 20, L"Content\\Textures\\television.jpg"); // TV but is using texture from bench. 
		mModel5->SetPosition(-1.57f, 0.0f, -0.0f, 0.025f, 1.0f, 0.5f, -1.5f);
		mComponents.push_back(mModel5);

		mModel6 = new ModelFromFile(*this, *mCamera, "Content\\Models\\Key.3ds", L"A Key", 20, L"Content\\Textures\\gold.jpg"); // key but is using texture from bench. 
		mModel6->SetPosition(-1.57f, -0.0f, -0.0f, 0.01f, -0.3f, 1.5f, -1.8f);
		mComponents.push_back(mModel6);

		mModel7 = new ModelFromFile(*this, *mCamera, "Content\\Models\\shelf.3ds", L"A Shelf", 20, L"Content\\Textures\\wood.jpg"); // Shelf but is using texture from bench. 
		mModel7->SetPosition(0.00f, -0.0f, -1.55f, 0.005f, -2.5f, 0.6f, -3.3f);
		mComponents.push_back(mModel7);

		mModel9 = new ModelFromFile(*this, *mCamera, "Content\\Models\\Bed.3ds", L"A Bed", 20, L"Content\\Textures\\bedtexture.png"); // Bed but is using texture from bench. Model not loading up properly
		mModel9->SetPosition(-1.57f, -0.0f, -0.0f, 0.4f, 1.0f, 0.05f, -3.0f);
		mComponents.push_back(mModel9);

		mModel11 = new ModelFromFile(*this, *mCamera, "Content\\Models\\Lion.3ds", L"A Statue", 20, L"Content\\Textures\\stone.jpg");
		mModel11->SetPosition(-1.57f, -0.0f, -0.0f, 0.1f, -2.5f, 0.1f, -3.0f);
		mComponents.push_back(mModel11);

		mModel12 = new ModelFromFile(*this, *mCamera, "Content\\Models\\Vase_01.3ds", L"A Vase", 20, L"Content\\Textures\\download.jpg");
		mModel12->SetPosition(0.0f, -0.0f, -0.0f, 0.0005f, 1.5f, 0.3f, -1.5f);
		mComponents.push_back(mModel12);

		mModel13 = new ModelFromFile(*this, *mCamera, "Content\\Models\\Wind.3ds", L"A Toy Car", 20, L"Content\\Textures\\marble.jpg");
		mModel13->SetPosition(-1.5f, 1.5f, -0.0f, 0.05f, -2.5f, 0.75f, -3.2f);
		mComponents.push_back(mModel13);


		//house object with diffuse lisghting effect:
		mObjectDiffuseLight = new ObjectDiffuseLight(*this, *mCamera);
		mObjectDiffuseLight->SetPosition(-1.57f, -0.0f, -0.0f, 0.01f, -1.0f, 1.75f, -2.5f);
		mComponents.push_back(mObjectDiffuseLight);
		RasterizerStates::Initialize(mDirect3DDevice);
		SamplerStates::Initialize(mDirect3DDevice);

	
		mFpsComponent = new FpsComponent(*this);
		mFpsComponent->Initialize();
		mRenderStateHelper = new RenderStateHelper(*this);
		
		mSpriteBatch = new SpriteBatch(mDirect3DDeviceContext);
		mSpriteFont = new SpriteFont(mDirect3DDevice, L"Content\\Fonts\\Arial_14_Regular.spritefont");

		Game::Initialize();

        mCamera->SetPosition(0.0f, 1.0f, 10.0f);

		



    }

    void RenderingGame::Shutdown()
    {
		

		
		DeleteObject(mDemo);
        DeleteObject(mCamera);
		
		
		DeleteObject(mKeyboard);
		DeleteObject(mMouse);
		ReleaseObject(mDirectInput);
		
		DeleteObject(mModel1);
		DeleteObject(mModel2);
		DeleteObject(mModel4);
		DeleteObject(mModel5);
		DeleteObject(mModel6);
		DeleteObject(mModel7);
		//DeleteObject(mModel8);
		DeleteObject(mModel9);
		DeleteObject(mModel11);
		DeleteObject(mModel12);
		DeleteObject(mModel13);

		DeleteObject(mFpsComponent);
		DeleteObject(mRenderStateHelper);

		DeleteObject(mObjectDiffuseLight);

		DeleteObject(mSpriteFont);
		DeleteObject(mSpriteBatch);
		

        Game::Shutdown();
    }

    void RenderingGame::Update(const GameTime &gameTime)
    {

		mFpsComponent->Update(gameTime);
		Game::Update(gameTime);
		

		//Add "ESC" to exit the application
		if (mKeyboard->WasKeyPressedThisFrame(DIK_ESCAPE))
		{
			Exit();
		}


		//bounding box , we need to see if we need to do the picking test
		if (Game::toPick)
		{
			
			//if (mModel1->Visible())
			//Pick(Game::screenX, Game::screenY, mModel1);
	
			if (mModel2->Visible()) 
			{
				Pick(Game::screenX, Game::screenY, mModel2);
			}

			//if (mModel3->Visible())
			//	Pick(Game::screenX, Game::screenY, mModel3);
		
			//if (mModel4->Visible())
			//	Pick(Game::screenX, Game::screenY, mModel4);

			//if (mModel5->Visible())
			//	Pick(Game::screenX, Game::screenY, mModel5);

			if (mModel6->Visible())
			{
				Pick(Game::screenX, Game::screenY, mModel6);
			}
			//if (mModel7->Visible())
			//	Pick(Game::screenX, Game::screenY, mModel7);
			
			//if (mModel8->Visible())
			//	Pick(Game::screenX, Game::screenY, mModel8);
			//if (mModel9->Visible())
			//	Pick(Game::screenX, Game::screenY, mModel9);
			if (mModel11->Visible())
			{
				Pick(Game::screenX, Game::screenY, mModel11);
			}
			if (mModel12->Visible())
			{
				Pick(Game::screenX, Game::screenY, mModel12);
			}
			if (mModel13->Visible())
			{
				Pick(Game::screenX, Game::screenY, mModel13);
			}
			
			Game::toPick = false;
		}

	}


	// do the picking here

	void RenderingGame::Pick(int sx, int sy, ModelFromFile* model)
	{
		//XMMATRIX P = mCam.Proj(); 
		XMFLOAT4X4 P;
		XMStoreFloat4x4(&P, mCamera->ProjectionMatrix());


		//Compute picking ray in view space.
		float vx = (+2.0f*sx / Game::DefaultScreenWidth - 1.0f) / P(0, 0);
		float vy = (-2.0f*sy / Game::DefaultScreenHeight + 1.0f) / P(1, 1);

		// Ray definition in view space.
		XMVECTOR rayOrigin = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		XMVECTOR rayDir = XMVectorSet(vx, vy, -1.0f, 0.0f);

		// Tranform ray to local space of Mesh via the inverse of both of view and world transform
		
		XMMATRIX V = mCamera->ViewMatrix();
		XMMATRIX invView = XMMatrixInverse(&XMMatrixDeterminant(V), V);

		
		XMMATRIX W = XMLoadFloat4x4(model->WorldMatrix());
			XMMATRIX invWorld = XMMatrixInverse(&XMMatrixDeterminant(W), W);

		XMMATRIX toLocal = XMMatrixMultiply(invView, invWorld);

		rayOrigin = XMVector3TransformCoord(rayOrigin, toLocal);
		rayDir = XMVector3TransformNormal(rayDir, toLocal);

		// Make the ray direction unit length for the intersection tests.
		rayDir =  XMVector3Normalize(rayDir);

	
	
		float tmin = 0.0;
		if (model->mBoundingBox.Intersects(rayOrigin, rayDir, tmin))
		{
			std::wostringstream pickupString;
			pickupString << L"Do you want to pick up: " << (model->GetModelDes()).c_str()<<'\n'<<'\t'<<'+'<<model->ModelValue()<<L" points";
			
			int result = MessageBox(0, pickupString.str().c_str(), L"Object Found", MB_ICONASTERISK | MB_YESNO);

			if (result == IDYES)
			{ 
				model->SetVisible(false);
				//update the score
				mScore += model->ModelValue();
			}
		
		}
	}

	

    void RenderingGame::Draw(const GameTime &gameTime)
    {
        mDirect3DDeviceContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&BackgroundColor));
        mDirect3DDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

        Game::Draw(gameTime);
		mRenderStateHelper->SaveAll();
		mFpsComponent->Draw(gameTime);
		
		mSpriteBatch->Begin();
		//draw the score
		std::wostringstream scoreLabel;
		scoreLabel << L"Your current score: " << mScore << "\n";
		mSpriteFont->DrawString(mSpriteBatch, scoreLabel.str().c_str(), XMFLOAT2(0.0f, 120.0f), Colors::Red);

		std::wostringstream initItem;
		initItem << L"Items you must find:" << "\n";
		mSpriteFont->DrawString(mSpriteBatch, initItem.str().c_str(), XMFLOAT2(700.0f, 20.0f));

		std::wostringstream item1;
		item1 << L"A Gold Ring" << "\n";
		mSpriteFont->DrawString(mSpriteBatch, item1.str().c_str(), XMFLOAT2(700.0f, 40.0f));

		std::wostringstream item2;
		item2 << L"A Key" << "\n";
		mSpriteFont->DrawString(mSpriteBatch, item2.str().c_str(), XMFLOAT2(700.0f, 60.0f));

		std::wostringstream item3;
		item3 << L"A Statue" << "\n";
		mSpriteFont->DrawString(mSpriteBatch, item3.str().c_str(), XMFLOAT2(700.0f, 80.0f));

		std::wostringstream item4;
		item4 << L"A Vase" << "\n";
		mSpriteFont->DrawString(mSpriteBatch, item4.str().c_str(), XMFLOAT2(700.0f, 100.0f));

		std::wostringstream item5;
		item5 << L"A Toy Car" << "\n";
		mSpriteFont->DrawString(mSpriteBatch, item5.str().c_str(), XMFLOAT2(700.0f, 120.0f));

		if (mScore == 100)
		{
			std::wostringstream winner;
			winner << "YOU HAVE WON!" << "\n";
			mSpriteFont->DrawString(mSpriteBatch, winner.str().c_str(), XMFLOAT2(360.0f, 360.0f), Colors::Green);
			system("PAUSE");
		}

		mSpriteBatch->End();



		
		mRenderStateHelper->RestoreAll();

       
        HRESULT hr = mSwapChain->Present(0, 0);
        if (FAILED(hr))
        {
            throw GameException("IDXGISwapChain::Present() failed.", hr);
        }


		

    }
}