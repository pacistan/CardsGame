#pragma once

enum class ETileType : uint32;

class SerializableTile
{
public:
	ETileType TileType;

	int32 Row;
	int32 Column;

	SerializableTile(ETileType tileType, int32 row, int32 column)
	{
		TileType = tileType;
		Row = row;
		Column = column;
	}
};
