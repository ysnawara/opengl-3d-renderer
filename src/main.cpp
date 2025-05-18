#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "camera.h"
#include "model.h"
#include "texture.h"

/* ── Window / input state ───────────────────────────────────────── */

static constexpr unsigned int SCR_WIDTH  = 1280;
static constexpr unsigned int SCR_HEIGHT = 720;

static Camera camera(glm::vec3(0.0f, 1.5f, 6.0f));
static float  lastX     = SCR_WIDTH / 2.0f;
static float  lastY     = SCR_HEIGHT / 2.0f;
static bool   firstMouse = true;
static bool   cursorCaptured = true;
static float  deltaTime  = 0.0f;
static float  lastFrame  = 0.0f;

/* ── Callbacks ──────────────────────────────────────────────────── */

static void framebufferSizeCallback(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
}

static void mouseCallback(GLFWwindow*, double xposIn, double yposIn) {
    if (!cursorCaptured) return;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    camera.processMouseMovement(xpos - lastX, lastY - ypos);
    lastX = xpos;
    lastY = ypos;
}

static void scrollCallback(GLFWwindow*, double, double yoffset) {
    camera.processMouseScroll(static_cast<float>(yoffset));
}

static void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Tab toggles mouse capture
    static bool tabPressed = false;
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && !tabPressed) {
        tabPressed = true;
        cursorCaptured = !cursorCaptured;
        glfwSetInputMode(window, GLFW_CURSOR,
            cursorCaptured ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        firstMouse = true;
    }
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE) tabPressed = false;

    if (!cursorCaptured) return;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.processKeyboard(FORWARD,  deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.processKeyboard(LEFT,     deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.processKeyboard(RIGHT,    deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE)      == GLFW_PRESS) camera.processKeyboard(UP,   deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)  == GLFW_PRESS) camera.processKeyboard(DOWN, deltaTime);
}

/* ── Main ───────────────────────────────────────────────────────── */

int main() {
    /* ── Init GLFW ─────────────────────────────────────────────── */
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                                           "OpenGL 3D Renderer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /* ── Load OpenGL ───────────────────────────────────────────── */
    if (!gladLoadGL((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    std::cout << "OpenGL " << glGetString(GL_VERSION) << "\n";
    std::cout << "GPU:   " << glGetString(GL_RENDERER) << "\n";

    /* ── GL state ──────────────────────────────────────────────── */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    /* ── Load resources ────────────────────────────────────────── */
    Shader shader("shaders/phong.vert", "shaders/phong.frag");

    Model cubeModel("assets/models/cube.obj");

    Texture diffuseTex;
    diffuseTex.generateCheckerboard();

    /* ── Scene setup ───────────────────────────────────────────── */
    glm::vec3 cubePositions[] = {
        { 0.0f,  0.0f,   0.0f},
        { 2.0f,  5.0f, -15.0f},
        {-1.5f, -2.2f,  -2.5f},
        {-3.8f, -2.0f, -12.3f},
        { 2.4f, -0.4f,  -3.5f},
        {-1.7f,  3.0f,  -7.5f},
        { 1.3f, -2.0f,  -2.5f},
        { 1.5f,  2.0f,  -2.5f},
        { 1.5f,  0.2f,  -1.5f},
        {-1.3f,  1.0f,  -1.5f},
    };

    glm::vec3 pointLightPositions[] = {
        { 0.7f,  0.2f,  2.0f},
        { 2.3f, -3.3f, -4.0f},
        {-4.0f,  2.0f, -12.0f},
        { 0.0f,  0.0f, -3.0f},
    };

    /* ── Render loop ───────────────────────────────────────────── */
    int frameCount = 0;
    float fpsTimer = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // FPS counter in window title
        frameCount++;
        fpsTimer += deltaTime;
        if (fpsTimer >= 0.5f) {
            int fps = static_cast<int>(frameCount / fpsTimer);
            glfwSetWindowTitle(window, ("OpenGL 3D Renderer  |  " + std::to_string(fps) + " FPS").c_str());
            frameCount = 0;
            fpsTimer = 0.0f;
        }

        processInput(window);

        glClearColor(0.08f, 0.08f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        /* Camera matrices */
        glm::mat4 projection = glm::perspective(
            glm::radians(camera.Zoom),
            static_cast<float>(SCR_WIDTH) / SCR_HEIGHT,
            0.1f, 100.0f);
        glm::mat4 view = camera.getViewMatrix();

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setVec3("viewPos", camera.Position);

        /* Directional light */
        shader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        shader.setVec3("dirLight.ambient",   glm::vec3(0.12f));
        shader.setVec3("dirLight.diffuse",   glm::vec3(0.5f));
        shader.setVec3("dirLight.specular",  glm::vec3(0.6f));

        /* Point lights */
        for (int i = 0; i < 4; ++i) {
            std::string base = "pointLights[" + std::to_string(i) + "]";
            shader.setVec3 (base + ".position",  pointLightPositions[i]);
            shader.setVec3 (base + ".ambient",   glm::vec3(0.05f));
            shader.setVec3 (base + ".diffuse",   glm::vec3(0.8f));
            shader.setVec3 (base + ".specular",  glm::vec3(1.0f));
            shader.setFloat(base + ".constant",  1.0f);
            shader.setFloat(base + ".linear",    0.09f);
            shader.setFloat(base + ".quadratic", 0.032f);
        }

        /* Material */
        shader.setInt  ("material.diffuse",   0);
        shader.setFloat("material.shininess", 32.0f);

        diffuseTex.bind(0);

        /* Draw cubes */
        for (unsigned int i = 0; i < 10; ++i) {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
            float angle = 20.0f * static_cast<float>(i) + currentFrame * 15.0f;
            model = glm::rotate(model, glm::radians(angle),
                                glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMat4("model", model);
            cubeModel.draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
