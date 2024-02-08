#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>


#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 500


int init(int w, int h, int argc, char *args[]);

//Definir estructuras y alias
typedef struct muro{

	int x,y,w,h;
} muro_t;

typedef struct J {

	int x,y;
	int w,h;
} J_t;

typedef struct enemigo {
	int x,y;
	int w,h;
	int dx, dy;
	int tipo;
	int dir;
	int predir;
}enemigo_t;

typedef struct bala{
	int x, y;
	int w, h;
	int dx, dy;
	int disparo;
}bala_t;

//Declarar las variables
static muro_t muro[200], muro1[200];
static J_t J[2];
static muro_t portal[200];
static bala_t bala;
static enemigo_t enemigo[30];

int sig_n = 0;
int width, height;
int valocidad = 2;
int m=0;
int tp;
int caminar=0;
int puntaje[] = {0,0,0,0,0,0,0};


//Punteros a ventana SDL
    SDL_Window *window = NULL;	
    SDL_Renderer *renderer;
    SDL_Texture *titulo;
    SDL_Texture *titulo2;
    SDL_Texture *menu = NULL;
    SDL_Texture *menu2 = NULL;
    SDL_Texture *menu3 = NULL;

 //Declaracion de variable como puntero a la superficie de dibujo
static SDL_Surface *screen;
static SDL_Surface *sig_N;
static SDL_Surface *jugador;
static SDL_Surface *Bala;
static SDL_Surface *Vidas;
static SDL_Surface *Vidas1;
static SDL_Surface *EnemigoAmarillo;
static SDL_Surface *EnemigoAzul;
static SDL_Surface *EnemigoRojo;
static SDL_Surface *EnemigoJefe;
static SDL_Surface *Numeros;
static SDL_Surface *GameO;

//Texturas
SDL_Texture *screen_texture;

  
  //Asignar los valores a las variables de las estructuras
static void creacion_muro(int n,int x, int y, int w, int h){
	muro[n].x = x;
	muro[n].y = y;
	muro[n].w = w;
	muro[n].h = h;
}

static void creacion_muro1(int n,int x, int y, int w, int h){
	muro1[n].x = x;
	muro1[n].y = y;
	muro1[n].w = w;
	muro1[n].h = h;
}

static void create_Portal(int n,int x, int y, int w, int h){
	portal[n].x = x;
	portal[n].y = y;
	portal[n].w = w;
	portal[n].h = h;
}

    
 //Limpia los muros internos del mapa
static void clean(){
	
	for (int i = 10; i < 70; ++i)
	{
		creacion_muro(i,0,0,0,0);
	}
}

static void Details(){
	//creacion de paredes exteriores
	creacion_muro(0,40,40,10,105);
	creacion_muro(1,40,195,10,145);
	creacion_muro(2,40,40,560,10);
	creacion_muro(3,40,340,560,10);
	creacion_muro(4,590,40,10,105);
	creacion_muro(5,590,195,10,145);

	//creacion del tunel parte izq
	creacion_muro(6,10,140,35,10);
	creacion_muro(7,10,190,85,10);

	//creacion del tunel parte der
	creacion_muro(8,595,140,35,10);
	creacion_muro(9,544,190,85,10);

	// creacion de pared de tunel 
	create_Portal(27,46,146,3,3);
	create_Portal(28,46,151,3,3);
	create_Portal(29,46,156,3,3);
	create_Portal(30,46,161,3,3);
	create_Portal(31,46,166,3,3);
	create_Portal(32,46,171,3,3);
	create_Portal(33,46,176,3,3);
	create_Portal(34,46,181,3,3);
	create_Portal(35,46,186,3,3);

	create_Portal(36,591,146,3,3);
	create_Portal(37,591,151,3,3);
	create_Portal(38,591,156,3,3);
	create_Portal(39,591,161,3,3);
	create_Portal(40,591,166,3,3);
	create_Portal(41,591,171,3,3);
	create_Portal(42,591,176,3,3);
	create_Portal(43,591,181,3,3);
	create_Portal(44,591,186,3,3);

		//Creacion de flechas  
	creacion_muro(45,20,165,15,5);
	creacion_muro(46,20,162,5,3);
	creacion_muro(47,22,159,5,3);
	creacion_muro(48,24,156,5,3);

	creacion_muro(49,20,168,5,3);
	creacion_muro(50,22,171,5,3);
	creacion_muro(51,24,174,5,3);

	creacion_muro(52,605,165,15,5);
	creacion_muro(53,615,162,5,3);
	creacion_muro(54,613,159,5,3);
	creacion_muro(55,611,156,5,3);

	creacion_muro(56,615,168,5,3);
	creacion_muro(57,613,171,5,3);
	creacion_muro(58,611,174,5,3);

	//creacion de cuadros del puntaje 
	
	creacion_muro1(76,10,390,115,15);
	creacion_muro1(77,10,390,15,85);
	creacion_muro1(78,10,460,115,15);
	creacion_muro1(79,110,390,15,85);

	creacion_muro1(80,410,390,215,15);
	creacion_muro1(81,410,390,15,85);
	creacion_muro1(82,410,460,215,15);
	creacion_muro1(83,615,390,15,85);
}

