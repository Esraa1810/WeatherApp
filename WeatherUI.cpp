#include "WeatherUI.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void WeatherUI::showWindow(const std::string& weatherData) {
    //  Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    // Create a larger window (1100x750)
    GLFWwindow* window = glfwCreateWindow(1100, 750, "Weather App", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    //  Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    //  Load a bigger font (28px)
    ImFont* bigFont = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 28.0f);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    //  Set background color
    ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //  Make the window resizable
        ImGui::SetNextWindowSize(ImVec2(900, 600), ImGuiCond_FirstUseEver); // Start larger
        ImGui::SetNextWindowPos(ImVec2(50, 25), ImGuiCond_FirstUseEver); // Position it better

        ImGui::Begin("Weather Information", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);

        if (bigFont) {
            ImGui::PushFont(bigFont);
        }

        //  Weather info box with SCROLLING (vertical & horizontal)
        ImGui::BeginChild("WeatherInfo", ImVec2(850, 450), true, ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::TextWrapped("%s", weatherData.c_str()); // Auto-wrap long text
        ImGui::EndChild();

        // Restore default font after using big font
        if (bigFont) {
            ImGui::PopFont();
        }

        ImGui::Spacing();

        //Close button
        if (ImGui::Button("Close", ImVec2(180, 70))) {
            glfwSetWindowShouldClose(window, true);
        }

        ImGui::End();

        //  Render UI
        ImGui::Render();
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}
ECHO is on.
