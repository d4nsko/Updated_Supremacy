#pragma once

class safe_conditions {
public:
	bool IsNotProcessing();
	bool IsReady();
	bool InvalidCommand(CUserCmd* cmd);
	bool ValidCommand(CUserCmd* cmd);
	bool NonSendPacket();
	bool IsPlayerReady();
};

extern safe_conditions m_safe;
