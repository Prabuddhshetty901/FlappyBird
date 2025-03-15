﻿#include<iostream>
#include<raylib.h>

using namespace std;


void s_Update();
void s_Draw();

void p_Draw();
void p_Update();

void Restart();
void ResetPage();


int s_width = 600;
int s_height = 700;


Rectangle s = {200,s_height / 2 - 20 ,20,20};
float velocity = 0;
float rotation = 0;  // Rotation angle



int score = 0;
bool passedPipe[2] = { false, false };  // Track whether a pipe pair has been counted
int winscore = 5;
int highScore = 0;


float pipeSpeed = 3.0f;
float pipeGap = 150; // constant Gap between top and bottom pipes


bool gameover = false;


Rectangle pipes[4] = {
	{s_width, 0, 60, 250},               
	{s_width, 250 + pipeGap, 60, s_height - 250 + pipeGap},
	{s_width + (s_width / 2), 0, 60, 150},   
	{s_width + (s_width / 2), 150 + pipeGap, 60, s_height - 150 + pipeGap}
};


Color grey = { 130, 130, 130, 255 };
Color lightGrey = { 200, 200, 200, 255 };
Color darkGrey = { 80, 80, 80, 255 };


int borderThickness = 10; // Thickness of the border
Rectangle gameArea = { borderThickness, borderThickness + 50, s_width - 2 * borderThickness, s_height - 2 * borderThickness - 50 };


int main() {



	InitWindow(s_width, s_height, "Flappy Bird");

	SetTargetFPS(60);

	while (WindowShouldClose() == false) {

		BeginDrawing();
		
		
		//clearing
		ClearBackground(lightGrey);
		
		if (!gameover) {
		
			s_Update();
			p_Update();

			//drawing
			s_Draw();
			p_Draw();


			/*cout << "s_x: " << s_x << " s_y :" << s_y << endl;*/
		}
		else {
			ResetPage();
		}

		
		EndDrawing();

	}


	CloseWindow();
	return 0;
}

void s_Draw() {
	/*DrawRectangle(s.x, s.y, s.width, s.height, BLUE);*/

	Vector2 pivot = { s.width / 2, s.height / 2 };

	DrawRectanglePro(s, pivot, rotation, darkGrey);

	int scoreX = s_width / 2 - MeasureText(TextFormat("Score: %d", score), 20) / 2;
	int scoreY = 10;  // Above the game area

	DrawText(TextFormat("Score: %d", score), scoreX, scoreY, 20, YELLOW);
}


void s_Update() {
	float gravity = 1;
	float jumpStrength = -14.0;
	float rotationSpeed = 5.0f; // Speed of rotation transition

	for (int i = 0; i < 4; i++) {
		if (CheckCollisionRecs(s, pipes[i])) {
			gameover = true;
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

	if (velocity < 0) {
		rotation -= rotationSpeed;
		if (rotation < -20) rotation = -20;
	}
	else {
		rotation += rotationSpeed;
		if (rotation > 20) rotation = 20;
	}
}

void p_Draw() {


	DrawRectangleLinesEx(gameArea, borderThickness, darkGrey);

	for (int i = 0; i < 4; i++) {
		DrawRectangle(pipes[i].x, pipes[i].y, pipes[i].width, pipes[i].height, grey);
	}
}

void p_Update() {

	for (int i = 0; i < 4; i += 2) {  // alternative pipes
		pipes[i].x -= pipeSpeed;      //top pipe
		pipes[i + 1].x -= pipeSpeed;  //bottom pipe


		// Check if the bird has passed the pipe pair
		if (s.x > pipes[i].x + pipes[i].width && !passedPipe[i / 2]) {
			score++;  // Increase score when bird fully passes pipe
			passedPipe[i / 2] = true;
		}


		if (pipes[i].x + pipes[i].width < 0) { // resetting pipes when they go off screen
			pipes[i].x = s_width;     // Reset top pipe -> width
			pipes[i + 1].x = s_width; // Reset bottom pipe -> width


			int newHeight = GetRandomValue(100, 400); // Varry pipe height
			pipes[i].height = newHeight; //top pipe -. height
			pipes[i + 1].y = newHeight + pipeGap; // bottom pipe(y pos -> Maintaining gap)
			pipes[i + 1].height = s_height - (newHeight + pipeGap); // bottom pipe -> height


			passedPipe[i / 2] = false;  // Reset passed status for new pipes
		}
	}
}

void Restart() {
	s.x = 200;
	s.y = s_height / 2 - 20;
	velocity = 0;



	pipes[0] = { (float)s_width, 0, 60, 250 };
	pipes[1] = { (float)s_width, 250 + pipeGap, 60, s_height - 250 + pipeGap };
	pipes[2] = { (float)s_width + (s_width / 2), 0, 60, 150 };
	pipes[3] = { (float)s_width + (s_width / 2), 150 + pipeGap, 60, s_height - 150 + pipeGap };
}

const char* w_text = "YOU WON";
const char* r_text = "Press R to restart";
const char* s_text = "Score: ";
const char* h_text = "High Score: ";
const char* l_text = "YOU LOSE";


void ResetPage() {
	if (score == winscore) {
		DrawText(w_text, ((s_width * s_height) - MeasureText(w_text, 60)) / 2, ((s_width * s_height) - MeasureText(w_text, 60)) / 2, 60, YELLOW);
		DrawText(r_text, ((s_width * s_height) - MeasureText(r_text, 30)) / 2, ((s_width * s_height) - MeasureText(r_text, 30)) / 2 + 130, 30, YELLOW);

		DrawText(TextFormat(s_text, score), ((s_width * s_height) - MeasureText(s_text, 30)) / 2, ((s_width * s_height) - MeasureText(s_text, 30)) / 2 + 100, 30, YELLOW);
		DrawText(TextFormat(h_text, highScore), ((s_width * s_height) - MeasureText(h_text, 30)) / 2, ((s_width * s_height) - MeasureText(h_text, 30)) / 2 + 200, 30, YELLOW);
	}
	else {
		DrawText(l_text, ((s_width * s_height) - MeasureText(l_text, 60)) / 2, ((s_width * s_height) - MeasureText(l_text, 60)) / 2, 60, YELLOW);
		DrawText(r_text, ((s_width * s_height) - MeasureText(r_text, 30)) / 2, ((s_width * s_height) - MeasureText(r_text, 30)) / 2 + 100, 30, YELLOW);


		DrawText(TextFormat(s_text, score), ((s_width * s_height) - MeasureText(s_text, 30)) / 2, ((s_width * s_height) - MeasureText(s_text, 30)) / 2 + 100, 30, YELLOW);
		DrawText(TextFormat(h_text, highScore), ((s_width * s_height) - MeasureText(h_text, 30)) / 2, ((s_width * s_height) - MeasureText(h_text, 30)) / 2 + 200, 30, YELLOW);
	}

	if (IsKeyPressed(KEY_R)) {
		Restart();
		score = 0;
		gameover = false;
	}
}