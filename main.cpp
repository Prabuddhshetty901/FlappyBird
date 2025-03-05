#include<iostream>
#include<raylib.h>

using namespace std;


void s_Update();
void s_Draw();

void p_Draw();


int s_width = 1080;
int s_height = 700;

int s_x = 20;
int s_y = s_height / 2 - 20;

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
		
		cout << "s_x: " << s_x << " s_y :" << s_y << endl;
		
		EndDrawing();

	}


	CloseWindow();
	return 0;
}

void s_Draw() {
	DrawRectangle(s_x, s_y, 20, 20, WHITE);
	s_x++;
}


void s_Update() {
	
	float inc = 0.1;

	if (IsKeyPressed(KEY_UP)) {
		s_y-=100;
	}
	else {
		s_y+=2;
	}

	
}