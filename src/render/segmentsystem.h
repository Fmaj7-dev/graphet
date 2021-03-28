
#ifndef SEGMENT_SYSTEM_H
#define SEGMENT_SYSTEM_H

#include "renderable.h"

#ifdef __APPLE__
   #define GL_SILENCE_DEPRECATION
   #include <GLUT/glut.h>
#else
    #define GL_GLEXT_PROTOTYPES
    #include <GL/glut.h>
#endif

#include <vector>

class SegmentPoint
{
public:
    SegmentPoint() = default;
    SegmentPoint( float x1, float y1, float z1,
                  int r, int g, int b )
    {
        position1_[0] = x1;
        position1_[1] = y1;
        position1_[2] = z1;

        color1_[0] = r;
        color1_[1] = g;
        color1_[2] = b; 

    }
    float position1_[3];
    unsigned char color1_[4];
};

class Segment
{
public:
    SegmentPoint a;
    SegmentPoint b;
};


class SegmentSystem: public Renderable
{
public:
    SegmentSystem(size_t n = 0);
    ~SegmentSystem();

    // init
    //void randInitPositions();
    

    // segments
    void addSegment( const Segment& );
    SegmentPoint* getSegmentPoints();
    size_t getNumSegmentPoints();

    // render
    void init();
    //GLint LoadShader( GLenum type, const char *src );
    void draw();
    void recreateBuffers( size_t n );

private:
    class Context{ public: enum type{ Position_loc=0, Color_loc=1 }; };

    GLuint vertex_id;
    GLuint fragment_id;
    GLuint program_id;
    GLuint geom_id;

private:
    std::vector<SegmentPoint> segmentPoints_;
};

#endif