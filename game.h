#ifndef I_GAME_H
#define I_GAME_H

namespace Tmpl8 {

#define MAXP1		 1000			// increase to test your optimized code
#define MAXP2		 (4 * MAXP1)	// because the player is smarter than the AI
#define MAXBULLET	200
#define GRIDSIZE 64

class Smoke
{
public:
	struct Puff { int x, y, vy, life; };
	Smoke() : active( false ), frame( 0 ) {};
	void Tick();
	Puff puff[8];
	bool active;
	int frame, xpos, ypos;
};

class Tank
{
public:
	enum { ACTIVE = 1, P1 = 2, P2 = 4 };
	Tank() : pos( vec2( 0, 0 ) ), speed( vec2( 0, 0 ) ), target( vec2( 0, 0 ) ), reloading( 0 ) {};
	~Tank();
	void Fire( unsigned int party, vec2& pos, vec2& dir );
	void Tick();
	vec2 pos, speed, target;
	//SIMD versions
	//__m128* pos4, *speed4, *target4, *force4;
	union { __m128* pos4; float posF[4]; };
	union { __m128* speed4; float speedF[4]; };
	union { __m128* target4; float targetF[4]; };
	union { __m128* force4; float forceF[4]; };
	float maxspeed;
	int flags, reloading;
	i32vec2 gridcel;
	Smoke smoke;
};

class Bullet
{
public:
	enum { ACTIVE = 1, P1 = 2, P2 = 4 };
	Bullet() : flags( 0 ) {};
	void Tick();
	vec2 pos, speed;
	int flags;
};

class Surface;
class Surface8;
class Sprite;
class Game
{
public:
	void SetTarget( Surface* a_Surface ) { m_Surface = a_Surface; }
	void MouseMove( int x, int y ) { m_MouseX = x; m_MouseY = y; }
	void MouseButton( bool b ) { m_LButton = b; }
	void Init();
	void UpdateTanks();
	void UpdateBullets();
	void DrawTanks();
	void PlayerInput();
	void Tick( float a_DT );
	Surface* m_Surface, *m_Backdrop, *m_Heights, *m_Grid;
	Sprite* m_P1Sprite, *m_P2Sprite, *m_PXSprite, *m_Smoke;
	int m_ActiveP1, m_ActiveP2;
	int m_MouseX, m_MouseY, m_DStartX, m_DStartY, m_DFrames;
	bool m_LButton, m_PrevButton;
	Tank** m_Tank;
};

}; // namespace Templ8

#endif