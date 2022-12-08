
#include <iostream>  
#include <armadillo>
#include "include/Cannon.hpp"
#include "include/Object.hpp"
#include "include/Transform.hpp"
#include <GL/glu.h>
#include <GLFW/glfw3.h>

using namespace std;
int main()
{
    GLFWwindow* window;

    if( !glfwInit() )
    {
        fprintf( stderr, "Fallo al inicializar GLFW\n" );
        getchar();
        return -1;
    }

    window = glfwCreateWindow(1024, 768, "Ejemplo OpenGL", NULL, NULL);
    if( window == NULL ) {
        fprintf( stderr, "Fallo al abrir la ventana de GLFW.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Proyeccion
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    int ancho, altura;
    glfwGetFramebufferSize(window, &ancho, &altura);
    float ar = ancho/altura;
    // Paralelo
    //glViewport(0, 0, ancho, altura);
    //glOrtho(-ar, ar, -1.0, 1.0, -20.0, 20.0);
    
    //prespectiva
    glFrustum(-ar, ar, -ar, ar, -2.0, 4.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    arma::frowvec eye = {0.0, 0.0, 1.0};
    arma::frowvec camera = {0.0, 0.0, 0.0};
    arma::frowvec upvector = {0.0, 1.0, 0.0};
    Cannon cn(10);
    do {
        glClear( GL_COLOR_BUFFER_BIT );
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye[0], eye[1], eye[2],  camera[0], camera[1], camera[2],  upvector[0], upvector[1], upvector[2]);
        cn.plot();
        if(!cn.fueDisparado()){
            double inclinacion = cn.getterInclinacion();
            int state_up = glfwGetKey(window,GLFW_KEY_UP);
            if(state_up == GLFW_PRESS && cn.getterInclinacion()<=80)
            {   
                inclinacion+= 10.0;
            }
            int state_down = glfwGetKey(window,GLFW_KEY_DOWN);
            if(state_down == GLFW_PRESS && cn.getterInclinacion()>=0)
            {   
                inclinacion-= 10.0;            
            }
            cn.setterInclinacion(inclinacion);
        }
        int state_sp = glfwGetKey(window,GLFW_KEY_SPACE);
        if(state_sp == GLFW_PRESS)
        {   
            cn.shoot(0.8);           
        }
        int state_r = glfwGetKey(window,GLFW_KEY_R);
        if(state_r == GLFW_PRESS)
        {   
            cn.resetear();           
        }
        glfwSwapBuffers(window);
        glfwPollEvents();

    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    glfwTerminate();

    return 0;
}
    
    

    