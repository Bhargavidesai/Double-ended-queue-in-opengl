#include <stdio.h>//c header
#include <string.h>//for string functions like string copy etc
#include <stdlib.h>//for exit(0)
#include <glut.h>//opengl
#include <ctype.h>//for iskey() function
#include "myheader.h"//initializations


//function declaration
void frontEnqueue(char*);
void frontpage();
void display1();
void help();
void mainmenu();
void colormenu();
void size_entering();
void mymouse(int button, int state, int ax, int ay);

// initialize the values requried
void myinit()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, SCREEN_X, 0.0, SCREEN_Y);
}





//function to draw a square
void square(int x1, int y1, int x2, int y2) {
	glBegin(GL_POLYGON);//drawing the square so polygon primitive
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glVertex2f(x2, y1);
	glEnd();
}






//function to draw the outline the square
void drawOutline(int x1, int y1, int x2, int y2) {
	glLineWidth(3.0);
		glBegin(GL_LINE_LOOP);//drawing border line so LINES primitive
		glVertex2f(x1, y1);
		glVertex2f(x1, y2);
		glVertex2f(x2, y2);
		glVertex2f(x2, y1);
		glEnd();
	
	}








//function to draw a string to the output screen
void drawString(const char* str, double x=0 , double y=0, double z=0 , double size = 3.0) {
	glRasterPos3f(x, y, z);
	glColor3f(redA, greenA, blueA);// color to the alphabets
	int len = strlen(str);//stores the length of string which is passed
	//glutbitmapcharecter render the charecter 
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
}







//function to draw the queue arrow anywhere requried
void drawArrow(int x1, const char* s) {
	glBegin(GL_LINES);//for drawing line 
	glVertex2f(x1, 3 * SCREEN_Y / 4);//y1 point
	glVertex2f(x1, 3 * SCREEN_Y / 4 - ARROW_LENGTH);//y2=y1-arrowlength
	glEnd();
	glBegin(GL_TRIANGLES);//for drawing triangle
	glVertex2f(x1, 3 * SCREEN_Y / 4 - ARROW_LENGTH);//triangle base should touch the line so same x and y is used as above
	glVertex2f(x1 - ARROW_LENGTH / 4 , 3 * SCREEN_Y / 4 - ARROW_LENGTH + ARROW_LENGTH / 4);//left side points
	glVertex2f(x1 + ARROW_LENGTH  / 4, 3 * SCREEN_Y / 4 - ARROW_LENGTH + ARROW_LENGTH / 4);//right side points
	glEnd();
	if (strcmp(s, "Rear"))//REAR string position on the screen
		drawString(s, x1 - ARROW_LENGTH / 3, 3 * SCREEN_Y / 4 + ARROW_LENGTH / 2);
	else//FRONT string position on the screen 
		drawString(s, x1 - ARROW_LENGTH / 3, 3 * SCREEN_Y / 4 + ARROW_LENGTH / 9);
}







