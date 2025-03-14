#include "Guard.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"

// Guard::Guard(const std::string& myselfImagePath) {
//     SetImage(myselfImagePath);
//     m_Transform.scale = {3, 3};
//     SetZIndex(10);
//     LOG_INFO("Guard built");
// }

void Guard::SetImage(const std::string& myselfImagePath) {
    m_myselfImagePath = myselfImagePath;

    m_Drawable = std::make_shared<Util::Image>(m_myselfImagePath);
}