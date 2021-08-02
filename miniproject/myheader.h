#pragma once
// CONSTANTS

//screen size
#define SCREEN_X 1250
#define SCREEN_Y 750


//menu
int background;
int font;
int box;


//key
int key1 = 1;
int flag = 0;
int m = 0;

//colors
float R = 0.3, G = 0.5, B = 0.8;
float red = 0.9, blue = 0.9, green = 0.9;
float red1 = 0.0, blue1 = 0.0, green1 = 0.0;
float redA = 0.0, blueA =0.0, greenA =0.0;



//initial point
#define OFFSET_X 50


//arrow size
#define ARROW_LENGTH 50

//used for displaying last operation
#define ENQUEUE1 19
#define ENQUEUE2 20
#define DEQUEUE1 38
#define DEQUEUE2 39
#define NO_OP 45

//for setting position instruction and last operation
#define OPERATION_POSITION_X SCREEN_X/4+SCREEN_X/20
#define OPERATION_POSITION_Y SCREEN_Y/5

//enter_str position on the screen
#define ENTER_POSITION_Y SCREEN_Y-40 // y=500-60=440 is set as ENTER_POSITION_Y
#define ENTER_POSITION_X OFFSET_X+400  //x=offset=50 is set as ENTER_POSITION_X

//To display message 
#define EMPTY 0
#define FULL 1
#define NO_MESSAGE 2 // we enqueing no queue status will be display until its full or empty

static int MAX;		// MAXIMUM NUMBER OF ELEMENTS IN THE QUEUE. TAKEN AS INPUT

int DIST = SCREEN_X - 2 * OFFSET_X;//2*offset_x then sub with screen_x

int f = 0;	// FRONT OF QUEUE
int b = 0;	// REAR OF QUEUE
int array = 0;


int YD = SCREEN_Y / 12;// just a random height. HEIGHT OF EACH ELEMENT (BOX) IN THE QUEUE

//font 
double FONT_ADJUST = 10;//DENOMINATOR OF FONT_RATIO.LARGER THE VALUE, LARGER THE FONT (FONT SIZE adjusting)
double FONT_RATIO = YD / FONT_ADJUST;  // SETS THE SIZE OF THE FONT

//used for displaying last operation
int enqORdq = NO_OP;			// indicates what the last operation was.

// end of all Constants
char enter_str[10000];
char blinking[2] = { '_', 0 }; //array holding 2 value
char displayString[10003];
int start_of_num;
int cnt_of_chars = 0;
int message = EMPTY;

// Each element of the queue is encapsulated into a structure.
struct elem {
	float r, g, b; // filling colors
	float rl, gl, bl; // for outlines
	float x1, x2;	// start and end x positions
	char num[11];
};
struct elem queue[10];// queue[] represents boxes which we are drawing  

