#ifndef FUNC_H
#define FUNC_H

#include <GL/glut.h>

#include <iostream>
#include <vector>


//Variaveis Globais:

GLint g_window_width, g_window_height;
GLdouble g_ratio;
GLint g_near = 1, g_far = 10000;
GLboolean g_keyboard[500] = {false};
GLboolean g_keyboard_spec[4] = {false}; // left, right, up, down

GLvoid keyboard(GLubyte key, GLint x, GLint y){
    
    switch (key)
    {
    case 'F':
    case 'f':
        //first person
        break;

    case 'H':
    case 'h':
        //help menu
        break;

    case 'I':
    case 'i':
        //outside 
        break;
    
    default:
        g_keyboard[key] = true;
        if(key >= 'A' && key <= 'Z')
            g_keyboard[key+('a'-'A')] = true;
        if(key >= 'a' && key <= 'z')
            g_keyboard[key+('a'-'A')] = true;
    }
}

GLvoid keyDown(GLubyte key, GLint x, GLint y){ // contratio do default keyboard, switch

    g_keyboard[key] = false;
    if(key >= 'A' && key <= 'Z')
        g_keyboard[key+('a'-'A')] = false;
    if(key >= 'a' && key <= 'z')
        g_keyboard[key+('a'-'A')] = false;

}

GLvoid keyUp(GLint key, GLint x, GLint y){

    switch (key)
    {
    case GLUT_KEY_LEFT:
        g_keyboard_spec[0] = true;
        break;
    
    default:
        break;
    }
}


GLvoid func_keyboard(){
    if(g_keyboard['w'] || g_keyboard['W']){
    
        if(g_submarino.velocidade<1000)
            g_submarino.velocidade += 10;
    }
    else if (g_submarino.velocidade > 0)
        g_submarino.velocidade -= 10;
}








#endif 