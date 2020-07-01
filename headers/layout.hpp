#pragma once 
#include "../Game_Resources/map_loader/include/tmx/MapLoader.hpp"
#include "../Interface/ilayout.hpp"
#include <cstring>
#include <memory>
#include "../struct/collectionobject.hpp"

namespace PROJECT::COLLECTION
{
    class Layout final : public PROJECT::COLLECTION::ILayout
    {   
        private:
            std::shared_ptr<tmx::MapLoader> _mapLoader;
            bool _isVisible;
            std::map<std::string, std::string> _mapStaticObjectInString = {
                    {CollectionObject::TREE, "Tree"}, {CollectionObject::BORDER, "Border"}
                };

            bool check_map_static_object_with_string(std::string object, std::string_view objectName);

            void load_map_from_file(std::string_view pathToMap);

        public:
            Layout(std::string_view pathToMap, std::string_view mapFileName);

            std::map<std::string, std::vector<PROJECT::BASE::DATA::RectangleF>> get_objects(const PROJECT::BASE::DATA::RectangleF &rectangleF) const noexcept override;

            void visible(bool flag) noexcept override;

            bool is_visible() noexcept override;

            PROJECT::BASE::DATA::DrawableObject draw() const noexcept override;

            PROJECT::BASE::DATA::Vector2UI get_size() const noexcept override;

            ~Layout();

			Layout(Layout&&) = default;

			Layout& operator= (Layout&&) = default;

    };
};
