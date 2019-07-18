#ifndef CSCIx229
#define CSCIx229

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

#ifdef __cplusplus
extern "C" {
#endif

void Print(const char* format , ...);
void Fatal(const char* format , ...);
unsigned int LoadTexBMP(const char* file);
//void Project(double fov,double asp,double dim);
void ErrCheck(const char* where);
//int  LoadOBJ(const char* file);
/*
void pot(double x, double y, double z, double rL, double rS, double hPot);
void cylinder(double x, double y, double z, double rx, double ry, double rz, double ang, double sx, double sy, double sz, double h);
void cylinder2(double x, double y, double z, double rx, double ry, double rz, double ang, double sx, double sy, double sz, double rL, double rS, double h);
void cone(double x, double y, double z, double rx, double ry, double rz, double ang, double sx, double sy, double sz, double h);
void Vertex(double th,double ph);
void sphere(double x,double y,double z,double sx, double sy, double sz);
void sun(double x,double y,double z,double r);
void leaf(double x, double y, double z, double rx, double ry, double rz, double ang, double sx, double sy, double sz, double h);
void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th);

*/




#ifdef __cplusplus
}
#endif

#endif
