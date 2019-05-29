#include "Demo.h"

static const int nP = 100;
Player player;
Enemy enemy[20];
Peluru p;
Peluru peluru[nP];
Peluru peluru_musuh[20][nP];
//Map map;
Tiles* tile[1600];
Menu menu;
Status status;
Budal budal;
string map[3] = { "map1.map", "map2.map", "map3.map" };
bool bbm = true;
bool buatEnemy = true;
int nEnemy;
float xspawn = 0.8, yspawn = 0.8;
float yy = 0.95;
Loading load;
Fsm fsm[20];
Fsm f;
int jumTiles = 400;

Demo::Demo()
{
}


Demo::~Demo()
{
}

void Demo::Init()
{
	//membuatMap(map[0]);
	player.BuildSprite();
	//enemy.Init();
	p.BuildSprite();
	for (int i = 0; i < nP; i++) {
		peluru[i].BuildSprite();
		//peluru_musuh[i].BuildSprite();
	}
	menu.BuildMenu();
	menu.BuildLogo();
	menu.BuildLvl();
	menu.BuildGameOver();
	load.BuildSprite();
	load.BuildTeks();
	InputMapping("SelectButton", SDLK_RETURN);
	InputMapping("NextButton", SDLK_DOWN);
	InputMapping("PrevButton", SDLK_UP);
	InputMapping("BackButton", SDLK_ESCAPE);
	status = Status::MAIN_MENU;
}

