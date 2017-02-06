#include "SDL2/SDL.h"
#include <math.h>
#include <memory.h>
#include <time.h>
#include <stdlib.h>
#ifdef _WIN32
#pragma  comment(lib , "sdl2.lib")
#define  TOUCH_MOTION   SDL_MOUSEMOTION
#define  TOUCH_DOWN     SDL_MOUSEBUTTONDOWN
#define  TOUCH_UP       SDL_MOUSEBUTTONUP
#define  _CW_    800
#define  _CH_    600
#define  TX()    e->motion.x
#define  TY()    e->motion.y
#define  TI()    0
#else
#define  TOUCH_MOTION   SDL_FINGERMOTION
#define  TOUCH_DOWN     SDL_FINGERDOWN
#define  TOUCH_UP       SDL_FINGERUP
#define  _CW_   0
#define  _CH_   0
#define  TX()       (width*e->tfinger.x) 
#define TY() (height*e->tfinger.y)
#define TI() (e->tfinger.fingerId)
#endif

#define SDL_Clear(s)  memset((s)->pixels, 0 , (s)->w*(s)->h*4)
inline Uint32& SDL_Pixel(SDL_Surface* sur , int x , int y) {
	static Uint32 t = 0;  if(x < 0 || x > sur->w - 1 || y < 0 || y > sur->h - 1) return t ; 
	return ((Uint32*)sur->pixels)[ y * sur->w + x ];
}
void SDL_Line(SDL_Surface* sur , int x1 , int y1 , int x2 , int y2 , Uint32 c=0xffffff){
	int l = sqrt( (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) );
	if(l == 0) l = 1;
	for(int i=0;i <= l ; i++) {
		int x=(x1*i+x2*(l-i))/l;
		int y=(y1*i+y2*(l-i))/l;
		SDL_Pixel(sur,x,y)=c; 
	}
}

void SDL_Circle(SDL_Surface* sur , int cx , int cy , int r , Uint32 c= 0xffffff) {
    int x=0,y=r , d = 1 - r;
    while(x<=y)
  SDL_Pixel(sur,cx+x,cy+y)=c,    SDL_Pixel(sur,cx+y,cy+x)=c,
  SDL_Pixel(sur,cx-x,cy+y)=c, 
  SDL_Pixel(sur,cx-y,cy+x)=c, 
  SDL_Pixel(sur,cx-x,cy-y)=c,
  SDL_Pixel(sur,cx-y,cy-x)=c, 
  SDL_Pixel(sur,cx+x,cy-y)=c,    SDL_Pixel(sur,cx+y,cy-x)=c,
  d = d + (d<0?2*x+3: 2*(x-y--)+5),x++;
}
void SDL_nStar(SDL_Surface* sur , int n , double cx , double cy , double cr , double a,Uint32 c = 0xffffff){
	double b = 3.14159 / 2 / n ;
  double oldx = 0 , oldy = 0;
	double R = 1 ;  double r = sin(b) / sin(3*b);
	for(int i=0;i<2*n+1;i++) {
		double rad=i%2==1?R:r;  
		double c =2*b*i+a; 
		double x = cx + cr * rad * cos(c),y=cy+cr*rad*sin(c);
		if( i > 0) SDL_Line(sur , oldx , oldy , x , y,c);
		oldx = x , oldy = y ;}
}

int width,height,quit;
SDL_Surface* screen;

#define min(a,b) (a<b?a:b)
#define n ((1<<6)+1)
#define for if(1)for
struct point{float x,y,z,h; int cx,cy; };
#define M(x,y) m[(x)*n+(y)]
inline void R(float&x,float&y,    float r) { float t=x;
	 x = x*cos(r) + y*sin(r) ,      y = y*cos(r) - t*sin(r);}
