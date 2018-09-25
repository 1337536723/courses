
/*********************�������ӵĿ��ļ�*******************************************************************************************/
#pragma comment(lib, "legacy_stdio_definitions.lib ")
#pragma comment( lib, "opengl32.lib" )				
#pragma comment( lib, "glu32.lib" )	
#pragma comment( lib, "glut32.lib")
#pragma comment( lib, "glew32.lib")
#pragma comment( lib, "glaux.lib")
#pragma comment( lib, "vfw32.lib" )	
/********************************************************************************************************************************/

#include <windows.h>		// Windows��ͷ�ļ�
#include "glew.h"			// �������µ�gl.h,glu.h��
//#include "glut.h"			// ����OpenGLʵ�ÿ�
/***********************************����Ĵ���***********************************************************************************/
#include	<stdio.h>		// ��׼����/������ͷ�ļ�
#include	"glaux.h"		// GLaux���ͷ�ļ�
#include	"Alpha_Beta.h"
char chInput[512];


Alpha_Beta Chess_AB;

GLfloat		xrot;			// X ��ת��
GLfloat		yrot;			// Y ��ת��
GLfloat		zrot;			// Z ��ת��

GLfloat		xrate;

#define		BLACK	1
#define		WHITE	2
#define		CHESS	0
GLuint		texture[3];		// �洢һ������
/********************************************************************************************************************************/
HDC			hDC=NULL;		// ������ɫ��������
HGLRC		hRC=NULL;		// OpenGL��Ⱦ��������
HWND		hWnd=NULL;		// �������ǵĴ��ھ��
HINSTANCE	hInstance;		// ��������ʵ��

bool	keys[256];			// ������̰���������
bool	active=TRUE;		// ���ڵĻ��־��ȱʡΪTRUE
bool	fullscreen=FALSE;	// ȫ����־ȱʡ��ȱʡ�趨��ȫ��ģʽ

GLfloat		rtri;			// ���������εĽǶ�
GLfloat		rquad;			// �����ı��εĽǶ�

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// WndProc�Ķ���
Move User_Move;
bool User_Down;





const char * szChessName = "Chess";






void GetPosition(int &x,int &y,GLfloat z)
{
	GLdouble    modelview[16];
    GLdouble    projection[16];
    GLint       viewport[4];
    glGetDoublev (GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev (GL_PROJECTION_MATRIX, projection);
    glGetIntegerv (GL_VIEWPORT, viewport);

	GLdouble world_x, world_y, world_z;
	GLdouble world_x1,world_y1,world_z1;
	gluUnProject( (GLdouble) x, (GLdouble) y, 0.0, 
                    modelview, projection, viewport, 
                    &world_x, &world_y, &world_z); 

	gluUnProject( (GLdouble) x, (GLdouble) y, 1.0, 
                    modelview, projection, viewport, 
                    &world_x1, &world_y1, &world_z1);

	x = (world_x1 - world_x) * z;
	y = (world_y1 - world_y) * z;

}










/***********************************����Ĵ���***********************************************************************************/
AUX_RGBImageRec *LoadBMP(CHAR *Filename)				// ����λͼͼ��
{
	FILE *File=NULL;									// �ļ����
	if (!Filename)										// ȷ���ļ������ṩ
	{
		return NULL;									// ���û�ṩ������ NULL
	}
	File=fopen(Filename,"r");							// ���Դ��ļ�
	if (File)											// �ļ�����ô?
	{
		fclose(File);									// �رվ��
		return auxDIBImageLoadA(Filename);				// ����λͼ������ָ��
	}
	return NULL;										// �������ʧ�ܣ����� NULL
}

int LoadGLTextures()									// ����λͼ(��������Ĵ���)��ת��������
{
	char buf_path[20] = "Data\\GoBang.bmp";
	char black_path[20] = "Data\\Black.bmp";
	char white_path[20] = "Data\\White.bmp";
	int Status=TRUE;									// ״ָ̬ʾ��
	AUX_RGBImageRec *TextureImage[3];					// ��������Ĵ洢�ռ�
	memset(TextureImage,0,sizeof(void *)*3);			// ��ָ����Ϊ NULL

	// ����λͼ��������޴������λͼû�ҵ����˳�
	
	glGenTextures(3, &texture[0]);					// ��������
	
		if(TextureImage[0]=LoadBMP(buf_path))
		{									// �� Status ��Ϊ TRUE

			// ʹ������λͼ�������� �ĵ�������
			glBindTexture(GL_TEXTURE_2D, texture[0]);
			// ��������
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);	// �����˲�
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	// �����˲�
		}
		else
			Status=FALSE;
		//////////////////////
		if(TextureImage[1] = LoadBMP(black_path))
		{
			// ʹ������λͼ�������� �ĵ�������
			glBindTexture(GL_TEXTURE_2D, texture[BLACK]);
			// ��������
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->sizeX, TextureImage[1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data);

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);	// �����˲�
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	// �����˲�
		}
		else
			Status = FALSE;
		////////////////////////////
		if(TextureImage[2] = LoadBMP(white_path))
		{
			// ʹ������λͼ�������� �ĵ�������
			glBindTexture(GL_TEXTURE_2D, texture[WHITE]);
			// ��������
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[2]->sizeX, TextureImage[2]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[2]->data);

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);	// �����˲�
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	// �����˲�
		}
		else
			Status = FALSE;

		//////
