/*
 * hw3 
 * Lauren Strand
 */

// correct makefile
// when zip, unpack in root directory (not sub)
// compile cleanly
#include "CSCIx229.h"
/*
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
*/
// Global variables -------------------------------------------------------

int th=0;	//Rotation (viewing) angle
int ph=0; 	//Elevation of view angle
/*  Lorenz Parameters  */
int mode=0; 
int fov = 55;
int axes = 0;
double zz=0;
double w=1;
double asp = 1;
double dim = 5.0;
int light = 1;
int move=1;

// Light values
int one       =   1;  // Unit value
int distance  =   4;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  55;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light
unsigned int texture[5]; // Texture names

// ------------------------------------------------------------------------
//  Cosine and Sine in degrees
//#define Cos(x) (cos((x)*3.1415927/180))
//#define Sin(x) (sin((x)*3.1415927/180))


// variables used for fp --------------------------------------------------
double Cx = 0;
double Cy = 0;
double Cz = 0;
int fp=0;
int rot=0;
double Ex = 0;
double Ey = 0;
double Ez = 0;


//  Print function used from ex6.c  ----------------------------------------
/*
#define LEN 8192  // Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}
*/
// -------------------------------------------------------------------------

static void Project()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   if(fp){
		gluPerspective(fov,asp,dim/4,4*dim);
   }
   else{
	   	//  Perspective transformation
	   if (mode)
	      gluPerspective(fov,asp,dim/4,4*dim);
	   //  Orthogonal projection
	   else
	      glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
	   //  Switch to manipulating the model matrix
   }
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

