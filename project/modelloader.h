


GLenum getDrawingType(char type[100])
{
	if(strcmp(type, "POINTS") == 0)
	{
        return GL_POINTS;
	}

	if(strcmp(type, "LINES") == 0)
	{
        return GL_LINES;
	}

	if(strcmp(type, "LINE_STRIP") == 0)
	{
        return GL_LINE_STRIP;
	}

	if(strcmp(type, "LINE_LOOP") == 0)
	{
        return GL_LINE_LOOP;
	}

	if(strcmp(type, "TRIANGLES") == 0)
	{
        return GL_TRIANGLES;
	}

	if(strcmp(type, "QUADS") == 0)
	{
        return GL_QUADS;
	}

	if(strcmp(type, "TRIANGLE_STRIP") == 0)
	{
        return GL_TRIANGLE_STRIP;
	}

	if(strcmp(type, "TRIANGLE_FAN") == 0)
	{
        return GL_TRIANGLE_FAN;
	}

	if(strcmp(type, "QUAD_STRIP") == 0)
	{
        return GL_QUAD_STRIP;
	}

	if(strcmp(type, "POLYGON") == 0)
	{
        return GL_POLYGON;
	}

	return 0;

}

int lines1 = 0;

GLfloat Color1[4];

GLfloat Vertices1[4]; 

GLfloat Normals1[4]; 

int i1;

FILE *filePointer;

char drawing[100];


void loaderData(char file[], int displayInt)
{
	filePointer = fopen(file, "r");
  //read drawing type
  fscanf(filePointer, "%s%d", drawing, &lines1);
  //read color
  fscanf(filePointer, "%f%f%f%f", &Color1[0], &Color1[1], &Color1[2], &Color1[3]);

	
	glNewList(displayInt, GL_COMPILE);
		
		glBegin(getDrawingType(drawing));

		//glBegin(GL_TRIANGLES);

			glColor4f(Color1[0], Color1[1], Color1[2], Color1[3]);

		  for(i1 = 0; i1 < lines1; i1 ++)

		  {
			//read vertices and normals
			fscanf(filePointer, "%f%f%f%f%f%f", &Vertices1[0], &Vertices1[1], &Vertices1[2], &Normals1[0], &Normals1[1], &Normals1[2]);

			glNormal3f(Normals1[0], Normals1[1], Normals1[2]);

			glVertex3f(Vertices1[0], Vertices1[1], Vertices1[2]);

		  }

		glEnd();
		
	glEndList();


	fclose(filePointer);

  //return lines*3;

	//return DisplayListName;
	//return 0;

}

//planes for model texturing
GLfloat Planes[] = {0.5, 0.0, 0.0, 0.5 };
GLfloat Planet[] = {0.0, 0.5, 0.0, 0.5 };

void loaderDataWithRandomTextures(char file[], int displayInt, int texture)
{
	filePointer = fopen(file, "r");
  //read drawing type
  fscanf(filePointer, "%s%d", drawing, &lines1);
  //read color
  fscanf(filePointer, "%f%f%f%f", &Color1[0], &Color1[1], &Color1[2], &Color1[3]);

	glNewList(displayInt, GL_COMPILE);



		glMatrixMode(GL_TEXTURE); //initialise texture matrix mode
		glEnable(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, texture);  //TEXTURE_GROUND	
			

			glBegin(getDrawingType(drawing));

            glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR); //GL_EYE_LINEAR
            glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
            glTexGenfv(GL_S, GL_OBJECT_PLANE, Planes);
            glTexGenfv(GL_T, GL_OBJECT_PLANE, Planet);

			//use textures for model
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);

			glColor4f(Color1[0], Color1[1], Color1[2], Color1[3]);
		
		//	glColor4f(1.0, 1.0, 1.0, 1.0);
			
			//glBindTexture(GL_TEXTURE_2D, TEXTURE_GROUND); 
					
			//still needs texture coordinates


		  for(i1 = 0; i1 < lines1; i1 ++)
		  {

			//glTexCoord3f(Vertices1[0], Vertices1[1], Vertices1[2]); //use vertixes instead of randoms for texture coordinates

			//glTexCoord2f( 0.0 , 0.0 );
			//glTexCoord2f( 1.0 , 0.0 );
			//glTexCoord2f( 1.0 , 1.0 );
			//glTexCoord2f( 0.0 , 1.0 );
			  
			  //read vertices and normals
			fscanf(filePointer, "%f%f%f%f%f%f", &Vertices1[0], &Vertices1[1], &Vertices1[2], &Normals1[0], &Normals1[1], &Normals1[2]);

			glNormal3f(Normals1[0], Normals1[1], Normals1[2]);

			glVertex3f(Vertices1[0], Vertices1[1], Vertices1[2]);




		  }

		glEnd();


			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T); 
			  
			glDisable(GL_TEXTURE_2D);
			glMatrixMode(GL_MODELVIEW); 

		
	glEndList(); //end display list


	fclose(filePointer);

  //return lines*3;

	//return DisplayListName;
	//return 0;

}
