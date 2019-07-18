/*
 * final project
 * Lauren Strand
 */

#include "CSCIx229.h"

// Global variables -------------------------------------------------------

int th=0;	//Rotation (viewing) angle
int ph=20; 	//Elevation of view angle

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
int distance  =   10;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int emission  =   0;  // Emission intensity (%)
int ambient   =  65;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
//int zh        =  90;  // Light azimuth
float zh = 90.0;
int direcLight = 1;
float ylight  =   9;  // Elevation of light
float Exp=0;

// Texture
unsigned int texture[27]; // Texture names

// ------------------------------------------------------------------------

// variables used for fp --------------------------------------------------
double Cx = 0;
double Cy = 0;
double Cz = 0;
int fp=0;
int rot=0;
double Ex = 0;
double Ey = 0;
double Ez = 0;

// -------------------------------------------------------------------------

static void Project()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   if(fp){
		gluPerspective(fov,asp,dim/6,9.2*dim);
   }
   else{
	   	//  Perspective transformation
	      gluPerspective(fov,asp,dim/6,9.2*dim);

   }
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

static void pot(double x, double y, double z, double rL, double rS, double hPot){
	const int d=30;
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

static void pot2(double x, double y, double z, double rL, double rS, double hPot){
	const int d=8;
	int thi;
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glPushMatrix();
	glTranslated(x,y,z);
	//glScaled(1,hPot,1);

	//glBindTexture(GL_TEXTURE_2D,texture[16]);

	glBindTexture(GL_TEXTURE_2D,texture[23]);


	glBegin(GL_QUAD_STRIP);
	
	// draw sides of pot
	for(thi = 0; thi<=360; thi+=d){
		glNormal3f(Cos(thi), (rL-rS)/hPot, Sin(thi));
		//glColor3f(0.48, 0.25, 0.14);
		//glColor3f(1, 0.180, 0.180);
		glColor3f(1,1,1);
		//glColor3f(0.564, 0.443, 0.658);
		//glTexCoord2f(0.0,0.0);
		//glTexCoord2f(Cos(thi),Sin(thi));
		glTexCoord2f(Cos(thi),Sin(thi));
		glVertex3d(Cos(thi)*rL, 0, Sin(thi)*rL);
		//glVertex3d(Cos(th+d), -1, Sin(th+d));
		//glTexCoord2f(0.5,0.0);
		glTexCoord2f(Cos(thi+d),0);
		glVertex3d(Cos(thi+d)*rS, -hPot, Sin(thi+d)*rS);
	}
	glEnd();
	//glDisable(GL_TEXTURE_2D);

	// draw end (bottom) cap
	//glEnable(GL_TEXTURE_2D);
	//glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	//glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	//glBindTexture(GL_TEXTURE_2D,texture[16]);
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
	const int d=8;
	int thi;
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	//glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glPushMatrix();
	glTranslated(x,y,z);
	glRotated(ang, rx,ry,rz);
	glScaled(sx,sy,sz);
	//glBindTexture(GL_TEXTURE_2D, texture[2]); // aloe texture
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
	const int d=8;
	int thi;

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
		//glVertex3d(Cos(thi+d)*rS, 1, Sin(thi+d)*rS);
		glVertex3d(Cos(thi+d)*rS, h, Sin(thi+d)*rS);
	}
	glEnd();

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


	glPopMatrix();
}

