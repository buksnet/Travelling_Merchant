#include "UI.h"
#include "Windows.h"

void UI::error(int code, const char* desc) {
	fputs(desc, stderr);
}

void UI::link_graph(graph* data)
{
    this->graph_ptr = data;
}

void UI::keyCallBack(GLFWwindow* root, int key, int scancode, int action, int mode) {
    int state = glfwGetKey(root, GLFW_KEY_ESCAPE);
    if (state == GLFW_PRESS) {
        glfwSetWindowShouldClose(root, GLFW_TRUE);
    }
}

UI::UI() {
    
}


UI::~UI() {
    
}

void UI::draw() {
    if (!glfwInit()) delete this;
    glfwSetErrorCallback(error);
    root = glfwCreateWindow(900, 900, "Travelling Merchant by buks.net", NULL, NULL);
    if (root == NULL) delete this;
    glfwMakeContextCurrent(root);
    glfwSwapInterval(1);
    glfwSetKeyCallback(root, keyCallBack);
    glClearColor(255, 255, 255, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glColor3f(1.f, 1.f, 1.f);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) throw runtime_error("glewInit failed");
    if (!gltInit()) cout << "Font init error";
    while (!glfwWindowShouldClose(root)) {
        int width, height;
        glfwGetFramebufferSize(root, &width, &height);
        glClear(GL_COLOR_BUFFER_BIT);
        clear_names();
        glViewport(0, 0, width, height);
        int i = 0, j = 0;
        float theta, x, y, x1, y1, x2, y2;

        for (auto const& it : (*graph_ptr).work) {
            theta = 2.0f * 3.1415926f * float(i - 1) / float((*graph_ptr).work.size());
            x = 0.55 * cosf(theta);
            y = 0.55 * sinf(theta);
            theta = 2.0f * 3.1415926f * float(i) / float((*graph_ptr).work.size());
            x1 = 0.55 * cosf(theta);
            y1 = 0.55 * sinf(theta);
            draw_edge(x + 0.01, y + 0.125, x1 + 0.01, y1 + 0.125);
            for (auto const& edge : it.second->adj) {
                if (j > 0 && j < (*graph_ptr).work.size()-1) {
                    theta = 2.0f * 3.1415926f * float(j) / float((*graph_ptr).work.size());
                    x2 = 0.55 * cosf(theta);
                    y2 = 0.55 * sinf(theta);
                    if (edge.second->name != it.second->name) draw_edge(x + 0.01, y + 0.125, x2 + 0.01, y2 + 0.125);
                }
                j++;
            }
            j = 0;
            i++;
        }
        i = 0;
        for (auto const& it : (*graph_ptr).work) {
            theta = 2.0f * 3.1415926f * float(i - 1) / float((*graph_ptr).work.size());
            x = 0.55 * cosf(theta);
            y = 0.55 * sinf(theta);
            theta = 2.0f * 3.1415926f * float(i) / float((*graph_ptr).work.size());
            x1 = 0.55 * cosf(theta);
            y1 = 0.55 * sinf(theta);
            draw_vertex(x, y);
            i++;
        }
        i = 0;
        for (auto const& it : (*graph_ptr).work) {
            theta = 2.0f * 3.1415926f * float(i - 1) / float((*graph_ptr).work.size());
            x = 0.55 * cosf(theta);
            y = 0.55 * sinf(theta);
            theta = 2.0f * 3.1415926f * float(i) / float((*graph_ptr).work.size());
            x1 = 0.55 * cosf(theta);
            y1 = 0.55 * sinf(theta);
            j = 0;
            put_name(it.second->name, x, y);
            i++;
        }
        Sleep(0.1);
        glfwSwapBuffers(root);
        glfwPollEvents();
    }
    gltTerminate();
    glfwDestroyWindow(this->root);
    glfwTerminate();
}


void UI::draw_vertex(float x, float y) {
    //circle
    glBegin(GL_POLYGON);
    glColor3f(.9098f, .8941f, .00785f);
    float theta;
    for (int i = 0; i < 100; i++) {
        theta = 2.0f * 3.1415926f * float(i) / float(100);//get the current angle 
        x += 0.008 * cosf(theta);//calculate the x component 
        y += 0.008 * sinf(theta);//calculate the y component 
        glVertex2f(x, y);//output vertex 
    }
    glEnd();

    //border
    glBegin(GL_LINE_LOOP);
    glColor3f(0.f, 0.f, 0.f);
    for (int i = 0; i < 100; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(100);
        x += 0.008 * cosf(theta);//calculate the x component 
        y += 0.008 * sinf(theta);//calculate the y component 
        glVertex2f(x, y);
    }
    glEnd();
}


void UI::draw_edge(float x1, float y1, float x2, float y2) {
    glColor3f(0.f, 0.f, 0.f);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}


void UI::put_name(string& name, GLfloat x, GLfloat y) {
    bool f = false;
    for (auto const& gr : (*graph_ptr).work) {
        if (gr.second->adj.size()!=0) f = true;
    }
    if (f) {
        GLTtext* text = gltCreateText();
        gltSetText(text, name.c_str());
        texts.push_back(text);
        gltBeginDraw();
        gltColor(1.f, 1.f, 1.f, 1.f);
        gltDrawText2D(text, (x + 0.95) * 450, (y + 0.85) * 450, 1);
        gltEndDraw();
    }
}

void UI::clear_names() {
    for (auto text : texts) {
        gltDeleteText(text);
    }
    texts.clear();
}
