////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"


SystemClass::SystemClass()
{
	m_Input = 0;
	m_Graphics = 0;
	/*m_Game = 0;*/
}


SystemClass::SystemClass(const SystemClass& other)
{
}


SystemClass::~SystemClass()
{
}


bool SystemClass::Initialize(int cntObj, int cntPoly)
{
	int screenWidth, screenHeight;
	bool result;

	// Initialize the width and height of the screen to zero before sending the variables into the function.
	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	InitializeWindows(screenWidth, screenHeight);

	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(m_hinstance, m_hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new GraphicsClass;
	if(!m_Graphics)
	{
		return false;
	}

	// Initialize the graphics object.
	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	if(!result)
	{
		return false;
	}

	//// Create the GameClass object.
	//m_Game = new GameClass;
	//if (!m_Game)
	//{
	//	return false;
	//}

	//// Initialize the GameClass object.
	//result = m_Game->Initialize();
	//if (!result)
	//{
	//	return false;
	//}
	
	// Create the fps object.
	m_Fps = new FpsClass;
	if (!m_Fps)
	{
		return false;
	}
	// Initialize the fps object.
	m_Fps->Initialize();

	// Create the cpu object.
	m_Cpu = new CpuClass;
	if (!m_Cpu)
	{
		return false;
	}
	// Initialize the cpu object.
	m_Cpu->Initialize();

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}
	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the Timer object.", L"Error", MB_OK);
		return false;
	}

	m_Obj = new ObjClass;
	if (!m_Obj) return false;

	m_Obj->Initialize(cntObj);

	m_Poly = new PolyClass;
	if (!m_Poly) return false;

	m_Poly->Initialize(cntPoly);

	m_ScreenSize = new ScreenSizeClass;
	if (!m_ScreenSize) return false;

	m_ScreenSize->Initialize(screenWidth, screenHeight);

	return true;
}


void SystemClass::Shutdown()
{
	// Release the graphics object.
	if(m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		//delete m_Input;
		//m_Input = 0;
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}
	// Release the cpu object.
	if (m_Cpu)
	{
		m_Cpu->Shutdown();
		delete m_Cpu;
		m_Cpu = 0;
	}
	// Release the fps object.
	if (m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	if (m_Obj)
	{
		delete m_Obj;
		m_Obj = 0;
	}

	if (m_Poly)
	{
		delete m_Poly;
		m_Poly = 0;
	}

	if (m_ScreenSize)
	{
		delete m_ScreenSize;
		m_ScreenSize = 0;
	}

	// Shutdown the window.
	ShutdownWindows();
	
	return;
}


void SystemClass::Run()
{
	MSG msg;
	bool done, result;


	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));
	
	// Loop until there is a quit message from the window or the user.
	done = false;
	while(!done)
	{
		// Handle the windows messages.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if(msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do the frame processing.
			result = Frame();
			if(!result)
			{
				done = true;
			}

			// Check if the user pressed escape and wants to quit.
			if (m_Input->IsEscapePressed() == true)
			{
				done = true;
			}
		}

	}

	return;
}