//function to display all things to the screen
void display() {
	if (m == 0) {
		m = 1;
		glutAddSubMenu("Box color", box);
		glutAddSubMenu("Font color", font);
		glutAddSubMenu("Background color", background);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
	}
	glClearColor(R, G, B, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	strcpy_s(displayString, enter_str);//copy enter_str to displayString 
	strcat_s(displayString, blinking);//concatinating displaystring with blinking

	//position of displayString on the screen
	drawString(displayString, ENTER_POSITION_X, ENTER_POSITION_Y, 1.0 / (FONT_RATIO));
		for (int i = 0; i < b; i++) {
			glColor3f(queue[i].r, queue[i].g, queue[i].b);
			square(queue[i].x1, SCREEN_Y / 2, queue[i].x2, SCREEN_Y / 2 + YD);
			glColor3f(queue[i].rl, queue[i].gl, queue[i].bl);
			drawOutline(queue[i].x1, SCREEN_Y / 2, queue[i].x2, SCREEN_Y / 2 + YD);
			
			//here we set the position of the entered number in the box
			if (queue[i].r ==red || queue[i].b == blue || queue[i].g == green) {
				double ln = strlen(queue[i].num);
				double width = queue[i].x2 - queue[i].x1;
				double step = width / (ln + 1);
				double step_y = YD / 4;
				drawString(queue[i].num, queue[i].x1 + step+9, SCREEN_Y / 2 + step_y+6, 1.0 / FONT_RATIO);
			}
			
		}
		

		if (message != EMPTY) {
			//for drawing arrow
			drawArrow(queue[f].x1 + OFFSET_X / 3, "Front");
			drawArrow(queue[b].x1 + OFFSET_X / 3, "Rear");
		}
	//displays the previous operation by comparing values
	if (enqORdq == ENQUEUE1 )
		drawString("OPERATION: ENQUEUE FROM BACK", OPERATION_POSITION_X+20, OPERATION_POSITION_Y + 20, 1.0 / (FONT_RATIO));
	else if (enqORdq == ENQUEUE2)
		drawString("OPERATION: ENQUEUE FROM FRONT", OPERATION_POSITION_X + 20, OPERATION_POSITION_Y + 20, 1.0 / (FONT_RATIO));
	else if (enqORdq == DEQUEUE1)
		drawString("OPERATION: DEQUEUE FROM FRONT", OPERATION_POSITION_X+20, OPERATION_POSITION_Y + 20, 1.0 / (FONT_RATIO));
	else if (enqORdq == DEQUEUE2)
		drawString("OPERATION: DEQUEUE FROM BACK", OPERATION_POSITION_X+20, OPERATION_POSITION_Y + 20, 1.0 / (FONT_RATIO));
	else
		drawString("OPERATION: NO OPERATION YET", OPERATION_POSITION_X+20, OPERATION_POSITION_Y + 20, 1.0 / (FONT_RATIO));

	//message
	if (message == EMPTY) {
		drawString("QUEUE EMPTY....!!!", OPERATION_POSITION_X + 90, OPERATION_POSITION_Y-30, 1.0 / (FONT_RATIO));
	}
	else if (message == FULL) {
		drawString("QUEUE FULL....!!!", OPERATION_POSITION_X + 90, OPERATION_POSITION_Y-30, 1.0 / (FONT_RATIO));
	}
	glFlush();
	glutPostRedisplay();
}





//adding datavalue from the back end of the queue
void backEnqueue(char* s) {
	int len = strlen(s);
	int i; 
	//if b is less then max then we can insert from back
	if (b < MAX) {
		//copies the (s+i) to queue[b].num for displaying
		len = strlen(s);
		for (i = 0; i < len - 1 && s[i] == '0'; i++);
		strcpy_s(queue[b].num, s + i);

		//setting color to the box
		queue[f].r = red;
		queue[f].g = green;
		queue[f].b = blue;

		queue[f].rl = red1;
		queue[f].gl = green1;
		queue[f].bl = blue1;

		//as we are inserting from back 
		b++;

		//displaying messages
		enqORdq = ENQUEUE1;
		message = NO_MESSAGE;
	}
	else if (b == MAX && f != 0)
	{
		frontEnqueue(s);
	}
	if (b == MAX && f == 0)
		message = FULL;
}








//adding datavalue from the front end of the queue
void frontEnqueue(char* s) {
	int len = strlen(s);
	int i;
	if (f > 0) {
		len = strlen(s);
		f--;
		//copies the (s+i) to queue[f].num for displaying
		for (i = 0; i < len - 1 && s[i] == '0'; i++);
		strcpy_s(queue[f].num,s + i);

		//box coloring
		queue[f].r = red;
		queue[f].g = green;
		queue[f].b = blue;
		//border color
		queue[f].rl = red1;
		queue[f].gl = green1;
		queue[f].bl = blue1;

		//for displaying msgs
		enqORdq = ENQUEUE2;
		message = NO_MESSAGE;
	}
	else if (f == 0 && b != MAX)
	{
		backEnqueue(s);
	}
	if (f == 0 && b==MAX)
		message = FULL;
}






// removing datavalue form the front end of the queue
void frontDequeue(void) {
	if (b <= 0 || b <= f) {
		message = EMPTY;
		return;
	}

	////makes the box invisible by setting color as background color
	queue[f].r = R;
	queue[f].g = G;
	queue[f].b = B;

	queue[f].rl = R;
	queue[f].gl = G;
	queue[f].bl = B;

	f++;
	//for displaying operation performed
	enqORdq = DEQUEUE1;
	message = NO_MESSAGE;

	if (b <= f) {
		message = EMPTY;
	}

}







//removing datavalue from the back end of the queue
void backDequeue(void) {
	if (f >= MAX || f >= b) {
		message = EMPTY;
		return;
	}

	b--;

	//for displaying operation performed
	enqORdq = DEQUEUE2;
	message = NO_MESSAGE;

	if (f >= b) {
		message = EMPTY;
	}
}

















//funtion to get input from the user by keyboard
void mykey(unsigned char key, int x, int y) {

	int len = strlen(enter_str);

	//executes the specified fucntion when particular key is pressed
	if ((key == 'F' || key == 'f') && (cnt_of_chars == 0))//cnt_of_chars is entered charecter to insert while deleting it should be empty means 0 
		frontDequeue();
	if ((key == 'B' || key == 'b') && (cnt_of_chars == 0))
		backDequeue();
	if ((key == 'E' || key == 'e') && (cnt_of_chars == 0))
		exit(0);


	//is didgit checks the condition that entered value is a digit, this uses ctype library
	//enter_str length is 24 we can add only 2 digit number into the box
	else if (isdigit(key) && strlen(enter_str) <= 25) {
		enter_str[len + 1] = '\0';//making next blank so that blink(_) will appear there
		enter_str[len] = key;//placing the entered number in that position 
		cnt_of_chars++;//we have taken input so char count is increamented
	}

	// if we backspace while entering the digits to be inserted then this condition will be executed
	else if (key == '\b' && len > start_of_num) {
		enter_str[len - 1] = '\0';//removes the element by making it null
		cnt_of_chars--;//char count will be decremented
	}
	//executes the specified fucntion when particular key is pressed
	else if (key == 'i' || key == 'I') {
		//box color
		queue[b].r = red;
		queue[b].g = green;
		queue[b].b = blue;
		//border color
		queue[b].rl = red1;
		queue[b].gl = green1;
		queue[b].bl = blue1;
		char newint[4];
		strncpy_s(newint, enter_str + start_of_num,3);
		// this condition makes sure that equeue happens only if number is entered
		if (newint[0]) {
			backEnqueue(newint);//calls function
			enter_str[start_of_num] = '\0';//after inserting entered number position will be blank
		}
		cnt_of_chars = 0;//set to 0
	}
	else if (key == 'o' || key == 'O') {
		//box color
		queue[b].r = red;
		queue[b].g = green;
		queue[b].b = blue;
		//border color
		queue[b].rl = red1;
		queue[b].gl = green1;
		queue[b].bl = blue1;
		char newint[4];
		strncpy_s(newint, enter_str + start_of_num, 3);
		// this condition makes sure that equeue happens only if number is entered
		if (newint[0]) {
			frontEnqueue(newint);//calls function
			enter_str[start_of_num] = '\0';//after inserting entered number position will be blank
		}
		cnt_of_chars = 0;//set to 0
	}
	//for space press
	else if (key == 13 && (key1==1 || key1==2 || key1==3) )
	{
		key1 = 2;
		display1();
	}
	glutPostRedisplay();//displays changed that had happend
}



void bgcolor(int id)
{
	switch (id)
	{
	case 1: 
		R = 0.3;
		G = 0.5;
		B = 0.8;
		glutPostRedisplay();
		break;
	case 2: 
		R = 0.7;
		G = 0.5;
		B = 0.8;
		glutPostRedisplay();
		break;
	case 3:  
		R = 0.7;
		G = 0.3;
		B = 0.5;
		glutPostRedisplay();
		break;
	}
	for (int i = 0; i < f; i++) {
		queue[i].r = R;
		queue[i].g = G;
		queue[i].b = B;

		queue[i].rl = R;
		queue[i].gl = G;
		queue[i].bl = B;
	}
}

void fontcolor(int id)
{
	switch (id)
	{
	case 4: // change color to red
		redA = 1.0;
		greenA = 1.0;
		blueA = 1.0;
		glutPostRedisplay();
		break;
	case 5:
		redA = 0.0;
		greenA = 0.0;
		blueA = 0.0;
		glutPostRedisplay();
		break;
	case 6:
		redA = 0.3;
		greenA = 0.0;
		blueA = 0.1;
		glutPostRedisplay();
		break;
	}
}

void boxcolor(int id)
{
	switch (id)
	{
	case 7: // change color to red
		red = 0.9;
		green = 0.9;
		blue = 0.9;
		glutPostRedisplay();
		break;
	case 8:
		red = 1.0;
		green = 0.8;
		blue = 0.8;
		glutPostRedisplay();
		break;
	case 9:
		red = 1.0;
		green = 0.8;
		blue = 0.6;
		glutPostRedisplay();
		break;
	}


}

void size_entering()
{
	printf("\n\n\n");
	printf("------------------------------------\n");
	printf("Simulation of  deQueue in OpenGL\n");
	printf("------------------------------------\n\n");
	printf("Enter the number of elements in the deQueue\n(Not greater than 9 and not lesser than 2):\n");
	scanf_s("%d", &MAX);
	while (MAX > 9 || MAX < 2) {
		printf("ERROR: Invalid value! \nEnter again: ");
		scanf_s("%d", &MAX);
	}
	// creates color of cube and outline color
	//box color
	int i;
	for (i = 0; i < 9; i++) {
		//box color
		queue[i].r = red;
		queue[i].g = green;
		queue[i].b = blue;
		//border color
		queue[i].rl = red1;
		queue[i].gl = green1;
		queue[i].bl = blue1;
	}

	float step = (DIST / MAX) - 25;
	queue[0].x1 = OFFSET_X + 20 + (MAX * 3);//1st point
	queue[0].x2 = queue[0].x1 + step;//width of the box

	//for i=0 we already have so we will start from i=1
	for (i = 1; i <= 9; i++) {
		queue[i].x1 = queue[i - 1].x1 + step;//end of previous box is x1 of next box
		queue[i].x2 = queue[i].x1 + step;
	}
	printf("\n\nVALUE ACCEPTED! Program Running...\n");
}

void colormenu()
{

		//MENU
		background = glutCreateMenu(bgcolor);
		glutAddMenuEntry("Blue", 1);
		glutAddMenuEntry("Purple", 2);
		glutAddMenuEntry("Pink", 3);
		glutCreateMenu(bgcolor);
		font = glutCreateMenu(fontcolor);
		glutAddMenuEntry("Brown", 6);
		glutAddMenuEntry("White", 4);
		glutAddMenuEntry("Black", 5);
		glutCreateMenu(fontcolor);
		box = glutCreateMenu(boxcolor);
		glutAddMenuEntry("Grey", 7);
		glutAddMenuEntry("Pink", 8);
		glutAddMenuEntry("Orange", 9);
		glutCreateMenu(boxcolor);

}





//main funtion where all the action takes place
int  main(int argc, char** argv) {
	strcpy_s(enter_str, "Enter Element to Queue: ");//copy string to enter_str
	start_of_num = strlen("Enter Element to Queue: ");//store length of string in start_of_num
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_X, SCREEN_Y);
	glutInitWindowPosition(260.0,60.0);
	glutCreateWindow("Double Ended Queue");
	myinit();
	glutDisplayFunc(display1);
	glutKeyboardFunc(mykey);
	glutMouseFunc(mymouse);
	colormenu();
	glutMainLoop();
	return 0;
}


