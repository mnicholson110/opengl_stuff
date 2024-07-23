#include "Renderer.h"
#include <GLFW/glfw3.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);
    
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return -1;
    }

    float positions[] =
    {
        -0.5f, -0.5f, 0.0f, 0.0f, // 0
         0.5f, -0.5f, 1.0f, 0.0f, // 1
         0.5f,  0.5f, 1.0f, 1.0f, // 2
        -0.5f,  0.5f, 0.0f, 1.0f  // 3
    };

    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    // vertex positions
    layout.Push<float>(2);
    // texture coords
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    Shader shader("src/res/shaders/Basic.glsl");
    shader.Bind();

    Texture texture("src/res/textures/tux.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        renderer.Draw(va, ib, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}