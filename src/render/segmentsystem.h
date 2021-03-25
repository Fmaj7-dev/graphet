
#ifndef SEGMENT_SYSTEM_H
#define SEGMENT_SYSTEM_H

#ifdef __APPLE__
   #define GL_SILENCE_DEPRECATION
   #include <GLUT/glut.h>
#else
    #define GL_GLEXT_PROTOTYPES
    #include <GL/glut.h>
#endif

#include <vector>

class Segment
{
public:
    Segment() = default;
    Segment( float x1, float y1, float z1,
          /*float x2, float y2, float z2, */
          int r, int g, int b )
    {
        position1_[0] = x1;
        position1_[1] = y1;
        position1_[2] = z1;

        /*position2_[0] = x2;
        position2_[1] = y2;
        position2_[2] = z2;*/

        color1_[0] = r;
        color1_[1] = g;
        color1_[2] = b; 

        /*color2_[0] = r;
        color2_[1] = g;
        color2_[2] = b; */
    }
//private:
    float position1_[3];
    unsigned char color1_[4];

    /*float position2_[3];
    unsigned char color2_[3];*/
};

class SegmentSystem
{
public:
    SegmentSystem(size_t n = 0);
    ~SegmentSystem();
    void randInitPositions();

    // segments
    void addSegment(const Segment&);
    Segment* getSegments();
    size_t getNumSegments();

    // render
    void init();
    GLint LoadShader(GLenum type, const char *src);
    void draw();

private:
    class Context{ public: enum type{ Position_loc=0, Color_loc=1 }; };

    GLuint vertex_id;
    GLuint fragment_id;
    GLuint program_id;
    GLuint geom_id;

private:
    std::vector<Segment> segments_;
};

#endif