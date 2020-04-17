#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

using namespace glm;

class PathSegment {
public:
    virtual vec2 f(const float x) const = 0;
    virtual vec2 slope(const float x) const = 0;
    virtual float length() const = 0;
};

class PathLine: public PathSegment {
public:
    PathLine(const vec2 start, const vec2 end);

    virtual vec2 f(const float x) const override;
    virtual vec2 slope(const float x) const override;
    virtual float length() const override;

private:
    const vec2 m_start;
    const vec2 m_end;
};

class Path {
public:
    Path() = default;
    Path(const Path&) = delete;

    Path& operator=(const Path&) = delete;

    std::vector<std::unique_ptr<PathSegment>> segments;
};
