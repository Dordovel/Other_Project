#pragma once
#include "./graphicobject/text.hpp"
#include <memory>
#include <array>

template <size_t N>
std::array<std::shared_ptr<PROJECT::BASE::GRAPHIC::Text>, N> build_items(std::array<std::pair<std::string, std::string>, N>&& listId,
												std::string_view resourcesPath) noexcept
{
	std::array<std::shared_ptr<PROJECT::BASE::GRAPHIC::Text>, N> result;

	size_t index = 0;

	for(const auto& var : listId)
	{
		std::shared_ptr<PROJECT::BASE::GRAPHIC::Text> temp = std::make_shared<PROJECT::BASE::GRAPHIC::Text>(resourcesPath, var.first);
		temp->set_text(var.second);

		result[index] = temp;
		index ++;
	}

	return result;
}


