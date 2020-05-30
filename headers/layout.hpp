#pragma once 
#include "../Game_Resources/map_loader/include/tmx/MapLoader.hpp"
#include "../Interface/ilayout.hpp"
#include <cstring>
#include <memory>
#include "../struct/colllectionobject.hpp"


class Layout final : public ILayout
{   
    private:
        std::shared_ptr<tmx::MapLoader> _mapLoader;
        std::string  _id;
        bool _isVisible;
        std::map<CollectionObject, std::string> _mapStaticObjectInString = {
                {CollectionObject::TREE, "Tree"}, {CollectionObject::BORDER, "Border"}
            };

        bool check_map_static_object_with_string(CollectionObject object, const std::string& objectName);

        void load_map_from_file(const std::string& pathToMap);

    public:
        Layout(const std::string& pathToMap , const std::string& mapFileName);

        std::map<CollectionObject, std::vector<RectangleF>> get_objects(const RectangleF &rectangleF) const noexcept override;

        void set_id(const std::string& id) noexcept override;

        std::string get_id() const noexcept override;

        void visible(bool flag) noexcept override;

        bool is_visible() noexcept override;

        DrawableObject draw() const noexcept override;

        Vector2UI get_size() const noexcept override;

		~Layout();
};
