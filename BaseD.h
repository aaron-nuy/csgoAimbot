#pragma once
#include "m_memory.h"
#include "offsets.hpp"
#include "vec.h"

namespace csgoBased {

	const short GLOW_YES = 0xffff;
	const short GLOW_NO = 0x0;


	namespace engine {

		uint32_t clientState;
		uint32_t localPlayerID;
		uint32_t maxPlayers;
		uint32_t glowManager;


		void refresh() {
			clientState = memory::readMemory<uint32_t>(memory::engineBase + hazedumper::signatures::dwClientState);
			localPlayerID = memory::readMemory<uint32_t>(clientState + hazedumper::signatures::dwClientState_GetLocalPlayer);
			maxPlayers = memory::readMemory<uint32_t>(clientState + hazedumper::signatures::dwClientState_MaxPlayer);
			glowManager = memory::readMemory<uint32_t>(memory::clientBase + hazedumper::signatures::dwGlowObjectManager);

		}

	}

	DWORD init() {

		if (!memory::init()) {
			return 0;
		}

		engine::refresh();
		return 1;
	}

	class Entity
	{

	public:

		uint32_t address;
		uint32_t boneMatrix;
		uint32_t glowIndex;

		Entity(uint32_t offset) {
			address = memory::readMemory<uint32_t>(memory::clientBase + hazedumper::signatures::dwEntityList + offset * 0x10);
			boneMatrix = memory::readMemory<uint32_t>(address + hazedumper::netvars::m_dwBoneMatrix);
			glowIndex = memory::readMemory<uint32_t>(address + hazedumper::netvars::m_iGlowIndex);
		}

		uint32_t getEntity(uint32_t offset) {
			address = memory::readMemory<uint32_t>(memory::clientBase + hazedumper::signatures::dwEntityList + offset * 0x10);
			boneMatrix = memory::readMemory<uint32_t>(address + hazedumper::netvars::m_dwBoneMatrix);
			glowIndex = memory::readMemory<uint32_t>(address + hazedumper::netvars::m_iGlowIndex);
			return address;
		}

		vec3 getLocation() {
			return memory::readMemory<vec3>(address + hazedumper::netvars::m_vecOrigin);
		}

		vec3 getHeadPosition() {
			return vec3(
				memory::readMemory<float>(boneMatrix + 0x30 * 8 + 0x0C),
				memory::readMemory<float>(boneMatrix + 0x30 * 8 + 0x1C),
				memory::readMemory<float>(boneMatrix + 0x30 * 8 + 0x2C));
		}

		bool isDormant() {
			return memory::readMemory<bool>(address + hazedumper::signatures::m_bDormant);
		}

		uint32_t isVisible() {
			return memory::readMemory<uint32_t>(address + hazedumper::netvars::m_bSpottedByMask) & (1 << engine::localPlayerID);
		}

		uint32_t getTeam() {
			return memory::readMemory<uint32_t>(address + hazedumper::netvars::m_iTeamNum);
		}

		uint32_t getGlowIndex() {
			return memory::readMemory<uint32_t>(address + hazedumper::netvars::m_iGlowIndex);
		}

		uint32_t isDead() {
			return memory::readMemory<uint32_t>(address + hazedumper::netvars::m_lifeState);
		}
		


		// TODO :: Try to optimize glow index
		bool setGlowColor(const vec4& vec4) {
			return memory::writeMemory(engine::glowManager + glowIndex * 0x38 + 0x8, vec4);
		}


		// TODO :: Try to optimize glow index
		bool setShouldGlow(short glow) {
			return memory::writeMemory<short>(engine::glowManager + glowIndex * 0x38 + 0x27, glow);
		}

	};

	class Player
	{
	public:

		uint32_t address;

		uint32_t getPlayer() {
			address = memory::readMemory<uint32_t>(memory::clientBase + hazedumper::signatures::dwLocalPlayer);
			return address;
		}

		vec3 getLocation() {
			return memory::readMemory<vec3>(address + hazedumper::netvars::m_vecOrigin);
		}

		vec3 getViewAngles() {
			return memory::readMemory<vec3>(engine::clientState + hazedumper::signatures::dwClientState_ViewAngles);
		}

		vec3 getAimPunch() {
			return memory::readMemory<vec3>(address + hazedumper::netvars::m_aimPunchAngle);
		}

		bool setAimPunch(const vec3& vec) {
			return memory::writeMemory<vec3>(address + hazedumper::netvars::m_aimPunchAngle,vec);
		}

		vec3 getEyePosition() {
			return getLocation() + memory::readMemory<vec3>(address + hazedumper::netvars::m_vecViewOffset);
		}

		uint32_t getTeam() {
			return memory::readMemory<uint32_t>(address + hazedumper::netvars::m_iTeamNum);
		}

		bool setViewAngles(const vec3& vec3) {
			return memory::writeMemory(engine::clientState + hazedumper::signatures::dwClientState_ViewAngles, vec3);
		}

	};



}