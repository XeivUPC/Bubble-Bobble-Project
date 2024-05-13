#define _CRT_SECURE_NO_WARNINGS
#include "GameController.hpp"
#include "EnemyManager.hpp"
#include "LevelManager.hpp"
#include "TextureManager.hpp"
#include "ObjectsManager.hpp"
#include "PointsParticlesManager.hpp"
#include "LoadingScreenParticle.hpp"
#include "ZenChan.hpp"
#include <iostream>


GameController::GameController()
{
	AudioManager& audioManager = AudioManager::Instance();
	audioManager.CreateSound("../Assets/Sounds/SFX/Pause.wav","StartGame");
	audioManager.CreateSound("../Assets/Sounds/SFX/Credito.wav","InsertCoin");
	audioManager.CreateSound("../Assets/Sounds/SFX/HurryMode.wav","GameHurryModeStart");
	audioManager.CreateMusic("../Assets/Sounds/Music/02_Room Theme (The Quest Begins).ogg","IntroSong");
	audioManager.CreateMusic("../Assets/Sounds/Music/03_Room Theme.ogg","GameSong");
	audioManager.CreateMusic("../Assets/Sounds/Music/06_Room Theme - Hurry (No Intro).ogg","GameHurryModeSong");

	TextureManager::Instance().CreateTexture("../Assets/Sprites/Text.png","TextUI");
	TextureManager::Instance().CreateTexture("../Assets/Sprites/TextTransparent.png","TextUITransparent");
	TextureManager::Instance().CreateTexture("../Assets/Sprites/IntroductionCover.png","IntroductionCover");

	topUI.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	initialScreen.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	insertCoinScreen.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	coinInsertedScreen.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	loadingGameScreen.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	controlsScreen.SetTexture(TextureManager::Instance().GetTexture("TextUI"));

	lifesHUD.SetTexture(TextureManager::Instance().GetTexture("TextUITransparent"));
	lifesHUD.ModifyRenderer().ChangeDisplacement({ 0,(GAME_TILE_HEIGHT-1) * TILE_SIZE });

	newRoundUI.SetTexture(TextureManager::Instance().GetTexture("TextUITransparent"));
	newRoundUI.ModifyRenderer().ChangeDisplacement({ ((GAME_TILE_WIDTH/ 2)-4) * TILE_SIZE,((GAME_TILE_HEIGHT/2)-1) * TILE_SIZE });
	newRoundUI.isActive = false;
	

	player1PointsMap.ModifyRenderer().ChangeDisplacement({ 0, 1.f * TILE_SIZE });
	player1PointsMap.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	player2PointsMap.ModifyRenderer().ChangeDisplacement(Vector2{ 21.f * TILE_SIZE,1.f * TILE_SIZE });
	player2PointsMap.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	highScorePointsMap.ModifyRenderer().ChangeDisplacement(Vector2{ 11.f * TILE_SIZE,1.f * TILE_SIZE });
	highScorePointsMap.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	

	Animation animHUrryMode = { TextureManager::Instance().GetTexture("TextUITransparent") ,0.2f };
	animHUrryMode.frames.push_back({ 2 * TILE_REAL_SIZE , 6 * TILE_REAL_SIZE , TILE_REAL_SIZE *7, TILE_REAL_SIZE  });
	animHUrryMode.frames.push_back({2 * TILE_REAL_SIZE , 7 * TILE_REAL_SIZE , TILE_REAL_SIZE *7, TILE_REAL_SIZE });
	hurryModeRenderer.AddAnimation("HurryMode",animHUrryMode);
	hurryModeRenderer.PlayAniamtion("HurryMode");


	ChangeState(0);
	

	EnemyManager::Instance().AddTarget(&player1);
	EnemyManager::Instance().AddTarget(&player2);

	ObjectsManager::Instance().AddCollector(&player1);
	ObjectsManager::Instance().AddCollector(&player2);


	int highScore = 0;
	int* highScore_ptr = &highScore;
	LoadGameData(highScore_ptr);
	highScorePoints.SetPuntutation(highScore);

}