//
		//////
		if (TextureImage[0])								// �����Ƿ����
		{
			if (TextureImage[0]->data)						// ����ͼ���Ƿ����
			{
				free(TextureImage[0]->data);				// �ͷ�����ͼ��ռ�õ��ڴ�
			}
			free(TextureImage[0]);							// �ͷ�ͼ��ṹ
		}
		if (TextureImage[1])								// �����Ƿ����
		{
			if (TextureImage[1]->data)						// ����ͼ���Ƿ����
			{
				free(TextureImage[1]->data);				// �ͷ�����ͼ��ռ�õ��ڴ�
			}
			free(TextureImage[1]);							// �ͷ�ͼ��ṹ
		}
		if (TextureImage[2])								// �����Ƿ����
		{
			if (TextureImage[2]->data)						// ����ͼ���Ƿ����
			{
				free(TextureImage[2]->data);				// �ͷ�����ͼ��ռ�õ��ڴ�
			}
			free(TextureImage[2]);							// �ͷ�ͼ��ṹ
		}
	return Status;										// ���� Status
}

/********************************************************************************************************************************/
GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// ����OpenGL���ڴ�С
{
	if (height==0)										// ��ֹ�����
	{
		height=1;										// ��Height��Ϊ1
	}

	glViewport(0,0,width,height);						// ���õ�ǰ���ӿ�

	glMatrixMode(GL_PROJECTION);						// ѡ��ͶӰ����
	glLoadIdentity();									// ����ͶӰ����

	// �����ӿڵĴ�С
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// ѡ��ģ�͹۲����
	glLoadIdentity();									// ����ģ�͹۲����
}

int InitGL(GLvoid)										// �˴���ʼ��OpenGL������������
{
/***********************************����Ĵ���***********************************************************************************/
	if (!LoadGLTextures())								// ������������������
	{
		return FALSE;									// ���δ�����룬����FALSE
	}

	glEnable(GL_TEXTURE_2D);							// ��������ӳ��
/********************************************************************************************************************************/
	glShadeModel(GL_SMOOTH);							// ������Ӱƽ��
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// ��ɫ����
	glClearDepth(1.0f);									// ������Ȼ���
	glEnable(GL_DEPTH_TEST);							// ������Ȳ���
	glDepthFunc(GL_LEQUAL);								// ������Ȳ��Ե�����
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// ����ϵͳ��͸�ӽ�������

/*
	glColor4f(1.0f,1.0f,1.0f,1.0f);			// ȫ���ȣ� 50% Alpha ���
//	glBlendFunc(GL_SRC_ALPHA,GL_ONE);		// ����Դ����alphaͨ��ֵ�İ�͸����Ϻ���

	glEnable(GL_BLEND);			// �򿪻��
	glDisable(GL_DEPTH_TEST);	// �ر���Ȳ���
	*/
	return TRUE;										// ��ʼ�� OK
}
#define CSQU 0.0637f


int Chess_Board[MAX_Y + 1][MAX_X + 1] = 
{
	{}
};
#define START 0.905f
#define Graph_Position_Z (- 4.0f)
int DrawGLScene(GLvoid)									// �����￪ʼ�������еĻ���
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// �����Ļ����Ȼ���
	glLoadIdentity();									// ���õ�ǰ��ģ�͹۲����

