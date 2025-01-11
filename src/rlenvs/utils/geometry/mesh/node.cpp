#include "rlenvs/utils/geometry/mesh/node.h"
#include "rlenvs/rlenvs_consts.h"

namespace rlenvscpp{
namespace utils{
namespace geom{
	
	
template<int dim>
Node<dim>::Node()
    :
   FaceElement<dim, 0> ()
  
{}

template<int dim>
Node<dim>::Node(real_t coord, uint_t id, const std::any& data)
    :
      FaceElement<dim, 0> (GeomPoint<dim>(coord), id,  
	                       static_cast<uint_t>(0),data)
   {}

template<int dim>
Node<dim>::Node(const std::array<real_t, dim>& coords, uint_t id, const std::any& data)
    :
      FaceElement<dim, 0>(coords, id, 
	                      static_cast<uint_t>(0), data)
   {}

template<int dim>
Node<dim>::Node(const GeomPoint<dim>& point, uint_t id, uint_t pid, const std::any& data)
    :
      FaceElement<dim, 0>(point, id, 
	                      pid, data)
{}



// explicit instantiations
template class Node<1>;
template class Node<2>;
template class Node<3>;

}
}
}