GameController::~GameController()
{
	SaveGameData(highScorePoints.GetPuntuation());
}

void GameController::Update()
{
	internalTimer += GetFrameTime();

	UpdateUI();
	if (state == GameScreen)
		UpdateGame();
}

void GameController::Render()
{
	RenderUIEarly();
	if (state == GameScreen)
		RenderGameEarly();
	RenderUILate();
	if (state == GameScreen)
		RenderGameLate();
}

void GameController::ChangeState(int stateIndex)
{
	internalTimer = 0;
	AudioManager& audioManager = AudioManager::Instance();
	state = static_cast<GameState>(stateIndex);

	topUI.isActive = false;
	initialScreen.isActive = false;
	insertCoinScreen.isActive = false;
	coinInsertedScreen.isActive = false;
	loadingGameScreen.isActive = false;
	controlsScreen.isActive = false;
	newRoundUI.isActive = false;

	std::cout << "Game State Changed --> " << state << std::endl;
	switch (state)
	{
	case GameController::InitialScreen:
		audioManager.PlaySoundByName("StartGame");
		coinsInserted = 0;
		coinsInsertedSound = 0;
		topUI.isActive = true;
		initialScreen.isActive = true;

		player1Points.SetPuntutation(0);
		player1Points.SetMultiplier(1);
		player2Points.SetPuntutation(0);
		player2Points.SetMultiplier(1);
		break;
	case GameController::InsertCoinScreen:
		topUI.isActive = true;
		insertCoinScreen.isActive = true;
		break;
	case GameController::TutorialScreen:
		controlsScreen.isActive = true;
		break;
	case GameController::CoinInsertedScreen:
		coinInsertedScreen.isActive = true;
		topUI.isActive = true;
		break;
	case GameController::LoadingGameScreen:
		loadingGameScreen.isActive = true;
		audioManager.PlayMusicByName("IntroSong");
		player1.SetState(6);
		player2.SetState(6);

		break;
	case GameController::GameScreen:
		ParticleManager::Instance().DestroyAll();
		topUI.isActive = true;
		audioManager.StopMusicByName("IntroSong");
		audioManager.PlayMusicByName("GameSong");

		player1.Reset();
		player2.Reset();
		BubbleManager::Instance().DisableAll();
		EnemyManager::Instance().DestroyAll();
		ObjectsManager::Instance().Reset();
		LevelManager::Instance().Reset();
		ChangeNextLevelUI();

		break;
	case GameController::Results:
		audioManager.StopMusicByName("GameSong");
		AudioManager::Instance().StopMusicByName("GameHurryModeSong");
		ChangeState(7);
		break;
	case GameController::GameOver:
		ChangeState(0);
		break;
	default:
		break;
	}
}