static void mapa_1(){
	SDL_SetWindowTitle(window, "Mapa 1");
	clean();
	//creacion de paredes dentro de mapa
	creacion_muro(10,445,90,100,10);

	creacion_muro(11,490,145,10,100);
	creacion_muro(12,395,140,100,10);

	creacion_muro(13,540,245,10,50);

	creacion_muro(14,240,50,10,45);
	creacion_muro(15,390,50,10,45);

	creacion_muro(16,290,95,10,50);
	creacion_muro(17,340,95,10,50);

	creacion_muro(18,245,190,50,10);
	creacion_muro(19,340,190,50,10);

	creacion_muro(20,245,240,145,10);

	creacion_muro(21,245,290,50,10);
	creacion_muro(22,340,290,50,10);

	creacion_muro(23,190,295,10,50);
	creacion_muro(24,440,295,10,50);

	creacion_muro(25,190,195,10,50);
	creacion_muro(26,440,195,10,50);
	creacion_muro(27,90,95,10,50);
	creacion_muro(28,95,90,100,10);

	creacion_muro(29,140,145,10,100);
	creacion_muro(30,145,140,100,10);

	creacion_muro(31,90,245,10,50);

	creacion_muro(32,540,95,10,50);
}

static void mapa_2(){
	clean();
	creacion_muro(10,295,90,50,10);
	creacion_muro(11,395,90,50,10);
	creacion_muro(12,195,140,50,10);
	creacion_muro(13,295,140,50,10);
	creacion_muro(14,395,140,50,10);
	creacion_muro(15,245,190,50,10);
	creacion_muro(16,345,190,50,10);

	creacion_muro(17,240,145,10,100);
	creacion_muro(18,390,145,10,100);

	creacion_muro(19,295,240,50,10);

	creacion_muro(20,190,295,10,50);
	creacion_muro(21,440,295,10,50);

	creacion_muro(22,490,50,10,45);
	creacion_muro(23,490,145,10,100);
	creacion_muro(24,445,240,50,10);

	creacion_muro(25,540,95,10,50);
	creacion_muro(26,540,245,10,50);

	creacion_muro(27,245,290,50,10);
	creacion_muro(28,345,290,50,10);

	creacion_muro(29,90,95,10,50);
	creacion_muro(30,90,245,10,50);
	creacion_muro(31,140,50,10,45);
	creacion_muro(32,140,145,10,100);
	creacion_muro(33,145,240,50,10);

	creacion_muro(34,195,90,50,10);
}

//Funcion random
int randint(int a, int b){

	return a + rand() % (b - a + 1);
}

int caminar_random(int a, int b,int c,int d, int t){
	if ((t==a) || (t==b) || (t==c) || (t==d)){return caminar_random(a,b,c,d,randint(1,4));}
	return t;
}

int enemigo_random_azul(int number){
	for (int i = 1; i < number+1; ++i)
	{
		int r1 = randint(0,10);
		int r2 = randint(0,5);
		if ((r1 == 0 || r1 == 1) && (r2 == 0 || r2 == 1)){
			i = i - 1;
		}else{
			enemigo[i].x = 55+(50*r1);
			enemigo[i].y = 55+(50*r2);
			enemigo[i].w = 30;
			enemigo[i].h = 30;
			enemigo[i].dy = 0;
			enemigo[i].dx = 0;
			enemigo[i].tipo = 1;

		}
	}
}

int enemigo_random_amarillo(int number){
	for (int i = 10; i < number+10; ++i)
	{
		int r1 = randint(0,10);
		int r2 = randint(0,5);
		
		if ((r1 == 0 || r1 == 1) && (r2 == 0 || r2 == 1)){
			i = i - 1;
		}else{
		//Generar aparicion random
			enemigo[i].x = 55 +(50*r1);//x max 500
			enemigo[i].y = 55 +(50*r2);//y max 250
			enemigo[i].w = 30;
			enemigo[i].h = 30;
			enemigo[i].dy = 0;
			enemigo[i].dx = 0;
			enemigo[i].tipo = 2;
		}
	}
}

static void nivel_1(){
	 SDL_SetWindowTitle(window, "Nivel 1");
	 
	  tp=0;
	for (int i = 0; i < 25; ++i)
	{
		enemigo[i].x=0;
		enemigo[i].y=0;
		enemigo[i].h=0;
		enemigo[i].w=0;
	}
	
	 mapa_1();
	 enemigo_random_amarillo(2);
	 enemigo_random_azul(5);
	
	//Reestablecer puntaje
	for (int i = 0; i < 7; ++i){
		puntaje[i]=0;
	}
	
}

static void nivel_2(){
	tp=0;
	mapa_2();
	enemigo_random_amarillo(2);
	enemigo_random_azul(0);
}



static void init_game() {

	J[1].x = 55;
	J[1].y = 55;
	J[1].w = 30;
	J[1].h = 30;
	Details();
	nivel_1();
	
}

//Reiniciar cuando el jugador muere
static void reiniciar_nivel(){
	for (int i = 0; i < 25; ++i)
	{
		if ((enemigo[i].h >1) && (enemigo[i].w >1))
		{
			int r1 = randint(0,10);
			int r2 = randint(0,5);
			if ((r1 == 0 || r1 == 1) && (r2 == 0 || r2 == 1)){
				i = i - 1;
			}else{
				enemigo[i].x = 55+(50*r1);
				enemigo[i].y = 55+(50*r2);
				enemigo[i].dy = 0;
				enemigo[i].dx = 0;
			}
		}
	}
	J[1].x = 55;
	J[1].y = 55;
}


