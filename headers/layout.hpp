#ifndef SFMLPROJECT_REBUILD_LAYOUT_HPP
#define SFMLPROJECT_REBUILD_LAYOUT_HPP

#include "../Interface/ilayout.hpp"
#include <cstring>
#include <memory>
#include "../struct/static_object_collection.hpp"


namespace tmx
{
	class MapLoader;
};

namespace PROJECT::COLLECTION
{
    class Layout final : public PROJECT::COLLECTION::ILayout
    {   
        private:
			std::unique_ptr<tmx::MapLoader> _mapLoader;
            bool _isVisible;
            std::vector<std::pair<std::string, std::string>> _mapStaticObjectInString = {
                    {StaticObjectCollection::TREE, "Tree"}, {StaticObjectCollection::BORDER, "Border"}
                };

            bool _check_map_static_object_with_string(std::string object, std::string_view objectName);

            void _load_map_from_file(std::string_view pathToFile);

        public:
            Layout(std::string_view pathToMap, std::string_view mapFileName);

            std::map<std::string, std::vector<PROJECT::BASE::DATA::RectangleF>> 
				get_objects(PROJECT::BASE::DATA::RectangleF rectangleF) const noexcept override;

            void visible(bool flag) noexcept override;

            bool is_visible() noexcept override;

            PROJECT::BASE::DATA::DrawableObject draw() const noexcept override;

            PROJECT::BASE::DATA::Vector2UI get_size() const noexcept override;

            ~Layout();

			Layout(Layout&&) = default;

			Layout& operator= (Layout&&) = default;

    };
};
#endif //SFMLPROJECT_REBUILD_LAYOUT_HPP
