#ifndef MESH_GENERATION_H
#define MESH_GENERATION_H

#include "kernel/base/types.h"
#include "kernel/data_structs/boost_serial_graph.h"
#include "kernel/discretization/line_mesh.h"
#include "kernel/discretization/edge_element.h"

#include <vector>

namespace kernel{

// forward declarations
template<int dim, typename T> class GeomPoint;
template<typename VertexData, typename EdgeData> class BoostSerialGraph;

namespace numerics{

/// forward declarations
template<int dim> class LineMesh;

/// \brief Generate a LineMesh with n_elements
void build_mesh(LineMesh<1>& mesh, uint_t n_elements,
                const GeomPoint<1, real_t>& start, const GeomPoint<1, real_t>& end );

/// \brief Generate a line mesh from the given graph
/// using the vertices of the graph. Note that the vertices
template<int dim, typename VertexData, typename EdgeData>
void build_mesh(LineMesh<dim>& mesh,
                const BoostSerialGraph<VertexData, EdgeData>& graph,
                const std::vector<uint_t>& vertices){

    // clear whatever the mesh has
    mesh.clear();

    mesh.reserve_nodes(vertices.size());

    const auto& vertex0 = graph.get_vertex(vertices[0]);
    auto* previous_node = mesh.add_node(vertex0.data.position);
    auto* next_node = previous_node;
    next_node = nullptr;

    for(uint_t v=1; v<vertices.size(); ++v){
        const auto& vertex = graph.get_vertex(vertices[v]);
        next_node = mesh.add_node(vertex.data.position);

        //add a new element
        auto* element = mesh.add_element();
        element->resize_nodes();
        element->set_node(0,previous_node);
        element->set_node(1,next_node);

        previous_node = next_node;
    }

    // now add the edges connecting the
    // nodes
}


}

}

#endif // MESH_GENERATION_H