static void pot(double x, double y, double z, double rL, double rS, double hPot){
	const int d=5;
	int thi;
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glPushMatrix();
	glTranslated(x,y,z);
	//glScaled(1,hPot,1);

	glBindTexture(GL_TEXTURE_2D,texture[1]);
	glBegin(GL_QUAD_STRIP);
	
	// draw sides of pot
	for(thi = 0; thi<=360; thi+=d){
		glNormal3f(Cos(thi), (rL-rS)/hPot, Sin(thi));
		glColor3f(0.48, 0.25, 0.14);
		glTexCoord2f(0.0,0.0);
		glVertex3d(Cos(thi)*rL, 0, Sin(thi)*rL);
		//glVertex3d(Cos(th+d), -1, Sin(th+d));
		glTexCoord2f(0.6,0.0);
		glVertex3d(Cos(thi+d)*rS, -hPot, Sin(thi+d)*rS);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// draw end (bottom) cap
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D,texture[1]);
	glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1,1);
	glBegin(GL_TRIANGLE_FAN);
	
	
	glVertex3d(0,-hPot,0);
	for(thi=0; thi<=360; thi+=d){
		glNormal3f(0,-1,0);
		glTexCoord2f(rS*Cos(thi+d),rS*Sin(thi+d));
		glVertex3d(Cos(thi+d)*rS, -hPot,Sin(thi+d)*rS);
	}
	glEnd();

	// draw dirt (at top)
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

	glEnable(GL_POLYGON_OFFSET_FILL);
	glBindTexture(GL_TEXTURE_2D,texture[3]);
    glPolygonOffset(1,1);
	glBegin(GL_TRIANGLE_FAN);
	
	glColor3f(0.623, 0.329, 0.035);
	glTexCoord2f(0.5,0.5);
	glVertex3d(0,0,0);
	for(thi=0; thi<=360; thi+=d){
		glNormal3f(0,1,0);
		glColor3f(0.623, 0.329, 0.035);
		//glColor3f(1,1,1);
		glTexCoord2f(0.5*Cos(thi)+0.5,0.5*Sin(thi)+0.5);
		glVertex3d(rL*Cos(thi),0,rL*Sin(thi));
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

// aloeLeaf creates end caps and allows different radii
static void aloeLeaf(double x, double y, double z, double rx, double ry, double rz, double ang, double sx, double sy, double sz, double rL, double rS, double h){
	const int d=5;
	int thi;
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glPushMatrix();
	glTranslated(x,y,z);
	glRotated(ang, rx,ry,rz);
	glScaled(sx,sy,sz);
	glBindTexture(GL_TEXTURE_2D, texture[2]); // aloe texture
	glBegin(GL_QUAD_STRIP);
	// draw sides 
	for(thi = 0; thi<=360; thi+=d){
		//glColor3f(0.48, 0.25, 0.14);
		glNormal3f(Cos(thi), (rL-rS)/h, Sin(thi));
		//glTexCoord2f(0.0,0.0);
		glTexCoord2f(0.5*Cos(thi),0.5*Sin(thi));
		glVertex3d(Cos(thi)*rL, 0, Sin(thi)*rL);
		
		//glTexCoord2f(1.0,0.0);
		glTexCoord2f(0.5*Cos(thi+d),0.5*Sin(thi+d));
		glVertex3d(Cos(thi+d)*rS, 1, Sin(thi+d)*rS);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// draw end (bottom) cap
	glEnable(GL_POLYGON_OFFSET_FILL);
	glNormal3f(0,-1,0);
    glPolygonOffset(1,1);
	glBegin(GL_TRIANGLES);
	glVertex3d(0,0,0);
	for(thi=0; thi<=360; thi+=d){
		glVertex3d(Cos(thi+d)*rL, 0,Sin(thi+d)*rL);
	}
	glEnd();
	glPopMatrix();

}

static void cylinder(double x, double y, double z, double rx, double ry, double rz, double ang, double sx, double sy, double sz, double rL, double rS, double h){
	// cylinder used when drawing jade stem
	const int d=5;
	int thi;
	//glEnable(GL_TEXTURE_2D);
	//glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	//glBindTexture(GL_TEXTURE_2D,texture[4]);

	glPushMatrix();
	glTranslated(x,y,z);
	glRotated(ang, rx,ry,rz);
	glScaled(sx,sy,sz);
	glBegin(GL_QUAD_STRIP);
	// draw sides 
	for(thi = 0; thi<=360; thi+=d){
		glNormal3f(Cos(thi), (rL-rS)/h, Sin(thi));
		glTexCoord2f(Cos(thi),0.0);
		glVertex3d(Cos(thi)*rL, 0, Sin(thi)*rL);
		glTexCoord2f(Sin(thi),0.0);
		glVertex3d(Cos(thi+d)*rS, 1, Sin(thi+d)*rS);
	}
	glEnd();
	//glDisable(GL_TEXTURE_2D);

	// draw end (bottom) cap
	glEnable(GL_POLYGON_OFFSET_FILL);
	glNormal3f(0,-1,0);
    glPolygonOffset(1,1);
	glBegin(GL_TRIANGLES);
	glVertex3d(0,0,0);
	for(thi=0; thi<=360; thi+=d){
		glTexCoord2f(Cos(thi+d)*rL,0);
		glVertex3d(Cos(thi+d)*rL, 0,Sin(thi+d)*rL);
	}
	glEnd();
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

static void jadeStem(){
	glPushMatrix();
	//glTranslated(x,y,z);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,texture[4]);
	cylinder(4,0.62,0, 4,0,0, 3, 1,0.71,1, 0.1, 0.02, -1.5);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

// vertex code used from ex8
static void Vertex(double th,double ph)
{
   //glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
   double x = -Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   glNormal3d(x,y,z);
   glTexCoord2d(th/360.0,ph/180.0+0.5);
   //glTexCoord2d(th/360.0,ph/180.0);
   glVertex3d(x,y,z);
   // all 3 values positive and in range (0,1)
   // Sin and Cos (not sin and cos) in deg!!! 
}

// sphere code used from ex8
static void sphere(double x,double y,double z,double sx, double sy, double sz)
{
   // better than 1st bc performance-wise not a huge difference but much more readable 
   const int d=1;
   // probs wanna increase value to make code in other cases work best
   // when changing, REMEMBER d MUST DIVIDE EVENLY BY 360
   int th1,ph1;
   //float yellow[] = {1.0,1.0,0.0,1.0};
   //float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(sx,sy,sz);
   //  Latitude bands
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   //glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
   glBindTexture(GL_TEXTURE_2D,texture[4]);
   for (ph1=-90;ph1<90;ph1+=d)
   {
      glBegin(GL_QUAD_STRIP);
      for (th1=0;th1<=360;th1+=d)
      {
         Vertex(th1,ph1);
         Vertex(th1,ph1+d);
      }
      glEnd();
   }
   glDisable(GL_TEXTURE_2D);
   //  Undo transformations
   glPopMatrix();
}

static void sun(double x,double y,double z,double r)
{
   int th,ph;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
      // associate material property w every vertex
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

// cube function from ex8
static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
	//  Set specular color to white
   float white[] = {1,1,1,1};
   float black[] = {0,0,0,1};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

   // Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   //glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  
   //  Cube
   glBegin(GL_QUADS);
   //  Front
   glVertex3f(-1,-1, 1);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(1.0,0.0);

   glVertex3f(+1,-1, 1);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0.0,0.0);
   
   glVertex3f(+1,+1, 1);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0.0,1.0);
   
   glVertex3f(-1,+1, 1);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(1.0,1.0);
   //  Back
   
   glVertex3f(+1,-1,-1);
   glNormal3f( 0, 0,-1);
   //glTexCoord2f(0.0,0.0);
   glTexCoord2f(0.0,0.0);

   glVertex3f(-1,-1,-1);
   glNormal3f( 0, 0,-1);
   //glTexCoord2f(1.0,0.0);
   glTexCoord2f(1.0,0.0);
   
   glVertex3f(-1,+1,-1);
   glNormal3f( 0, 0,-1);
   //glTexCoord2f(1.0,1.0);
   glTexCoord2f(0.0,1.0);
   
   glVertex3f(+1,+1,-1);
   glNormal3f( 0, 0,-1);
   //glTexCoord2f(0.0,1.0);
   glTexCoord2f(1.0,1.0);
   
   //  Right
   glVertex3f(+1,-1,+1);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0.0,0.0);

   glVertex3f(+1,-1,-1);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(1.0,0.0);
   
   glVertex3f(+1,+1,-1);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(1.0,1.0);

   glVertex3f(+1,+1,+1);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0.0,1.0);
   //  Left
   glVertex3f(-1,-1,-1);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0.0,0.0);

   glVertex3f(-1,-1,+1);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(1.0,0.0);
   
   glVertex3f(-1,+1,+1);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(1.0,1.0);
   
   glVertex3f(-1,+1,-1);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0.0,1.0);
   //  Top
   glVertex3f(-1,+1,+1);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0.0,0.0);

   glVertex3f(+1,+1,+1);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(1.0,0.0);

   glVertex3f(+1,+1,-1);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(1.0,1.0);

   glVertex3f(-1,+1,-1);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0.0,1.0);
   //  Bottom
   glVertex3f(-1,-1,-1);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(0.0,0.0);

   glVertex3f(+1,-1,-1);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(1.0,0.0);

   glVertex3f(+1,-1,+1);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(1.0,1.0);

   glVertex3f(-1,-1,+1);
   glNormal3f( 0,-1, 0);
   glTexCoord2f(0.0,1.0);
   //  End
   glEnd();
   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void table(double x, double y, double z, double sx, double sy, double sz){
	glScaled(sx,sy,sz);
	glColor3f(1,1,1);
	cube(x,y,z, 3.4, 0.2, 1.3, 0);
	cube(x-2,y-1.2,z, 0.2, 1.2, 0.8, 0);
	cube(x+2,y-1.2,z, 0.2, 1.2, 0.8, 0);
}

