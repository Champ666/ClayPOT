#include "stdafx.h"
#include "EditorMode.h"

EditorMode::EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
	: stateData(state_data), tileMap(tile_map), editorStateData(editor_state_data)
{

}

EditorMode::~EditorMode()
{

}