int colision_jugador_muro(J_t a, muro_t b) {

	int izquierda_a, izquierda_b;
	int derecha_a, derecha_b;
	int arriba_a, arriba_b;
	int abajo_a, abajo_b;

	izquierda_a = a.x;
	derecha_a = a.x + a.w;
	arriba_a = a.y;
	abajo_a = a.y + a.h;

	izquierda_b = b.x;
	derecha_b = b.x + b.w;
	arriba_b = b.y;
	abajo_b = b.y + b.h;
	
	if (izquierda_a > derecha_b) {
		return 0;
	}

	if (derecha_a < izquierda_b) {
		return 0;
	}

	if (arriba_a > abajo_b) {
		return 0;
	}

	if (abajo_a < arriba_b) {
		return 0;
	}

	if ((abajo_a > arriba_b) && (derecha_a > izquierda_b) && (izquierda_a < derecha_b) && (arriba_a < abajo_b)){
		return 1;
	}

	
}

//indica el tipo de colisión que se ha producido (1 para colisión horizontal, 2 para colisión vertical, y 3 si no hay colisión)
int colision_enemigo_muro(enemigo_t a, muro_t b) {

	int izquierda_a, izquierda_b;
	int derecha_a, derecha_b;
	int arriba_a, arriba_b;
	int abajo_a, abajo_b;

	izquierda_a = a.x;
	derecha_a = a.x + a.w;
	arriba_a = a.y;
	abajo_a = a.y + a.h;

	izquierda_b = b.x;
	derecha_b = b.x + b.w;
	arriba_b = b.y;
	abajo_b = b.y + b.h;
	
	if (izquierda_a > derecha_b) {
		return 0;
	}

	if (derecha_a < izquierda_b) {
		return 0;
	}

	if (arriba_a > abajo_b) {
		return 0;
	}

	if (abajo_a < arriba_b) {
		return 0;
	}
	
		return 1;
	

}


int colision_bala_muro(bala_t a, muro_t b) {

	int izquierda_a, izquierda_b;
	int derecha_a, derecha_b;
	int arriba_a, arriba_b;
	int abajo_a, abajo_b;

	izquierda_a = a.x;
	derecha_a = a.x + a.w;
	arriba_a = a.y;
	abajo_a = a.y + a.h;

	izquierda_b = b.x;
	derecha_b = b.x + b.w;
	arriba_b = b.y;
	abajo_b = b.y + b.h;
	
	if (izquierda_a > derecha_b) {
		return 0;
	}

	if (derecha_a < izquierda_b) {
		return 0;
	}

	if (arriba_a > abajo_b) {
		return 0;
	}

	if (abajo_a < arriba_b) {
		return 0;
	}

	if ((abajo_a > arriba_b) && (derecha_a > izquierda_b) && (izquierda_a < derecha_b) &&  (arriba_a < abajo_b)) {
		return 1;
	}
}

int colision_bala_enemigo(bala_t a, enemigo_t b) {

	int izquierda_a, izquierda_b;
	int derecha_a, derecha_b;
	int arriba_a, arriba_b;
	int abajo_a, abajo_b;

	izquierda_a = a.x;
	derecha_a = a.x + a.w;
	arriba_a = a.y;
	abajo_a = a.y + a.h;

	izquierda_b = b.x;
	derecha_b = b.x + b.w;
	arriba_b = b.y;
	abajo_b = b.y + b.h;
	
	if (izquierda_a > derecha_b) {
		return 0;
	}

	if (derecha_a < izquierda_b) {
		return 0;
	}

	if (arriba_a > abajo_b) {
		return 0;
	}

	if (abajo_a < arriba_b) {
		return 0;
	}
	return 1;

}

int colision_jugador_enemigo(enemigo_t a, J_t b) {
	int izquierda_a, izquierda_b;
	int derecha_a, derecha_b;
	int arriba_a, arriba_b;
	int abajo_a, abajo_b;

	izquierda_a = a.x;
	derecha_a = a.x + a.w;
	arriba_a = a.y;
	abajo_a = a.y + a.h;

	izquierda_b = b.x;
	derecha_b = b.x + b.w;
	arriba_b = b.y;
	abajo_b = b.y + b.h;
	
	if (izquierda_a > derecha_b) {
		return 0;
	}

	if (derecha_a < izquierda_b) {
		return 0;
	}

	if (arriba_a > abajo_b) {
		return 0;
	}

	if (abajo_a < arriba_b) {
		return 0;
	}

	return 1;
}

static void mover_bala(int dir) {
	if ((bala.w > 1) && (bala.h > 1)){
		if (bala.disparo == 0){ //Esperar a que la bala desaparezca
			bala.disparo = 1;
			if (dir == 4){
				bala.dy = 10;
			}
			if (dir == 1){
				bala.dy = -10;
			}
			if (dir == 3){
				bala.dx = 10;
			}
			if (dir == 2){
				bala.dx = -10;
			}
		}
		bala.x += bala.dx;
		bala.y += bala.dy;
		
		//Recorrer arreglo y detectar colision
		for (int i = 0; i < 100; ++i){
			
			if ((colision_bala_muro(bala, muro[i]) != 0) || (colision_bala_muro(bala, portal[i]) != 0)){
				//restablecer(eliminar bala)
				bala.dy = 0;
				bala.dx = 0;
				bala.w = 0;
				bala.h = 0;
				bala.disparo = 0;
			}
		}
		for (int b = 0; b < 25; ++b){
			//check for collision with the enemigo
			if (colision_bala_enemigo(bala, enemigo[b]) != 0) {
				if ((enemigo[b].w > 1) && (enemigo[b].h > 1))
				{
					enemigo[b].x = 0;
					enemigo[b].y = 0;
					enemigo[b].w = 0;
					enemigo[b].h = 0;
					enemigo[b].dy = 0;
					enemigo[b].dx = 0;

					bala.dy = 0;
					bala.dx = 0;
					bala.w = 0;
					bala.h = 0;
					bala.x = 0;
					bala.y = 0;

					bala.disparo = 0;
					puntaje[5] += 1;
					puntaje[1] += enemigo[b].tipo;
				}
			}
		}
	}
}

