/*
COMPUTACAO GRAFICA 2021
ALEXY DE ALMEIDA
N_2019192123
*/

/* --------------------------------------- INCLUDES -------------------------------------- */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL\glut.h>
#include "RgbImage.h"
#include <windows.h>


/* --------------------------------------- DEFINES --------------------------------------- */


#define PI			3.14159
#define BLUE		0.0, 0.0, 1.0, 1.0
#define LIGHT_B		0.6, 0.8, 0.9, 1.0
#define RED			1.0, 0.0, 0.0, 1.0
#define YELLOW		1.0, 1.0, 0.0, 1.0
#define GREEN		0.0, 1.0, 0.0, 1.0
#define ORANGE		1.0, 0.5, 0.1, 1.0
#define WHITE		1.0, 1.0, 1.0, 1.0
#define BLACK		0.0, 0.0, 0.0, 1.0
#define GRAY		0.15, 0.15, 0.15, 1.0
#define GRAY_MEDIUM	0.20, 0.20, 0.20, 1.0
#define GRAY_DARK	0.05, 0.05, 0.05, 0.05


/* --------------------------------------- ANIMACOES ------------------------------------- */


float		centrox, centrox_botao1, centrox_botao2, centrox_joystick = 0;
float rotacao, rotacao_botao1, rotacao_joystick_x, rotacao_joystick_z = 0;
GLfloat										 altura, altura_joystick  = 0;

// joystick
bool   start_animation_joystick = false;
bool		 animation_joystick = true;
int				   joystick_dir = 0;

// botao 1
float			  altura_botao1 = 0;
float		increment_y_button1 = 0.005;
bool	start_animation_button1 = false;
bool	 animation_button_down1 = true;

// botao 2
float			  altura_botao2 = 0;
float		increment_y_button2 = 0.005;
bool	start_animation_button2 = false;
bool	 animation_button_down2 = true;

// tempo
GLint		msec = 10;


/* --------------------------------------- VERTICES --------------------------------------- */


