#include "main.h"
#include "shader.h"
#include "texture.h"
        
int main(void)  
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK)
        std::cout << "GLEW Error" << std::endl;


    std::cout << glGetString(GL_VERSION) << std::endl;

    Shader shaderProgramObj = Shader::Shader("vertex.shader", "frag.shader");
    unsigned int shaderProgram = shaderProgramObj.createShaderProgram();
    shaderProgramObj.addUniform1i("texture1", 0);
    shaderProgramObj.addUniform1i("texture2", 1);

    float vertices[] = {    
             // pos               color         tex-coords
        -0.25f, 0.25f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f, // top-left (0)
        0.25f, 0.25f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // top-right (1)
        -0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom-left (2)
        0.25f, -0.25f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f  // bottom-right (3)
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 1
    };

    // Intialize vertex array and vertex buffer object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    TextureLoader loader;
    Texture texture1 = Texture::Texture(0, "dvd.png");

    loader.addTexture(0, texture1);
    loader.loadTexture(0);

    Texture texture2 = Texture::Texture(1, "container.jpg");

    loader.addTexture(1, texture2);
    loader.loadTexture(1);
    

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)  0);
    glEnableVertexAttribArray(0);

    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // tex-coord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    float x = 0.0f;
    float y = 0.25f;
    float dx = 0.01f;
    float dy = 0.01f;

    float colors[4][3] = { {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f} };
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;

    int i = 0;

    /* Loop until the user closes the window */ 
    while (!glfwWindowShouldClose(window))
    {   
        /* Input check */   

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        loader.bindTextures();

        float time = glfwGetTime();

        if (x >= 0.75f || x <= -0.75f) {
            dx = -dx;
            if (i < 3) {
                i += 1;
            }
            else {
                i = 0;
            }
            

            r = colors[i][0];
            g = colors[i][1];
            b = colors[i][2];
        }
        if (y >= 0.75f || y <= -0.75f) {
            dy = -dy;
        }
        
        x = x + dx;
        y = y + dy;

        shaderProgramObj.addUniform1f("x", x);
        shaderProgramObj.addUniform1f("y", y);
        shaderProgramObj.addUniform4f("currColor", 1.0f - sin(x) / 2, g, b, 1.0f);
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}