void GameController::UpdateUI()
{
	switch (state)
	{
	case GameController::InitialScreen:
		if (internalTimer > INIT_SCREEN_TIME)
			ChangeState(1);
		if (IsKeyPressed(KEY_RIGHT_SHIFT))
		{
			InsertCoin(); ChangeState(3);
		}
		break;
	case GameController::InsertCoinScreen:
		if (internalTimer > INSERT_COIN_TIME)
			ChangeState(2);
		if (IsKeyPressed(KEY_RIGHT_SHIFT))
		{
			InsertCoin(); ChangeState(3);
		}
		break;
	case GameController::TutorialScreen:
		if (internalTimer > TUTORIAL_TIME)
			ChangeState(0);
		if (IsKeyPressed(KEY_RIGHT_SHIFT))
		{
			InsertCoin(); ChangeState(3);
		}
		break;
	case GameController::CoinInsertedScreen:
		CheckInsertedCoinsSound();
		if (IsKeyPressed(KEY_RIGHT_SHIFT))
			InsertCoin();
		if (IsKeyPressed(KEY_ENTER))
			ChangeState(4);
		break;
	case GameController::LoadingGameScreen:
		player1.position.x = 6 * TILE_SIZE + sin(internalTimer*6) * TILE_SIZE*1;
		player1.position.y = 15 * TILE_SIZE + cos(internalTimer*6) * TILE_SIZE*1;

		player2.position.x = (GAME_TILE_WIDTH-8) * TILE_SIZE - sin(internalTimer * 6) * TILE_SIZE * 1;
		player2.position.y = 15 * TILE_SIZE + cos(internalTimer * 6) * TILE_SIZE * 1;

		loadingShootTimer += deltaTime;
		if (loadingShootTimer >= LOADING_GAME_SHOOT_TIME) {
			ParticleManager::Instance().AddParticle(new LoadingScreenParticle({ GAME_TILE_WIDTH / 2 * TILE_SIZE, 15 * TILE_SIZE }, { - sin(internalTimer * 6),0+ cos(internalTimer * 6) }));
			ParticleManager::Instance().AddParticle(new LoadingScreenParticle({ GAME_TILE_WIDTH / 2 * TILE_SIZE, 15 * TILE_SIZE }, { -sin(PI / 2 + internalTimer * 6), cos(PI / 2 + internalTimer * 6) }));
			ParticleManager::Instance().AddParticle(new LoadingScreenParticle({ GAME_TILE_WIDTH / 2 * TILE_SIZE, 15 * TILE_SIZE }, {  -sin(PI + internalTimer * 6), cos(PI + internalTimer * 6) }));
			ParticleManager::Instance().AddParticle(new LoadingScreenParticle({ GAME_TILE_WIDTH / 2 * TILE_SIZE, 15 * TILE_SIZE }, { -sin(3 * PI / 2 + internalTimer * 6), cos(3 * PI / 2 + internalTimer * 6) }));
			loadingShootTimer = 0;
		}
		ParticleManager::Instance().Update();
		if (internalTimer > LOADING_GAME_TIME)
			ChangeState(5);
		break;
	case GameController::GameScreen:

		for (size_t i = 0; i < GAME_TILE_WIDTH; i++)
		{
			if(i< player1.GetLifes() && player1.isActive && player1.GetLifes()>=0)
				lifesHUD.ModifyTile(Vector2{(float)i,0}, 385);
			else {
				lifesHUD.ModifyTile(Vector2{ (float)i,0 }, 400);
			}
		}
		for (int i = player2.GetLifes()-1; i >=0 ; i--)
		{
			if (player2.isActive && player1.GetLifes() >= 0)
				lifesHUD.ModifyTile(Vector2{ (GAME_TILE_WIDTH- 1) - (float)i, 0 }, 386);
		}

		break;
	case GameController::Results:

		break;
	case GameController::GameOver:

		break;
	case GameController::Cover:
		if (internalTimer >= COVER_SCREEN_TIME)
			ChangeState(0);
		break;
	default:
		break;
	}

	if (topUI.isActive) {
		player1PointsUpdater.Update();
		player2PointsUpdater.Update();
		highScorePointsUpdater.Update();
	}

}

