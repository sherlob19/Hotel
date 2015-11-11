//#include <gl/gl.h>     // The GL Header File
//#include <windows.h>	//Solo para Windows
//#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header
//#include <stdlib.h>		// Descomentar para Linux
//#include <stdio.h>
//#include <string.h>
//#include <malloc.h>		// Solo para Windows

#include "texture.h"
#include "figuras.h"
#include "Camera.h"


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
CCamera objCamera; 

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 
//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int font=(int)GLUT_BITMAP_HELVETICA_18;

//Otras opciones son:
/*GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18*/



GLUquadricObj *quadratic;				// Storage For Our Quadratic Objects ( NEW )


//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = {18};

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = {22};

CTexture text1;
CTexture tex;
CTexture vent;
CTexture muro;
CTexture p1;//puertas
CTexture p2;
CTexture audit;
CTexture techo;

CFiguras fig1;
CFiguras fig2;

/*
Inicio variables para el proyecto
*/
float entrepiso = 2;
/*
Fin variables para el proyecto
*/

void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable ( GL_COLOR_MATERIAL );
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glPolygonMode(GL_BACK, GL_LINE);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
    
    text1.LoadBMP("Texturas/01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	tex.LoadTGA("Texturas/f6.tga");
	tex.BuildGLTexture();
	tex.ReleaseImage();
	
	vent.LoadTGA("Texturas/v1.tga");
	vent.BuildGLTexture();
	vent.ReleaseImage();

	muro.LoadTGA("Texturas/m2.tga");
	muro.BuildGLTexture();
	muro.ReleaseImage();

	p1.LoadTGA("Texturas/p1.tga");
	p1.BuildGLTexture();
	p1.ReleaseImage();


	p2.LoadTGA("Texturas/p3.tga");
	p2.BuildGLTexture();
	p2.ReleaseImage();


	audit.LoadTGA("Texturas/a2.tga");
	audit.BuildGLTexture();
	audit.ReleaseImage();

	techo.LoadTGA("Texturas/t1.tga");
	techo.BuildGLTexture();
	techo.ReleaseImage();


	objCamera.Position_Camera(0,2.5f,7, 0,2.5f,0, 0, 1, 0);

}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

