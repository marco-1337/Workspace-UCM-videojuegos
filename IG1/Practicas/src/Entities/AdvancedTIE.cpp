#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "AdvancedTIE.h"

#include "Sphere.h"
#include "Disk.h"
#include "Cone.h"
#include "WingAdvancedTIE.h"

using namespace glm;

AdvancedTIE::AdvancedTIE(GLdouble scale, Texture* tex) 
: CompoundEntity()
{

    Sphere* body = new Sphere(200. * scale, 20, 20);

    Cone* frontCylinder = new Cone(120. * scale, 70. * scale, 70. * scale, 20, 14);
    // Mueve y rota para que el morro mire alante
    frontCylinder->setModelMat
    (
        rotate
        (
            translate(mat4(1.0), vec3(0., 0., 230. * scale)), 
            glm::half_pi<GLfloat>(), 
            vec3(1., 0., 0.)
        )
    );

    // Mismas samples que front cylinder
    Disk* frontDisk = new Disk(70. * scale, 0., 6, 14);
    // Mueve y rota como en frontcylinder
    frontDisk->setModelMat
    (
        rotate
        (
            // Mas distancia para que quede en la punta
            translate(mat4(1.0), vec3(0., 0., 290. * scale)), 
            glm::half_pi<GLfloat>(), 
            vec3(1., 0., 0.)
        )
    );

    Cone* shaft = new Cone(800. * scale, 30. * scale, 30. * scale, 20, 12);
    shaft->setModelMat(rotate(mat4(1.0), glm::half_pi<GLfloat>(), vec3(0., 0., 1.)));

    WingAdvancedTIE* leftWing = new WingAdvancedTIE(600. * scale, 400. * scale, 100. * scale, tex);
    leftWing->setModelMat
    (
        rotate
        (
            translate(mat4(1.0), vec3(400. * scale, 0., 0.)), 
            glm::pi<GLfloat>(), 
            vec3(0., 1., 0.)
        )
    );

    WingAdvancedTIE* rightWing = new WingAdvancedTIE(600. * scale, 400. * scale, 100. * scale, tex);
    rightWing->setModelMat(translate(mat4(1.0), vec3(-400. * scale, 0., 0.)));

    body->setColor({0., 65./255., 106./255., 1.});
    frontCylinder->setColor({0., 65./255., 106./255., 1.});
    frontDisk->setColor({0., 65./255., 106./255., 1.});
    shaft->setColor({0., 65./255., 106./255., 1.});

    CompoundEntity::addEntity(body);
    CompoundEntity::addEntity(frontCylinder);
    CompoundEntity::addEntity(frontDisk);
    CompoundEntity::addEntity(shaft);
    CompoundEntity::addEntity(leftWing);
    CompoundEntity::addEntity(rightWing);
}