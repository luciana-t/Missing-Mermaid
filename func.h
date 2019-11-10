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
GLboolean g_keyboard_espec[4] = {false}; // left, right, up, down

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

GLvoid keyDown(GLubyte key, GLint x, GLint y){ // contrario do default keyboard, switch

    g_keyboard[key] = false;
    if(key >= 'A' && key <= 'Z')
        g_keyboard[key+('a'-'A')] = false;
    if(key >= 'a' && key <= 'z')
        g_keyboard[key+('a'-'A')] = false;

}

GLvoid keyUp(GLint key, GLint x, GLint y){

    switch (key){
        case GLUT_KEY_LEFT:
            g_keyboard_espec[0] = true;
            break;
        case GLUT_KEY_RIGHT:
            g_keyboard_espec[1] = true;
            break;
        case GLUT_KEY_UP:
            g_keyboard_espec[2] = true;
            break;
        case GLUT_KEY_DOWN:
            g_keyboard_espec[3] = true;
            break;
    }
}

GLvoid keyboard_espec(GLint key, GLint x, GLint y){ // contrario do default keyUp, switch

    switch (key){
        case GLUT_KEY_LEFT:
            g_keyboard_espec[0] = false;
            break;
        case GLUT_KEY_RIGHT:
            g_keyboard_espec[1] = false;
            break;
        case GLUT_KEY_UP:
            g_keyboard_espec[2] = false;
            break;
        case GLUT_KEY_DOWN:
            g_keyboard_espec[3] = false;
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

    if(g_keyboard['s'] || g_keyboard['S']){
    
        if(g_submarino.velocidade<-400)
            g_submarino.velocidade -= 5;
    }
    else if (g_submarino.velocidade > 0)
        g_submarino.velocidade += 10;

    if(g_keyboard_espec[2]){ // KEY UP
        if(g_submarino.speed_rotate > -50)
            g_submarino.speed_rotate -= 5;
    }
    else if (g_submarino.speed_rotate < 0)
        g_submarino.speed_rotate +=5;
    

    if(g_keyboard_espec[3]){ // KEY DOWN
        if(g_submarino.speed_rotate < 50)
            g_submarino.speed_rotate += 5;
    }
    else if (g_submarino.speed_rotate > 0)
        g_submarino.speed_rotate -=5;

    
}








#endif 