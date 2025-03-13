#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "Photo.h"

using namespace glm;

Photo::Photo(Texture* texture, GLdouble w, GLdouble h)
: EntityWithTexture(texture)
{
	mMesh = Mesh::generateRectangleTexCor(w, h);
    // Al hacer el load color se le tiene que pasar el ancho y largo de la parte de la ventana a cargar,
    // la instancia estatica de IG1App y los accesores de dimensiones de la ventana hacen que sea posible
    // independientemente del tamaño de la ventana
	mTexture->loadColorBuffer(IG1App::s_ig1app.getWinWidth(), IG1App::s_ig1app.getWinHeight());
}

Photo::~Photo()
{ }

void
Photo::update()
{
	mTexture->loadColorBuffer(IG1App::s_ig1app.getWinWidth(), IG1App::s_ig1app.getWinHeight());
}