inline void T(float&x,float t)    { x+= t; } 
inline void S(float&x,float s)    { x*= s; }
inline Uint32 Color(float h){
	static const Uint32 c[]={
		0x0000cc,0x0000ff,
		0x4444ff,0x8888ff,
		0x00ff00,0x88cc44,
		0xcc8844,0x884400,
		0xaaffaa,0xffffff,
		-1,-1,-1,-1,-1,-1};
	return c[int(h*6+4)];
}
struct Map
{
	point m[n*n];
    float tx,ty,tz,rx,ry, rz,sx,sy,sz;
};
Map* map;
  void Draw(){
  SDL_Clear(screen);
  float w = min(width,height);
  point* m = map->m;
    // 3d --> 2d
	for(int i=0;i<n;i++)
  	for(int j=0;j<n;j++){
		M(i,j).x = i*2./n-1;
		M(i,j).y = M(i,j).h;
		M(i,j).z = j*2./n-1;  
		S(M(i,j).x,map->sx);
		S(M(i,j).y,map->sy);
		S(M(i,j).z,map->sz);
		R(M(i,j).y,M(i,j).z,map->rx);
		R(M(i,j).x,M(i,j).z,map->ry);
		R(M(i,j).x,M(i,j).y,map->rz);
		T(M(i,j).x,map->tx);
		T(M(i,j).y,map->ty);
		T(M(i,j).z,map->tz);
	  M(i,j).cx = width*.5 - w*M(i,j).x/M(i,j).z;  
	  M(i,j).cy = height*.5 - w*M(i,j).y/M(i,j).z;
	  }
  for(int i=0;i<n;i++)
  {
  	for(int j=0;j<n;j++){
  		point* p = &M(i,j);
  		point* q = &M(i,j+1);
  		point* r = &M(i+1,j);
      if(j+1<n)
    	SDL_Line(screen, p->cx,p->cy,q->cx,q->cy, Color((p->h+q->h)*.5));
    if(i+1<n) SDL_Line(screen, p->cx,p->cy,r->cx,r->cy, Color((p->h+r->h)*.5));//*/
  	}
  }
  }
	float Rnd(float k){
		return k-2*k*rand()/RAND_MAX;
	}
	void Calc(int l,int t,int d)
	{
		 int r = l+d , b = t+d;
		 int f = d >> 1;
		 if(f<1) return ;
		 float k = f*1./(n-1);
		  point* m = map->m;
		 M(l+f,t+f).h = (
M(l,t).h+M(r,t).h+M(r,b).h+ M(l,b).h)*.25 + Rnd(k);
     if(!M(l,t+f).h) M(l,t+f).h = (M(l,t).h + M(l,b).h)*.5 + Rnd(k);
     if(!M(r,t+f).h) M(r,t+f).h = (M(r,t).h + M(r,b).h)*.5 + Rnd(k);
     if(!M(l+f,b).h) M(l+f,b).h = (M(l,b).h + M(r,b).h)*.5 + Rnd(k);
     if(!M(l+f,t).h) M(l+f,t).h = (M(l,t).h + M(r,t).h)*.5 + Rnd(k);
     Calc(l,t,f);
     Calc(l+f,t,f);
     Calc(l,t+f,f);
     Calc(l+f,t+f,f);
	}
	void Calc(){
	  point* m = map->m;
	  Calc(0,0,n);
	  M(n/2,n).h=(M(n/2+1,n).h+ M(n/2-1,n).h)/2;
	}
  void Event(SDL_Event* e)
  {
  	static int tt=0,dx,dy;
	  switch (e->type){
	  case SDL_QUIT: 
	     quit = 1; break;
	  case TOUCH_DOWN: tt=1,
	     dx=TX(),dy=TY();break;
	  case TOUCH_MOTION:
	  if(tt==1){ 
	   map->ry+=(TX()-dx)*6./width;
	   map->rx+=(TY()-dy)*6./height;
	   dx=TX(),dy=TY(); break;
	  }
	  case TOUCH_UP:tt=0; break;
	  }
  }

int Run(const char* title = "Test" ,int fps = 30,int w=_CW_,int h=_CH_){
	double quit=0,step=1000.0/(fps+1);	 double ticks ; 
	SDL_Window* win = NULL; SDL_Renderer* ren = NULL; 
	if(!(win=SDL_CreateWindow( title ,200,200,w,h,SDL_WINDOW_SHOWN))){ SDL_Quit(); return 0;}
    if(w>0) width=w,height=h;  else SDL_GetWindowSize(win, &width,&height);
	ren =SDL_CreateRenderer(win, -1,SDL_RENDERER_PRESENTVSYNC);
	screen = SDL_CreateRGBSurface(0,width, height,32,0,0,0,0);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren,screen); 
    ticks = SDL_GetTicks();  
    SDL_Event  event; while(!quit)  {
	    while(SDL_PollEvent(&event))  Event(&event);        
	    if( (ticks += step) < SDL_GetTicks() ) continue ;    Draw();       
	    SDL_UpdateTexture(tex ,  0 , screen->pixels , screen->pitch);			   
	    SDL_RenderCopy(ren,tex,0,0);   SDL_RenderPresent(ren);     
	    SDL_Delay(ticks - SDL_GetTicks()); 
		}
		SDL_Quit();    return 0;
}

#undef main
main(){ 
      map = new Map;   memset(map , 0 , sizeof(Map));
	  map->tz = 3;  map->rx = 1;
	  map->sx = map->sy = map->sz = 1;
	  srand(time(0));
	  Calc();  Run();
}