/***********************************����Ĵ���***********************************************************************************/
	glTranslatef(0.0f,0.0f,Graph_Position_Z);									// ������Ļ 5 ����λ
	glBindTexture(GL_TEXTURE_2D, texture[0]);						// ѡ������
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// ������ı��ε�����
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// ������ı��ε�����

	glEnd();
	glTranslatef( - START,START,1.0f);
	for(int y = 1;y <= MAX_Y;y ++)
	{
		float dis = 0;
		for(int x = 1;x <= MAX_X;x ++)
		{
			if(Chess_Board[y][x])
			{
				if(Chess_Board[y][x] == BLACK)
					glBindTexture(GL_TEXTURE_2D, texture[BLACK]);
				else
					glBindTexture(GL_TEXTURE_2D, texture[WHITE]);
				glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-CSQU, -CSQU,  CSQU);	// ������ı��ε�����
					glTexCoord2f(1.0f, 0.0f); glVertex3f( CSQU, -CSQU,  CSQU);	// ������ı��ε�����
					glTexCoord2f(1.0f, 1.0f); glVertex3f( CSQU,  CSQU,  CSQU);	// ������ı��ε�����
					glTexCoord2f(0.0f, 1.0f); glVertex3f(-CSQU,  CSQU,  CSQU);	// ������ı��ε�����
				glEnd();
			}
			glTranslatef( 2 * CSQU + 0.0017,0.0f,0.0f);
			dis += 2 * CSQU + 0.0017;
		}
		glTranslatef(- dis ,- (CSQU * 2 + 0.0017),0.0f);
	}

	glTranslatef( 8.0f,0.0f,0.0f);

	glBindTexture(GL_TEXTURE_2D, texture[WHITE]);
	return TRUE;										// һ�� OK
}

