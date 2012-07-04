//---------------------------------------------------------------------------
#include <windows.h>    // Header file for windows
#include <gl\gl.h>      // Header file for the OpenGL32 library
#include <gl\glu.h>     // Header file for the GLu32 library
#include <gl\glaux.h>   // Header file for the GLaux library
#include <queue.h>
#include "VertexReader.cpp"
#include "math.h"
#include "ArcBall.h"

//#pragma hdrstop

//---------------------------------------------------------------------------
//#pragma argsused


struct tImage
{
	int channels;
	int sizeX;
	int sizeY;
	unsigned char *data;
};


HGLRC hRC = NULL;               // Permanent rendering context
HDC hDC = NULL;                 // Private GDI device context
HWND hWnd = NULL;               // Holds our window handle
HINSTANCE hInstance = NULL;     // Holds the instance of the application

bool keys[256];                 // Array used for the keyboard routine
bool active = true;             // Window active flag set to true by default
bool fullscreen = true;         // Fullscreen flag set to fullscreen mode by default
bool wireframemode=true;

Vertex* verticesarray;          // List of Vertexes which describe the chainages
float rotation=45.0f;
float translatez=-2.0f;

float rotatex,rotatey,rotatez;
static int rendermode=1;

//float scalex=100.0f,scaley=15.0f,scalez=100.0f;
float scalex=30.0f,scaley=5.0f,scalez=40.0f;
vector<string> Points;
static int pointsinline;

//Textures
GLuint grasstexture,walltexture,roadtexture,darkgrasstexture;

//Lighting
GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
GLfloat specularLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat position[] = { -1.5f, 1.0f, -6.0f, 1.0f };

//Lighting
GLfloat ambientLight1[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat diffuseLight1[] = { 0.8f, 0.8f, 0.8, 1.0f };
GLfloat specularLight1[] = { 0.8f, 0.8f, 1.0f, 1.0f };
GLfloat position1[] = { -0.5f, 0.0f, -1.0f, 2.0f };


GLuint	scene; //displaylist	


// Arcball
GLUquadricObj *quadratic;											// Used For Our Quadric

const float PI2 = 2.0*3.1415926535f;								// PI Squared

Matrix4fT   Transform   = {  1.0f,  0.0f,  0.0f,  0.0f,				// NEW: Final Transform
                             0.0f,  1.0f,  0.0f,  0.0f,
                             0.0f,  0.0f,  1.0f,  0.0f,
                             0.0f,  0.0f,  0.0f,  1.0f };

Matrix3fT   LastRot     = {  1.0f,  0.0f,  0.0f,					// NEW: Last Rotation
                             0.0f,  1.0f,  0.0f,
                             0.0f,  0.0f,  1.0f };

Matrix3fT   ThisRot     = {  1.0f,  0.0f,  0.0f,					// NEW: This Rotation
                             0.0f,  1.0f,  0.0f,
                             0.0f,  0.0f,  1.0f };

ArcBallT    ArcBall(1024.0f, 768.0f);				                // NEW: ArcBall Instance
Point2fT    MousePt;												// NEW: Current Mouse Point
bool        isClicked  = false;										// NEW: Clicking The Mouse?
bool        isRClicked = false;										// NEW: Clicking The Right Mouse Button?
bool        isDragging = false;


//---------------------------------------------------------------------------
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);   // Declaration for WndProc


/////////////////////////////////////////////////////////////////////////////////////////////////
//										TEXTURE LOADER
/////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////
//										BMP LOADER
/////////////////////////////////////////////////////////////////////////////////////////////////



