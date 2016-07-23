//
// Created by lewin on 22.07.16.
//

#include "Skybox.hpp"

Skybox::Skybox() {
    this->shader = new Shader("../src/shaders/skybox.vs","../src/shaders/skybox.frag");
    float marginesXZ = 50.0f;
    float marginesY = 10.0f;
    float height = maxMapHeight*1.4f + 400.0f;
    float lewo = - marginesXZ;
    float prawo = vertX + marginesXZ;
    float dol = -marginesY;
    float gora = maxMapHeight + marginesY;
    float back = - marginesXZ;
    float front = vertY + marginesXZ;

//    this->vertices= {
//            // Positions
//            -1.0f,  height, -1.0f,
//            -1.0f, -1.0f, -1.0f,
//            vertX, -1.0f, -1.0f,
//            vertX, -1.0f, -1.0f,
//            vertX,  height, -1.0f,
//            -1.0f,  height, -1.0f,
//
//            -1.0f, -1.0f,  vertY,
//            -1.0f, -1.0f, -1.0f,
//            -1.0f,  height, -1.0f,
//            -1.0f,  height, -1.0f,
//            -1.0f,  height,  vertY,
//            -1.0f, -1.0f,  vertY,
//
//            vertX, -1.0f, -1.0f,
//            vertX, -1.0f,  vertY,
//            vertX,  height,  vertY,
//            vertX,  height,  vertY,
//            vertX,  height, -1.0f,
//            vertX, -1.0f, -1.0f,
//
//            -1.0f, -1.0f,  vertY,
//            -1.0f,  height,  vertY,
//            vertX,  height,  vertY,
//            vertX,  height,  vertY,
//            vertX, -1.0f,  vertY,
//            -1.0f, -1.0f,  vertY,
//
//            -1.0f,  height, -1.0f,
//            vertX,  height, -1.0f,
//            vertX,  height,  vertY,
//            vertX,  height,  vertY,
//            -1.0f,  height,  vertY,
//            -1.0f,  height, -1.0f,
//
//            -1.0f, -1.0f, -1.0f,
//            -1.0f, -1.0f,  vertY,
//            vertX, -1.0f, -1.0f,
//            vertX, -1.0f, -1.0f,
//            -1.0f, -1.0f,  vertY,
//            vertX, -1.0f,  vertY
//    };
//
//    this->vertices= {
//            // Positions
//            lewo, 1.5f * height, -vertY / 2.0f,
//            lewo, -height / 2.0f, -vertY / 2.0f,
//            1.5f*vertX, -height/2.0f, -vertY/2.0f,
//            1.5f*vertX, -height/2.0f, -vertY/2.0f,
//            1.5f*vertX,  1.5f*height, -vertY/2.0f,
//            lewo, 1.5f * height, -vertY / 2.0f,
//
//            lewo, -height / 2.0f, 1.5f * vertY,
//            lewo, -height / 2.0f, -vertY / 2.0f,
//            lewo, 1.5f * height, -vertY / 2.0f,
//            lewo, 1.5f * height, -vertY / 2.0f,
//            lewo, 1.5f * height, 1.5f * vertY,
//            lewo, -height / 2.0f, 1.5f * vertY,
//
//            1.5f*vertX, -height/2.0f, -vertY/2.0f,
//            1.5f*vertX, -height/2.0f,  1.5f*vertY,
//            1.5f*vertX,  1.5f*height,  1.5f*vertY,
//            1.5f*vertX,  1.5f*height,  1.5f*vertY,
//            1.5f*vertX,  1.5f*height, -vertY/2.0f,
//            1.5f*vertX, -height/2.0f, -vertY/2.0f,
//
//            lewo, -height / 2.0f, 1.5f * vertY,
//            lewo, 1.5f * height, 1.5f * vertY,
//            1.5f*vertX,  1.5f*height,  1.5f*vertY,
//            1.5f*vertX,  1.5f*height,  1.5f*vertY,
//            1.5f*vertX, -height/2.0f,  1.5f*vertY,
//            lewo, -height / 2.0f, 1.5f * vertY,
//
//            lewo, 1.5f * height, -vertY / 2.0f,
//            1.5f*vertX,  1.5f*height, -vertY/2.0f,
//            1.5f*vertX,  1.5f*height,  1.5f*vertY,
//            1.5f*vertX,  1.5f*height,  1.5f*vertY,
//            lewo, 1.5f * height, 1.5f * vertY,
//            lewo, 1.5f * height, -vertY / 2.0f,
//
//            lewo, -height / 2.0f, -vertY / 2.0f,
//            lewo, -height / 2.0f, 1.5f * vertY,
//            1.5f*vertX, -height/2.0f, -vertY/2.0f,
//            1.5f*vertX, -height/2.0f, -vertY/2.0f,
//            lewo, -height / 2.0f, 1.5f * vertY,
//            1.5f*vertX, -height/2.0f,  1.5f*vertY
//    };

            this->vertices = {
                    // Positions
                    //Tył
//                    -1.0f,  1.0f, -1.0f,
                    lewo,  gora, back,
//                    -1.0f, -1.0f, -1.0f,
                    lewo, dol, back,
//                    1.0f, -1.0f, -1.0f,
                    prawo, dol, back,
//                    1.0f, -1.0f, -1.0f,
                    prawo, dol, back,
//                    1.0f,  1.0f, -1.0f,
                    prawo,  gora, back,
//                    -1.0f,  1.0f, -1.0f,
                    lewo,  gora, back,

//                    -1.0f, -1.0f,  1.0f,
                    lewo, dol,  front,
//                    -1.0f, -1.0f, -1.0f,
                    lewo, dol, back,
//                    -1.0f,  1.0f, -1.0f,
                    lewo,  gora, back,
//                    -1.0f,  1.0f, -1.0f,
                    lewo,  gora, back,
//                    -1.0f,  1.0f,  1.0f,
                    lewo,  gora,  front,
//                    -1.0f, -1.0f,  1.0f,
                    lewo, dol,  front,

//                    1.0f, -1.0f, -1.0f,
                    prawo, dol, back,
//                    1.0f, -1.0f,  1.0f,
                    prawo, dol,  front,
//                    1.0f,  1.0f,  1.0f,
                    prawo,  gora,  front,
//                    1.0f,  1.0f,  1.0f,
                    prawo,  gora, front,
//                    1.0f,  1.0f, -1.0f,
                    prawo,  gora, back,
//                    1.0f, -1.0f, -1.0f,
                    prawo, dol, back,
              //Prawo
//                    -1.0f, -1.0f,  1.0f,
                    lewo, dol,  front,
//                    -1.0f,  1.0f,  1.0f,
                    lewo,  gora, front,
//                    1.0f,  1.0f,  1.0f,
                    prawo, gora, front,
//                    1.0f,  1.0f,  1.0f,
                    prawo,  gora,  front,
//                    1.0f, -1.0f,  1.0f,
                    prawo, dol,  front,
//                    -1.0f, -1.0f,  1.0f,
                    lewo, dol,  front,
                //Gora
//                    -1.0f,  1.0f, -1.0f,
                    lewo, gora, back,
//                    1.0f,  1.0f, -1.0f,
                    prawo, gora, back,
//                    1.0f,  1.0f,  1.0f,
                    prawo, gora,  front,
//                    1.0f,  1.0f,  1.0f,
                    prawo, gora,  front,
//                    -1.0f,  1.0f,  1.0f,
                    lewo,  gora,  front,
//                    -1.0f,  1.0f, -1.0f,
                    lewo, gora, back,
                //Dół
//                    -1.0f, -1.0f, -1.0f,
                    lewo, dol, back,
//                    -1.0f, -1.0f,  1.0f,
                    lewo, dol, front,
//                    1.0f, -1.0f, -1.0f,
                    prawo, dol, back,
//                    1.0f, -1.0f, -1.0f,
                    prawo, dol, back,
//                    -1.0f, -1.0f,  1.0f,
                    lewo, dol,  front,
//                    1.0f, -1.0f,  1.0f
                    prawo, dol,  front
            };
    this->bindBuffers(3,3,GL_STATIC_DRAW);
    std::vector<std::string> faces = {
            "../src/img/skyboxRight.png",
            "../src/img/skyboxLeft.png",
            "../src/img/skyboxTop.png",
            "../src/img/skyboxBottom.png",
            "../src/img/skyboxBack.png",
            "../src/img/skyboxFront.png",
    };
    this->bindTextureCube(faces,&this->textureCube);

}


void Skybox::draw(glm::mat4 projection, glm::mat4 modelView) {
//    std::cout << "Rysowanie skyboxa" << std::endl;
    glDepthMask(GL_FALSE);
    this->shader->useShaderProgram(0);
//    glUniformMatrix4fv(this->getUniform("V"),1,GL_FALSE,glm::value_ptr(glm::mat4(1)));
    glm::mat4 view = glm::mat4(glm::mat3(modelView));
    glUniformMatrix4fv(this->getUniform("V"),1,GL_FALSE,glm::value_ptr(view));
//    glUniformMatrix4fv(this->getUniform("P"),1,GL_FALSE,glm::value_ptr(glm::mat4(1)));
    glUniformMatrix4fv(this->getUniform("P"),1,GL_FALSE,glm::value_ptr(projection));

    glBindVertexArray(this->currentVAO());
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(this->getUniform("skybox"),0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureCube);
    glDrawArrays(GL_TRIANGLES, 0,36);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
}

