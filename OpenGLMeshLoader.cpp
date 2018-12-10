#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <string>
#include <random>
#include <iostream>
#include <math.h>
#include <time.h>
//#include <Audio.h>

//#include "./SDL2.dll"

//#include "SDL_mixer.h"

#define width  1400
#define height 700

#define maxLife 5
#define maxLevelNumber 5
#define maxClockFrequency 2
#define maxCoinFrequency 30
#define maxHeartFrequency 5
#define maxJerkenFrequency 4
#define maxConeFrequency 8
#define maxTyreFrequency 3
#define maxHummerFrequency 2

void InitLightSource();
void InitMaterial();
void myInit(void);
void colorRGB(int red, int green, int blue);
void bezier(float t, float* p0, float* p1, float* p2, float* p3, float* res);
void loadWhiteImage();
void cameraSetup();

void drawScene(GLTexture texture, float startX, float endX, float startZ, float endZ, float repetitionX, float repetitionZ);
void drawRoad();
void drawRasif();
void drawLamps();
void drawOneRock();
void drawOneBush();
void drawCamels();
void draw3dsModel(int objectCount, int horizontalDistance, int separatingDistance, int startingSeparatingDistance, int sceneThousands, int globalSceneVariable, void(*drawingFunction)());
void drawSnowMan();

void drawGrass();
void drawSand();
void drawSea();
void drawSnow();

void collision(float* zPosition, float* xPosition, int collisionType);
void roadCollision();
void checkTheifCollision();
void checkCollision();
void incrementLevel(int newLevel);

void Display();
void Timer(int value);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void arrows(int key, int x, int y);
void arrowsUp(int key, int x, int y);
void mouseListener(int button, int state, int x, int y);
void LoadModels();
void print(int x, int y, int z, char *string);

bool third = true;

float cameraX = 0;
float cameraY = 0.25;
float cameraZ = -0.4;

float lookAtX = 0;
float lookAtY = 0;
float lookAtZ = 0;

float cameraFirstX = 0.15;
float cameraFirstY = 0.1;
float cameraFirstZ = 0.07;

float lookAtFirstX = 0.15;
float lookAtFirstY = 0;
float lookAtFirstZ = 0.5;

bool game = false;
float skyRotation = 0;

int delay = 150;
int seconds = 120;

int score = 0;
int level = 0;
int life = 3;

bool displayScore = false;

float policeMaxSpeed = 1.2;
float theifMaxSpeed = 1.2;

float policeStepSpeed = 0.001;
float theifStepSpeed = 0.005;

float policeAccelerationValue = 0.00001;
float theifAccelerationValue = 0.0001;


int policeAccelerationDelay = 0;
float currentPoliceSpeed = policeMaxSpeed;
bool policeSpeedUp = false;

// Model Variables
Model_3DS theif_car;
Model_3DS police_car;
Model_3DS street_lamp;
Model_3DS heart;
Model_3DS timer;
Model_3DS coin;
Model_3DS cone;
Model_3DS jerrycan;
Model_3DS tyre;
Model_3DS truck;
Model_3DS hittostart;
Model_3DS level1;
Model_3DS level2;
Model_3DS level3;
Model_3DS level4;
Model_3DS level5;
Model_3DS gameOver;
Model_3DS youWin;
Model_3DS snowMan;
Model_3DS boat;
Model_3DS ship;
Model_3DS bush1;
Model_3DS bush2;
Model_3DS camel;
Model_3DS rock1;
Model_3DS palm;

// Textures Variables
GLTexture road;
GLTexture rasif;
GLTexture white;

GLTexture grass;
GLTexture sand;
GLTexture sea;
GLTexture snow;

GLuint sky;

float theifCarStepX = 0;
float theifCarStepY = 0;
float theifCarStepZ = 0;

float theifCarX = 0;
float theifCarY = 0;
float theifCarZ = 0;

float policeCarStepX = 0;
float policeCarStepY = 0;
float policeCarStepZ = 0;

float policeCarX = 0;
float policeCarY = 0;
float policeCarZ = 0;

int clock1Index = -1;
int clock2Index = -1;

int clockFrequency = 1;

float clock1X[maxClockFrequency];
float clock1Z[maxClockFrequency];

float clock2X[maxClockFrequency];
float clock2Z[maxClockFrequency];


int heart1Index = -1;
int heart2Index = -1;

int heartFrequency = 1;

float heart1X[maxHeartFrequency];
float heart1Z[maxHeartFrequency];

float heart2X[maxHeartFrequency];
float heart2Z[maxHeartFrequency];


int cone1Index = -1;
int cone2Index = -1;

int coneFrequency = 2;

float cone1X[maxConeFrequency];
float cone1Z[maxConeFrequency];
float cone2X[maxConeFrequency];
float cone2Z[maxConeFrequency];


int jerken1Index = -1;
int jerken2Index = -1;

int jerkenFrequency = 1;

float jerken1X[maxJerkenFrequency];
float jerken1Z[maxJerkenFrequency];
float jerken2X[maxJerkenFrequency];
float jerken2Z[maxJerkenFrequency];



int coin1Index = -1;
int coin2Index = -1;

int coinFrequency = 20;

float coin1X[maxCoinFrequency];
float coin1Y[maxCoinFrequency];
float coin1Z[maxCoinFrequency];

float coin2X[maxCoinFrequency];
float coin2Y[maxCoinFrequency];
float coin2Z[maxCoinFrequency];


int hummer1Index = -1;
int hummer2Index = -1;

int hummerFrequency = 1;

float hummer1X[maxHummerFrequency];
float hummer1Y[maxHummerFrequency];
float hummer1Z[maxHummerFrequency];

float hummer2X[maxHummerFrequency];
float hummer2Y[maxHummerFrequency];
float hummer2Z[maxHummerFrequency];


//boat
float boatX = -60;
float boatY = 0;
float boatZ = 2500;

//animation (bezier)
float p0b[2];
float p1b[2];
float p2b[2];
float p3b[2];

//coin animation 
float resc[2];
float tc = 0.5;
double coinJump = 0;
long coinRotation = 0;

//clock animation
long clockRotation = 0;

//heart animation
float resd[2];
float td = 0.75;
double heartJump = 0.25;
double heartWave = 0;
double heartWaveIncrement = 0.5;


// tyre coords
//tyre animation
float resb[2];
//float tb = 0;
//double tyreJump = 0;
//float tyreX = 0;
//double tyreXIncrement = 0.1;
double troll = 0;
double trollIncrement = 3;

int tyre1Index = -1;
int tyre2Index = -1;

int tyreFrequency = 1;

float tyre1X[maxTyreFrequency];
float tyre1Z[maxTyreFrequency];
double tyre1Xincrement[maxTyreFrequency];
double tyre1t[maxTyreFrequency];
double tyre1Jump[maxTyreFrequency];
float tyre2X[maxTyreFrequency];
float tyre2Z[maxTyreFrequency];
double tyre2Xincrement[maxTyreFrequency];
double tyre2t[maxTyreFrequency];
double tyre2Jump[maxTyreFrequency];

//steering
double carSteering = 0;
bool rightPressed = false;
bool leftPressed = false;
double steeringValue = 0.1;
double staLim = 0.5;
double steeringTransAcc = 0;

int threshold = 600;

int roadScene = 0;
int grassScene = 0;
int sandScene = 0;
int seaScene = 0;
int snowScene = 0;
int firstScene = 0;

