#include "Include.h"
#include "Game.h"

Game*												theGame								= NULL;
bool												keys[256]							= {false};

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);		//FWD DECL FOR WndProc


int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	DWORD t = timeGetTime();
	srand( t );

	//#ifdef _DEBUG
		RedirectIOToConsole();
		log_open(std::cout);
	//#endif
			
	bool fullscreen = true;

	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
		fullscreen=false;							// Windowed Mode

	theGame = new Game(WndProc);			//the Game now handles the memory dellocation of this window
	if(!theGame->initialize(fullscreen)) {
		return false;
	}

	MSG msg;
	while(theGame->isAlive())									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			TranslateMessage(&msg);				// Translate The Message
			DispatchMessage(&msg);				// Dispatch The Message
		}
		else										// If There Are No Messages
		{
			if(!theGame->isPaused()) {
				theGame->update();
				theGame->draw();
			}
		}
	}

	delete theGame;

	//#ifdef _DEBUG
		log_close(std::cout);
	//#endif

	return 0;
}


LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			/*
			if (!HIWORD(wParam))					// Check Minimization State
			{
				theGame->unpause();
			}
			else
			{
				theGame->pause();
			}
			*/
			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_QUIT:
		{
			theGame->kill();
			return 0;								// Jump Back
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			theGame->kill();
			return 0;								// Jump Back
		}

		//case WM_MOUSEMOVE:
		//{
		//	theGame->onMouseMove(wParam, LOWORD(lParam), HIWORD(lParam));
		//	return 0;
		//}
		case WM_MOUSEWHEEL:
		{
			theGame->onMouseScroll(GET_WHEEL_DELTA_WPARAM(wParam));

			return 0;

		}
		
		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			theGame->onKeyDown((unsigned char)wParam);
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			theGame->onKeyUp((unsigned char)wParam);			
			return 0;								// Jump Back
		}
		
		case WM_SIZE:								// Resize The OpenGL Window
		{
			theGame->getWindow()->resize(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}