// Recibe el parametro de dirección
static void mover_jugador(int d) {
			
	// W moverse hacia arriba
	if (d == 0) {
		J[1].y -= valocidad;
		
		for (int i = 0; i < 2; ++i){
			for (int b = 0; b < 100; ++b){
				if(colision_jugador_muro(J[1],muro[b]) != 0) {
					J[1].y = muro[b].y + (muro[b].h+1);
				}
			}
		}
	}
	
	// A moverse a la izquierda
	if (d == 1) {
		J[1].x -= valocidad;
		
		for (int i = 0; i < 2; ++i){
			for (int b = 0; b < 100; ++b){
				if(colision_jugador_muro(J[1],muro[b]) != 0) {
					J[1].x = muro[b].x + (muro[b].w+1);
	}
if(colision_jugador_muro(J[1],portal[b]) != 0) {
					J[1].x = 590 - (J[1].w+1);
	}
			}
		}
	}

	// D moverse a la derecha
	if (d == 2) {
		J[1].x += valocidad;
		
		for (int i = 0; i < 2; ++i){
			for (int b = 0; b < 100; ++b){
				if(colision_jugador_muro(J[1],muro[b]) != 0) {
					J[1].x = muro[b].x - (J[1].w+1);
	}
if(colision_jugador_muro(J[1],portal[b]) != 0) {
					J[1].x = 55;
	}
			}
		}
		
	}	
	
	// S mmoverse hacia abajo
	if (d == 3) {
		J[1].y += valocidad;
		
		for (int i = 0; i < 2; ++i){
			for (int b = 0; b < 100; ++b){
				if(colision_jugador_muro(J[1],muro[b]) != 0) {
					J[1].y = muro[b].y - (J[1].h+1);
				}
			}
		}
	}
}

//indica la dirección de la colisión. Por ende la direccion en la que se puede mover
int movimiento_enemigo_muro(enemigo_t a, muro_t b) {
	int izquierda_a, izquierda_b;
	int derecha_a, derecha_b;
	int arriba_a, arriba_b;
	int abajo_a, abajo_b;

	izquierda_a = a.x;
	derecha_a = a.x + a.w;
	arriba_a = a.y;
	abajo_a = a.y + a.h;

	izquierda_b = b.x;
	derecha_b = b.x + b.w;
	arriba_b = b.y;
	abajo_b = b.y + b.h;

	if (((arriba_a) < abajo_b) && ((arriba_a-7) > arriba_b) && ((derecha_a -2) > izquierda_b) && ((izquierda_a +2) < derecha_b)){
		return 1;
	}
	if (((abajo_a+7) > arriba_b) && ((abajo_a+7) < abajo_b) && ((derecha_a -2) > izquierda_b) && ((izquierda_a +2) < derecha_b)){
		return 2;
	}
	if (((izquierda_a-7) < derecha_b) && ((izquierda_a-7) > izquierda_b) && ((arriba_a +2) < abajo_b) && ((abajo_a -2)> arriba_b)){
		return 3;
	}
	if (((derecha_a+7) > izquierda_b) && ((derecha_a+7) < derecha_b) && ((arriba_a +2) < abajo_b) && ((abajo_a -2) > arriba_b)){
		return 4;
	}
	return 5;
}

