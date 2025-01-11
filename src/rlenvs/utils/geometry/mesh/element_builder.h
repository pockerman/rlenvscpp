#ifndef ELEMENT_BUILDER_H
#define ELEMENT_BUILDER_H

#include "kernel/discretization/element_traits.h"
#include "kernel/discretization/element_type.h"


namespace kernel
{
namespace numerics
{

template<int dim>
struct ElementBuilder
{
  static Element<dim>* build_element(ElementType::sub_type t);
};

template<int dim>
struct EdgeBuilder
{
  typedef typename element_traits<Element<dim> >::edge_ptr_t edge_ptr_t;
  static edge_ptr_t build_edge(ElementType::sub_type t);
};

template<int dim>
struct FaceBuilder
{
  typedef typename element_traits<Element<dim> >::face_ptr_t face_ptr_t;
  static face_ptr_t build_face(ElementType::sub_type t);
};

}

}

#endif // ELEMENT_BUILDER_H
