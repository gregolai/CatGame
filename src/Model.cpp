#include "Include.h"
#include "Model.h"
#include "Game.h"

Model::Model()
{
	mName			= "";
	mId				= 0;
	mBoundingBox	= Math::Box3();
	mTextures		= std::vector<Texture*>();
}

Model::~Model()
{
	if(mId != 0) {
		glDeleteLists(mId, 1);
	}
}

Model* Model::loadFromOBJ(const char* filename)
{
	mName = filename;

	std::vector<std::string> lines;

	if(!getFileLines(MODEL_DIR + filename, lines)) {
		log_error(STR("Filed to load file: ") + filename);
		return NULL;
	}

	size_t numLines = lines.size();
	std::string tok;

	std::vector<std::string>	words;

	std::vector<Texture*>		textures;
	std::vector<float>			verts;
	std::vector<float>			texCoords;
	std::vector<float>			norms;
	std::vector<std::string>	faces;

	//loop thru lines of the file, until the end of the file...
	for(size_t i=0; i<numLines; ++i) {

		StringUtil::trim(lines[i]);

		//get the next line
		if(lines[i] != "") {

			//get the first word of the line, which is always the keyword token
			words = StringUtil::split(lines[i], std::string(" "));
			if(words.size() > 0) {

				tok = words[0];
				
				if(tok == "v") {	//v - add a vertex to our array list
					//save the vert
					verts.push_back( (float)atof(words[1].c_str()) );
					verts.push_back( (float)atof(words[2].c_str()) );
					verts.push_back( (float)atof(words[3].c_str()) );		
				}		
				else if(tok == "vt"){	//vt - read texture UV coordinates
					//save the texture UVs
					texCoords.push_back( (float)atof(words[1].c_str()) );
					texCoords.push_back( (float)atof(words[2].c_str()) );
				}		
				else if(tok == "vn"){	//vn - read a vertex normal
					//save the normal
					norms.push_back( (float)atof(words[1].c_str()) );
					norms.push_back( (float)atof(words[2].c_str()) );
					norms.push_back( (float)atof(words[3].c_str()) );		
				}
				else if(tok == "mtllib"){	

					std::vector<Texture*> tex;
					if(loadTextureFromMtl(words[1].c_str(), tex)) {
						size_t tsz = tex.size();
						for(size_t i=0; i<tsz; ++i) {
							mTextures.push_back(tex[i]);
						}
					}
				}
				else if(tok == "f"){	//f - read a face!
					faces.push_back(words[1]);
					faces.push_back(words[2]);
					faces.push_back(words[3]);
				}
			}
		}

	}

	bool useNormals = ( norms.size() != 0 ? true : false );

	size_t sizeF = faces.size();
	//short* F = new short[sizeF];

	//all the vertices (3 components (x,y,z) each)
	size_t sizeV = sizeF * 3;
	float* V = new float[sizeV];
	
	//all the texture UVs (2 coordinates (u,v) per vertex)
	size_t sizeT = sizeF * 2;
	float* T = new float[sizeT];
	
	//all the texture normals (3 v's per face, 3 normal components (x,y,z) each)
	size_t sizeN = sizeF * 3;
	float* N = new float[sizeN];
	
	
	//holds the faces components
	std::vector<std::string> C;
	
	//loop thru the faces, and add to the arrays

	mBoundingBox.left = 10000.0f;
	mBoundingBox.right = -10000.0f;
	mBoundingBox.bottom = 10000.0f;
	mBoundingBox.top = -10000.0f;
	mBoundingBox.front = 10000.0f;
	mBoundingBox.back = -10000.0f;

	int idx;
	float* vPtr = V; float vVal;
	float* tPtr = T; float tVal;
	float* nPtr = N; float nVal;
	for(size_t i=0; i<sizeF; ++i) {

		//get the components for the face
		C = StringUtil::split(faces[i], std::string("/"));

		//save the 3 vertex components
		idx = atoi(C[0].c_str())-1;

		//X
		vVal = *vPtr = verts[idx*3+0];
		++vPtr;

		if(vVal < mBoundingBox.left)
			mBoundingBox.left = vVal;
		if(vVal > mBoundingBox.right)
			mBoundingBox.right = vVal;

		//Y
		vVal = *vPtr = verts[idx*3+1];
		++vPtr;

		if(vVal < mBoundingBox.bottom)
			mBoundingBox.bottom = vVal;
		if(vVal > mBoundingBox.top)
			mBoundingBox.top = vVal;
		
		//Z
		vVal = *vPtr = verts[idx*3+2];
		++vPtr;

		if(vVal < mBoundingBox.front)
			mBoundingBox.front = vVal;
		if(vVal > mBoundingBox.back)
			mBoundingBox.back = vVal;		

		//save the 2 UV coordinates
		idx = atoi(C[1].c_str())-1;

		//U
		tVal = *tPtr = texCoords[idx*2+0];
		++tPtr;

		//V
		tVal = *tPtr = texCoords[idx*2+1];
		++tPtr;
		
		if(useNormals) {

			//save the 3 normal components
			idx = atoi(C[2].c_str())-1;

			//NX
			nVal = *nPtr = norms[idx*3+0];
			++nPtr;

			//NY
			nVal = *nPtr = norms[idx*3+1];
			++nPtr;

			//NZ
			nVal = *nPtr = norms[idx*3+2];
			++nPtr;
		}

	}//next i

	mId = glGenLists(1);
	glNewList(mId, GL_COMPILE);
	
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		if(useNormals) {			
			glEnableClientState(GL_NORMAL_ARRAY);
		}
		glEnableClientState(GL_VERTEX_ARRAY);

		glTexCoordPointer(2, GL_FLOAT, 0, T);
		glVertexPointer(3, GL_FLOAT, 0, V);
		if(useNormals) {
			glNormalPointer(GL_FLOAT, 0, N);
		}

		glEnable(GL_LIGHTING);

		// draw a cube
		glDrawArrays(GL_TRIANGLES, 0, sizeF);

		// deactivate vertex arrays after drawing
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		if(useNormals) {
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glDisableClientState(GL_VERTEX_ARRAY);

	glEndList();

	delete[] V;
	delete[] T;
	delete[] N;

	return this;
}

bool Model::loadTextureFromMtl(const char* filename, std::vector<Texture*>& textures)
{
	std::vector<std::string> lines;

	if(!getFileLines(MODEL_DIR + filename, lines)) {
		log_error(STR("Filed to load file: ") + filename);
		return false;
	}

	size_t numLines = lines.size();
	std::string					tok;
	std::vector<std::string>	words;
	Texture*					tex;

	for(size_t i=0; i<numLines; ++i) {
		StringUtil::trim(lines[i]);

		//get the next line
		if(lines[i] != "") {

			//get the first word of the line, which is always the keyword token
			words = StringUtil::split(lines[i], std::string(" "));
			if(words.size() > 0) {
				tok = words[0];

				if(tok == "map_Kd") {

					tex = MM.getTexture(words[1].c_str());
					if(!tex) {
						log_warning(STR("Texture not found: ") + words[1].c_str());
					} else {
						textures.push_back(tex);
					}
				}	//map_Kd

			} //words size
		
		} //line not empty

	} //foreach line

	return true;
}

Texture* Model::getTextureVariant(unsigned int variant)
{ 
	if(mTextures.size() == 0) {
		log_info(STR("No textures in model: ") + mName);
		return NULL;
	}

	size_t sz = mTextures.size();
	if(variant >= sz) {
		log_info("Texture variant out of range. Applying different texture.");
		variant = sz-1;
	}
	return mTextures[variant];
}
GLuint Model::getId()
{
	return mId;
}

Math::Box3& Model::getBoundingBox()
{
	return mBoundingBox;
}