bool SystemClass::Frame()
{
	bool result;
	int mouseX, mouseY;
	DIMOUSESTATE mouseState;


	// Update the system stats.
	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();

	m_Obj->Frame();
	m_Poly->Frame();
	m_ScreenSize->Frame();

	// Do the input frame processing.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	if(
		m_Input->IsKeyPressed(DIK_W) || m_Input->IsKeyPressed(DIK_S) ||
		m_Input->IsKeyPressed(DIK_A) || m_Input->IsKeyPressed(DIK_D)
		)
	{
		if (m_Input->IsKeyPressed(DIK_W))
		{
			m_Graphics->MoveCameraAndChar(DIK_W);
		}
		if (m_Input->IsKeyPressed(DIK_S))
		{
			m_Graphics->MoveCameraAndChar(DIK_S);
		}
		if (m_Input->IsKeyPressed(DIK_A))
		{
			m_Graphics->MoveCameraAndChar(DIK_A);
		}
		if (m_Input->IsKeyPressed(DIK_D))
		{
			m_Graphics->MoveCameraAndChar(DIK_D);
		}

		m_Graphics->AnimCharWalk(m_Timer->GetTime());
	}

	if (m_Input->IsKeyPressed(DIK_LEFT)) m_Graphics->MovePad(DIK_LEFT, m_Timer->GetTime());
	if (m_Input->IsKeyPressed(DIK_RIGHT)) m_Graphics->MovePad(DIK_RIGHT, m_Timer->GetTime());

	m_Graphics->MovePadAI(m_Timer->GetTime());

	m_Input->GetMouseState(mouseState);
	m_Graphics->RotateCameraAndChar(mouseState.lY / 20.0f, mouseState.lX / 20.0f, mouseState.lZ / 20.0f);
	//m_Graphics->m_oldCamRot = mouseState.lX / 20.0f;

	//if (m_Input->IsKeyPressed(DIK_Z))
	//	m_Game->SetBuildType(BuildType::SCFICRATE);
	//else if (m_Input->IsKeyPressed(DIK_X))
	//	m_Game->SetBuildType(BuildType::MARKETTENT);
	//else if (m_Input->IsKeyPressed(DIK_C))
	//	m_Game->SetBuildType(BuildType::ENERGYCELL);
	//else if (m_Input->IsKeyPressed(DIK_V))
	//	m_Game->SetBuildType(BuildType::MARKETTENTADVENCED);

	// Do the frame processing for the graphics object.
	result = m_Graphics->Frame(m_hwnd, m_Fps->GetFps(), m_Cpu->GetCpuPercentage(), m_Obj->GetCntObject(), m_Poly->GetCntPolygon(),
		m_ScreenSize->GetScreenSizeX(), m_ScreenSize->GetScreenSizeY(), m_Timer->GetTime(), mouseState, m_Input->IsKeyPressed(DIK_RETURN), m_Input->IsKeyPressed(DIK_F5), m_Input->IsKeyPressed(DIK_SPACE), m_Input->IsKeyPressed(DIK_I), m_Input->IsKeyPressed(DIK_E), m_Input->IsKeyPressed(DIK_1), m_Input->IsKeyPressed(DIK_2), m_Input->IsKeyPressed(DIK_3), m_Input->IsKeyPressed(DIK_4));
	if(!result)
	{
		return false;
	}

	//if (m_Input->IsKeyPressed(DIK_R)) m_Graphics->AnimChar(m_Timer->GetTime());

	return true;
}


LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	//switch(umsg)
	//{
	//	// Check if a key has been pressed on the keyboard.
	//	case WM_KEYDOWN:
	//	{
	//		// If a key is pressed send it to the input object so it can record that state.
	//		m_Input->KeyDown((unsigned int)wparam);
	//		return 0;
	//	}

	//	// Check if a key has been released on the keyboard.
	//	case WM_KEYUP:
	//	{
	//		// If a key is released then send it to the input object so it can unset the state for that key.
	//		m_Input->KeyUp((unsigned int)wparam);
	//		return 0;
	//	}

	//	// Any other messages send to the default message handler as our application won't make use of them.
	//	default:
	//	{
	//		return DefWindowProc(hwnd, umsg, wparam, lparam);
	//	}
	//}

	return DefWindowProc(hwnd, umsg, wparam, lparam);
}


void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	// Get an external pointer to this object.	
	ApplicationHandle = this;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = L"GraduationProject v3.0";

	// Setup the windows class with default settings.
	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = m_hinstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm       = wc.hIcon;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize        = sizeof(WNDCLASSEX);
	
	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if(FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 1600x900 resolution.
		screenWidth  = 1600;
		screenHeight = 900;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, 
						    WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
						    posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(false);

	return;
}


void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if(FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}