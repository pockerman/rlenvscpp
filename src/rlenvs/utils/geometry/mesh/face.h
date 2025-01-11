#ifndef FACE_H
#define FACE_H

#include "kernel/base/types.h"
#include "kernel/discretization/face_element.h"

namespace kernel
{

namespace numerics
{

//specialization for 3D faces. A Face in 3D acts like a FaceElement
class Face: public FaceElement<3,2>
{
  
  protected:
  
  Face();
  
  Face(uint_t id,uint_t pid=0);


};


inline
Face::Face()
         :
         FaceElement<3,2>()
         {}
                 
inline                 
Face::Face(uint_t id,uint_t pid)
            :
           FaceElement<3,2>(id,pid)
           {}
                 

}

}//libsimpp

#endif