// maquina
GLfloat tam_maquina				   = 1;
static GLfloat  vertices_maquina[] = {
		// esquerda
	-tam_maquina,  -tam_maquina,  tam_maquina,	// 0 
	-tam_maquina,   tam_maquina,  tam_maquina,	// 1 
	-tam_maquina,   tam_maquina, -tam_maquina,	// 2 
	-tam_maquina,  -tam_maquina, -tam_maquina,	// 3 
		// cima
	-tam_maquina,   tam_maquina,  tam_maquina,	// 4 
	-tam_maquina,   tam_maquina, -tam_maquina,	// 5 
		tam_maquina,   tam_maquina, -tam_maquina,	// 6 
		tam_maquina,   tam_maquina,  tam_maquina,	// 7   
		// baixo
		-tam_maquina,  -tam_maquina,  tam_maquina, // 8
		tam_maquina,   -tam_maquina,  tam_maquina, // 9
		tam_maquina,   -tam_maquina, -tam_maquina, // 10
		-tam_maquina,  -tam_maquina, -tam_maquina, // 11
		// atras
		-tam_maquina,  -tam_maquina, -tam_maquina, // 12
		-tam_maquina,   tam_maquina, -tam_maquina, // 13
		tam_maquina,    tam_maquina, -tam_maquina, // 14
		tam_maquina,   -tam_maquina, -tam_maquina, // 15
		// frente
		-tam_maquina,  -tam_maquina,  tam_maquina, // 16
		tam_maquina,   -tam_maquina,  tam_maquina, // 17
		tam_maquina,    tam_maquina,  tam_maquina, // 18
		-tam_maquina,   tam_maquina,  tam_maquina, // 19
		// frente caixa
		tam_maquina,   -tam_maquina,  tam_maquina, // 20
		3*tam_maquina, -tam_maquina,  tam_maquina, // 21
		3*tam_maquina,  0,			   tam_maquina, // 22
		tam_maquina,    tam_maquina,  tam_maquina, // 23
		// tras caixa
		tam_maquina,   -tam_maquina, -tam_maquina, // 24
		tam_maquina,    tam_maquina, -tam_maquina, // 25
		3*tam_maquina,  0,			  -tam_maquina,	// 26
		3*tam_maquina, -tam_maquina, -tam_maquina,	// 27
		// baixo caixa
		tam_maquina,   -tam_maquina,  tam_maquina, // 28
		3*tam_maquina, -tam_maquina,  tam_maquina, // 29
		3*tam_maquina, -tam_maquina, -tam_maquina,	// 30
		tam_maquina,   -tam_maquina, -tam_maquina, // 31
		// direita caixa
		3*tam_maquina, -tam_maquina,  tam_maquina, // 32
		3*tam_maquina,  0,			   tam_maquina, // 33
		3*tam_maquina,  0,			  -tam_maquina, // 34
		3*tam_maquina, -tam_maquina, -tam_maquina, // 35
		// caixa
		tam_maquina,	 0,			   tam_maquina, // 36
		3 * tam_maquina,0,			   tam_maquina, // 37
		3 * tam_maquina,0,			  -tam_maquina, // 38
		tam_maquina,    0,			  -tam_maquina, // 39
		// moldura
		tam_maquina, tam_maquina*0.8, tam_maquina, // 40
		tam_maquina,   tam_maquina,   tam_maquina, // 41
		tam_maquina,   tam_maquina,  -tam_maquina,	// 42
		tam_maquina, tam_maquina*0.8,-tam_maquina,	// 43 
		// ecra
		tam_maquina,	 0,			   tam_maquina, // 44
		tam_maquina, tam_maquina*0.8, tam_maquina, // 45
		tam_maquina, tam_maquina*0.8,-tam_maquina, // 46
		tam_maquina,    0,			  -tam_maquina, // 47
};
static GLfloat   normais_maquina[] = {
		// esquerda
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
		// cima
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		// baixo
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		// atras
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
		// frente
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		// frente caixa
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		// tras caixa
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
		0.0,  0.0,  -1.0,
		// baixo caixa
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		0.0,  -1.0,  0.0,
		// direita caixa
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		// caixa
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		// moldura
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		// ecra
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
};
static GLuint	esquerda_maquina[] = { 0,  1,  2,  3 };
static GLuint		cima_maquina[] = { 4,  5,  6,  7 };
static GLuint	   baixo_maquina[] = { 8,  11, 10, 9 };
static GLuint	   atras_maquina[] = { 12, 13, 14, 15 };
static GLuint	  frente_maquina[] = { 16, 17, 18, 19 };
static GLuint       frente_caixa[] = { 20, 21, 22, 23 };
static GLuint	      tras_caixa[] = { 24, 25, 26, 27 };
static GLuint		 baixo_caixa[] = { 28, 29, 30, 31 };
static GLuint	   direita_caixa[] = { 32, 33, 34, 35 };
static GLuint              caixa[] = { 36, 37, 38, 39 };
static GLuint			 moldura[] = { 40, 41, 42, 43 };
static GLuint			    ecra[] = { 44, 45, 46, 47 };
	
// cubos
static GLfloat vertices_cubo[] = {
	// esquerda botao
	-tam_maquina,  -tam_maquina,   tam_maquina,
	-tam_maquina,   tam_maquina,   tam_maquina,
	-tam_maquina,   tam_maquina,  -tam_maquina,
	-tam_maquina,  -tam_maquina,  -tam_maquina,
	// direita botao
	tam_maquina,  -tam_maquina,  tam_maquina,
	tam_maquina,   tam_maquina,  tam_maquina,
	tam_maquina,   tam_maquina, -tam_maquina,
	tam_maquina,  -tam_maquina, -tam_maquina,
	// atras botao
	-tam_maquina,  -tam_maquina,  -tam_maquina,
	-tam_maquina,   tam_maquina,  -tam_maquina,
	tam_maquina,   tam_maquina,  -tam_maquina,
	tam_maquina,  -tam_maquina,  -tam_maquina,
	// frente botao
	-tam_maquina,  -tam_maquina,   tam_maquina,
	tam_maquina,  -tam_maquina,   tam_maquina,
	tam_maquina,   tam_maquina,   tam_maquina,
	-tam_maquina,   tam_maquina,   tam_maquina,
	// cima botao
	-tam_maquina,   tam_maquina,   tam_maquina,
	-tam_maquina,   tam_maquina,  -tam_maquina,
	tam_maquina,   tam_maquina,  -tam_maquina,
	tam_maquina,   tam_maquina,   tam_maquina,
	// baixo botao
	-tam_maquina,  -tam_maquina,   tam_maquina,
	tam_maquina,  -tam_maquina,   tam_maquina,
	tam_maquina,  -tam_maquina,  -tam_maquina,
	-tam_maquina,  -tam_maquina,  -tam_maquina,
};
static GLfloat	normais_cubo[] = {
	// esquerda
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	// direita 
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	// atras
	0.0,  0.0,  -1.0,
	0.0,  0.0,  -1.0,
	0.0,  0.0,  -1.0,
	0.0,  0.0,  -1.0,
	// frente
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	// cima
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	// baixo
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
};
static GLuint  esquerda_cubo[] = { 0,  1,  2,  3 };
static GLuint   direita_cubo[] = { 4,  5,  6,  7 };
static GLuint     atras_cubo[] = { 8,  11, 10, 9 };
static GLuint	 frente_cubo[] = { 12, 13, 14, 15 };
static GLuint	   cima_cubo[] = { 16, 17, 18, 19 };
static GLuint     baixo_cubo[] = { 20, 21, 22, 23 };


