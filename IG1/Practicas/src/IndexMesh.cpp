#include "IndexMesh.h"


void 
IndexMesh ::load() {
    Mesh::load(); 
    glBindVertexArray (mVAO);
    glGenBuffers (1, &mIBO);
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , mIBO);
    glBufferData ( GL_ELEMENT_ARRAY_BUFFER , vIndexes.size() * sizeof(GLuint ), vIndexes.data(), GL_STATIC_DRAW );
    glBindVertexArray (0);
}

void
IndexMesh::unload()
{
    Mesh::unload();
    if (mIBO != NONE)
    {    
        glDeleteBuffers(1, &mIBO);
        mIBO = NONE;
    }
}

IndexMesh*
IndexMesh::generateByRevolution(const std::vector<glm::vec2>& profile, GLuint nSamples, GLfloat angleMax)
{
    IndexMesh * mesh = new IndexMesh ;
    mesh-> mPrimitive = GL_TRIANGLES ;
    int tamPerfil = profile.size();
    mesh-> vVertices . reserve ( nSamples * tamPerfil );
    // Genera los vértices de las muestras 
    GLdouble theta1 = angleMax / nSamples ;

    for (int i = 0; i <= nSamples; ++i) // muestra i-ésima
    {
        GLdouble c = cos(i * theta1 ), s = sin(i * theta1 );
        for (auto p : profile) // rota el perfil
            mesh-> vVertices . emplace_back (p.x * c, p.y, - p.x * s);
    }

    for (int i = 0; i < nSamples ; ++i) // caras i a i + 1
    {
        for (int j = 0; j < tamPerfil - 1; ++j) // una cara
        {
            if (profile[j].x != 0.0) // triángulo inferior
            for (auto [s, t] : {pair{i, j}, {i, j+1}, {i+1, j}})
            mesh-> vIndexes . push_back (s * tamPerfil + t);
            if (profile[j + 1].x != 0.0) // triángulo superior
            for (auto [s, t] : {pair{i, j+1}, {i+1, j+1}, {i+1, j}})
            mesh-> vIndexes . push_back (s * tamPerfil + t);
         }
    }

    mesh->buildNormalVectors();

    mesh->mNumVertices = mesh->vVertices.size();

    GLint startLastFace = mesh->mNumVertices - tamPerfil;

    for (GLint i = 0; i < tamPerfil; ++i)
    {
        mesh->vNormals[i] += mesh->vNormals[startLastFace + i];
        mesh->vNormals[i] = normalize(mesh->vNormals[i]);
        mesh->vNormals[startLastFace + i] = mesh->vNormals[i];
    }

    return mesh;
}

IndexMesh* 
IndexMesh::generateIndexedSphere(GLdouble radius, GLuint nParallels, GLuint nMeridians)
{
    vector<vec2> profile = vector<vec2>();

    GLdouble startingPoint = std::numbers::pi/2;

	GLdouble theta = std::numbers::pi / (nParallels + 1);

    for (GLuint i = 0; i < nParallels + 2; ++i)
    {
        // Resta para que sea clockwise y los triangulos se pinten en counter-clockwise
		profile.emplace_back((radius * cos(startingPoint - theta * i)), radius * sin(startingPoint- theta * i));
    }

    IndexMesh* iMesh = generateByRevolution(profile, nMeridians);

    iMesh->vNormals[0] = vec3(0., 1., 0.);
    iMesh->vNormals[profile.size() - 1] = vec3(0., -1., 0.);

    for (int i = 1; i < nMeridians + 1; ++i) 
    {
        iMesh->vNormals[i*profile.size()] = iMesh->vNormals[0]; 
        
        iMesh->vNormals[i*profile.size() + profile.size() - 1] = 
            iMesh->vNormals[profile.size() - 1];
    }

    return iMesh;
}

IndexMesh*
IndexMesh::generateIndexedTorus(GLdouble R, GLdouble r, GLuint nPoints, GLuint nSamples)
{
    vector<vec2> profile = vector<vec2>();

    GLdouble angleStep = radians(360.0) / nPoints;

    // clockwise para culling bien
    GLdouble theta = -(2.0f * std::numbers::pi) / nPoints;

    for (GLuint i = 0; i < nPoints + 1; ++i)
    {
        profile.emplace_back(R + (r * cos(theta * i)), r * sin(theta * i));
    }

    IndexMesh* iMesh = IndexMesh::generateByRevolution(profile, nSamples);

    for (int i = 0; i <= nSamples; ++i)
    {
        iMesh->vNormals[i * (nPoints+1)] += iMesh->vNormals[i * (nPoints+1) + nPoints];
        iMesh->vNormals[i * (nPoints+1)] = normalize(iMesh->vNormals[i * (nPoints+1)]);
        iMesh->vNormals[i * (nPoints+1) + nPoints] = iMesh->vNormals[i * (nPoints+1)];
    }

    return iMesh;
}

IndexMesh* 
IndexMesh::generateIndexedBox(GLdouble l)
{
    IndexMesh * mesh = new IndexMesh;
    mesh-> mPrimitive = GL_TRIANGLES;
    mesh-> vVertices.reserve(8);

    GLdouble hL = l/2;

    mesh-> mNumVertices = 8;

    mesh->vVertices = 
    {
        {hL, hL, -hL},
        {hL, -hL, -hL},
        {hL, hL, hL},
        {hL, -hL, hL},
        {-hL, hL, hL},
        {-hL, -hL, hL},
        {-hL, hL, -hL},
        {-hL, -hL, -hL}
    };

    mesh->vIndexes = 
    {
        2, 1, 0,    1, 2, 3,
        5, 3, 2,    2, 4, 5,
        4, 6, 5,    5, 6, 7,
        7, 6, 1,    0, 1, 6,
        6, 2, 0,    6, 4, 2,
        1, 3, 5,    1, 5, 7
    };

    mesh->buildNormalVectors();

    mesh->mNumVertices = 8;

    return mesh;
}

void 
IndexMesh ::draw() const
{
    glDrawElements (
        mPrimitive , // primitiva ( GL_TRIANGLES , etc.)
        vIndexes .size(), // número de índices
        GL_UNSIGNED_INT , // tipo de los índices
        nullptr // offset en el VBO de índices
    );
}

// Apartado 62
/// @brief Suma las normales de cada cara a sus vertices correspondientes y luego normaliza
void
IndexMesh::buildNormalVectors()
{
    for (int i = 0; i < vVertices.size(); ++i)
        vNormals.push_back(vec3(0, 0, 0));

    vec3 normal;

    for (int k = 0; k < vIndexes.size(); k+=3) // De 3 en tres por trata en triángulos
    {
        // Normal del triángulo
        normal = normalize(cross(vVertices[vIndexes[k+1]] - vVertices[vIndexes[k]], 
            vVertices[vIndexes[k+2]] - vVertices[vIndexes[k]]));

        vNormals[vIndexes[k]] += normal;
        vNormals[vIndexes[k+1]] += normal;
        vNormals[vIndexes[k+2]] += normal;
    }

    for (vec3& n : vNormals) n = normalize(n);
}