GLvoid Buildwireframe()
{
    scene=glGenLists(1);
    glNewList(scene,GL_COMPILE);

    //how deep we are going in ?
    int deep=Points.size()/pointsinline;

    for(int z=0;z<deep-1;z++)
    {
       //this is the starting element for this line
       int sele=z*pointsinline;

        for(int index=0;index<pointsinline-1;index++)
        {
            glBegin(GL_QUADS);

                //point 0
                glVertex3f( verticesarray[sele+index].x/scalex,
                            verticesarray[sele+index].y/scaley,
                            verticesarray[sele+index].z/scalez);			// Left And Up 1 Unit (Top Left)

                //point 1
		        glVertex3f(verticesarray[sele+1+index].x/scalex,verticesarray[sele+1+index].y/scaley,verticesarray[sele+1+index].z/scalez );			// Right And Up 1 Unit (Top Right)

                //point 2
                glVertex3f(verticesarray[sele+pointsinline+1+index].x/scalex,verticesarray[sele+pointsinline+1+index].y/scaley,verticesarray[sele+pointsinline+1+index].z/scalez);

                //point 3
                glVertex3f(verticesarray[sele+pointsinline+index].x/scalex,verticesarray[sele+pointsinline+index].y/scaley,verticesarray[sele+pointsinline+index].z/scalez);			// Right And Down One Unit (Bottom Right)

	        glEnd();
        }

    }

    glEndList();
}


GLvoid BuildTextured()
{
    scene=glGenLists(1);
    glNewList(scene,GL_COMPILE);

    //how deep we are going in ?
    int deep=Points.size()/pointsinline;

    for(int z=0;z<deep-1;z++)
    {
       float red=0.005f,green=0.205f,blue=0.005f;
       //this is the starting element for this line
       int sele=z*pointsinline;

        for(int index=0;index<pointsinline-1;index++)
        {

            if(index==0 || index==pointsinline-2)
                glBindTexture(GL_TEXTURE_2D, grasstexture);

            if(index==1 )
            {   if(verticesarray[sele+index].y>=0)
                 {
                    glBindTexture(GL_TEXTURE_2D, darkgrasstexture);
                    //glBindTexture(GL_TEXTURE_2D, grasstexture);
                 }
                 else
                 {
                    //build some quads inside this quad to make
                    //the wall a bit more realistic
                    glBindTexture(GL_TEXTURE_2D, walltexture);


                    //just draw one cube for now on the wall

                    //left extruding
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.0f, 1.0f);
                        glVertex3f(verticesarray[sele+index].x/scalex,verticesarray[sele+index].y/scaley,verticesarray[sele+index].z/scalez+0.05f);			// Left And Up 1 Unit (Top Left)

                        glTexCoord2f(1.0f, 1.0f);
                        glVertex3f(verticesarray[sele+index].x/scalex,verticesarray[sele+index].y/scaley,verticesarray[sele+index].z/scalez+0.05f );			// Right And Up 1 Unit (Top Right)

                        glTexCoord2f(1.0f, 0.0f);
                        glVertex3f(verticesarray[sele+index].x/scalex,verticesarray[sele+pointsinline+1+index].y/scaley+0.02f,verticesarray[sele+index].z/scalez+0.05f);

                        glTexCoord2f(0.0f, 0.0f);
                        glVertex3f(verticesarray[sele+index].x/scalex,verticesarray[sele+pointsinline+1+index].y/scaley+0.02f,verticesarray[sele+index].z/scalez+0.05f);
                    glEnd();
                 }
            }
            

            if( index==pointsinline-3 )
            {
                if(verticesarray[pointsinline-1+sele].y>0)
                  glBindTexture(GL_TEXTURE_2D, darkgrasstexture);
                 //glBindTexture(GL_TEXTURE_2D, grasstexture);
                else
                 glBindTexture(GL_TEXTURE_2D, walltexture);
                    //glBindTexture(GL_TEXTURE_2D, walltexture);
            }

            else if(index==pointsinline/2 || index==pointsinline/2-1)
                glBindTexture(GL_TEXTURE_2D,roadtexture);


            glBegin(GL_QUADS);

            //if y for quad 1 is <0 then make it grass cos its a fill
            //otherwise leave as rock cos its a cut

                //glTexCoord2f(0.0f, 0.0f);
                glTexCoord2f(0.0f, 1.0f);
		        glVertex3f(verticesarray[sele+index].x/scalex,verticesarray[sele+index].y/scaley,verticesarray[sele+index].z/scalez);			// Left And Up 1 Unit (Top Left)

                glTexCoord2f(1.0f, 1.0f);
                //glTexCoord2f(1.0f, 0.0f);
		        glVertex3f(verticesarray[sele+1+index].x/scalex,verticesarray[sele+1+index].y/scaley,verticesarray[sele+1+index].z/scalez );			// Right And Up 1 Unit (Top Right)

                glTexCoord2f(1.0f, 0.0f);
                //glTexCoord2f(1.0f, 1.0f);
                glVertex3f(verticesarray[sele+pointsinline+1+index].x/scalex,verticesarray[sele+pointsinline+1+index].y/scaley,verticesarray[sele+pointsinline+1+index].z/scalez);

                glTexCoord2f(0.0f, 0.0f);
                //glTexCoord2f(0.0f, 1.0f);
                glVertex3f(verticesarray[sele+pointsinline+index].x/scalex,verticesarray[sele+pointsinline+index].y/scaley,verticesarray[sele+pointsinline+index].z/scalez);			// Right And Down One Unit (Bottom Right)

	        glEnd();

            }
        }
        glEndList();
}


