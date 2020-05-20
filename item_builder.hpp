#pragma once
#include "./graphicobject/text.hpp"
#include <vector>
#include <memory>
#include <unordered_map>

std::vector<std::shared_ptr<Text>> build_items(const std::vector<std::pair<std::string, std::string>>& listId,
												const std::string& resourcesPath)
{
	std::vector<std::shared_ptr<Text>> result;

	for(const auto& var : listId)
	{
		std::shared_ptr<Text> temp = std::make_shared<Text>(resourcesPath);
		temp->set_text(var.second);
		temp->set_id(var.first);

		result.emplace_back(temp);
	}

	return result;
}


