#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GameEngine.h"

#include <shaders/shader.h>
#include <camera/camera.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.cpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

/**
* Challenges (EP1):
* 1. Create Entry Point (main) 
* 2. Create Window & Game loop
* 3. Add support for multiple monitors
* 4. Add way to launch game in full screen
* 5. Add event handlers for keyboard, mouse, mouse scroll, controllers
*
**/

int main() {
    // Initialize Glfw 4.6
    GameEngine::init(4, 6);
    GLFWwindow* window = GameEngine::createWindow();

    // Callbacks for when certain properties are updated
    glfwSetKeyCallback(window, GameEngine::Input::keyCallback);
    glfwSetCursorPosCallback(window, GameEngine::Input::cursorPositionCallback);

    // COMPILE AND CREATE SHADERS
    Shader triangleProgram = Shader("L:/Projects/C++/GWG Minecraft Clone/shaders/shape.vs.glsl", "L:/Projects/C++/GWG Minecraft Clone/shaders/color.fs.glsl");

    // VERTEX DATA
    float vertices[] = {
         // positions         // colors         
        -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // top left
         0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // bottom left
    };
    unsigned int indices[]{
        0, 1, 2,  // 1st triangle
        0, 2, 3,  // 2nd triangle
    };

    // Creating buffers to store our vertex data and index data 
    // Wrapping those buffers in a vertex array to attribute the data
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Binding VAO 
    glBindVertexArray(VAO);

    // Storing the contents of "vertices" in VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Adding pointers to different positions of vertices to distinguish the meaning behind the data
    // Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // Colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // Unbinding
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    glViewport(0, 0, GameEngine::Settings::windowWidth, GameEngine::Settings::windowHeight);
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen to a pale-bluish color and insures the color gets refreshed by the frame 
        glClearColor(135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        triangleProgram.use();
        glBindVertexArray(VAO);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        // Updates underlying OS events, such as mouse being moved, window resized, etc
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