static void aloe(double s, double x, double y, double z){
	glScaled(s,s,s);
	glTranslated(x,y,z);
	pot(0,0,0, 0.8, 0.6, 1.5);
		glColor3f(0.19, 0.35, 0.09); // dark green
		//         x, y, z,    rx, ry, rz, ang, sx, sy, sz, rL, rS, h
		aloeLeaf(-0.1,0,0.05, 0,0,1, 0, 0.08,1.7,0.1, 1,0, 2);
		aloeLeaf(0,0,0.05, 0,0,-1, 10, 0.08,1.78,0.08, 1,0, 2);
		glColor3f(0.298, 0.556, 0.145); // light
		aloeLeaf(0,0,-0.1, -0.8,0,0, 10, 0.1,1.69,0.06, 1,0, 2);
		aloeLeaf(0.15,0,0, 0,0,-1, 20, 0.05,1.6,0.15, 1,0, 2);
		aloeLeaf(-0.15,0,0, 0,0,1, 20, 0.05,1.4,0.15, 1,0, 2);
		glColor3f(0.19, 0.35, 0.09); // dark green
		aloeLeaf(0,0,-0.2, -1,0,0, 15, 0.15,1.5,0.05, 1,0, 2);
		aloeLeaf(0.07,0,0.18, 1,0,0, 15, 0.15,1.6,0.09, 1,0, 2);
		glColor3f(0.298, 0.556, 0.145); // light
		aloeLeaf(-0.18,0,-0.15, -0.8,0,0.5, 22, 0.1,1.7,0.13, 1,0, 2);
		glColor3f(0.19, 0.35, 0.09); // dark green
		aloeLeaf(-0.21,-0.08,0.25, 1,-1,0.5, 24, 0.12,1.6,0.13, 1,0, 2);
		aloeLeaf(0.21,-0.08,0.19, 0,0,-0.8, 29, 0.1,1.6,0.13, 1,0, 2);
		glColor3f(0.298, 0.556, 0.145); // light
		aloeLeaf(0.21,-0.08,-0.19, -0.2,0,-1, 32, 0.15,1.4,0.12, 1,0, 2);
		aloeLeaf(-0.32,-0.08,0, 0,0,1, 32, 0.1,1.68,0.17, 1,0, 2);
}