/* ------------------------------------------ COR ----------------------------------------- */


static GLfloat		cor[] = {
	// esquerda
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	// cima
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	// baixo
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	// atras
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	// frente
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	// frente caixa
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	// tras caixa
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	// baixo caixa
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	// direita caixa
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	// caixa
	ORANGE,
	ORANGE,
	ORANGE,
	ORANGE,
	// moldura
	RED,
	GRAY_DARK,
	GRAY_DARK,
	RED,
	// ecra
	LIGHT_B,
	BLUE,
	LIGHT_B,
	BLUE,

	// ----- joystick ----- //

	// esquerda base
	RED,
	RED,
	RED,
	RED,
	// direita base
	RED,
	RED,
	RED,
	RED,
	// atras base
	RED,
	RED,
	RED,
	RED,
	// frente base
	RED,
	RED,
	RED,
	RED,

	// esquerda botao
	RED,
	RED,
	RED,
	RED,
	// direita botao
	RED,
	RED,
	RED,
	RED,
	// atras botao
	RED,
	RED,
	RED,
	RED,
	// frente botao
	RED,
	RED,
	RED,
	RED,
	// cima botao
	RED,
	RED,
	RED,
	RED,
	// baixo botao
	RED,
	RED,
	RED,
	RED
};
static GLfloat cor_cubo[] = {
	// esquerda
RED,
RED,
RED,
RED,
// direita
RED,
RED,
RED,
RED,
// cima
RED,
RED,
RED,
RED,
// baixo
RED,
RED,
RED,
RED,
// atras
RED,
RED,
RED,
RED,
// frente
RED,
RED,
RED,
RED
};


/* ---------------------------------------- TEXTURA --------------------------------------- */


GLuint   textures[9];
RgbImage imag;

// maquina
static GLfloat texturas_maquina[] = {
		// esquerda
		1, 0, 1, 1, 0, 1, 0, 0,

		// cima
		0, 0, 1, 0, 1, 1, 0, 1,

		// baixo
		0, 0, 1, 0, 1, 1, 0, 1,

		// atras
		1, 0, 1, 1, 0, 1, 0, 0,

		// frente
		1, 0, 1, 1, 0, 1, 0, 0,

		// frente caixa
		1, 0, 1, 1, 0, 1, 0, 0,

		// tras caixa
		1, 0, 1, 1, 0, 1, 0, 0,

		// baixo caixa
		0, 0, 1, 0, 1, 1, 0, 1,

		// direita caixa
		0, 0, 0, 1, 1, 1, 1, 0,

		// caixa
		0, 0.8, 0, 0.5, 1, 0.5, 1, 0.8,

		// moldura
		0, 0, 0, 1, 1, 1, 1, 0,

		// ecra
		0, 0, 1, 0, 1, 1, 0, 1
	};

// cubos
static GLfloat		 texturas_cubos[] = {
		// esquerda botao
		0, 0, 1, 0, 1, 1, 0, 1,

		// direita botao
		0, 0, 1, 0, 1, 1, 0, 1,

		// atras botao
		0, 0, 1, 0, 1, 1, 0, 1,

		// frente botao
		0, 0, 1, 0, 1, 1, 0, 1,

		// cima botao
		0, 0, 1, 0, 1, 1, 0, 1,

		// baixo botao
		0, 0, 1, 0, 1, 1, 0, 1
	};