/*
Esta función crea todos los techos de atras para adelante y de izquierda a derecha.
Cada techo esta encerrad en PUSH y POP porque me estoy regresando al origen (0,0,0) para mayor facilidad
al momento de hacer los techo del lado derecho.
Los que estan en el FOR son para la parte que quiere que se amueble el ultimo piso para el de teoría.
*/
void techos(){
	//techo1
	glPushMatrix();
		glColor3f(1,1,1);
		for (int i = 9; i < 60; i=i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);//sube al centro del entrepiso del 5 piso
				glPushMatrix();//parte grande
					glTranslatef(0,0,-96);//va al centro de la parte grande
					fig2.prisma(entrepiso,77.5,54,techo.GLindex);//dibuja el techo de la parte grande
				glPopMatrix();//regresa al origen
				glPushMatrix();//escalera
					glTranslatef(0,0,-63.5);//va al centro del ducto de las escaleras
					fig2.prisma(entrepiso,20,10,techo.GLindex);//dibuja el techo de las escaleras
				glPopMatrix();//regresa al origen
				glPushMatrix();//izq-escalera
					glTranslatef(-24.75,0,-66.375);//va al centro del techo costado izquierdo de las escaleras
					fig2.prisma(entrepiso,28.25,5.25,techo.GLindex);//dibuja el techo del costado izquierdo de las escaleras
				glPopMatrix();//regresa al origen
				glPushMatrix();//der-escalera
					glTranslatef(24.75,0,-66.375);//va al centro del techo costado derecho de las escaleras
					fig2.prisma(entrepiso,28.25,5.25,techo.GLindex);//dibuja el techo del costado derecho de las escaleras				
				glPopMatrix();//regresa al origen
				glPushMatrix();//izq-largo
					glTranslatef(-28.5,0,-32.25);//va al centro del techo del largo izquierdo
					fig2.prisma(entrepiso,20,63.5,techo.GLindex);//dibuja el techo del largo izquierdo			
				glPopMatrix();//regresa al origen
				glPushMatrix();//der-largo
					glTranslatef(28.5,0,-32.25);//va al centro del techo del largo derecho
					fig2.prisma(entrepiso,20,63.5,techo.GLindex);//dibuja el techo del largo derecho	
				glPopMatrix();//regresa al origen
			glPopMatrix();
		}
		glPushMatrix();//escalera
			glTranslatef(0,69,-63.5);//va al centro del ducto de las escaleras
			fig2.prisma(entrepiso,20,10,techo.GLindex);//dibuja el techo de las escaleras
		glPopMatrix();//regresa al origen
		glPushMatrix();//ducto-izq
			glTranslatef(-14,69,-9.5);//va al centro del techo del ducto del lado izquierdo
			fig2.prisma(entrepiso,7,11.5,techo.GLindex);//dibuja el techo del ducto del lado izquierdo
		glPopMatrix();//regresa al origen
		glPushMatrix();//ducto-der
			glTranslatef(14,69,-9.5);//va al centro del techo del ducto del lado derecho
			fig2.prisma(entrepiso,7,11.5,techo.GLindex);//dibuja el techo del ducto del lado derecho
		glPopMatrix();//regresa al origen
		
		glPushMatrix();
			glTranslatef(-16,59,39.55);
			fig2.prisma(entrepiso,38,86,techo.GLindex);//dibuja el techo largo en la parte 2
		glPopMatrix();//regresa al origen
		glPushMatrix();
			glTranslatef(19,59,18.5);
			fig2.prisma(entrepiso,32,44,techo.GLindex);//dibuja el techo mediando en la parte 2
		glPopMatrix();//regresa al origen
		glPushMatrix();
			glTranslatef(12.5,59,52);
			glRotatef(-45,0,1.0,0);
			fig2.prisma(entrepiso,8,11.5,techo.GLindex);//dibuja el techo en diagonal
		glPopMatrix();//regresa al origen
		glPushMatrix();
			glTranslatef(11.125,59,45.75);
			fig2.prisma(entrepiso,16.25,10.5,techo.GLindex);//dibuja el techo parte 1 deforme
		glPopMatrix();//regresa al origen
		glPushMatrix();
			glTranslatef(7.25,59,55);
			fig2.prisma(entrepiso,8.5,8,techo.GLindex);//dibuja el techo parte 2 deforme
		glPopMatrix();//regresa al origen
		glPushMatrix();
			glTranslatef(-0.375,31,79.125);
			fig2.prisma(entrepiso,9.25,9.75,techo.GLindex);//dibuja el piso del cuarto salido
			glTranslatef(0,28,0);
			fig2.prisma(entrepiso,9.25,9.75,techo.GLindex);//dibuja el techo del cuarto salido
		glPopMatrix();//regresa al origen
	glPopMatrix();
}

/*
Función para crear muros de 6 pisos.
Cada piso tiene 8 de altura y 2 de techo.
Despues del ultimo piso le agrego 3 para la barda en la azotea
*/
void muros6P(float largo,float prof){
	fig2.prisma(73,largo,prof,muro.GLindex);
}
/*
Función para los muros de la parte 1, ya que aqui pongo 3 metros para la
azotea y en la parte 2 solo pongo 2 para que se vea como en la imagen.
Es llamada cuando esta en una posición (?,5,?) por lo que dibuja el muro de
10 que es lo de 1 piso y sube 10 para llegar al centro del otro piso.
Al final sube lo necesario para colocar la parte extra de la azotea.
*/
void muroPisoGr(float ancho,float prof){
	glPushMatrix();
		for (int i = 0; i < 60; i= i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);
				fig2.prisma(10,ancho,prof,muro.GLindex);
			glPopMatrix();
		}
		glTranslatef(0,56.5,0);
		fig2.prisma(3,ancho,prof,muro.GLindex);
	glPopMatrix();
}