//controlar el movimiento de los enemigos en un juego
static void mover_enemigo() {
	caminar=caminar+1;
	tp = tp + 1;
	int t = 0;
	//Recorrer arreglo de enemigo y muros
	for (int b = 0; b < 25; ++b){
		
		for (int i = 0; i < 100; ++i){

			//detectar colision
			if (colision_enemigo_muro(enemigo[b], muro[i]) != 0 ){
				//cambiar direccion
				enemigo[b].dx = -enemigo[b].dx;
				enemigo[b].dy = -enemigo[b].dy;
			}
			if( colision_enemigo_muro(enemigo[b], portal[i]) != 0){
				enemigo[b].x=0;
				enemigo[b].y=0;
				enemigo[b].dx=0;
				enemigo[b].dy=0;
				enemigo[b].w = 0;
				enemigo[b].h = 0;
			}

		}
		
		//Verificar colision y cargar opcion de movimiento
		int arriba = 0 ;
		int abajo = 0 ;
		int derecha  = 0 ;
		int izquierda  = 0 ;
		for (int i = 0; i < 100; ++i){
			int n = movimiento_enemigo_muro(enemigo[b],muro[i]);
			
			if (n==1){arriba=1;}
			if (n==2){abajo=2;}
			if (n==3){derecha =3;}
			if (n==4){izquierda =4;}
		}
		// Recorre arreglo para enemigos tipo 1 e inicializa direcion
		if ((caminar==50) && (b < 10)){
			enemigo[b].dx = 0;
			enemigo[b].dy = 0;
			//Escoger de manera random la direccion
			t = (caminar_random(arriba,abajo,derecha ,izquierda ,randint(1,4)));
			if ((enemigo[b].w > 1) && (enemigo[b].h > 1))
			{
				if (t == 1){
					enemigo[b].dy = -1;
					enemigo[b].dir = 2;
				}
				if (t == 2){
					enemigo[b].dy = 1;
					enemigo[b].dir = 4;
				}
				if (t == 3){
					enemigo[b].dx = -1;
					enemigo[b].dir = 5;
					enemigo[b].predir = 1;
				}
				if (t == 4){
					enemigo[b].dx = 1;	
					enemigo[b].dir = 10;
					enemigo[b].predir = 2;
				}
			}
		}
		if (((caminar==15) || (caminar==30) || (caminar==50 )) && (9<b<14)){
			enemigo[b].dx = 0;
			enemigo[b].dy = 0;
			
			int arriba = 0 ;
			int abajo = 0 ;
			int derecha  = 0 ;
			int izquierda  = 0 ;
			for (int i = 0; i < 100; ++i){
				int n = movimiento_enemigo_muro(enemigo[b],muro[i]);
					
				if (n==1){arriba=1;}
				if (n==2){abajo=2;}
				if (n==3){derecha =3;}
				if (n==4){izquierda =4;}
			}
			t = (caminar_random(arriba,abajo,derecha ,izquierda ,randint(1,4)));
			
			if ((enemigo[b].w > 1) && (enemigo[b].h > 1)){
				if (t == 1){
					enemigo[b].dy = -2;
					enemigo[b].dir = 2;
				}
				if (t == 2){
					enemigo[b].dy = 2;
					enemigo[b].dir = 4;
				}
				if (t == 3){
					enemigo[b].dx = -2;
					enemigo[b].dir = 5;
					enemigo[b].predir = 1;
				}
				if (t == 4){
					enemigo[b].dx = 2;
					enemigo[b].dir = 10;
					enemigo[b].predir = 2;
				}
			}
		}
		
		enemigo[b].x += enemigo[b].dx;
		enemigo[b].y += enemigo[b].dy;
		
		for (int i = 0; i < 2; i++) {	
			if (colision_jugador_enemigo(enemigo[b], J[i]) !=0) {
				if ((enemigo[b].w > 1) && (enemigo[b].h > 1) ){
					puntaje[0] += 1;
					reiniciar_nivel();
					
				}
			}
		}
		
			
	}
	
	if(caminar==50){caminar=0;}
}



static void dibujar_menu(){
	 
	if(m==0){
	 // Render first image
    SDL_SetWindowTitle(window, "Wizard of Wor");
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, titulo, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    
    m=1;
	}
    SDL_SetWindowTitle(window, "Wizard of Wor");
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, titulo2, NULL, NULL);
    SDL_RenderPresent(renderer);
}

static void dibujar_menu2(){
	SDL_SetWindowTitle(window, "Inicio");
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, menu, NULL, NULL);
	SDL_RenderPresent(renderer);
	
	SDL_Delay(3000);
	
	SDL_SetWindowTitle(window, "Inicio");
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, menu2, NULL, NULL);
	SDL_RenderPresent(renderer);
	
	SDL_Delay(2000);
	
	SDL_SetWindowTitle(window, "Inicio");
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, menu3, NULL, NULL);
	SDL_RenderPresent(renderer);
	
	SDL_Delay(2000);
	
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
	
	SDL_RenderPresent(renderer);
	
}

static void dibujar_vidas() {
	
	SDL_Rect src, src2;
	SDL_Rect dest, dest2;

	src.x = 384;
	src.y = 179;
	src.w = 30;
	src.h = 90;

	dest.x = 2; 
	dest.y = 50;
	dest.w = 30;
	dest.h = 90;

	if (puntaje[0] > 0 && puntaje[0] < 3) {
		
		src.y += src.h * puntaje[0];
	}
	
	SDL_BlitSurface(Vidas, &src, screen, &dest);
	
	src2.x = 369;
	src2.y = 147;
	src2.w = 70;
	src2.h = 20;

	dest2.x = 2; 
	dest2.y = 10;
	dest2.w = 80;
	dest2.h = 25;
	
	SDL_BlitSurface(Vidas1, &src2, screen, &dest2);
}

//cero				560,400
//cero				525,400
//puntaje[0]: vidas
//puntaje[1]: puntaje, +1([2]) 	490,400
//puntaje[2]: mil, +1([3])	455,400
//puntaje[3]: diez mil		420,400
//puntaje[4]: viidas
//puntaje[5]: muertes, +1([6])	 55,400
//puntaje[6]: decenas 		20,400


int contar_puntaje() {
	
	int cuenta = 0;

	if (puntaje[0] == 3){ //vidas
		init_game();
		return 1;	
	}
	
	//Revisar que queden enemigos en el mapa
	for (int i = 0; i < 25; ++i){
		if ((enemigo[i].h > 1) && (enemigo[i].w > 1))
		{
			cuenta+=1;
		}
	}
	if (cuenta == 0){
		
		return 2;
	}
	
	return 0;
}

static void dibujar_contador_diez_mil() {
	
	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0;
	src.y = 0;
	src.w = 54;
	src.h = 54;

	dest.x = 420;
	dest.y = 400;
	dest.w = 54;
	dest.h = 54;
	
	if (puntaje[3] > 0 && puntaje[3] < 10) {
		
		src.x += src.w * puntaje[3];
	}

	SDL_BlitSurface(Numeros, &src, screen, &dest);
}

static void dibujar_contador_mil() {
	
	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0;
	src.y = 0;
	src.w = 54;
	src.h = 54;

	dest.x = 455;
	dest.y = 400;
	dest.w = 54;
	dest.h = 54;
	
	if (puntaje[2] >= 0 && puntaje[2] < 10) {
		
		src.x += src.w * puntaje[2];
	}else{
		puntaje[2] = puntaje[2]-10;
		puntaje[3] +=1;
	}
	dibujar_contador_diez_mil();
	SDL_BlitSurface(Numeros, &src, screen, &dest);
}