Book* book = xlCreateBook();
void Demo::Update(float deltaTime)
{
	fps;
	Input(deltaTime);
	if (Status::MAIN_MENU == status)
	{
		if (IsKeyUp(SDLK_RETURN)) {
			if (menu.ActiveButtonIndex == 0) {
				status = Status::LEVEL;
			}
			if (menu.ActiveButtonIndex == 1) {
				SDL_Quit();
				exit(0);
			}
		}
		if (IsKeyDown(SDLK_DOWN)) {
			if (menu.ActiveButtonIndex < NUM_BUTTON - 1) {
				menu.ActiveButtonIndex = menu.ActiveButtonIndex + 1;
				SDL_Delay(150);
			}
		}
		if (IsKeyDown(SDLK_UP)) {
			if (menu.ActiveButtonIndex > 0) {
				menu.ActiveButtonIndex = menu.ActiveButtonIndex - 1;
				SDL_Delay(150);
			}
		}
	}

	if (Status::LEVEL == status)
	{
		if (IsKeyDown(SDLK_SPACE)) {
			if (menu.ActiveButtonLevel == 0) {
				status = Status::NPC1;
			}
			if (menu.ActiveButtonLevel == 1) {
				status = Status::NPC5;
			}
			if (menu.ActiveButtonLevel == 2) {
				status = Status::NPC10;
			}
			if (menu.ActiveButtonLevel == 3) {
				status = Status::NPC15;
			}
			if (menu.ActiveButtonLevel == 4) {
				status = Status::MAP1;
			}
			if (menu.ActiveButtonLevel == 5) {
				status = Status::MAP2;
			}
			if (menu.ActiveButtonLevel == 6) {
				status = Status::MAP3;
			}
		}
		if (IsKeyDown(SDLK_DOWN)) {
			if (menu.ActiveButtonLevel < NUM_LEVEL - 1) {
				menu.ActiveButtonLevel = menu.ActiveButtonLevel + 1;
				SDL_Delay(150);
			}
		}
		if (IsKeyDown(SDLK_UP)) {
			if (menu.ActiveButtonLevel > 0) {
				menu.ActiveButtonLevel = menu.ActiveButtonLevel - 1;
				SDL_Delay(150);
			}
		}
	}

	
	if (Status::NPC1 == status)
	{
		if (bbm) {
			//std::thread t(thread_loading);
			//t.join();
			membuatMap(map[0], jumTiles);
			bbm = false;
		}
		// Movement
		player.MoveSprite(deltaTime);
		fsm[0].Update(deltaTime);

		for (int i = 0; i < nP; i++) {
			if (peluru[i].active) {
				peluru[i].MoveSprite(deltaTime);
			}
			for (int j = 0; j < nEnemy; j++)
			{
				if (peluru_musuh[j][i].active) {
					peluru_musuh[j][i].MoveSprite(deltaTime);
				}
			}
		}

		count++;
		if (count > 5) {
			Fsm(deltaTime);
		}

		//cek collison
		Collision(deltaTime);

		static int num = 5;
		static int frame = 0;
		frame++;
		if (frame == 100) {
			if (book) {
				if (book->load("example.xls")) {
					Sheet* sheet = book->getSheet(0);
					if (sheet) {
						sheet->writeNum(num, 1, fps);
					}
					//cout << num << "+" << fps << endl;
				}
				book->save("example.xls");
			}
			num++;
			frame = 0;
		}
	}
	if (Status::NPC5 == status)
	{
		if (bbm) {
			//std::thread t(thread_loading);
			//t.join();
			membuatMap(map[0], jumTiles);
			bbm = false;
		}
		// Movement
		player.MoveSprite(deltaTime);
		for (int i = 0; i < nEnemy; i++)
		{
			fsm[i].Update(deltaTime);
		}
		for (int i = 0; i < nP; i++) {
			if (peluru[i].active) {
				peluru[i].MoveSprite(deltaTime);
			}
			for (int j = 0; j < nEnemy; j++)
			{
				if (peluru_musuh[j][i].active) {
					peluru_musuh[j][i].MoveSprite(deltaTime);
				}
			}
		}

		count++;
		if (count > 5) {
			Fsm(deltaTime);
		}

		//cek collison
		Collision(deltaTime);

		static int num = 5;
		static int frame = 0;
		frame++;
		if (frame == 60) {
			if (book) {
				if (book->load("example.xls")) {
					Sheet* sheet = book->getSheet(0);
					if (sheet) {
						sheet->writeNum(num, 2, fps);
					}
					//cout << num << "+" << fps << endl;
				}
				book->save("example.xls");
			}
			num++;
			frame = 0;
		}
	}
	if (Status::NPC10 == status)
	{
		if (bbm) {
			//std::thread t(thread_loading);
			//t.join();
			membuatMap(map[0], jumTiles);
			bbm = false;
		}
		// Movement
		player.MoveSprite(deltaTime);
		for (int i = 0; i < nEnemy; i++)
		{
			fsm[i].Update(deltaTime);
		}
		for (int i = 0; i < nP; i++) {
			if (peluru[i].active) {
				peluru[i].MoveSprite(deltaTime);
			}
			for (int j = 0; j < nEnemy; j++)
			{
				if (peluru_musuh[j][i].active) {
					peluru_musuh[j][i].MoveSprite(deltaTime);
				}
			}
		}

		count++;
		if (count > 5) {
			Fsm(deltaTime);
		}

		//cek collison
		Collision(deltaTime);

		static int num = 5;
		static int frame = 0;
		frame++;
		if (frame == 15) {
			if (book) {
				if (book->load("example.xls")) {
					Sheet* sheet = book->getSheet(0);
					if (sheet) {
						sheet->writeNum(num, 3, fps);
					}
					//cout << num << "+" << fps << endl;
				}
				book->save("example.xls");
			}
			num++;
			frame = 0;
		}
	}
	if (Status::NPC15 == status)
	{
		if (bbm) {
			//std::thread t(thread_loading);
			//t.join();
			membuatMap(map[0], jumTiles);
			bbm = false;
		}
		// Movement
		player.MoveSprite(deltaTime);
		for (int i = 0; i < nEnemy; i++)
		{
			fsm[i].Update(deltaTime);
		}
		for (int i = 0; i < nP; i++) {
			if (peluru[i].active) {
				peluru[i].MoveSprite(deltaTime);
			}
			for (int j = 0; j < nEnemy; j++)
			{
				if (peluru_musuh[j][i].active) {
					peluru_musuh[j][i].MoveSprite(deltaTime);
				}
			}
		}

		count++;
		if (count > 5) {
			Fsm(deltaTime);
		}

		//cek collison
		Collision(deltaTime);

		static int num = 5;
		static int frame = 0;
		frame++;
		if (frame == 3) {
			if (book) {
				if (book->load("example.xls")) {
					Sheet* sheet = book->getSheet(0);
					if (sheet) {
						sheet->writeNum(num, 4, fps);
					}
					//cout << num << "+" << fps << endl;
				}
				book->save("example.xls");
			}
			num++;
			frame = 0;
		}
	}


	if (Status::MAP1 == status)
	{
		if (bbm) {
			//std::thread t(thread_loading);
			//t.join();
			membuatMap(map[0], jumTiles);
			bbm = false;
		}
		// Movement
		player.MoveSprite(deltaTime);
		for (int i = 0; i < nEnemy; i++)
		{
			fsm[i].Update(deltaTime);
		}
		for (int i = 0; i < nP; i++) {
			if (peluru[i].active) {
				peluru[i].MoveSprite(deltaTime);
			}
			for (int j = 0; j < nEnemy; j++)
			{
				if (peluru_musuh[j][i].active) {
					peluru_musuh[j][i].MoveSprite(deltaTime);
				}
			}
		}

		count++;
		if (count > 5) {
			Fsm(deltaTime);
		}

		//cek collison
		Collision(deltaTime);

		static int num = 5;
		static int frame = 0;
		frame++;
		if (frame == 60) {
			if (book) {
				if (book->load("example.xls")) {
					Sheet* sheet = book->getSheet(0);
					if (sheet) {
						sheet->writeNum(num, 5, fps);
					}
					//cout << num << "+" << fps << endl;
				}
				book->save("example.xls");
			}
			num++;
			frame = 0;
		}
	}
	if (Status::MAP2 == status)
	{
		jumTiles = 900;
		if (bbm) {
			//std::thread t(thread_loading);
			//t.join();
			membuatMap(map[1], jumTiles);
			bbm = false;
		}
		// Movement
		player.MoveSprite(deltaTime);
		for (int i = 0; i < nEnemy; i++)
		{
			fsm[i].Update(deltaTime);
		}
		for (int i = 0; i < nP; i++) {
			if (peluru[i].active) {
				peluru[i].MoveSprite(deltaTime);
			}
			for (int j = 0; j < nEnemy; j++)
			{
				if (peluru_musuh[j][i].active) {
					peluru_musuh[j][i].MoveSprite(deltaTime);
				}
			}
		}

		count++;
		if (count > 10) {
			Fsm(deltaTime);
		}

		//cek collison
		Collision(deltaTime);

		static int num = 5;
		static int frame = 0;
		frame++;
		if (frame == 60) {
			if (book) {
				if (book->load("example.xls")) {
					Sheet* sheet = book->getSheet(0);
					if (sheet) {
						sheet->writeNum(num, 6, fps);
					}
					//cout << num << "+" << fps << endl;
				}
				book->save("example.xls");
			}
			num++;
			frame = 0;
		}
	}
	if (Status::MAP3 == status)
	{
		jumTiles = 1600;
		if (bbm) {
			//std::thread t(thread_loading);
			//t.join();
			membuatMap(map[2], jumTiles);
			bbm = false;
		}
		// Movement
		player.MoveSprite(deltaTime);
		for (int i = 0; i < nEnemy; i++)
		{
			fsm[i].Update(deltaTime);
		}
		for (int i = 0; i < nP; i++) {
			if (peluru[i].active) {
				peluru[i].MoveSprite(deltaTime);
			}
			for (int j = 0; j < nEnemy; j++)
			{
				if (peluru_musuh[j][i].active) {
					peluru_musuh[j][i].MoveSprite(deltaTime);
				}
			}
		}

		count++;
		if (count > 60) {
			Fsm(deltaTime);
		}

		//cek collison
		Collision(deltaTime);

		static int num = 5;
		static int frame = 0;
		frame++;
		if (frame == 60) {
			if (book) {
				if (book->load("example.xls")) {
					Sheet* sheet = book->getSheet(0);
					if (sheet) {
						sheet->writeNum(num, 7, fps);
					}
					//cout << num << "+" << fps << endl;
				}
				book->save("example.xls");
			}
			num++;
			frame = 0;
		}
	}
}

