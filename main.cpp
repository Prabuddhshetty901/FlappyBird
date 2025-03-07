#include<iostream>
#include<raylib.h>

using namespace std;


void s_Update();
void s_Draw();

void p_Draw();
void p_Update();


int s_width = 600;
int s_height = 700;


Rectangle s = {200,s_height / 2 - 20 ,20,20};
float velocity = 0;



float pipeSpeed = 3.0f;
float pipeGap = 150; // constant Gap between top and bottom pipes

Rectangle pipes[4] = {
	{s_width, 0, 60, 250},               
	{s_width, 250 + pipeGap, 60, s_height - 250 + pipeGap},
	{s_width + (s_width / 2), 0, 60, 150},   
	{s_width + (s_width / 2), 150 + pipeGap, 60, s_height - 150 + pipeGap}
};

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
		p_Update();
		
		/*cout << "s_x: " << s_x << " s_y :" << s_y << endl;*/
		
		EndDrawing();

	}


	CloseWindow();
	return 0;
}

void s_Draw() {
	DrawRectangle(s.x, s.y, s.width, s.height, WHITE);
}


void s_Update() {
	float gravity = 1;
	float jumpStrength = -14.0;

	for (int i = 0; i < 4; i++) {
		if (CheckCollisionRecs(s, pipes[i])) {
			s.x = 200;
			s.y = s_height / 2 - 20;
			velocity = 0;
		}
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


	for (int i = 0; i < 4; i++) {
		DrawRectangle(pipes[i].x, pipes[i].y, pipes[i].width, pipes[i].height, RED);
	}
}

void p_Update() {

	for (int i = 0; i < 4; i += 2) {  // alternative pipes
		pipes[i].x -= pipeSpeed;      //top pipe
		pipes[i + 1].x -= pipeSpeed;  //bottom pipe

		if (pipes[i].x + pipes[i].width < 0) { // resetting pipes when they go off screen
			pipes[i].x = s_width;     // Reset top pipe -> width
			pipes[i + 1].x = s_width; // Reset bottom pipe -> width


			int newHeight = GetRandomValue(100, 400); // Varry pipe height
			pipes[i].height = newHeight; //top pipe -. height
			pipes[i + 1].y = newHeight + pipeGap; // bottom pipe(y pos -> Maintaining gap)
			pipes[i + 1].height = s_height - (newHeight + pipeGap); // bottom pipe -> height
		}
	}
}