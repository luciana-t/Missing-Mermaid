#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <GL/glut.h>
#include <array>
#include <iostream>
#include <cmath> 


#include "func.h"

using namespace std;

typedef array<GLfloat,3> Point; //ponto do espaço 3D
typedef array<int, 3> Face; //faces do objeto

int window_width = 800, window_height = 600;

struct Objeto3D {
	Objeto3D() {
		velocidade = 0;
		deslocamento = rotacao = { 0,0,0 };
	}

	vector<Face> faces;
	vector<Point> vertices;

    array<GLfloat, 3> rotacao;
    array<GLfloat, 3> deslocamento;
    GLfloat velocidade;
    

    //posiciona o ponto medio do objeto em 0,0,0
    void transladaOrigem(){
        Point medio{0,0,0};
        for(auto &v:vertices){ 
            for(int i = 0; i < 3; i++)
                medio[i] += v[i];
        }

        for(int i = 0; i < 3; i++)
            medio[i] /= vertices.size(); 

        for(auto &v:vertices){
            for(int i = 0; i < 3; i++){
                v[i] -= medio[i];
                //cerr << v[i] << " ";
            }   //cerr << endl;
        }
    }

    //função draw
    void draw(){
        glPushMatrix();
        glTranslatef(deslocamento[0], deslocamento[1], deslocamento[2]);
        glRotatef(rotacao[0], 1, 0, 0);
        glRotatef(rotacao[1], 0, 1, 0);
        glRotatef(rotacao[2], 0, 0, 1);

        for(auto &t:faces){
            glBegin(GL_TRIANGLES);
                for(int i = 0; i < 3; i++) {
                    glVertex3f(vertices[t[i]][0], vertices[t[i]][1], vertices[t[i]][2]);
                    glColor3f(1, 0, 0);
                }
            glEnd();
        }

        glPopMatrix();
    }

    //função translada 
    void translada(GLfloat dx0, GLfloat dy0, GLfloat dz0){
        deslocamento[0] += dx0;
        deslocamento[1] += dy0;
        deslocamento[2] += dz0;
    }

    void rotaciona(GLfloat dx0, GLfloat dy0, GLfloat dz0) {
        rotacao[0] += dx0;
        rotacao[1] += dy0;
        rotacao[2] += dz0;
    }
};

// Faces sempre triangulares (malha triangular)
void parseObject(Objeto3D &o, const string &file){

    ifstream fin(file.c_str());
    string temp;

    o = Objeto3D();
// MEU CUBO PARA TESTAR AS COISAS DO JOGO!! COMENTE DAQUI...
    o.vertices = {
        { 0.0,  0.0,  0.0},
        { 0.0,  0.0,  1.0},
        { 0.0,  1.0,  0.0},
        { 0.0,  1.0,  1.0},
        { 1.0,  0.0,  0.0},
        { 1.0,  0.0,  1.0},
        { 1.0,  1.0,  0.0},
        { 1.0,  1.0,  1.0}
    };

    o.faces = {
        { 0,  6,  4},
        { 0,  2,  6},
        { 0,  3,  2},
        { 0,  1,  3},
        { 2,  7,  6},
        { 2,  3,  7},
        { 4,  6,  7},
        { 4,  7,  5},
        { 0,  4,  5},
        { 0,  5,  1},
        { 1,  5,  7},
        { 1,  7,  3}
    };
//                          ..ATÉ AQUI
    

    /*
    while(fin >> temp){
        if(temp == "v"){ //linha que caracteriza um vértice
            Point ponto;
            fin >> ponto[0] >> ponto[1] >> ponto[2];
            o.vertices.push_back(ponto);
        
        }
		else if(temp == "vt"){ //trabalho3
            GLfloat a, b;
            fin >> a >> b;
        }else if(temp == "vn"){ //trabalho3
            GLfloat a, b, c;
            fin >> a >> b >> c;
        }else if (temp == "f"){ //processar faces

            string s;
            getline(fin, s);
            stringstream ss(s);

            int a, b, c, tempF;
            char tempC;

            if(s.find("/") == string::npos){
                ss >> a >> b >> c;
            }else{
                ss >> a >> tempC >> tempF >> tempC >> tempF;
                ss >> b >> tempC >> tempF >> tempC >> tempF;
                ss >> c >> tempC >> tempF >> tempC >> tempF;
            }
			
            a--;
            b--;
            c--;
            o.faces.push_back({a,b,c});
			
        }
    }
*/
}

vector<Objeto3D> g_objetos;
Objeto3D g_submarino;


void load(){

	vector<string> file_names = {"dog.obj", "dog.obj", "dog.obj"};
	
	parseObject(g_submarino, "dog.obj");

    g_submarino.transladaOrigem();
    g_submarino.translada(0,0,-2);

	g_objetos.resize(file_names.size());

	for(size_t i=0; i < file_names.size(); i++){

		parseObject(g_objetos[i], file_names[i]);
        g_objetos[i].transladaOrigem();
    }
}

GLvoid init(){
    glClearColor(0, 0.2, 0.5, 1.0);
}

GLvoid reshape(GLint width, GLint height){

    g_window_width = width;
    g_window_height = height;

    g_ratio = (GLdouble)width/(GLdouble)height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-g_ratio, g_ratio, -1, 1, g_near, g_far);

    glViewport(0, 0, width, height);

    //cout << width <

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    cout << g_ratio << endl;

    //gluLookAt
}

GLfloat rot = 0.0f;

GLvoid display(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //g_submarino.rotaciona(0, rot, 0);
    //rot += 0.0001f; //GIRANDO O CUBO

    g_submarino.draw();

    func_keyboard();

/* TRIANGULO PARA TESTE
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5, -0.5, -10.0); glColor3f(1, 0, 0);
    glVertex3f(0.5, -0.5, -10.0); glColor3f(0, 1, 0);
    glVertex3f(0.0, 0.5, -10.0); glColor3f(0, 0, 1);
    glEnd();
*/
    glutSwapBuffers();

}

void idle() {
    glutPostRedisplay();
}

int main(GLint argc, GLchar **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-window_width)/2,(glutGet(GLUT_SCREEN_HEIGHT)-window_height)/2); //centralizar janela
	glutCreateWindow("Trabalho 2");

	load();

    init(); 
    glutDisplayFunc(display); 
	/*glutSpecialFunc(keyboard_espec); // ainda nao foi feita
	glutKeyboardFunc(keyboard); // ainda nao foi feita
	glutTimerFunc(menu_update_delay,update,1); // ainda nao foi feita 
	*/

    glutReshapeFunc(reshape);

	/*glutMouseFunc(mouseClick); // ainda nao foi feita
	glutSpecialUpFunc(keyUp); // ainda nao foi feita

    glutMotionFunc(mouseMove); // ainda nao foi feita
    glutPassiveMotionFunc(mouseMovePassivo); // ainda nao foi feita
    glutKeyboardUpFunc(keyDown); // ainda nao foi feita
*/
    glutIdleFunc(idle); 
    
    glutMainLoop();

	return 0;
}