static void jade(double x, double y, double z){
	glTranslated(x,y,z);
	pot(4,0.62,0,0.7, 0.5, 2);
	glColor3f(0.2, 0.533, 0.168);
	//cylinder(4,0.62,0, 4,0,0, 3, 1,0.71,1, 0.1, 0.02, -1.5);
	jadeStem();
	glColor3f(0.14, 0.42, 0.14);
	sphere(4,0.71,0.4, 0.2,0.1,0.35);
	sphere(4,0.69,-0.4, 0.2,0.1,0.3);
	sphere(4.2,1,0, 0.3,0.1,0.22);
	sphere(3.74,1.22,0.19, 0.3,0.1,0.22);
	sphere(4.05,1.29,-0.17, 0.18,0.1,0.24);
}

static void halfleafyLeaf(){
	// x y z defines initial coordinate
	double length = 0;
	int thi,phi;
	const int d = 5;
	glPushMatrix();
	glColor3f(0.5,0.5,1);
	glBegin(GL_TRIANGLES);
	//glVertex3d(0,0,0);
	// bottom face
	
	for(thi = 0; thi<=180-d; thi+=d){		
		glNormal3f(0,-1,0);
		glVertex3d(0,0,0);
		glVertex3d(length*Cos(thi), 0, length*Sin(thi));
		length += 0.07;	
		glVertex3d(length*Cos(thi+d), 0, length*Sin(thi+d));
	}
	glEnd();

	// sides
	glBegin(GL_QUAD_STRIP);
	length = 0;
	for(thi = 0; thi<=180; thi +=d){
		glNormal3f(length*Cos(thi), 0, length*Sin(thi));
		glVertex3d(length*Cos(thi), 0, length*Sin(thi));
		glVertex3d(length*Cos(thi), 0.1, length*Sin(thi));
		length += 0.07;
	}
	glEnd();
	
	// top face
	//glBegin(GL_TRIANGLE_FAN);
	glBegin(GL_TRIANGLES);
	
	// bottom face
	glColor3f(0.5,0.5,1);
	length = 0;
	
	for(thi = 0; thi<=180-d; thi+=d){
		glNormal3f(0,1,0);
		glVertex3d(0,0.1,0);
		glVertex3d(length*Cos(thi), 0.1, length*Sin(thi));
		length += 0.07;	
		glVertex3d(length*Cos(thi+d), 0.1, length*Sin(thi+d));
	}
	glEnd();
	
	glPopMatrix();
}
static void fullLeafyLeaf(double x, double y, double z, double rx, double ry, double rz, double ang, double sx, double sy, double sz){
	
	glRotated(ang,rx,ry,rx);
	glTranslated(x,y,z);
	glScaled(sx,sy,sz);

	halfleafyLeaf();

	glPushMatrix();
	//glTranslated(0, 0.1,0);
	glRotated(180,1,0,0);
	glScaled(1,-1,1);
	halfleafyLeaf();
	glPopMatrix();
}