static void dibujar_cero() {
	
	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0;
	src.y = 0;
	src.w = 54;
	src.h = 54;

	dest.x = 560;
	dest.y = 400;
	dest.w = 54;
	dest.h = 54;
	SDL_BlitSurface(Numeros, &src, screen, &dest);
	dest.x = 525;
	SDL_BlitSurface(Numeros, &src, screen, &dest);
}

static void dibujar_puntaje() {
	
	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0;
	src.y = 0;
	src.w = 52;
	src.h = 52;

	dest.x = 490;
	dest.y = 400;
	dest.w = 52;
	dest.h = 52;
	
	if (puntaje[1] >= 0 && puntaje[1] < 10) {
		
		src.x += src.w * puntaje[1];
	}else{
		puntaje[1] = puntaje[1]-10 ;
		puntaje[2] +=1;
	}
	dibujar_contador_mil();
	dibujar_cero();
	SDL_BlitSurface(Numeros, &src, screen, &dest);
}

static void dibujar_contador_decenas() {
	
	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0;
	src.y = 0;
	src.w = 54;
	src.h = 54;

	dest.x = 20;
	dest.y = 400;
	dest.w = 54;
	dest.h = 54;
	
	if (puntaje[6] > 0 && puntaje[6] < 10) {
		
		src.x += src.w * puntaje[6];
	}

	SDL_BlitSurface(Numeros, &src, screen, &dest);
}

static void dibujar_contador_muertes() {
	
	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0;
	src.y = 0;
	src.w = 52;
	src.h = 52;

	dest.x = 55;
	dest.y = 400;
	dest.w = 52;
	dest.h = 52;
	
	if (puntaje[5] >= 0 && puntaje[5] < 10) {
		
		src.x += src.w * puntaje[5];
	}else{
		puntaje[5] = puntaje[5]-10 ;
		puntaje[6] +=1;
	}
	dibujar_contador_decenas();
	SDL_BlitSurface(Numeros, &src, screen, &dest);
}

static void dibujar_J(int dir, int predir) {

	SDL_Rect src;
	SDL_Rect dest;

	dest.x = 291;
	dest.y = 205;
	dest.w = 30;
	dest.h = 30;

	
		src.x = J[1].x;
		src.y = J[1].y;
		src.w = J[1].w;
		src.h = J[1].h;
		if (dir == 1 ){
			if(predir == 1 ){
			dest.x = 410;
			}else if(predir == 2 ){
			dest.x = 320;
			}
		}
		
		if (dir == 2){
			dest.x = 440;
		}
		if (dir == 3){
			dest.x = 290;
		}
		if ( dir ==4 ){
			if(predir == 1){
			dest.x = 380;
			}else if(predir == 2 ){
			dest.x = 350;
			}
		}
		
		if ((J[1].w > 1) && (J[1].h)){
			SDL_BlitSurface(jugador, &dest, screen, &src);
		}
	
}


static void dibujar_muro() {
 
 //Reepresentar los rectangulos en ventana
	SDL_Rect wally;
	SDL_Rect wally1;
	SDL_Rect porty;

	for (int i = 0; i < 200; ++i){

		wally.x = muro[i].x;
		wally.y = muro[i].y;
		wally.w = muro[i].w;
		wally.h = muro[i].h;
		
		wally1.x = muro1[i].x;
		wally1.y = muro1[i].y;
		wally1.w = muro1[i].w;
		wally1.h = muro1[i].h;

		porty.x = portal[i].x;
		porty.y = portal[i].y;
		porty.w = portal[i].w;
		porty.h = portal[i].h;

		int r = SDL_FillRect(screen, &wally, 0xff410761);
		int r1 = SDL_FillRect(screen, &wally1, 0xffd5c8db);
		int p = SDL_FillRect(screen, &porty, 0xff0000ff);
		//draw the muro
		if (r != 0) { 
		
			printf("fill rectangle faliled in func draw_wall()");
		}
	}
}

static void dibujar_bala(int dir) {
	SDL_Rect src;
	SDL_Rect dest;

	dest.y = 0;

	src.x = bala.x;
	src.y = bala.y;
	src.w = bala.w;
	src.h = bala.h;
	if (dir == 2){
		dest.x = 24;//24
		dest.w = 10;
		dest.h = 7;
	}
	if (dir == 3){
		dest.x = 7;//7
		dest.w = 10;
		dest.h = 7;
	}
	if (dir == 1){
		dest.x = 0;//0
		dest.w = 7;
		dest.h = 10;
	}
	if ( dir ==4){
		dest.x = 17;//17
		dest.w = 7;
		dest.h = 10;
	}
	if ((bala.w>1) && (bala.h >1))
	{
		SDL_BlitSurface(Bala, &dest, screen, &src);
	}
}

