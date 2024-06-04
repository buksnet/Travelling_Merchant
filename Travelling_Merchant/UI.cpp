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
        glLineWidth(1.f);
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
        if (hasSolution) draw_solution();
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

void UI::solve_init(vector<pair<int, int>> arg)
{
    data = arg;
    hasSolution = true;
}

vector<pair<float, float>> UI::fetch_coordinates(pair<int, int> coord, int q) {
    float theta = 2.0f * 3.1415926f * float(coord.first - 1) / float(q), x, y, x1, y1;
    vector < pair<float, float>> result;
    pair<float, float> one, two;
    one.first = 0.55 * cosf(theta);
    one.second = 0.55 * sinf(theta);
    
    theta = 2.0f * 3.1415926f * float(coord.second-1) / float(q);
    two.first = 0.55 * cosf(theta);
    two.second = 0.55 * sinf(theta);
    result.push_back(one);
    result.push_back(two);
    return result;
}

void UI::draw_solution()
{
    vector<pair<float, float>> coord;
    for (vector<pair<int, int>>::iterator it = data.begin(); it != data.end(); it++) {
        glColor3f(0.f, 0.5f, 0.f);
        glLineWidth(5.f);
        glBegin(GL_LINES);
        coord = fetch_coordinates((*it), data.size());
        glVertex2f(coord[0].first-0.02, coord[0].second+0.18);
        glVertex2f(coord[1].first-0.02, coord[1].second+0.18);
        glEnd();
    }
}
