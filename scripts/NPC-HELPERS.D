instance npcVarInst(C_Npc)
{
};


func void SetNpcVar(var int aivrx, var int value) {
    RX_SetNpcVar(npcVarInst, aivrx, value);
};

func int GetNpcVar(var int aivrx) {
    return RX_GetNpcVar(npcVarInst, aivrx);
};