/*
Función para los muros con ventanas de la parte 1, respeta que se agrega 3 a la azotea.
Es llamada desde (?,5,?) por lo que debe bajar hasta (?,1.6,?) para empezar a construir los muros:
- el primero de 3.2 que es la barda
- el segundo de 2.8 que es la ventana
- el tercero de 4, 2 para el resto del piso y 2 para el techo
- el cuarto saliendo del for sería el de la azotea de 3
*/
void ventanaPorPisoGr(float ancho,float prof){
	glPushMatrix();
		glTranslatef(0,-3.4,0);
		for (int i = 0; i < 60; i= i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);
				fig2.prisma(3.2,ancho,prof,tex.GLindex);
				glTranslatef(0,3,0);
				glColor3f(1,1,1);
				fig2.prisma(2.8,ancho,prof,vent.GLindex);
				glColor3f(1,1,1);
				glTranslatef(0,3.4,0);
				fig2.prisma(4,ancho,prof,tex.GLindex);
			glPopMatrix();
		}
		glTranslatef(0,59.9,0);
		fig2.prisma(3,ancho,prof,tex.GLindex);
	glPopMatrix();
}

/*
Función para los muros de la parte 2 que tienen la puerta chica.
Primero hace el muro donde se encuentra la puerta, luego sube a hacer los muros repetidos
del resto de los pisos y termina con la parte de la azotea
*/
void muroPisoChConPuerta(float ancho,float prof){
	glPushMatrix();
		glTranslatef(0,0,0.75);//avanza .75 para la pared larga de 10 
		fig2.prisma(10,ancho,1.5,muro.GLindex);//dibuja pared de 10
		glTranslatef(0,-1.5,2.25);//baja a 3.5 para puerta de 7
		glColor3f(1,1,1);//cambia color a cafe
		fig2.prisma(7,ancho,3,p2.GLindex);//dibuja puerta de 7 de alto y 3 de largo
		glTranslatef(0,5,0);//sube 5 y llegua a 8.5
		glColor3f(1,1,1);//cambia color del muro
		fig2.prisma(3,ancho,3,muro.GLindex);//dibuja muro sobre puerta de 3 x 3
		glTranslatef(0,-3.5,2.25);//regresa a 5 y avanza despues de la puerta
		fig2.prisma(10,ancho,1.5,muro.GLindex);//dibuja pared de 10
		glTranslatef(0,10,-2.25);//sube 10 para el segundo piso y regresa al centro
		for (int i = 0; i < 50; i= i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);
				fig2.prisma(10,ancho,prof,muro.GLindex);
			glPopMatrix();
		}
		glTranslatef(0,46,0);
		fig2.prisma(2,ancho,prof,muro.GLindex);
	glPopMatrix();
}

/*
Función para los muros de la parte 2 con solo 2 en la parte de la azotea.
Es llamada desde (?,5,?) por lo que empieza a construir los muros de 10
*/
void muroPisoCh(float ancho,float prof){
	glPushMatrix();
		for (int i = 0; i < 60; i= i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);
				fig2.prisma(10,ancho,prof,muro.GLindex);
			glPopMatrix();
		}
		glTranslatef(0,56,0);
		fig2.prisma(2,ancho,prof,muro.GLindex);
	glPopMatrix();
}

/*
Función para los muros con ventana de la parte 2, con 2 en la parte de la azotea.
Igual que en la función para la parte 1 baja a 1.6 y construye la barda, la ventana y 
el muro superior con el entrepiso.
*/
void ventanaPorPisoCh(float ancho,float prof){
	glPushMatrix();
		glTranslatef(0,-3.4,0);
		for (int i = 0; i < 60; i= i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);
				fig2.prisma(3.2,ancho,prof,tex.GLindex);
				glTranslatef(0,3,0);
				glColor3f(1,1,1);
				fig2.prisma(2.8,ancho,prof,vent.GLindex);
				glColor3f(1,1,1);
				glTranslatef(0,3.4,0);
				fig2.prisma(4,ancho,prof,tex.GLindex);
			glPopMatrix();
		}
		glTranslatef(0,59.4,0);
		fig2.prisma(2,ancho,prof,tex.GLindex);
	glPopMatrix();
}

/*
Función para los muros con ventana de los últimos 3 pisos.
*/
void ventana3pisos(float ancho,float prof){
	glPushMatrix();
		glTranslatef(0,-3.4,0);
		for (int i = 0; i < 30; i= i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);
				fig2.prisma(3.2,ancho,prof,tex.GLindex);
				glTranslatef(0,3,0);
				glColor3f(1,1,1);
				fig2.prisma(2.8,ancho,prof,vent.GLindex);
				glColor3f(1,1,1);
				glTranslatef(0,3.4,0);
				fig2.prisma(4,ancho,prof,tex.GLindex);
			glPopMatrix();
		}
		glTranslatef(0,29.4,0);
		fig2.prisma(2,ancho,prof,tex.GLindex);
	glPopMatrix();
}