GLvoid KillGLWindow(GLvoid)								// �������ٴ���
{
	if (fullscreen)										// ���Ǵ���ȫ��ģʽ��?
	{
		ChangeDisplaySettings(NULL,0);					// �ǵĻ����л�������
		ShowCursor(TRUE);								// ��ʾ���ָ��
	}

	if (hRC)											//����ӵ��OpenGL��������?
	{
		if (!wglMakeCurrent(NULL,NULL))					// �����ܷ��ͷ�DC��RC������?
		{
			MessageBox(NULL,"�ͷ�DC��RCʧ�ܡ�","�رմ���",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// �����ܷ�ɾ��RC?
		{
			MessageBox(NULL,"�ͷ�RCʧ�ܡ�","�رմ���",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// ��RC��Ϊ NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// �����ܷ��ͷ� DC?
	{
		MessageBox(NULL,"�ͷ�DCʧ�ܡ�","�رմ���",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// �� DC ��Ϊ NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// �ܷ����ٴ���?
	{
		MessageBox(NULL,"�ͷŴ��ھ��ʧ�ܡ�","�رմ���",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// �� hWnd ��Ϊ NULL
	}

	if (!UnregisterClass("OpenG",hInstance))			// �ܷ�ע����?
	{
		MessageBox(NULL,"����ע�������ࡣ","�رմ���",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// �� hInstance ��Ϊ NULL
	}
}

/*	���������������OpenGL���ڣ�����Ϊ��									*
 *	title			- ���ڱ���												*
 *	width			- ���ڿ��												*
 *	height			- ���ڸ߶�												*
 *	bits			- ��ɫ��λ�8/16/32��									*
 *	fullscreenflag	- �Ƿ�ʹ��ȫ��ģʽ��ȫ��ģʽ(TRUE)������ģʽ(FALSE)		*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// �������ƥ��Ľ��
	WNDCLASS	wc;						// ������ṹ
	DWORD		dwExStyle;				// ��չ���ڷ��
	DWORD		dwStyle;				// ���ڷ��
	RECT		WindowRect;				// ȡ�þ��ε����ϽǺ����½ǵ�����ֵ
	WindowRect.left=(long)0;			// ��Left   ��Ϊ 0
	WindowRect.right=(long)width;		// ��Right  ��ΪҪ��Ŀ��
	WindowRect.top=(long)0;				// ��Top    ��Ϊ 0
	WindowRect.bottom=(long)height;		// ��Bottom ��ΪҪ��ĸ߶�

	fullscreen=fullscreenflag;			// ����ȫ��ȫ����־

	hInstance			= GetModuleHandle(NULL);				// ȡ�����Ǵ��ڵ�ʵ��
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// �ƶ�ʱ�ػ�����Ϊ����ȡ��DC
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc������Ϣ
	wc.cbClsExtra		= 0;									// �޶��ⴰ������
	wc.cbWndExtra		= 0;									// �޶��ⴰ������
	wc.hInstance		= hInstance;							// ����ʵ��
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// װ��ȱʡͼ��
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// װ�����ָ��
	wc.hbrBackground	= NULL;									// GL����Ҫ����
	wc.lpszMenuName		= NULL;									// ����Ҫ�˵�
	wc.lpszClassName	= "OpenG";							// �趨������

	if (!RegisterClass(&wc))									// ����ע�ᴰ����
	{
		MessageBox(NULL,"ע�ᴰ��ʧ��","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// �˳�������FALSE
	}
	

	if (fullscreen)												// Ҫ����ȫ��ģʽ��?
	{
		DEVMODE dmScreenSettings;								// �豸ģʽ
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// ȷ���ڴ����Ϊ��
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Devmode �ṹ�Ĵ�С
		dmScreenSettings.dmPelsWidth	= width;				// ��ѡ��Ļ���
		dmScreenSettings.dmPelsHeight	= height;				// ��ѡ��Ļ�߶�
		dmScreenSettings.dmBitsPerPel	= bits;					// ÿ������ѡ��ɫ�����
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// ����������ʾģʽ�����ؽ����ע: CDS_FULLSCREEN ��ȥ��״̬��
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// ��ģʽʧ�ܣ��ṩ����ѡ��˳����ڴ��������С�
			if (MessageBox(NULL,"ȫ��ģʽ�ڵ�ǰ�Կ�������ʧ�ܣ�\nʹ�ô���ģʽ��","NeHe G",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				//����û�ѡ�񴰿�ģʽ������fullscreen ��ֵ��ΪFALSE,�����������
				fullscreen=FALSE;		// ѡ�񴰿�ģʽ(Fullscreen=FALSE)
			}
			else
			{
				//����û�ѡ���˳���������Ϣ���ڸ�֪�û����򽫽�����������FALSE���߳��򴰿�δ�ܳɹ������������˳���
				MessageBox(NULL,"���򽫱��ر�","����",MB_OK|MB_ICONSTOP);
				return FALSE;									// �˳������� FALSE
			}
		}
	}
	ShowCursor(TRUE);
	if (fullscreen)												// �Դ���ȫ��ģʽ��?
	{
		dwExStyle=WS_EX_APPWINDOW;								// ��չ������
		dwStyle=WS_POPUP;										// ������
											// �������ָ��
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// ��չ������
		dwStyle=WS_OVERLAPPEDWINDOW;							// ������
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// �������ڴﵽ����Ҫ��Ĵ�С


	// ��������
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// ��չ������
								"OpenG",							// ������
								title,								// ���ڱ���
								dwStyle |							// ����Ĵ���������
								WS_CLIPSIBLINGS |					// ����Ĵ���������
								WS_CLIPCHILDREN,					// ����Ĵ���������
								0, 0,								// ����λ��
								WindowRect.right-WindowRect.left,	// ��������õĴ��ڿ��
								WindowRect.bottom-WindowRect.top,	// ��������õĴ��ڸ߶�
								NULL,								// �޸�����
								NULL,								// �޲˵�
								hInstance,							// ʵ��
								NULL)))								// ����WM_CREATE�����κζ���
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"���ڴ�������","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				//pfd ���ߴ���������ϣ���Ķ�����������ʹ�õ����ظ�ʽ
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// ������ʽ�������Ĵ�С
		1,											// �汾��
		PFD_DRAW_TO_WINDOW |						// ��ʽ֧�ִ���
		PFD_SUPPORT_OPENGL |						// ��ʽ����֧��OpenGL
		PFD_DOUBLEBUFFER,							// ����֧��˫����
		PFD_TYPE_RGBA,								// ���� RGBA ��ʽ
		bits,										// ѡ��ɫ�����
		0, 0, 0, 0, 0, 0,							// ���Ե�ɫ��λ
		0,											// ��Alpha����
		0,											// ����Shift Bit
		0,											// ���ۼӻ���
		0, 0, 0, 0,									// ���Ծۼ�λ
		16,											// 16λ Z-���� (��Ȼ���) 
		0,											// ���ɰ建��
		0,											// �޸�������
		PFD_MAIN_PLANE,								// ����ͼ��
		0,											// ��ʹ���ص���
		0, 0, 0										// ���Բ�����
	};
	
	if (!(hDC=GetDC(hWnd)))							// ȡ���豸��������ô?
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"���ܴ���һ�������豸������","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Windows �ҵ���Ӧ�����ظ�ʽ����?
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"���ܴ���һ����ƥ������ظ�ʽ","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// �ܹ��������ظ�ʽô?
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"�����������ظ�ʽ","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// �ܷ�ȡ��OpenGL��Ⱦ������?
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"���ܴ���OpenGL��Ⱦ������","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// ���Լ�����ɫ������
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"���ܼ��ǰ��OpenGL��Ȼ������","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// ��ʾ����
	SetForegroundWindow(hWnd);						// ����������ȼ�
	SetFocus(hWnd);									// ���ü��̵Ľ������˴���
	ReSizeGLScene(width, height);					// ����͸�� GL ��Ļ

	if (!InitGL())									// ��ʼ���½���GL����
	{
		KillGLWindow();								// ������ʾ��
		MessageBox(NULL,"��ʼ��ʧ��","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ���� FALSE
	}

	return TRUE;									// �ɹ�
}

#define XP 177
#define YP 78

#define XPE 623 
#define YPE 524



#define MAXTIME_MS 2000
LRESULT CALLBACK WndProc(	HWND	hWnd,			// ���ڵľ��	
							UINT	uMsg,			// ���ڵ���Ϣ
							WPARAM	wParam,			// ���ӵ���Ϣ����
							LPARAM	lParam)			// ���ӵ���Ϣ����
{
	static POINT CurPoint,PointNow;
	static int cx,cy;//�������
	static RECT rect;

	switch (uMsg)									// ���Windows��Ϣ
	{
		case WM_CREATE:
		{
			cx = (XPE - XP) / (MAX_X - 1);
			cy = (YPE - YP) / (MAX_Y - 1);
			Chess_AB.Reload();
		}
		case WM_ACTIVATE:							// ���Ӵ��ڼ�����Ϣ
		{
			if (!HIWORD(wParam))					// �����С��״̬
			{
				active=TRUE;						// �����ڼ���״̬
			}
			else
			{
				active=FALSE;						// �����ټ���
			}

			return 0;								// ������Ϣѭ��
		}
		
		case WM_COMMAND:
		{
			if(WM_LBUTTONDOWN == wParam)
			{
				int y = lParam >> 8;
				int x = lParam & 0xff;
				if( x <= MAX_X && x > 0 && y <= MAX_Y && y >0 && !Chess_Board[y][x])
				{
					User_Move.x = x;
					User_Move.y = y;
					
					User_Move = Chess_AB.Search(User_Move);
					if(!Chess_Board[User_Move.y][User_Move.x])
						Chess_Board[User_Move.y][User_Move.x] = WHITE;
					
				}
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			GetCursorPos(&CurPoint);
			ScreenToClient(hWnd,&CurPoint);

			CurPoint.x -= XP;
			CurPoint.y -= YP;

			int x = CurPoint.x / cx;
			int y = CurPoint.y / cy;

			if((CurPoint.x % cx) >= (cx/2))
				x ++;
			if((CurPoint.y % cy) >= (cy/2))
				y ++;
				
			x ++;
			y ++;
			
			User_Down = true;

			User_Move.x = x;
			User_Move.y = y;

			//char chInput[512];
			sprintf(chInput, "int:%d %d\n",y,x);
			OutputDebugString(chInput);


			Chess_Board[y][x] = BLACK;
			

			if(Chess_AB.IsKill(User_Move,BLACK))
			{
				MessageBox(hWnd,"�ҹ���","��ǿ",MB_OK);
			}
			break;
		}
		case WM_SYSCOMMAND:							// ϵͳ�ж�����
		{
			switch (wParam)							// ���ϵͳ����
			{
				case SC_SCREENSAVE:					// ����Ҫ����?
				case SC_MONITORPOWER:				// ��ʾ��Ҫ����ڵ�ģʽ?
				return 0;							// ��ֹ����
			}
			break;									// �˳�
		}

		case WM_CLOSE:								// �յ�Close��Ϣ?
		{
			PostQuitMessage(0);						// �����˳���Ϣ
			return 0;								// ����
		}

		case WM_KEYDOWN:							// �м�����ô?
		{
			keys[wParam] = TRUE;					// ����ǣ���ΪTRUE
			return 0;								// ����
		}

		case WM_KEYUP:								// �м��ſ�ô?
		{
			keys[wParam] = FALSE;					// ����ǣ���ΪFALSE
			return 0;								// ����
		}

		case WM_SIZE:								// ����OpenGL���ڴ�С
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width,HiWord=Height
			GetWindowRect(hWnd,&rect);
			return 0;								// ����
		}
	}

	// �� DefWindowProc��������δ�������Ϣ��
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// ��ǰ����ʵ��
					HINSTANCE	hPrevInstance,		// ǰһ������ʵ��
					LPSTR		lpCmdLine,			// �����в���
					int			nCmdShow)			// ������ʾ״̬
{
	MSG		msg;									// Windowsx��Ϣ�ṹ
	BOOL	done=FALSE;								// �����˳�ѭ����Bool ����


	// ����OpenGL����
//	if (!CreateGLWindow("NeHe's 3Dʵ��",640,480,16,fullscreen))
/***********************************����Ĵ���***********************************************************************************/
	if (!CreateGLWindow("NeHe's ����ʵ��",800,600,16,fullscreen))
/********************************************************************************************************************************/
	{
		return 0;									// ʧ���˳�
	}

	while(!done)									// ����ѭ��ֱ�� done=TRUE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// ����Ϣ�ڵȴ���?
		{
			if (msg.message==WM_QUIT)				// �յ��˳���Ϣ?
			{
				done=TRUE;							// �ǣ���done=TRUE
			}
			else									// ���ǣ���������Ϣ
			{
				TranslateMessage(&msg);				// ������Ϣ
				DispatchMessage(&msg);				// ������Ϣ
			}
		}
		else										// ���û����Ϣ
		{

			// ���Ƴ���������ESC��������DrawGLScene()���˳���Ϣ
			if (active)								// ���򼤻��ô?
			{
				if (keys[VK_ESCAPE])				// ESC ������ô?
				{
					done=TRUE;						// ESC �����˳��ź�
				}
				else								// �����˳���ʱ��ˢ����Ļ
				{
					DrawGLScene();					// ���Ƴ���
					SwapBuffers(hDC);				// �������� (˫����)
				}
			}

			if (keys[VK_F1])						// F1��������ô?
			{
				keys[VK_F1]=FALSE;					// ���ǣ�ʹ��Ӧ��Key�����е�ֵΪ FALSE
				KillGLWindow();						// ���ٵ�ǰ�Ĵ���
				fullscreen=!fullscreen;				// �л� ȫ�� / ���� ģʽ
				// �ؽ� OpenGL ����
//				if (!CreateGLWindow("NeHe's 3Dʵ��",640,480,16,fullscreen))
/***********************************����Ĵ���***********************************************************************************/
				if (!CreateGLWindow("NeHe's ����ʵ��",640,480,16, fullscreen))
/********************************************************************************************************************************/
				{
					return 0;						// �������δ�ܴ����������˳�
				}
			}

			if (keys[VK_UP])
			{
				keys[VK_UP] = FALSE;
				xrate += 0.01;
			}
			
			
			if (User_Down)
			{
				User_Down = false;
				sprintf(chInput, "AI-before:%d %d\n", User_Move.y, User_Move.x);
				OutputDebugString(chInput);

				User_Move = Chess_AB.Search(User_Move);

				

			//	sprintf(chInput, "AI:%d %d\n", User_Move.y, User_Move.x);
			//	OutputDebugString(chInput);

				Chess_Board[User_Move.y][User_Move.x] = WHITE;

				int i;
				int j;
				int index = 0;
				for (i = 0; i < 17; i++,index++)
				{
					for (j = 0; j < 17; j++,index++)
					{
						sprintf(chInput+index, "%d\n",Chess_AB.Chess[i][j]);
					}
					sprintf(chInput + index, "\n");
				}

				//OutputDebugString(chInput);



				if(Chess_AB.IsKill(User_Move,WHITE))
				{
					MessageBox(hWnd,"�����","����",MB_OK);
				}
			}

		}
	}

	// �رճ���
	KillGLWindow();									// ���ٴ���
	return (msg.wParam);							// �˳�����
}
