#include "display.h"

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

void dispState(SDL_Surface *screen, s_neuralSystem *sys){
	
}

void dispSquare(SDL_Surface *screen, int x, int y, double color){
		int X,Y;

		for(Y=0;Y<Size;Y++){
			for(X=0;X<Size;X++){
				setPixel(screen,x*Size+X,y*Size+Y,(int)color+((int)color<<8)+((int)color<<16));
			}
		}
}

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel){

	Uint8 *p;
	int bpp; 
	if(x>=0 && y>=0 && x<surface->w && y<surface->h)
	{
		bpp = surface->format->BytesPerPixel;

		p = (Uint8 *)surface->pixels+y*surface->pitch+x*bpp;

		switch(bpp) 
		{
			case 1:
				*p = pixel;
				break;

			case 2:
				*(Uint16 *)p = pixel;
				break;

			case 3:
				if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
					p[0] = (pixel >> 16) & 0xff;
					p[1] = (pixel >> 8) & 0xff;
					p[2] = pixel & 0xff;
				} else {
					p[0] = pixel & 0xff;
					p[1] = (pixel >> 8) & 0xff;
					p[2] = (pixel >> 16) & 0xff;
				}
				break;

			case 4:
				*(Uint32 *)p = pixel;
				break;
		}
	}
}