void TextureMode()
{

    glEnable(GL_TEXTURE_2D);                // Enable texture mapping ( NEW )
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear screen and depth buffer
    glLoadIdentity();
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT1, GL_POSITION, position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    BuildTextured();

}

void WireframeMode()
{
    //turn off lighting and texturing
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear screen and depth buffer
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);                // Enable texture mapping ( NEW )
    glDisable(GL_LIGHTING);
    Buildwireframe();
}


AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
{
	FILE *File=NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File=fopen(Filename,"r");							// Check To See If The File Exists

	if (File)
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}
	
	return NULL;										// If Load Failed Return NULL
}


GLuint LoadGLTexture( char *filename )			// Load Bitmaps And Convert To Textures
{
	AUX_RGBImageRec *pImage;							// Create Storage Space For The Texture
	GLuint texture = 0;									// Texture ID

	pImage = LoadBMP( filename );						// Loads The Bitmap Specified By filename

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if ( pImage != NULL && pImage->data != NULL )		// If Texture Image Exists
	{
		glGenTextures(1, &texture);						// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, pImage->sizeX, pImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		free(pImage->data);								// Free The Texture Image Memory
		free(pImage);									// Free The Image Structure
	}

	return texture;										// Return The Status
}


GLvoid ReSizeGLScene(GLsizei width, GLsizei height)     // Resize and initialize the GL window
{
    if (height == 0)                        // Prevent a divide by zero by
    {
				height = 1;                     // Making height equal One
    }

    glViewport(0, 0, width, height);        // Reset the current viewport

    glMatrixMode(GL_PROJECTION);            // Select the projection matrix
    glLoadIdentity();                       // Reset the projection matrix

	// Calculate the aspect ratio of the window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);             // Select the modelview matrix
	glLoadIdentity();                       // Reset the modelview matrix
}

int InitGL(GLvoid)      // All setup for OpenGL goes here
{

    walltexture=LoadGLTexture( "C:\\Wall.bmp"); // Load BMP Images
	grasstexture=LoadGLTexture( "C:\\grass.bmp");
    darkgrasstexture=LoadGLTexture("C:\\Grass.bmp");
    roadtexture=LoadGLTexture("C:\\Road.bmp");



	glShadeModel(GL_SMOOTH);                // Enable smooth shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);   // Black background
	glClearDepth(1.0f);                     // Depth buffer setup
	glEnable(GL_DEPTH_TEST);                // Enables depth testing
	glDepthFunc(GL_LEQUAL);                 // The type of depth testing to do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Really nice perspective calculations

    isClicked   = false;								            // Clicking The Mouse?
    isDragging  = false;

    WireframeMode();
    glEnable(GL_COLOR_MATERIAL);
    
	return true;                            // Initialization went OK
}

int DrawGLScene(GLvoid)         // Here's where we do all the drawing
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear screen and depth buffer
	glLoadIdentity();       // Reset t

    glTranslatef(0.0f,-0.5f,translatez);   //apply movement
    glRotatef(180.0f,1.0f,0.0f,0.0f); //so we are looking at it

    //apply rotation depending on keyboard input
    glRotatef(rotatex,1.0f,0.0f,0.0f);
    glRotatef(rotatey,0.0f,1.0f,0.0f);
    glRotatef(rotatez,0.0f,0.0f,1.0f);

     glPushMatrix();


    //call the dispaly list and draw it
    glMultMatrixf(Transform.M);
    glCallList(scene);

    glPopMatrix();

    glFlush();
    
	return true;            // Everything went OK
}

