#include<iostream>
#include<raylib.h>

using namespace std;


void s_Update();
void s_Draw();

void p_Draw();


int s_width = 1080;
int s_height = 700;


Rectangle s = {20,s_height / 2 - 20 ,20,20};
float velocity = 0;



Rectangle p1 = { 1 * s_width / 4, 0, 60, 250 };
Rectangle p2 = { 1 * s_width / 4, s_height - 250, 60, 250 };
Rectangle p3 = { 2 * s_width / 4, 0, 60, 250 };
Rectangle p4 = { 2 * s_width / 4, s_height - 250, 60, 250 };
Rectangle p5 = { 3 * s_width / 4, 0, 60, 250 };
Rectangle p6 = { 3 * s_width / 4, s_height - 250, 60, 250 };

int main() {



	InitWindow(s_width, s_height, "Flappy Bird");

	SetTargetFPS(60);

	while (WindowShouldClose() == false) {

		BeginDrawing();
		
		
		//clearing
		ClearBackground(BLACK);
		

		//drawing
		s_Draw();
		s_Update();
		p_Draw();
		
		/*cout << "s_x: " << s_x << " s_y :" << s_y << endl;*/
		
		EndDrawing();

	}


	CloseWindow();
	return 0;
}

void s_Draw() {
	DrawRectangle(s.x, s.y, s.width, s.height, WHITE);
	s.x++;
}


void s_Update() {
	float gravity = 0.5;
	float jumpStrength = -8.0;

	if (CheckCollisionRecs(s, p1) || CheckCollisionRecs(s, p2) || CheckCollisionRecs(s, p3) || CheckCollisionRecs(s, p4) ||
		CheckCollisionRecs(s, p5) || CheckCollisionRecs(s, p6) || s.x> s_width - s.width){
		s.x = 20;
		s.y = s_height / 2 - 20;
	}


	if (IsKeyPressed(KEY_UP)) {
		velocity = jumpStrength;
	}

	velocity += gravity;
	s.y += velocity;

	if (s.y < 0) {
		s.y = 0;
		velocity = 0;
	}

	if (s.y > s_height - 20) {
		s.y = s_height - 20;
		velocity = 0;
	}
}

void p_Draw() {


	DrawRectangle(p1.x,p1.y,p1.width,p1.height, RED);
	DrawRectangle(p2.x, p2.y, p2.width, p2.height, RED);

	DrawRectangle(p3.x, p3.y, p3.width, p3.height, RED);
	DrawRectangle(p4.x, p4.y, p4.width, p4.height, RED);


	DrawRectangle(p5.x, p5.y, p5.width, p5.height, RED);
	DrawRectangle(p6.x, p6.y, p6.width, p6.height, RED);
}