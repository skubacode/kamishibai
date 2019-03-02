#include<windows.h>
#include<stdio.h>

// url ref: http://www.winprog.org/tutorial/simple_window.html



const char g_szClassName[]="myWinowClass";

// Step 4 : The Window Procedure
/*
If the message loop is the heart of the program, the window procedure is the brain. 
This is where all the messages that are sent to our window get processed.
*/
/*
The window procedure is called for each message, the HWND parameter is the handle of your window, the one that the message applies to. 
This is important since you might have two or more windows of the same class and they will use the same window procedure (WndProc()). 
The difference is that the parameter hwnd will be different depending on which window it is. 
For example when we get the WM_CLOSE message we destroy the window. Since we use the window handle that we received as the first paramter, 
any other windows will not be affected, only the one that the message was intended for.
*/

/*
WM_CLOSE is sent when the user presses the Close Button  [x] or types Alt-F4. 
This will cause the window to be destroyed by default, but I like to handle it explicitly, since this is the perfect spot to do cleanup checks, 
or ask the user to save files etc. before exiting the program.

When we call DestroyWindow() the system sends the WM_DESTROY message to the window getting destroyed, in this case it's our window, 
and then destroys any remaining child windows before finally removing our window from the system. Since this is the only window in our program, 
we are all done and we want the program to exit, so we call PostQuitMessage(). This posts the WM_QUIT message to the message loop. 
We never receive this message, because it causes GetMessage() to return FALSE, and as you'll see in our message loop code, 
when that happens we stop processing messages and return the final result code, the wParam of WM_QUIT which happens to be the value we passed into 
PostQuitMessage(). The return value is only really useful if your program is designed to be called by another program and you want to return a specific value.
*/

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch(msg)
  {
   case WM_CLOSE:
        DestroyWindow(hwnd);
		break;
   case WM_DESTROY:
        PostQuitMessage(0);
		break;
   default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
  }//eo switch	  
  return 0;
}// Eo WndProc

// eo STEP 4.




/*
WINAPI is a macro that evaluates to __stdcall, a Microsoft-specific keyword that specifies a calling 
convention where the callee cleans the stack. The function's caller and callee need to agree on a calling 
convention to avoid corrupting the stack.

It's Windows-specific. It specifies the calling convention. 
WinMain gets called by Windows, and this ensures that the caller and callee agree on the calling convention.
*/
int WINAPI WinMain  /* Entry point for win32 apps */
( 
 HINSTANCE hInstance, /*handle pointer to the module (module is code loaded in memory .exe or .dll, here is used only one module 
                        and is used to load resources or somelike stuff */
 HINSTANCE hPrevInstance, /*always NULL form win32 programs win32 ignores it. It was the previous instance of the program in other execution*/
 LPSTR lpCmdLine, /* Command line arguments programe name not included */
 int nCmdShow /*integer number needed by ShowWindow() function */
)
{
 // WINAPI calling convention _stdcall
 // Win32 use some data types definitions
 // LPSTR char *
 // LPCSTR constant long pointer to string  
 // UINT unsigned int
 // ... 
 WNDCLASSEX wc;
 HWND hwnd;
 MSG msg;
 
 
 // Step 1: Register the Window Class
 // Store information about a type of window. This way you can register a class once
 // and create as many windows as you want from it without having specify those attribs over and over.
 wc.cbSize        = sizeof(WNDCLASSEX); // The size of the wc structure
 wc.style         = 0; // Class Styles (CS_*), not to be confused with Window Styles (WS_*) This can usually be set to 0.
 wc.lpfnWndProc   = WndProc; // Pointer to the window procedure for this window class.
 wc.cbClsExtra    = 0; // Amount of extra data allocated for this class in memory. Usually 0.
 wc.cbWndExtra    = 0; // Amount of extra data allocated in memory per window of this type. Usually 0.
 wc.hInstance     = hInstance; // Handle to application instance (that we got in the first parameter of WinMain()).
 wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION); // Large (usually 32x32) icon shown when the user presses Alt+Tab.
 wc.hCursor       = LoadCursor(NULL, IDC_ARROW); // Cursor that will be displayed over our window.
 wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // Background Brush to set the color of our window.
 wc.lpszMenuName  = NULL; // Name of a menu resource to use for the windows with this class.
 wc.lpszClassName = g_szClassName; // Name to identify the class with.
 wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION); // Small (usually 16x16) icon to show in the taskbar and in the top left corner of the window.
 
 if(!RegisterClassEx(&wc))
 {
  MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK );
  return 0;  
 }// Eoif
 
 // Eo Step 1.
 
 // Step 2: Creating the window
 hwnd = CreateWindowEx(
                       WS_EX_CLIENTEDGE, // the extended windows style
                       g_szClassName, // tells the system what kind of window to create
                       "The Title of my Window",
                       WS_OVERLAPPEDWINDOW, // Window Style
                       CW_USEDEFAULT, // Window position TOP LEFT X 
					   CW_USEDEFAULT, // Window position TOP LEFT Y 
					   240, 120,      // Window Size with, Window Size height
					   NULL,          // Parent Window handle
					   NULL,          // the menu handle 
					   hInstance,     // application instance handle
					   NULL			  // pointer to window creation data.Send additional data to the window that is being created( almost never use ) 
                      );
					  
 if(hwnd == NULL)
 {
  MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK); 	 
  return 0; 
 }//eoif	
 
 /*
 The nCmdShow parameter is optional, you could simply pass in SW_SHOWNORMAL all the time and be done with it. However using the 
 parameter passed into WinMain() gives whoever is running your program to specify whether or not they want your window to start off visible, 
 maximized, minimized, etc... You will find options for these in the properties of windows shortcuts, and this parameter is how the choice is carried out.
 */
 ShowWindow(hwnd, nCmdShow);
 UpdateWindow(hwnd);
 // Eo Step2.

 // Step 3: The Messge Loop
 // This is the heart of the whole program, pretty much everything that your program does passes through this point of control.
 while(GetMessage(&msg, NULL, 0, 0)> 0 ) //
 {
   /*
   GetMessage() gets a message from your application's message queue. Any time the user moves the mouse, types on the keyboard, 
   clicks on your window's menu, or does any number of other things, messages are generated by the system and entered into your program's message queue. 
   By calling GetMessage() you are requesting the next available message to be removed from the queue and returned to you for processing. 
   If there is no message, GetMessage() Blocks.
   */	 
   TranslateMessage(&msg); // does some additional processing on keyboard events like generating WM_CHAR messages to go along with WM_KEYDOWN messages.
   DispatchMessage(&msg); /*  sends the message out to the window that the message was sent to. This could be our main window or it could be another one, 
                              or a control, and in some cases a window that was created behind the scenes by the sytem or another program. 
							  This isn't something you need to worry about because all we are concerned with is that we get the message and send it out, 
                              the system takes care of the rest making sure it gets to the proper window  */
 }//eo while
 // Eo Step 3.
 
 return msg.wParam;
}// Eo WinMain