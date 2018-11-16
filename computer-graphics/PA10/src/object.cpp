#include "object.h"
Object::Object(std::string filename, int shape, bool needsLoading, float s_x, float s_y, float s_z, int flip)
{

  scale_x = s_x;
  scale_y = s_y;
  scale_z = s_z;

  flipper = flip;
  flipping = false;

	if(needsLoading)
	{

	 //File Path to find object name
		m_objDirectory = "../assets/objects/";
		m_textDirectory = "../assets/textures/";

		m_objDirectory.append(filename);

	 //Assimp object loading

	 //Create our importer which reads the file for us, thank god
		Assimp::Importer importer;


		//Reading the file in one line, bless
		m_scene = importer.ReadFile(m_objDirectory, aiProcess_Triangulate);

		//This is the same process of constructing the vertices and indices that we did when we
		//were writing our own object loader

		InitMesh();

	}

  m_shape = shape;

  switch(shape)
	{
		case 1:
			m_collisionShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
			break;
		case 2:
			m_collisionShape = new btSphereShape(.13);
			break;
		case 3:
			m_collisionShape = new btCylinderShape(btVector3(.24, .24, .24));
			break;
		case 4:
			m_collisionShape = new btBoxShape(btVector3(.13, .13, .4));
			break;
		case 5:
			m_collisionShape = new btStaticPlaneShape(btVector3(0, 0, -1), 0);
			break;
		case 6:
			m_collisionShape = new btStaticPlaneShape(btVector3(0, 0, 1), 0);
			break;
		case 7:
			m_collisionShape = new btStaticPlaneShape(btVector3(-1, 0, 0), 0);
			break;
		case 8:
			m_collisionShape = new btStaticPlaneShape(btVector3(0, -1, 0), 0);
			break;
	  case 9:
      m_collisionShape = new btBvhTriangleMeshShape(m_btTriangleObject, true);
	    break;
		default:
			break;
	}

}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

//Update the object's model using all of its unique values
void Object::Update(unsigned int dt, glm::mat4 origin, float scale)
{
   // model = glm::translate(origin, glm::vec3(0, 0, 0));
    //model = glm::scale(model, glm::vec3(.5, .5, .5));

    //Physics objects update
    if(m_physics) {
      btTransform trans;
      btScalar m[16];
      m_rigidBody->getMotionState()->getWorldTransform(trans);

      //flipping the flippers
      if(flipper == 1) //left flipper
      {
          if(flipping)
          {
            //if max flippage has not been reached
            if(trans.getRotation().getY() < .4)
            {
              btQuaternion newQuat = trans.getRotation() + btQuaternion(0.0, .1, 0.0, 0);
              trans.setRotation(newQuat);
              m_rigidBody->getMotionState()->setWorldTransform(trans);
            }

          }
          else
          {
            //if min flippage has not been reached
            if( trans.getRotation().getY() > -0.155176)
            {
              btQuaternion newQuat = trans.getRotation() - btQuaternion(0.0, .1, 0.0, 0);
              trans.setRotation(newQuat);
              m_rigidBody->getMotionState()->setWorldTransform(trans);
            }
            else{
              btQuaternion newQuat = btQuaternion(0.0, (-M_PI / 20), 0.0, 1);
              trans.setRotation(newQuat);
              m_rigidBody->getMotionState()->setWorldTransform(trans);
            }

          }

      }
      else if(flipper == 2) //right flipper
        {
          if (flipping) {
            //if max flippage has not been reached
            if (trans.getRotation().getY() > -.4) {
              btQuaternion newQuat = trans.getRotation() - btQuaternion(0.0, .1, 0.0, 0);
              trans.setRotation(newQuat);
              m_rigidBody->getMotionState()->setWorldTransform(trans);
            }

          }
          else {
            //if min flippage has not been reached
            if (trans.getRotation().getY() < 0.155176) {
              btQuaternion newQuat = trans.getRotation() + btQuaternion(0.0, .1, 0.0, 0);
              trans.setRotation(newQuat);
              m_rigidBody->getMotionState()->setWorldTransform(trans);
            }
            else{
              btQuaternion newQuat = btQuaternion(0.0, (M_PI / 20), 0.0, 1);
              trans.setRotation(newQuat);
              m_rigidBody->getMotionState()->setWorldTransform(trans);
            }
          }
        }

        //rest of physics object update
      trans.getOpenGLMatrix(m);
      model = glm::make_mat4(m);

      model = glm::scale(model, glm::vec3(scale, scale, scale));
    }

    //non physics object update
    else{

      model = glm::translate(origin, m_translate);
      model = glm::rotate(model, (float) m_rotate, glm::vec3(0.0, 1.0, 0.0));
    }


//  model = glm::rotate(model, (rotate_angle), glm::vec3(x_axis, y_axis, z_axis)); //This axis needs to be dependent on tilt
}

//set ball back to start position
void Object::ResetBall()
{
  btTransform trans;
  m_rigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOrigin() = btVector3(m_translate.x, m_translate.y, m_translate.z);
  m_rigidBody->setWorldTransform(trans);
}


glm::mat4 Object::GetModel()
{
  return model;
}

//returns location without direction information as a mat4
glm::mat4 Object::GetLocation()
{
  return glm::translate(glm::mat4(1.0f), glm::vec3(model[3]));
}

//returns location without direction information as a vec3
glm::vec3 Object::GetLocationVector()
{
  return glm::vec3(model[3]);
}

