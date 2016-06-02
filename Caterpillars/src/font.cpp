#include "font.hpp"


Character::Character(GLuint text,glm::ivec2 roz, glm::ivec2 bear, GLuint adv){
	this->textureID = text;
	this->size = roz;
	this->bearing = bear;
	this->advance = adv;
}

Font::Font(const char* ttf,GLFWwindow* window,int size){
	std::cout << "Tworzenie fontu" << std::endl;
	this->kolor = glm::vec3(1.0f,1.0f,1.0f);
	this->initChar(ttf, window,size);
}

void Font::initChar(const char* ttf,GLFWwindow* window,int size){
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	this->shader = new Shader("../src/shaders/font.vs","../src/shaders/font.frag");

	int width,height;
	glfwGetWindowSize(window, &width,&height);
	glm::mat4 projection = glm::ortho(0.0f,(float) width, 0.0f,(float) height);
	this->shader->useShaderProgram(0);
	glUniformMatrix4fv(glGetUniformLocation(this->shader->shaderProgram[0], "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	if(FT_Init_FreeType(&this->ft)) {
		std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}
	// if(FT_New_Face(Font::ft,"/usr/share/fonts/truetype/freefont/FreeMono.ttf", 0, &this->face)) {
	// if(FT_New_Face(this->ft,"../src/fonts/Arial.ttf", 0, &this->face)) {
	if(FT_New_Face(this->ft,ttf, 0, &this->face)) {
		std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}

	this->file = ttf;
	this->setRozmiar(size);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// int i =0;
	for (GLubyte c = 0; c < 128; c++) {
		// Load character glyph
		if (FT_Load_Char(this->face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            this->face->glyph->bitmap.width,
            this->face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            this->face->glyph->bitmap.buffer
        );
		this->paramText2D();
		Character *character = new Character(
			texture,
			glm::ivec2(this->face->glyph->bitmap.width, this->face->glyph->bitmap.rows),
            glm::ivec2(this->face->glyph->bitmap_left, this->face->glyph->bitmap_top),
            this->face->glyph->advance.x
		);

		// std::cout << "here " << i << std::endl;
		mapCharacters.insert(std::pair<GLchar, Character*>(c, character));
		// i++;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	// glDisable(GL_CULL_FACE);
	// glDisable(GL_BLEND);
	this->initBinding(true);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	this->endBinding();
}

void Font::setRozmiar(int roz){
	this->rozmiar = roz;
	FT_Set_Pixel_Sizes(this->face, 0, this->rozmiar);
}

void Font::paramText2D(){
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Font::print(std::string text, float x, float y, GLfloat scale){
	this->print(text,x,y,scale, this->kolor);
}

void Font::print(std::string text, GLfloat x, GLfloat y,GLfloat scale,glm::vec3 color){
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	this->shader->useShaderProgram(0);
	glUniform3f(glGetUniformLocation(this->shader->shaderProgram[0], "textColor"), color.x, color.y, color.z);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->currentVAO());

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++){
        Character *ch = this->mapCharacters[*c];

        GLfloat xpos = x + ch->bearing.x * scale;
        GLfloat ypos = y - (ch->size.y - ch->bearing.y) * scale;

        GLfloat w = ch->size.x * scale;
        GLfloat h = ch->size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos,     ypos,       0.0, 1.0 },
            { xpos + w, ypos,       1.0, 1.0 },

            { xpos,     ypos + h,   0.0, 0.0 },
            { xpos + w, ypos,       1.0, 1.0 },
            { xpos + w, ypos + h,   1.0, 0.0 }
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch->textureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, this->buffers[0]->VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
    	glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch->advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

}


// void Font::print(const char* text,float x,float y,float skalax,float skalay){
// void Font::print(const char* text,float x,float y){
//
// 	const char *p;
// 	this->bindBuffers();
// 	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
// 	this->shader->useShaderProgram(0);
// 	// //
// 	glActiveTexture(GL_TEXTURE0);
// 	glGenTextures(1, &this->texture2D);
// 	glBindTexture(GL_TEXTURE_2D, this->texture2D); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
// 	this->paramText2D();
// 	glUniform1i(glGetUniformLocation(this->shader->shaderProgram[0], "ourTexture1"), 0);
// 	GLint vertexColorLocation = glGetUniformLocation(this->shader->shaderProgram[0], "uColor"); //Ustawiamy kolor przycisku, wykorzystywany przy wyborze
// 	glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
//
//
// 	for(p = text; *p; p++) {
// 		if (FT_Load_Char(this->face, *p, FT_LOAD_RENDER)) {
// 			continue;
// 		}
// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, this->znak->bitmap.width, this->znak->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, this->znak->bitmap.buffer);
// 		// glGenerateMipmap(GL_TEXTURE_2D);
// 		float x2 = x + this->znak->bitmap_left * skalax;
// 		float y2 = -y - this->znak->bitmap_top * skalay;
// 		float w = this->znak->bitmap.width * skalax;
// 		float h = this->znak->bitmap.rows * skalay;
// 		GLfloat rect[4][4] {
// 			x2, -y2, 0, 0,
// 			x2+w, -y2, 1, 0,
// 			x2, -y2 - h, 0, 1,
// 			x2+w, -y2 - h, 1, 1,
// 		};
// 		glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_DYNAMIC_DRAW);
// 		glBindVertexArray(this->currentVAO());
// 		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
// 		glBindVertexArray(0);
//
// 		// x += (this->znak->advance.x >> 6) * skalax;
// 		// y += (this->znak->advance.y >> 6) * skalay;
// 		x += (this->znak->advance.x/64) * skalax;
// 		y += (this->znak->advance.y/64) * skalay;
// 		// errorCheck("RYSOWANIE FONT");
// 	}
//
//
//
//
// 	this->endBinding();
// 	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
// 	glDeleteTextures(1, &this->texture2D);
// }



//
// void Font::bindBuffers(){
//
// 	// if(this->buffersCount > 0){
// 	//      this->initBinding(false);
// 	// }
// 	// else{
// 	//      this->initBinding(true);
// 	// }
//
// 	this->initBinding(false);
// 	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
// 	glEnableVertexAttribArray(0);
//
// 	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
// 	glEnableVertexAttribArray(1);
//
// 	//Od tego momentu zmieniamy!
// 	// glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*this->vertices.size(), &this->vertices.front(), GL_DYNAMIC_DRAW);
// 	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*this->indices.size(), &this->indices.front(), GL_DYNAMIC_DRAW);
//
//
// 	// this->endBinding();
// 	// glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
// 	//
// 	// glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
//
// }
