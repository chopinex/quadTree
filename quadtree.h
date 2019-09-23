#include <vector>

#define BUCKET 5
#define MAXDEPTH 6
#ifndef QUADTREE_H
#define QUADTREE_H

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

	int depth(){
	    if(cuadrantes[0])
            return 1+std::max(cuadrantes[0]->depth(),std::max(cuadrantes[1]->depth(),std::max(cuadrantes[2]->depth(),cuadrantes[3]->depth())));
        return 0;
	}

public:
    punto2d p1,p2,c1,c2;
    //int cx,cy,dim=0;
	bool isInBoundary(punto2d);
	bool colision(int,int,int,int);
	void insertar(punto2d);
	void draw();
	void cuadro(int,int,int,int);
	void busqueda(int,int,int,int);
};
#endif
