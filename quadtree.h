#include <vector>
#include <string>

#define BUCKET 7
#define MAXDEPTH 7
#ifndef QUADTREE_H
#define QUADTREE_H

using namespace std;
struct punto2d{
	float x,y;
	bool found;
};

class quadTree{
	std::vector<punto2d> puntos;
    quadTree* cuadrantes[4]={NULL,NULL,NULL,NULL};//cuadrantes[0]=NO,cuadrantes[1]=NE,cuadrantes[2]=SO,cuadrantes[3]=SE
    bool used=0;
    punto2d pm(punto2d np1,punto2d np2){
		punto2d ret;
		ret.x=(np1.x+np2.x)/2;
		ret.y=(np1.y+np2.y)/2;
		ret.found=0;
		return ret;
	}
public:
    int depth=1;
    punto2d p1,p2,c1,c2;
    bool isInBoundary(punto2d);
	bool colision(int,int,int,int);
	void insertar(punto2d);
	void draw();
	void cuadro(int,int,int,int);
	void busqueda(int,int,int,int);
	void leerArchivo(string);
};
#endif