GLvoid KillGLWindow(GLvoid)     // Properly kill the window
{
	if (fullscreen)         // Are we in fullscreen mode?
	{
		ChangeDisplaySettings(NULL,0);  // If so switch back to the desktop
		ShowCursor(true);               // Show mouse pointer
	}

	if (hRC)        // Do we have a rendering context?
	{
		if (!wglMakeCurrent(NULL,NULL))         // Are we able to release the DC and RC contexts?
		{
			MessageBox(NULL,"Release of DC and RC failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))             // Are we able to delete the RC?
		{
			MessageBox(NULL,"Release rendering context failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;             // Set RC to NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))        // Are we able to release the DC
	{
		MessageBox(NULL,"Release device context failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC = NULL;             // Set DC to NULL
	}

	if (hWnd && !DestroyWindow(hWnd))       // Are we able to destroy the window?
	{
		MessageBox(NULL,"Could not release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;            // Set hWnd to NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))       // Are we able to unregister class
	{
		MessageBox(NULL,"Could not unregister class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;       // Set hInstance to NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:
 *	title			- Title To Appear At The Top Of The Window
 *	width			- Width Of The GL Window Or Fullscreen Mode
 *	height			- Height Of The GL Window Or Fullscreen Mode
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)
 *	fullscreenflag	- Use Fullscreen Mode (true) Or Windowed Mode (false)*/
 
bool CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;		// Holds the results after searching for a match
	WNDCLASS	wc;		        // Windows class structure
	DWORD		dwExStyle;              // Window extended style
	DWORD		dwStyle;                // Window style
	RECT		WindowRect;             // Grabs rctangle upper left / lower right values
	WindowRect.left = (long)0;              // Set left value to 0
	WindowRect.right = (long)width;		// Set right value to requested width
	WindowRect.top = (long)0;               // Set top value to 0
	WindowRect.bottom = (long)height;       // Set bottom value to requested height

	fullscreen = fullscreenflag;              // Set the global fullscreen flag

	hInstance               = GetModuleHandle(NULL);		// Grab an instance for our window
	wc.style                = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;   // Redraw on size, and own DC for window
	wc.lpfnWndProc          = (WNDPROC) WndProc;			// WndProc handles messages
	wc.cbClsExtra           = 0;					// No extra window data
	wc.cbWndExtra           = 0;					// No extra window data
	wc.hInstance            = hInstance;				// Set the Instance
	wc.hIcon                = LoadIcon(NULL, IDI_WINLOGO);		// Load the default icon
	wc.hCursor              = LoadCursor(NULL, IDC_ARROW);		// Load the arrow pointer
	wc.hbrBackground        = NULL;					// No background required for GL
	wc.lpszMenuName		= NULL;					// We don't want a menu
	wc.lpszClassName	= "OpenGL";				// Set the class name

	if (!RegisterClass(&wc))					// Attempt to register the window class
	{
		MessageBox(NULL,"Failed to register the window class.","Error",MB_OK|MB_ICONEXCLAMATION);

		return false;   // Return false
	}

    //Only a windowed style
    dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;           // Window extended style
    dwStyle = WS_OVERLAPPEDWINDOW;                            // Windows style

	AdjustWindowRectEx(&WindowRect,dwStyle,false,dwExStyle);        // Adjust window to true requested size

	// Create the window
	if (!(hWnd = CreateWindowEx(dwExStyle,          // Extended Style For The Window
                "OpenGL",				// Class name
		title,					// Window title
		dwStyle |				// Defined window style
		WS_CLIPSIBLINGS |			// Required window style
		WS_CLIPCHILDREN,			// Required window style
		0, 0,					// Window position
		WindowRect.right-WindowRect.left,	// Calculate window width
		WindowRect.bottom-WindowRect.top,	// Calculate window height
		NULL,					// No parent window
		NULL,					// No menu
		hInstance,				// Instance
		NULL)))					// Dont pass anything to WM_CREATE
	{
		KillGLWindow();                         // Reset the display
		MessageBox(NULL,"Window creation error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;                           // Return false
	}

	static	PIXELFORMATDESCRIPTOR pfd =             // pfd tells windows how we want things to be
	{
		sizeof(PIXELFORMATDESCRIPTOR),          // Size of this pixel format descriptor
		1,					// Version number
		PFD_DRAW_TO_WINDOW |			// Format must support window
		PFD_SUPPORT_OPENGL |			// Format must support OpenGL
		PFD_DOUBLEBUFFER,			// Must support double buffering
		PFD_TYPE_RGBA,				// Request an RGBA format
		bits,					// Select our color depth
		0, 0, 0, 0, 0, 0,			// Color bits ignored
		0,					// No alpha buffer
		0,					// Shift bit ignored
		0,					// No accumulation buffer
		0, 0, 0, 0,				// Accumulation bits ignored
		16,					// 16Bit Z-Buffer (Depth buffer)
		0,					// No stencil buffer
		0,					// No auxiliary buffer
		PFD_MAIN_PLANE,				// Main drawing layer
		0,					// Reserved
		0, 0, 0					// Layer masks ignored
	};
	
    //We need to get the device context from the frames handle
    //then maybe we can draw in the frame?

	if (!(hDC = GetDC(hWnd)))         // Did we get a device context?
    //if (!(hDC = GetDC(Frame->)))
	{
		KillGLWindow();         // Reset the display
		MessageBox(NULL,"Can't create a GL device context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;           // Return false
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC,&pfd)))	// Did windows find a matching pixel format?
	{
		KillGLWindow();         // Reset the display
		MessageBox(NULL,"Can't find a suitable pixelformat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;           // Return false
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))       // Are we able to set the pixel format?
	{
		KillGLWindow();         // Reset the display
		MessageBox(NULL,"Can't set the pixelformat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;           // Return false
	}

	if (!(hRC = wglCreateContext(hDC)))               // Are we able to get a rendering context?
	{
		KillGLWindow();         // Reset the display
		MessageBox(NULL,"Can't create a GL rendering context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;           // Return false
	}

	if(!wglMakeCurrent(hDC,hRC))    // Try to activate the rendering context
	{
		KillGLWindow();         // Reset the display
		MessageBox(NULL,"Can't activate the GL rendering context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;           // Return false
	}

	ShowWindow(hWnd,SW_SHOW);       // Show the window
	SetForegroundWindow(hWnd);      // Slightly higher priority
	SetFocus(hWnd);                 // Sets keyboard focus to the window
	ReSizeGLScene(width, height);   // Set up our perspective GL screen

	if (!InitGL())                  // Initialize our newly created GL window
	{
		KillGLWindow();         // Reset the display
		MessageBox(NULL,"Initialization failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;           // Return false
	}

	return true;                    // Success
}

LRESULT CALLBACK WndProc(HWND hWnd,     // Handle for this window
                        UINT uMsg,      // Message for this window
			WPARAM wParam,  // Additional message information
			LPARAM lParam)  // Additional message information
{
	switch (uMsg)                           // Check for windows messages
	{
		case WM_ACTIVATE:               // Watch for window activate message
		{
			if (!HIWORD(wParam))    // Check minimization state
			{
				active = true;  // Program is active
			}
			else
			{
				active = false; // Program is no longer active
			}

			return 0;               // Return to the message loop
		}

		case WM_SYSCOMMAND:             // Intercept system commands
		{
			switch (wParam)         // Check system calls
			{
				case SC_SCREENSAVE:     // Screensaver trying to start?
				case SC_MONITORPOWER:	// Monitor trying to enter powersave?
				return 0;       // Prevent from happening
			}
			break;                  // Exit
		}

		case WM_CLOSE:                  // Did we receive a close message?
		{
			PostQuitMessage(0);     // Send a quit message
			return 0;               // Jump back
		}


		case WM_KEYDOWN:                // Is a key being held down?
		{
			keys[wParam] = true;    // If so, mark it as true
			return 0;               // Jump back
		}

		case WM_KEYUP:                  // Has a key been released?
		{
			keys[wParam] = false;   // If so, mark it as false
			return 0;               // Jump back
		}

		case WM_SIZE:                   // Resize the OpenGL window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord = Width, HiWord = Height
			return 0;               // Jump back
		}

        case WM_MOUSEMOVE:
            MousePt.s.X = (GLfloat)LOWORD(lParam);
            MousePt.s.Y = (GLfloat)HIWORD(lParam);
            isClicked   = (LOWORD(wParam) & MK_LBUTTON) ? true : false;
            isRClicked  = (LOWORD(wParam) & MK_RBUTTON) ? true : false;
	}

	// Pass all unhandled messages to DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void ImportREFile()
{
    Points=LoadPointVector("C:\\REIMPORTVIEW.csv");
    verticesarray= FillStruct(Points);
}

WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //go and get the contents
    ImportREFile();

    //start the windows loop

    MSG msg;                // Windows message structure
	bool done = false;      // bool variable to exit loop
    fullscreen = false;       // Windowed mode


	// Create our OpenGL window
	if (!CreateGLWindow("Roadworks Estimator OpenGL Renderer",1024,768,16,fullscreen))
	{
		return 0;               // Quit if window was not created
	}

	while(!done)                    // Loop that runs while done = false
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is there a message waiting?
		{
			if (msg.message == WM_QUIT)             // Have we received a quit message?
			{
				done = true;                    // If so done = true
			}
			else                                    // If not, deal with window messages
			{
				TranslateMessage(&msg);         // Translate the message
				DispatchMessage(&msg);          // Dispatch the message
			}
		}
		else            // If there are no messages
		{
			// Draw the scene.  Watch for ESC key and quit messages from DrawGLScene()
			if (active)                             // Program active?
			{
                if (keys['W'] )
                {
                    translatez+=0.01f;
                }

                 if (keys['S'] )
                {
                    translatez-=0.01f;
                }

                 if (keys['A'] )
                {
                    rotatey+=0.01f;
                }

                 if (keys['D'] )
                {
                    rotatey-=0.01f;
                }

                if (keys[VK_UP] )
                {
                    rotatex+=0.025f;
                }

                if (keys[VK_DOWN] )
                {
                    rotatex-=0.025f;
                }

                if (keys[VK_LEFT] )
                {
                    rotatez+=0.1f;
                }

                if (keys[VK_RIGHT] )
                {
                    rotatez-=0.1f;
                }

                if (keys[VK_F1] )
                {
                    wireframemode=!wireframemode;
                    if(wireframemode)
                    {
                       WireframeMode();
                       Sleep(100);
                    }
                    else
                    {
                        TextureMode();
                        Sleep(100);


                    }
                }

				if (keys[VK_ESCAPE])            // Was ESC pressed?
				{
					done = true;            // ESC signalled a quit
				}
				                           // Not time to quit, Update screen


                if (isRClicked)													// If Right Mouse Clicked, Reset All Rotations
                {
		            Matrix3fSetIdentity(&LastRot);								// Reset Rotation
                    Matrix3fSetIdentity(&ThisRot);								// Reset Rotation
                    Matrix4fSetRotationFromMatrix3f(&Transform, &ThisRot);		// Reset Rotation
                }

                if (!isDragging)												// Not Dragging
                {
                    if (isClicked)												// First Click
                    {
			            isDragging = true;										// Prepare For Dragging
			            LastRot = ThisRot;										// Set Last Static Rotation To Last Dynamic One
			            ArcBall.click(&MousePt);								// Update Start Vector And Prepare For Dragging
                    }
                }


                if (isClicked)												// Still Clicked, So Still Dragging
                {
                    Quat4fT     ThisQuat;

                    ArcBall.drag(&MousePt, &ThisQuat);						// Update End Vector And Get Rotation As Quaternion
                    Matrix3fSetRotationFromQuat4f(&ThisRot, &ThisQuat);		// Convert Quaternion Into Matrix3fT
                    Matrix3fMulMatrix3f(&ThisRot, &LastRot);				// Accumulate Last Rotation Into This One
                    Matrix4fSetRotationFromMatrix3f(&Transform, &ThisRot);	// Set Our Final Transform's Rotation From This One
                }
                else														// No Longer Dragging
                    isDragging = false;


                DrawGLScene();          // Draw the scene
                SwapBuffers(hDC);       // Swap buffers (Double buffering)
            }
        }

    }

	// Shutdown
	KillGLWindow();         // Kill the window
	return (msg.wParam);    // Exit the program
}

//------------------------------------------------------------------------------------------------------