//render all the object's meshes
void Object::Render()
{

  for(int i = 0; i < meshes.size(); i++)
  {
    meshes[i].Draw();
  }
}

void Object::InitMesh()
{

  //This is the same process of constructing the vertices and indices that we did when we
  //were writing our own object loader

  btVector3 triArray[3];
  m_btTriangleObject = new btTriangleMesh();

  const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

  for(int j = 0; j < m_scene->mNumMeshes; j++)
  {
    std::vector<Vertex> tempVert;
    std::vector<unsigned int> tempInd;
    std::vector<GLuint> temptexture;


    for (int i = 0; i < m_scene->mMeshes[j]->mNumVertices; i++)
    {
      const aiVector3D *pPos = &(m_scene->mMeshes[j]->mVertices[i]);
      const aiVector3D *pNormal = m_scene->mMeshes[j]->HasNormals() ? &(m_scene->mMeshes[j]->mNormals[i]) : &Zero3D;
      const aiVector3D *pTexCoord = m_scene->mMeshes[j]->HasTextureCoords(0) ? &(m_scene->mMeshes[j]->mTextureCoords[0][i]) : &Zero3D;

      Vertex v(glm::vec3(pPos->x * scale_x, pPos->y * scale_y, pPos->z * scale_z), //scaling the vertices directly for the bttriangle meshes
               glm::vec2(pTexCoord->x, -pTexCoord->y),
               glm::vec3(pNormal->x, pNormal->y, pNormal->z));

      tempVert.push_back(v);
    }

    for (unsigned int i = 0; i < m_scene->mMeshes[j]->mNumFaces; i++)
    {
      const aiFace &Face = m_scene->mMeshes[j]->mFaces[i];
      assert(Face.mNumIndices == 3);
      tempInd.push_back(Face.mIndices[0]);
      tempInd.push_back(Face.mIndices[1]);
      tempInd.push_back(Face.mIndices[2]);


      //Bullet triangle mesh collision object stuff
      for(int count = 0; count < 3; count++)
      {
        glm::vec3 t = tempVert[Face.mIndices[count]].vertex;
        triArray[count] = btVector3(t.x, t.y, t.z);
      }

      m_btTriangleObject->addTriangle(triArray[0], triArray[1], triArray[2]);
    }

    //Texture stuff

    temptexture = loadMaterialTextures(m_scene->mMaterials[m_scene->mMeshes[j]->mMaterialIndex], aiTextureType_DIFFUSE);


    Mesh* v = new Mesh(tempVert, tempInd, temptexture);
    meshes.push_back(*v);

  }

  //Finalizing the collision object
  //m_collisionShape = new btBvhTriangleMeshShape(m_btTriangleObject, true);

}

std::vector<GLuint> Object::loadMaterialTextures(aiMaterial *mat, aiTextureType type)
{
  std::vector<GLuint> textures;

  //loading in all the diffuse textures, however we only have the capability
  //to render one
  for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
  {
    GLuint texture;
    aiString str;
    std::string t_path;
    mat->GetTexture(type, i, &str);

    t_path = m_textDirectory + str.C_Str();

    Magick::Blob my_blob;
    Magick::Image image;
    unsigned int* data;

    try {
      image.read(t_path); //the texture for the mesh we're on
      image.write(&my_blob, "RGBA");
    }
    catch (Magick::Error& Error) {
      std::cout << "Error loading texture '" << t_path << "': " << Error.what() << std::endl;
    }

    //Pointing our GLuint pointer to a place in the gpu
    glGenTextures(1, &texture);

    //Specifies the type of texture the pointer is pointing at (still nothing actually there)
    glBindTexture(GL_TEXTURE_2D, texture);

    //Reading our texture data into the place we set up in memory
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.columns(), image.rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, my_blob.data());

    //"fits" the texture to our object in the way we want it to
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Releasing out texture into the wild because we did all the things
    //We can access the texture with m_textureObj in the gpu so we dont need it no mo.
    glBindTexture(GL_TEXTURE_2D, 0);

    textures.push_back(texture);
  }
  return textures;
}
void Object::SetValues(float specB, int specS )
{
  //setting our specular info, hopefully we will later move it into material loading...
  specular_brightness = specB;
  specular_size = specS;
}

//Bullet initializations
void Object::SetBullet(int m, glm::vec3 inert, bool kinObject, bool phys, glm::vec3 start, double rotate, float restitution, float friction)
{
    m_translate = start;
    m_rotate = rotate;
    m_physics = phys;

    if(m_physics) {
      m_shapeMotionState = new btDefaultMotionState(
              btTransform(btQuaternion(0, rotate, 0, 1), btVector3(start.x, start.y, start.z)));
      btScalar mass(m);
      btVector3 inertia(inert.x, inert.y, inert.z);
      m_collisionShape->calculateLocalInertia(mass, inertia);
      btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(mass, m_shapeMotionState, m_collisionShape, inertia);
      shapeRigidBodyCI.m_restitution = restitution;
      shapeRigidBodyCI.m_friction = friction;
      m_rigidBody = new btRigidBody(shapeRigidBodyCI);

      if (kinObject) {
        m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
      }
      m_rigidBody->setActivationState(DISABLE_DEACTIVATION);
    }

}

btRigidBody* Object::GetRigidBody()
{
  return m_rigidBody;
}


