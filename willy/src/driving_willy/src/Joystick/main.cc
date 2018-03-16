#include <SDL/SDL.h>
#include <sstream>
#include <fstream>

#include "src/joystick.h"
#include "src/glhelper.h"

#define WIDTH 1280
#define HEIGHT 720
#define BPP 32

void saveTGA(unsigned char* buffer) {
	static int i = 0;
	std::stringstream out;
	out << "capture" << (i++) << ".tga";
	std::string s = out.str();
	
	glReadPixels(0, 0, WIDTH, HEIGHT, GL_BGRA, GL_UNSIGNED_BYTE, buffer);
	std::fstream of(s.c_str(), std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
	char header[18] = { 0 };
	header[2] = 2;
	header[12] = WIDTH & 0xff;
	header[13] = WIDTH >> 8;
	header[14] = HEIGHT & 0xff;
	header[15] = HEIGHT >> 8;
	header[16] = 32;
	of.write(header, 18);
	of.write((char *)buffer, WIDTH * HEIGHT * 4);
}

int main(int argc, char *argv[]) {
	cJoystick js; joystick_position jp[2];

	unsigned char *buffer = new unsigned char[WIDTH * HEIGHT * 4];

	bool active = true, fullscreen = false, grab = false;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface *screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, (fullscreen ? SDL_FULLSCREEN : 0) | SDL_HWSURFACE | SDL_OPENGL);
	SDL_Event event;

	setupOrtho(WIDTH, HEIGHT);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	while(active) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				active = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_g:
					grab = true;
					break;
				case SDLK_f:
					fullscreen ^= true;
					screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, (fullscreen ? SDL_FULLSCREEN : 0) | SDL_HWSURFACE | SDL_OPENGL);
					break;
				}
				break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);

		renderCircle(  WIDTH/4.0f, HEIGHT/2.0f, WIDTH/6.0f, 10, 0.5, 1.0, 0.5);
		renderCircle(3*WIDTH/4.0f, HEIGHT/2.0f, WIDTH/6.0f, 10, 0.5, 1.0, 0.5);

		renderSquare(  WIDTH/4.0f-WIDTH/6.0f, HEIGHT/2+WIDTH/6.0f,   WIDTH/4.0f+WIDTH/6.0f, HEIGHT/2.0f-WIDTH/6.0f, 0.5, 0.5, 1.0);
		renderSquare(3*WIDTH/4.0f-WIDTH/6.0f, HEIGHT/2+WIDTH/6.0f, 3*WIDTH/4.0f+WIDTH/6.0f, HEIGHT/2.0f-WIDTH/6.0f, 0.5, 0.5, 1.0);
		
		jp[0] = js.joystickPosition(0);
		jp[1] = js.joystickPosition(1);

		renderCircle(  WIDTH/4.0f + cos(jp[0].theta)*jp[0].r*WIDTH/6.0f, HEIGHT/2.0f + sin(jp[0].theta)*jp[0].r*WIDTH/6.0f, WIDTH/48.0f, 10, 0.5, 0.5, 1.0);
		renderCircle(3*WIDTH/4.0f + cos(jp[1].theta)*jp[1].r*WIDTH/6.0f, HEIGHT/2.0f + sin(jp[1].theta)*jp[1].r*WIDTH/6.0f, WIDTH/48.0f, 10, 0.5, 0.5, 1.0);

		renderCircle(  WIDTH/4.0f + jp[0].x*WIDTH/6.0f, HEIGHT/2 + jp[0].y*WIDTH/6.0f, WIDTH/48.0f, 10, 1.0, 0.5, 1.0);
		renderCircle(3*WIDTH/4.0f + jp[1].x*WIDTH/6.0f, HEIGHT/2 + jp[1].y*WIDTH/6.0f, WIDTH/48.0f, 10, 1.0, 0.5, 1.0);
		
		glBegin(GL_LINES);
		glColor3f(0.5, 0.5, 1.0);
		glVertex3f(  WIDTH/4.0f, HEIGHT/2.0f, 0);
		glVertex3f(  WIDTH/4.0f + cos(jp[0].theta)*jp[0].r*WIDTH/6.0f, HEIGHT/2.0f + sin(jp[0].theta)*jp[0].r*WIDTH/6.0f, 0);
		glColor3f(0.5, 0.5, 1.0);
		glVertex3f(3*WIDTH/4.0f, HEIGHT/2.0f, 0);
		glVertex3f(3*WIDTH/4.0f + cos(jp[1].theta)*jp[1].r*WIDTH/6.0f, HEIGHT/2.0f + sin(jp[1].theta)*jp[1].r*WIDTH/6.0f, 0);
		glColor3f(1.0, 0.5, 1.0);
		glVertex3f(  WIDTH/4.0f, HEIGHT/2.0f, 0);
		glVertex3f(  WIDTH/4.0f + jp[0].x*WIDTH/6.0f, HEIGHT/2.0f + jp[0].y*WIDTH/6.0f, 0);
		glColor3f(1.0, 0.5, 1.0);
		glVertex3f(3*WIDTH/4.0f, HEIGHT/2.0f, 0);
		glVertex3f(3*WIDTH/4.0f + jp[1].x*WIDTH/6.0f, HEIGHT/2.0f + jp[1].y*WIDTH/6.0f, 0);
		glEnd();

		SDL_GL_SwapBuffers();

		if (grab) {
			grab = false;
			saveTGA(buffer);
		}
	}

	SDL_Quit();

	delete[] buffer;

	return 0;
}