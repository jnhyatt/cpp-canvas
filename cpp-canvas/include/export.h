#pragma once

#pragma comment(lib, "opengl32.lib")
#pragma warning(disable: 4251)

#ifdef CPP_CANVAS_EXPORT
#define CPP_CANVAS_API __declspec(dllexport)
#else
#define CPP_CANVAS_API __declspec(dllimport)
#endif
