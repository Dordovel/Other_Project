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
		this._borderOffsetX = 10;
		this._borderOffsetY = 10;
	}

	get_cell_width()
	{
		return this._cellWidth;
	}

	get_cell_height()
	{
		return this._cellHeight;
	}

	get_border_offset_x()
	{
		return this._borderOffsetX;
	}

	get_border_offset_y()
	{
		return this._borderOffsetY;
	}

	convert_element_to_cell_h(element)
	{
		return element.offsetHeight / this.get_cell_height();
	}

	convert_element_to_cell_w(element)
	{
		return element.offsetWidth / this.get_cell_width();
	}
	
	sortY(line, Y)
	{
		var higher = 0;
		var value = 0;

		for(var a = 0; a < line.length; ++a)
		{
			const elem = line[a];

			value = elem.offsetHeight;
			if(higher < value);
			{
				higher = value;
			}

			elem.style.top = Y;
		}

		return higher;
	}

	sortX(line, begin)
	{
		var cells = 0;
		var gridWidth = (this._width - this.get_cell_width()) / this.get_cell_width();
		var mark;

		for (var i = begin; i < line.length; ++i)
		{
			const element = line[i];
			mark = (cells + this.convert_element_to_cell_w(element) + 1);
			
			if((mark) < gridWidth)
			{
				element.style.left = (this._x + this.get_border_offset_x()) + (cells * this.get_cell_width()) + "px";
				cells = mark;
			}
			else return i;
		}

		return line.length - begin;
	}


	sort(list)
	{
		var collection = document.getElementsByTagName("div");
		var array = Array.prototype.slice.call (collection);

		var end = 0;
		var begin = 0;
		var line = [];

		var Y = this._y + this.get_border_offset_y();

		while(end < array.length)
		{
			end += this.sortX(array, begin);
			line = array.slice(begin);
			var y = this.sortY(line, Y);

			Y += y + this.get_cell_width();
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

