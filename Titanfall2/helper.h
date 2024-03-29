#pragma once
#include "T2.h"
#include "Vector Structor.h"
#include <GLFW/glfw3.h> 
#include <math.h>
#define PI 3.14159265359

bool WTS(const Vec3& Origin, Vec2& Pos, float* Matrix) {
	Vec2 Res{ Res.x = GetSystemMetrics(SM_CXSCREEN) / 2, Res.y = GetSystemMetrics(SM_CYSCREEN) / 2 };

	Pos.x = (Origin.x * Matrix[0]) + (Origin.y * Matrix[1]) + (Origin.z * Matrix[2]) + Matrix[3];
	Pos.y = (Origin.x * Matrix[4]) + (Origin.y * Matrix[5]) + (Origin.z * Matrix[6]) + Matrix[7];
	/*Pos.z = (Origin.x * Matrix[8]) + (Origin.y * Matrix[9]) + (Origin.z * Matrix[10]) + Matrix[11];*/
	float w = (Origin.x * Matrix[12]) + (Origin.y * Matrix[13]) + (Origin.z * Matrix[14]) + Matrix[15];

	if (w < 0.01f) {
		return false;
	}


	Vec2 NDC;
	NDC.x = Pos.x / w;
	NDC.y = Pos.y / w;

	Pos.x = (((Res.x * NDC.x) + (NDC.x + Res.x)) / (Res.x * 2.f)) * 2.f - 1.f;
	Pos.y = (((Res.y * NDC.y) + (NDC.y + Res.y)) / (Res.y * 2.f)) * 2.f - 0.978f;

	return true;
}