void display1() {
	switch (key1)
	{
	case 1:
		frontpage();
		break;
	case 2:
		mainmenu();
		break;
	case 3:
		help();
		break;

	case 4:
		if (flag == 0) {
			flag = 1;
			size_entering();
		}
		display();
		break;
	case 5:
		exit(0);
	}
	glFlush();
	
}











void frontpage()
{
	glClearColor(0.9, 0.9, 0.9, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0, 1);//string color
	drawString("SDM INSTITUTE OF TECHNOLOGY", OPERATION_POSITION_X+50, OPERATION_POSITION_Y+500, 0.0);

	glColor3f(0.7, 0, 1);
	drawString("DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING", OPERATION_POSITION_X-70, OPERATION_POSITION_Y+450, 0.0);
	
	glColor3f(1, 0.5, 0);
	drawString("MINI PROJECT ON", OPERATION_POSITION_X +125, OPERATION_POSITION_Y + 370, 0.0);
	
	glColor3f(0.9, 0.1, 0.3);
	drawString("********** SIMULATION  OF  DOUBLE ENDED QUEUE **********", OPERATION_POSITION_X-100, OPERATION_POSITION_Y + 320, 0.0);
	
	glColor3f(0.7, 0, 0.5);
	drawString("SUBMITTED BY:", ENTER_POSITION_X-300, ENTER_POSITION_Y - 340, 0.0);
	
	glColor3f(0.0, 0, 1);
	drawString("BHARGAVI P DESAI \t\t 4SU18CS018", ENTER_POSITION_X-300, ENTER_POSITION_Y - 380, 0.0);
	
	glColor3f(0.0, 0, 1);
	drawString("B CHHAYASHREE \t\t   4SU18CS015", ENTER_POSITION_X-300, ENTER_POSITION_Y - 420, 0.0);
	
	glColor3f(0.7, 0, 0.5);
	drawString("GUIDED BY:", ENTER_POSITION_X + 350, ENTER_POSITION_Y - 340, 0.0);
	
	glColor3f(0.0, 0, 1);
	drawString("MR.ARJUN.K", ENTER_POSITION_X + 350, ENTER_POSITION_Y - 380, 0.0);
	
	glColor3f(0.3, 0.4, 0.2);
	drawString("[PRESS ENTER TO CONTINUE]",(SCREEN_X/2)-170,SCREEN_Y-640, 0.0);
	
	glFlush();
	glutSwapBuffers();
}


