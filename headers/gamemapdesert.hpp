#pragma once 
#include "../Game_Resources/map_loader/include/tmx/MapLoader.hpp"
#include "../Interface/igamemap.hpp"
#include <cstring>
#include <memory>

enum class CollectionObject
{
    BORDER,
    TREE
};

class GameMapDesert : public IMap
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

        GameMapDesert(const std::string& pathToMap , const std::string& mapFileName);

        std::map<CollectionObject, std::vector<RectangleF>> get_objects(const RectangleF &rectangleF) const override;

        void set_id(const std::string& id) override;

        std::string get_id() const override;

        void visible(bool flag) override;

        bool is_visible() override;

        DrawableObject draw() const override;

        unsigned int get_map_size_x() const override;

        unsigned int get_map_size_y() const override;

		~GameMapDesert() = default;
};
