#ifndef NODE_MESH_ITERATOR_H
#define NODE_MESH_ITERATOR_H

#include "kernel/utilities/filtered_iterator.h"

namespace kernel{
namespace numerics{

template<typename Predicate, typename  MeshTp>
class NodeMeshIterator
{

public:

    typedef Predicate predicate_t;
    typedef MeshTp mesh_t;
    typedef typename mesh_t::node_iterator_impl iterator_impl;
    typedef typename FilteredIterator<Predicate, iterator_impl>::value_type value_type;
    typedef FilteredIterator<Predicate, iterator_impl> result_t;

    /// constructor
    NodeMeshIterator(mesh_t& mesh);

    /// \brief begin the iteration
    result_t begin();

    /// \brief end the iteration
    result_t end();

protected:

    // the mesh over which the iterator is working
    mesh_t& mesh_;

};

template<typename Predicate, typename  MeshTp>
NodeMeshIterator<Predicate, MeshTp>::NodeMeshIterator(typename NodeMeshIterator<Predicate, MeshTp>::mesh_t& mesh)
    :
//FilteredIterator<Predicate, typename MeshTp::node_iterator_impl>(),
mesh_(mesh)
{}

template<typename Predicate, typename  MeshTp>
typename NodeMeshIterator<Predicate, MeshTp>::result_t
NodeMeshIterator<Predicate, MeshTp>::begin(){
    Predicate p;
    return NodeMeshIterator<Predicate, MeshTp>::result_t(p, mesh_.nodes_begin(), mesh_.nodes_end() );
}

template<typename Predicate, typename  MeshTp>
typename NodeMeshIterator<Predicate, MeshTp>::result_t
NodeMeshIterator<Predicate, MeshTp>::end(){
    Predicate p;
    return NodeMeshIterator<Predicate, MeshTp>::result_t(p, mesh_.nodes_end(), mesh_.nodes_end() );
}


template<typename Predicate, typename  MeshTp>
class ConstNodeMeshIterator
{

public:

    typedef Predicate predicate_t;
    typedef MeshTp mesh_t;
    typedef typename mesh_t::cnode_iterator_impl iterator_impl;
    typedef typename FilteredIterator<Predicate, iterator_impl>::value_type value_type;
    typedef FilteredIterator<Predicate, iterator_impl> result_t;

    /// constructor
    ConstNodeMeshIterator(const mesh_t& mesh);

    /// \brief begin the iteration
    result_t begin()const;

    /// \brief end the iteration
    result_t end()const;

protected:

    // the mesh over which the iterator is working
    const mesh_t& mesh_;

};

template<typename Predicate, typename  MeshTp>
ConstNodeMeshIterator<Predicate, MeshTp>::ConstNodeMeshIterator(const typename ConstNodeMeshIterator<Predicate, MeshTp>::mesh_t& mesh)
    :
//FilteredIterator<Predicate, typename MeshTp::node_iterator_impl>(),
mesh_(mesh)
{}

template<typename Predicate, typename  MeshTp>
typename ConstNodeMeshIterator<Predicate, MeshTp>::result_t
ConstNodeMeshIterator<Predicate, MeshTp>::begin()const{
    Predicate p;
    return ConstNodeMeshIterator<Predicate, MeshTp>::result_t(p, mesh_.nodes_begin(), mesh_.nodes_end() );
}

template<typename Predicate, typename  MeshTp>
typename ConstNodeMeshIterator<Predicate, MeshTp>::result_t
ConstNodeMeshIterator<Predicate, MeshTp>::end()const{
    Predicate p;
    return ConstNodeMeshIterator<Predicate, MeshTp>::result_t(p, mesh_.nodes_end(), mesh_.nodes_end() );
}


}

}

#endif // NODE_MESH_ITERATOR_H