//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT7);

	GLfloat specular7[4];
	GLfloat diffuse7[4];

	int i = firstScene % 4;

	switch (i){
	case 0:specular7[0] = 1; specular7[1] = 1; specular7[2] = 1; specular7[3] = 1; diffuse7[0] = 1; diffuse7[1] = 1; diffuse7[2] = 1; diffuse7[3] = 1; break;
	case 1:specular7[0] = 1; specular7[1] = 1; specular7[2] = 0.4; specular7[3] = 1; diffuse7[0] = 1; diffuse7[1] = 1; diffuse7[2] = 0.4; diffuse7[3] = 1; break;
	case 2:specular7[0] = 1; specular7[1] = 1; specular7[2] = 1; specular7[3] = 1; diffuse7[0] = 1; diffuse7[1] = 1; diffuse7[2] = 1; diffuse7[3] = 1; break;
	case 3:specular7[0] = 3; specular7[1] = 3; specular7[2] = 3; specular7[3] = 1; diffuse7[0] = 2; diffuse7[1] = 2; diffuse7[2] = 2; diffuse7[3] = 1; break;
	}

	GLfloat light_position7[] = { 0, 0, 0.15 + cameraZ, 1.0f };
	GLfloat spot_direction7[] = { 0, 0, 0.5 };

	glLightfv(GL_LIGHT7, GL_SPECULAR, specular7);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, diffuse7);
	glLightfv(GL_LIGHT7, GL_POSITION, light_position7);
	glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, spot_direction7);
	glLightf(GL_LIGHT7, GL_QUADRATIC_ATTENUATION, 0.025);
	glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, 5.0);
	glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, 80);




	glEnable(GL_LIGHT6);

	GLfloat specular6[] = { 3, 3, 1, 1.0f };
	GLfloat diffuse6[] = { 3, 3, 1, 1.0f };
	GLfloat light_position6[] = { 0.15 + (policeCarX / 100), 0.04, (policeCarZ / 100), 1.0f };
	GLfloat spot_direction6[] = { 0, 0, 1 };

	glLightfv(GL_LIGHT6, GL_SPECULAR, specular6);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, diffuse6);
	glLightfv(GL_LIGHT6, GL_POSITION, light_position6);
	glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spot_direction6);
	glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, 0.025);
	glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 5.0);
	glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 2);

}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}
//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void reset() {
	third = true;

	cameraX = 0;
	cameraY = 0.25;
	cameraZ = -0.4;

	lookAtX = 0;
	lookAtY = 0;
	lookAtZ = 0;

	cameraFirstX = 0.15;
	cameraFirstY = 0.1;
	cameraFirstZ = 0.07;

	lookAtFirstX = 0.15;
	lookAtFirstY = 0;
	lookAtFirstZ = 0.5;

	policeMaxSpeed = 1.2;

	theifMaxSpeed = 1.2;

	policeStepSpeed = 0.001;
	theifStepSpeed = 0.005;

	policeAccelerationValue = 0.00001;
	theifAccelerationValue = 0.0001;


	policeAccelerationDelay = 0;
	currentPoliceSpeed = policeMaxSpeed;
	policeSpeedUp = false;

	theifCarStepX = 0;
	theifCarStepY = 0;
	theifCarStepZ = 0;

	theifCarX = 0;
	theifCarY = 0;
	theifCarZ = 0;

	policeCarStepX = 0;
	policeCarStepY = 0;
	policeCarStepZ = 0;

	policeCarX = 0;
	policeCarY = 0;
	policeCarZ = 0;

	clock1Index = -1;
	clock2Index = -1;

	heart1Index = -1;
	heart2Index = -1;

	cone1Index = -1;
	cone2Index = -1;

	jerken1Index = -1;
	jerken2Index = -1;

	coin1Index = -1;
	coin2Index = -1;

	hummer1Index = -1;
	hummer2Index = -1;

	//boat
	boatX = -60;
	boatY = 0;
	boatZ = 2500;

	//tyre animation
	//tb = 0;
	//tyreJump = 0;

	//coin animation 
	tc = 0.5;
	coinJump = 0;
	coinRotation = 0;

	//clock animation
	clockRotation = 0;

	//heart animation
	td = 0.75;
	heartJump = 0.25;
	heartWave = 0;
	heartWaveIncrement = 0.5;


	// tyre coords
	//tyreX = 0;
	//tyreXIncrement = 0.1;
	troll = 0;
	trollIncrement = 3;

	tyre1Index = -1;
	tyre2Index = -1;

	//steering
	carSteering = 0;
	rightPressed = false;
	leftPressed = false;
	steeringValue = 0.1;
	staLim = 0.5;
	steeringTransAcc = 0;

	roadScene = 0;
	grassScene = 0;
	sandScene = 0;
	seaScene = 0;
	snowScene = 0;

}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{

	//tyre animation
	p0b[0] = 0;
	p0b[1] = 0;

	p1b[0] = 0;
	p1b[1] = 0.5;

	p2b[0] = 0.5;
	p2b[1] = 0.5;

	p3b[0] = 0.5;
	p3b[1] = 0;

	srand(unsigned(time(NULL)));

	for (int i = 0; i < maxTyreFrequency; ++i)
	{
		tyre1Xincrement[i] = 0.2;
		tyre2Xincrement[i] = 0.2;

		tyre1X[i] = rand() % 41;
		tyre2X[i] = rand() % 41;


		tyre1t[i] = ((double)(rand() % 100)) / 100;
		tyre2t[i] = ((double)(rand() % 100)) / 100;
		//printf("%f\n", tyre1t[i]);
	}

	//InitLightSource();

	//InitMaterial();

	//glEnable(GL_DEPTH_TEST);

	//glEnable(GL_NORMALIZE);

	glClearColor(1.0, 1.0, 1.0, 0.0);
}

//=======================================================================
// color in RGB
//=======================================================================
void colorRGB(int red, int green, int blue){
	double r = red / 255.0;
	double g = green / 255.0;
	double b = blue / 255.0;
	glColor3f(r, g, b);
}

//=======================================================================
// Bezier function
//=======================================================================
void bezier(float t, float* p0, float* p1, float* p2, float* p3, float* res)
{
	*res = pow((1 - t), 3)*p0[0] + 3 * t*pow((1 - t), 2)*p1[0] + 3 * pow(t, 2)*(1 - t)*p2[0] + pow(t, 3)*p3[0];
	*(res + 1) = pow((1 - t), 3)*p0[1] + 3 * t*pow((1 - t), 2)*p1[1] + 3 * pow(t, 2)*(1 - t)*p2[1] + pow(t, 3)*p3[1];
}

//=======================================================================
// load white image
//=======================================================================
void loadWhiteImage()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, white.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);			glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0);			glVertex3f(0, 0, 0);
	glTexCoord2f(1, 1);			glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1);			glVertex3f(0, 0, 0);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

}

//=======================================================================
// camera Setup
//=======================================================================
void cameraSetup()
{
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(60.0, (width / height), 0.01, 100);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	if (third)
		gluLookAt(cameraX, cameraY, cameraZ, lookAtX, lookAtY, lookAtZ, 0, 1, 0);
	else
		gluLookAt(cameraFirstX, cameraFirstY, cameraFirstZ, lookAtFirstX, lookAtFirstY, lookAtFirstZ, 0, 1, 0);
}

//=======================================================================
// Draw Scene function
//=======================================================================
void drawScene(GLTexture texture, float startX, float endX, float startZ, float endZ, float repetitionX, float repetitionZ){

	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

	glBindTexture(GL_TEXTURE_2D, texture.texture[0]);	// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);						glVertex3f(startX, 0, startZ);
	glTexCoord2f(repetitionX, 0);			glVertex3f(endX, 0, startZ);
	glTexCoord2f(repetitionX, repetitionZ);	glVertex3f(endX, 0, endZ);
	glTexCoord2f(0, repetitionZ);			glVertex3f(startX, 0, endZ);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.
}

