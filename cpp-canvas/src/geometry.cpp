#include "cpp-canvas/geometry.h"

namespace canvas {
    PathLine::PathLine(const vec2 start, const vec2 end)
        : m_start(start), m_end(end) {}

    vec2 PathLine::f(const float x) const {
        return m_start + (x * (m_end - m_start));
    }

    vec2 PathLine::slope(const float x) const {
        return normalize(m_end - m_start);
    }

    float PathLine::length() const {
        return static_cast<float>((m_end - m_start).length());
    }

    float PathLine::resolutionFactor() const { return 0.0f; }

    Path::Path() : closed(false) {}

    void Path::reset() { segments.clear(); }

    Mesh Path::toMesh(const float resolution) const {
        Mesh mesh;
        for (const auto& segment: segments) {
            mesh.points.push_back(segment->f(0.0f));
        }
        mesh.points.push_back(segments.back()->f(1.0f));
        return mesh;
    }

    Triangle::Triangle(const vec2 a, const vec2 b, const vec2 c)
        : a(a), b(b), c(c) {}

    void Mesh::removeDoubles(const float epsilon) {}

    std::vector<Triangle> triangulate(Mesh mesh) {
        mesh.removeDoubles(
            0.0001f); // TODO Figure out a good epsilon based on size
        std::vector<Triangle> triangles;
        // while (mesh.lines.size() > 3) {
        //    triangles.push_back(clipEar(mesh));
        //}
        return triangles;
    }

    Triangle clipEar(Mesh& rMesh) {
        // Mesh line segments point clockwise around the mesh:
        //
        //                   AB
        //                   |
        //                   V
        //               A O----->O B
        //                 ^      |
        //                 |      |
        //           DA -> |      V
        //                 |      O C
        //                 |     /
        //                 |    /
        //                 |   /
        //                 |  /
        //                 | /
        //                 |L
        //               D O
        //
        // To determine convex vs concave, we test dot(perp(AB), DA):
        //
        //     Condition                | Indication
        //     -------------------------+-------------------------------------------
        //     dot(perp(AB), DA) > 0    | Corner is convex
        //     dot(perp(AB), DA) < 0    | Corner is concave
        //     dot(perp(AB), DA) = 0    | Corner is flat and can be removed
        //
        // Thus, the procedure becomes:
        //
        // clip ear:
        //   for vertex a in mesh:
        //     ab = a.outgoing
        //     da = a.incoming
        //     convexFactor = dot(perp(ab), da)
        //     if (convexFactor > greatestConvexFactor):
        //       greatestConvexFactor = convexFactor
        //       mostConvexVertex = v
        //   mesh.remove(mostConvexVertex)
        //   d = mostConvexVertex.incoming.start
        //   b = mostConvexVertex.outgoing.end
        //   return triangle(mostConvexVertex, b, d)
        //
        // This removes the most convex vertex from the mesh to avoid creating
        // extremely thin triangles. The triangle formed by this vertex and its
        // two adjacent vertices is returned.
        return Triangle();
    }
} // namespace canvas
