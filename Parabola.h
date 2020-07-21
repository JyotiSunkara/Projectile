//Parabola.h
#ifndef PARABOLA_H
#define PARABOLA_H

typedef class Parabola{
	
    
    
    public:
    
    
    
    float m_v;
	float m_angle;
	float m_time;
	float m_maxheight;
	float m_range;
	
	
           
         
         void    CreateParabola(float, float);
         void 	 CalcParams();
         float 	 GetH(float t);
         float   GetR(float t);
         float   GetT();
         float   MaxH();
}Parabola_t;

#endif
