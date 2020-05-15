#include "../headers/layout.hpp"

#include <utility>
#include "../struct/rectobject.hpp"
#include "../struct/vectorobject.hpp"
#include "../struct/drawableobject.hpp"

Layout::Layout(const std::string& pathToMap , const std::string& mapFileName):_mapLoader(std::make_shared<tmx::MapLoader>(pathToMap)),
                                                                                _isVisible(true)
{
	std::cout<<pathToMap + mapFileName<<std::endl;
    this->load_map_from_file(mapFileName);
}

Layout::~Layout()
{
	std::cout<<this->get_id()<<"	Deleted"<<std::endl;
}

void Layout::load_map_from_file(const std::string& pathToFile)
{
    bool load_map_status = this->_mapLoader->load(pathToFile);

	if(!load_map_status)
	{
		std::cout<<"Layout not load"<<std::endl;

		//assert(load_map_status);
	}
}

bool Layout::check_map_static_object_with_string(CollectionObject object, const std::string& objectName)
{
    auto temp = this->_mapStaticObjectInString.find(object);
    if(temp != this->_mapStaticObjectInString.end())
    {
        return (strcmp(objectName.c_str(), temp->second.c_str()) == 0);
    }

    return false;
}

Vector2UI Layout::get_size() const
{
    return this->_mapLoader->getMapSize();
}
DrawableObject Layout::draw() const
{
    return DrawableObject{this->_mapLoader};
}

void Layout::set_id(const std::string& id)
{
    this->_id = id;
}

std::string Layout::get_id() const
{
    return this->_id;
}

void Layout::visible(bool flag)
{
    this->_isVisible = flag;
}

bool Layout::is_visible()
{
    return this->_isVisible;
}

std::map<CollectionObject, std::vector<RectangleF>> Layout::get_objects(const RectangleF &rectangleF) const
{
    std::map<CollectionObject, std::vector<RectangleF>> result{};

    this->_mapLoader->updateQuadTree(rectangleF);

    auto mapObjectList = _mapLoader->queryQuadTree(rectangleF);

    for(auto var : mapObjectList)
    {
        for(auto&& [object, name] : this->_mapStaticObjectInString)
        {
            if(name == var->getParent())
            {
                auto status = result.emplace(object, std::vector<RectangleF>());
                status.first->second.emplace_back(var->getAABB());
            }
        }
    }

    return result;
}
