#include "font.hpp"


Character::Character(GLuint text,glm::ivec2 roz, glm::ivec2 bear, GLuint adv){
	this->textureID = text;
	this->size = roz;
	this->bearing = bear;
	this->advance = adv;
}

Font::Font(const char *ttf, int size) {
	std::cout << "Tworzenie fontu" << std::endl;
	start(size);
	// this->kolor = glm::vec3(0.0f,0.0f,0.0f);
    this->initChar(ttf, size);
}


Font::Font(const char *ttf, int size, glm::mat4 projection) {
	std::cout << "Tworzenie fontu 3D" << std::endl;
	this->start(size);
	this->initChar3D(ttf,size,projection);
}


void Font::start(int size) {
	rozmiar = size;
	posM = glm::mat4(1);
	rotM = glm::mat4(1);
	sclM = glm::mat4(1);
	kolor = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Font::initChar(const char *ttf, int size) {
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	this->shader = new Shader("../src/shaders/font.vs","../src/shaders/font.frag");
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
	//TODO: Sprawdzić czy dziala dla wielu rozdzielczosci
	glm::mat4 projection = glm::ortho((float) -1366.0f/2.0f,(float) 1366.0f/2.0f, (float) 768.0f/2.0f,  (float) -768.0f/2.0f,-1.0f,1.0f);
//	glm::mat4 projection = glm::ortho((float) -viewport[2]/2.0f,(float) viewport[2]/2.0f, (float) viewport[3]/2.0f,  (float) -viewport[3]/2.0f,-1.0f,1.0f);


//    std::cout << "width: " << viewport[2] << " height: " << viewport[3] << std::endl;
//	glm::mat4 projection = glm::ortho(0.0f,(float) width, 0.0f,(float) height);
//	glm::mat4 projection = glm::ortho(0.0f,(float) width, (float) height, 0.0f,-1.0f,1.0f);
//	glm::mat4 projection = glm::ortho((float) -width/2,(float) width/2, (float) height/2,  (float) -height/2,-1.0f,1.0f);
//	glm::mat4 projection = glm::ortho(0.0f,800.0f, 600.0f, 0.0f,-1.0f,1.0f);
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
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	this->initBinding();
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
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	this->shader->useShaderProgram(0);
	glUniform3f(glGetUniformLocation(this->shader->shaderProgram[0], "textColor"), color.x, color.y, color.z);


	glUniformMatrix4fv(this->getUniform("M"),1,GL_FALSE,glm::value_ptr(this->posM*this->sclM*this->rotM));

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->currentVAO());

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++){
        Character *ch = this->mapCharacters[*c];

        GLfloat xpos = x + ch->bearing.x * scale;
//        GLfloat ypos = y - (ch->size.y - ch->bearing.y) * scale;
        GLfloat ypos = y + (this->mapCharacters['H']->bearing.y - ch->bearing.y) * scale;

        GLfloat w = ch->size.x * scale;
        GLfloat h = ch->size.y * scale;
        // Update VBO for each character
//        GLfloat vertices[6][4] = {
//            { xpos,     ypos + h,   0.0, 0.0 },
//            { xpos,     ypos,       0.0, 1.0 },
//            { xpos + w, ypos,       1.0, 1.0 },
//
//            { xpos,     ypos + h,   0.0, 0.0 },
//            { xpos + w, ypos,       1.0, 1.0 },
//            { xpos + w, ypos + h,   1.0, 0.0 }
//
//        };
		GLfloat vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 0.0 },
				{ xpos,     ypos,       0.0, 0.0 },

				{ xpos,     ypos + h,   0.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 1.0 },
				{ xpos + w, ypos,       1.0, 0.0 }
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

//	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);

}

float Font::length(std::string text, GLfloat scale) {
    float width = 0.0f;
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Character *ch = this->mapCharacters[*c];
        width += (ch->advance >> 6) * scale;
    }
    return width;
}

