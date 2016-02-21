// Fill out your copyright notice in the Description page of Project Settings.

#include "cashgenUE.h"
#include "WorldGenerator.h"
#include "Kismet/KismetMathLibrary.h"


TArray<GridRow>* WorldGenerator::GetTerrainGrid()
{
	return &MyGrid;
}

int8 WorldGenerator::InitialiseTerrainGrid(int aX, int aY)
{
	for (int x = 0; x < aX; ++x)
	{
		GridRow row;
		for (int y = 0; y < aY; ++y)
		{
			row.blocks.Add(ZoneBlock(FMath::RandRange(0,5) * 100.0f, FColor::Cyan, x, y));
		}
		MyGrid.Add(row);
	}

	// Now set the LRUD pointers
	for (int x = 0; x < aX; ++x)
	{
		for (int y = 0; y < aY; ++y)
		{ 
			// Bottom left case
			if (x == 0 && y == 0)
			{
				MyGrid[x].blocks[y].topLeftCorner.topLeftBlock = nullptr;
				MyGrid[x].blocks[y].topLeftCorner.topRightBlock = &MyGrid[x].blocks[y + 1];
				MyGrid[x].blocks[y].topLeftCorner.bottomLeftBlock = nullptr;
				MyGrid[x].blocks[y].topLeftCorner.bottomRightBlock = &MyGrid[x].blocks[y];

				MyGrid[x].blocks[y].topRightCorner.topLeftBlock = &MyGrid[x].blocks[y + 1];
				MyGrid[x].blocks[y].topRightCorner.topRightBlock = &MyGrid[x + 1].blocks[y + 1];
				MyGrid[x].blocks[y].topRightCorner.bottomLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].topRightCorner.bottomRightBlock = &MyGrid[x + 1].blocks[y];

				MyGrid[x].blocks[y].bottomLeftCorner.topLeftBlock = nullptr;
				MyGrid[x].blocks[y].bottomLeftCorner.topRightBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomLeftCorner.bottomLeftBlock = nullptr;
				MyGrid[x].blocks[y].bottomLeftCorner.bottomRightBlock = nullptr;

				MyGrid[x].blocks[y].bottomRightCorner.topLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomRightCorner.topRightBlock = &MyGrid[x + 1].blocks[y];
				MyGrid[x].blocks[y].bottomRightCorner.bottomLeftBlock = nullptr;
				MyGrid[x].blocks[y].bottomRightCorner.bottomRightBlock = nullptr;
			}
			// top left case
			if (x == 0 && y == aY -1)
			{
				MyGrid[x].blocks[y].topLeftCorner.topLeftBlock = nullptr;
				MyGrid[x].blocks[y].topLeftCorner.topRightBlock = nullptr;
				MyGrid[x].blocks[y].topLeftCorner.bottomLeftBlock = nullptr;
				MyGrid[x].blocks[y].topLeftCorner.bottomRightBlock = &MyGrid[x].blocks[y];

				MyGrid[x].blocks[y].topRightCorner.topLeftBlock = nullptr;
				MyGrid[x].blocks[y].topRightCorner.topRightBlock = nullptr;
				MyGrid[x].blocks[y].topRightCorner.bottomLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].topRightCorner.bottomRightBlock = &MyGrid[x + 1].blocks[y];

				MyGrid[x].blocks[y].bottomLeftCorner.topLeftBlock = nullptr;
				MyGrid[x].blocks[y].bottomLeftCorner.topRightBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomLeftCorner.bottomLeftBlock = nullptr;
				MyGrid[x].blocks[y].bottomLeftCorner.bottomRightBlock = &MyGrid[x].blocks[y - 1];

				MyGrid[x].blocks[y].bottomRightCorner.topLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomRightCorner.topRightBlock = &MyGrid[x + 1].blocks[y];
				MyGrid[x].blocks[y].bottomRightCorner.bottomLeftBlock = &MyGrid[x].blocks[y - 1];
				MyGrid[x].blocks[y].bottomRightCorner.bottomRightBlock = &MyGrid[x + 1].blocks[y - 1];
			}
			// top right case
			if (x == aX - 1 && y == aY - 1)
			{
				MyGrid[x].blocks[y].topLeftCorner.topLeftBlock = nullptr;
				MyGrid[x].blocks[y].topLeftCorner.topRightBlock = nullptr;
				MyGrid[x].blocks[y].topLeftCorner.bottomLeftBlock = &MyGrid[x - 1].blocks[y];
				MyGrid[x].blocks[y].topLeftCorner.bottomRightBlock = &MyGrid[x].blocks[y];

				MyGrid[x].blocks[y].topRightCorner.topLeftBlock = nullptr;
				MyGrid[x].blocks[y].topRightCorner.topRightBlock = nullptr;
				MyGrid[x].blocks[y].topRightCorner.bottomLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].topRightCorner.bottomRightBlock = nullptr;

				MyGrid[x].blocks[y].bottomLeftCorner.topLeftBlock = &MyGrid[x - 1].blocks[y];
				MyGrid[x].blocks[y].bottomLeftCorner.topRightBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomLeftCorner.bottomLeftBlock = &MyGrid[x - 1].blocks[y - 1];
				MyGrid[x].blocks[y].bottomLeftCorner.bottomRightBlock = &MyGrid[x].blocks[y - 1];

				MyGrid[x].blocks[y].bottomRightCorner.topLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomRightCorner.topRightBlock = nullptr;
				MyGrid[x].blocks[y].bottomRightCorner.bottomLeftBlock = &MyGrid[x].blocks[y - 1];
				MyGrid[x].blocks[y].bottomRightCorner.bottomRightBlock = nullptr;
			}
			// bottom right case
			if (x == aX - 1 && y == 0)
			{
				MyGrid[x].blocks[y].topLeftCorner.topLeftBlock = &MyGrid[x - 1].blocks[y + 1];
				MyGrid[x].blocks[y].topLeftCorner.topRightBlock = &MyGrid[x].blocks[y + 1];
				MyGrid[x].blocks[y].topLeftCorner.bottomLeftBlock = &MyGrid[x - 1].blocks[y];
				MyGrid[x].blocks[y].topLeftCorner.bottomRightBlock = &MyGrid[x].blocks[y];

				MyGrid[x].blocks[y].topRightCorner.topLeftBlock = &MyGrid[x].blocks[y + 1];
				MyGrid[x].blocks[y].topRightCorner.topRightBlock = nullptr;
				MyGrid[x].blocks[y].topRightCorner.bottomLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].topRightCorner.bottomRightBlock = nullptr;

				MyGrid[x].blocks[y].bottomLeftCorner.topLeftBlock = &MyGrid[x - 1].blocks[y];
				MyGrid[x].blocks[y].bottomLeftCorner.topRightBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomLeftCorner.bottomLeftBlock = nullptr;
				MyGrid[x].blocks[y].bottomLeftCorner.bottomRightBlock = nullptr;

				MyGrid[x].blocks[y].bottomRightCorner.topLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomRightCorner.topRightBlock = nullptr;
				MyGrid[x].blocks[y].bottomRightCorner.bottomLeftBlock = nullptr;
				MyGrid[x].blocks[y].bottomRightCorner.bottomRightBlock = nullptr;
			}

			// Set left edge pointers
			if (x == 0 && y > 0 && y < aY - 1)
			{
				MyGrid[x].blocks[y].topLeftCorner.topLeftBlock = nullptr;
				MyGrid[x].blocks[y].topLeftCorner.topRightBlock = &MyGrid[x].blocks[y + 1];
				MyGrid[x].blocks[y].topLeftCorner.bottomLeftBlock = nullptr;
				MyGrid[x].blocks[y].topLeftCorner.bottomRightBlock = &MyGrid[x].blocks[y];

				MyGrid[x].blocks[y].topRightCorner.topLeftBlock = &MyGrid[x].blocks[y + 1];
				MyGrid[x].blocks[y].topRightCorner.topRightBlock = &MyGrid[x + 1].blocks[y + 1];
				MyGrid[x].blocks[y].topRightCorner.bottomLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].topRightCorner.bottomRightBlock = &MyGrid[x + 1].blocks[y];

				MyGrid[x].blocks[y].bottomLeftCorner.topLeftBlock = nullptr;
				MyGrid[x].blocks[y].bottomLeftCorner.topRightBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomLeftCorner.bottomLeftBlock = nullptr;
				MyGrid[x].blocks[y].bottomLeftCorner.bottomRightBlock = &MyGrid[x].blocks[y - 1];

				MyGrid[x].blocks[y].bottomRightCorner.topLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomRightCorner.topRightBlock = &MyGrid[x + 1].blocks[y];
				MyGrid[x].blocks[y].bottomRightCorner.bottomLeftBlock = &MyGrid[x].blocks[y - 1];
				MyGrid[x].blocks[y].bottomRightCorner.bottomRightBlock = &MyGrid[x + 1].blocks[y - 1];
			}
			// Set right edge pointers
			if (x == aX - 1 && y > 0 && y < aY - 1) {
				MyGrid[x].blocks[y].topLeftCorner.topLeftBlock = &MyGrid[x - 1].blocks[y + 1];
				MyGrid[x].blocks[y].topLeftCorner.topRightBlock = &MyGrid[x].blocks[y + 1];
				MyGrid[x].blocks[y].topLeftCorner.bottomLeftBlock = &MyGrid[x - 1].blocks[y];
				MyGrid[x].blocks[y].topLeftCorner.bottomRightBlock = &MyGrid[x].blocks[y];

				MyGrid[x].blocks[y].topRightCorner.topLeftBlock = &MyGrid[x].blocks[y + 1];
				MyGrid[x].blocks[y].topRightCorner.topRightBlock = nullptr;
				MyGrid[x].blocks[y].topRightCorner.bottomLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].topRightCorner.bottomRightBlock = nullptr;

				MyGrid[x].blocks[y].bottomLeftCorner.topLeftBlock = &MyGrid[x - 1].blocks[y];
				MyGrid[x].blocks[y].bottomLeftCorner.topRightBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomLeftCorner.bottomLeftBlock = &MyGrid[x - 1].blocks[y - 1];
				MyGrid[x].blocks[y].bottomLeftCorner.bottomRightBlock = &MyGrid[x].blocks[y - 1];

				MyGrid[x].blocks[y].bottomRightCorner.topLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomRightCorner.topRightBlock = nullptr;
				MyGrid[x].blocks[y].bottomRightCorner.bottomLeftBlock = &MyGrid[x].blocks[y - 1];
				MyGrid[x].blocks[y].bottomRightCorner.bottomRightBlock = nullptr;
			}
			// Set bottom edge pointers
			if (y == 0 && x > 0 && x < aX -1) {
				MyGrid[x].blocks[y].topLeftCorner.topLeftBlock = &MyGrid[x - 1].blocks[y + 1];
				MyGrid[x].blocks[y].topLeftCorner.topRightBlock = &MyGrid[x].blocks[y + 1];
				MyGrid[x].blocks[y].topLeftCorner.bottomLeftBlock = &MyGrid[x - 1].blocks[y];
				MyGrid[x].blocks[y].topLeftCorner.bottomRightBlock = &MyGrid[x].blocks[y];

				MyGrid[x].blocks[y].topRightCorner.topLeftBlock = &MyGrid[x].blocks[y + 1];
				MyGrid[x].blocks[y].topRightCorner.topRightBlock = &MyGrid[x + 1].blocks[y + 1];
				MyGrid[x].blocks[y].topRightCorner.bottomLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].topRightCorner.bottomRightBlock = &MyGrid[x + 1].blocks[y];

				MyGrid[x].blocks[y].bottomLeftCorner.topLeftBlock = &MyGrid[x - 1].blocks[y];
				MyGrid[x].blocks[y].bottomLeftCorner.topRightBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomLeftCorner.bottomLeftBlock = nullptr;
				MyGrid[x].blocks[y].bottomLeftCorner.bottomRightBlock = nullptr;

				MyGrid[x].blocks[y].bottomRightCorner.topLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomRightCorner.topRightBlock = &MyGrid[x + 1].blocks[y];
				MyGrid[x].blocks[y].bottomRightCorner.bottomLeftBlock = nullptr;
				MyGrid[x].blocks[y].bottomRightCorner.bottomRightBlock = nullptr;
			}
			// Set top edge pointers
			if (y == aY - 1 && x > 0 && x < aX -1) {
				MyGrid[x].blocks[y].topLeftCorner.topLeftBlock = nullptr;
				MyGrid[x].blocks[y].topLeftCorner.topRightBlock = nullptr;
				MyGrid[x].blocks[y].topLeftCorner.bottomLeftBlock = &MyGrid[x - 1].blocks[y];
				MyGrid[x].blocks[y].topLeftCorner.bottomRightBlock = &MyGrid[x].blocks[y];

				MyGrid[x].blocks[y].topRightCorner.topLeftBlock = nullptr;
				MyGrid[x].blocks[y].topRightCorner.topRightBlock = nullptr;
				MyGrid[x].blocks[y].topRightCorner.bottomLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].topRightCorner.bottomRightBlock = &MyGrid[x + 1].blocks[y];

				MyGrid[x].blocks[y].bottomLeftCorner.topLeftBlock = &MyGrid[x - 1].blocks[y];
				MyGrid[x].blocks[y].bottomLeftCorner.topRightBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomLeftCorner.bottomLeftBlock = &MyGrid[x - 1].blocks[y - 1];
				MyGrid[x].blocks[y].bottomLeftCorner.bottomRightBlock = &MyGrid[x].blocks[y - 1];

				MyGrid[x].blocks[y].bottomRightCorner.topLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomRightCorner.topRightBlock = &MyGrid[x + 1].blocks[y];
				MyGrid[x].blocks[y].bottomRightCorner.bottomLeftBlock = &MyGrid[x].blocks[y - 1];
				MyGrid[x].blocks[y].bottomRightCorner.bottomRightBlock = &MyGrid[x + 1].blocks[y - 1];
			}

			// Normal cases :
			if (x > 0 && x < aX - 1 && y > 0 && y < aY - 1) {
				MyGrid[x].blocks[y].topLeftCorner.topLeftBlock = &MyGrid[x - 1].blocks[y + 1];
				MyGrid[x].blocks[y].topLeftCorner.topRightBlock = &MyGrid[x].blocks[y + 1];
				MyGrid[x].blocks[y].topLeftCorner.bottomLeftBlock = &MyGrid[x - 1].blocks[y];
				MyGrid[x].blocks[y].topLeftCorner.bottomRightBlock = &MyGrid[x].blocks[y];

				MyGrid[x].blocks[y].topRightCorner.topLeftBlock = &MyGrid[x].blocks[y + 1];
				MyGrid[x].blocks[y].topRightCorner.topRightBlock = &MyGrid[x + 1].blocks[y + 1];
				MyGrid[x].blocks[y].topRightCorner.bottomLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].topRightCorner.bottomRightBlock = &MyGrid[x + 1].blocks[y];

				MyGrid[x].blocks[y].bottomLeftCorner.topLeftBlock = &MyGrid[x - 1].blocks[y];
				MyGrid[x].blocks[y].bottomLeftCorner.topRightBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomLeftCorner.bottomLeftBlock = &MyGrid[x - 1].blocks[y - 1];
				MyGrid[x].blocks[y].bottomLeftCorner.bottomRightBlock = &MyGrid[x].blocks[y - 1];

				MyGrid[x].blocks[y].bottomRightCorner.topLeftBlock = &MyGrid[x].blocks[y];
				MyGrid[x].blocks[y].bottomRightCorner.topRightBlock = &MyGrid[x + 1].blocks[y];
				MyGrid[x].blocks[y].bottomRightCorner.bottomLeftBlock = &MyGrid[x].blocks[y - 1];
				MyGrid[x].blocks[y].bottomRightCorner.bottomRightBlock = &MyGrid[x + 1].blocks[y - 1];
			}
		}
	}

	// Now run through and calculate vertex heights
	for (int x = 0; x < aX; ++x)
	{
		for (int y = 0; y < aY; ++y)
		{
			MyGrid[x].blocks[y].ProcessCorners();
		}
	}

	return 0;
}
