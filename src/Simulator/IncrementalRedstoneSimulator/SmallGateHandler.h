
#pragma once





namespace SmallGateHandler
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
		// LOGD("Evaluating gateydory the fence gate/trapdoor (%d %d %d)", a_Position.x, a_Position.y, a_Position.z);

		const bool ShouldBeOpen = a_PoweringData.PowerLevel != 0;
		const bool IsOpen = (a_Meta & 0x4) == 0x4;

		if (ShouldBeOpen != IsOpen)
		{
			a_Chunk.SetMeta(a_Position, ShouldBeOpen ? (a_Meta | 0x4) : (a_Meta & ~0x04));
		}
	}

	inline void ForValidSourcePositions(const cChunk & a_Chunk, Vector3i a_Position, BLOCKTYPE a_BlockType, NIBBLETYPE a_Meta, ForEachSourceCallback & Callback)
	{
		UNUSED(a_Chunk);
		UNUSED(a_BlockType);
		UNUSED(a_Meta);
		InvokeForAdjustedRelatives(Callback, a_Position, RelativeAdjacents);
	}
};
