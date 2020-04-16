#include "color.h"

#include <algorithm>
#include <unordered_map>

std::unordered_map<std::string, vec4> namedColors = {
    {"aliceblue", vec4(0.941f, 0.973f, 1.000f, 1.0f)},
    {"antiquewhite", vec4(0.980f, 0.922f, 0.843f, 1.0f)},
    {"aqua", vec4(0.000f, 1.000f, 1.000f, 1.0f)},
    {"aquamarine", vec4(0.498f, 1.000f, 0.831f, 1.0f)},
    {"azure", vec4(0.941f, 1.000f, 1.000f, 1.0f)},
    {"beige", vec4(0.961f, 0.961f, 0.863f, 1.0f)},
    {"bisque", vec4(1.000f, 0.894f, 0.769f, 1.0f)},
    {"black", vec4(0.000f, 0.000f, 0.000f, 1.0f)},
    {"blanchedalmond", vec4(1.000f, 0.922f, 0.804f, 1.0f)},
    {"blue", vec4(0.000f, 0.000f, 1.000f, 1.0f)},
    {"blueviolet", vec4(0.541f, 0.169f, 0.886f, 1.0f)},
    {"brown", vec4(0.647f, 0.165f, 0.165f, 1.0f)},
    {"burlywood", vec4(0.871f, 0.722f, 0.529f, 1.0f)},
    {"cadetblue", vec4(0.373f, 0.620f, 0.627f, 1.0f)},
    {"chartreuse", vec4(0.498f, 1.000f, 0.000f, 1.0f)},
    {"chocolate", vec4(0.824f, 0.412f, 0.118f, 1.0f)},
    {"coral", vec4(1.000f, 0.498f, 0.314f, 1.0f)},
    {"cornflowerblue", vec4(0.392f, 0.584f, 0.929f, 1.0f)},
    {"cornsilk", vec4(1.000f, 0.973f, 0.863f, 1.0f)},
    {"crimson", vec4(0.863f, 0.078f, 0.235f, 1.0f)},
    {"cyan", vec4(0.000f, 1.000f, 1.000f, 1.0f)},
    {"darkblue", vec4(0.000f, 0.000f, 0.545f, 1.0f)},
    {"darkcyan", vec4(0.000f, 0.545f, 0.545f, 1.0f)},
    {"darkgoldenrod", vec4(0.722f, 0.525f, 0.043f, 1.0f)},
    {"darkgray", vec4(0.663f, 0.663f, 0.663f, 1.0f)},
    {"darkgrey", vec4(0.663f, 0.663f, 0.663f, 1.0f)},
    {"darkgreen", vec4(0.000f, 0.392f, 0.000f, 1.0f)},
    {"darkkhaki", vec4(0.741f, 0.718f, 0.420f, 1.0f)},
    {"darkmagenta", vec4(0.545f, 0.000f, 0.545f, 1.0f)},
    {"darkolivegreen", vec4(0.333f, 0.420f, 0.184f, 1.0f)},
    {"darkorange", vec4(1.000f, 0.549f, 0.000f, 1.0f)},
    {"darkorchid", vec4(0.600f, 0.196f, 0.800f, 1.0f)},
    {"darkred", vec4(0.545f, 0.000f, 0.000f, 1.0f)},
    {"darksalmon", vec4(0.914f, 0.588f, 0.478f, 1.0f)},
    {"darkseagreen", vec4(0.561f, 0.737f, 0.561f, 1.0f)},
    {"darkslateblue", vec4(0.282f, 0.239f, 0.545f, 1.0f)},
    {"darkslategray", vec4(0.184f, 0.310f, 0.310f, 1.0f)},
    {"darkslategrey", vec4(0.184f, 0.310f, 0.310f, 1.0f)},
    {"darkturquoise", vec4(0.000f, 0.808f, 0.820f, 1.0f)},
    {"darkviolet", vec4(0.580f, 0.000f, 0.827f, 1.0f)},
    {"deeppink", vec4(1.000f, 0.078f, 0.576f, 1.0f)},
    {"deepskyblue", vec4(0.000f, 0.749f, 1.000f, 1.0f)},
    {"dimgray", vec4(0.412f, 0.412f, 0.412f, 1.0f)},
    {"dimgrey", vec4(0.412f, 0.412f, 0.412f, 1.0f)},
    {"dodgerblue", vec4(0.118f, 0.565f, 1.000f, 1.0f)},
    {"firebrick", vec4(0.698f, 0.133f, 0.133f, 1.0f)},
    {"floralwhite", vec4(1.000f, 0.980f, 0.941f, 1.0f)},
    {"forestgreen", vec4(0.133f, 0.545f, 0.133f, 1.0f)},
    {"fuchsia", vec4(1.000f, 0.000f, 1.000f, 1.0f)},
    {"gainsboro", vec4(0.863f, 0.863f, 0.863f, 1.0f)},
    {"ghostwhite", vec4(0.973f, 0.973f, 1.000f, 1.0f)},
    {"gold", vec4(1.000f, 0.843f, 0.000f, 1.0f)},
    {"goldenrod", vec4(0.855f, 0.647f, 0.125f, 1.0f)},
    {"gray", vec4(0.502f, 0.502f, 0.502f, 1.0f)},
    {"grey", vec4(0.502f, 0.502f, 0.502f, 1.0f)},
    {"green", vec4(0.000f, 0.502f, 0.000f, 1.0f)},
    {"greenyellow", vec4(0.678f, 1.000f, 0.184f, 1.0f)},
    {"honeydew", vec4(0.941f, 1.000f, 0.941f, 1.0f)},
    {"hotpink", vec4(1.000f, 0.412f, 0.706f, 1.0f)},
    {"indianred", vec4(0.804f, 0.361f, 0.361f, 1.0f)},
    {"indigo", vec4(0.294f, 0.000f, 0.510f, 1.0f)},
    {"ivory", vec4(1.000f, 1.000f, 0.941f, 1.0f)},
    {"khaki", vec4(0.941f, 0.902f, 0.549f, 1.0f)},
    {"lavender", vec4(0.902f, 0.902f, 0.980f, 1.0f)},
    {"lavenderblush", vec4(1.000f, 0.941f, 0.961f, 1.0f)},
    {"lawngreen", vec4(0.486f, 0.988f, 0.000f, 1.0f)},
    {"lemonchiffon", vec4(1.000f, 0.980f, 0.804f, 1.0f)},
    {"lightblue", vec4(0.678f, 0.847f, 0.902f, 1.0f)},
    {"lightcoral", vec4(0.941f, 0.502f, 0.502f, 1.0f)},
    {"lightcyan", vec4(0.878f, 1.000f, 1.000f, 1.0f)},
    {"lightgoldenrodyellow", vec4(0.980f, 0.980f, 0.824f, 1.0f)},
    {"lightgray", vec4(0.827f, 0.827f, 0.827f, 1.0f)},
    {"lightgrey", vec4(0.827f, 0.827f, 0.827f, 1.0f)},
    {"lightgreen", vec4(0.565f, 0.933f, 0.565f, 1.0f)},
    {"lightpink", vec4(1.000f, 0.714f, 0.757f, 1.0f)},
    {"lightsalmon", vec4(1.000f, 0.627f, 0.478f, 1.0f)},
    {"lightseagreen", vec4(0.125f, 0.698f, 0.667f, 1.0f)},
    {"lightskyblue", vec4(0.529f, 0.808f, 0.980f, 1.0f)},
    {"lightslategray", vec4(0.467f, 0.533f, 0.600f, 1.0f)},
    {"lightslategrey", vec4(0.467f, 0.533f, 0.600f, 1.0f)},
    {"lightsteelblue", vec4(0.690f, 0.769f, 0.871f, 1.0f)},
    {"lightyellow", vec4(1.000f, 1.000f, 0.878f, 1.0f)},
    {"lime", vec4(0.000f, 1.000f, 0.000f, 1.0f)},
    {"limegreen", vec4(0.196f, 0.804f, 0.196f, 1.0f)},
    {"linen", vec4(0.980f, 0.941f, 0.902f, 1.0f)},
    {"magenta", vec4(1.000f, 0.000f, 1.000f, 1.0f)},
    {"maroon", vec4(0.502f, 0.000f, 0.000f, 1.0f)},
    {"mediumaquamarine", vec4(0.400f, 0.804f, 0.667f, 1.0f)},
    {"mediumblue", vec4(0.000f, 0.000f, 0.804f, 1.0f)},
    {"mediumorchid", vec4(0.729f, 0.333f, 0.827f, 1.0f)},
    {"mediumpurple", vec4(0.576f, 0.439f, 0.859f, 1.0f)},
    {"mediumseagreen", vec4(0.235f, 0.702f, 0.443f, 1.0f)},
    {"mediumslateblue", vec4(0.482f, 0.408f, 0.933f, 1.0f)},
    {"mediumspringgreen", vec4(0.000f, 0.980f, 0.604f, 1.0f)},
    {"mediumturquoise", vec4(0.282f, 0.820f, 0.800f, 1.0f)},
    {"mediumvioletred", vec4(0.780f, 0.082f, 0.522f, 1.0f)},
    {"midnightblue", vec4(0.098f, 0.098f, 0.439f, 1.0f)},
    {"mintcream", vec4(0.961f, 1.000f, 0.980f, 1.0f)},
    {"mistyrose", vec4(1.000f, 0.894f, 0.882f, 1.0f)},
    {"moccasin", vec4(1.000f, 0.894f, 0.710f, 1.0f)},
    {"navajowhite", vec4(1.000f, 0.871f, 0.678f, 1.0f)},
    {"navy", vec4(0.000f, 0.000f, 0.502f, 1.0f)},
    {"oldlace", vec4(0.992f, 0.961f, 0.902f, 1.0f)},
    {"olive", vec4(0.502f, 0.502f, 0.000f, 1.0f)},
    {"olivedrab", vec4(0.420f, 0.557f, 0.137f, 1.0f)},
    {"orange", vec4(1.000f, 0.647f, 0.000f, 1.0f)},
    {"orangered", vec4(1.000f, 0.271f, 0.000f, 1.0f)},
    {"orchid", vec4(0.855f, 0.439f, 0.839f, 1.0f)},
    {"palegoldenrod", vec4(0.933f, 0.910f, 0.667f, 1.0f)},
    {"palegreen", vec4(0.596f, 0.984f, 0.596f, 1.0f)},
    {"paleturquoise", vec4(0.686f, 0.933f, 0.933f, 1.0f)},
    {"palevioletred", vec4(0.859f, 0.439f, 0.576f, 1.0f)},
    {"papayawhip", vec4(1.000f, 0.937f, 0.835f, 1.0f)},
    {"peachpuff", vec4(1.000f, 0.855f, 0.725f, 1.0f)},
    {"peru", vec4(0.804f, 0.522f, 0.247f, 1.0f)},
    {"pink", vec4(1.000f, 0.753f, 0.796f, 1.0f)},
    {"plum", vec4(0.867f, 0.627f, 0.867f, 1.0f)},
    {"powderblue", vec4(0.690f, 0.878f, 0.902f, 1.0f)},
    {"purple", vec4(0.502f, 0.000f, 0.502f, 1.0f)},
    {"rebeccapurple", vec4(0.400f, 0.200f, 0.600f, 1.0f)},
    {"red", vec4(1.000f, 0.000f, 0.000f, 1.0f)},
    {"rosybrown", vec4(0.737f, 0.561f, 0.561f, 1.0f)},
    {"royalblue", vec4(0.255f, 0.412f, 0.882f, 1.0f)},
    {"saddlebrown", vec4(0.545f, 0.271f, 0.075f, 1.0f)},
    {"salmon", vec4(0.980f, 0.502f, 0.447f, 1.0f)},
    {"sandybrown", vec4(0.957f, 0.643f, 0.376f, 1.0f)},
    {"seagreen", vec4(0.180f, 0.545f, 0.341f, 1.0f)},
    {"seashell", vec4(1.000f, 0.961f, 0.933f, 1.0f)},
    {"sienna", vec4(0.627f, 0.322f, 0.176f, 1.0f)},
    {"silver", vec4(0.753f, 0.753f, 0.753f, 1.0f)},
    {"skyblue", vec4(0.529f, 0.808f, 0.922f, 1.0f)},
    {"slateblue", vec4(0.416f, 0.353f, 0.804f, 1.0f)},
    {"slategray", vec4(0.439f, 0.502f, 0.565f, 1.0f)},
    {"slategrey", vec4(0.439f, 0.502f, 0.565f, 1.0f)},
    {"snow", vec4(1.000f, 0.980f, 0.980f, 1.0f)},
    {"springgreen", vec4(0.000f, 1.000f, 0.498f, 1.0f)},
    {"steelblue", vec4(0.275f, 0.510f, 0.706f, 1.0f)},
    {"tan", vec4(0.824f, 0.706f, 0.549f, 1.0f)},
    {"teal", vec4(0.000f, 0.502f, 0.502f, 1.0f)},
    {"thistle", vec4(0.847f, 0.749f, 0.847f, 1.0f)},
    {"tomato", vec4(1.000f, 0.388f, 0.278f, 1.0f)},
    {"turquoise", vec4(0.251f, 0.878f, 0.816f, 1.0f)},
    {"violet", vec4(0.933f, 0.510f, 0.933f, 1.0f)},
    {"wheat", vec4(0.961f, 0.871f, 0.702f, 1.0f)},
    {"white", vec4(1.000f, 1.000f, 1.000f, 1.0f)},
    {"whitesmoke", vec4(0.961f, 0.961f, 0.961f, 1.0f)},
    {"yellow", vec4(1.000f, 1.000f, 0.000f, 1.0f)},
    {"yellowgreen", vec4(0.604f, 0.804f, 0.196f, 1.0f)},
};