void Demo::Render()
{
	//Setting Viewport
	glViewport(0, 0, screenWidth, screenHeight);

	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the background color
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (Status::MAIN_MENU == status)
	{
		menu.DrawLogo();
		menu.DrawMenu();
	}

	if (Status::LEVEL == status)
	{
		menu.DrawLogo();
		menu.DrawLvl();
	}

	if (Status::NPC1 == status)
	{
		nEnemy = 1;
		for (int i = 0; i < nEnemy; i++)
		{
			if (buatEnemy) {
				//enemy[i].Init();
				enemy[i].Spawn(xspawn, 0.8);
				xspawn -= 0.2;
				fsm[i].BuildFsm();
				fsm[i].Posisi(0.95, yy);
				yy -= 0.05;
				for (int j = 0; j < nP; j++)
				{
					peluru_musuh[i][j].BuildSprite();
				}
				if (i == nEnemy - 1) {
					//fsm[0].BuildFsm();
					enemy[0].Init();
					buatEnemy = false;
				}
			}
			enemy[i].DrawTank();
		}

		player.DrawSprite();
		p.DrawSprite();

		for (int i = 0; i < 400; i++)
		{
			if (tile[i]->frame_idx == 0)
			{
				tile[i]->DrawSprite();
			}
		}

		for (int i = 0; i < nEnemy; i++)
		{
			fsm[i].DrawFsm();
		}

		//tile[0]->DrawSprite();

		for (int i = 0; i < nP; i++)
		{
			peluru[i].DrawSprite();
			for (int j = 0; j < nEnemy; j++)
			{
				peluru_musuh[j][i].DrawSprite();
			}
		}
		if (player.nyawa == 0) {
			menu.DrawGameOver();
		}
	}
	if (Status::NPC5 == status)
	{
		nEnemy = 5;
		for (int i = 0; i < nEnemy; i++)
		{
			if (buatEnemy) {
				//enemy[i].Init();
				enemy[i].Spawn(xspawn, 0.8);
				xspawn -= 0.2;
				fsm[i].BuildFsm();
				fsm[i].Posisi(0.95, yy);
				yy -= 0.05;
				for (int j = 0; j < nP; j++)
				{
					peluru_musuh[i][j].BuildSprite();
				}
				if (i == nEnemy - 1) {
					enemy[0].Init();
					enemy[1].Init();
					enemy[2].Init();
					enemy[3].Init();
					enemy[4].Init();
					buatEnemy = false;
				}
			}
			enemy[i].DrawTank();
		}

		player.DrawSprite();
		p.DrawSprite();

		for (int i = 0; i < 400; i++)
		{
			if (tile[i]->frame_idx == 0)
			{
				tile[i]->DrawSprite();
			}
		}

		for (int i = 0; i < nEnemy; i++)
		{
			fsm[i].DrawFsm();
		}
		//tile[0]->DrawSprite();
		
		for (int i = 0; i < nP; i++)
		{
			peluru[i].DrawSprite();
			for (int j = 0; j < nEnemy; j++)
			{
				peluru_musuh[j][i].DrawSprite();
			}
		}
		if (player.nyawa == 0) {
			menu.DrawGameOver();
		}
	}
	if (Status::NPC10 == status)
	{
		nEnemy = 10;
		for (int i = 0; i < nEnemy; i++)
		{
			if (buatEnemy) {
				//enemy[i].Init();
				enemy[i].Spawn(xspawn, yspawn);
				xspawn -= 0.15;
				if (xspawn < -0.2) {
					yspawn -= 0.15;
				}
				fsm[i].BuildFsm();
				fsm[i].Posisi(0.95, yy);
				yy -= 0.05;
				for (int j = 0; j < nP; j++)
				{
					peluru_musuh[i][j].BuildSprite();
				}
				if (i == nEnemy - 1) {
					enemy[0].Init();
					enemy[1].Init();
					enemy[2].Init();
					enemy[3].Init();
					enemy[4].Init();
					enemy[5].Init();
					enemy[6].Init();
					enemy[7].Init();
					enemy[8].Init();
					enemy[9].Init();
					buatEnemy = false;
				}
			}
			enemy[i].DrawTank();
		}

		player.DrawSprite();
		p.DrawSprite();

		for (int i = 0; i < 400; i++)
		{
			if (tile[i]->frame_idx == 0)
			{
				tile[i]->DrawSprite();
			}
		}

		for (int i = 0; i < nEnemy; i++)
		{
			fsm[i].DrawFsm();
		}

		for (int i = 0; i < nP; i++)
		{
			peluru[i].DrawSprite();
			for (int j = 0; j < nEnemy; j++)
			{
				peluru_musuh[j][i].DrawSprite();
			}
		}
		if (player.nyawa == 0) {
			menu.DrawGameOver();
		}
	}
	if (Status::NPC15 == status)
	{
		nEnemy = 15;
		for (int i = 0; i < nEnemy; i++)
		{
			if (buatEnemy) {
				//enemy[i].Init();
				enemy[i].Spawn(xspawn, yspawn);
				xspawn -= 0.16;
				if (xspawn < -0.2) {
					yspawn -= 0.15;
				}
				fsm[i].BuildFsm();
				fsm[i].Posisi(0.95, yy);
				yy -= 0.05;
				for (int j = 0; j < nP; j++)
				{
					peluru_musuh[i][j].BuildSprite();
				}
				if (i == nEnemy - 1) {
					enemy[0].Init();
					enemy[1].Init();
					enemy[2].Init();
					enemy[3].Init();
					enemy[4].Init();
					enemy[5].Init();
					enemy[6].Init();
					enemy[7].Init();
					enemy[8].Init();
					enemy[9].Init();
					enemy[10].Init();
					enemy[11].Init();
					enemy[12].Init();
					enemy[13].Init();
					enemy[14].Init();
					buatEnemy = false;
				}
			}
			enemy[i].DrawTank();
		}

		player.DrawSprite();
		p.DrawSprite();

		for (int i = 0; i < 400; i++)
		{
			if (tile[i]->frame_idx == 0)
			{
				tile[i]->DrawSprite();
			}
		}

		for (int i = 0; i < nEnemy; i++)
		{
			fsm[i].DrawFsm();
		}
		
		for (int i = 0; i < nP; i++)
		{
			peluru[i].DrawSprite();
			for (int j = 0; j < nEnemy; j++)
			{
				peluru_musuh[j][i].DrawSprite();
			}
		}
		if (player.nyawa == 0) {
			menu.DrawGameOver();
		}
	}

	if (Status::MAP1 == status)
	{
		nEnemy = 5;
		for (int i = 0; i < nEnemy; i++)
		{
			if (buatEnemy) {
				//enemy[i].Init();
				enemy[i].Spawn(xspawn, 0.8);
				xspawn -= 0.2;
				fsm[i].BuildFsm();
				fsm[i].Posisi(0.95, yy);
				yy -= 0.05;
				for (int j = 0; j < nP; j++)
				{
					peluru_musuh[i][j].BuildSprite();
				}
				if (i == nEnemy - 1) {
					enemy[0].Init();
					enemy[1].Init();
					enemy[2].Init();
					enemy[3].Init();
					enemy[4].Init();
					buatEnemy = false;
				}
			}
			enemy[i].DrawTank();
		}

		player.DrawSprite();
		p.DrawSprite();

		for (int i = 0; i < jumTiles; i++)
		{
			if (tile[i]->frame_idx == 0)
			{
				tile[i]->DrawSprite();
			}
		}

		for (int i = 0; i < nEnemy; i++)
		{
			fsm[i].DrawFsm();
		}
		//tile[0]->DrawSprite();

		for (int i = 0; i < nP; i++)
		{
			peluru[i].DrawSprite();
			for (int j = 0; j < nEnemy; j++)
			{
				peluru_musuh[j][i].DrawSprite();
			}
		}
		if (player.nyawa == 0) {
			menu.DrawGameOver();
		}
	}
	if (Status::MAP2 == status)
	{
		nEnemy = 5;
		for (int i = 0; i < nEnemy; i++)
		{
			if (buatEnemy) {
				//enemy[i].Init();
				enemy[i].Spawn(xspawn, 0.8);
				xspawn -= 0.2;
				fsm[i].BuildFsm();
				fsm[i].Posisi(0.95, yy);
				yy -= 0.05;
				for (int j = 0; j < nP; j++)
				{
					peluru_musuh[i][j].BuildSprite();
				}
				if (i == nEnemy - 1) {
					enemy[0].Init();
					enemy[1].Init();
					enemy[2].Init();
					enemy[3].Init();
					enemy[4].Init();
					buatEnemy = false;
				}
			}
			enemy[i].DrawTank();
		}

		player.DrawSprite();
		p.DrawSprite();

		for (int i = 0; i < jumTiles; i++)
		{
			if (tile[i]->frame_idx == 0)
			{
				tile[i]->DrawSprite();
			}
		}

		for (int i = 0; i < nEnemy; i++)
		{
			fsm[i].DrawFsm();
		}
		//tile[0]->DrawSprite();

		for (int i = 0; i < nP; i++)
		{
			peluru[i].DrawSprite();
			for (int j = 0; j < nEnemy; j++)
			{
				peluru_musuh[j][i].DrawSprite();
			}
		}
		if (player.nyawa == 0) {
			menu.DrawGameOver();
		}
	}
	if (Status::MAP3 == status)
	{
		nEnemy = 5;
		for (int i = 0; i < nEnemy; i++)
		{
			if (buatEnemy) {
				//enemy[i].Init();
				enemy[i].Spawn(xspawn, 0.8);
				xspawn -= 0.2;
				fsm[i].BuildFsm();
				fsm[i].Posisi(0.95, yy);
				yy -= 0.05;
				for (int j = 0; j < nP; j++)
				{
					peluru_musuh[i][j].BuildSprite();
				}
				if (i == nEnemy - 1) {
					enemy[0].Init();
					enemy[1].Init();
					enemy[2].Init();
					enemy[3].Init();
					enemy[4].Init();
					buatEnemy = false;
				}
			}
			enemy[i].DrawTank();
		}

		player.DrawSprite();
		p.DrawSprite();

		for (int i = 0; i < jumTiles; i++)
		{
			if (tile[i]->frame_idx == 0)
			{
				tile[i]->DrawSprite();
			}
		}

		for (int i = 0; i < nEnemy; i++)
		{
			fsm[i].DrawFsm();
		}
		//tile[0]->DrawSprite();

		for (int i = 0; i < nP; i++)
		{
			peluru[i].DrawSprite();
			for (int j = 0; j < nEnemy; j++)
			{
				peluru_musuh[j][i].DrawSprite();
			}
		}
		if (player.nyawa == 0) {
			menu.DrawGameOver();
		}
	}
	//	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
		glDisable(GL_BLEND);
}

