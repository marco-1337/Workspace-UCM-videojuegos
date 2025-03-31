#include "Shader.h"
#include "Camera.h"

#include <IG1App.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>

#include <iostream>

using namespace glm;

Camera::Camera(Viewport* vp)
  : mViewMat(1.0)
  , mProjMat(1.0)
  , xRight(vp->width() / 2.0)
  , xLeft(-xRight)
  , yTop(vp->height() / 2.0)
  , yBot(-yTop)
  , mViewPort(vp)
{
	setPM();
}

void
Camera::uploadVM() const
{
	Shader::setUniform4All("modelView", mViewMat);
}

void
Camera::setVM()
{
	mViewMat = lookAt(mEye, mLook, mUp); // glm::lookAt defines the view matrix
	setAxes();
}

void
Camera::set2D()
{
	mEye = {0, 0, 1500};
	mLook = {0, 0, 1000};
	mUp = {0, 1, 0};

	// Pone el angulo como el que da actualmente look respecto a eye con el origen
	GLfloat x = mLook.x - mEye.x;
	GLfloat z = mLook.z - mEye.z;
	mAng = degrees(glm::atan(z, x));

	// Ajusta la x y la z al angulo tal y como se haría en orbit para que esté coherente
	mEye.x = mLook.x + cos(radians(mAng));
	mEye.z = mLook.z - sin(radians(mAng));

	setVM();
}

void
Camera::set3D()
{
	mEye = {1000, 900, 1000};
	mLook = {0, 0, 0};
	mUp = {0, 1, 0};

	// Pone el angulo como el que da actualmente look respecto a eye con el origen
	mAng = -degrees(glm::atan(mEye.z, mEye.x));

	// Ajusta la x y la z al angulo tal y como se haría en orbit para que esté coherente
	mEye.x = mLook.x + cos(radians(mAng)) * mRadio;
	mEye.z = mLook.z - sin(radians(mAng)) * mRadio;

	setVM();
}

void
Camera::pitch(GLdouble a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(1.0, 0, 0));
	setAxes();
	// glm::rotate returns mViewMat * rotationMatrix
}

void
Camera::yaw(GLdouble a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 1.0, 0));
	setAxes();
	// glm::rotate returns mViewMat * rotationMatrix
}

void
Camera::roll(GLdouble a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 0, 1.0));
	setAxes();
	// glm::rotate returns mViewMat * rotationMatrix
}

void
Camera::moveLR(GLfloat cs)
{
	mEye += (normalize(mRight) * cs);
	mLook += (normalize(mRight) * cs);
	setVM();
}

void
Camera::moveFB(GLfloat cs)
{
	// ¡Hay que invertir f porque apunta al revés! 
	mEye += (normalize(mFront) * cs);
	mLook += (normalize(mFront) * cs);
	setVM();
}

void 
Camera::moveUD(GLfloat cs) 
{
	mEye += (normalize(mUpward) * cs);
	mLook += (normalize(mUpward) * cs);
	setVM();
}

void
Camera::changePrj() 
{
	bOrto = !bOrto;
	setPM();
}

// Tanto para este como para el resto hace falta actualizar tanto up como look con el giro sobre
// el eje correspondiente
// 
// si no se actualza up en pitch por ejemplo, cuando la camara apunta perpendicular al plano XZ
// Up y Forward son linealmente dependientes porque están en la misma recta por lo que
// la cámara le da un telele
void Camera::pitchReal(GLfloat cs)
{
	mat4 rot = glm::rotate(mat4(1.0), glm::radians(cs), mRight);
	mLook = dvec3(dvec4(mFront, 0.0) * rot) + mEye;
	mUp = dvec3(dvec4(mUp, 0.0) * rot);
	setVM();
}

void Camera::yawReal(GLfloat cs)
{
	mat4 rot = glm::rotate(mat4(1.0), glm::radians(cs), mUpward);
	mLook = dvec3(dvec4(mFront, 0.0) * rot) + mEye;
	mUp = dvec3(dvec4(mUp, 0.0) * rot);
	setVM();
}

void Camera::rollReal(GLfloat cs)
{
	mat4 rot = glm::rotate(mat4(1.0), glm::radians(cs), mFront);
	mLook = dvec3(dvec4(mFront, 0.0) * rot) + mEye;
	mUp = dvec3(dvec4(mUp, 0.0) * rot);
	setVM();
}

void Camera::orbit(GLdouble incAng, GLdouble incY)
{
	mAng += incAng;
	mEye.x = mLook.x + cos(radians(mAng)) * mRadio;
	mEye.z = mLook.z - sin(radians(mAng)) * mRadio;
	mEye.y += incY;
	setVM();
}

void Camera::setCenital()
{
	mEye = {0, 1000, 0};
	mLook = {0, 0, 0};
	mUp = {0, 0, -1};
	
	setVM();
}

void
Camera::setSize(GLdouble xw, GLdouble yh)
{
	xRight = xw / 2.0;
	xLeft = -xRight;
	yTop = yh / 2.0;
	yBot = -yTop;
	setPM();
}

void
Camera::setScale(GLdouble s)
{
	mScaleFact -= s;
	if (mScaleFact < 0)
		mScaleFact = 0.01;
	setPM();
}

void
Camera::setPM()
{
	if (bOrto) { //  if orthogonal projection
		mProjMat = ortho(xLeft * mScaleFact,
		                 xRight * mScaleFact,
		                 yBot * mScaleFact,
		                 yTop * mScaleFact,
		                 mNearVal,
		                 mFarVal);
		// glm::ortho defines the orthogonal projection matrix
	}
	else {
		
		GLfloat yTop = mNearVal * tan(glm::half_pi<GLfloat>() / 2.0);
		GLfloat yBot = -yTop;
		GLfloat xRight = yTop * ((GLfloat)IG1App::s_ig1app.getWinWidth()/(GLfloat)IG1App::s_ig1app.getWinHeight());
		GLfloat xLeft = -xRight;

		// Ajuste manual para que lo que está en el punto mLook se vea con la menor deformacion posible
		GLfloat ratio = mNearVal / mFront.length();

		// Las multiplicaciones afectan unicamente al marco de la matriz de proyeccion, 
		// cuando mas grande es el marco menos zoom y viceversa
		mProjMat = frustum(
			xLeft * mScaleFact * ratio,
			xRight * mScaleFact * ratio,
			yBot * mScaleFact * ratio,
			yTop * mScaleFact * ratio,
			mNearVal,
			mFarVal);
		
	}
}

void
Camera::uploadPM() const
{
	Shader::setUniform4All("projection", mProjMat);
}

void
Camera::upload() const
{
	mViewPort->upload();
	uploadVM();
	uploadPM();
}

// Apartado 38
/// @brief se asigna a cada eje la fila de la matriz de vista
void
Camera::setAxes() 
{
	mRight = row(mViewMat, 0);
	mUpward = row(mViewMat, 1);
	mFront = - row(mViewMat, 2);
}