static GLfloat texturas_upper_stick[] = {
		// esquerda botao
		0.45, 0.45, 0.5, 0.45, 0.5, 0.5, 0.45, 0.5,

		// direita botao
		0.45, 0.45, 0.5, 0.45, 0.5, 0.5, 0.45, 0.5,

		// atras botao
		0.5, 0.5, 0.45, 0.5, 0.45, 0.45, 0.5, 0.45,

		// frente botao
		0.5, 0.5, 0.45, 0.5, 0.45, 0.45, 0.5, 0.45,

		// cima botao
		0.45, 0.45, 0.5, 0.45, 0.5, 0.5, 0.45, 0.5,

		// baixo botao
		0.45, 0.45, 0.5, 0.45, 0.5, 0.5, 0.45, 0.5,
	};
static GLfloat		 texturas_botao[] = {
		// esquerda botao
		0, 0, 1, 0, 1, 1, 0, 1,

		// direita botao
		0, 0, 1, 0, 1, 1, 0, 1,

		// atras botao
		0, 0, 1, 0, 1, 1, 0, 1,

		// frente botao
		0, 0, 1, 0, 1, 1, 0, 1,

		// cima botao
		0, 0.25, 0.25, 0, 0.25, 0.25, 0, 0.25,

		// baixo botao
		0, 0, 1, 0, 1, 1, 0, 1
	};


/* ------------------------------------------ LUZ ----------------------------------------- */

// ----- ambiente
GLint   Dia = 0;     
GLfloat intensidadeDia = 0.0;
GLfloat luzGlobalCorAmb[4] = { intensidadeDia, intensidadeDia,intensidadeDia, 1.0 };

// ----- pontual no teto
GLint   luzR = 1;
GLint   luzG = 1;	 
GLint   luzB = 1;

GLint   ligaTeto				= 1;															// 'T'  								 
GLfloat luz_teto_posicao[4]		= { tam_maquina, tam_maquina * 2, 0, 1.0 };
GLfloat luz_teto_ambiente[4]	= { 0, 0, 0, 0 };
GLfloat luz_teto_difusa[4]		= { luzR, luzG, luzB, 1 };
GLfloat luz_teto_especular[4]	= { luzR, luzG, luzB, 1 };

GLfloat intensidadeT = 0.3;														// 'I'

/* --------------------------------------- MATERIAL --------------------------------------- */


void initMaterials(int material);
char Materiais[18][30] = {
	"Esmerald", "Jade", "obsidian", "Pearl", "Ruby", "Turquoise", 
	"Brass", "Bronze", "Chrome", "Copper", "Gold", "Silver", 
	"blackPlastic", "cyankPlastic", "greenPlastic", "redPlastic", 
	"whitePlastic","yellowPlastic"};


/* -------------------------------------- COORD e OBS ------------------------------------- */


GLint		wScreen = 800, hScreen = 600;		// janela
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;	// Mundo
GLboolean   frenteVisivel = 1;

GLfloat		rVisao = 10, aVisao = 0.5 * PI, incVisao = 0.05;
GLfloat		obsP[] = { rVisao * cos(aVisao), 3.0, rVisao * sin(aVisao) };
GLfloat		angZoom = 45;
GLfloat		incZoom = 3;


/* ------------------------------------ 1. INICIALIZAR ------------------------------------ */


void initLights(void) {
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
	// Teto
	glLightfv(GL_LIGHT0, GL_POSITION, luz_teto_posicao);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_teto_ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_teto_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luz_teto_especular);
}

