
#pragma once

#include "../../BlockEntities/NoteEntity.h"





namespace NoteBlockHandler
{
	inline unsigned char GetPowerDeliveredToPosition(const cChunk & a_Chunk, Vector3i a_Position, BLOCKTYPE a_BlockType, Vector3i a_QueryPosition, BLOCKTYPE a_QueryBlockType, bool IsLinked)
	{
		UNUSED(a_Chunk);
		UNUSED(a_Position);
		UNUSED(a_BlockType);
		UNUSED(a_QueryPosition);
		UNUSED(a_QueryBlockType);
		UNUSED(IsLinked);
		return 0;
	}

	inline void Update(cChunk & a_Chunk, cChunk &, Vector3i a_Position, BLOCKTYPE a_BlockType, NIBBLETYPE a_Meta, PoweringData a_PoweringData)
	{
		// LOGD("Evaluating sparky the magical note block (%d %d %d) %i", a_Position.x, a_Position.y, a_Position.z, a_PoweringData.PowerLevel);

		auto Previous = DataForChunk(a_Chunk).ExchangeUpdateOncePowerData(a_Position, a_PoweringData);
		if ((Previous.PowerLevel != 0) || (a_PoweringData.PowerLevel == 0))
		{
			// If we're already powered or received an update of no power, don't make a sound
			return;
		}

		a_Chunk.DoWithNoteBlockAt(a_Position, [](cNoteEntity & a_NoteBlock)
		{
			a_NoteBlock.MakeSound();
			return false;
		});
	}

	inline void ForValidSourcePositions(const cChunk & a_Chunk, Vector3i a_Position, BLOCKTYPE a_BlockType, NIBBLETYPE a_Meta, ForEachSourceCallback & Callback)
	{
		UNUSED(a_Chunk);
		UNUSED(a_BlockType);
		UNUSED(a_Meta);
		InvokeForAdjustedRelatives(Callback, a_Position, RelativeAdjacents);
	}
};
