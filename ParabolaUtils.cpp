//ParabolaUtils.cpp

#include <math.h>
#include "parabola.h"
static float g_const = 9.8;

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

Parabola_t p;
/* Specify a Projectile using velocity and Angle */
void Parabola::CreateParabola(float v, float angle) {
	p.m_v = v;
	p.m_angle = (M_PI * angle)/180;
	p.CalcParams();
}

/* Caculate the basic paramters of the projectile motion */
void Parabola::CalcParams() {
	p.m_time = 2 * p.m_v * sin(p.m_angle) /  g_const;
	p.m_range = p.m_v * cos(p.m_angle) * p.m_time;
	p.m_maxheight = (p.m_v * sin(p.m_angle) * p.m_time  / 2) - ((g_const *  p.m_time * p.m_time)  / (2 * 2 * 2));

}


/* Given time get the height achieved */
float Parabola::GetH(float t) {
	float H = (p.m_v * sin(p.m_angle) * t) - (g_const * t * t / 2);
	return MIN(p.m_maxheight, H);
}

/* Given time get the Range achieved */

float Parabola::GetR(float t) {
	return MIN((p.m_v * cos(p.m_angle) * t), p.m_range);
}

/* Given time get the Flight time*/
float Parabola::GetT() {
	return p.m_time;
}

float Parabola::MaxH() {
	return p.m_maxheight;
}