static void leafyPlant(double x, double y, double z, double sx, double sy, double sz){
	glTranslated(x,y,z);
	glScaled(sx,sy,sz);

	table(2, 0, -3, 1,1,1);
	//double x, double y, double z, double rL, double rS, double hPot
	pot(1,1.5,-3, 0.8, 0.6, 1.5);
	// cylinder(x, y, z, rx, ry, rz, ang, sx, sy, sz, rL, rS, h)
	glColor3f(0.113, 0.376, 0.082);
	cylinder(1, 1.5, -3, 0,0,0,0, 1,1,1, 0.1, 0.04, 5);
	// x y z rx ry rz ang sx sy sz
	fullLeafyLeaf(2,0,0, 0,0,0,0, 0.2,0.5,0.1);	

}

void display(){
	//const double len=5;  //  Length of axes
	//Clear screen 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	//glRotatef(ph,1,0,0);
	//glRotatef(th,0,1,0);

	if(fp){
		Cx = +2*dim*Sin(rot);
		Cz = -2*dim*Cos(rot);
		gluLookAt(Ex,Ey,Ez,Cx+Ex,Cy+Ey,Cz-Ez,0,1,0);
	}

	else{
		if(mode){
			// Perspective 
			double px = -2*dim*Sin(th)*Cos(ph);
	      	double py = +2*dim        *Sin(ph);
	      	double pz = +2*dim*Cos(th)*Cos(ph);
	      	gluLookAt(px,py,pz , 0,0,0 , 0,Cos(ph),0);
		}
		else{
			// Orthogonal
			glRotatef(ph,1,0,0);
	      	glRotatef(th,0,1,0);
		}
	}
	
// lighting code from ex13 --------------------------------------------------------
	// Flat or smooth shading
	glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);
	// Light switch
	if(light){
		//  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light position
         // figure out position of light (little ball)
      float Position[]  = {distance*Cos(zh)*1.1,ylight,distance*Sin(zh)*1.1,1.0*1.1};
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);

      sun(Position[0],Position[1],Position[2] , 0.1);
         // draw ball at where light is
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE); 
         // make normal vectors unit length
      //  Enable lighting
      glEnable(GL_LIGHTING);  // Enable lighting

      //  Location of viewer for specular calculations
      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
         // default is global viewer 
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
         // set ambient and diffuse components
         // if want to set specular component too, set separately
      glEnable(GL_COLOR_MATERIAL);
         // whenever call glColor, set material properties assoc w those vertices according to how I set the color
      //  Enable light 0
      glEnable(GL_LIGHT0);    // Switch on light (can have up to 8 lights)
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
            // tell openGL that this is where that light is
            // takes 4 parameters (don't forget w)
	}
	else{
		glDisable(GL_LIGHTING);
	}