static void dibujar_enemigo() {
	
	SDL_Rect src;
	SDL_Rect dest;

	int r = 0;
	for (int i = 0; i < 25; ++i){
		if ((enemigo[i].w > 1) && (enemigo[i].h > 1)){
			dest.x = enemigo[i].x;
			dest.y = enemigo[i].y;
			dest.w = enemigo[i].w;
			dest.h = enemigo[i].h;
			
			if (enemigo[i].dir == 2){
				if (enemigo[i].predir==2){
					src.x = 414;
					src.y = 209;
					src.w = 30;
					src.h = 30;
				}else{
					src.x = 414;
					src.y = 239;
					src.w = 30;
					src.h = 30;
				}
			}
			if (enemigo[i].dir == 4){
				if (enemigo[i].predir==2){
					src.x = 444;
					src.y = 209;
					src.w = 30;
					src.h = 30;
				}else{
					src.x = 444;
					src.y = 239;
					src.w = 30;
					src.h = 30;
				}
			}
			if (enemigo[i].dir == 5){
				
					src.x = 384;
					src.y = 239;
					src.w = 30;
					src.h = 30;
			}
			if (enemigo[i].dir == 10){
				
					src.x = 384;
					src.y = 209;
					src.w = 30;
					src.h = 30;
			}
			
			
			if ((i >0) && (i < 10)){
				SDL_BlitSurface(EnemigoAzul, &src, screen, &dest);
			}
			if ((i > 9) && (i < 14 )){
				SDL_BlitSurface(EnemigoAmarillo, &src, screen, &dest);
			}
			
			/*if ((i < 5 )){
				if ((caminar==25) || (caminar==50 )){
					Banish[i] = randint(0,1);
				}
				if (Banish[i] == 0){
					SDL_BlitSurface(enemigoRed, &src, screen, &dest);

				}else{
					r = SDL_FillRect(screen , &src, 0x00000000);
				}
			}*/
			
			/*if (i == 22 ){
				if (enemigo[i].dir == 10){
					src.x = 0;
				}else{
					src.x = 30;
				}
				SDL_BlitSurface(enemigoBoss, &src, screen, &dest);
			}
			if (i == 24 ){
				SDL_BlitSurface(enemigoBonus, &src, screen, &dest);
			}
			if (r !=0){
				printf("fill rectangle faliled in func drawenemigo()");
			}*/
		}
	}
}


static void dibujar_game_over() { 

	
	SDL_Rect src;
	SDL_Rect dest;
	
	src.x = 0;
	src.y = 0;

	dest.x = 700;
	dest.y = 500;
		
		
	SDL_RenderClear(renderer);
	
	SDL_BlitSurface(GameO, &src, screen, &dest);
	SDL_RenderPresent(renderer);	
}


static void dibujar_niveles() { 

	SDL_Rect src;
	SDL_Rect dest;

	src.x = 0;
	src.y = 0;

	dest.x = 0;
	dest.y = 0;

	switch (sig_n) {
	
		case 0:		
			src.w = sig_N->w;
			src.h = sig_N->h;
			dest.w = sig_N->w;
			dest.h = sig_N->h;	
			SDL_BlitSurface(sig_N, &src, screen, &dest);
			break;
		case 1:
			src.w = sig_N->w;
			src.h = sig_N->h;
			dest.w = sig_N->w;
			dest.h = sig_N->h;
			SDL_BlitSurface(sig_N, &src, screen, &dest);
			break;

	}	
}



static void siguiente_nivel(){
	sig_n = sig_n + 1;
	if(sig_n == 1){
		nivel_1();
	}
	if(sig_n == 2){
		nivel_2();
		
	}
	if(sig_n == 3){
		//mision completada
	}
	
}


