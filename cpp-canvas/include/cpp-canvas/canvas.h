#pragma once

#include "cpp-canvas/context.h"
#include "cpp-canvas/export.h"
#include "cpp-canvas/field.h"
#include "cpp-canvas/geometry.h"
#include "cpp-canvas/style.h"

#include <functional>
#include <glm/glm.hpp>
#include <stack>
#include <string>

using namespace glm;

namespace canvas {
    class MouseEvent;

    class CPP_CANVAS_API Canvas {
    public:
        typedef std::function<void()> Handler;
        typedef std::function<void(const MouseEvent&)> MouseHandler;

        Canvas();

        void initialize();

        Context2D& getContext2D();
        const Context2D& getContext2D() const;

        ivec2 getDimensions() const;

        void onResize(ivec2 dimensions);

        void addEventListener(const std::string& type, Handler& handler);
        void addEventListener(const std::string& type,
                              const MouseHandler& handler);

        Color backgroundColor;

    private:
        Context2D m_context;
        ivec2 m_dimensions;
    };
} // namespace canvas
