struct _TK_RGBImageRec *texture;

void loadTextureRGB(char file[], int textureInt)
{
	//load texture

		glBindTexture(GL_TEXTURE_2D, textureInt);  //al changes after binding apply to this texture(bind)

		texture = LoadRGB(file);
	
		

		glTexImage2D(GL_TEXTURE_2D, 0, (*texture).components, (*texture).sizeX, (*texture).sizeY, 0,	GL_RGB, GL_UNSIGNED_BYTE, (*texture).data);
		//GL_RGB for VUA textures
		//GL_RGBA for some custom (A = Alpha RGB format) textures

		// create mipmaps for texture texture

		gluBuild2DMipmaps(GL_TEXTURE_2D, (*texture).components, (*texture).sizeX, (*texture).sizeY, GL_RGB, GL_UNSIGNED_BYTE, (*texture).data) ;
		//GL_RGB for VUA textures
		//GL_RGBA for some custom (A = Alpha RGB format) textures


		//void glBindTexture( GLenum target, GLuint texture )

		//glBindTexture(GL_TEXTURE_2D, TEXTURE_texture); 

		//glGetTexImage

	//setup texture vars

		/* whole texture repeated */

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		/* take average of closest 2 x 2 pixels 

		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		*/

		/* take nearest texel (less pretty imho so not used)*/

		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		

		/* use mipmaps: */

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

		


}


void loadTextureRGBA(char file[], int textureInt)
{
	//load texture

		glBindTexture(GL_TEXTURE_2D, textureInt);  //al changes after binding apply to this texture(bind)

		texture = LoadRGB(file);

		glTexImage2D(GL_TEXTURE_2D, 0, (*texture).components, (*texture).sizeX, (*texture).sizeY, 0,	GL_RGBA, GL_UNSIGNED_BYTE, (*texture).data);
		//GL_RGB for VUA textures
		//GL_RGBA for some custom (A = Alpha RGB format) textures

		// create mipmaps for texture texture

		gluBuild2DMipmaps(GL_TEXTURE_2D, (*texture).components, (*texture).sizeX, (*texture).sizeY, GL_RGBA, GL_UNSIGNED_BYTE, (*texture).data) ;
		//GL_RGB for VUA textures
		//GL_RGBA for some custom (A = Alpha RGB format) textures


		//void glBindTexture( GLenum target, GLuint texture )

		//glBindTexture(GL_TEXTURE_2D, TEXTURE_texture); 

		//glGetTexImage

	//setup texture vars

		/* whole texture repeated */

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		/* take average of closest 2 x 2 pixels */

		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

		/* take nearest texel (less pretty imho so not used)

		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		*/

		/* use mipmaps: */

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);


}
