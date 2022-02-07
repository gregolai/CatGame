#ifndef WINDOW_H
#define WINDOW_H

#include "Include.h"

class Window
{
public:
	Window(WNDPROC wndProc);
	~Window();
	bool initialize(const char* title, int width, int height, int bits, bool fullscreenflag);
	void resize(int width, int height);

	void start2d();
	void end2d();
	
	void drawGui3d(Texture* tex, Math::Vector3& pos, Math::Vector3& scale, Math::Degree& rotate);
	//void drawGui2d(Texture* tex, int winX, int winY, Math::Vector3& scale, Math::Vector& rotate);

	void swapBuffers();

	void setFovy(float newFovy);

	std::string& getTitle();
	int getWidth();
	int getHeight();
	int getBits();
	bool getFullscreen();
	float getFovy();
private:
	WNDPROC			mWndProc;
	HWND			mHwnd;
	HDC				mHdc;
	HGLRC			mHrc;
	HINSTANCE		mHInstance;
	std::string		mTitle;
	int				mWidth;
	int				mHeight;
	int				mBits;
	bool			mFullscreen;
	float			mFovy;
	GLfloat			mMatrix2d[16];
};

#endif