/*
Función para dibujar el bloque de las puertas grandes que puede ser sustituida.
Yo la use para hacer el cambio de color, pero si se usan texturas directamente donde es llamada esta
función no habría problema.
Tener en cuenta que si se quita esta función colocar color en blanco antes de donde se mandaba a llamar para
que la textura no se vea afectada, también será necesario regresar al color o texturas de los muros despues
*/
void puerta(float ancho,float prof){
	glPushMatrix();
		glColor3f(1,1,1);
		fig2.prisma(10,ancho,prof,p1.GLindex);
		glColor3f(1,1,1);
	glPopMatrix();
}

/*
Función que dibuja la puerta grande y las ventanas de los pisos superiores.
Aquí es donde se puede omitir la llamada a la función "puerta" haciendo lo de los colores antes y despues de
la sustitución por fig2.prisma...
*/
void ventana3pisosConPuerta(float ancho,float prof){
	glPushMatrix();
		puerta(ancho,prof);
		glTranslatef(0,6.6,0);
		for (int i = 0; i < 20; i= i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);
				fig2.prisma(3.2,ancho,prof,muro.GLindex);
				glTranslatef(0,3,0);
				glColor3f(1,1,1);
				fig2.prisma(2.8,ancho,prof,vent.GLindex);
				glColor3f(1,1,1);
				glTranslatef(0,3.4,0);
				fig2.prisma(4,ancho,prof,muro.GLindex);
			glPopMatrix();
		}
		glTranslatef(0,19.4,0);
		fig2.prisma(2,ancho,prof,muro.GLindex);
	glPopMatrix();
}
/*
Función para dibujar solo 2 ventanas correspondientes a la planta baja y primer piso.
*/
void ventana2pisos(float ancho,float prof){
	glPushMatrix();
		glTranslatef(0,-3.4,0);
		for (int i = 0; i < 20; i= i+10)
		{
			glPushMatrix();
				glTranslatef(0,i,0);
				fig2.prisma(3.2,ancho,prof,tex.GLindex);
				glTranslatef(0,3,0);
				glColor3f(1,1,1);
				fig2.prisma(2.8,ancho,prof,vent.GLindex);
				glColor3f(1,1,1);
				glTranslatef(0,3.4,0);
				fig2.prisma(4,ancho,prof,tex.GLindex);
			glPopMatrix();
		}
		glTranslatef(0,39.4,0);
		fig2.prisma(42,ancho,prof,muro.GLindex);
	glPopMatrix();
}
/*
En esta funcion se dibujan todos los muros del edificio
*/
void muros(){
	glTranslatef(0,5,0);
	glColor3f(1,1,1);
	//////////////////////////////////////
	//muros atras parte 1
	//////////////////////////////////////
	glPushMatrix();
		glTranslatef(-38,0,-123.25);
		muroPisoGr(2,0.5);//muro 1
		glTranslatef(2.5,0,0);
		ventanaPorPisoGr(3,0.5);//ventana 1
		glTranslatef(4.25,0,0);
		muroPisoGr(5.5,0.5);//muro 2
		glTranslatef(6.5,0,0);
		ventanaPorPisoGr(7.5,0.5);//ventana 2
		glTranslatef(9.5,0,0);
		muroPisoGr(11.5,0.5);//muro 3
		glTranslatef(9.5,0,0);
		ventanaPorPisoGr(7.5,0.5);//ventana 3
		glTranslatef(5.75,0,0);
		muroPisoGr(4,0.5);//muro 4
		glTranslatef(5.75,0,0);
		ventanaPorPisoGr(7.5,0.5);//ventana 4
		glTranslatef(9.5,0,0);
		muroPisoGr(11.5,0.5);//muro 5
		glTranslatef(9.5,0,0);
		ventanaPorPisoGr(7.5,0.5);//ventana 5
		glTranslatef(6.5,0,0);
		muroPisoGr(5.5,0.5);//muro 6
		glTranslatef(4.25,0,0);
		ventanaPorPisoGr(3,0.5);//ventana 6
		glTranslatef(2.5,0,0);
		muroPisoGr(2,0.5);//muro 7
	glPopMatrix();
	//////////////////////////////////////
	//muros izquierda parte 1
	//////////////////////////////////////
	glPushMatrix();
		glTranslatef(-38.75,0,-111);
		muroPisoGr(0.5,25);//muro 1
		glTranslatef(0,0,16.5);
		ventanaPorPisoGr(0.5,8);//ventana 1
		glTranslatef(0,0,10.25);
		muroPisoGr(0.5,12.5);//muro 2
		glTranslatef(0,0,8.25);
		ventanaPorPisoGr(0.5,4);//ventana 2
		glTranslatef(0,0,3);
		muroPisoGr(0.5,2);//muro 3
		glTranslatef(0,0,2.5);
		ventanaPorPisoGr(0.5,3);//ventana 3
		glTranslatef(0,0,7.25);
		muroPisoGr(0.5,11.5);//muro 4
		glTranslatef(0,0,9.75);
		ventanaPorPisoGr(0.5,8);//ventana 4
		glTranslatef(0,0,9.75);
		muroPisoGr(0.5,11.5);//muro 5
		glTranslatef(0,0,9.75);
		ventanaPorPisoGr(0.5,8);//ventana 5
		glTranslatef(0,0,11.625);
		muroPisoGr(0.5,15.25);//muro 6
		glTranslatef(0,0,11.625);
		ventanaPorPisoGr(0.5,8);//ventana 6
		glTranslatef(0,0,7.375);
		muroPisoGr(0.5,6.75);//muro 7
	glPopMatrix();
	//////////////////////////////////////
	//muros derecha parte 1
	//////////////////////////////////////
	glPushMatrix();
		glTranslatef(38.75,0,-111);
		muroPisoGr(0.5,25);//muro 1
		glTranslatef(0,0,16.5);
		ventanaPorPisoGr(0.5,8);//ventana 1
		glTranslatef(0,0,10.25);
		muroPisoGr(0.5,12.5);//muro 2
		glTranslatef(0,0,8.25);
		ventanaPorPisoGr(0.5,4);//ventana 2
		glTranslatef(0,0,3);
		muroPisoGr(0.5,2);//muro 3
		glTranslatef(0,0,2.5);
		ventanaPorPisoGr(0.5,3);//ventana 3
		glTranslatef(0,0,7.25);
		muroPisoGr(0.5,11.5);//muro 4
		glTranslatef(0,0,9.75);
		ventanaPorPisoGr(0.5,8);//ventana 4
		glTranslatef(0,0,8.375);
		muroPisoGr(0.5,8.75);//muro 5
		glTranslatef(0,0,7.375);
		ventanaPorPisoGr(0.5,6);//ventana 5
		glTranslatef(0,0,5.25);
		muroPisoGr(0.5,4.5);//muro 6
		glTranslatef(0,0,5.25);
		ventanaPorPisoGr(0.5,6);//ventana 6
		glTranslatef(0,0,5.25);
		muroPisoGr(0.5,4.5);//muro 7
		glTranslatef(0,0,5.25);
		ventanaPorPisoGr(0.5,6);//ventana 7
		glTranslatef(0,0,5.25);
		muroPisoGr(0.5,4.5);//muro 8
		glTranslatef(0,0,5.25);
		ventanaPorPisoGr(0.5,6);//ventana 8
		glTranslatef(0,0,4.625);
		muroPisoGr(0.5,3.25);//muro 9
	glPopMatrix();
	//////////////////////////////////////
	//muros enfrente parte 1
	//////////////////////////////////////
	glPushMatrix();
		glPushMatrix();
			glTranslatef(-28.5,0,-0.25);
			muroPisoGr(20.875,0.5);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-18.25,0,-7.75);
			muroPisoGr(0.5,15.5);					
		glPopMatrix();
		glPushMatrix();
			glTranslatef(28.5,0,-0.25);
			muroPisoGr(20.875,0.5);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(18.25,0,-7.75);
			muroPisoGr(0.5,15.5);					
		glPopMatrix();
	glPopMatrix();
	//////////////////////////////////////
	//muros interiores parte 1
	//////////////////////////////////////
	glPushMatrix();
		glPushMatrix();//escaleras
			glTranslatef(0,31.5,-68.75);//el centro es 31.5 pero ya esta en 5
			muros6P(20,0.5);//dibuja muro atraz
			glTranslatef(-10.25,0,5);
			muros6P(0.5,10.5);//dibuja muro izquierdo
			glTranslatef(20.5,0,0);
			muros6P(0.5,10.5);//dibuja muro derecho
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-14.5,0,-63.5);
			ventanaPorPisoGr(8,0.5);//vent izq escaleras
			glTranslatef(14.5*2,0,0);
			ventanaPorPisoGr(8,0.5);//vent der escaleras
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-18.25,0,-62.5);
			muroPisoGr(0.5,2);//col 1 izq
			glTranslatef(0,0,10);
			ventanaPorPisoGr(0.5,18);//vent 1 izq
			glTranslatef(0,0,10);
			muroPisoGr(0.5,2);//col 2 izq
			glTranslatef(0,0,10);
			ventanaPorPisoGr(0.5,18);//vent 2 izq
			glTranslatef(0,0,10);
			muroPisoGr(0.5,2);//col 3 izq
			glTranslatef(0,0,4);
			ventanaPorPisoGr(0.5,6);//vent 3 izq
		glPopMatrix();
		glPushMatrix();
			glTranslatef(18.25,0,-62.5);
			muroPisoGr(0.5,2);//col 1 der
			glTranslatef(0,0,10);
			ventanaPorPisoGr(0.5,18);//vent 1 der
			glTranslatef(0,0,10);
			muroPisoGr(0.5,2);//col 2 izq
			glTranslatef(0,0,10);
			ventanaPorPisoGr(0.5,18);//vent 2 der
			glTranslatef(0,0,10);
			muroPisoGr(0.5,2);//col 3 izq
			glTranslatef(0,0,4);
			ventanaPorPisoGr(0.5,6);//vent 3 der
		glPopMatrix();
		glPushMatrix();//Para los ductos
			glTranslatef(0,31.5,0);//el centro es 31.5 pero ya esta en 5
			glPushMatrix();//atras-ducto-izq
				glTranslatef(-14,0,-15.25);
				muros6P(8,0.5);					
			glPopMatrix();
			glPushMatrix();//izq-ducto-izq
				glTranslatef(-17.75,0,-9.5);
				muros6P(0.5,12);					
			glPopMatrix();
			glPushMatrix();//der-ducto-izq
				glTranslatef(-10.25,0,-9.5);
				muros6P(0.5,12);					
			glPopMatrix();
			glPushMatrix();//frente-ducto-izq
				glTranslatef(-14,0,-3.75);
				muros6P(8,0.5);						
			glPopMatrix();
			glPushMatrix();//atras-ducto-der
				glTranslatef(14,0,-15.25);
				muros6P(8,0.5);						
			glPopMatrix();
			glPushMatrix();//izq-ducto-der
				glTranslatef(17.75,0,-9.5);
				muros6P(0.5,12);				
			glPopMatrix();
			glPushMatrix();//der-ducto-der
				glTranslatef(10.25,0,-9.5);
				muros6P(0.5,12);						
			glPopMatrix();
			glPushMatrix();//frente-ducto-der
				glTranslatef(14,0,-3.75);
				muros6P(8,0.5);				
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0,-3.75);
			ventanaPorPisoGr(20.5,0.5);//ventanas entre ductos
		glPopMatrix();
	glPopMatrix();
	//////////////////////////////////////
	//muros izquierda parte 2
	//////////////////////////////////////
	glPushMatrix();
		glTranslatef(-35.25,0,0);
		muroPisoChConPuerta(0.5,6);//muro 1
		glTranslatef(0,0,8.5);
		ventanaPorPisoCh(0.5,5);//ventana 1
		glTranslatef(0,0,3.5);
		muroPisoCh(0.5,2);//muro 2
		glTranslatef(0,0,3);
		ventanaPorPisoCh(0.5,4);//ventana 2
		glTranslatef(0,0,7);
		muroPisoCh(0.5,10);//muro 3
		glTranslatef(0,0,7);
		ventanaPorPisoCh(0.5,4);//ventana 3
		glTranslatef(0,0,4);
		muroPisoCh(0.5,4);//muro 4
		glTranslatef(0,0,4);
		ventanaPorPisoCh(0.5,4);//ventana 4
		glTranslatef(0,0,7);
		muroPisoCh(0.5,10);//muro 5
		glTranslatef(0,0,7);
		ventanaPorPisoCh(0.5,4);//ventana 5
		glTranslatef(0,0,3);
		muroPisoCh(0.5,2);//muro 6
		glTranslatef(0,0,3);
		ventanaPorPisoCh(0.5,4);//ventana 6
		glTranslatef(0,0,4);
		muroPisoCh(0.5,4);//muro 7
		glTranslatef(0,0,4);
		ventanaPorPisoCh(0.5,4);//ventana 7
		glTranslatef(0,0,3);
		muroPisoCh(0.5,2);//muro 8
		glTranslatef(0,0,3);
		ventanaPorPisoCh(0.5,4);//ventana 8
		glTranslatef(0,0,4);
		muroPisoCh(0.5,4);//muro 9
		glTranslatef(0,0,4);
		ventanaPorPisoCh(0.5,4);//ventana 9
		glTranslatef(0,0,3);
		muroPisoCh(0.5,2);//muro 10
	glPopMatrix();
	//////////////////////////////////////
	//muros derecha parte 2
	//////////////////////////////////////
	glPushMatrix();
		glTranslatef(35.25,0,0);
		muroPisoChConPuerta(0.5,6);//muro 1
		glTranslatef(0,0,8.5);
		ventanaPorPisoCh(0.5,5);//ventana 1
		glTranslatef(0,0,3.5);
		muroPisoCh(0.5,2);//muro 2
		glTranslatef(0,0,3);
		ventanaPorPisoCh(0.5,4);//ventana 2
		glTranslatef(0,0,7);
		muroPisoCh(0.5,10);//muro 3
		glTranslatef(0,0,7);
		ventanaPorPisoCh(0.5,4);//ventana 3
		glTranslatef(0,0,4);
		muroPisoCh(0.5,4);//muro 4
		glTranslatef(0,0,4);
		ventanaPorPisoCh(0.5,4);//ventana 4
		glTranslatef(0,0,3);
		muroPisoCh(0.5,2);//muro 5
		glTranslatef(-8,0,0.75);
		muroPisoCh(16,0.5);
	glPopMatrix();

	//////////////////////////////////////
	//muros 3, 4 y 5 piso parte deforme
	//////////////////////////////////////
	glPushMatrix();
		glPushMatrix();
			glTranslatef(19.5,0,46);
			ventanaPorPisoCh(0.5,10);//vent vert
		glPopMatrix();
		glPushMatrix();
			glTranslatef(15.5,30,55);
			glRotatef(-45,0,1.0,0);
			ventana3pisosConPuerta(0.5,11.5);//vent incli
			glTranslatef(0,-30,0);
			puerta(0.5,11.5);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(7.5,0,59);
			ventanaPorPisoCh(8.5,0.5);//vent horizo
		glPopMatrix();
		glPushMatrix();
			glTranslatef(3,0,66.25);
			muroPisoCh(0.5,15);//pared
		glPopMatrix();
		glPushMatrix();
			glTranslatef(3.75,30,74);
			ventana3pisos(2,0.5);//v1
			glTranslatef(0.75,0,5);
			ventana3pisos(0.5,10);//v2
			glTranslatef(-4.75,0,5.25);
			ventana3pisos(10,0.5);//v3
			glTranslatef(-5,0,-0.75);
			ventana3pisos(0.5,2);//v4
		glPopMatrix();
	glPopMatrix();

	//////////////////////////////////////
	//muros frente parte 2
	//////////////////////////////////////
	glPushMatrix();
		glTranslatef(-30.5,0,82.75);
		muroPisoCh(9,0.5);//muro 1
		glTranslatef(8.5,0,0);
		ventana2pisos(8,0.5);//vent 1
		glTranslatef(5,0,0);
		muroPisoCh(2,0.5);//muro 2
		glTranslatef(5,0,0);
		ventana2pisos(8,0.5);//vent 2
		glTranslatef(5.25,0,0);
		muroPisoCh(2.5,0.5);//muro 3
		glTranslatef(5.5,10,0);
		fig2.prisma(30,8.5,0.5,muro.GLindex);//muro 4
		glTranslatef(4.25,-13.4,-4.375);
		fig2.prisma(3.2,0.5,9.25,tex.GLindex);//muro bajo vent
		glTranslatef(0,16.4,0); //>---------------------------------------------------------------------------------------------------------------
		fig2.prisma(24,0.5,9.25,tex.GLindex);//muro sup vent
		glTranslatef(0,-13.4,3.125);
		fig2.prisma(2.8,0.5,3,tex.GLindex);//muro izq vent
		glTranslatef(0,0,-3);
		glColor3f(1,1,1);
		fig2.prisma(2.8,0.5,3,vent.GLindex);//ventana
		glColor3f(1,1,1);
		glTranslatef(0,0,-3.125);
		fig2.prisma(2.8,0.5,3.25,tex.GLindex);//muro der vent
	glPopMatrix();

	//////////////////////////////////////
	//muros piso 2 y 3
	//////////////////////////////////////
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(19.5,15,62);
		fig2.prisma(20,32,42,audit.GLindex);//auditorio
	glPopMatrix();

}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();

	glPushMatrix();	
	glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	

		glPushMatrix();		
			glPushMatrix(); //Creamos cielo
				glColor3f(1.0, 1.0, 1.0);
				glDisable(GL_LIGHTING);
				//glTranslatef(0,60,0);
				fig1.skybox(300.0, 250.0, 600.0,text1.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();
				
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glLineWidth(2.0);
				glBegin(GL_LINES); //Ejes de Referencia
					glColor3f(1.0, 0.0, 0.0);
					glVertex3f(-80, 0.0, 0);
					glVertex3f(80.0, 0.0, 0);
					glColor3f(0.0, 1.0, 0.0);
					glVertex3f(0.0, 0.0, 0.0);
					glVertex3f(0.0, 80.0, 0.0);
					glColor3f(0.0, 0.0, 1.0);
					glVertex3f(0.0, 0.0, 0.0);
					glVertex3f(0.0, 0.0, 85.0);
				glEnd();
				glEnable(GL_LIGHTING);
				
			glPopMatrix();
		
			//Poner Figuras Aqui
			//glColor3f(1.0, 1.0, 0.0);
			//fig2.prisma(1.0, 1.0, 1.0, 0);
			//fig2.esfera(1,12, 12, 0);  //Pueden mandar llamar nuevas figuras utilizando la variable fig2 y el operador punto
			
			/*
			Falta hacer la parte de las escaleras de la entrada para lo cual todo se tendría que levantar N unidades
			por eso lo pongo en el PUSH y POP para subirlo
			*/
			glPushMatrix();
				glTranslatef(0,0,0);
				techos();
				muros();
			glPopMatrix();
			//aqui podría continuar desde la base del escenario
			

		glPopMatrix();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
		glColor3f(1.0,0.0,0.0);
		pintaTexto(-0.25, 0.23,-0.25,(void *)font,"Figuras");
		pintaTexto(-0.25, 0.21,-0.25,(void *)font,"Crear modelos basicos");
		glColor3f(1.0,1.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glutSwapBuffers ( );

}

void animacion()
{
	/*fig2.text_izq-= 0.001;
	fig2.text_der-= 0.001;
	if(fig2.text_izq<-1)
		fig2.text_izq=0;
	if(fig2.text_der<0)
		fig2.text_der=1;*/
	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {
		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;

		case 'r':		//
			break;

		case 'R':		//
			break;

		case 'f':		//
		case 'F':
			
			break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		//pos_camY -= 0.5f;
		//pos_cam.y += 0.5f;
		//eye_cam.y += 0.5f;
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		//pos_camY += 0.5f;
		//pos_cam.y -= 0.5f;
		//eye_cam.y -= 0.5f;
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}


int main ( int argc, char** argv )   // Main Function
{
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (80, 80);	//Posicion de la Ventana
  glutCreateWindow    ("Figura Examen"); // Nombre de la Ventana

  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
glutIdleFunc		  ( animacion );
  glutMainLoop        ( );          // 

  return 0;
}