void init_textures() {

	glGenTextures(1, &textures[0]);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	imag.LoadBmpFile("azul_maquina.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

	glGenTextures(1, &textures[1]);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	imag.LoadBmpFile("wallpaper.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

	glGenTextures(1, &textures[2]);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	imag.LoadBmpFile("red_plastic.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

	glGenTextures(1, &textures[3]);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	imag.LoadBmpFile("screen.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

	glGenTextures(1, &textures[4]);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	imag.LoadBmpFile("red_rubber.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

	glGenTextures(1, &textures[5]);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	imag.LoadBmpFile("red_plastic_2.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

	glGenTextures(1, &textures[6]);
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	imag.LoadBmpFile("grey_board.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

	glGenTextures(1, &textures[7]);
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	imag.LoadBmpFile("moldura.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

	glGenTextures(1, &textures[8]);
	glBindTexture(GL_TEXTURE_2D, textures[8]);
	imag.LoadBmpFile("azul_caixa.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());
};

void init(void)
{
	glClearColor(0, 0, 0, 1.0);							// Apagar
	glShadeModel(GL_SMOOTH);									// Interpolacao de cores	
	glEnable(GL_DEPTH_TEST);									// Profundidade

	// NORMAIS
	glEnable(GL_NORMALIZE);

	// TEXTURAS
	init_textures();

	// LUZ
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	initLights();

	// MATERIAIS
	//initMaterials(12);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void drawEixos()
{
	glColor4f(RED);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(10, 0, 0);
	glEnd();
	glColor4f(GREEN);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 10, 0);
	glEnd();
	glColor4f(BLUE);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 10);
	glEnd();
}


/* ------------------------------------- 2. DESENHOS ------------------------------------- */


void drawStick() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, atras_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo_cubo);
	glDisable(GL_TEXTURE_2D);
}

void drawUpperStick() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, atras_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo_cubo);
	glDisable(GL_TEXTURE_2D);
}

void drawButton1() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, atras_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente_cubo);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_cubo);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo_cubo);
	glDisable(GL_TEXTURE_2D);
}

void drawButton2() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, atras_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente_cubo);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_cubo);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo_cubo);
	glDisable(GL_TEXTURE_2D);
}

void drawMachine() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda_maquina);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_maquina);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo_maquina);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, atras_maquina);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente_maquina);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente_caixa);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras_caixa);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo_caixa);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita_caixa);
	glBindTexture(GL_TEXTURE_2D, textures[8]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, caixa);
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, moldura);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, ecra);
	glDisable(GL_TEXTURE_2D);
}

void drawScene()
{

	// --- figura inteira --- //

	glTranslatef(centrox, altura, 0.0);
	glRotatef(rotacao, 0.0, 1.0, 0.0);
	glScalef(1, 2.5, 1.5);

	// --- m�quina --- //

	glColorPointer(4, GL_FLOAT, 0, cor);
	glVertexPointer(3, GL_FLOAT, 0, vertices_maquina);
	glTexCoordPointer(2, GL_FLOAT, 0, texturas_maquina);
	
	glPushMatrix();
		drawMachine();
	glPopMatrix();

	// --- joystick e bot�es --- //

	glColorPointer(4, GL_FLOAT, 0, cor_cubo);
	

	// --- joystick --- //

	glPushMatrix();

		glTranslatef(tam_maquina * 2.25, -0.015, tam_maquina * 0.5);
		glScalef(0.03, 0.03, 0.03);
		glRotatef(rotacao_joystick_x, 0.0, 0.0, 1.0);
		glRotatef(rotacao_joystick_z, 1.0, 0.0, 0.0);

		glVertexPointer(3, GL_FLOAT, 0, vertices_cubo);
		glTexCoordPointer(2, GL_FLOAT, 0, texturas_cubos);

		glPushMatrix();
			glScalef(1, 3, 1);
			glTranslatef(0, 1, 0);
			drawStick();
		glPopMatrix();

		glVertexPointer(3, GL_FLOAT, 0, vertices_cubo);
		glTexCoordPointer(2, GL_FLOAT, 0, texturas_upper_stick);
		
		glPushMatrix();
			glTranslatef(0, 4, 0);
			glTranslatef(0, 1, 0);
			glScalef(2, 1.5, 1.5);
			drawUpperStick();
		glPopMatrix();

	glPopMatrix();

	// --- bot�es ---

	glVertexPointer(3, GL_FLOAT, 0, vertices_cubo);
	glTexCoordPointer(2, GL_FLOAT, 0, texturas_botao);

	glPushMatrix();
		glTranslatef(centrox_botao1, altura_botao1, 0.0);
		glTranslatef(tam_maquina * 2, 0.01, -tam_maquina * 0.5);
		glScalef(0.03, 0.03, 0.03);
		glScalef(3, 1.5, 2);
		drawButton1();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(centrox_botao2, altura_botao2, 0.0);
		glTranslatef(tam_maquina * 2.25, 0.01, -tam_maquina * 0.75);
		glScalef(0.03, 0.03, 0.03);
		glScalef(3, 1.5, 2);
		drawButton2();
	glPopMatrix();
};

