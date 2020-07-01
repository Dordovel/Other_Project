#include "../headers/layout.hpp"

#include <utility>
#include "../struct/rectobject.hpp"
#include "../struct/vectorobject.hpp"
#include "../struct/drawableobject.hpp"

namespace PROJECT::COLLECTION
{
    Layout::Layout(std::string_view pathToMap , std::string_view mapFileName):_mapLoader(std::make_shared<tmx::MapLoader>(pathToMap.data())),
                                                                                _isVisible(true)
    {
        std::cout<<pathToMap<< mapFileName<< '\n';
        this->load_map_from_file(mapFileName);
    }

    Layout::~Layout()
    {
        std::cout<<"\t~Layout(): \n";
    }

    void Layout::load_map_from_file(std::string_view pathToFile)
    {
        bool load_map_status = this->_mapLoader->load(pathToFile.data());

        if(!load_map_status)
        {
            std::cout<<"Layout not load"<<std::endl;

            //assert(load_map_status);
        }
    }

    bool Layout::check_map_static_object_with_string(std::string object, std::string_view objectName)
    {
        auto temp = this->_mapStaticObjectInString.find(object);
        if(temp != this->_mapStaticObjectInString.end())
        {
            return (strcmp(objectName.data(), temp->second.c_str()) == 0);
        }

        return false;
    }

    PROJECT::BASE::DATA::Vector2UI Layout::get_size() const noexcept
    {
        return this->_mapLoader->getMapSize();
    }

    PROJECT::BASE::DATA::DrawableObject Layout::draw() const noexcept
    {
        return PROJECT::BASE::DATA::DrawableObject{this->_mapLoader};
    }

    void Layout::visible(bool flag) noexcept
    {
        this->_isVisible = flag;
    }

    bool Layout::is_visible() noexcept
    {
        return this->_isVisible;
    }

    std::map<std::string, std::vector<PROJECT::BASE::DATA::RectangleF>> Layout::get_objects(const PROJECT::BASE::DATA::RectangleF &rectangleF) const noexcept
    {
        std::map<std::string, std::vector<PROJECT::BASE::DATA::RectangleF>> result{};

        this->_mapLoader->updateQuadTree(rectangleF);

        auto mapObjectList = _mapLoader->queryQuadTree(rectangleF);

        for(auto* var : mapObjectList)
        {
            for(auto&& [object, name] : this->_mapStaticObjectInString)
            {
                if(name == var->getParent())
                {
                    auto status = result.emplace(object, std::vector<PROJECT::BASE::DATA::RectangleF>());
                    status.first->second.emplace_back(var->getAABB());
                }
            }
        }

        return result;
    }
};