static void shovel(double x, double y, double z, double rx, double ry, double rz, double ang, double sx, double sy, double sz, double rL, double rS, double h){
	// cylinder used when drawing jade stem
	const int d=9;
	int thi;
	//glEnable(GL_TEXTURE_2D);
	//glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	//glBindTexture(GL_TEXTURE_2D,texture[4]);

	glPushMatrix();
	glTranslated(x,y,z);
	glRotated(ang, rx,ry,rz);
	glScaled(sx,sy,sz);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	//glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glBindTexture(GL_TEXTURE_2D,texture[7]);
	glColor3f(1,1,1);
	float dx = 0;
	for(int i=0; i<1000; i++){
		glBegin(GL_QUAD_STRIP);
		// draw sides 
		for(thi = 20; thi<=160; thi+=d){
			glNormal3f(Cos(thi), (rL-rS)/h, Sin(thi));
			glTexCoord2f(Cos(thi),0.0);
			glVertex3d(Cos(thi)*rL+dx, 0, Sin(thi)*rL+dx);
			glTexCoord2f(Sin(thi),0.0);
			//glVertex3d(Cos(thi+d)*rS, 1, Sin(thi+d)*rS);
			glVertex3d(Cos(thi+d)*rS+dx, h, Sin(thi+d)*rS+dx);
		}
		glEnd();
		dx += 0.0001;
	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	//glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glBindTexture(GL_TEXTURE_2D,texture[8]);
	glColor3f(0.662, 0.529, 0.298);
	cylinder(x,y-(rL/2),z-h,rx,ry,rz,ang,sx,sy,sz,rL*0.2,rL*0.2,1.1*h);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
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
   const int d=45;
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
   //glBindTexture(GL_TEXTURE_2D,texture[4]);
   for (ph1=-90;ph1<90;ph1+=d)
   {
      glBegin(GL_QUAD_STRIP);
      for (th1=0;th1<=360;th1+=d)
      {
         glTexCoord2f(0,0); Vertex(th1,ph1);
         glTexCoord2f(1,0); Vertex(th1,ph1+d);
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
static void cube(double x,double y,double z,double dx,double dy,double dz,double th){
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
   //glBindTexture(GL_TEXTURE_2D,texture[0]);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  
    //  Cube
   glBegin(GL_QUADS);
   //  Front
   glVertex3f(-1,-1, 1);glNormal3f( 0, 0, 1);glTexCoord2f(0.0,0.0);
   glVertex3f(+1,-1, 1);glNormal3f( 0, 0, 1);glTexCoord2f(1.0,0.0); 
   glVertex3f(+1,+1, 1);glNormal3f( 0, 0, 1);glTexCoord2f(1.0,1.0);   
   glVertex3f(-1,+1, 1);glNormal3f( 0, 0, 1);glTexCoord2f(0.0,1.0);
   
   //  Back
   glVertex3f(+1,-1,-1);glNormal3f( 0, 0,-1); glTexCoord2f(0.0,0.0);
   glVertex3f(-1,-1,-1);glNormal3f( 0, 0,-1);glTexCoord2f(1.0,0.0);  
   glVertex3f(-1,+1,-1);glNormal3f( 0, 0,-1); glTexCoord2f(1.0,1.0);  
   glVertex3f(+1,+1,-1);glNormal3f( 0, 0,-1);glTexCoord2f(0.0,1.0);
   
   //  Right
   glVertex3f(+1,-1,+1);glNormal3f(+1, 0, 0);glTexCoord2f(0.0,0.0);
   glVertex3f(+1,-1,-1);glNormal3f(+1, 0, 0);glTexCoord2f(1.0,0.0);  
   glVertex3f(+1,+1,-1);glNormal3f(+1, 0, 0);glTexCoord2f(1.0,1.0);
   glVertex3f(+1,+1,+1);glNormal3f(+1, 0, 0);glTexCoord2f(0.0,1.0);
   
   //  Left
   glVertex3f(-1,-1,-1);glNormal3f(-1, 0, 0);glTexCoord2f(0.0,0.0);
   glVertex3f(-1,-1,+1);glNormal3f(-1, 0, 0);glTexCoord2f(1.0,0.0);   
   glVertex3f(-1,+1,+1);glNormal3f(-1, 0, 0);glTexCoord2f(1.0,1.0);   
   glVertex3f(-1,+1,-1);glNormal3f(-1, 0, 0);glTexCoord2f(0.0,1.0);
   
   //  Top
   glVertex3f(-1,+1,+1);glNormal3f( 0,+1, 0);glTexCoord2f(0.0,0.0);
   glVertex3f(+1,+1,+1);glNormal3f( 0,+1, 0);glTexCoord2f(1.0,0.0);
   glVertex3f(+1,+1,-1);glNormal3f( 0,+1, 0);glTexCoord2f(1.0,1.0);
   glVertex3f(-1,+1,-1);glNormal3f( 0,+1, 0);glTexCoord2f(0.0,1.0);
   
   //  Bottom
   glVertex3f(-1,-1,-1);glNormal3f( 0,-1, 0);glTexCoord2f(0.0,0.0);
   glVertex3f(+1,-1,-1);glNormal3f( 0,-1, 0);glTexCoord2f(1.0,0.0);
   glVertex3f(+1,-1,+1);glNormal3f( 0,-1, 0);glTexCoord2f(1.0,1.0);
   glVertex3f(-1,-1,+1);glNormal3f( 0,-1, 0);glTexCoord2f(0.0,1.0);
   
   //  End
   glEnd();
   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void planter(double x,double y,double z,double dx,double dy,double dz,double th){
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
   glBindTexture(GL_TEXTURE_2D,texture[24]);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
   glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glColor3f(0.694, 0.125, 0.231);
   //  Cube
   glBegin(GL_QUADS);
   
   //  Front
   glVertex3f(-1,-1, 1);glNormal3f( 0, 0, 1);glTexCoord2f(0.0,0.0);

   glVertex3f(+1,-1, 1);glNormal3f( 0, 0, 1);glTexCoord2f(1.0,0.0);
   
   glVertex3f(+1.5,+1, 1);glNormal3f( 0, 0, 1);glTexCoord2f(1.0,1.0);
   
   glVertex3f(-1.5,+1, 1);glNormal3f( 0, 0, 1);glTexCoord2f(0.0,1.0);
   
   //  Back  
   glVertex3f(+1,-1,-1);glNormal3f( 0, 0,-1);glTexCoord2f(0.0,0.0);
   //glTexCoord2f(0.0,0.0);

   glVertex3f(-1,-1,-1);glNormal3f( 0, 0,-1);glTexCoord2f(1.0,0.0);
   //glTexCoord2f(1.0,0.0);
   
   glVertex3f(-1.5,+1,-1);glNormal3f( 0, 0,-1);glTexCoord2f(1.0,1.0);
   //glTexCoord2f(1.0,1.0);
    
   glVertex3f(+1.5,+1,-1);glNormal3f( 0, 0,-1);glTexCoord2f(0.0,1.0);
   //glTexCoord2f(0.0,1.0);
   
   //  Right
   glVertex3f(+1,-1,+1);glNormal3f(2, -0.25, 0);glTexCoord2f(0.0,0.0);

   glVertex3f(+1,-1,-1);/*glNormal3f(+1, 0, 0);*/glTexCoord2f(1.0,0.0);
   
   glVertex3f(+1.5,+1,-1);/*glNormal3f(+1, 0, 0);*/glTexCoord2f(1.0,1.0);

   glVertex3f(+1.5,+1,+1);/*glNormal3f(+1, 0, 0);*/glTexCoord2f(0.0,1.0);
   
   //  Left
   glVertex3f(-1,-1,-1);glNormal3f(-2, -0.25, 0);glTexCoord2f(0.0,0.0);

   glVertex3f(-1,-1,+1);/*glNormal3f(-1, 0, 0);*/glTexCoord2f(1.0,0.0);
   
   glVertex3f(-1.5,+1,+1);/*glNormal3f(-1, 0, 0);*/glTexCoord2f(1.0,1.0);
   
   glVertex3f(-1.5,+1,-1);/*glNormal3f(-1, 0, 0);*/glTexCoord2f(0.0,1.0);
   
   //  Top
   /*glVertex3f(-1.5,+1,+1);glNormal3f( 0,+1, 0);glTexCoord2f(0.0,0.0);

   glVertex3f(+1.5,+1,+1);glNormal3f( 0,+1, 0);glTexCoord2f(1.0,0.0);

   glVertex3f(+1.5,+1,-1);glNormal3f( 0,+1, 0);glTexCoord2f(1.0,1.0);

   glVertex3f(-1.5,+1,-1);glNormal3f( 0,+1, 0);glTexCoord2f(0.0,1.0);*/
  
   //  Bottom
   glVertex3f(-1,-1,-1);glNormal3f( 0,-1, 0);glTexCoord2f(0.0,0.0);

   glVertex3f(+1,-1,-1);glNormal3f( 0,-1, 0);glTexCoord2f(1.0,0.0);

   glVertex3f(+1,-1,+1);glNormal3f( 0,-1, 0);glTexCoord2f(1.0,1.0);

   glVertex3f(-1,-1,+1);glNormal3f( 0,-1, 0);glTexCoord2f(0.0,1.0);
   //  End
   glEnd();
   glDisable(GL_TEXTURE_2D);

   glColor3f(1,1,1);
   glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glVertex3f(-1.5,+1,+1);glNormal3f( 0,+1, 0);glTexCoord2f(0.0,0.0);

   glVertex3f(+1.5,+1,+1);glNormal3f( 0,+1, 0);glTexCoord2f(1.0,0.0);

   glVertex3f(+1.5,+1,-1);glNormal3f( 0,+1, 0);glTexCoord2f(1.0,1.0);

   glVertex3f(-1.5,+1,-1);glNormal3f( 0,+1, 0);glTexCoord2f(0.0,1.0);
   glEnd();
   glDisable(GL_TEXTURE_2D);

   glPopMatrix();
   
 
}

static void table(double x, double y, double z, double sx, double sy, double sz){
	glPushMatrix();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glScaled(sx,sy,sz);
	glColor3f(1,1,1);
	cube(x,y,z, 3.4, 0.2, 1.3, 0);
	cube(x-2,y-1.2,z, 0.2, 1.2, 0.8, 0);
	cube(x+2,y-1.2,z, 0.2, 1.2, 0.8, 0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

static void aloe(double s, double x, double y, double z){
	glPushMatrix();
	glScaled(s,s,s);
	glTranslated(x,y,z);
	pot(0,0,0, 0.8, 0.6, 1.5);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[2]); // aloe texture

glColor3f(0.19, 0.35, 0.09); // dark green
	
	//         x, y, z,    rx, ry, rz, ang, sx, sy, sz, rL, rS, h
	aloeLeaf(-0.1,0,0.05, 0,0,1, 0, 0.08,1.7,0.1, 1,0, 2);
//glColor3f(0.298, 0.556, 0.145); // light
glColor3f(0.231, 0.431, 0.109);
	aloeLeaf(0,0,0.05, 0,0,-1, 10, 0.08,1.78,0.08, 1,0, 2);
glColor3f(0.231, 0.431, 0.109); // light
	aloeLeaf(0,0,-0.1, -0.8,0,0, 10, 0.1,1.69,0.06, 1,0, 2);

glColor3f(0.19, 0.35, 0.09); // dark green
	aloeLeaf(0.15,0,0, 0,0,-1, 20, 0.05,1.6,0.15, 1,0, 2);
glColor3f(0.231, 0.431, 0.109); // light
	aloeLeaf(-0.15,0,0, 0,0,1, 20, 0.05,1.4,0.15, 1,0, 2);
glColor3f(0.19, 0.35, 0.09); // dark green
	aloeLeaf(0,0,-0.2, -1,0,0, 15, 0.15,1.5,0.05, 1,0, 2);
glColor3f(0.231, 0.431, 0.109); // light
	aloeLeaf(0.07,0,0.18, 1,0,0, 15, 0.15,1.6,0.09, 1,0, 2);
glColor3f(0.19, 0.35, 0.09); // dark green
	aloeLeaf(-0.18,0,-0.15, -0.8,0,0.5, 22, 0.1,1.7,0.13, 1,0, 2);
	aloeLeaf(-0.21,-0.08,0.25, 1,-1,0.5, 24, 0.12,1.6,0.13, 1,0, 2);
	aloeLeaf(0.21,-0.08,0.19, 0,0,-0.8, 29, 0.1,1.6,0.13, 1,0, 2);

	aloeLeaf(0.21,-0.08,-0.19, -0.2,0,-1, 32, 0.15,1.4,0.12, 1,0, 2);
	aloeLeaf(-0.32,-0.08,0, 0,0,1, 32, 0.1,1.68,0.17, 1,0, 2);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

static void halfleafyLeaf(){
	// x y z defines initial coordinate
	double length = 0;
	int thi;
	const int d = 6;

	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glVertex3d(0,0,0);
	// bottom face
	
	for(thi = 0; thi<=180-d; thi+=d){		
		glNormal3f(0,-1,0);
		glTexCoord2f(0.5,0.5);
		glVertex3d(0,0,0);
		glTexCoord2f(0.5*Cos(thi)+0.5, 0.5*Sin(thi)+0.5);
		glVertex3d(length*Cos(thi), 0, length*Sin(thi));
		length += 0.07;	
		glTexCoord2f(0.5*Cos(thi+d)+0.5, 0.5*Sin(thi+d)+0.5);
		glVertex3d(length*Cos(thi+d), 0, length*Sin(thi+d));
	}
	glEnd();

	// sides
	glBegin(GL_QUAD_STRIP);
	length = 0;
	for(thi = 0; thi<=180; thi +=d){
		glNormal3f(length*Cos(thi), 0, length*Sin(thi));
		glTexCoord2f(0,0);
		glVertex3d(length*Cos(thi), 0, length*Sin(thi));
		glTexCoord2f(0.1,0);
		glVertex3d(length*Cos(thi), 0.1, length*Sin(thi));
		length += 0.07;
	}
	glEnd();
	
	// top face
	glBegin(GL_TRIANGLES);
	
	// bottom face
	length = 0;
	
	for(thi = 0; thi<=180-d; thi+=d){
		glNormal3f(0,1,0);
		glTexCoord2f(0.5,0.5);
		glVertex3d(0,0.1,0);
		glTexCoord2f(0.5*Cos(thi)+0.5, 0.5*Sin(thi)+0.5);
		glVertex3d(length*Cos(thi), 0.1, length*Sin(thi));
		length += 0.07;	
		glTexCoord2f(0.5*Cos(thi+d)+0.5, 0.5*Sin(thi+d)+0.5);
		glVertex3d(length*Cos(thi+d), 0.1, length*Sin(thi+d));
	}
	glEnd();
	
	glPopMatrix();
}

static void halfleafyLeaf2(){
	// x y z defines initial coordinate
	double length = 0;
	int thi;
	const int d = 6;

	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glEnable(GL_TEXTURE_2D);
	//glVertex3d(0,0,0);
	// bottom face
	//glBindTexture(GL_TEXTURE_2D, texture[26]);
	for(thi = 0; thi<=180-d; thi+=d){		
		glColor3f(1,1,1);
		glNormal3f(0,-1,0);
		glTexCoord2f(0.5,0.5);
		glVertex3d(0,0,0);
		//glTexCoord2f(0.5*Cos(thi)+0.5, 0.5*Sin(thi)+0.5);
		glTexCoord2f(0.6*Cos(thi)+0.6, 0.6*Sin(thi)+0.6);
		glVertex3d(length*Cos(thi), 0, length*Sin(thi));
		length += 0.07;	
		//glTexCoord2f(0.5*Cos(thi+d)+0.5, 0.5*Sin(thi+d)+0.5);
		glTexCoord2f(0.6*Cos(thi+d)+0.6, 0.6*Sin(thi+d)+0.6);
		glVertex3d(length*Cos(thi+d), 0, length*Sin(thi+d));
	}
	glEnd();
	//glDisable(GL_TEXTURE_2D);
	//glEnable(GL_TEXTURE_2D);
	// sides
	glBegin(GL_QUAD_STRIP);
	length = 0;
	//glBindTexture(GL_TEXTURE_2D, texture[27]);
	for(thi = 0; thi<=180; thi +=d){
		glColor3f(0.949, 0.968, 0.450);
		glNormal3f(length*Cos(thi), 0, length*Sin(thi));
		glTexCoord2f(0,0);
		glVertex3d(length*Cos(thi), 0, length*Sin(thi));
		glTexCoord2f(0.1,0);
		glVertex3d(length*Cos(thi), 0.1, length*Sin(thi));
		length += 0.07;
	}
	glEnd();
	//glDisable(GL_TEXTURE_2D);
	// top face
	//glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);
	
	// bottom face
	length = 0;
	
	//glBindTexture(GL_TEXTURE_2D, texture[26]);
	for(thi = 0; thi<=180-d; thi+=d){
		glColor3f(1,1,1);
		glNormal3f(0,1,0);
		glTexCoord2f(0.5,0.5);
		glVertex3d(0,0.1,0);
		//glTexCoord2f(0.5*Cos(thi)+0.5, 0.5*Sin(thi)+0.5);
		glTexCoord2f(0.6*Cos(thi)+0.6, 0.6*Sin(thi)+0.6);
		glVertex3d(length*Cos(thi), 0.1, length*Sin(thi));
		length += 0.07;	
		//glTexCoord2f(0.5*Cos(thi+d)+0.5, 0.5*Sin(thi+d)+0.5);
		glTexCoord2f(0.6*Cos(thi+d)+0.6, 0.6*Sin(thi+d)+0.6);
		glVertex3d(length*Cos(thi+d), 0.1, length*Sin(thi+d));
	}
	glEnd();
	//glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();
}

static void fullLeafyLeaf(double x, double y, double z, double rx, double ry, double rz, double ang, double sx, double sy, double sz){
	glPushMatrix();
	glTranslated(x,y,z);
	glRotated(ang,rx,ry,rz);
	glScaled(sx,sy,sz);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[6]);

	halfleafyLeaf();

	//glPushMatrix();
	
	glRotated(180,1,0,0);
	glScaled(1,-1,1);
	halfleafyLeaf();
	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

static void fullLeafyLeaf2(double x, double y, double z, double rx, double ry, double rz, double ang, double sx, double sy, double sz){
	glPushMatrix();
	glTranslated(x,y,z);
	glRotated(ang,rx,ry,rz);
	glScaled(sx,sy,sz);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[26]);

	halfleafyLeaf2();

	//glPushMatrix();
	
	glRotated(180,1,0,0);
	glScaled(1,-1,1);
	halfleafyLeaf();
	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

static void MILTongue(double x, double y, double z, double s){
	glPushMatrix();
	glTranslated(x,y,z);
	glScaled(s,s,s);

	//double x, double y, double z, double rL, double rS, double hPot
	pot(-0.1,0,-0.12, 1.05, 0.8, 2);	
	glColor3f(1,1,1);
	glPushMatrix(); glRotated(90,0,1,0); fullLeafyLeaf2(0,0,0,0,0,-1,90,1.4,0.5,0.2);glPopMatrix();
	glPushMatrix(); glRotated(80,0,1,0); fullLeafyLeaf2(-0.2,0,-0.2,0,0,-1,90,1.2,0.5,0.2);glPopMatrix();
	glPushMatrix(); glRotated(120,0,1,0); fullLeafyLeaf2(0.28,0,-0.5,0,0,-1,90,1.1,0.5,0.2);glPopMatrix();
	glPushMatrix(); glRotated(60,0,1,0); fullLeafyLeaf2(-0.05,0,0.3,0,0,-1,90,1.4,0.5,0.2);glPopMatrix();
	glPushMatrix(); glRotated(30,0,1,0); fullLeafyLeaf2(0.4,0,0.1,0,0,-1,90,1.3,0.5,0.2);glPopMatrix();
	glPushMatrix(); glRotated(130,0,1,0); fullLeafyLeaf2(0.28,0,-0.58,0,0,-1,90,1.5,0.5,0.2);glPopMatrix();
	glPushMatrix(); glRotated(100,0,1,0); fullLeafyLeaf2(0.25,0,0,0,0,-1,90,1.35,0.5,0.2);glPopMatrix();
	glPushMatrix(); glRotated(95,0,1,0); fullLeafyLeaf2(0.48,0,-0.1,0,0,-1,90,1.2,0.5,0.2);glPopMatrix();
	glPushMatrix(); glRotated(35,0,1,0); fullLeafyLeaf2(0.5,0,0.1,0,0,-1,90,1.3,0.5,0.2);glPopMatrix();
	glPushMatrix(); glRotated(148,0,1,0); fullLeafyLeaf2(0.65,0,-0.2,0,0,-1,90,1.4,0.5,0.2);glPopMatrix();
	glPushMatrix(); glRotated(134,0,1,0); fullLeafyLeaf2(0.73,0,0,0,0,-1,90,1.4,0.5,0.2);glPopMatrix();
	glPushMatrix(); glRotated(100,0,1,0); fullLeafyLeaf2(0.8,0,0,0,0,-1,90,1.4,0.5,0.2);glPopMatrix();
	glPushMatrix(); glRotated(93,0,1,0); fullLeafyLeaf2(0.6,0,0,0,0,-1,90,1.6,0.5,0.2);glPopMatrix();
	glPushMatrix(); glRotated(85,0,1,0); fullLeafyLeaf2(0.4,0,0,0,0,-1,90,1.5,0.5,0.2);glPopMatrix();
	glPushMatrix(); glRotated(55,0,1,0); fullLeafyLeaf2(0.7,0,0,0,0,-1,90,1.45,0.5,0.2);glPopMatrix();
	glPushMatrix(); glRotated(86,0,1,0); fullLeafyLeaf2(-0.4,0,0,0,0,-1,90,1.4,0.5,0.2);glPopMatrix();
	glPushMatrix(); glRotated(80,0,1,0); fullLeafyLeaf2(-0.5,0,-0.35,0,0,-1,90,1.2,0.5,0.2);glPopMatrix();

	glPopMatrix();
}

static void leafyStemLeaf(double x, double y, double z, double rx, double ry, double rz, double ang, double sx, double sy, double sz){
	glPushMatrix();
	glTranslated(x,y,z);
	glScaled(sx,sy,sz);
	glRotated(ang, rx, ry, rz);
	
	//glColor3f(0.160, 0.505, 0.074);
	glColor3f(0.431, 0.690, 0.368);
	//cylinder(x, y, z, rx, ry, rz, ang, sx*0.6, sy, sz*0.6, rL, rS, h);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,texture[5]);
	cylinder(0, 0, 0, 0, 0, 0, 0, 0.6, 1, 0.6, 0.1, 0.02, 1.3);
	glDisable(GL_TEXTURE_2D);

	glColor3f(0.250, 0.772, 0.125);
	//glColor3f(1,1,1);
	//fullLeafyLeaf(x, y+sy*h, z, rx, ry, rz, ang, sx*0.3, sy*0.3, sz*0.3);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	fullLeafyLeaf(0, 1.29, 0, 0, 0, 0, 0, 0.3, 0.1, 0.1);	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

static void leafyPlant(double x, double y, double z, double sx, double sy, double sz){
glPushMatrix();
	glTranslated(x,y,z);
	glScaled(sx,sy,sz);

	//double x, double y, double z, double rL, double rS, double hPot
	pot(1,1.5,-3, 0.8, 0.6, 1.5);	

	leafyStemLeaf(0.8,1,-3,0,0,1,20,1,1.1,1);

	glPushMatrix();
	glRotated(20,-0.5,0,0.5);
	leafyStemLeaf(1,1.2,-3,0,-1,0,70,1,1,1);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(20,-1,0,0);
	leafyStemLeaf(0.8,2.5,-2.8,0,-1,0,90,1,1.2,1);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(15,-0.5,0,-0.5);
	leafyStemLeaf(0.6,2.1,-3.1,0,-1,0,110,1,0.8,1);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(20, -1, 0, 0);
	leafyStemLeaf(0.7,2.2,-2.5,0,-1,0,80,1,0.85,0.8);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(20, -0.5, 0, -1);
	leafyStemLeaf(0.7,2.2,-3.2,0,-1,0,115,1.2,0.9,0.8);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(10, -1, 0, 0);
	leafyStemLeaf(0.9,2,-2.8,0,-1,0,90,1.2,0.95,0.8);
	glPopMatrix();

	glPushMatrix();
	glRotated(15, -0.7, 0, -0.5);
	leafyStemLeaf(0.8,2,-2.6,0,-1,0,98,1.2,0.98,0.8);
	glPopMatrix();

	glPushMatrix();
	glRotated(22, 0, 0, -0.5);
	leafyStemLeaf(0.9,1.5,-3.2,0,-1,0,125,1.2,1,0.8);
	glPopMatrix();

	glPushMatrix();
	glRotated(18, -0.2, 0, -1);
	leafyStemLeaf(0.7,1.5,-2.8,0,-1,0,120,1.2,1.2,0.8);
	glPopMatrix();

	glPushMatrix();
	glRotated(23, -0.2, 0, -1);
	leafyStemLeaf(0.82,1.5,-2.8,0,-1,0,145,1.2,1.2,0.8);
	glPopMatrix();

	glPushMatrix();
	glRotated(23, 0.2, 0, -0.5);
	leafyStemLeaf(1,1.5,-3,0,1,0,160,1.2,1,0.8);
	glPopMatrix();

	glPushMatrix();
	glRotated(19, -0.2, 0, -0.5);
	leafyStemLeaf(1,1.5,-2.8,0,1,0,150,1,1,0.8);
	glPopMatrix();

	glPushMatrix();
	glRotated(19, 0.7, 0, -0.2);
	leafyStemLeaf(1.3,0.5,-3,0,1,0,130,1,1,0.8);
	glPopMatrix();

	glPushMatrix();
	glRotated(19, 0.8, 0, -0.2);
	leafyStemLeaf(1.15,0.5,-3.1,0,1,0,115,1,1.1,0.8);
	glPopMatrix();

	glPushMatrix();
	glRotated(15, 0.8, 0, -0.2);
	leafyStemLeaf(1.,0.5,-3.1,0,1,0,118,1,0.95,0.8);
	glPopMatrix();

	glPushMatrix();
	glRotated(23, 1, 0, -0.2);
	leafyStemLeaf(1,0,-2.8,0,1,0,110,1.2,1.1,0.8);
	glPopMatrix();

	glPushMatrix();
	glRotated(25, 1, 0, 0);
	leafyStemLeaf(0.8,0,-2.8,0,1,0,90,0.9,1,0.8);
	glPopMatrix();

	glPushMatrix();
	glRotated(21, 1, 0, 0);
	leafyStemLeaf(0.9,0,-3,0,1,0,92,1.2,1,0.8);
	glPopMatrix();

	glPushMatrix();
	glRotated(25, 1, 0, 0.5);
	leafyStemLeaf(0.7,0,-3,0,1,0,70,1.2,1.15,0.8);
	glPopMatrix();

	glPushMatrix();
	glRotated(15, 1, 0, 0.2);
	leafyStemLeaf(0.8,0,-3.2,0,1,0,70,1.2,1.15,0.8);
	glPopMatrix();

	glPushMatrix();
	glRotated(21, 1, 0, 0.2);
	leafyStemLeaf(1,0,-3.2,0,1,0,70,1.2,1.2,0.8);
	glPopMatrix();

	glPushMatrix();
	glRotated(15, 0.8, 0, 0.5);
	leafyStemLeaf(0.7,0,-3.5,0,1,0,60,1.2,0.9,0.8);
	glPopMatrix();
glPopMatrix();
}

static void leafyPlant2Stick(double x, double y, double z){
glPushMatrix();
	glTranslated(x,y,z);
	//glScaled(sx,sy,sz);

	//glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	
	glColor3f(0.533, 0.588, 0.352);
	glBindTexture(GL_TEXTURE_2D, texture[10]);
	cylinder(0.25,0,0.25, 0,0,0, 0, 1,1,1, 0.05, 0.02, 1.6);
	glDisable(GL_TEXTURE_2D);

	//fullLeafyLeaf(x, y, z, rx, ry, rz, ang, sx, sy, sz);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,texture[9]);
	glPushMatrix();
	fullLeafyLeaf2(0.25,0.5,0.25, 0,0,-1,30, 0.1,0.05,0.05);
	glPopMatrix();

 glPushMatrix();
	glRotated(180,0,1,0);
	fullLeafyLeaf2(-0.3,0.6,-0.25, 0,0,-1,50, 0.15,0.05,0.05);
 glPopMatrix();
 glPushMatrix();
	glRotated(25,1,0,0);
	fullLeafyLeaf2(0.28,0.8,-0.14, 0,-1,0,95, 0.1,0.05,0.05);
 glPopMatrix();
 glPushMatrix();
	glRotated(30,-1,0,0);
	fullLeafyLeaf2(0.28,0.8,0.77, 0,1,0,95, 0.11,0.1,0.08);
 glPopMatrix();
 glPushMatrix();
	fullLeafyLeaf2(0.2,1.4,0.25, 0,0,-1,30, 0.19,0.1,0.1);
 glPopMatrix();
 glPushMatrix();
	fullLeafyLeaf2(0.27,1.43,0.25, 0,0,-1,100, 0.13,0.15,0.1);
 glPopMatrix();
 glPushMatrix();
	fullLeafyLeaf2(0.2,1,0.25, 0,0,-1,35, 0.11,0.1,0.1);
 glPopMatrix();
 glPushMatrix();
	glRotated(270,0,1,0);
	fullLeafyLeaf2(0.2,0.89,-0.2, 0,0,-1,20, 0.1,0.13,0.08); // x and z flipped
 glPopMatrix();
 glPushMatrix();
	glRotated(75,0,1,0);
	fullLeafyLeaf2(-0.22,0.8,0.32, 0,0,-1,20, 0.13,0.1,0.05); // x and z flipped
 glPopMatrix();
 glPushMatrix();
	glRotated(60,0,-1,0);
	fullLeafyLeaf2(0.3,0.65,-0.1, 0,0,-1,30, 0.1,0.09,0.08); // x and z flipped
 glPopMatrix();
	glDisable(GL_TEXTURE_2D);
glPopMatrix();
}

static void leafyPlant2(double x, double y, double z, double sx, double sy, double sz){
glPushMatrix();
	glTranslated(x,y,z);
	glScaled(sx,sy,sz);
	//glPopMatrix();
	pot(0,0,0, 0.9, 0.7, 1.8);	
	
	leafyPlant2Stick(0,0,0);
	glPushMatrix();
	glScaled(1,1.2,1);
	leafyPlant2Stick(-0.35,0,-0.2);
	glPopMatrix();
	glPushMatrix();
	glRotated(15,1,0,0);
	glRotated(5,0,1,0);
	leafyPlant2Stick(-0.5,0,0.2);
	glPopMatrix();
	glPushMatrix();
	glRotated(15,0,0,1);
	glRotated(15,0,1,0);
	leafyPlant2Stick(-0.5,0,-0.5);
	glPopMatrix();
	glPushMatrix();
	glRotated(15,-1,0,0);
	glRotated(35,0,1,0);
	leafyPlant2Stick(-0.1,0,-0.5);
	glPopMatrix();
	glPushMatrix();
	glRotated(15,0,0,-1);
	glRotated(35,0,1,0);
	leafyPlant2Stick(0.05,0,0.2);
	glPopMatrix();
glPopMatrix();
}

static void succulentLeaf(double y, double ang, double ang2, double s, double num){
glPushMatrix();
	glRotated(ang,0,1,0); glRotated(ang2,0,0,1);
	glScaled(0.3,0.3,0.3);
	glScaled(s,s,s);
	glRotated(15,0,0,1);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[18]);
	glColor3f(0.450, 0.549, 0.388);
	sphere(1,y,0,1,0.15,0.15);
	glDisable(GL_TEXTURE_2D);
glPopMatrix();
}

static void succulentLeaf2(double y, double ang, double ang2, double s, double num){
glPushMatrix();
	glRotated(ang,0,1,0); glRotated(ang2,0,0,1);
	glScaled(0.3,0.3,0.3);
	glScaled(s,s,s);
	glRotated(15,0,0,1);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[18]);
	//glColor3f(0.560, 0.737, 0.603);
	glColor3f(0.596, 0.631, 0.784);
	sphere(1,y,0,1,0.08,0.15);
	glDisable(GL_TEXTURE_2D);
glPopMatrix();
}

static void succulentLeaf3(double y, double ang, double ang2, double s, double num){
glPushMatrix();
	glRotated(ang,0,1,0); glRotated(ang2,0,0,1);
	glScaled(0.3,0.3,0.3);
	glScaled(s,s,s);
	glRotated(15,0,0,1);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[18]);
	glColor3f(0.823, 0.717, 0.803);
	//cylinder(x, y, z, rx, ry, rz, ang, sx, sy, sz, rL, rS, h)
	//cylinder(0,0,0,0,0,0,20,0.2,1.2,1,0.2,0.1,1);
	//sphere(double x,double y,double z,double sx, double sy, double sz)
	sphere(1,y,0,0.5,0.08,0.3);
	glDisable(GL_TEXTURE_2D);
glPopMatrix();
}

static void succulentLeafRow(double x, double y, double z, double ang2, double s, double num){
	glPushMatrix();
	glTranslated(x,y,z); glScaled(s,s,s);
	double rot = 0;
	//double num = 18;
	for(int i=0; i<=360; i++){
		if(rot>360){
			rot = 0;
			break;
		}
		succulentLeaf(0,rot,ang2,1,num);
		rot += 360/num;
		//num -= 1;
	}
	//succulentLeaf(0,0,30,1,1);


	glPopMatrix();
}

static void succulentLeafRow2(double x, double y, double z, double ang2, double s, double num){
	glPushMatrix();
	glTranslated(x,y,z); glScaled(s,s,s);
	double rot = 0;
	//double num = 18;
	for(int i=0; i<=360; i++){
		if(rot>360){
			rot = 0;
			break;
		}
		succulentLeaf2(0,rot,ang2,1,num);
		rot += 360/num;
		//num -= 1;
	}
	//succulentLeaf(0,0,30,1,1);


	glPopMatrix();
}

static void succulentLeafRow3(double x, double y, double z, double ang2, double s, double num){
	glPushMatrix();
	glTranslated(x,y,z); glScaled(s,s,s);
	double rot = 0;
	//double num = 18;
	for(int i=0; i<=360; i++){
		if(rot>360){
			rot = 0;
			break;
		}
		succulentLeaf3(0,rot,ang2,1,num);
		rot += 360/num;
		//num -= 1;
	}
	//succulentLeaf(0,0,30,1,1);


	glPopMatrix();
}

static void succulent(double x, double y, double z,double s){
	glPushMatrix();
	glTranslated(x,y,z);
	glScaled(s,s,s);

	pot(0,0,0, 0.35, 0.25, 0.55);

		//glPushMatrix(); glRotated(10,1,0,0); glRotated(35,0,1,0); succulentLeafRow(0,0.05,0,0.9,6); glPopMatrix();
		succulentLeafRow(0,-0.05,0,10,1,18);
		glPushMatrix(); glRotated(20,0,1,0); succulentLeafRow(0,0,0,15,1,14); glPopMatrix();
		glPushMatrix(); glRotated(30,0,1,0); succulentLeafRow(0,0,0,30,0.7,10); glPopMatrix();
		glPushMatrix(); glRotated(40,0,1,0); succulentLeafRow(0,0,0,45,0.5,6); glPopMatrix();
		glPushMatrix(); glRotated(50,0,1,0); succulentLeafRow(0,0,0,55,0.5,3); glPopMatrix();

	glPopMatrix();
}

static void succulent2(double x, double y, double z,double s){
	glPushMatrix();
	glTranslated(x,y,z);
	glScaled(s,s,s);

	//pot(0,0,0, 0.35, 0.25, 0.55);
		//glPushMatrix(); glRotated(10,1,0,0); glRotated(35,0,1,0); succulentLeafRow(0,0.05,0,0.9,6); glPopMatrix();
		succulentLeafRow2(0,-0.05,0,10,1,18);
		glPushMatrix(); glRotated(20,0,1,0); succulentLeafRow2(0,0,0,15,1,14); glPopMatrix();
		glPushMatrix(); glRotated(30,0,1,0); succulentLeafRow2(0,0,0,30,0.7,10); glPopMatrix();
		glPushMatrix(); glRotated(40,0,1,0); succulentLeafRow2(0,0,0,45,0.5,6); glPopMatrix();
		glPushMatrix(); glRotated(50,0,1,0); succulentLeafRow2(0,0,0,55,0.5,3); glPopMatrix();

	glPopMatrix();
}

static void succulent3(double x, double y, double z,double s){
	glPushMatrix();
	glTranslated(x,y,z);
	glScaled(s,s,s);

	//pot(0,0,0, 0.35, 0.25, 0.55);

		//glPushMatrix(); glRotated(10,1,0,0); glRotated(35,0,1,0); succulentLeafRow(0,0.05,0,0.9,6); glPopMatrix();
		succulentLeafRow3(-0.1,0,0.2,20,1,10);
		glPushMatrix(); glRotated(18,0,1,0); succulentLeafRow3(-0.1,0,0.2,15,1,8); glPopMatrix();
		glPushMatrix(); glRotated(22,0,1,0); succulentLeafRow3(-0.18,0.02,0.18,30,0.8,7); glPopMatrix();
		glPushMatrix(); glRotated(30,0,1,0); succulentLeafRow3(-0.19,-0.1,0.12,58,0.75,4); glPopMatrix();
		glPushMatrix(); glRotated(15,0,1,0); glScaled(1,1.2,1); succulentLeafRow3(-0.16,-0.1,0.12,70,0.75,1); glPopMatrix();

	glPopMatrix();
}

static void tableWPlants(double x, double y, double z, double rx, double ry, double rz, double ang, double sx, double sy, double sz){
	glPushMatrix();
	glTranslated(x,y,z);
	glRotated(ang,rx,ry,rz);
	glScaled(sx,sy,sz);
	//table(double x, double y, double z, double sx, double sy, double sz)
	table(0,0,0,1,1,1);

	//aloe(double s, double x, double y, double z)
	//double xAl = 5.5;
	double xAl = 4.8;
	for(int i=0; i<5; i++){
		aloe(0.5,xAl,1.7,1.8);
		xAl -= 2.2;
	}
	
	xAl = 5.6;
	for(int i=0; i<5; i++){
		aloe(0.5,xAl,1.7,-1);
		xAl -= 2.6;
	}
	glPopMatrix();
}

static void tableWPlants2(double x, double y, double z, double rx, double ry, double rz, double ang, double sx, double sy, double sz){
	glPushMatrix();
	glTranslated(x,y,z);
	glRotated(ang,rx,ry,rz);
	glScaled(sx,sy,sz);
	//table(double x, double y, double z, double sx, double sy, double sz)
	table(0,0,0,1,1,1);

	//leafyPlant(double x, double y, double z, double sx, double sy, double sz)
	double xAl = 1.6;
	//double zAl = 0;
	for(int i=0; i<5; i++){
		leafyPlant(xAl,0.2,0.3, 0.4,0.4,0.4);
		xAl -= 1.2;
	}
	
	xAl = 1;
	for(int i=0; i<3; i++){
		leafyPlant(xAl,0.2,2.8, 0.7,0.7,0.7);
		xAl -= 2;
	}
	glPopMatrix();
}


static void tableWPlants3(double x, double y, double z, double rx, double ry, double rz, double ang, double sx, double sy, double sz){
glPushMatrix();
	glTranslated(x,y,z);
	glRotated(ang,rx,ry,rz);
	glScaled(sx,sy,sz);
	//table(double x, double y, double z, double sx, double sy, double sz)
	table(0,0,0,1,1,1);

	//leafyPlant2(double x, double y, double z, double sx, double sy, double sz)
	double xAl = 2.5;
	for(int i=0; i<4; i++){
		leafyPlant2(xAl,0.8,-0.8, 0.3,0.3,0.3);
		xAl -= 1.4;
	}/*
	xAl = 2.6;
	for(int i=0; i<6; i++){
		leafyPlant2(xAl,0.8,-0.1, 0.35,0.35,0.35);
		xAl -= 1;
	}*/
	xAl = 2.4;
	for(int i=0; i<3; i++){
		leafyPlant2(xAl,0.8,0.74, 0.4,0.4,0.4);
		xAl -= 2.2;
	}

glPopMatrix();
}

static void tableWPlants4(double x, double y, double z, double rx, double ry, double rz, double ang, double sx, double sy, double sz){
glPushMatrix();
	glTranslated(x,y,z);
	glRotated(ang,rx,ry,rz);
	glScaled(sx,sy,sz);
	//table(double x, double y, double z, double sx, double sy, double sz)
	table(0,0,0,1,1,1);

	double xAl = 2.4;
	for(int i=0; i<4; i++){
		//succulent(double x, double y, double z,double s)
		//succulent(xAl,0.8,0.7,0.5); // x and z flipped
		succulent(xAl,0.4,0.75,0.5);
		xAl -= 1.2;
	}
	
	xAl = 2;
	for(int i=0; i<3; i++){
		//succulent(xAl,0.8,0.1,0.53);
		succulent(xAl,0.4,0,0.53);
		xAl -= 2;
	}
	
	xAl = 2.65;
	for(int i=0; i<4; i++){
		//succulent(xAl,0.8,-0.6,0.58);
		succulent(xAl,0.4,-0.75,0.58);
		xAl -= 1.5;
	}

glPopMatrix();
}

static void plantShelf(double x, double y, double z, double ang, double sx, double sy, double sz, double num){
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[11]);
   	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	glTranslated(x,y,z);
	glRotated(ang,0,1,0);
	glScaled(sx,sy,sz);

	//glColor3f(0.360, 0.368, 0.376);
	glColor3f(0.725, 0.721, 0.713);
	double yTop = 0;
	double yLeg = -1;
	for(int i=0; i<num; i++){
		cube(0,yTop,0,1,0.1,1,0);

		cube(-0.9,yLeg,0.9,0.1,1,0.05,0);
		cube(0.9,yLeg,0.9,0.1,1,0.05,0);
		cube(-0.9,yLeg,-0.9,0.1,1,0.05,0);
		cube(0.9,yLeg,-0.9,0.1,1,0.05,0);

		yTop += 2;
		yLeg += 2;
	}
	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
}

static void shelfWPots(double x, double y, double z, double ang, double sx, double sy, double sz){
	glPushMatrix();
	glTranslated(x,y,z);
	glRotated(ang,0,1,0);
	glScaled(sx,sy,sz);
	plantShelf(0,0,0,0,1,1,1,4);
	////pot2(double x, double y, double z, double rL, double rS, double hPot)
	glPopMatrix();
	glPushMatrix();
	glTranslated(x,y,z);
	glRotated(ang,0,1,0);
	double xPot = -0.75;

	for(int i=0; i<=1; i++){
		pot2(xPot,1,0,0.2,0.13,0.8);
		for(int j=0; j<1; j++){
			pot2(xPot,1,0.5,0.2,0.13,0.8);
		}
		xPot += 1.5;
	}
	xPot = -1;
	for(int i=0; i<=2; i++){
		pot2(xPot+0.3,4.7,0,0.22,0.16,0.6);
		for(int j=0; j<1; j++){
			pot2(xPot,4.7,0.5,0.2,0.13,0.8);
		}
		xPot += 1;
	}

	glPopMatrix();
}

static void ground(double x, double y, double z, double s, double D){
glPushMatrix();

   glTranslated(x,y,z);
   //glRotated(90, 1,0,0);
   glScaled(s,s,s);
   // Enable textures
   glEnable(GL_TEXTURE_2D); 
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D, texture[12]);
   glColor3f(0.733, 0.737, 0.749);
   double mul = 2.0/D;
   
   glBegin(GL_QUADS);
   for(int i=0; i<D; i++){
   		for(int j=0; j<D; j++){
   			glNormal3f(0,0,1);
   		glTexCoord2d(5*mul*(i+0),5*mul*(j+0)); glVertex3d(20*mul*(i+0)-20,0,20*mul*(j+0)-20);
        glTexCoord2d(5*mul*(i+1),5*mul*(j+0)); glVertex3d(20*mul*(i+1)-20,0,20*mul*(j+0)-20);
        glTexCoord2d(5*mul*(i+1),5*mul*(j+1)); glVertex3d(20*mul*(i+1)-20,0,20*mul*(j+1)-20);
        glTexCoord2d(5*mul*(i+0),5*mul*(j+1)); glVertex3d(20*mul*(i+0)-20,0,20*mul*(j+1)-20);
   		}
   }

   glEnd();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void ceilingFun(double x, double y, double z, double ang, double D){
	// ceiling function
glPushMatrix();
	glTranslated(x,y,z);
	
	glRotated(ang,0,0,1);
	//glRotated(90,1,0,0);
	glEnable(GL_TEXTURE_2D);
	double mul = 2.0/D;
	glNormal3f(0,-1,0);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[15]);
	glBegin(GL_QUADS);

	 for(int i=0; i<D; i++){
   		for(int j=0; j<D; j++){
		glTexCoord2d(7*mul*(i+0),9*mul*(j+0)); glVertex3d(25*mul*(i+0)-25,0,25*mul*(j+0)-25);
        glTexCoord2d(7*mul*(i+1),9*mul*(j+0)); glVertex3d(25*mul*(i+1)-25,0,25*mul*(j+0)-25);
        glTexCoord2d(7*mul*(i+1),9*mul*(j+1)); glVertex3d(25*mul*(i+1)-25,0,25*mul*(j+1)-25);
        glTexCoord2d(7*mul*(i+0),9*mul*(j+1)); glVertex3d(25*mul*(i+0)-25,0,25*mul*(j+1)-25);
   		}
   }
   glEnd();	
	glDisable(GL_TEXTURE_2D);
glPopMatrix();
}

static void ceilingFront(double x, double y, double z, double D){
	glPushMatrix();
	glTranslated(x,y,z);

	double mul = 2.0/D;
	//glNormal3f(0,0,-1);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBegin(GL_QUADS);

	 for(int i=0; i<D; i++){
   		for(int j=0; j<D; j++){
	 	 glTexCoord2d(5*mul*(i+0),3*mul*(j+0)); glVertex2d(22*mul*(i+0)-22,10*mul*(j+0)-10);
         glTexCoord2d(5*mul*(i+1),3*mul*(j+0)); glVertex2d(22*mul*(i+1)-22,10*mul*(j+0)-10);
         glTexCoord2d(5*mul*(i+1),3*mul*(j+1)); glVertex2d(22*mul*(i+1)-22,10*mul*(j+1)-10);
         glTexCoord2d(5*mul*(i+0),3*mul*(j+1)); glVertex2d(22*mul*(i+0)-22,10*mul*(j+1)-10);
   		}
   }
   glEnd();	

glPopMatrix();
}

static void ceilingAll(){

	ceilingFun(-15, 20, -10, 25,50); // slanted 100
	ceilingFun(15, 20, -10, -25,50); // slanted

	
	//ceilingFront(18,10,-25,100);
	double xStart = -1;
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[15]);
	//for(int i=0; i<4; i++){
		glNormal3f(0,0,1);
		ceilingFront(xStart,27,-25,50); 
		//ceilingFront(-xStart,10,-25,100);
		glNormal3f(0,0,-1);
		ceilingFront(xStart,27,10,50);
		//ceilingFront(-xStart,10,10,100);
		//xStart += 8;
	//}
	glDisable(GL_TEXTURE_2D);
}
	
static void truss(double x, double y, double z, double sx, double sy, double sz){
glPushMatrix(); glTranslated(x,y,z); glScaled(sx,sy,sz);
	glEnable(GL_TEXTURE_2D); glColor3f(0.529, 0.529, 0.529);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[21]);
//cube(double x,double y,double z,double dx,double dy,double dz,double th)
	cube(0,0,0,4.5,0.1,0.1,0);

	glPushMatrix(); glRotated(32,0,0,1);
		cube(-1.2,2.3,0,2.7,0.1,0.1,0);
	glPopMatrix();
	glPushMatrix(); glRotated(32,0,0,-1);
		cube(1.2,2.3,0,2.7,0.1,0.1,0);
	glPopMatrix();

glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

static void wall(double x, double y, double z, double D){
	glPushMatrix();
	glTranslated(x,y,z);
	double mul = 2.0/D;
	glBegin(GL_QUADS);

	 for(int i=0; i<D; i++){
   		for(int j=0; j<D; j++){
	 	 glTexCoord2d(4*mul*(i+0),3*mul*(j+0)); glVertex2d(25*mul*(i+0)-25,17*mul*(j+0)-17);
         glTexCoord2d(4*mul*(i+1),3*mul*(j+0)); glVertex2d(25*mul*(i+1)-25,17*mul*(j+0)-17);
         glTexCoord2d(4*mul*(i+1),3*mul*(j+1)); glVertex2d(25*mul*(i+1)-25,17*mul*(j+1)-17);
         glTexCoord2d(4*mul*(i+0),3*mul*(j+1)); glVertex2d(25*mul*(i+0)-25,17*mul*(j+1)-17);
   		}
   }
   glEnd();	
glPopMatrix();
}

static void wallAll(){
	double xStart = 0;
	double xStartL = 10;
	double D = 50; // 100
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, texture[17]);
		glNormal3f(0,0,1);
		wall(xStart,0,-25,D); // front wall

		glNormal3f(0,0,-1);
		wall(xStart,0,10,D); // back wall

		glPushMatrix();
		glRotated(90,0,1,0);
		glNormal3f(1,0,0);
		wall(xStartL,0,-20,D); // left
		glPopMatrix();

		glPushMatrix();
		glRotated(90,0,1,0);
		glNormal3f(-1,0,0);
		wall(xStartL, 0,20,D); // right
		glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

static void pottingBin(double x, double y, double z, double ang, double sx, double sy, double sz){
	glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(ang,0,1,0);
   glScaled(sx,sy,sz);

   // Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  
   //  Cube
   // x y z sx sy sz ang
   glBindTexture(GL_TEXTURE_2D, texture[13]);
   glColor3f(0.615, 0.737, 0.847);
   //glColor3f(0.611, 0.588, 0.596);
   cube(0,0,0,1,1,1,0);
   glDisable(GL_TEXTURE_2D);

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   //sphere(double x,double y,double z,double sx, double sy, double sz)
   glBindTexture(GL_TEXTURE_2D, texture[14]);
   glColor3f(1,1,1);
   sphere(0,0.85,0,1,0.35,1);
   glDisable(GL_TEXTURE_2D);

   //  Undo transformations
   glPopMatrix();
   
}

static void hawthoriaLeaf(double y, double ang, double ang2, double s, double rL, double rS, double h, double num){
	const int d=8;
	int thi;
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glPushMatrix();
	//glTranslated(x,y,z);
	glRotated(ang, 0,1,0); glRotated(ang2,-1,0,0); glScaled(1,1,0.5);
	glScaled(s,s,s);
	//glBindTexture(GL_TEXTURE_2D, texture[2]); // aloe texture
	glBegin(GL_QUAD_STRIP);
	// draw sides 
	for(thi = 0; thi<=360; thi+=d){
		//glColor3f(0.48, 0.25, 0.14);
		glNormal3f(Cos(thi), (rL-rS)/h, Sin(thi));
		//glTexCoord2f(2.0*Cos(thi),2*Sin(thi));
		glTexCoord2f(3*Cos(thi),3*Sin(thi));
		glVertex3d(Cos(thi)*rL, 0, Sin(thi)*rL);
		
		//glTexCoord2f(0.01*Cos(thi+d),0.01*Sin(thi+d));
		glTexCoord2f(0.05*Cos(thi+d),0.05*Sin(thi+d));

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

static void hawthoriaGen(double x, double y, double z, double ang, double s, double num){
	glPushMatrix(); glTranslated(x,y,z); glScaled(s,s,s);
	double rot = 0;
	for(int i=0; i<=360; i++){
		if(rot>360){
			rot = 0;
			break;
		}
		//hawthoriaLeaf(y, ang, ang2, s, rL, rS, h, num)
		hawthoriaLeaf(0,rot,ang,1,0.1,0.01,0.2,8);
		rot += 360/num;
		//num -= 1;
	}
	glPopMatrix();
}

static void hawthoria(double x, double y, double z, double s){
	//aloeLeaf(x,y,z,rx,ry,rz,ang,sx,sy,sz,rL,rS,h)
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glPushMatrix();
	glTranslated(x,y,z);
	//glRotated(ang, rx,ry,rz);
	glScaled(s,s,s);
	////table(double x, double y, double z, double sx, double sy, double sz)
	table(0,-0.5,0,1,1,1);

	//planter(double x,double y,double z,double dx,double dy,double dz,double th)
	
	planter(0,0,0,0.5,0.6,1,90);
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D, texture[20]); 
	glPushMatrix(); hawthoriaGen(0,0.6,0,40,0.8,8); glPopMatrix();
	glPushMatrix(); glRotated(20,0,1,0); hawthoriaGen(0,0.6,0,30,0.65,6); glPopMatrix();
	glPushMatrix(); glRotated(25,0,1,0); hawthoriaGen(0,0.5,0,15,0.4,3); glPopMatrix();
	//hawthoriaLeaf(x, y, z, rx, ry, rz, ang, sx, sy, sz, rL, rS, h)

	//succulent(double x, double y, double z,double s)
	

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

static void tableWPlants5(double x, double y, double z, double ang, double s){
glPushMatrix();
glTranslated(x,y,z); glRotated(ang,0,1,0); glScaled(s,s,s);
	hawthoria(0,0,0,1);

	// succulent2(double x, double y, double z,double s)
	succulent2(0.5,0.6,0.2,0.5);

	//succulent3(double x, double y, double z,double s)
	succulent3(-0.5,0.5,0.2,1);

glPopMatrix();
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
			// Perspective 
			double px = -2*dim*Sin(th)*Cos(ph);
	      	double py = +2*dim        *Sin(ph);
	      	double pz = +2*dim*Cos(th)*Cos(ph);
	      	gluLookAt(px,py,pz , 0,0,0 , 0,Cos(ph),0);
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
      float Position[]  = {distance*Cos(zh)*1.10,ylight,distance*Sin(zh)*1.1-4,1.0*1.1};
      //float Position[]  = {distance*1.1*Cos(zh+90)*1.10,ylight*Sin(zh+90),distance*1.1*Sin(zh+90)*1.1,1.0*1.1};
      float Direction[] = {Cos(th)*Sin(ph),Sin(th)*Sin(ph),-Cos(ph),0};
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
      //glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
      glMaterialf(GL_FRONT,GL_SHININESS,shiny);
      //  Enable light 0
      glEnable(GL_LIGHT0);    // Switch on light (can have up to 8 lights)
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
            // tell openGL that this is where that light is
            // takes 4 parameters (don't forget w)
      glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,Direction);
      //glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,sco);
      glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,Exp);
	}
	else{
		glDisable(GL_LIGHTING);
	}

// ----------------------------------------------------------------------------------

/////////////////////// DRAW SCENE ////////////////////////////////////////////////////

		
	tableWPlants2(-4,-1,-1,0,1,0,82,1,1,1); //leafy
	tableWPlants(-3,-1,-11,0,1,0,82,1,1,1);

	tableWPlants(5,-1,-2,0,-1,0,85,1,1,1); //aloe

	tableWPlants3(4,-1,-11,0,-1,0,85,1,1,1); //leafy2

	shelfWPots(-7,-2,-5,90,2.1,1,1);
	shelfWPots(18,-2,6,90,2.1,1,1);
	shelfWPots(0.5,-2,-20,180,2.1,1,1);

	glPushMatrix();
	glRotated(12,1,0,0);
	glRotated(10,0,1,0);
		// shovel(x, y, z, rx, ry, rz, ang, sx, sy, sz, rL, rS, h)
	shovel(1.4, -2.7, -9.5, 1, 0, 0, 90, 0.5, 1, 0.5, 0.5, 0.05, 1);
	glPopMatrix();

	ground(0,-4,-25,2,10);

	ceilingAll(); // front and back triangular

	wallAll();

	// pottingBin(double x, double y, double z, double ang, double sx, double sy, double sz)
	pottingBin(0,-2,-10,100,1,1,1);


	//succulent(0,0,0,1);
	tableWPlants4(-8.5,-1,1,0,1,0,100,1,1,1);
		//tableWPlants4(8,-1,-11,0,1,0,90,1,1,1);
	tableWPlants4(8,-1,-11,0,1,0,90,1,1,1);

	tableWPlants2(-9,-1,-11,0,1,0,90,1,1,1);

	//chineseEvergreen(0,1,0);

	double zStart = 3;
	for(int i=0; i<5; i++){
		truss(0,12,zStart,2.5,1.5,1);
		zStart-=3;
	}
	
	//hawthoria(double x, double y, double z, double rx, double ry, double rz, double ang, double sx, double sy, double sz)
	// x, y, z, s
	
	//tableWPlants5(double x, double y, double z, double ang, double s)
	tableWPlants5(15,-1,-5,90,1);
	tableWPlants5(0,-1,8,0,1);

	//MILTongue(double x, double y, double z, double s)
	MILTongue(18,-2,-21,1);
	MILTongue(-16,-2,8,0.8);

/////////////////////////////////////////////////////////////////////////////////////////


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
		glWindowPos2i(5,10);
	}
	else{
		glWindowPos2i(5,5);
		Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s Light=%s",
     	th,ph,dim,fov,"Perpective",light?"On":"Off");
	}
	
	//Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s",th,ph,dim,fov,mode?"Perpective":"Orthogonal");	
	
	glFlush();
	glutSwapBuffers();
}

