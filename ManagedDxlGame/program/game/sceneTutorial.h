#pragma once

const tnl::Vector3 T_HAND_TYPE_STONE_POS = { 200, 200, 0 };
const tnl::Vector3 T_HAND_TYPE_SCISSORS_POS = { 200, 350, 0 };
const tnl::Vector3 T_HAND_TYPE_PAPER_POS = { 200, 500, 0 };

extern int t_hand_type_stone_hdl;
extern int t_hand_type_scissors_hdl;
extern int t_hand_type_paper_hdl;

void sceneTutorialInit();
void sceneTutorial();