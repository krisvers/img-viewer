#include <SDL2/SDL.h>
#include <stdio.h>

SDL_Surface * surface;
SDL_Event event;

void draw(unsigned int x, unsigned int y, unsigned int color) {
	if (x >= (unsigned int) surface->w || y >= (unsigned int) surface->h) {
		return;
	}

	((unsigned int *) surface->pixels)[x + (y * surface->w)] = color;
}

void draw_bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char * bytes, unsigned char bpp) {
	unsigned int color;
	for (unsigned int w = 0; w < width; ++w) {
		for (unsigned int h = 0; h < height; ++h) {
			if (bpp == 8) {
				color = bytes[w + (h * width)];
			} else if (bpp == 16) {
				color = (bytes[(w + (h * width)) * (bpp / 8) + 1] << 8) | (bytes[(w + (h * width)) * (bpp / 8)]);
			} else if (bpp == 24) {
				color = bytes[(w + (h * width)) * bpp + 2] | bytes[(w + (h * width)) * bpp + 1] | bytes[(w + (h * width)) * bpp];
			} else {
				color = bytes[(w + (h * width)) * bpp + 3] | bytes[(w + (h * width)) * bpp + 2] | bytes[(w + (h * width)) * bpp + 1] | bytes[(w + (h * width)) * bpp];
			}
			draw(x + w, y + h, color);
			printf("%x\n", color);
		}
	}
}

int main(void) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window * win = SDL_CreateWindow(
		"image viewer", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 800, 800,
		0
	);
	surface = SDL_GetWindowSurface(win);

	unsigned int img[4] = {
		0xFF0000, 0x00FF00,
		0x0000FF, 0xFF00FF
	};

	draw_bitmap(0, 0, 2, 2, img, 32);

	while (event.type != SDL_QUIT) {
		SDL_UpdateWindowSurface(win);
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				event.type = SDL_QUIT;
			}
		}
	}

	SDL_DestroyWindow(win);
	SDL_Quit();
}
