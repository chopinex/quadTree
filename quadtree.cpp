#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <iostream>
#include "quadTree.h"
#include<GL/glut.h>
#include <vector>

#define forp for(vector<punto2d>::iterator it=puntos.begin();it!=puntos.end();it++)

using namespace std;

bool quadTree::isInBoundary(punto2d p){
		return (p.x>p1.x&&p.y<p1.y&&p.x<p2.x&&p.y>p2.y);
}

void quadTree::insertar(punto2d p){
	if (!isInBoundary(p))
		return;
	if (depth()<MAXDEPTH&&!used&&puntos.size()<BUCKET)
        puntos.push_back(p);
	else{
        if (!cuadrantes[0]){
            used=1;
            punto2d int0=pm(p1,p2);
            punto2d int1={int0.x,p1.y,0};
            punto2d int2={p2.x,int0.y,0};
            punto2d int3={p1.x,int0.y,0};
            punto2d int4={int0.x,p2.y,0};
            cuadrantes[0]=new quadTree;cuadrantes[0]->p1=p1;cuadrantes[0]->p2=int0;
            cuadrantes[1]=new quadTree;cuadrantes[1]->p1=int1;cuadrantes[1]->p2=int2;
            cuadrantes[2]=new quadTree;cuadrantes[2]->p1=int3;cuadrantes[2]->p2=int4;
            cuadrantes[3]=new quadTree;cuadrantes[3]->p1=int0;cuadrantes[3]->p2=p2;
            forp{
                cuadrantes[0]->insertar(*it);
                cuadrantes[1]->insertar(*it);
                cuadrantes[2]->insertar(*it);
                cuadrantes[3]->insertar(*it);
            }
            puntos.clear();
        }
        cuadrantes[0]->insertar(p);
        cuadrantes[1]->insertar(p);
        cuadrantes[2]->insertar(p);
        cuadrantes[3]->insertar(p);
	}

}

void quadTree::draw(){
    if(cuadrantes[0])
        for(int i=0;i<4;++i)
            cuadrantes[i]->draw();
    else{
        glBegin(GL_LINE_LOOP);
        glColor3d(0.5,0.5,0.5);
        glVertex2d(p1.x, p1.y);
        glVertex2d(p2.x, p1.y);
        glVertex2d(p2.x, p2.y);
        glVertex2d(p1.x, p2.y);
        glEnd();
        glPointSize(3);
        glBegin(GL_POINTS);
        forp{
            if((*it).found)
                glColor3d(1,1,0);
            else
                glColor3d(1,0,0);
            glVertex2d((*it).x, (*it).y);
        }
        glEnd();
    }
}

void quadTree::cuadro(int x0,int x1,int y0,int y1){
        glBegin(GL_LINE_LOOP);
        glColor3d(0.8,0.8,0);
        glVertex2d(x0, y0);
        glVertex2d(x1, y0);
        glVertex2d(x1, y1);
        glVertex2d(x0, y1);
        glEnd();
}
bool quadTree::colision(int x0,int x1,int y0, int y1){
    return ((x0<=p2.x&&y1>=p2.y)||(x1>=p1.x&&y0<=p1.y));
}

void quadTree::busqueda(int x0,int x1,int y0,int y1){
    if(cuadrantes[0]){
        for(int i=0;i<4;++i)
            if(cuadrantes[i]->colision(x0,x1,y0,y1))
                cuadrantes[i]->busqueda(x0,x1,y0,y1);
    }
    else{
        forp{
            if((*it).x>=x0&&(*it).x<=x1&&(*it).y<=y1&&(*it).y>=y0)
                (*it).found=1;
            else
                (*it).found=0;
        }
    }
}

