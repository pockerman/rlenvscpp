#ifndef QUAD_MESH_GENERATION_H
#define QUAD_MESH_GENERATION_H

#include "kernel/base/types.h"

namespace kernel
{

// forward declarations
template<int dim, typename T> class GeomPoint;

namespace numerics
{

template<int dim> class Mesh;

/// \brief build a cartesian mesh with quad elements
void build_quad_mesh(Mesh<2>& mesh, uint_t nx, uint_t ny,
                     const GeomPoint<2, real_t>& lower_point,
                     const GeomPoint<2, real_t>& upper_point);

}

}

#endif // QUAD_MESH_GENERATION_H
