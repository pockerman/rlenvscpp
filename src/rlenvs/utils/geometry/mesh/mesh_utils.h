#ifndef MESH_UTILS_H
#define MESH_UTILS_H

#include "kernel/base/types.h"
#include "kernel/base/kernel_consts.h"
#include "kernel/geometry/geom_point.h"
#include "kernel/geometry/generic_line.h"
#include "kernel/discretization/element_mesh_iterator.h"
#include "kernel/discretization/mesh_predicates.h"
#include "kernel/geometry/shapes/circle.h"

#include <stdexcept>
#include <cmath>
#include <utility>
#include <tuple>

namespace kernel{
namespace discretization{

/// \brief Find the element in the mesh
/// with the smallest distance from the point
///
template<typename MeshTp>
const typename MeshTp::element_t*
find_closest_element(const MeshTp& mesh, const GeomPoint<MeshTp::dimension>& p,
                     uint_t nsamples, real_t tol){

    numerics::ConstElementMeshIterator<numerics::Active, MeshTp> filter(mesh);
    typedef typename MeshTp::element_t element_t;
    element_t* ptr = nullptr;
    real_t dist = std::numeric_limits<real_t>::max();

    auto begin = filter.begin();
    auto end   = filter.end();

    for(; begin != end; ++begin){

        auto element = *begin;
        auto dist_cur = distance_from(*element, p, nsamples, tol);

        if(dist_cur < dist){
            dist = dist_cur;
            ptr = element;
        }
    }

    return ptr;
}

///
///
///
template<typename MeshTp>
std::tuple<const typename MeshTp::point_t, const typename MeshTp::element_t*>
find_closest_point_to(const MeshTp& mesh, const GeomPoint<2>& p,
                      uint_t nsamples, real_t tol){

    static_assert (MeshTp::dimension == 2, "Mesh dimension is not 2");

    typedef typename MeshTp::point_t point_t;

    std::vector<point_t> min_points;
    min_points.reserve(mesh.n_elements());

    numerics::ConstElementMeshIterator<numerics::Active, MeshTp> filter(mesh);

    auto begin = filter.begin();
    auto end   = filter.end();

    for(; begin != end; ++begin){

        auto element = *begin;
        auto min_point = find_point_on_line_closest_to(*element, p, nsamples, tol);
        min_points.push_back(min_point);
    }

    auto result = get_point_with_min_distance(p, min_points);

    /// find out to which segment this point belongs to
    auto element = find_closest_element(mesh, result, nsamples, tol);

    return {result, element};
}

/// \brief Returns the intersection points of the
/// Circle with the elements of the LineMesh.
/// The algorithn implemented is the one described here
/// https://stackoverflow.com/questions/1073336/circle-line-segment-collision-detection-algorithm/1084899#1084899%E2%80%8B
///
template<typename MeshTp>
const std::vector<typename MeshTp::point_t> find_intersections(const MeshTp& mesh,
                                                                 const Circle& circle){

    static_assert (MeshTp::dimension == 2, "Mesh dimension is not 2");

    std::vector<typename MeshTp::point_t> intersections;

    const auto r = circle.radius();
    const auto center = circle.center();

    numerics::ConstElementMeshIterator<numerics::Active, MeshTp> filter(mesh);
    auto begin = filter.begin();
    auto end   = filter.end();

    for(; begin != end; ++begin){

        auto element = *begin;
        auto v0 = element->get_vertex(0);
        auto v1 = element->get_vertex(1);

        auto d = v1 - v0;
        auto f = v0 - center;

        auto a = d.dot(d);
        auto b = 2.0*f.dot(d);
        auto c = f.dot(f) - r*r;

        auto discriminant = b*b-4*a*c;

        auto intersects = has_intersection(discriminant, b, a);
        if(intersects.first){

            /// thats an intersection point
            auto intersection = v0  + d*intersects.second;
            intersections.push_back(intersection);
        }
    }

    return intersections;
}


}//discretization

}

#endif // GEOMETRY_UTILS_H
