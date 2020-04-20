#pragma once

namespace canvas {
    template <typename T, typename U, void (U::*setter)(const T&),
              T (U::*getter)()>
    class Field {
    public:
        Field(U& parent) : m_parent(parent) {}
        Field& operator=(const T& value) {
            setter(value);
            return *this;
        }
        operator T() const { return (m_parent.*getter)(); }

    private:
        U& m_parent;
    };

    template <typename T, typename U, T (U::*getter)()> class Getter {
    public:
        Getter(U& parent) : m_parent(parent) {}
        operator T() const { return (m_parent.*getter)(); }
        template <typename U> bool operator==(const U& rhs) const {
            return static_cast<const T>(*this) == rhs;
        }

    private:
        U& m_parent;
    };

    class DrawStyle;

    template <typename T, typename U, void (U::*setter)(const T&)>
    class Setter {
    public:
        Setter(U& parent) : m_parent(parent) {}
        template <typename V> Setter& operator=(const V& value) {
            (m_parent.*setter)(value);
            return *this;
        }

    private:
        U& m_parent;
    };
} // namespace canvas