void iluminacao() {
	glLightfv(GL_LIGHT0, GL_POSITION, luz_teto_posicao);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_teto_ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_teto_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luz_teto_especular);
	if (ligaTeto)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);
}


/* ------------------------------------- 3. DISPLAY -------------------------------------- */


void display(void) {

	// --- N�o alterar --- //
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// --- VIEWPORT: Mundo --- //
	glViewport(0.3 * wScreen, 0, 0.7 * wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3.0 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

		// Observador
		gluLookAt(obsP[0] - 3, obsP[1] - 1.5, obsP[2], 0, 0, 0, 0, 1, 0);

		// Objetos
		//drawEixos();
		drawScene();


	// --- VIEWPORT: Player POV --- //
	glViewport(0.05 * wScreen, 0.05 * wScreen, 0.3 * wScreen, 0.3 * hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, (float)wScreen / hScreen, 0.5, 5.0 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

		// Observador
		gluLookAt(3.4, 1, 0, -1, 0, 0, 0, 1, 0);

		// Objetos
		
		drawScene();

	// --- Atualiza��o --- //
	glutSwapBuffers();
}

void Timer(int value)
{

	// --- animacao joystick --- //
	int rotacao = 3;
	if (start_animation_joystick) {	
		if (joystick_dir == 1){
			if (animation_joystick) rotacao_joystick_x += rotacao;
			else {
				rotacao_joystick_x -= rotacao;
				if (rotacao_joystick_x <= 0) {
					animation_joystick = true;
					start_animation_joystick = false;
				}
			}
			if (rotacao_joystick_x >= 30) animation_joystick = false;
		}		
		if (joystick_dir == 2) {
			if (animation_joystick) rotacao_joystick_x -= rotacao;
			else {
				rotacao_joystick_x += rotacao;
				if (rotacao_joystick_x >= 0) {
					animation_joystick = true;
					start_animation_joystick = false;
				}
			}
			if (rotacao_joystick_x <= -30) animation_joystick = false;
		}
		if (joystick_dir == 3) {
			if (animation_joystick) rotacao_joystick_z += rotacao;
			else {
				rotacao_joystick_z -= rotacao;
				if (rotacao_joystick_z <= 0) {
					animation_joystick = true;
					start_animation_joystick = false;
				}
			}
			if (rotacao_joystick_z >= 30) animation_joystick = false;
		}
		if (joystick_dir == 4) {
			if (animation_joystick) rotacao_joystick_z -= rotacao;
			else {
				rotacao_joystick_z += rotacao;
				if (rotacao_joystick_z >= 0) {
					animation_joystick = true;
					start_animation_joystick = false;
				}
			}
			if (rotacao_joystick_z <= -30) animation_joystick = false;
		}
	}

	// --- animacao botao 1 --- //
	if (start_animation_button1) {												// � pressionado B ; start = true, button down = false (inicialmente)
		if (animation_button_down1) altura_botao1 -= increment_y_button1;			
		else {
			altura_botao1 += increment_y_button1;									
			if (fabs(altura_botao1) <= 0) {									
				animation_button_down1 = true;								
				start_animation_button1 = false;								
			}
		}
		if (fabs(altura_botao1) >= 0.05) animation_button_down1 = false;		// chegou ao limite em baixo								
	}

	// --- animacao botao 2 --- //
	if (start_animation_button2) {												// � pressionado B ; start = true, button down = false (inicialmente)
		if (animation_button_down2) altura_botao2 -= increment_y_button2;
		else {
			altura_botao2 += increment_y_button2;
			if (fabs(altura_botao2) <= 0) {
				animation_button_down2 = true;
				start_animation_button2 = false;
			}
		}
		if (fabs(altura_botao2) >= 0.05) animation_button_down2 = false;		// chegou ao limite em baixo								
	}

	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}

void updateLuz() {
	luz_teto_ambiente[0] = luzR * intensidadeT;
	luz_teto_ambiente[1] = luzG * intensidadeT;
	luz_teto_ambiente[2] = luzB * intensidadeT;
	luz_teto_difusa[0] = luzR * intensidadeT;
	luz_teto_difusa[1] = luzG * intensidadeT;
	luz_teto_difusa[2] = luzB * intensidadeT;
	luz_teto_especular[0] = luzR * intensidadeT;
	luz_teto_especular[1] = luzG * intensidadeT;
	luz_teto_especular[2] = luzB * intensidadeT;;
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_teto_ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_teto_difusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luz_teto_especular);
}


/* ------------------------------------- 4. TECLAS --------------------------------------- */


void keyboard(unsigned char key, int x, int y) {

	switch (key) {

	// --- m�quina --- //

	case 'q': case 'Q':
		altura = altura + 0.25;
		glutPostRedisplay();
		break;

	case 'e': case 'E':
		altura = altura - 0.25;
		glutPostRedisplay();
		break;
		
	case 's': case 'S':
		centrox = centrox - 0.25;
		glutPostRedisplay();
		break;
	case 'w': case 'W':
		centrox = centrox + 0.25;
		glutPostRedisplay();
		break;

	case 'a': case 'A':
		rotacao = rotacao + 2.5;
		glutPostRedisplay();
		break;

	case 'd': case 'D':
		rotacao = rotacao - 2.5;
		glutPostRedisplay();
		break;

	case 'x': case 'X':
		rVisao = rVisao++;
		obsP[0] = rVisao * cos(aVisao);
		obsP[2] = rVisao * sin(aVisao);
		glutPostRedisplay();
		break;

	case 'y': case 'Y':
		rVisao = rVisao--;
		obsP[0] = rVisao * cos(aVisao);
		obsP[2] = rVisao * sin(aVisao);
		glutPostRedisplay();
		break;

	// --- joystick --- //

	case 'i': case 'I':
		start_animation_joystick = true;
		joystick_dir = 1;
		rotacao_joystick_x += 5;
		glutPostRedisplay();
		break;

	case 'k': case 'K':
		start_animation_joystick = true;
		joystick_dir = 2;
		rotacao_joystick_x -= 5;
		glutPostRedisplay();
		break;

	case 'j': case 'J':
		start_animation_joystick = true;
		joystick_dir = 3;
		rotacao_joystick_z += 5;
		glutPostRedisplay();
		break;
	case 'l': case 'L':
		start_animation_joystick = true;
		joystick_dir = 4;
		rotacao_joystick_z -= 5;
		glutPostRedisplay();
		break;

	// --- botoes --- // 

	case 'n': case 'N':
		start_animation_button1 = true;
		glutPostRedisplay();
		break;

	case 'm': case 'M':
		start_animation_button2 = true;
		glutPostRedisplay();
		break;

	// --- luz --- // 
	case 't': case 'T':
		ligaTeto = !ligaTeto;
		updateLuz();
		glutPostRedisplay();
		break;

	case 'g':	case 'G':
		Dia = !Dia;
		if (Dia) {
			luzGlobalCorAmb[0] = 1.0;
			luzGlobalCorAmb[1] = 1.0;
			luzGlobalCorAmb[2] = 1.0;
		}
		else {
			luzGlobalCorAmb[0] = 0.0;
			luzGlobalCorAmb[1] = 0.0;
			luzGlobalCorAmb[2] = 0.0;
		}
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
		glutPostRedisplay();
		break;

	//--- escape --- //

	case 27:
		exit(0);
		break;
	}

}

void teclasNotAscii(int key, int x, int y) {

	if (key == GLUT_KEY_UP)
		obsP[1] = (obsP[1] + 0.1);
	if (key == GLUT_KEY_DOWN)
		obsP[1] = (obsP[1] - 0.1);

	if (obsP[1] > yC)
		obsP[1] = yC;
	if (obsP[1] < -yC)
		obsP[1] = -yC;

	if (key == GLUT_KEY_LEFT)
		aVisao = (aVisao + 0.1);
	if (key == GLUT_KEY_RIGHT)
		aVisao = (aVisao - 0.1);

	obsP[0] = rVisao * cos(aVisao);
	obsP[2] = rVisao * sin(aVisao);

	glutPostRedisplay();

}


/* -------------------------------------- 5. MAIN ---------------------------------------- */


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("|Posicionar m�quina -'qweasd'|        |Joystick - 'ijkl'|        |Bot�es - 'nm'|        |Observador - 'SETAS'|        |Zoom - x/y|");

	init();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}