void Demo::Collision(float deltaTime) {
	
	// Player Collision
	for (int i = 0; i < nEnemy; i++)
	{
		if (IsCollided(player.xpos, player.ypos, player.spriteWidth, player.spriteHeight, enemy[i].xpos2, enemy[i].ypos2, enemy[i].crateWidth, enemy[i].crateHeight)) {
			player.xpos = player.oldxpos;
			player.ypos = player.oldypos;
		}
	}

	//Enemy Collision
	for (int i = 0; i < nEnemy; i++)
	{
		for (int j = 0; j < nEnemy; j++)
		{
			if (i != j) {
				if (IsCollided(enemy[i].xpos2, enemy[i].ypos2, enemy[i].crateWidth, enemy[i].crateHeight, enemy[j].xpos2, enemy[j].ypos2, enemy[j].crateWidth, enemy[j].crateHeight)) {
					enemy[i].xpos2 = enemy[i].oldxpos;
					enemy[i].ypos2 = enemy[i].oldypos;
					enemy[j].xpos2 = enemy[j].oldxpos;
					enemy[j].ypos2 = enemy[j].oldypos;
				}
			}
		}
	}


	//Nabrak Tembok
	for (int i = 0; i < jumTiles; i++)
	{
		if (tile[i]->frame_idx == 0)
		{
			//Player to Tile
			if (IsCollided(player.xpos, player.ypos, player.spriteWidth, player.spriteHeight, tile[i]->xpos, tile[i]->ypos, tile[i]->spriteWidth, tile[i]->spriteHeight)) {
				player.xpos = player.oldxpos;
				player.ypos = player.oldypos;
			}

			//Peluru ke tembok
			if (IsCollided(p.xpos, p.ypos, p.spriteWidth, p.spriteHeight, tile[i]->xpos, tile[i]->ypos, tile[i]->spriteWidth, tile[i]->spriteHeight)) {
				p.Destroy();
			}

			//Enemy ke Tembok
			for (int k = 0; k < nEnemy; k++)
			{
				if (IsCollided(enemy[k].xpos2, enemy[k].ypos2, enemy[k].crateWidth, enemy[k].crateHeight, tile[i]->xpos, tile[i]->ypos, tile[i]->spriteWidth, tile[i]->spriteHeight)) {
					enemy[k].xpos2 = enemy[k].oldxpos;
					enemy[k].ypos2 = enemy[k].oldypos;
				}
			}

			//Peluru tank nabrak tembok
			for (int j = 0; j < nP; j++)
			{
				if (IsCollided(peluru[j].xpos, peluru[j].ypos, peluru[j].spriteWidth, peluru[j].spriteHeight, tile[i]->xpos, tile[i]->ypos, tile[i]->spriteWidth, tile[i]->spriteHeight)) {
					peluru[j].Destroy();
				}
				for (int k = 0; k < nEnemy; k++)
				{
					if (IsCollided(peluru_musuh[k][j].xpos, peluru_musuh[k][j].ypos, peluru_musuh[k][j].spriteWidth, peluru_musuh[k][j].spriteHeight, tile[i]->xpos, tile[i]->ypos, tile[i]->spriteWidth, tile[i]->spriteHeight)) {
						peluru_musuh[k][j].Destroy();
					}
				}
			}
		}
	}

	// Enemy Collision
	for (int i = 0; i < nEnemy; i++)
	{
		if (IsCollided(enemy[i].xpos2, enemy[i].ypos2, enemy[i].crateWidth, enemy[i].crateHeight, player.xpos, player.ypos, player.spriteWidth, player.spriteHeight)) {
			enemy[i].xpos2 = enemy[i].oldxpos;
			enemy[i].ypos2 = enemy[i].oldypos;
		}

		//Peluru player Collision
		if (IsCollided(p.xpos, p.ypos, p.spriteWidth, p.spriteHeight, enemy[i].xpos2, enemy[i].ypos2, enemy[i].crateWidth, enemy[i].crateHeight)) {
			kurangiNyawa();
			p.Destroy();
		}
	}

	//Peluru ke tank
	for (int j = 0; j < nP; j++)
	{
		for (int k = 0; k < nEnemy; k++)
		{
			//Kena NPC
			if (IsCollided(peluru[j].xpos, peluru[j].ypos, peluru[j].spriteWidth, peluru[j].spriteHeight, enemy[k].xpos2, enemy[k].ypos2, enemy[k].crateWidth, enemy[k].crateHeight)) {
				peluru[j].Destroy();
				enemy[k].nyawa -= 1;
				kurangiNyawa();
			}

			//Kena Player
			if (IsCollided(peluru_musuh[k][j].xpos, peluru_musuh[k][j].ypos, peluru_musuh[k][j].spriteWidth, peluru_musuh[k][j].spriteHeight, player.xpos, player.ypos, player.spriteWidth, player.spriteHeight)) {
				peluru_musuh[k][j].Destroy();
				kurangiNyawaPlayer();
			}
		}
	}
}

