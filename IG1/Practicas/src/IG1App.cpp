#include "IG1App.h"

#include "Scene0.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"

#include <iostream>

using namespace std;

// static single instance (singleton pattern)
IG1App IG1App::s_ig1app; // default constructor (constructor with no parameters)

// Print OpenGL errors and warnings
void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                   GLsizei length, const GLchar* message, const void* userParam)
{
	const char* prefix = (type == GL_DEBUG_TYPE_ERROR)
		? "\x1b[31m[ERROR]\x1b[0m "
		: "\x1b[33m[WARNING]\x1b[0m ";
	cout << prefix << message << endl;
}

void
IG1App::close()
{
	cout << "Closing GLFW...\n";
	glfwSetWindowShouldClose(mWindow, true); // stops main loop
}

void
IG1App::run() // enters the main event processing loop
{
	if (mWindow == 0) // if not intilialized
		init();

	// IG1App main loop
	while (!glfwWindowShouldClose(mWindow)) {
		// Redisplay the window if needed

		// Apartado 14
		if (mUpdateEnabled)
		{
			if (mNextUpdate - glfwGetTime() <= 0.0)
			{
				// Dejo esto aquí porque los update no tienen por que tener la responsabilidad
				// de actualizar el display.
				// Uno asume que como se está actualizando se requiere un refresco de lo visible por si acaso
				display();

				mNextUpdate = glfwGetTime() + FRAME_DURATION;
				mScenes[mCurrentScene]->update();			
				
				// Como este método también tiene en cuenta la recepción de eventos además del tiempo
				// es posible que la duración sea menor a la restante
				glfwWaitEventsTimeout(mNextUpdate - glfwGetTime());
			}
		}
		else
		{
			if (mNeedsRedisplay) {
				display();
				mNeedsRedisplay = false;
			}

			// Stop and wait for new events
			glfwWaitEvents();
		}

	}

	destroy();
}

void
IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// create the scene after creating the context
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH);
	mCamera = new Camera(mViewPort);
	mScenes.push_back(new Scene0);
	mScenes.push_back(new Scene1);
	mScenes.push_back(new Scene2);
	mScenes.push_back(new Scene3);

	mCamera->set2D();

	// Apartado 9
	for (Scene* s : mScenes)
	{
		s->init();
	}

	mScenes[0]->load();

	// Apartado 50
	glfwSetMouseButtonCallback(mWindow, s_mouse);
	glfwSetCursorPosCallback (mWindow, s_motion);
	glfwSetScrollCallback (mWindow, s_mouseWheel);

}

void
IG1App::iniWinOpenGL()
{ // Initialization
	cout << "Starting GLFW...\n";
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // enable on macOS

	// Create window with its associated OpenGL context, return window's pointer
	mWindow = glfwCreateWindow(mWinW, mWinH, "IG1App", nullptr, nullptr);

	if (mWindow == nullptr) {
		glfwTerminate();
		throw std::logic_error("cannot create GLFW window");
	}

	glfwMakeContextCurrent(mWindow);

	// Initialize OpenGL extension library
	if (GLenum err = glewInit(); err != GLEW_OK) {
		glfwTerminate();
		throw std::logic_error("Error while loading extensions: "s +
		                       reinterpret_cast<const char*>(glewGetErrorString(err)));
	}

	// Callback registration
	glfwSetWindowSizeCallback(mWindow, s_resize);
	glfwSetCharCallback(mWindow, s_key);
	glfwSetKeyCallback(mWindow, s_specialkey);
	glfwSetWindowRefreshCallback(mWindow, s_display);

	// Error message callback (all messages)
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0u, 0, GL_TRUE);
	glDebugMessageCallback(debugCallback, nullptr);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}

void
IG1App::destroy()
{ // release memory and resources
	for (Scene* scene : mScenes)
		delete scene;
	mScenes.clear();

	delete mCamera;
	mCamera = nullptr;
	delete mViewPort;
	mViewPort = nullptr;

	glfwTerminate();
}

void
IG1App::display() const
{ // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer

	if (m2vistas)
		display2V();
	else
		mScenes[mCurrentScene]->render(*mCamera); // uploads the viewport and camera to the GPU

	glfwSwapBuffers(mWindow); // swaps the front and back buffer
}

void
IG1App::display2V() const
{
	// para renderizar las vistas utilizamos una cámara
	// auxiliar:
	Camera auxCam = *mCamera; // copiando mCamera
	// el puerto de vista queda compartido (se copia el
	// puntero)
	// lo copiamos en una var. aux.
	Viewport auxVP = *mViewPort;
	// el tamaño de los 4 puertos de vista es el mismo,
	// lo configuramos
	mViewPort->setSize(mWinW / 2, mWinH);
	// igual que en resize, para que no cambie la escala,
	// tenemos que cambiar el tamaño de la ventana de vista
	// de la cámara
	auxCam.setSize(mViewPort->width(), mViewPort ->height());

	// Vista 3D
	mViewPort ->setPos(0, 0);
	auxCam.set3D();
	mScenes[mCurrentScene]->render(auxCam);

	// Vista cenital
	mViewPort ->setPos(mWinW / 2, 0);
	auxCam. setCenital ();
	mScenes[mCurrentScene]->render(auxCam);

	// Máquina de estados pensamiento
	*mViewPort = auxVP; // * restaurar el puerto de vista
}

void
IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth;
	mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height());
}