float Font::height(GLfloat scale) {
    return this->mapCharacters['H']->size.y * scale;
}


void Font::print3d(std::string text, float x, float y, GLfloat scale, glm::vec3 color) {
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	this->shader->useShaderProgram(0);
	glUniform3f(glGetUniformLocation(this->shader->shaderProgram[0], "textColor"), color.x, color.y, color.z);


//	glUniformMatrix4fv(this->getUniform("projection"),1,GL_FALSE,glm::value_ptr(this->projection));
//	glUniformMatrix4fv(this->getUniform("V"),1,GL_FALSE,glm::value_ptr(glm::mat4(1)));
	glUniformMatrix4fv(this->getUniform("V"),1,GL_FALSE,glm::value_ptr(this->view));
	glUniformMatrix4fv(this->getUniform("M"),1,GL_FALSE,glm::value_ptr(this->posM*this->sclM*this->rotM));

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->currentVAO());

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++){
		Character *ch = this->mapCharacters[*c];

		GLfloat xpos = x + ch->bearing.x * scale;
//        GLfloat ypos = y - (ch->size.y - ch->bearing.y) * scale;
		GLfloat ypos = y + (this->mapCharacters['H']->bearing.y - ch->bearing.y) * scale;

		GLfloat w = ch->size.x * scale;
		GLfloat h = ch->size.y * scale;
		// Update VBO for each character
//        GLfloat vertices[6][4] = {
//            { xpos,     ypos + h,   0.0, 0.0 },
//            { xpos,     ypos,       0.0, 1.0 },
//            { xpos + w, ypos,       1.0, 1.0 },
//
//            { xpos,     ypos + h,   0.0, 0.0 },
//            { xpos + w, ypos,       1.0, 1.0 },
//            { xpos + w, ypos + h,   1.0, 0.0 }
//
//        };
		GLfloat vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 0.0 },
				{ xpos,     ypos,       0.0, 0.0 },

				{ xpos,     ypos + h,   0.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 1.0 },
				{ xpos + w, ypos,       1.0, 0.0 }
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

//	glDisable(GL_BLEND);
//	glDisable(GL_CULL_FACE);

}


void Font::initChar3D(const char *ttf, int size, glm::mat4 projection) {
	this->projection = projection;
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	this->shader = new Shader("../src/shaders/font3d.vs","../src/shaders/font3d.frag");
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	//TODO: Sprawdzić czy dziala dla wielu rozdzielczosci
//	glm::mat4 projection = glm::ortho((float) -1366.0f/2.0f,(float) 1366.0f/2.0f, (float) 768.0f/2.0f,  (float) -768.0f/2.0f,-1.0f,1.0f);
//	glm::mat4 projection = glm::ortho((float) -viewport[2]/2.0f,(float) viewport[2]/2.0f, (float) viewport[3]/2.0f,  (float) -viewport[3]/2.0f,-1.0f,1.0f);


//    std::cout << "width: " << viewport[2] << " height: " << viewport[3] << std::endl;
//	glm::mat4 projection = glm::ortho(0.0f,(float) width, 0.0f,(float) height);
//	glm::mat4 projection = glm::ortho(0.0f,(float) width, (float) height, 0.0f,-1.0f,1.0f);
//	glm::mat4 projection = glm::ortho((float) -width/2,(float) width/2, (float) height/2,  (float) -height/2,-1.0f,1.0f);
//	glm::mat4 projection = glm::ortho(0.0f,800.0f, 600.0f, 0.0f,-1.0f,1.0f);
	this->shader->useShaderProgram(0);
	glUniformMatrix4fv(glGetUniformLocation(this->shader->shaderProgram[0], "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(this->shader->shaderProgram[0], "V"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));
	glUniformMatrix4fv(glGetUniformLocation(this->shader->shaderProgram[0], "M"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));

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
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	this->initBinding();
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	this->endBinding();
}

