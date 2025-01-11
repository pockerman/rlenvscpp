#include "kernel/discretization/mesh_generation.h"
#include "kernel/discretization/line_mesh.h"
#include "kernel/discretization/edge_element.h"
#include "kernel/discretization/node.h"

#include <exception>

namespace kernel
{
namespace numerics
{

void build_mesh(LineMesh<1>& mesh, uint_t n_elements,
                const GeomPoint<1, real_t>& start, const GeomPoint<1, real_t>& end){

    if(n_elements == 0){
        throw std::logic_error("Cannot generate a LineMesh without elements");
    }

    if(start == end){
        throw std::logic_error("Cannot generate a LineMesh with the same start and ending points");
    }

    mesh.reserve_elements(n_elements);

    //add the elements to the mesh
    for(uint_t e=0; e<n_elements; ++e){
        mesh.add_element();
    }

    const real_t h = (end[0] - start[0])/n_elements;

    // create the nodes
    mesh.reserve_nodes(n_elements + 1);

    real_t coord = start[0];
    for(uint_t e=0; e<n_elements + 1; ++e){
        auto node = mesh.add_node(coord + h*e);
        node->make_vertex();
    }

    typedef LineMesh<1>::elem_ptr_t elem_ptr_t;

    // element-element connectivity
    auto* element = mesh.get_elem(0);
    element->resize_neighbors();
    element->set_neighbor(0, nullptr);
    element->set_neighbor(1, mesh.get_elem(1));

    uint_t e=1;
    for(; e<mesh.n_elements()-1; ++e){
        element = mesh.get_elem(e);
        element->resize_neighbors();
        element->set_neighbor(0, mesh.get_elem(e - 1));
        element->set_neighbor(1, mesh.get_elem(e + 1));
    }

    element = mesh.get_elem(mesh.n_elements()-1);
    element->resize_neighbors();
    element->set_neighbor(0, mesh.get_elem(e - 1));
    element->set_neighbor(1, elem_ptr_t());

    // element-node connectivity

    element = mesh.get_elem(0);
    element->resize_nodes();
    element->set_node(0, mesh.get_node(0));
    element->set_node(1, mesh.get_node(1));

    e=1;
    for(; e<mesh.n_elements()-1; ++e){
        element = mesh.get_elem(e);
        element->resize_nodes();
        element->set_node(0, mesh.get_node(e ));
        element->set_node(1, mesh.get_node(e + 1));
    }

    element = mesh.get_elem(mesh.n_elements()-1);
    element->resize_nodes();
    element->set_node(0, mesh.get_node(e ));
    element->set_node(1, mesh.get_node(e + 1));
}


}
}