//=======================================================================
// Draw Road
//=======================================================================
void drawRoad()
{

	int start = -50 + (roadScene * 2000);
	int end = 4000 + (roadScene * 2000);

	drawScene(road, -40, 40, start, end, 2, 10);

}
//=======================================================================
// Draw Rasif
//=======================================================================
void drawRasif()
{

	int start = -50 + (roadScene * 2000);
	int end = 4000 + (roadScene * 2000);

	drawScene(rasif, 40, 50, start, end, 1, 100);
	drawScene(rasif, -40, -50, start, end, 1, 100);

}

//=======================================================================
// Draw Street Lamps
//=======================================================================
void drawLamps(){

	for (int i = 0; i < 26; i++){
		if (-50 + (4000 * grassScene) + (i * 40) - policeCarZ < threshold)
		{
			glPushMatrix();
			glTranslatef(0, 0, -50 + (4000 * grassScene) + (i * 40));
			glScalef(0.15, 0.15, 0.15);
			street_lamp.Draw();
			glPopMatrix();
		}
	}

	for (int i = 0; i < 26; i++){
		if (-50 + (4000 * grassScene) + (i * 40) - policeCarZ < threshold)
		{
			glPushMatrix();
			glTranslatef(-87, 0, -50 + (4000 * grassScene) + (i * 40));
			glScalef(0.15, 0.15, 0.15);
			street_lamp.Draw();
			glPopMatrix();
		}
	}
}

//=======================================================================
// Draw One Rock
//=======================================================================
void drawOneRock(){

	glPushMatrix();
	glScaled(4, 4, 4);
	colorRGB(231, 77, 0);
	glTranslated(0, -0.5, 0);
	rock1.Draw();
	glPopMatrix();
}

//=======================================================================
// Draw One bush
//=======================================================================
void drawOneBush()
{
	glPushMatrix();
	glScaled(10, 10, 10);
	colorRGB(0, 128, 0);
	bush1.Draw();
	glPopMatrix();
}