void GameController::UpdateGame()
{

	if (player1Points.GetPuntuation() > highScorePoints.GetPuntuation() || player2Points.GetPuntuation() > highScorePoints.GetPuntuation())
	{
		if (player1Points.GetPuntuation() > player2Points.GetPuntuation()) {
			highScorePoints.SetPuntutation(player1Points.GetPuntuation());
		}else
			highScorePoints.SetPuntutation(player2Points.GetPuntuation());
	}

	if (IsKeyPressed(KEY_F3)) {
		player1.HitPlayer_GOD_MODE(player1.GetLifes() + 1);
		player2.HitPlayer_GOD_MODE(player2.GetLifes() + 1);
	}
	if (IsKeyPressed(KEY_F4))
		player1.HitPlayer_GOD_MODE();
	if (IsKeyPressed(KEY_F5))
		player2.HitPlayer_GOD_MODE();

	if (IsKeyPressed(KEY_F6))\
		EnemyManager::Instance().KillAllEnemies();

	if (IsKeyPressed(KEY_F2)) {
		DebugMode = !DebugMode;
	}

	if (IsKeyPressed(KEY_F1)) {
		player1.SetIfCanBeHitted_GOD_MODE(!player1.CanBeHit_GOD_MODE());
		player2.SetIfCanBeHitted_GOD_MODE(!player2.CanBeHit_GOD_MODE());

	}
	if (!player2.isActive && !player1.isActive) {
		////Lose
		ChangeState(6);
	}
	LevelManager::Instance().Update();
	PointsParticlesManager::Instance().Update();
	ParticleManager::Instance().Update();
	bool isInTransition = player1.IsInBubbleMode() || ( player2.IsInBubbleMode());

	if (isInTransition) {
		if (player1.isActive && player1.IsInBubbleMode())
			player1.Update();
		if (player2.isActive && player2.IsInBubbleMode())
			player2.Update();
		internalTimer = 0;
		return;
	}

	if (internalTimer < START_GAME_DELAY) {
		if(!newRoundUI.isActive)
			ChangeNextLevelUI();
		newRoundUI.isActive = true;
		return;
	}
	else
		newRoundUI.isActive = false;

	
	hurryModeTimer += deltaTime;
	if (!isHurryOnMode) {
		if (hurryModeTimer > HURRY_MODE_TIME_WAIT) {
			isHurryOnMode = true;
			hurryModeSprite.position.y = GAME_TILE_HEIGHT * TILE_SIZE;
			hurryModeTimer = 0;
			AudioManager::Instance().PlaySoundByName("GameHurryModeStart");
			AudioManager::Instance().StopMusicByName("GameSong");
		}
	}
	else {
		if (hurryModeTimer < HURRY_MODE_TIME_HOLD) {
			if (hurryModeSprite.position.y <= hurryModeYTilePosition) {
				hurryModeSprite.position.y = hurryModeYTilePosition;
			}
			hurryModeSprite.position.y -= hurryModeMoveSpeed * deltaTime;
			return;
		}else{
			if (!EnemyManager::Instance().IsAngryMode())
			{
				EnemyManager::Instance().SetAngry(true);
				AudioManager::Instance().PlayMusicByName("GameHurryModeSong");
			}
		}
	}
	
	BubbleManager::Instance().Update();
	EnemyManager::Instance().Update();
	ObjectsManager::Instance().Update();
	if (player1.isActive)
		player1.Update();
	if (player2.isActive)
		player2.Update();

	if (EnemyManager::Instance().EnemiesAlive() == 0) {
		if (!levelEnded) {
			BubbleManager::Instance().PopAll();

		}
		levelEnded = true;
		endLevelTimer += deltaTime;
		hurryModeTimer = 0;
		isHurryOnMode = false;
		if (endLevelTimer >= END_LEVEL_TIME_WAIT) {
			LevelManager::Instance().StartTransition();
			BubbleManager::Instance().DisableAll();
			BubbleManager::Instance().Reset();
			EnemyManager::Instance().DestroyAll();
			ObjectsManager::Instance().DestroyAll();
			EnemyManager::Instance().SetAngry(false);
			
			hurryModeTimer = 0;
			endLevelTimer = 0;
			levelEnded = false;

			if (isHurryOnMode) {
				AudioManager::Instance().StopMusicByName("GameHurryModeSong");
				AudioManager::Instance().PlayMusicByName("GameSong");
			}
			isHurryOnMode = false;
		}	
	}


}

void GameController::RenderUIEarly()
{
	if (state == InitialScreen) {
		DrawRectangle(7 * TILE_SIZE, 5 * TILE_SIZE, 17 * TILE_SIZE, 13 * TILE_SIZE, logoColors[(int)logoColorIndex]);
		logoColorIndex += deltaTime * 25;
		if (logoColorIndex >= 6)
			logoColorIndex -= 6;
	}
	initialScreen.Render();
	insertCoinScreen.Render();
	coinInsertedScreen.Render();
	loadingGameScreen.Render();
	controlsScreen.Render();
	
	if (state == Cover) {
		DrawTextureEx(*TextureManager::Instance().GetTexture("IntroductionCover"), { 0,0 }, 0, TILE_SCALE_FACTOR, WHITE);
	}

}