uintptr_t DrawLines(Vec2 &Pos) {
	glColor3f(Stog.Line_color[0], Stog.Line_color[1], Stog.Line_color[2]);
	glLineWidth(1.f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(snap.start.x, snap.start.y);
    glVertex2f(Pos.x, Pos.y);
	glEnd();
    return true;

}

uintptr_t DrawCircle(float& circ, Vec2& pos) {
	glColor3f(Stog.Circ_color[0], Stog.Circ_color[1], Stog.Circ_color[2]);
	glLineWidth(1.f);
	Vec2 Res{ Res.x = GetSystemMetrics(SM_CXSCREEN), Res.y = GetSystemMetrics(SM_CYSCREEN) - 60.f };
	float ResScale = Res.y / Res.x;
	Vec2 c;

	glColor3f(Stog.Circ_color[0], Stog.Circ_color[1], Stog.Circ_color[2]);
	glBegin(GL_LINE_LOOP);
	

	for (int i = 0; i < 100; i++) {
		float t = 2.f * PI * i / 100;
		c.x = (circ * sin(t) * ResScale) + pos.x;
		c.y = circ * cos(t) + pos.y;
		
		glVertex2f(c.x, c.y);
		
	 }

	glEnd();
	return true;
}

uintptr_t DrawRadar(Vec2& pos) {

	Vec2 Res{ Res.x = GetSystemMetrics(SM_CXSCREEN), Res.y = GetSystemMetrics(SM_CYSCREEN) - 60.f };
	float ResScale = Res.y / Res.x;
	Vec2 c;
	if (!Stog.radarBackground) { glColor4f(Stog.radar_Circ_color[0], Stog.radar_Circ_color[1], Stog.radar_Circ_color[2], 0); }
	else {
		glColor4f(Stog.radar_Circ_color[0], Stog.radar_Circ_color[1], Stog.radar_Circ_color[2], Stog.radarAlpha / 10);
	}

	glBegin(GL_POLYGON);

	for (int i = 0; i < 100; i++) {
		float t = 2.f * PI * i / 100;
		c.x = (Stog.radarCirc * sin(t) * ResScale) + pos.x;
		c.y = Stog.radarCirc * cos(t) + pos.y;
		glVertex2f(c.x, c.y);
	}
	glEnd();	
	return true;
}

void DrawRadarBorder(Vec2& pos) {
	Vec2 Res{ Res.x = GetSystemMetrics(SM_CXSCREEN), Res.y = GetSystemMetrics(SM_CYSCREEN) - 60.f };
	float ResScale = Res.y / Res.x;
	Vec2 c;
		glBegin(GL_LINE_LOOP);
		glColor4f(Stog.Border_color[0], Stog.Border_color[1], Stog.Border_color[2], Stog.radarBorderAlpha / 10);
		for (int i = 0; i < 100; i++) {
			float t = 2.f * PI * i / 100;
			c.x = (Stog.radarCirc * sin(t) * ResScale) + pos.x;
			c.y = Stog.radarCirc * cos(t) + pos.y;
			glVertex2f(c.x, c.y);	
		}
		glEnd();
}

void DrawLocalPlayerDot(Vec2& pos) {
	glColor3f(Stog.player_dot_color[0], Stog.player_dot_color[1], Stog.player_dot_color[2]); // Red color for enemy dot
	glPointSize(Stog.PlayerSize); // Size of the dot
	glBegin(GL_POINTS);
	glVertex2f(pos.x, pos.y);
	glEnd();
}

void DrawNPCDot(const Vec2& position, Vec3 tri_color) {
	glColor3f(tri_color.x, tri_color.y, tri_color.z); // Red color for enemy dot
	glPointSize(Stog.NPCSize); // Size of the dot
	glBegin(GL_POINTS);
	glVertex2f(position.x, position.y);
	glEnd();
}

void DrawRadarLine(const Vec2& position) {
	glLineWidth(1.f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(Stog.radarPos.x, Stog.radarPos.y);
	glVertex2f(position.x, position.y);
	glEnd();
}

void DrawEnemyTriangle(Rotate rr, Vec2& pos, static float& ResScale, Vec3 tri_color) {

	Vec2 top = { ((1.f * cosf(rr.yaw)) * ResScale) * 0.015f + pos.x, pos.y - (1.f * sinf(rr.yaw)) * 0.015f };
	Vec2 btmL = { ((1.f * cosf(rr.yaw + PI - 1.f)) * ResScale) * 0.01f + pos.x, pos.y - (1.f * sinf(rr.yaw + PI - 1.f)) * 0.01f };
	Vec2 btmR = { ((1.f * cosf(rr.yaw + PI + 1.f)) * ResScale) * 0.01f + pos.x, pos.y - (1.f * sinf(rr.yaw + PI + 1.f)) * 0.01f };
	Vec2 mid = { ((1.f * cosf(rr.yaw)) * ResScale) * -0.015f + pos.x, pos.y - (1.f * sinf(rr.yaw)) * -0.015f };
	glLineWidth(2.f);
	glColor3f(tri_color.x, tri_color.y, tri_color.z);
	glBegin(GL_POLYGON);
	glVertex2f(top.x, top.y);
	glVertex2f(btmL.x, btmL.y);
	glVertex2f(mid.x, mid.y);
	glVertex2f(btmR.x, btmR.y);
	glEnd();
}

void DrawFriendlyTriangle(Rotate rr, static float LinePos, static float& ResScale) {
	if (Stog.radarNotRotated) {
		Vec2 top = { ((1.f * cosf(rr.yaw)) * ResScale) * 0.015f + Stog.radarPos.x, Stog.radarPos.y - (1.f * sinf(rr.yaw)) * 0.015f };
		Vec2 btmL = { ((1.f * cosf(rr.yaw + PI - 1.f)) * ResScale) * 0.01f + Stog.radarPos.x, Stog.radarPos.y - (1.f * sinf(rr.yaw + PI - 1.f)) * 0.01f };
		Vec2 btmR = { ((1.f * cosf(rr.yaw + PI + 1.f)) * ResScale) * 0.01f + Stog.radarPos.x, Stog.radarPos.y - (1.f * sinf(rr.yaw + PI + 1.f)) * 0.01f };
		Vec2 mid = { ((1.f * cosf(rr.yaw)) * ResScale) * -0.01f + Stog.radarPos.x, Stog.radarPos.y - (1.f * sinf(rr.yaw)) * -0.01f };

		glLineWidth(2.f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex2f(top.x, top.y);
		glVertex2f(btmL.x, btmL.y);
		glVertex2f(mid.x, mid.y);
		glVertex2f(btmR.x, btmR.y);
		
		glEnd();
	}
	else if (Stog.radarRotaed) {
		LinePos = PI / 2;
		Vec2 top = { ((1.f * cosf(LinePos)) * ResScale) * 0.01f + Stog.radarPos.x, Stog.radarPos.y + (1.f * sinf(LinePos)) * 0.01f };
		Vec2 btmL = { ((1.f * cosf(LinePos + PI - 1.f)) * ResScale) * 0.01f + Stog.radarPos.x, Stog.radarPos.y + (1.f * sinf(LinePos + PI - 1.f)) * 0.01f };
		Vec2 btmR = { ((1.f * cosf(LinePos + PI + 1.f)) * ResScale) * 0.01f + Stog.radarPos.x, Stog.radarPos.y + (1.f * sinf(LinePos + PI + 1.f)) * 0.01f };
		Vec2 mid = { ((1.f * cosf(LinePos)) * ResScale) * -0.01f + Stog.radarPos.x, Stog.radarPos.y + (1.f * sinf(LinePos)) * -0.01f };
		glLineWidth(2.f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex2f(top.x, top.y);
		glVertex2f(btmL.x, btmL.y);
		glVertex2f(mid.x, mid.y);
		glVertex2f(btmR.x, btmR.y);
		glEnd();
	}
}

uintptr_t DrawBox(int& health, Vec2& Pos, Vec2& HPos) {
	float height = ((Pos.y - HPos.y) * -1.f);
	float width = (height / 6.f);
	height += width / 1.1;
	float WTSHealth = (health / 100.f) * height;



	glColor3f(Stog.Box_color[0], Stog.Box_color[1], Stog.Box_color[2]); // default color - white
	glLineWidth(1.f); // default width

	glBegin(GL_LINE_STRIP); //btm left
	glVertex2f(Pos.x - width, Pos.y+width);
	glVertex2f(Pos.x - width, Pos.y);
	glVertex2f(Pos.x - (width / 2.f), Pos.y);
	glEnd();

	glBegin(GL_LINE_STRIP); //btm right
	glVertex2f(Pos.x + width, Pos.y + width);
	glVertex2f(Pos.x + width, Pos.y);
	glVertex2f(Pos.x + (width / 2.f), Pos.y);
	glEnd();

	glBegin(GL_LINE_STRIP); //top left
	glVertex2f(Pos.x - (width / 2.f), Pos.y + height);
	glVertex2f(Pos.x - width, Pos.y + height);
	glVertex2f(Pos.x - width, Pos.y + (height-width));
	glEnd();

	glBegin(GL_LINE_STRIP); //top right
	
	glVertex2f(Pos.x + (width / 2.f), Pos.y + height);
	glVertex2f(Pos.x + width, Pos.y + height);
	glVertex2f(Pos.x + width, Pos.y + (height - width));
	glEnd();
	

	glLineWidth(2.8f);
	glBegin(GL_LINE_STRIP); //Health Base
	glColor3f(1.f, 0.f, 0.f);
	glVertex2f(Pos.x - (width + 0.004), Pos.y);
	glVertex2f(Pos.x - (width + 0.004), Pos.y + height);
	glEnd();

	
	glBegin(GL_LINE_STRIP); //btm left
	glColor3f(0.f, 1.f, 0.f);
	glVertex2f(Pos.x - (width + 0.004), Pos.y);
	glVertex2f(Pos.x - (width + 0.004), Pos.y + WTSHealth);
	glEnd();
	return true;

}

uintptr_t DrawBones(Vec2& BPos1, Vec2& BPos2) {
	
	glColor3f(Stog.Bone_color[0], Stog.Bone_color[1], Stog.Bone_color[2]); // default color - white
	glLineWidth(1.f); // default width
	glBegin(GL_LINES); //btm left
	glVertex2f(BPos1.x, BPos1.y);
	glVertex2f(BPos2.x, BPos2.y);
	glEnd();
	
	return true;
}

Vec3 BoneMatrix(float* Matrix) {
	Vec3 Bone;
	Bone.x = Matrix[11];
	Bone.y = Matrix[3];
	Bone.z = Matrix[7];

	return Bone;
}


uintptr_t DrawBoneEsp(mem& m, uintptr_t& boneMatrix, float BoneNum1, float BoneNum2) {
	
	Vec2 BPos1;
	Vec2 BPos2;

	Matrix VM = m.readmem<Matrix>(addr.VM);

	const size_t pad = 0x30;

	uintptr_t BonePos1Addr = m.findMA(boneMatrix, BoneNum1 * pad);
	uintptr_t BonePos2Addr = m.findMA(boneMatrix, BoneNum2 * pad);
	Matrix BonePos1 = m.readmem<Matrix>(BonePos1Addr);
	Matrix BonePos2 = m.readmem<Matrix>(BonePos2Addr);

	Vec3 Bone1 = BoneMatrix(BonePos1.BM);
	Vec3 Bone2 = BoneMatrix(BonePos2.BM);
	
	if (WTS(Bone1, BPos1, VM.VM) && WTS(Bone2, BPos2, VM.VM)) {
		DrawBones(BPos1, BPos2);	
	}
	


	return true;
}


uintptr_t RadtoDeg(Rotate& r) {
	r.yaw *= (180 / PI);
	r.pitch *= (180 / PI);
	
	return true;
}

// Please fix this my god it shorrible
float SetAim(mem& m, Rotate r, float smoothVal, float aimFOV, uintptr_t& pitchAddr, uintptr_t& yawAddr) {

	Rotate smooth;
	smooth.pitch = m.readmem<float>(addr.pitchAddr); // current angles
	smooth.yaw = m.readmem<float>(addr.yawAddr);
	float pitch = (r.pitch - smooth.pitch); // difference btween current aingles and desired
	float yaw = (r.yaw - smooth.yaw);
	
	smooth.yaw += yaw / smoothVal;
	smooth.pitch += pitch / smoothVal;
	if (yaw < aimFOV && yaw > -aimFOV && pitch < aimFOV && pitch > -aimFOV) {
		m.writemem<float>(addr.pitchAddr, smooth.pitch);
		m.writemem<float>(addr.yawAddr, smooth.yaw);
	}

	return true;
}

uintptr_t Aim(mem& m, Vec3 Head, Vec3 Origin, float& c, Rotate& r, uintptr_t& pitchAddr, uintptr_t& yawAddr, Vec3& Diff) {

	r.pitch = m.readmem<float>(addr.pitchAddr);
	r.yaw = m.readmem<float>(addr.yawAddr);
		
	r.yaw = atan2(Diff.y, Diff.x);
	r.pitch = -asin(Diff.z/c);

	return (RadtoDeg(r)), c;
	
	
}

void radarGUI() {
	if (ImGui::Begin("Custom Radar Settings", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize)) {
		ImGui::SetWindowSize({ 550.f, 500.f });
		if (ImGui::BeginTabBar("Settings")) {
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(ImGui::GetStyle().FramePadding.x, ImGui::GetStyle().FramePadding.y - 2.f));
			ImGui::SameLine(495.f);
			if (ImGui::Button("Exit")) { Stog.radarExit = true; }
			else { Stog.radarExit = false; };
			ImGui::PopStyleVar();
			ImGui::ShowDemoWindow();
			if (ImGui::BeginTabItem("Aesthetic")) {
				ImGui::SeparatorText("Radar");
				ImGui::Checkbox("Show Radar", &Stog.radar2D); if (Stog.radar2D) { Stog.radarFill = true; }
				else { Stog.radarFill = false; };
				ImGui::SeparatorText("Position");
				ImGui::SliderFloat("X-Axis", &Stog.radarPos.x, -1.f, 1.f, "%.2f");
				ImGui::SliderFloat("Y-Axis", &Stog.radarPos.y, -1.f, 1.f, "%.2f");
				ImGui::SeparatorText("Sizing");
				ImGui::SliderFloat("Circumference", &Stog.radarCirc, 0.01f, 5.f, "%.3f");
				ImGui::SliderFloat("Player Size", &Stog.PlayerSize, .01f, 100.0f, "%.01f");
				ImGui::SliderFloat("Pilot Size", &Stog.PilotSize, .01f, 100.0f, "%.01f");
				ImGui::SliderFloat("NPC Size", &Stog.NPCSize, .01f, 100.0f, "%.01f");
				ImGui::SeparatorText("Radar Visability");
				ImGui::SliderFloat("Background Transparency", &Stog.radarAlpha, .01f, 10.0f, "%.01f");
				ImGui::SliderFloat("Border Transparency", &Stog.radarBorderAlpha, .01f, 10.0f, "%.01f");
				ImGui::SeparatorText("Options");
				ImGui::Checkbox("Show Border", &Stog.radarBorder);
				ImGui::Checkbox("Show Backround", &Stog.radarBackground);
				ImGui::Checkbox("Show Player Dot", &Stog.radarLocalPlayer);
				ImGui::Checkbox("Show Edge Dots", &Stog.radarEdgeDot);
				ImGui::Checkbox("Show NPC", &Stog.radarNPC);
				ImGui::Checkbox("Show Friendly NPC", &Stog.radarNPC_F);
				ImGui::Checkbox("Show Pilot", &Stog.radarPilot);
				ImGui::Checkbox("Show Friendly Pilot", &Stog.radarPilot_F);
				ImGui::SeparatorText("Color");
				ImGui::ColorEdit3("Radar Background Color", Stog.radar_Circ_color, ImGuiColorEditFlags_NoInputs);
				ImGui::ColorEdit3("Player Color", Stog.player_dot_color, ImGuiColorEditFlags_NoInputs);
				ImGui::ColorEdit3("NPC Color", Stog.NPC_dot_color, ImGuiColorEditFlags_NoInputs);
				if (Stog.radarBorder) { ImGui::ColorEdit3("Border Color", Stog.Border_color, ImGuiColorEditFlags_NoInputs); };
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Gameplay")) {
				ImGui::SeparatorText("Radar Game Settings");
				ImGui::SliderFloat("Render Distance", &Stog.radarRenderDist, 1.f, 10000.f, "%.f");
				ImGui::SeparatorText("Radar Rotation");
				if (ImGui::Checkbox("Rotate Enemys", &Stog.radarRotaed)) { Stog.radarNotRotated = !Stog.radarNotRotated; };
				if (ImGui::Checkbox("Rotate FOV", &Stog.radarNotRotated)) { Stog.radarRotaed = !Stog.radarRotaed; };


				ImGui::EndTabItem();
			}

		}
		ImGui::EndTabBar();
	}
	ImGui::End();

}