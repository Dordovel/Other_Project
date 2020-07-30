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
		this._cellX;
		this._cellY;
	}

	get_cell_width()
	{
		return this._cellWidth;
	}

	get_cell_height()
	{
		return this._cellHeight;
	}

	get_cell_H(element)
	{
		return element.offsetHeight / this.get_cell_height();
	}

	get_cell_W(element)
	{
		return element.offsetWidth / this.get_cell_width()
	}

	change_valueX(line, begin)
	{
		var cells = 0;
		var gridWidth = this._width / this.get_cell_width();
		var mark;

		for (var i = begin; i < line.length; ++i)
		{
			const element = line[i];

			mark = (cells + this.get_cell_W(element) + 1);
			
			if(mark < gridWidth)
			{
				element.style.left = (this._x + this.get_cell_width()) + (cells * this.get_cell_width()) + "px";
				cells = mark;
			}
			else return i;
		}

		return line.length - begin;
	}

	change_valueY_A(line)
	{
		for(var a = 0; a < line.length; ++a)
		{
			line[a].style.top = this._y + this.get_cell_height() + "px";
		}
	}

	change_valueY(line, lastLine, Y)
	{
		if(typeof lastLine !== 'undefined')
		{
			if(lastLine.length == 0)
			{
				this.change_valueY_A(line);
				return;
			}
		}
		else
		{
			this.change_valueY_A(line);
			return;
		}

		var widthLast = 0;
		var heightLast = 0;
		var width = 0;
		var height = 0;
		var posY = 0;
		var LastIndex = 0;
		var currentIndex = 0;
		var mark = false;

		while(true)
		{
			const lastElement = lastLine[LastIndex];
			const curElement = lastLine[currentIndex];

			widthLast = this.get_cell_W(lastElement) * this.get_cell_width();
			heightLast = this.get_cell_H(lastElement) * this.get_cell_height();
			posY = element.offsetTop;
			
			width = this.get_cell_W(line[currentIndex]) * this.get_cell_width();
			height = this.get_cell_H(line[currentIndex]) * this.get_cell_height();
			
			if(width < widthLast)
			{
				if(!mark)
				{
					curElement.style.top = posY + heightLast + this.get_cell_height();
					++currentIndex;
					mark = true;
				}
				else
				{
					var size = this.get_cell_W(line[--currentIndex]) * this.get_cell_width();
					if(((size + width) + this.get_cell_width) < widthLast)
					{
						curElement.style.top = posY + heightLast + this.get_cell_height();
						++currentIndex;
						++LastIndex;
					}
					else 
					{
						++currentIndex;
						++LastIndex;
					}
					mark = false;
				}
				continue;
			}
			if(width == widthLast)
			{
				curElement.style.top = posY + heightLast + this.get_cell_height();
				++currentIndex;
				++LastIndex;
				mark = false;
				continue;
			}

		}
			
	}


	sort(list)
	{
		var collection = document.getElementsByTagName("div");
		var array = Array.prototype.slice.call (collection);

		var end = 0;
		var begin = 0;
		var line = [];
		var lastLine = [];

		var Y = this._y + this.get_cell_height();

		while(end < array.length)
		{
			end += this.change_valueX(array, begin);
			
			line = array.slice(begin);
			this.change_valueY(line, lastLine);

			begin = end;
			lastLine = line;
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