void GameController::RenderGameEarly()
{
	LevelManager::Instance().Render();
	ObjectsManager::Instance().Render();
	BubbleManager::Instance().Render();
	EnemyManager::Instance().Render();
	PointsParticlesManager::Instance().Render();
	ParticleManager::Instance().Render();
	if (DebugMode) {
		LevelManager::Instance().Debug();
		ObjectsManager::Instance().Debug();
		BubbleManager::Instance().Debug();
		EnemyManager::Instance().Debug();
		PointsParticlesManager::Instance().Debug();
		ParticleManager::Instance().Debug();
	}
}

void GameController::RenderUILate()
{
	topUI.Render();
	
	if (topUI.isActive) {
		player1PointsMap.Render();
		player2PointsMap.Render();
		highScorePointsMap.Render();
	}
	if (state == GameScreen) {
		newRoundUI.Render();
		lifesHUD.Render();
	}

	if (state == LoadingGameScreen) {
		player1.Render();
		player2.Render();
		ParticleManager::Instance().Render();
	}
}

void GameController::RenderGameLate()
{
	if (player2.isActive)
		player2.Render();
	if (player1.isActive)
		player1.Render();

	if (DebugMode) {
		if (player2.isActive)
			player2.Debug();
		if (player1.isActive)
			player1.Debug();
	}

	if (isHurryOnMode && hurryModeTimer < HURRY_MODE_TIME_HOLD) {
		hurryModeSprite.position = { 14 * TILE_SIZE,hurryModeSprite.position.y };
		hurryModeRenderer.UpdateAnimation();
		hurryModeRenderer.Draw(hurryModeSprite.position.x - TILE_SIZE, hurryModeSprite.position.y - TILE_SIZE , 0, WHITE);
	}
}

void GameController::InsertCoin()
{
	if (coinsInserted < MAX_COINS) {
		coinsInserted++;
		coinInsertedScreen.ModifyTile(Vector2{ GAME_TILE_WIDTH - 2.f,GAME_TILE_HEIGHT - 1.f }, FromNumberToTile(coinsInserted));
	}
}

void GameController::CheckInsertedCoinsSound()
{
	if (coinsInserted > coinsInsertedSound) {
		if (!AudioManager::Instance().IsSoundPlayingNow("InsertCoin"))
		{
			AudioManager::Instance().PlaySoundByName("InsertCoin");
			coinsInsertedSound++;
		}
	}
}

void GameController::ChangeNextLevelUI()
{
	int levelNumber = LevelManager::Instance().GetActualLevelIndex();
	if (levelNumber > 9) {
		int num = levelNumber % 10;
		int numTile = FromNumberToTile(num);
		newRoundUI.ModifyTile(7, 0, FromNumberToTile(numTile));
		levelNumber -= num;
		levelNumber /= 10;
		num = levelNumber % 10;
		numTile = FromNumberToTile(num);
		newRoundUI.ModifyTile(6, 0, FromNumberToTile(numTile));
	}
	else {
		newRoundUI.ModifyTile(7, 0, FromNumberToTile(levelNumber));
		newRoundUI.ModifyTile(6, 0, 336);
	}
}

void GameController::SaveGameData(int highScore)
{
	FILE* file;
	file = fopen("../Assets/SaveData/HighScore.txt", "w");
	fprintf(file, "%d", highScore);
	fclose(file);
}

void GameController::LoadGameData(int* highScore)
{
	FILE* file;
	file = fopen("../Assets/SaveData/HighScore.txt", "r");
	fscanf(file, "%d", highScore);
	fclose(file);
}

int GameController::FromNumberToTile(int num)
{
	switch (num)
	{
	case 0:
		return 208;
	case 1:
		return 209;
	case 2:
		return 210;
	case 3:
		return 211;
	case 4:
		return 212;
	case 5:
		return 213;
	case 6:
		return 214;
	case 7:
		return 215;
	case 8:
		return 216;
	case 9:
		return 217;
	default:
		break;
	}
}