void
IG1App::key(unsigned int key)
{
	bool need_redisplay = true;

	switch (key) {
		case '+':
			mCamera->setScale(+0.01); // zoom in  (increases the scale)
			break;
		case '-':
			mCamera->setScale(-0.01); // zoom out (decreases the scale)
			break;
		case 'l':
			mCamera->set3D();
			break;
		case 'o':
			mCamera->set2D();
			break;
		// Apartado 12
		case 'u':
			mScenes[mCurrentScene]->update();
			break;
		case 'U':
			mUpdateEnabled = !mUpdateEnabled;
			break;
		// Apartado 40
		case 'a' :
			mCamera->moveLR(-5);
			break;
		case 'd' :
			mCamera->moveLR(5);
			break;
		case 's' :
			mCamera->moveFB(-5);
			break;
		case 'w' :
			mCamera->moveFB(5);
			break;
		case 'S' :
			mCamera->moveUD(-5);
			break;	
		case 'W' :
			mCamera->moveUD(5);
			break;	
		// Apartado 41
		case 'p' :
			mCamera->changePrj();
			break;
		case 'P' :
			mCamera->changePrj();
			break;
		// Apartado 43
		case 'm' :
			mCamera->orbit(2, 2);
			break;
		case 'M' :
			mCamera->orbit(-2, -2);
			break;
		case 'n' :
			mCamera->orbit(2, 0.0);
			break;
		case 'N' :
			mCamera->orbit(-2, 0.0);
			break;
		// Apartado 48
		case 'z' :
			mCamera->setCenital();
			break;
		// Apartado 49
		case 'k' :
			m2vistas = !m2vistas;
			break;
		default:
			if (key >= '0' && key <= '9' && !changeScene(key - '0'))
					cout << "[NOTE] There is no scene " << char(key) << ".\n";
			else
				need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		mNeedsRedisplay = true;
}

void
IG1App::specialkey(int key, int scancode, int action, int mods)
{
	// Only interested in press events
	if (action == GLFW_RELEASE)
		return;

	bool need_redisplay = true;

	// Handle keyboard input
	// (key reference: https://www.glfw.org/docs/3.4/group__keys.html)
	switch (key) {
		case GLFW_KEY_ESCAPE:                     // Escape key
			glfwSetWindowShouldClose(mWindow, true); // stops main loop
			break;
		case GLFW_KEY_RIGHT:
			if (mods == GLFW_MOD_CONTROL)
				mCamera->rollReal(-1); // rotates -1 on the Z axis
			else
				mCamera->yawReal(1); // rotates 1 on the Y axis
			break;
		case GLFW_KEY_LEFT:
			if (mods == GLFW_MOD_CONTROL)
				mCamera->rollReal(1); // rotates 1 on the Z axis
			else
				mCamera->yawReal(-1); // rotate -1 on the Y axis
			break;
		case GLFW_KEY_UP:
			mCamera->pitchReal(1); // rotates 1 on the X axis
			break;
		case GLFW_KEY_DOWN:
			mCamera->pitchReal(-1); // rotates -1 on the X axis
			break;
		default:
			need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		mNeedsRedisplay = true;
}

bool
IG1App::changeScene(size_t sceneNr)
{
	// Check whether the scene exists
	if (sceneNr >= mScenes.size())
		return false;

	// Change only if a different scene
	if (sceneNr != mCurrentScene) {
		mScenes[mCurrentScene]->unload();
		mCurrentScene = sceneNr;
		mScenes[mCurrentScene]->load();

		mNeedsRedisplay = true;
	}

	return true;
}

void 
IG1App::s_mouse( GLFWwindow * win, GLint button, GLint action, GLint mods)
{
	s_ig1app.mouse(button, action, mods);
}

void 
IG1App::s_motion( GLFWwindow * win, GLdouble x, GLdouble y)
{
	s_ig1app.motion(x, y);
}

void 
IG1App::s_mouseWheel ( GLFWwindow * win, GLdouble dx, GLdouble dy)
{
	s_ig1app.mouseWheel(dx, dy);
}

void 
IG1App::mouse( GLint button, GLint action, GLint mods)
{
	if (mMouseButt == button)
		mMouseButt = -1;
	else 
		mMouseButt = button;
	std::cout << button << "\n";

	glfwGetCursorPos(mWindow, &mMouseCoord.x, &mMouseCoord.y);

	GLint height;
	glfwGetWindowSize (mWindow, nullptr, &height);
	mMouseCoord.y = height - mMouseCoord.y;
}

void 
IG1App::motion( GLdouble x, GLdouble y)
{
	glm::dvec2 mp;
	glfwGetCursorPos(mWindow, &mp.x, &mp.y);

	GLint height;
	glfwGetWindowSize (mWindow, nullptr, &height);
	mp.y = height - mp.y;
	glm::dvec2 a_mCoord = mp;

	mp -= mMouseCoord;

	mMouseCoord = a_mCoord;

	if (mMouseButt ==  GLFW_MOUSE_BUTTON_LEFT)
	{
		mCamera->orbit(-mp.x * 0.1, -mp.y * 2);
	}
	else if (mMouseButt ==  GLFW_MOUSE_BUTTON_RIGHT)
	{
		mCamera->moveLR(-mp.x);
		mCamera->moveUD(-mp.y);
	}

	mNeedsRedisplay = true;
}

void 
IG1App::mouseWheel ( GLdouble dx, GLdouble dy )
{
	std::cout << dx << " " << dy << "\n";
	if (glfwGetKey(mWindow, GLFW_MOD_CONTROL) == GLFW_PRESS)
		mCamera->setScale(dy*10);
	else 
		mCamera->moveFB(dy*10);

	mNeedsRedisplay = true;
}