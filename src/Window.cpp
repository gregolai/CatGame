#include "Include.h"
#include "Window.h"
#include "Game.h"

Window::Window(WNDPROC wndProc)
{
	mWndProc		= wndProc;
	mHwnd			= NULL;
	mHdc			= NULL;
	mHrc			= NULL;
	mHInstance		= NULL;
	mWidth			= 1;
	mHeight			= 1;
	mFullscreen		= false;
	mFovy			= MIN_FOVY;
	for(int i=0; i<16; ++i) {
		mMatrix2d[i] = (i/4 == i%4 ? 1.0f : 0);
	}
}
Window::~Window()
{

	if (mHrc)
	{
		wglMakeCurrent(NULL,NULL);
		wglDeleteContext(mHrc);
		mHrc = NULL;
	}

	if (mHdc)
	{
		ReleaseDC(mHwnd,mHdc);
		mHdc = NULL;
	}

	if (mHwnd)
	{
		DestroyWindow(mHwnd);
		mHwnd = NULL;
	}

	UnregisterClass("OpenGL", mHInstance);
	mHInstance = NULL;
}
bool Window::initialize(const char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values

	mTitle				= title;
	mWidth				= width;
	mHeight				= height;
	mBits				= bits;
	mFullscreen			= fullscreenflag;			// Set The Global Fullscreen Flag

	WindowRect.left		=(long)0;			// Set Left Value To 0
	WindowRect.right	=(long)width;		// Set Right Value To Requested Width
	WindowRect.top		=(long)0;				// Set Top Value To 0
	WindowRect.bottom	=(long)height;		// Set Bottom Value To Requested Height

	

	mHInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= mWndProc;								// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= mHInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;											// Return false
	}
	
	if (mFullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				mFullscreen=false;		// Windowed Mode Selected.  Fullscreen = false
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return false;									// Return false
			}
		}
	}

	if (mFullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(false);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(mHwnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								mHInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return false
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(mHdc=GetDC(mHwnd)))							// Did We Get A Device Context?
	{
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return false
	}

	if (!(PixelFormat=ChoosePixelFormat(mHdc,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return false
	}

	if(!SetPixelFormat(mHdc,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return false
	}

	if (!(mHrc=wglCreateContext(mHdc)))				// Are We Able To Get A Rendering Context?
	{
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return false
	}

	if(!wglMakeCurrent(mHdc,mHrc))					// Try To Activate The Rendering Context
	{
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return false
	}

	ShowWindow(mHwnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(mHwnd);						// Slightly Higher Priority
	SetFocus(mHwnd);									// Sets Keyboard Focus To The Window
	resize(width, height);					// Set Up Our Perspective GL Screen

	return true;									// Success
}

void Window::resize(int width, int height)
{
	if (height==0)										// Prevent A Divide By Zero By
		height=1;										// Making Height Equal One

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix

	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glGetFloatv(GL_PROJECTION_MATRIX, mMatrix2d);		//get the 2d projection matrix

	glLoadIdentity();									// Reset The Projection Matrix
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(mFovy,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

	RECT rc;
	GetClientRect(mHwnd, &rc);
	mWidth = rc.right - rc.left;
	mHeight = rc.bottom - rc.top;
}

void Window::start2d()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadMatrixf(mMatrix2d);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glPushAttrib( GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT );
				glDisable(GL_LIGHTING);
				glDisable(GL_DEPTH_TEST);
}

void Window::end2d()
{
			glPopAttrib();
			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	
}

void Window::drawGui3d(Texture* tex, Math::Vector3& pos, Math::Vector3& scale, Math::Degree& rotate)
{
	int width = tex->getWidth();
	int height = tex->getHeight();

	GLdouble winX, winY, winZ;
	GLdouble mv[16];
	GLdouble pj[16];
	GLint vp[4];
	glGetDoublev(GL_MODELVIEW_MATRIX, mv);
	glGetDoublev(GL_PROJECTION_MATRIX, pj);
	glGetIntegerv(GL_VIEWPORT, vp);
	gluProject(	pos.x, pos.y, pos.z, mv, pj, vp, &winX, &winY, &winZ);
	
	//if winZ is greater than 1, it means the projected point was opposite, so dont draw in this case
	if(winZ < 1) {
		glColor3f(1,1,1);
		glBindTexture(GL_TEXTURE_2D, tex->getId());

			start2d();
				glTranslatef((float)winX, (float)winY, 0);				//translate to position			
				glRotatef(rotate.getValue(), 0, 0, 1.0f);
				glScalef(scale.x, scale.y, scale.z);
				glTranslatef(-width*0.5f, -height*0.5f, 0);

				glBegin(GL_QUADS);
					glTexCoord2f(0,0);
					glVertex2i(0,0);
					glTexCoord2f(0,1.0f);
					glVertex2i(0,height);
					glTexCoord2f(1.0f,1.0f);
					glVertex2i(width, height);
					glTexCoord2f(1.0f, 0);
					glVertex2i(width,0);
				glEnd();

			end2d();

		glBindTexture(GL_TEXTURE_2D, 0);

	}
}

void Window::swapBuffers()
{
	SwapBuffers(mHdc);
}

void Window::setFovy(float newFovy)
{
	mFovy = newFovy;
	mFovy = Math::clamp<float>(mFovy, MIN_FOVY, MAX_FOVY);
	resize(mWidth, mHeight);
}

std::string& Window::getTitle()
{
	return mTitle;
}

int Window::getWidth()
{
	return mWidth;
}

int Window::getHeight()
{
	return mHeight;
}

int Window::getBits()
{
	return mBits;
}

bool Window::getFullscreen()
{
	return mFullscreen;
}

float Window::getFovy()
{
	return mFovy;
}