// ----------------------------------------------------------------------------------

	//////////////////// DRAW SCENE ////////////////////////////
		//double s, double x, double y, double z
	//first(1, 0,0,0);

	table(1,0,0, 0.5,0.5,0.5);
	aloe(1, -1.5, 1.6, 0);
		//double s, double x, double y, double z, double dx, double dy, double dz, double th
	jade(1,0,0);
		//leafyPlant(double x, double y, double z, double sx, double sy, double sz)
	leafyPlant(3,0,-2, 1,1,1);

// -------------------------------------------------------------------------------


//  Draw axes in white; no lighting from here on 
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
   const double len=5;  //  Length of axes
	if (axes){
	      glBegin(GL_LINES);
	      glVertex3d(0.0,0.0,0.0);
	      glVertex3d(len,0.0,0.0);
	      glVertex3d(0.0,0.0,0.0);
	      glVertex3d(0.0,len,0.0);
	      glVertex3d(0.0,0.0,0.0);
	      glVertex3d(0.0,0.0,len);
	      glEnd();
	      //  Label axes
	      glRasterPos3d(len,0.0,0.0);
	      Print("X");
	      glRasterPos3d(0.0,len,0.0);
	      Print("Y");
	      glRasterPos3d(0.0,0.0,len);
	      Print("Z");
	}
   
	glWindowPos2i(5,5);
	if(fp){
		Print("Angle=%d, Projection=FP",rot);
		glWindowPos2i(5,30);
	}

	//Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s",th,ph,dim,fov,mode?"Perpective":"Orthogonal");	
	Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s Light=%s",
     th,ph,dim,fov,mode?"Perpective":"Orthogonal",light?"On":"Off");
/*
	if (light)
   {
      //glWindowPos2i(5,45);
      //Print("Model=%s LocalViewer=%s Distance=%d Elevation=%.1f",smooth?"Smooth":"Flat",local?"On":"Off",distance,ylight);
      //glWindowPos2i(5,25);
      //Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }
*/
	glFlush();
	glutSwapBuffers();
}

void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

