#pragma once
#include "../sdk/sdk.h"

namespace cmd_pb
{
	inline c_subtick_move_step* subtick_move_step = nullptr;
	inline c_csgo_input_history_entry_pb* input_history_entry = nullptr;

	inline c_subtick_move_step* create_new_subtick_move_step(google::protobuf::repeated_ptr_field_t<c_subtick_move_step>* rept_ptr, void* arena)
	{
		using fn = c_subtick_move_step * (__fastcall*)(void*);
		using fn2 = c_subtick_move_step * (__fastcall*)(google::protobuf::repeated_ptr_field_t<c_subtick_move_step>*, void*);

		auto subtick_move = patterns::create_new_subtick_move_step.as<fn>()(arena);
		return patterns::add_to_move_step.as<fn2>()(rept_ptr, subtick_move);
	}

	inline c_subtick_move_step* add_subtick_move_step(c_user_cmd* user_cmd) 
	{
		auto rept_field_move_steps = reinterpret_cast<google::protobuf::repeated_ptr_field_t<c_subtick_move_step>*>((PBYTE)user_cmd->pb.mutable_base() + 0x18);

		if (rept_field_move_steps->m_rep && rept_field_move_steps->m_current_size < rept_field_move_steps->m_rep->m_allocated_size)
			subtick_move_step = rept_field_move_steps->m_rep->m_elements[rept_field_move_steps->m_current_size++];
		else
			subtick_move_step = create_new_subtick_move_step(rept_field_move_steps, rept_field_move_steps->m_arena);

		return subtick_move_step;
	}
}