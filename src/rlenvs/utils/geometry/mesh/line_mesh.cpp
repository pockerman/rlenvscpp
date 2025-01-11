#include "kernel/discretization/line_mesh.h"
#include "kernel/discretization/edge_element.h"
#include "kernel/discretization/node.h"

#include <exception>
namespace kernel{
namespace numerics{

template<int dim>
LineMesh<dim>::~LineMesh()
{
    clear();
}
template<int dim>
void
LineMesh<dim>::reserve_elements(uint_t elements){

    if(elements == 0){

        throw std::logic_error("Cannot reserve space for zero elements");
    }

    elements_.reserve(elements);
}

template<int dim>
void
LineMesh<dim>::reserve_nodes(uint_t nodes){

    if(nodes == 0){
       throw std::logic_error("Cannot reserve space for zero nodes");
    }

    nodes_.reserve(nodes);
}

template<int dim>
uint_t
LineMesh<dim>::n_edges()const{
    return 0;
}

template<int dim>
uint_t
LineMesh<dim>::n_faces()const{
    return 0;
}

template<int dim>
typename LineMesh<dim>::node_ptr_t
LineMesh<dim>::add_node(real_t x){
    uint_t id = nodes_.size();
    nodes_.push_back(new Node<dim>(x, id));
    return nodes_[id];
}

template<>
typename LineMesh<1>::node_ptr_t
LineMesh<1>::add_node(const GeomPoint<1>&  x){
    uint_t id = nodes_.size();
    nodes_.push_back(new Node<1>(x[0], id));
    return nodes_[id];
}

template<int dim>
typename LineMesh<dim>::node_ptr_t
LineMesh<dim>::add_node(const GeomPoint<dim>&  x){
    uint_t id = nodes_.size();
    nodes_.push_back(new Node<dim>(x, id, 0));
    return nodes_[id];
}

template<int dim>
typename LineMesh<dim>::node_ptr_t
LineMesh<dim>::get_node(uint_t n){
    if(n >= nodes_.size()){
       throw std::logic_error("Invalid node index "+std::to_string(n)+" not in [0,"+std::to_string(nodes_.size())+")");
    }

    return nodes_[n];
}

template<int dim>
typename LineMesh<dim>::elem_ptr_t
LineMesh<dim>::add_element(){

    uint_t id = elements_.size();
    elements_.push_back(new EdgeElem<dim>(id));
    return elements_[id];
}

template<int dim>
typename LineMesh<dim>::elem_ptr_t
LineMesh<dim>::get_elem(uint_t e){

    if(e >= elements_.size()){
       throw std::logic_error("Invalid element index "+std::to_string(e)+" not in [0,"+std::to_string(elements_.size())+")");
    }

    return elements_[e];
}

template<int dim>
void
LineMesh<dim>::clear(){

    for(uint_t n=0; n<nodes_.size(); ++n){
        if(nodes_[n]){
            delete nodes_[n];
            nodes_[n] = nullptr;
        }
    }

    nodes_.clear();

    for(uint_t e=0; e<elements_.size(); ++e){
        if(elements_[e]){
            delete elements_[e];
            elements_[e] = nullptr;
        }
    }

    elements_.clear();
}

template class LineMesh<1>;
template class LineMesh<2>;
template class LineMesh<3>;
}
}
