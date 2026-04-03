#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include "shader.h"
#include "camera.h"
#include "model.h"
#include "texture.h"
#include "orbit.h"

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

static bool   satelliteMode = false;
static bool   mKeyPressed   = false;

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

    static bool tabPressed = false;
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && !tabPressed) {
        tabPressed = true;
        cursorCaptured = !cursorCaptured;
        glfwSetInputMode(window, GLFW_CURSOR,
            cursorCaptured ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        firstMouse = true;
    }
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE) tabPressed = false;

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && !mKeyPressed) {
        mKeyPressed = true;
        satelliteMode = !satelliteMode;
        if (satelliteMode)
            camera = Camera(glm::vec3(0.0f, 3.0f, 8.0f));
        else
            camera = Camera(glm::vec3(0.0f, 1.5f, 6.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_RELEASE) mKeyPressed = false;

    if (!cursorCaptured) return;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.processKeyboard(FORWARD,  deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.processKeyboard(LEFT,     deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.processKeyboard(RIGHT,    deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE)      == GLFW_PRESS) camera.processKeyboard(UP,   deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)  == GLFW_PRESS) camera.processKeyboard(DOWN, deltaTime);
}

/* ── Sphere mesh generation ─────────────────────────────────────── */

struct SphereMesh {
    unsigned int VAO = 0, VBO = 0, EBO = 0;
    int indexCount = 0;
};

static SphereMesh createSphere(float radius, int sectors, int stacks) {
    SphereMesh sphere;
    std::vector<float> verts;
    std::vector<unsigned int> indices;

    for (int i = 0; i <= stacks; ++i) {
        float stackAngle = glm::pi<float>() / 2.0f - glm::pi<float>() * i / stacks;
        float xy = radius * cosf(stackAngle);
        float z  = radius * sinf(stackAngle);

        for (int j = 0; j <= sectors; ++j) {
            float sectorAngle = 2.0f * glm::pi<float>() * j / sectors;
            float x = xy * cosf(sectorAngle);
            float y = xy * sinf(sectorAngle);

            verts.push_back(x);
            verts.push_back(z);
            verts.push_back(y);

            float nx = x / radius, ny = z / radius, nz = y / radius;
            verts.push_back(nx);
            verts.push_back(ny);
            verts.push_back(nz);

            float s = static_cast<float>(j) / sectors;
            float t = static_cast<float>(i) / stacks;
            verts.push_back(s);
            verts.push_back(t);
        }
    }

    for (int i = 0; i < stacks; ++i) {
        int k1 = i * (sectors + 1);
        int k2 = k1 + sectors + 1;
        for (int j = 0; j < sectors; ++j, ++k1, ++k2) {
            if (i != 0) { indices.push_back(k1); indices.push_back(k2); indices.push_back(k1 + 1); }
            if (i != stacks - 1) { indices.push_back(k1 + 1); indices.push_back(k2); indices.push_back(k2 + 1); }
        }
    }

    sphere.indexCount = static_cast<int>(indices.size());

    glGenVertexArrays(1, &sphere.VAO);
    glGenBuffers(1, &sphere.VBO);
    glGenBuffers(1, &sphere.EBO);

    glBindVertexArray(sphere.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, sphere.VBO);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    return sphere;
}

/* ── Line buffer helpers ────────────────────────────────────────── */

struct LineMesh {
    unsigned int VAO = 0, VBO = 0;
    int vertexCount = 0;
};

static LineMesh createLineMesh(const std::vector<glm::vec3>& points) {
    LineMesh lm;
    lm.vertexCount = static_cast<int>(points.size());

    glGenVertexArrays(1, &lm.VAO);
    glGenBuffers(1, &lm.VBO);
    glBindVertexArray(lm.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, lm.VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    return lm;
}

static void updateLineMesh(LineMesh& lm, const std::vector<glm::vec3>& points) {
    lm.vertexCount = static_cast<int>(points.size());
    glBindBuffer(GL_ARRAY_BUFFER, lm.VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_DYNAMIC_DRAW);
}

/* ── Main ───────────────────────────────────────────────────────── */

int main() {
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

    if (!gladLoadGL((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glfwSwapInterval(1);

    std::cout << "OpenGL " << glGetString(GL_VERSION) << "\n";
    std::cout << "GPU:   " << glGetString(GL_RENDERER) << "\n";

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    /* ── Load resources ────────────────────────────────────────── */
    Shader phongShader("shaders/phong.vert", "shaders/phong.frag");
    Shader earthShader("shaders/earth.vert", "shaders/earth.frag");
    Shader lineShader("shaders/line.vert", "shaders/line.frag");

    Model cubeModel("assets/models/cube.obj");

    Texture diffuseTex;
    diffuseTex.generateCheckerboard();

    /* ── Cube scene setup ──────────────────────────────────────── */
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

    /* ── Satellite scene setup ─────────────────────────────────── */
    constexpr float EARTH_VIS_RADIUS = 2.0f;
    constexpr float VIS_SCALE = EARTH_VIS_RADIUS; // 1 Earth-radius = 2.0 GL units

    SphereMesh earthSphere = createSphere(EARTH_VIS_RADIUS, 64, 32);

    OrbitalElements issOrbit{};
    issOrbit.a     = 6778.0;
    issOrbit.e     = 0.0002;
    issOrbit.inc   = glm::radians(51.6);
    issOrbit.Omega = glm::radians(120.0);
    issOrbit.omega = glm::radians(0.0);
    issOrbit.M0    = 0.0;

    OrbitalElements polarOrbit{};
    polarOrbit.a     = 7178.0;
    polarOrbit.e     = 0.001;
    polarOrbit.inc   = glm::radians(98.0);
    polarOrbit.Omega = glm::radians(45.0);
    polarOrbit.omega = glm::radians(0.0);
    polarOrbit.M0    = glm::radians(90.0);

    OrbitalElements geoTransfer{};
    geoTransfer.a     = 24400.0;
    geoTransfer.e     = 0.73;
    geoTransfer.inc   = glm::radians(7.0);
    geoTransfer.Omega = glm::radians(200.0);
    geoTransfer.omega = glm::radians(178.0);
    geoTransfer.M0    = 0.0;

    auto issPath   = computeOrbitPath(issOrbit, 256, VIS_SCALE);
    auto polarPath = computeOrbitPath(polarOrbit, 256, VIS_SCALE);
    auto gtoPath   = computeOrbitPath(geoTransfer, 256, VIS_SCALE);

    LineMesh issLine   = createLineMesh(issPath);
    LineMesh polarLine = createLineMesh(polarPath);
    LineMesh gtoLine   = createLineMesh(gtoPath);

    double period1 = 2.0 * glm::pi<double>() * std::sqrt(issOrbit.a * issOrbit.a * issOrbit.a / 398600.4418);
    auto issGroundTrack = computeGroundTrack(issOrbit, 0.0, period1 * 1.5, 500, EARTH_VIS_RADIUS);
    LineMesh groundTrackLine = createLineMesh(issGroundTrack);

    SphereMesh satMarker = createSphere(0.05f, 12, 8);

    double simTime = 0.0;
    constexpr double TIME_SCALE = 200.0;

    /* ── Render loop ───────────────────────────────────────────── */
    int frameCount = 0;
    float fpsTimer = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        frameCount++;
        fpsTimer += deltaTime;
        if (fpsTimer >= 0.5f) {
            int fps = static_cast<int>(frameCount / fpsTimer);
            std::string mode = satelliteMode ? "Satellite" : "Cubes";
            glfwSetWindowTitle(window, ("OpenGL 3D Renderer  |  " + mode + "  |  " + std::to_string(fps) + " FPS  |  M to toggle").c_str());
            frameCount = 0;
            fpsTimer = 0.0f;
        }

        processInput(window);

        glClearColor(0.02f, 0.02f, 0.04f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(
            glm::radians(camera.Zoom),
            static_cast<float>(SCR_WIDTH) / SCR_HEIGHT,
            0.1f, 200.0f);
        glm::mat4 view = camera.getViewMatrix();

        if (!satelliteMode) {
            /* ── Cube demo ─────────────────────────────────────── */
            phongShader.use();
            phongShader.setMat4("projection", projection);
            phongShader.setMat4("view", view);
            phongShader.setVec3("viewPos", camera.Position);

            phongShader.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
            phongShader.setVec3("dirLight.ambient",   glm::vec3(0.12f));
            phongShader.setVec3("dirLight.diffuse",   glm::vec3(0.5f));
            phongShader.setVec3("dirLight.specular",  glm::vec3(0.6f));

            for (int i = 0; i < 4; ++i) {
                std::string base = "pointLights[" + std::to_string(i) + "]";
                phongShader.setVec3 (base + ".position",  pointLightPositions[i]);
                phongShader.setVec3 (base + ".ambient",   glm::vec3(0.05f));
                phongShader.setVec3 (base + ".diffuse",   glm::vec3(0.8f));
                phongShader.setVec3 (base + ".specular",  glm::vec3(1.0f));
                phongShader.setFloat(base + ".constant",  1.0f);
                phongShader.setFloat(base + ".linear",    0.09f);
                phongShader.setFloat(base + ".quadratic", 0.032f);
            }

            phongShader.setInt  ("material.diffuse",   0);
            phongShader.setFloat("material.shininess", 32.0f);
            diffuseTex.bind(0);

            for (unsigned int i = 0; i < 10; ++i) {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
                float angle = 20.0f * static_cast<float>(i) + currentFrame * 15.0f;
                model = glm::rotate(model, glm::radians(angle),
                                    glm::vec3(1.0f, 0.3f, 0.5f));
                phongShader.setMat4("model", model);
                cubeModel.draw();
            }
        } else {
            /* ── Satellite visualization ───────────────────────── */
            simTime += static_cast<double>(deltaTime) * TIME_SCALE;

            /* Earth */
            earthShader.use();
            earthShader.setMat4("projection", projection);
            earthShader.setMat4("view", view);
            earthShader.setVec3("viewPos", camera.Position);
            earthShader.setVec3("sunDir", glm::vec3(1.0f, 0.3f, 0.5f));

            float earthRotation = static_cast<float>(simTime * 7.2921159e-5);
            glm::mat4 earthModel = glm::rotate(glm::mat4(1.0f), earthRotation, glm::vec3(0.0f, 1.0f, 0.0f));
            earthShader.setMat4("model", earthModel);

            glBindVertexArray(earthSphere.VAO);
            glDrawElements(GL_TRIANGLES, earthSphere.indexCount, GL_UNSIGNED_INT, 0);

            /* Orbit paths */
            lineShader.use();
            lineShader.setMat4("projection", projection);
            lineShader.setMat4("view", view);

            lineShader.setVec3("lineColor", glm::vec3(0.2f, 0.8f, 0.3f));
            glBindVertexArray(issLine.VAO);
            glDrawArrays(GL_LINE_STRIP, 0, issLine.vertexCount);

            lineShader.setVec3("lineColor", glm::vec3(0.3f, 0.5f, 1.0f));
            glBindVertexArray(polarLine.VAO);
            glDrawArrays(GL_LINE_STRIP, 0, polarLine.vertexCount);

            lineShader.setVec3("lineColor", glm::vec3(1.0f, 0.4f, 0.2f));
            glBindVertexArray(gtoLine.VAO);
            glDrawArrays(GL_LINE_STRIP, 0, gtoLine.vertexCount);

            /* Ground track */
            lineShader.setVec3("lineColor", glm::vec3(1.0f, 1.0f, 0.3f));
            glBindVertexArray(groundTrackLine.VAO);
            glDrawArrays(GL_LINE_STRIP, 0, groundTrackLine.vertexCount);

            /* Animated satellite markers */
            glDisable(GL_CULL_FACE);

            auto drawSat = [&](const OrbitalElements& oe, const glm::vec3& color) {
                glm::dvec3 pos = propagate(oe, simTime);
                glm::vec3 visPos = glm::vec3(pos * static_cast<double>(VIS_SCALE / 6371.0));

                lineShader.setVec3("lineColor", color);
                glBindVertexArray(satMarker.VAO);

                glm::mat4 satModel = glm::translate(glm::mat4(1.0f), visPos);
                lineShader.setMat4("projection", projection * view * satModel);
                lineShader.setMat4("view", glm::mat4(1.0f));
                glDrawElements(GL_TRIANGLES, satMarker.indexCount, GL_UNSIGNED_INT, 0);
            };

            drawSat(issOrbit, glm::vec3(0.2f, 1.0f, 0.3f));
            drawSat(polarOrbit, glm::vec3(0.3f, 0.5f, 1.0f));
            drawSat(geoTransfer, glm::vec3(1.0f, 0.4f, 0.2f));

            glEnable(GL_CULL_FACE);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