void kurangiNyawa() {
//	enemy.nyawa = enemy.nyawa - 1;
//	cout << enemy.nyawa << endl;
}

void kurangiNyawaPlayer() {
	player.nyawa = player.nyawa - 1;
	cout << "Nyawa Player = " << player.nyawa << endl;
	if (player.nyawa == 0) {
		player.Destroy();
	}
}

bool Demo::IsCollided(float x1, float y1, float width1, float height1,
	float x2, float y2, float width2, float height2) {
	return (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2);
}

void Demo::Input(float deltaTime) {

	player.oldxpos = player.xpos;
	player.oldypos = player.ypos;

	if (IsKeyDown(SDLK_RIGHT) || IsKeyDown(SDL_BUTTON_RIGHT)) {
		player.xpos += deltaTime * SPEED;
		player.degree = 270;
	}

	if (IsKeyDown(SDLK_LEFT) || IsKeyDown(SDL_BUTTON_LEFT)) {
		player.xpos -= deltaTime * SPEED;
		player.degree = 90;
	}

	if (IsKeyDown(SDLK_DOWN)) {
		player.ypos -= deltaTime * SPEED;
		player.degree = 180;
	}

	if (IsKeyDown(SDLK_UP)) {
		player.ypos += deltaTime * SPEED;
		player.degree = 0;
	}

	
	/*if (IsKeyDown(SDLK_a)) {
		p.xpos = player.xpos;
		p.ypos = player.ypos;
		p.active = true;
		p.degree = player.degree;
	}

	if (IsKeyDown(SDLK_s)) {
		p.Destroy();
	}*/
	
	if (IsKeyPressed(SDLK_q)) {		
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10) {
			peluru[nPeluru].xpos = player.xpos;
			peluru[nPeluru].ypos = player.ypos;
			peluru[nPeluru].active = true;
			peluru[nPeluru].degree = player.degree;
			nPeluru++;
			if (nPeluru == nP + 1 ) {
				nPeluru = 0;
			}
			frameCounter = 0;
		}
	}
}

