#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

using namespace glm;

class LineSegment {
public:
    LineSegment() = default;
    LineSegment(const vec2 start, const vec2 end);

    vec2 direction() const;

public:
    vec2 start;
    vec2 end;
};

class Triangle {
public:
    Triangle() = default;
    Triangle(const vec2 a, const vec2 b, const vec2 c);

public:
    vec2 a;
    vec2 b;
    vec2 c;
};

class Mesh {
public:
    void removePoint(const vec2 point);
    void removeDoubles(const float epsilon);

public:
    std::vector<LineSegment> lines;
};

class PathSegment {
public:
    virtual vec2 f(const float x) const = 0;
    virtual vec2 slope(const float x) const = 0;
    virtual float length() const = 0;
    virtual float resolutionFactor() const = 0;
};

class PathLine: public PathSegment {
public:
    PathLine(const vec2 start, const vec2 end);

    virtual vec2 f(const float x) const override;
    virtual vec2 slope(const float x) const override;
    virtual float length() const override;
    virtual float resolutionFactor() const override;

private:
    const vec2 m_start;
    const vec2 m_end;
};

class PathArc: public PathSegment {
public:
    PathArc(const vec2 start, const float radius, const float arcOffset,
            const float arcLength);

    virtual vec2 f(const float x) const override;
    virtual vec2 slope(const float x) const override;
    virtual float length() const override;
    virtual float resolutionFactor() const override;

private:
    const vec2 m_start;
    const float m_radius;
    const float m_offset;
    const float m_arcLength;
};

class Path {
public:
    Path() = default;
    Path(const Path&) = delete;

    Path& operator=(const Path&) = delete;

    template <typename T, typename... Args> void addSegment(Args&&... args) {
        segments.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
    }

    void reset();

    Mesh toMesh(const float resolution) const;

public:
    std::vector<std::unique_ptr<PathSegment>> segments;
};

std::vector<Triangle> triangulate(Mesh mesh);

Triangle clipEar(Mesh& rMesh);