int main(int argc, char* args[]) {
	

	//confirmar inicializacion
	if (init(SCREEN_WIDTH, SCREEN_HEIGHT, argc, args) == 1) {
		
		return 0;
	}

	//Obtener el tamaño actual de las dimenciones de la ventana
	SDL_GetWindowSize(window, &width, &height);
   
    SDL_Event e;	
    int exit = 0;
    int estado = 0;
    int sleep=0;
    Uint32 next_game_tick = SDL_GetTicks();
    int dir=0;
    int predir=0;
    int r =0;
   
   
    init_game();
  
while (exit==0){

	 SDL_PumpEvents();
	 const Uint8 *keystate=SDL_GetKeyboardState(NULL);

	
	if (keystate[SDL_SCANCODE_ESCAPE]){
	  	exit=1;
	}
	
	
	if(keystate[SDL_SCANCODE_W]){
		mover_jugador(0);
		
		dir=1;
	}
	if(keystate[SDL_SCANCODE_A]){
		mover_jugador(1);
		predir=1;
		dir=2;
	}
	if(keystate[SDL_SCANCODE_D]){
		mover_jugador(2);
		predir=2;
		dir=3;
	}
	if(keystate[SDL_SCANCODE_S]){
		mover_jugador(3);
		
		dir=4;
	}
	
	if (keystate[SDL_SCANCODE_SPACE]) {
			

			if ((bala.disparo==0) && (dir != 0))
			{	
				if(dir==1){
					if(predir==2){
					bala.x = J[1].x+10;
					bala.y = J[1].y+0;
					bala.w = 6;
					bala.h = 6;
					}
					else if(predir==1){
					bala.x = J[1].x+12;
					bala.y = J[1].y+0;
					bala.w = 6;
					bala.h = 6;
					}
				}
				if(dir==4){
					if(predir==2){
					bala.x = J[1].x+4;
					bala.y = J[1].y+30;
					bala.w = 6;
					bala.h = 6;
					}
					else if(predir==1){
					bala.x = J[1].x+20;
					bala.y = J[1].y+30 ;
					bala.w = 6;
					bala.h = 6;
					}
				}
				if (dir==2){
				bala.x = J[1].x+11;
				bala.y = J[1].y+11;
				bala.w = 6;
				bala.h = 6;
				}
				if (dir==3){
				bala.x = J[1].x+11;
				bala.y = J[1].y+11;
				bala.w = 6;
				bala.h = 6;
				}
				
			}
			
		}
		
	
	 //Refrescar pantalla
	 SDL_RenderClear(renderer);
	 SDL_FillRect(screen, NULL, 0x000000ff);
	
		 
	//display main menu
	if (estado == 0 ) {
		
			if (keystate[SDL_SCANCODE_SPACE]) {
				
				dibujar_menu2();
				siguiente_nivel();
				estado = 1;

				if (sig_n >3){
					sig_n=0;
				}
			}
			if (sig_n==0){
				dibujar_menu();

			}else{
				dibujar_niveles();
			}
	}	
	
	else if(estado==1){
	
	//chaquear puntaje
			r = contar_puntaje();
		
			//Reiniciar puntajes
			if (r == 1) {
				puntaje[0] = 0;
				puntaje[1] = 0;
				puntaje[2] = 0;
				puntaje[3] = 0;
				puntaje[4] = 0;
				sig_n =0;
				estado = 2;	

			} else if (r == 2) {
			
				estado = 2;	
			}
	
		dibujar_muro();
		dibujar_J(dir, predir);
		dibujar_bala(dir);
		mover_bala(dir);
		dibujar_vidas();
		dibujar_enemigo();
		mover_enemigo();
		dibujar_puntaje();
		dibujar_contador_muertes();
		
	}
	
	else if (estado==2){
		if (keystate[SDL_SCANCODE_SPACE]) {
				estado = 0;
				SDL_Delay(500);
		}
		if (r == 1) {
				dibujar_game_over();

			} else { 
				dibujar_niveles();
			}
	}
	
	
	SDL_UpdateTexture(screen_texture, NULL, screen->pixels, screen->w * sizeof (Uint32));
	SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
	
	//display
		SDL_RenderPresent(renderer);
		
		//Actualizar el estado del juego
		next_game_tick += 1000 / 60;
		sleep = next_game_tick - SDL_GetTicks();
	
		if( sleep >= 0 ) {
            				
			SDL_Delay(sleep);
		}
 
}		
	  
	//Liberar la memoria asignada a las imagenes
	
	SDL_FreeSurface(screen);
	SDL_FreeSurface(jugador);
	SDL_FreeSurface(sig_N);
	SDL_FreeSurface(Bala);
	SDL_FreeSurface(Vidas);
	SDL_FreeSurface(Vidas1);
	SDL_FreeSurface(EnemigoAmarillo);
	SDL_FreeSurface(EnemigoAzul);
	SDL_FreeSurface(EnemigoRojo);
	SDL_FreeSurface(EnemigoJefe);
	SDL_FreeSurface(Numeros);
	SDL_FreeSurface(GameO);

 //Limpiar
    
    SDL_DestroyTexture(titulo);
    SDL_DestroyTexture(titulo2);
    SDL_DestroyTexture(menu);
    SDL_DestroyTexture(menu2);
    SDL_DestroyTexture(menu3);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

int init(int width, int height, int argc, char *args[]) {

		 SDL_Init(SDL_INIT_VIDEO);		// Inicialización de SDL
    IMG_Init(IMG_INIT_PNG);		// Inicialización de SDL_image para cargar imágenes

	//Crear ventana SDL, inicializar window y redender
			SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer);
		
	
	//Crear la superficie screen en la que se va a trabajar
	screen = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
	
	
	//Crear la textura para renderizar
	screen_texture = SDL_CreateTextureFromSurface(renderer, screen);

	
		// Carga de textura
	titulo = IMG_LoadTexture(renderer, "titulo.bmp");
	titulo2 = IMG_LoadTexture(renderer, "titulo2_2.bmp");
    	menu = IMG_LoadTexture(renderer, "menu.bmp");
     	menu2 = IMG_LoadTexture(renderer, "getready.bmp");
      	menu3 = IMG_LoadTexture(renderer, "go.bmp");
	jugador = SDL_LoadBMP("player1.bmp");
	Bala = SDL_LoadBMP("Bala.bmp");
	Vidas = SDL_LoadBMP("vidas.bmp");
	Vidas1 = SDL_LoadBMP("vidas1.bmp");
	EnemigoAmarillo = SDL_LoadBMP("enemigo11.bmp");
	EnemigoAzul = SDL_LoadBMP("enemigo22.bmp");
	EnemigoRojo = SDL_LoadBMP("enemigo3.bmp");
	EnemigoJefe = SDL_LoadBMP("enemigo4.bmp");
	Numeros = SDL_LoadBMP("numeros.bmp");
	sig_N = SDL_LoadBMP("nextlevel.bmp");
	GameO = SDL_LoadBMP("gameover.bmp");
	
	
	Uint32 colorkey = SDL_MapRGB(screen->format, 255, 0, 255);

	SDL_SetColorKey(jugador, SDL_TRUE, colorkey);
	SDL_SetColorKey(Bala, SDL_TRUE, colorkey);
	SDL_SetColorKey(Vidas, SDL_TRUE, colorkey);
	SDL_SetColorKey(Vidas1, SDL_TRUE, colorkey);
	SDL_SetColorKey(EnemigoAmarillo, SDL_TRUE, colorkey);
	SDL_SetColorKey(EnemigoAzul, SDL_TRUE, colorkey);
	SDL_SetColorKey(EnemigoRojo, SDL_TRUE, colorkey);
	SDL_SetColorKey(EnemigoJefe, SDL_TRUE, colorkey);
	SDL_SetColorKey(Numeros, SDL_TRUE, colorkey);
	SDL_SetColorKey(sig_N, SDL_TRUE, colorkey);
	SDL_SetColorKey(GameO, SDL_TRUE, colorkey);


	return 0;
}