void membuatMap(string map, int jumlahTile) {
	setTiles(map, jumlahTile);
	//tile[0]->BuildSprite();
	for (int i = 0; i < jumlahTile; i++)
	{
		tile[i]->BuildSprite();
	}
}

bool setTiles(string maps, int jumlahTile)
{
	float WIDTH, HEIGHT;
	float mex;
	if (jumlahTile == 400) {
		WIDTH = 0.05;
		HEIGHT = 0.05;
		mex = 0.95;
	}
	else if (jumlahTile == 900) {
		WIDTH = 0.03333333333;
		HEIGHT = 0.03333333333;
		mex = 0.973333;
	}
	else if (jumlahTile == 1600) {
		WIDTH = 0.025;
		HEIGHT = 0.025;
		mex = 0.975;
	}
	//Success flag
	bool tilesLoaded = true;

	//The tile offsets
	float x = -1, y = -1;

	//Open the map
	std::ifstream map(maps);

	//If the map couldn't be loaded
	if (false)
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	if (true)
	{
		//tile[0] = new Tiles(0, 0, 0);
		//Initialize the tiles
		for (int i = 0; i < jumlahTile; ++i)
		{
		//	cout << "Enemy Pos = " << enemy.xpos2 << endl;
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
			{
			//	cout << x << " " << y << " " << tileType << endl;
				tile[i] = new Tiles(x+WIDTH, y+HEIGHT, tileType);
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += WIDTH * 2;

			//If we've gone too far
			if (x >= mex)
			{
				//Move back
				x = -1;

				//Move to the next row
				y += HEIGHT * 2;
			}
		}

		//Clip the sprite sheet
		if (tilesLoaded)
		{
//			TileClips[TILE_WHITE].frame_idx = 0;
//			TileClips[TILE_WHITE].spriteWidth = TILE_WIDTH;
//			TileClips[TILE_WHITE].spriteHeight = TILE_HEIGHT;

//			TileClips[TILE_BLACK].frame_idx = 1;
//			TileClips[TILE_BLACK].spriteWidth = TILE_WIDTH;
//			TileClips[TILE_BLACK].spriteHeight = TILE_HEIGHT;
		}
	}

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}

void Enemy::Serang(int i) {
	static int frameCounter = 0;
		frameCounter++;
//		for (int i = 0; i < nEnemy; i++)
		{
			if (frameCounter == 40) {
				peluru_musuh[i][nPeluru].xpos = enemy[i].xpos2;
				peluru_musuh[i][nPeluru].ypos = enemy[i].ypos2;
				peluru_musuh[i][nPeluru].active = true;
				peluru_musuh[i][nPeluru].degree = enemy[i].degree;
				nPeluru++;
				if (nPeluru == nP + 1) {
					nPeluru = 0;
				}
				frameCounter = 0;
			}
			if (enemy[i].texture2 == NULL) {
				for (int j = 0; j < nP; i++)
				{
					peluru_musuh[i][j].Destroy();
				}
			}
		}
}

void Demo::Fsm(float deltaTime) {
	float jarak;

	for (int i = 0; i < nEnemy; i++)
	{
		jarak = enemy[i].HitungJarak(enemy[i].xpos2, enemy[i].ypos2, player.xpos, player.ypos);

		GLint l1 = glGetUniformLocation(fsm[i].program, "jarak");
		UseShader(fsm[i].program);
		glUniform1f(l1, jarak);

		GLint l2 = glGetUniformLocation(fsm[i].program, "nyawa");
		UseShader(fsm[i].program);
		glUniform1f(l2, enemy[i].nyawa);

		glm::vec3 color;
		glReadPixels(hitungPosx(fsm[i].xpos), hitungPosy(fsm[i].ypos), 1, 1, GL_RGB, GL_FLOAT, &color);
		//cout << "Pos x : " << (fsm[i].xpos) << endl;
		//cout << color.r << endl;
		float state = color.r;
		if (color.r <= 0.1)
		{
			enemy[i].Patroli(deltaTime, i);
		}
		else if (color.r >= 0.9) {
			enemy[i].Destroy();
		}
		else {
			enemy[i].Kejar(enemy[i].xpos2, enemy[i].ypos2, player.xpos, player.ypos, deltaTime);
			enemy[i].Serang(i);
		}

		GLint l3 = glGetUniformLocation(fsm[i].program, "state");
		UseShader(fsm[i].program);
		glUniform1f(l3, state);
	}
}

float hitungPosx(float xpos) {
	float posx = 700 * (xpos + 1) / 2;
	return posx;
}

float hitungPosy(float ypos) {
	float posy = 700 * (ypos + 1) / 2;
	return posy;
}

void thread_loading() {
	cout << "Thread Jalan" << endl;
//	load.DrawSprite();
//	load.DrawTeks();
}

void call_from_thread() {
	std::cout << "Hello, World!" << std::endl;
}