void help()
{
	glClearColor(0.9, 0.9, 0.9, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);//string color
	drawString("HELP FOR USER", OPERATION_POSITION_X + 145, OPERATION_POSITION_Y + 480, 0.0);//position and string
	glColor3f(1, 0.5, 0);
	glColor3f(0.9, 0.1, 0.3);
	drawString("********** SIMULATION OF DOUBLE ENDED QUEUE **********", OPERATION_POSITION_X-80, OPERATION_POSITION_Y + 380, 0.0);
	//instructions position on the screen
	glColor3f(1, 0, 0.4);
	drawString("Instructions:", OPERATION_POSITION_X -80, OPERATION_POSITION_Y + 280, 1.0 / (1.5 * FONT_RATIO));
	glColor3f(0.5, 0, 0);
	drawString("*  I or i  :  Enqueue from back", OPERATION_POSITION_X +70, OPERATION_POSITION_Y + 200, 1.0 / (2 * FONT_RATIO));
	glColor3f(0.5, 0, 0);
	drawString("*  O or o  :  Enqueue from front", OPERATION_POSITION_X +70, OPERATION_POSITION_Y+160, 1.0 / (2 * FONT_RATIO));
	glColor3f(0.5, 0, 0);
	drawString("*  F or f  :  Dequeue from front.", OPERATION_POSITION_X +70, OPERATION_POSITION_Y+120, 1.0 / (2 * FONT_RATIO));
	glColor3f(0.5, 0, 0);
	drawString("*  B or b  :  Dequeue from back.", OPERATION_POSITION_X +70, OPERATION_POSITION_Y +80, 1.0 / (2 * FONT_RATIO));
	glColor3f(0.5, 0, 0);
	drawString("*  Right_MouseClick : Color change. ", OPERATION_POSITION_X +70, OPERATION_POSITION_Y +40, 1.0 / (2 * FONT_RATIO));
	glColor3f(0.5, 0, 0);
	drawString("*  E or e  :  Exit. ", OPERATION_POSITION_X + 70, OPERATION_POSITION_Y , 1.0 / (FONT_RATIO));
	glColor3f(0, 0, 0);
	drawString("Press ENTER to go BACK", OPERATION_POSITION_X + 90, OPERATION_POSITION_Y - 80, 1.0 / (FONT_RATIO));
	glFlush();

}

