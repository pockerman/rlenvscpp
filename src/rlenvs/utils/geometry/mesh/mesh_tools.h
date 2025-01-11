#ifndef MESH_TOOLS_H
#define MESH_TOOLS_H

#include "kernel/base/config.h"
#include "kernel/base/types.h"
#include "kernel/discretization/element.h"
#include "kernel/discretization/element_mesh_iterator.h"
#include "kernel/discretization/mesh_predicates.h"
#include "kernel/discretization/mesh.h"

namespace kernel {
namespace numerics {

/// \brief Provides some utility functions
/// for a Mesh that are not necessarily efficinetly
/// implemented


/// \brief Returns the number of elements in the mesh
/// that satisfy the predicate Active
template<int dim>
uint_t n_active_elements(const Mesh<dim>& mesh){

    uint_t result = 0;
    ConstElementMeshIterator<Active, Mesh<dim>> filter(mesh);

    auto element_begin = filter.begin();
    auto element_end = filter.end();

    for(; element_begin != element_end; ++element_begin){
        result++;
    }

    return result;
}



}

}

#endif // MESH_TOOLS_H