// code from ex8
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Switch display mode
   else if (ch == 'm' || ch == 'M')
      mode = 1-mode;
   		//mode = (mode+1)%3;
   else if(ch=='f' || ch=='F'){
   	  fp = 1-fp;
   }
   else if(ch=='l' || ch=='L'){
      light = 1-light;
   }
   // Toggle light movement
   else if(ch=='v' || ch=='V'){
   		move = 1-move;
   }
   // Move light
   else if(ch=='<'){
   	zh += 1;
   }
   else if(ch=='>'){
   	zh -= 1;
   }
   // Light elevation
   else if(ch=='['){
   	ylight -= 0.1;
   }
   else if(ch==']'){
   	ylight += 0.1;
   }
   // Ambient level
   else if(ch=='b' && ambient>0){
   	ambient -= 5;
   }
   else if(ch=='B' && ambient<100){
   	ambient += 5;
   }
   // Diffuse level
   else if(ch=='n' && diffuse>0){
   	diffuse -= 5;
   }
   else if(ch=='N' && diffuse<100){
   	diffuse += 5;
   }
   // Specular level
   else if(ch=='p' && specular>0){
   	specular -= 5;
   }
   else if(ch=='P' && specular<100){
   	specular += 5;
   }
   // Emission level
   else if(ch=='e' && emission>0){
   	emission -= 5;
   }
   else if(ch=='E' && emission<100){
   	emission += 5;
   }
   // Shininess level
   else if(ch=='i' && shininess>-1){
   	shininess -= 1;
   }
   else if(ch=='I' && shininess<7){
   	shininess += 1;
   }
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      //fov--;
   		fov++;
   else if (ch == '+' && ch<179)
      //fov++;
   		fov--;
 // Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0, shininess);
  if(fp){
  	// fp code used from https://github.com/jheil/CSCI-4229-Fish-Tank/blob/master/julia_heil_finalproject/main.cpp
  	// written by Julia Heil
  	if(ch=='w' || ch=='W'){
  		Ex += Cx*0.05;
  		Ez += Cz*0.05;
  	}
	else if(ch=='a' || ch=='A'){
  		rot -= 3;
  	}  	
  	else if(ch=='s' || ch=='S'){
  		Ex -= Cx*0.05;
  		Ez -= Cz*0.05;
  	}
  	else if(ch=='d' || ch=='D'){
  		rot += 3;
  	}
  	rot%=360;
  }
  else{
  	if(ch=='0'){
  		th=0;
  		ph=0;
  	}
  	else if(ch=='-' && ch>1){
  		//fov--;
  		fov++;
  	}
  	else if(ch=='+' && ch<179){
  		//fov++;
  		fov--;
  	}
  }
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(mode?fov:0,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutIdleFunc(move?idle:NULL);
   glutPostRedisplay();

}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
	if(!fp){
	//  Right arrow key - increase azimuth by 5 degrees
	   if (key == GLUT_KEY_RIGHT){
	      th += 5;
	   }
	   //  Left arrow key - decrease azimuth by 5 degrees
	   else if (key == GLUT_KEY_LEFT){
	      th -= 5;
	   }
	   //  Up arrow key - increase elevation by 5 degrees
	   else if (key == GLUT_KEY_UP){
	      ph += 5;
	   }
	   //  Down arrow key - decrease elevation by 5 degrees
	   else if (key == GLUT_KEY_DOWN){
	      ph -= 5;
	   }
	   //  PageUp key - increase dim
	   else if (key == GLUT_KEY_PAGE_UP)
	      dim += 0.1;
	   //  PageDown key - decrease dim
	   else if (key == GLUT_KEY_PAGE_DOWN && dim>1)
	      dim -= 0.1;
	   else if (key == GLUT_KEY_F3)
	   	  distance = (distance==2) ? 4 : 2;
	   
	}
	else{
		double dt=0.05;
		if(key== GLUT_KEY_RIGHT){
			rot += 3;
		}
		else if(key == GLUT_KEY_LEFT){
			rot -=3;
		}
		else if(key == GLUT_KEY_UP){
			Ex += Cx*dt;
			Ez += Cz*dt;
		}
		else if(key == GLUT_KEY_DOWN){
			Ex -= Cx*dt;
			Ez -= Cz*dt;
		}
		else if(key == GLUT_KEY_PAGE_UP){
			Ey += dt;
		}
		else if(key == GLUT_KEY_PAGE_DOWN){
			Ey =- dt;
		}
	}
	//  Keep angles to +/-360 degrees
	   th %= 360;
	   ph %= 360;

   Project();
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

// This function is used from ex5.c
void reshape(int width,int height){
	// code used from ex9
	 //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project();
}

/*
 *  Main
 */
int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(700,700);
	glutCreateWindow("hw3 - Lauren Strand");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	//glEnable(GL_DEPTH_TEST);
	//  Load textures
   texture[0] = LoadTexBMP("wood.bmp");
   texture[1] = LoadTexBMP("ceramic.bmp");
   //texture[2] = LoadTexBMP("aloe2.bmp");
   texture[2] = LoadTexBMP("aloe4.bmp");
   texture[3] = LoadTexBMP("soil2.bmp");
   texture[4] = LoadTexBMP("oedema-jade.bmp");
   //texture[5] = LoadTexBMP("leafyStem.bmp");
   ErrCheck("init");
	glutMainLoop();
   return 0;
}