void mainmenu()
{
	
	glClearColor(0.9, 0.9, 0.9, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);//string color
	drawString("MENU", OPERATION_POSITION_X + 205, OPERATION_POSITION_Y + 450, 0.0);//position and string
	glColor3f(1, 0.5, 0);
	glColor3f(0.9, 0.1, 0.3);
	drawString("********** SIMULATION OF DOUBLE ENDED QUEUE **********", OPERATION_POSITION_X - 80, OPERATION_POSITION_Y + 360, 0.0);
    //1
	glColor3f(0.0, 0.0, 0.0);
	drawOutline(454,(SCREEN_Y / 2) + 3, 746,SCREEN_Y / 2 + YD - 3);
	glColor3f(0.9, 0.6,0.5);
	square(455, (SCREEN_Y / 2)+3, 745, SCREEN_Y / 2 + YD-3);//box2
	glColor3f(0.0, 0.0, 0.0);
	drawString("NEW SIMULATION", 500,20+SCREEN_Y / 2,0.0);//label
	//2
	glColor3f(0.0, 0.0, 0.0);
	drawOutline(454,(SCREEN_Y / 2) - 97, 746,SCREEN_Y / 2 - 100 + YD - 3);
	glColor3f(0.9, 0.6, 0.5);
	square(455, (SCREEN_Y / 2)-97, 745, SCREEN_Y / 2-100 + YD-3);//box2
	glColor3f(0.0, 0.0, 0.0);
	drawString("HELP", 560, (SCREEN_Y / 2)-80, 0.0);//label
	//3
	glColor3f(0.0, 0.0, 0.0);
	drawOutline(454,SCREEN_Y / 2 - 197, 746,SCREEN_Y / 2 - 200 + YD - 3);
	glColor3f(0.9, 0.6, 0.5);
	square(455, SCREEN_Y / 2-197, 745, SCREEN_Y / 2-200 + YD-3);//box2
	glColor3f(0.0, 0.0, 0.0);
	drawString("QUIT", 560, (SCREEN_Y / 2) -180, 0.0);//label

	glFlush();
	glutSwapBuffers();
}





void mymouse(int button, int state, int x, int y) {
	if (key1 == 2) {
		y = SCREEN_Y - y;
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && x > (455) && x < (745) && y >((SCREEN_Y / 2) + 3) && y < (SCREEN_Y / 2 + YD - 3)) //new
		{

			glClear(GL_COLOR_BUFFER_BIT);
			key1 = 4;
			display1();
		}
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && x > (455) && x < (745) && y >((SCREEN_Y / 2) - 97) && y < (SCREEN_Y / 2 - 100 + YD - 3)) //Help
		{

			glClear(GL_COLOR_BUFFER_BIT);
			key1 = 3;
			display1();
		}
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN) && x > (455) && x < (745) && y >(SCREEN_Y / 2 - 197) && y < (SCREEN_Y / 2 - 200 + YD - 3)) //exit
		{

			glClear(GL_COLOR_BUFFER_BIT);
			key1 = 5;
			display1();
		}
	}
}
	
