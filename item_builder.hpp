#pragma once
#include "./graphicobject/text.hpp"
#include <memory>
#include <array>

template <size_t N>
std::array<std::shared_ptr<Text>, N> build_items(std::array<std::pair<std::string, std::string>, N>&& listId,
												const std::string& resourcesPath) noexcept
{
	std::array<std::shared_ptr<Text>, N> result;

	size_t index = 0;

	for(const auto& var : listId)
	{
		std::shared_ptr<Text> temp = std::make_shared<Text>(resourcesPath);
		temp->set_text(var.second);
		temp->set_id(var.first);

		result[index] = temp;
		index ++;
	}

	return result;
}