Color::Color() : m_color(0.0f, 0.0f, 0.0f, 1.0f) {}

Color::Color(vec3 rgb) : m_color(rgb, 1.0f) {}

Color::Color(vec4 rgba) : m_color(rgba) {}

Color::Color(float r, float g, float b) : m_color(r, g, b, 1.0f) {}

Color::Color(float r, float g, float b, float a) : m_color(r, g, b, a) {}

Color::Color(const std::string& str) : Color(fromString(str)) {}

vec4 Color::asVec4() const { return m_color; }

Color Color::fromString(const std::string& str) {
    return str[0] == '#' ? Color::parseHex(str) : Color::named(str);
}

Color Color::named(std::string name) {
    std::transform(name.begin(), name.end(), name.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return namedColors[name];
}

Color Color::parseHex(const std::string& hex) {
    vec4 rgba(1.0f, 1.0f, 1.0f, 1.0f);
    switch (hex.length()) {
    case 4: // #rgb
        rgba.r = std::strtol(hex.substr(1, 1).c_str(), nullptr, 16) / 15.0f;
        rgba.g = std::strtol(hex.substr(2, 1).c_str(), nullptr, 16) / 15.0f;
        rgba.b = std::strtol(hex.substr(3, 1).c_str(), nullptr, 16) / 15.0f;
        break;
    case 5: // #rgba
        rgba.r = std::strtol(hex.substr(1, 1).c_str(), nullptr, 16) / 15.0f;
        rgba.g = std::strtol(hex.substr(2, 1).c_str(), nullptr, 16) / 15.0f;
        rgba.b = std::strtol(hex.substr(3, 1).c_str(), nullptr, 16) / 15.0f;
        rgba.a = std::strtol(hex.substr(4, 1).c_str(), nullptr, 16) / 15.0f;
        break;
    case 7: // #rrggbb
        rgba.r = std::strtol(hex.substr(1, 2).c_str(), nullptr, 16) / 255.0f;
        rgba.g = std::strtol(hex.substr(3, 2).c_str(), nullptr, 16) / 255.0f;
        rgba.b = std::strtol(hex.substr(5, 2).c_str(), nullptr, 16) / 255.0f;
        break;
    case 9: // #rrggbbaa
        rgba.r = std::strtol(hex.substr(1, 2).c_str(), nullptr, 16) / 255.0f;
        rgba.g = std::strtol(hex.substr(3, 2).c_str(), nullptr, 16) / 255.0f;
        rgba.b = std::strtol(hex.substr(5, 2).c_str(), nullptr, 16) / 255.0f;
        rgba.a = std::strtol(hex.substr(7, 2).c_str(), nullptr, 16) / 255.0f;
        break;
    }
    return Color(rgba);
}
