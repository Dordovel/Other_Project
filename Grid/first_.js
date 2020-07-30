function get_table()
{
	return document.getElementById("table");
}

function get_element_width(element)
{
	return table.offsetWidth;
}

function get_element_height(element)
{
	return table.offsetHeight;
}

function get_x(table)
{
	return table.offsetLeft;
}

function get_y(table)
{
	return table.offsetTop;
}

//grid class

class Grid
{
	constructor(x, y, width, height)
	{
		this._x = x;
		this._y = y;
		this._width = width;
		this._height = height;
		this._cellWidth = 23;
		this._cellHeight = 20;
	}

	get_cell_width()
	{
		return this._cellWidth;
	}

	get_cell_height()
	{
		return this._cellHeight;
	}

	get_element_line(array, begin)
	{
		var result = [];
		var sum = this.get_cell_width();

		for(var a = begin; a < array.length; ++a)
		{
			const element = array[a];
			sum += element.offsetWidth + this.get_cell_width();

			if(sum < this._width)
				result.push(element);
			else return result;
		}

		return result;
	}

	change_value(array, Y)
	{
		var posXBegin = this._x + this.get_cell_width();
		var posXEnd = (this._x + this._width) - this.get_cell_width();
		var nextXPos = 0;
		var posX = posXBegin;

		for (var i = 0; i < array.length; ++i)
		{
			const element = array[i];

			element.style.left = posX + "px";
			element.style.top = Y + "px";

			posX = posX + element.offsetWidth + this.get_cell_width();
		}
	}

	get_higher_elem(array)
	{
		var hight = 0;

		for (var a = 0; a < array.length; ++a)
		{
			const elem = array[a];

			if(elem.offsetHeight > hight)
			{
				hight = elem.offsetHeight;
			}
		}

		return hight;
	}

	sort(list)
	{
		var array = document.getElementsByTagName("div");

		var end = 0;
		var begin = 0;
		var arr = [];

		var Y = this._y + this.get_cell_height();

		while (true)
		{
			arr = this.get_element_line(array, begin);
			end += arr.length;
			this.change_value(arr, Y);

			Y = Y + this.get_higher_elem(arr) + this.get_cell_height();

			if(end >= array.length || Y >= this._height + this.get_cell_height())
			{
				break;
			}

			begin = end;
		}
	}
}


window.onload = function()
{
	var table = get_table();

	var list = document.getElementsByTagName("div");

	var grid = new Grid(get_x(table), get_y(table), get_element_width(table), get_element_height(table));
	grid.sort(list);

}