void idle()
{
   //  Elapsed time in seconds
   //double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   double t = glutGet(GLUT_ELAPSED_TIME)/4000.0;
   zh = fmod(90*t,360.0);
   /*
   if(abs(zh) >= 90.0){
   	direcLight *= -1;
   	
   }
   zh += direcLight*9;
	*/
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
   	else if (ch == '1'){
   		th = 0;
   		ph = 5;
   		fov = 67;
   	}
   	else if (ch == '2'){
   		th = 105; ph = 15;
   		fov = 29;
   	}
   	else if (ch == '3'){
   		th = 30; ph = 20;
   		fov = 113;
   	}
   	else if (ch == '4'){
   		th = 280; ph = 5;
   		fov = 33;
   	}
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
   Project(asp,dim);
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
	      // if th == someAng
	      	// th = th
	      // else
	      	// th += 5
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
	   		if(ph<=-5){
	   			ph = -5;
	   		}
	   		else{
	   			ph -= 5;		
	   		}
	      
	   }
	   //  PageUp key - increase dim
	   else if (key == GLUT_KEY_PAGE_UP)
	      dim += 0.1;
	   //  PageDown key - decrease dim
	   else if (key == GLUT_KEY_PAGE_DOWN && dim>1)
	      dim -= 0.1;
	   else if (key == GLUT_KEY_F3)
	   	  distance = (distance==9) ? 10 : 9;
	   
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
	glutInitWindowSize(1000,900);
	glutCreateWindow("final project - Lauren Strand");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	// glEnable(GL_DEPTH_TEST);
	//  Load textures
   texture[0] = LoadTexBMP("wood.bmp");
   texture[1] = LoadTexBMP("ceramic.bmp");
   //texture[2] = LoadTexBMP("aloe2.bmp");
   texture[2] = LoadTexBMP("aloe4.bmp");
   texture[3] = LoadTexBMP("soil2.bmp");
   texture[4] = LoadTexBMP("oedema-jade.bmp");
   texture[5] = LoadTexBMP("leafyStem.bmp");
   texture[6] = LoadTexBMP("frontLeafyLeaf.bmp");
   texture[7] = LoadTexBMP("metalShovel.bmp");
   texture[8] = LoadTexBMP("woodenHandle.bmp");
   texture[9] = LoadTexBMP("leafyPlant2.bmp");
   texture[10] = LoadTexBMP("leafy2Stem.bmp");
   texture[11] = LoadTexBMP("woodShelf.bmp");
   texture[12] = LoadTexBMP("floor2.bmp");
   texture[13] = LoadTexBMP("pottingWood.bmp");
   texture[14] = LoadTexBMP("pottingSoil.bmp");
   //texture[15] = LoadTexBMP("glass3.bmp");
   texture[15] = LoadTexBMP("polycarbonate2.bmp");
   texture[16] = LoadTexBMP("pot2.bmp");
   texture[17] = LoadTexBMP("glassWindow2.bmp"); //wall
   texture[18] = LoadTexBMP("succulent3.bmp");
   //texture[19] = LoadTexBMP("smoothSuc.bmp");
 	texture[19] = LoadTexBMP("smallWindow.bmp");
 	texture[20] = LoadTexBMP("hawthoria.bmp"); // hawthoria
   	texture[21] = LoadTexBMP("truss.bmp");
   	texture[22] = LoadTexBMP("ceramic2.bmp");
   	texture[23] = LoadTexBMP("glazed2.bmp");
   	texture[24] = LoadTexBMP("planter.bmp");
   	texture[25] = LoadTexBMP("smoothSuc.bmp");
   	texture[26] = LoadTexBMP("mothers.bmp");

   ErrCheck("init");

	glutMainLoop();
   return 0;
}