//=======================================================================
// Draw Camel
//=======================================================================
void drawCamels()
{

	glDisable(GL_LIGHTING);
	colorRGB(160, 82, 45);

	for (int i = 0; i < 3; i++) //index: kam wa7da fel scene
	{
		if (1050 + (4000 * sandScene) + (i * 120) - policeCarZ < threshold)
		{
			glPushMatrix();
			glTranslatef(70, 0, 1050 + (4000 * sandScene) + (i * 280)); //1050: scene rakam kam //4000: constant //120: masafa ben koll wa7da //70 el shemal
			glScaled(2, 2, 2);
			glRotatef(180, 0, 1, 0);
			camel.Draw();
			glPopMatrix();
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (1050 + (4000 * sandScene) + (i * 120) - policeCarZ < threshold)
		{
			glPushMatrix();
			glTranslatef(-70, 0, 1350 + (4000 * sandScene) + (i * 320));
			glScaled(2, 2, 2);
			camel.Draw();
			glPopMatrix();
		}
	}
	glEnable(GL_LIGHTING);
}

//=======================================================================
// Helper gunction to draw rock and bush
//=======================================================================
void draw3dsModel(int objectCount, int horizontalDistance, int separatingDistance, int startingSeparatingDistance, int sceneThousands, int globalSceneVariable, void(*drawingFunction)())
{

	for (int i = 0; i < objectCount; ++i)
	{
		if (startingSeparatingDistance + sceneThousands + 4000 * globalSceneVariable + i*separatingDistance - policeCarZ < threshold)
		{
			glPushMatrix();
			glTranslatef(70 + horizontalDistance, 0, startingSeparatingDistance + sceneThousands + 4000 * globalSceneVariable + i*separatingDistance);
			(*drawingFunction)();
			glPopMatrix();
		}
	}

	for (int i = 0; i < objectCount; ++i)
	{
		if (startingSeparatingDistance + sceneThousands + 4000 * globalSceneVariable + i*separatingDistance - policeCarZ < threshold)
		{
			glPushMatrix();
			glTranslatef(-70 - horizontalDistance, 0, startingSeparatingDistance + sceneThousands + 4000 * globalSceneVariable + i*separatingDistance);
			(*drawingFunction)();
			glPopMatrix();
		}
	}
}

//=======================================================================
// Draw Snowman
//=======================================================================
void drawSnowMan()
{
	for (int i = 0; i < 6; i++)
	{
		if (3060 + (4000 * snowScene) + (i * 150) - policeCarZ < threshold)
		{
			glPushMatrix();
			glTranslatef(60, 0, 3060 + (4000 * snowScene) + (i * 150));
			glScalef(2, 2, 2);
			glRotatef(180, 0, 1, 0);
			snowMan.Draw();
			glPopMatrix();
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (3060 + (4000 * snowScene) + (i * 150) - policeCarZ < threshold)
		{
			glPushMatrix();
			glTranslatef(-60, 0, 3060 + (4000 * snowScene) + (i * 150));
			glScalef(2, 2, 2);
			snowMan.Draw();
			glPopMatrix();
		}
	}
}

//=======================================================================
// Draw Grass Scene
//=======================================================================
void drawGrass()
{

	int start = (4000 * grassScene);
	int end = (4000 * grassScene) + 1000;

	if (start == 0)
		start = -50;

	drawScene(grass, 50, 400, start, end, 10, 50);
	drawScene(grass, -50, -400, start, end, 10, 50);
}

//=======================================================================
// Draw Sand Scene
//=======================================================================
void drawSand(){

	int start = (4000 * sandScene) + 1000;
	int end = (4000 * sandScene) + 2000;

	drawScene(sand, 50, 400, start, end, 1, 1);
	drawScene(sand, -50, -400, start, end, 1, 1);
}

//=======================================================================
// Draw Sea Scene
//=======================================================================
void drawSea(){

	int start = (4000 * seaScene) + 2000;
	int end = (4000 * seaScene) + 3000;

	drawScene(sea, 50, 400, start, end, 1, 1);
	drawScene(sea, -50, -400, start, end, 1, 1);

	boatZ = start + 500;
}

//=======================================================================
// Draw Snow Scene
//=======================================================================
void drawSnow(){

	int start = (4000 * snowScene) + 3000;
	int end = (4000 * snowScene) + 4000;

	drawScene(snow, 50, 400, start, end, 1, 10);
	drawScene(snow, -50, -400, start, end, 1, 10);
}

//=======================================================================
// check if a collision happened using z and x position and collision type
//=======================================================================
void collision(float* zPosition, float* xPosition, int collisionType){

	if (*zPosition< policeCarZ + 17 && *zPosition>policeCarZ - 17)
	{

		int r = *xPosition - (policeCarX + 15);
		if (r < 0)
			r = -r;

		if (r<11.5){

			*zPosition = -100;

			switch (collisionType)
			{
				case 10: life--; PlaySound("sounds/crashV3.wav", NULL, SND_ASYNC | SND_FILENAME); break; //hummer
				case 11: life--; PlaySound("sounds/crashV4b.wav", NULL, SND_ASYNC | SND_FILENAME);  break;	//tyre
				case 12: life--; PlaySound("sounds/crashV4b.wav", NULL, SND_ASYNC | SND_FILENAME);  break;	//cone
				case 1:	seconds += 30; PlaySound("sounds/tickTock.wav", NULL, SND_ASYNC | SND_FILENAME);  break;
				case 2:currentPoliceSpeed = policeMaxSpeed + 0.05; policeAccelerationDelay = 1000; policeSpeedUp = true; PlaySound("sounds/speed up2.wav", NULL, SND_ASYNC | SND_FILENAME); break;
				case 3:life++; PlaySound("sounds/heart.wav", NULL, SND_ASYNC | SND_FILENAME); break;
				case 4:score++; PlaySound("sounds/coin.wav", NULL, SND_ASYNC | SND_FILENAME); break;
			}
		}
	}

}

//=======================================================================
// Check if car out of street
//=======================================================================
void roadCollision(){


	int left = (policeCarX + 15) + 6.5;
	int right = (policeCarX + 15) - 6.5;


	if (left >= 40 || right <= -40)
	{
		PlaySound("sounds/sideBump.wav", NULL, SND_ASYNC | SND_FILENAME);
		life--;
		policeCarX = 0;
	}

}
//=======================================================================
// check theif Collision
//=======================================================================
void checkTheifCollision(){

	float zDistance = policeCarZ - theifCarZ;
	float xDistance = (policeCarX + 15) - (theifCarX - 15);

	//printf("z:%f\n",zDistance );
	//printf("x:%f\n", xDistance);

	if (zDistance < 0)
		zDistance = -zDistance;

	if (zDistance < 30){

		float xDistance = (policeCarX + 15) - (theifCarX - 15);

		if (xDistance < 0)
			xDistance = -xDistance;

		if (xDistance < 13)
		{
			game = false;
			reset();
			incrementLevel(++level);
		}

	}
}


//=======================================================================
// check Collisions
// collisionType 
// --------------
//	0 ==> Obstacle
//  1 ==> time
//  2 ==> speed
//  3 ==> life
//  4 ==> score
//=======================================================================
void checkCollision(){

	//theif collision
	checkTheifCollision();

	//side road collision
	roadCollision();

	//obstacles collision

	for (int i = 0; i < coneFrequency; i++){
		collision(&cone1Z[i], &cone1X[i], 12);
		collision(&cone2Z[i], &cone2X[i], 12);
	}

	for (int i = 0; i < tyreFrequency; i++){
		collision(&tyre1Z[i], &tyre1X[i], 11);
		collision(&tyre2Z[i], &tyre2X[i], 11);
	}

	for (int i = 0; i < hummerFrequency; i++)
	{
		collision(&hummer1Z[i], &hummer1X[i], 10);
		collision(&hummer2Z[i], &hummer2X[i], 10);
	}


	//time powerUp
	for (int i = 0; i < clockFrequency; i++){
		collision(&clock1Z[i], &clock1X[i], 1);
		collision(&clock2Z[i], &clock2X[i], 1);
	}

	//speed powerUp
	for (int i = 0; i < jerkenFrequency; i++){
		collision(&jerken1Z[i], &jerken1X[i], 2);
		collision(&jerken2Z[i], &jerken2X[i], 2);
	}

	//life powerUp
	if (life < maxLife){
		for (int i = 0; i < heartFrequency; i++){
			collision(&heart1Z[i], &heart1X[i], 3);
			collision(&heart2Z[i], &heart2X[i], 3);
		}
	}

	if (life <= 0)
	{
		game = false;
		reset();
		incrementLevel(1);
		level = 0;
		PlaySound(TEXT("sounds/lose.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	}

	if (seconds <= 0)
	{
		game = false;
		reset();
		incrementLevel(1);
		level = 0;
		PlaySound(TEXT("sounds/lose.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	}



	//coin score
	for (int i = 0; i < coinFrequency; i++){
		if (roadScene % 2 == 0){
			collision(&coin1Z[i], &coin1X[i], 4);
		}
		else{
			collision(&coin2Z[i], &coin2X[i], 4);
		}

	}
}

//=======================================================================
// start new level
//=======================================================================
void incrementLevel(int newLevel)
{

	switch (newLevel)
	{
	case 1:
		coneFrequency = 2;
		tyreFrequency = 1;
		hummerFrequency = 1;
		heartFrequency = 1;
		displayScore = true;
		PlaySound(TEXT("sounds/levelup.wav"), NULL, SND_ASYNC | SND_FILENAME);
		break;
	case 2:
		coneFrequency += 2;
		heartFrequency++;
		displayScore = false;
		PlaySound(TEXT("sounds/levelup.wav"), NULL, SND_ASYNC | SND_FILENAME);
		break;
	case 3:
		tyreFrequency++;
		coneFrequency++;
		displayScore = false;
		PlaySound(TEXT("sounds/levelup.wav"), NULL, SND_ASYNC | SND_FILENAME);
		break;
	case 4:
		hummerFrequency++;
		coneFrequency++;
		heartFrequency++;
		displayScore = false;
		PlaySound(TEXT("sounds/levelup.wav"), NULL, SND_ASYNC | SND_FILENAME);
		break;
	case 5:
		tyreFrequency++;
		coneFrequency++;
		heartFrequency++;
		displayScore = false;
		PlaySound(TEXT("sounds/levelup.wav"), NULL, SND_ASYNC | SND_FILENAME);
		break;
	case 6:
		coneFrequency = 2;
		tyreFrequency = 1;
		hummerFrequency = 1;
		heartFrequency = 1;
		displayScore = true;
		PlaySound(TEXT("sounds/win.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
		break;
	default:
		break;
	}
}

//=======================================================================
// Display Function
//=======================================================================
void Display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	InitLightSource();
	InitMaterial();
	cameraSetup();

	if (game)
		checkCollision();

	glPushMatrix();

	glScalef(0.01, 0.01, 0.01);

	//Display Timer
	glPushMatrix();
	glDisable(GL_LIGHTING);
	colorRGB(255, 255, 255);
	colorRGB(128, 128, 0);
	char* str[20];
	sprintf((char *)str, "%d sec", seconds);

	int x, y, z;

	if (third){
		x = 0;
		y = 0;
		z = (cameraZ + 0.4) * 100;
	}
	else{
		x = (cameraFirstX)* 100;
		y = 80;
		z = (cameraFirstZ + 0.43) * 100;
	}

	print(290 + x, 2 + y, 270 + z, (char*)str);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	//Display Score
	glPushMatrix();
	glDisable(GL_LIGHTING);
	colorRGB(255, 255, 255);
	colorRGB(128, 128, 0);
	char* str2[20];
	sprintf((char *)str2, "%d", score);

	int x1, y1, z1;

	if (third){
		x1 = 0;
		y1 = 0;
		z1 = (cameraZ + 0.4) * 100;
	}
	else{
		x1 = (cameraFirstX)* 100;
		y1 = 45;
		z1 = (cameraFirstZ + 0.43) * 100;
	}

	print(188 + x1, 1.7 + y1, 160 + z1, (char*)str2);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//Display Last Score

	if (!game && displayScore){
		glPushMatrix();
		glDisable(GL_LIGHTING);
		colorRGB(255, 255, 255);
		colorRGB(0, 128, 0);
		char* str3[20];
		sprintf((char *)str2, "Score: %d", score);

		print(10, 5, 200, (char*)str2);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}

	//Draw Road
	glPushMatrix();
	drawRoad();
	drawRasif();
	drawLamps();
	drawSnowMan();
	drawCamels();
	//void draw3dsModel(int objectCount, int horizontalDistance, int separatingDistance, int startingSeparatingDistance, int sceneThousands, int globalSceneVariable, void(*drawingFunction)())
	draw3dsModel(8, 40, 120, 15, 1000, sandScene, drawOneRock);
	draw3dsModel(2, 20, 540, 232, 1000, sandScene, drawOneBush);
	glPopMatrix();

	// Draw Side Scenes
	glPushMatrix();
	drawGrass();
	drawSand();
	drawSea();
	drawSnow();
	glPopMatrix();


	// Draw Theif Car
	glPushMatrix();
	glTranslatef(theifCarX, theifCarY, theifCarZ);
	glTranslatef(-15, 4, 0);
	glScalef(0.1, 0.1, 0.1);
	theif_car.Draw();
	glPopMatrix();


	//Draw Police Car
	glPushMatrix();

	glTranslatef(policeCarX, policeCarY, policeCarZ);
	glTranslatef(15, 4.8, 0);
	glScalef(0.006, 0.006, 0.006);
	glRotated(carSteering, 0, 1, 0);
	police_car.Draw();
	glPopMatrix();


	//Draw Boat
	if (boatZ + 200 - policeCarZ < threshold)
	{
		glPushMatrix();
		glTranslatef(boatX - 10, boatY, boatZ+200);
		glTranslatef(0, 10, 0);
		glRotated(180, 0, 1, 0);
		boat.Draw();
		glPopMatrix();
	}

	//Draw Ship
	if (boatZ - 200 - policeCarZ < threshold)
	{
		glPushMatrix();
		glTranslatef(-boatX, boatY, boatZ-200);
		glTranslatef(0, 4.8, 0);
		glRotated(180, 0, 1, 0);
		ship.Draw();
		glPopMatrix();
	}

	if (game){

		//Draw Truck 
		for (int i = 0; i < hummerFrequency; i++)
		{
			if (hummer1Z[i] - policeCarZ < threshold)
			{
				glPushMatrix();
				glTranslatef(hummer1X[i], 0, hummer1Z[i]);
				glTranslatef(0, 12, 0);
				glRotated(180, 0, 1, 0);
				glScalef(0.11, 0.11, 0.11);
				truck.Draw();
				glPopMatrix();
			}
			if (hummer2Z[i] - policeCarZ < threshold)
			{
				glPushMatrix();
				glTranslatef(hummer2X[i], 0, hummer2Z[i]);
				glTranslatef(0, 12, 0);
				glRotated(180, 0, 1, 0);
				glScalef(0.11, 0.11, 0.11);
				truck.Draw();
				glPopMatrix();
			}

		}

		//Draw clock1

		for (int i = 0; i < clockFrequency; i++)
		{
			if (clock1Z[i] - policeCarZ < threshold)
			{
				glPushMatrix();
				glTranslatef(clock1X[i], 0, clock1Z[i]);
				glTranslated(0, 7, 0);
				glScaled(10, 10, 10);
				glRotated(-90 + clockRotation, 0, 1, 0);
				timer.Draw();
				glPopMatrix();

				glPushMatrix();
				glTranslatef(clock1X[i], 0, clock1Z[i]);
				glTranslated(0, 7, 0);
				glScaled(10, 10, 10);
				glRotated(90 + clockRotation, 0, 1, 0);
				timer.Draw();
				glPopMatrix();
			}
		}

		//Draw clock2

		for (int i = 0; i < clockFrequency; i++)
		{
			if (clock2Z[i] - policeCarZ < threshold)
			{
				glPushMatrix();
				glTranslatef(clock2X[i], 0, clock2Z[i]);
				glTranslated(0, 7, 0);
				glScaled(10, 10, 10);
				glRotated(-90 + clockRotation, 0, 1, 0);
				timer.Draw();
				glPopMatrix();

				glPushMatrix();
				glTranslatef(clock2X[i], 0, clock2Z[i]);
				glTranslated(0, 7, 0);
				glScaled(10, 10, 10);
				glRotated(90 + clockRotation, 0, 1, 0);
				timer.Draw();
				glPopMatrix();
			}

		}

		for (int i = 0; i < coneFrequency; i++)
		{
			if (cone1Z[i] - policeCarZ < threshold)
			{
				//Draw cone 1
				glPushMatrix();
				colorRGB(255, 255, 255);
				glTranslatef(cone1X[i], 0, cone1Z[i]);
				glScaled(0.3, 0.25, 0.3);
				glRotated(-90, 0, 1, 0);
				cone.Draw();
				glPopMatrix();
			}

			if (cone2Z[i] - policeCarZ < threshold)
			{
				//Draw cone 2
				glPushMatrix();
				colorRGB(255, 255, 255);
				glTranslatef(cone2X[i], 0, cone2Z[i]);
				glScaled(0.3, 0.25, 0.3);
				glRotated(-90, 0, 1, 0);
				cone.Draw();
				glPopMatrix();
			}

		}
		// Draw jerken

		for (int i = 0; i < jerkenFrequency; i++)
		{
			if (jerken1Z[i] - policeCarZ < threshold)
			{
				glPushMatrix();
				glTranslatef(jerken1X[i], -10, jerken1Z[i]);
				glScaled(1.4, 1.4, 1.4);
				glTranslated(-18, 0, -2.5);
				glRotated(-90, 0, 1, 0);
				glScaled(8, 8, 8);
				jerrycan.Draw();
				glPopMatrix();
			}

			if (jerken2Z[i] - policeCarZ < threshold)
			{
				glPushMatrix();
				glTranslatef(jerken2X[i], -10, jerken2Z[i]);
				glScaled(1.4, 1.4, 1.4);
				glTranslated(-18, 0, -2.5);
				glRotated(-90, 0, 1, 0);
				glScaled(8, 8, 8);
				jerrycan.Draw();
				glPopMatrix();
			}
		}

		for (int i = 0; i < tyreFrequency; i++)
		{
			//if (tyre1Z[i] - policeCarZ < threshold)
			//{
				//tyre1
			printf("%f\n", tyre1X[i]);
				glPushMatrix();
				glTranslated(0, 0, tyre1X[i]*3);
				glTranslated(0, 0, tyre1Z[i] + tyre1X[i]);
				glRotated(90,0,1,0);
				glTranslated(0, 8, 0);
				glRotated(troll, 1, 0, 0);
				glTranslated(0, -8, 0);
				//glTranslated(0, 0, );
				glTranslated(0, tyre1Jump[i], 0);
				glColor3f(0.3, 0.3, 0.3);
				glScaled(0.05, 0.05, 0.05);
				glRotated(90, 0,1 , 0);
				tyre.Draw();
				glPopMatrix();
			//}

			//if (tyre2Z[i] - policeCarZ < threshold)
			//{
				//tyre2
				glPushMatrix();
				glTranslated(0, 0, tyre1X[i] * 3);
				glTranslated(0, 0, tyre2Z[i] + tyre2X[i]);
				glRotated(90, 0, 1, 0);
				glTranslated(0, 8, 0);
				glRotated(troll, 1, 0, 0);
				glTranslated(0, -8, 0);
				//glTranslated(0, 0, );
				glTranslated(0, tyre2Jump[i], 0);
				glColor3f(0.3, 0.3, 0.3);
				glScaled(0.05, 0.05, 0.05);
				glRotated(90, 0, 1, 0);
				tyre.Draw();
				glPopMatrix();
			//}

		}

		//draw coins 1
		for (int i = 0; i < coinFrequency; i++)
		{
			if (coin1Z[i] - policeCarZ < threshold)
			{
				glPushMatrix();
				colorRGB(255, 255, 255);
				glTranslatef(coin1X[i], coin1Y[i] + coinJump, coin1Z[i]);
				glTranslated(0, 7, 0);
				glScaled(10, 10, 10);
				glRotated(-90 + coinRotation, 0, 1, 0);
				coin.Draw();
				glPopMatrix();

				glPushMatrix();
				colorRGB(255, 255, 255);
				glTranslatef(coin1X[i], coin1Y[i] + coinJump, coin1Z[i]);
				glTranslated(0, 7, 0);
				glScaled(10, 10, 10);
				glRotated(90 + coinRotation, 0, 1, 0);
				coin.Draw();
				glPopMatrix();
			}


			//draw coins 2
			if (coin2Z[i] - policeCarZ < threshold)
			{
				glPushMatrix();
				colorRGB(255, 255, 255);
				glTranslatef(coin2X[i], coin2Y[i] + coinJump, coin2Z[i]);
				glTranslated(0, 7, 0);
				glScaled(10, 10, 10);
				glRotated(-90 + coinRotation, 0, 1, 0);
				coin.Draw();
				glPopMatrix();

				glPushMatrix();
				colorRGB(255, 255, 255);
				glTranslatef(coin2X[i], coin2Y[i] + coinJump, coin2Z[i]);
				glTranslated(0, 7, 0);
				glScaled(10, 10, 10);
				glRotated(90 + coinRotation, 0, 1, 0);
				coin.Draw();
				glPopMatrix();
			}
		}

		//Draw Heart

		if (life < maxLife)
		{
			for (int i = 0; i < heartFrequency; i++)
			{
				if (heart1Z[i] - policeCarZ < threshold)
				{
					glPushMatrix();
					glTranslatef(heart1X[i], heartJump, heart1Z[i]);
					glTranslatef(0, 0, 0);
					glScalef(5, 5, 5);
					glTranslated(0, 1, 0);
					glRotated(heartWave, 0, 0, 1);
					glTranslated(0, -1, 0);
					glRotatef(90, 0, 1, 0);
					colorRGB(255, 0, 0);
					heart.Draw();
					glPopMatrix();
				}

				if (heart2Z[i] - policeCarZ < threshold)
				{
					glPushMatrix();
					glTranslatef(heart2X[i], heartJump, heart2Z[i]);
					glTranslatef(0, 0, 0);
					glScalef(5, 5, 5);
					glTranslated(0, 1, 0);
					glRotated(heartWave, 0, 0, 1);
					glTranslated(0, -1, 0);
					glRotatef(90, 0, 1, 0);
					colorRGB(255, 0, 0);
					heart.Draw();
					glPopMatrix();
				}
			}
		}

	}

	if (!game)
	{
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslated(0, 6, -16);
		glRotated(30, 1, 0, 0);
		colorRGB(255, 255, 255);
		glScaled(8, 8, 8);
		hittostart.Draw();
		glEnable(GL_LIGHTING);
		glPopMatrix();

		if (level == 0){

			glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslated(0, 14, -16);
			glRotated(30, 1, 0, 0);
			colorRGB(255, 255, 255);
			glScaled(6, 6, 6);
			gameOver.Draw();
			glEnable(GL_LIGHTING);
			glPopMatrix();
		}


		if (level == 1){

			glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslated(0, 14, -16);
			glRotated(30, 1, 0, 0);
			colorRGB(255, 255, 255);
			glScaled(6, 6, 6);
			level1.Draw();
			glEnable(GL_LIGHTING);
			glPopMatrix();
		}

		if (level == 2){

			glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslated(0, 14, -16);
			glRotated(30, 1, 0, 0);
			colorRGB(255, 255, 255);
			glScaled(6, 6, 6);
			level2.Draw();
			glEnable(GL_LIGHTING);
			glPopMatrix();
		}

		if (level == 3){

			glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslated(0, 14, -16);
			glRotated(30, 1, 0, 0);
			colorRGB(255, 255, 255);
			glScaled(6, 6, 6);
			level3.Draw();
			glEnable(GL_LIGHTING);
			glPopMatrix();
		}

		if (level == 4){

			glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslated(0, 14, -16);
			glRotated(30, 1, 0, 0);
			colorRGB(255, 255, 255);
			glScaled(6, 6, 6);
			level4.Draw();
			glEnable(GL_LIGHTING);
			glPopMatrix();
		}

		if (level == 5){

			glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslated(0, 14, -16);
			glRotated(30, 1, 0, 0);
			colorRGB(255, 255, 255);
			glScaled(6, 6, 6);
			level5.Draw();
			glEnable(GL_LIGHTING);
			glPopMatrix();
		}
		if (level == 6){

			glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslated(0, 14, -16);
			glRotated(30, 1, 0, 0);
			colorRGB(40, 128, 40);
			glScaled(6, 6, 6);
			youWin.Draw();
			glEnable(GL_LIGHTING);
			glPopMatrix();
		}
	}


	//Display coin icon
	glPushMatrix();
	glDisable(GL_LIGHTING);
	if (third)
		glTranslated(0, 0, (cameraZ + 0.4) * 100);
	else
		glTranslated((cameraFirstX)* 100, 0, (cameraFirstZ + 0.43) * 100);

	glRotated(20, 1, 0, 0);
	glTranslated(40, 21, 0);
	glScaled(2, 2, 2);
	glRotated(-90, 0, 1, 0);
	colorRGB(200, 200, 0);
	coin.Draw();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//Display Heart
	glPushMatrix();
	glDisable(GL_LIGHTING);
	if (third)
		glTranslated(0, 0, (cameraZ + 0.4) * 100);
	else
		glTranslated((cameraFirstX)* 100, 0, (cameraFirstZ + 0.43) * 100);

	glRotated(20, 1, 0, 0);
	glTranslated(-7, 0, 0);

	for (int i = 0; i < life; i++){
		glPushMatrix();
		glTranslatef(-35 + (i * 5), 24.5, -0.4);
		glScalef(2, 2, 2);
		glTranslatef(0, -3, 0);
		glRotatef(90, 0, 1, 0);
		colorRGB(255, 0, 0);
		heart.Draw();
		glPopMatrix();
	}
	glEnable(GL_LIGHTING);
	glPopMatrix();


	//sky box
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glColor3f(0.6, 0.6, 0.6);
	GLUquadricObj * qobj;
	qobj = gluNewQuadric();
	glTranslated(0, 0, policeCarZ);
	glRotated(skyRotation, 0, 1, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, sky);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 10000, 10000, 100);
	gluDeleteQuadric(qobj);
	glEnable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	glPopMatrix();

	loadWhiteImage();

	glPopMatrix();

	glFlush();

	glutSwapBuffers();
}

//=======================================================================
// Timer Function
//=======================================================================
void Timer(int value) {

	if (game){

		if (leftPressed)
		{
			if (steeringTransAcc < staLim)
			{
				steeringTransAcc += 0.01;
			}
			policeCarX += steeringTransAcc;

			if (carSteering < 5)
			{
				carSteering += steeringValue;
			}
		}
		else if (rightPressed)
		{
			if (steeringTransAcc > -staLim)
			{
				steeringTransAcc -= 0.01;
			}
			policeCarX += steeringTransAcc;

			if (carSteering > -5)
			{
				carSteering -= steeringValue;
			}
		}
		else
		{
			if (steeringTransAcc > 0)
			{
				steeringTransAcc -= 0.01;
				if (steeringTransAcc < 0.005)
					steeringTransAcc = 0;
			}
			else if (steeringTransAcc < 0)
			{
				steeringTransAcc += 0.01;
				if (steeringTransAcc > -0.005)
					steeringTransAcc = 0;
			}
			policeCarX += steeringTransAcc;

			if (carSteering > 0)
			{
				carSteering -= steeringValue;
			}
			else if (carSteering < 0)
			{
				carSteering += steeringValue;
			}
		}

		//tyre animation
		for (int i = 0; i < tyreFrequency; ++i)
		{
			tyre1X[i] += tyre1Xincrement[i];
			if (tyre1X[i] < -40 || tyre1X[i] > 40)
				tyre1Xincrement[i] = -tyre1Xincrement[i];

			tyre2X[i] += tyre2Xincrement[i];
			if (tyre2X[i] < -40 || tyre2X[i] > 40)
				tyre2Xincrement[i] = -tyre2Xincrement[i];
		}
		//tyreX += tyreXIncrement;

		//if (tyreX < -35 || tyreX > 35)
			//tyreXIncrement = -tyreXIncrement;

		troll += trollIncrement;
		if (troll > 20 || troll < -20)
			trollIncrement = -trollIncrement;


		for (int i = 0; i < tyreFrequency; ++i)
		{
			bezier(tyre1t[i], p0b, p1b, p2b, p3b, resb);
			tyre1Jump[i] = resb[1] * 10;
			tyre1t[i] += 0.01;
			if (tyre1t[i] >= 1)
				tyre1t[i] = 0;
			bezier(tyre2t[i], p0b, p1b, p2b, p3b, resb);
			tyre2Jump[i] = resb[1] * 10;
			tyre2t[i] += 0.01;
			if (tyre2t[i] >= 1)
				tyre2t[i] = 0;
		}

		for (int i = 0; i < tyreFrequency; ++i)
		{
			float dummy = 0;
			bezier(dummy, p0b, p1b, p2b, p3b, resb);
			tyre2Jump[i] = resb[1] * 10;
			tyre2t[i] += 0.01;
			if (tyre2t[i] >= 1)
				tyre2t[i] = 0;
		}

		//coin animation
		bezier(tc, p0b, p1b, p2b, p3b, resc);
		tc += 0.01;
		coinJump = resc[1] * 10;
		if (tc > 1)
			tc = 0;

		coinRotation += 1;

		//clock animation
		clockRotation += 1;

		//heart animation
		bezier(td, p0b, p1b, p2b, p3b, resd);
		td += 0.015;
		heartJump = resd[1] * 10;
		if (td > 1)
			td = 0;
		heartWave += heartWaveIncrement;
		if (heartWave > 20 || heartWave < -20)
			heartWaveIncrement = -heartWaveIncrement;



		delay--;

		skyRotation += 0.05;
		if (skyRotation > 360)
			skyRotation = 0;

		if (delay < 0){
			delay = 120;
			seconds--;
		}


		if (policeSpeedUp){

			if (policeAccelerationDelay < 0){
				currentPoliceSpeed = policeMaxSpeed;
				policeCarStepZ = theifCarStepZ;
				policeSpeedUp = false;
			}
			else{
				policeAccelerationDelay--;
			}
		}

		if (theifCarStepZ < theifMaxSpeed){
			theifCarStepZ += theifStepSpeed;


			theifStepSpeed += theifAccelerationValue;

			if (theifStepSpeed > 0.007)
				theifAccelerationValue = 0;

		}

		if (policeCarStepZ < currentPoliceSpeed){
			policeCarStepZ += policeStepSpeed;


			policeStepSpeed += policeAccelerationValue;

			if (policeStepSpeed > 0.007)
				policeAccelerationValue = 0;

		}


		theifCarZ += theifCarStepZ;

		policeCarZ += policeCarStepZ;

		cameraZ = (policeCarZ / 100) - 0.4;
		lookAtZ = cameraZ + 0.4;

		cameraFirstZ = (policeCarZ / 100) + 0.07;
		lookAtFirstZ = cameraFirstZ + 0.43;

		cameraFirstX = (policeCarX / 100) + 0.15;
		lookAtFirstX = cameraFirstX;



		roadScene = policeCarZ / 2000;
		grassScene = (policeCarZ + 3000) / 4000;
		sandScene = (policeCarZ + 2000) / 4000;
		seaScene = (policeCarZ + 1000) / 4000;
		snowScene = policeCarZ / 4000;
		firstScene = policeCarZ / 1000;

		if (snowScene > clock1Index){

			if (snowScene == 0)
				clock1Index = 0;
			else
				clock1Index = clock1Index + 2;

			for (int i = 0; i < clockFrequency; i++){

				if (clock1Index != 0)
					clock1Z[i] = ((rand() % 4000) - 1) + (clock1Index * 4000);
				else
					clock1Z[i] = ((rand() % 3500) + 500);

				clock1X[i] = ((rand() % 70) - 35);
			}
		}

		if (snowScene > clock2Index){

			if (snowScene == 0)
				clock2Index = 1;
			else
				clock2Index = clock2Index + 2;

			for (int i = 0; i < clockFrequency; i++){

				clock2Z[i] = ((rand() % 4000) - 1) + (clock2Index * 4000);

				clock2X[i] = ((rand() % 70) - 35);

			}
		}

		if (snowScene > heart1Index){

			if (snowScene == 0)
				heart1Index = 0;
			else
				heart1Index = heart1Index + 2;

			for (int i = 0; i < heartFrequency; i++){

				if (heart1Index != 0)
					heart1Z[i] = ((rand() % 4000) - 1) + (heart1Index * 4000);
				else
					heart1Z[i] = ((rand() % 3500) + 500);

				heart1X[i] = ((rand() % 70) - 35);
			}
		}

		if (snowScene > heart2Index){

			if (snowScene == 0)
				heart2Index = 1;
			else
				heart2Index = heart2Index + 2;

			for (int i = 0; i < heartFrequency; i++){
				heart2Z[i] = ((rand() % 4000) - 1) + (heart2Index * 4000);
				heart2X[i] = ((rand() % 70) - 35);
			}
		}


		if (firstScene > cone1Index){

			if (firstScene == 0)
				cone1Index = 0;
			else
				cone1Index = cone1Index + 2;

			for (int i = 0; i < coneFrequency; i++){

				if (cone1Index != 0)
					cone1Z[i] = ((rand() % 1000) - 1) + (cone1Index * 1000);
				else
					cone1Z[i] = ((rand() % 600) + 400);

				cone1X[i] = ((rand() % 70) - 35);
			}

		}

		if (firstScene > cone2Index){

			if (firstScene == 0)
				cone2Index = 1;
			else
				cone2Index = cone2Index + 2;


			for (int i = 0; i < coneFrequency; i++){

				cone2Z[i] = ((rand() % 1000) - 1) + (cone2Index * 1000);
				cone2X[i] = ((rand() % 70) - 35);
			}

		}

		if (snowScene > jerken1Index)
		{

			if (snowScene == 0)
				jerken1Index = 0;
			else
				jerken1Index += 2;

			for (int i = 0; i < jerkenFrequency; i++){

				if (jerken1Index != 0)
					jerken1Z[i] = ((rand() % 4000) - 1) + (jerken1Index * 4000);
				else
					jerken1Z[i] = ((rand() % 3500) + 500);

				jerken1X[i] = ((rand() % 70) - 35);
			}
		}

		if (snowScene > jerken2Index)
		{

			if (snowScene == 0)
				jerken2Index = 1;
			else
				jerken2Index += 2;

			for (int i = 0; i < jerkenFrequency; i++){
				jerken2Z[i] = ((rand() % 4000) - 1) + (jerken2Index * 4000);
				jerken2X[i] = ((rand() % 70) - 35);
			}
		}


		if (roadScene > coin1Index){

			if (roadScene == 0)
				coin1Index = 0;
			else
				coin1Index = coin1Index + 2;

			for (int i = 0; i < coinFrequency; i++)
			{
				if (coin1Index != 0)
					coin1Z[i] = ((rand() % 2000) - 1) + (coin1Index * 2000);
				else
					coin1Z[i] = ((rand() % 1500) + 500);

				coin1X[i] = ((rand() % 70) - 35);
			}

		}

		if (roadScene > coin2Index){

			if (roadScene == 0)
				coin2Index = 1;
			else
				coin2Index = coin2Index + 2;

			for (int i = 0; i < coinFrequency; i++)
			{
				coin2Z[i] = ((rand() % 2000) - 1) + (coin2Index * 2000);
				coin2X[i] = ((rand() % 70) - 35);
			}

		}

		if (roadScene % 2 == 0){
			for (int i = 0; i < hummerFrequency; i++)
				hummer1Z[i]--;
		}
		else{
			for (int i = 0; i < hummerFrequency; i++)
				hummer2Z[i]--;
		}

		if (roadScene > hummer1Index){

			if (roadScene == 0)
				hummer1Index = 0;
			else
				hummer1Index = hummer1Index + 2;

			for (int i = 0; i < hummerFrequency; i++){

				if (hummer1Index != 0)
					hummer1Z[i] = ((rand() % 2000) - 1) + (hummer1Index * 2000);
				else
					hummer1Z[i] = ((rand() % 1500) + 500);

				hummer1X[i] = ((rand() % 25) - 0);
			}
		}

		if (roadScene > hummer2Index){

			if (roadScene == 0)
				hummer2Index = 1;
			else
				hummer2Index = hummer2Index + 2;

			for (int i = 0; i < hummerFrequency; i++){
				hummer2Z[i] = ((rand() % 2000) - 1) + (hummer2Index * 2000);
				hummer2X[i] = ((rand() % 25) - 0);
			}
		}

		if (firstScene > tyre1Index)
		{
			if (firstScene == 0)
				tyre1Index = 0;
			else
				tyre1Index += 2;

			for (int i = 0; i < tyreFrequency; i++){
				if (tyre1Index != 0)
					tyre1Z[i] = ((rand() % 1000) - 1) + (tyre1Index * 1000);
				else
					tyre1Z[i] = ((rand() % 500) + 500);
			}
		}

		if (firstScene > tyre2Index)
		{
			if (firstScene == 0)
				tyre2Index = 1;
			else
				tyre2Index += 2;

			for (int i = 0; i < tyreFrequency; i++){
				tyre2Z[i] = ((rand() % 1000) - 1) + (tyre2Index * 1000);
			}
		}


	}
	glutPostRedisplay();

	glutTimerFunc(5, Timer, 0);
}

//=======================================================================
// Keyboard Function
//=======================================================================
void keyboard(unsigned char button, int x, int y)
{
	switch (button)
	{
		case 'c':
			if (game){
				third = !third;
			}
			break;
		case 27:
			exit(0);
			break;
		case 13:
			game = true;
			PlaySound("sounds/startDrive2.wav", NULL, SND_ASYNC | SND_FILENAME);

			if (level == 0 || level == maxLevelNumber + 1)
			{
				life = 3;
				seconds = 120;
				score = 0;
			}

			break;
		default:
			break;
	}

	glutPostRedisplay();
}

//=======================================================================
// Keyboard Up Function
//=======================================================================
void keyboardUp(unsigned char key, int x, int y)
{

}

//=======================================================================
// Arrows Function
//=======================================================================
void arrows(int key, int x, int y)
{
	if (game && policeCarStepZ>0.3){
		switch (key)
		{
			case GLUT_KEY_LEFT:
				leftPressed = true;
				break;
			case GLUT_KEY_RIGHT:
				rightPressed = true;
				break;
		}
	}
	glutPostRedisplay();
}

//=======================================================================
// Arrows Up Function
//=======================================================================
void arrowsUp(int key, int x, int y)
{
	if (game && policeCarStepZ>0.3)
	{
		switch (key)
		{
			case GLUT_KEY_LEFT:
				leftPressed = false;
				break;
			case GLUT_KEY_RIGHT:
				rightPressed = false;
				break;
		}
	}
	glutPostRedisplay();
}
//=======================================================================
// Mouse Function
//=======================================================================
void mouseListener(int button, int state, int x, int y)
{

}


//=======================================================================
// Models Loading Function
//=======================================================================
void LoadModels()
{
	// Loading Model files
	theif_car.Load("Models/theif_car/audi a5.3ds");
	police_car.Load("Models/police_car/PoliceCar.3ds");
	street_lamp.Load("Models/street_lamp/lamp.3ds");
	heart.Load("Models/heart/Heart.3ds");
	timer.Load("Models/clock/Clock_3ds.3ds");
	coin.Load("Models/coin/Clock_3ds.3ds");
	cone.Load("Models/cone/cone_3ds.3ds");
	jerrycan.Load("Models/jerrycan/Jerrycan.3ds");
	tyre.Load("Models/tyre/Tire Vic Rich N251012.3DS");
	truck.Load("Models/H2/H2.3DS");
	hittostart.Load("Models/hittostart/hittostart2.3ds");
	level1.Load("Models/level/level1.3ds");
	level2.Load("Models/level/level2.3ds");
	level3.Load("Models/level/level3.3ds");
	level4.Load("Models/level/level4.3ds");
	level5.Load("Models/level/level5.3ds");
	gameOver.Load("Models/gameover/gameover1.3ds");
	youWin.Load("Models/youwin/youwin.3ds");
	snowMan.Load("Models/snowman/snowman.3ds");
	boat.Load("Models/boat/Yacht.3ds");
	ship.Load("Models/ship/Galleon.3ds");
	bush1.Load("Models/bush1/Bush1.3ds");
	bush2.Load("Models/bush2/Bush rose Sanina N060617.3DS");
	camel.Load("Models/camel/Camel_By_Sielxm3d.3ds");
	rock1.Load("Models/rock1/Rock1.3ds");
	palm.Load("Models/palmTree1/palmtree.3ds");


	// Loading texture files
	road.Load("Textures/road.bmp");
	rasif.Load("Textures/rasif.bmp");
	white.Load("Textures/white.bmp");
	grass.Load("Textures/grass.bmp");
	sand.Load("Textures/sand.bmp");
	sea.Load("Textures/sea.bmp");
	snow.Load("Textures/snow.bmp");

	loadBMP(&sky, "Textures/sky4-jpg.bmp", true);
}

//=======================================================================
// Print text on screen
//=======================================================================
void print(int x, int y, int z, char *string)
{
	int len, i;

	glRasterPos3f(x, y, z);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

//=======================================================================
// Main Function
//=======================================================================

//Mix_Music* music1;





//std::unique_ptr<DirectX::SoundEffect> m_explode;
//std::unique_ptr<DirectX::SoundEffect> m_ambient;



void main(int argc, char** argv)
{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(width, height);

	glutInitWindowPosition(0, 0);

	glutCreateWindow("Chase Fel Seka");

	glutDisplayFunc(Display);
	glutTimerFunc(0, Timer, 0);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(arrows);
	glutSpecialUpFunc(arrowsUp);
	glutMouseFunc(mouseListener);

	myInit();
	PlaySound(TEXT("police.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	//PlayMusic

	LoadModels();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}