#include "kernel/discretization/element_builder.h"
#include "kernel/discretization/edge_element.h"
#include "kernel/discretization/quad_element.h"
#include "kernel/base/kernel_consts.h"

#include <exception>
namespace kernel
{
namespace numerics
{

template<>
Element<1>*
ElementBuilder<1>::build_element(ElementType::sub_type t){

    Element<1>* ptr = nullptr;

    if(t == ElementType::sub_type::EDGE2){
        ptr = new EdgeElem<1>(KernelConsts::invalid_size_type());
    }

    return ptr;
}


template<>
Element<2>*
ElementBuilder<2>::build_element(ElementType::sub_type t){

    Element<2>* ptr = nullptr;

    if(t == ElementType::sub_type::QUAD4){
        ptr = new Quad<2>();
    }

    return ptr;
}

template<>
Element<3>*
ElementBuilder<3>::build_element(ElementType::sub_type t){

    Element<3>* ptr = nullptr;
    return ptr;
}


template<>
EdgeBuilder<1>::edge_ptr_t
EdgeBuilder<1>::build_edge(ElementType::sub_type t){

   throw std::logic_error("Cannot build edges in 1D");
   EdgeBuilder<1>::edge_ptr_t ptr = nullptr;
   return ptr;
}


template<>
EdgeBuilder<2>::edge_ptr_t
EdgeBuilder<2>::build_edge(ElementType::sub_type t){


   EdgeBuilder<2>::edge_ptr_t ptr = nullptr;

   switch(t)
   {

      case ElementType::sub_type::EDGE2:
      {

        ptr = new EdgeElem<2>(2);
        break;

      }
      case ElementType::sub_type::EDGE3:
      case ElementType::sub_type::EDGE4:
      case ElementType::sub_type::EDGE5:
      case ElementType::sub_type::EDGE6:
      case ElementType::sub_type::EDGE7:
      {
       ptr = nullptr;
       break;
     }
     default:
     {
       throw std::logic_error("Invalid EdgeElem specified");
     }
   }


   return ptr;
}

template<>
FaceBuilder<2>::face_ptr_t
FaceBuilder<2>::build_face(ElementType::sub_type t)
{
  return EdgeBuilder<2>::build_edge(t);
}


template<>
FaceBuilder<1>::face_ptr_t
FaceBuilder<1>::build_face(ElementType::sub_type t)
{
   throw std::logic_error("Cannot build faces in 1D");
   FaceBuilder<1>::face_ptr_t ptr = nullptr;
   return ptr;
}


template<>
EdgeBuilder<3>::edge_ptr_t
EdgeBuilder<3>::build_edge(ElementType::sub_type t)
{

   EdgeBuilder<3>::edge_ptr_t ptr = nullptr;

   switch(t)
   {

     case ElementType::sub_type::EDGE2:
     {

      ptr = new EdgeElem<3>(2);
      break;

     }
     case ElementType::sub_type::EDGE3:
     case ElementType::sub_type::EDGE4:
     case ElementType::sub_type::EDGE5:
     case ElementType::sub_type::EDGE6:
     case ElementType::sub_type::EDGE7:
     {

       ptr = nullptr;
       break;
     }
    default:
    {

      throw std::logic_error("Invalid EdgeElem specified");
    }
   }

  return ptr;

}


template<>
FaceBuilder<3>::face_ptr_t
FaceBuilder<3>::build_face(ElementType::sub_type t){

   FaceBuilder<3>::face_ptr_t ptr = nullptr;

   switch(t)
   {

     case ElementType::sub_type::QUAD4:
     {

      ptr = new Quad<3>();
      break;
     }

    default:
    {
      throw std::logic_error("Invalid EdgeElem specified");
    }
   }

  return ptr;
}


template class ElementBuilder<1>;
template class ElementBuilder<2>;
template class ElementBuilder<3>;
template class EdgeBuilder<1>;
template class EdgeBuilder<2>;
template class EdgeBuilder<3>;
template class FaceBuilder<1>;
template class FaceBuilder<2>;
template class FaceBuilder<3>;

}
}
