#ifndef LINE_MESH_H
#define LINE_MESH_H

#include "kernel/base/types.h"
#include "kernel/geometry/geom_point.h"

#include "boost/noncopyable.hpp"
#include <memory>
#include <vector>


namespace kernel{
namespace numerics{

template<int dim> class Node;
template<int dim> class EdgeElem;

/// \brief Models a LineMesh in dim spatial dimensions
template<int dim>
class LineMesh: private boost::noncopyable
{
public:

    typedef Node<dim> edge_t;
    typedef Node<dim> face_t;
    typedef Node<dim> node_t;
    typedef node_t* node_ptr_t;
    typedef EdgeElem<dim> elem_t;
    typedef elem_t* elem_ptr_t;

    /// \brief Node iteration
    typedef typename std::vector<node_ptr_t>::iterator node_iterator_impl;
    typedef typename std::vector<node_ptr_t>::const_iterator cnode_iterator_impl;

    /// \brief Element iteration
    typedef typename std::vector<elem_ptr_t>::iterator element_iterator_impl;
    typedef typename std::vector<elem_ptr_t>::const_iterator celement_iterator_impl;

    /// \brief Constructor
    LineMesh()=default;

    /// \brief Destructor
    ~LineMesh();

    /// \brief How many elements
    uint_t n_elements()const{return elements_.size();}

    /// \brief How many nodes
    uint_t n_nodes()const{return nodes_.size();}

    /// \brief How many sides
    uint_t n_edges()const;

    /// \brief How many sides
    uint_t n_faces()const;

    /// \brief Create a new node
    /// and get back the pointer
    node_ptr_t add_node(real_t x);

    /// \brief Add a new node
    node_ptr_t add_node(const GeomPoint<dim>&  x);

    /// \brief Access the n-th node
    node_ptr_t get_node(uint_t n);

    /// \brief Create a new element and get
    /// back the pointer
    elem_ptr_t add_element();

    /// \brief Access the e-th element
    elem_ptr_t get_elem(uint_t e);

    /// \brief Reserve space for n elements
    void reserve_elements(uint_t elements);

    /// \brief Reserve space for n elements
    void reserve_nodes(uint_t nodes);

    /// \brief Get the number of boundaries of the mesh
    uint_t n_boundaries()const{return 2;}

    /// \brief Clear the memory allocated
    void clear();

    /// \brief Raw node iteration
    node_iterator_impl nodes_begin(){return nodes_.begin();}
    node_iterator_impl nodes_end(){return nodes_.end();}

    /// \brief Raw node iteration
    cnode_iterator_impl nodes_begin()const{return nodes_.begin();}
    cnode_iterator_impl nodes_end()const{return nodes_.end();}

    /// \brief Raw elements iteration
    element_iterator_impl elements_begin(){return elements_.begin();}
    element_iterator_impl elements_end(){return elements_.end();}

    /// \brief Raw elements iteration
    celement_iterator_impl elements_begin()const{return elements_.begin();}
    celement_iterator_impl elements_end()const{return elements_.end();}
private:

    /// \brief List of nodes in the mesh
    std::vector<node_ptr_t> nodes_;

    /// \brief List of elements in the mesh
    std::vector<elem_ptr_t> elements_;

};

}
}

#endif // LINE_MESH_H
