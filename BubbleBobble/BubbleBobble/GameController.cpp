#define _CRT_SECURE_NO_WARNINGS
#include "GameController.hpp"
#include "EnemyManager.hpp"
#include "LevelManager.hpp"
#include "TextureManager.hpp"
#include "ObjectsManager.hpp"
#include "ZenChan.hpp"
#include <iostream>


GameController::GameController()
{
	AudioManager& audioManager = AudioManager::Instance();
	audioManager.CreateSound("../Assets/Sounds/SFX/Pause.wav","StartGame");
	audioManager.CreateSound("../Assets/Sounds/SFX/Credito.wav","InsertCoin");
	audioManager.CreateMusic("../Assets/Sounds/Music/02_Room Theme (The Quest Begins).ogg","IntroSong");
	audioManager.CreateMusic("../Assets/Sounds/Music/03_Room Theme.ogg","GameSong");

	TextureManager::Instance().CreateTexture("../Assets/Sprites/Text.png","TextUI");
	TextureManager::Instance().CreateTexture("../Assets/Sprites/TextTransparent.png","TextUITransparent");
	TextureManager::Instance().CreateTexture("../Assets/Sprites/IntroductionCover.png","IntroductionCover");

	topUI.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	initialScreen.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	insertCoinScreen.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	coinInsertedScreen.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	loadingGameScreen.SetTexture(TextureManager::Instance().GetTexture("TextUI"));

	lifesHUD.SetTexture(TextureManager::Instance().GetTexture("TextUITransparent"));
	lifesHUD.ModifyRenderer().ChangeDisplacement({ 0,(GAME_TILE_HEIGHT-1) * TILE_SIZE });

	player1PointsMap.ModifyRenderer().ChangeDisplacement({ 0, 1.f * TILE_SIZE });
	player1PointsMap.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	player2PointsMap.ModifyRenderer().ChangeDisplacement(Vector2{ 21.f * TILE_SIZE,1.f * TILE_SIZE });
	player2PointsMap.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	highScorePointsMap.ModifyRenderer().ChangeDisplacement(Vector2{ 11.f * TILE_SIZE,1.f * TILE_SIZE });
	highScorePointsMap.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	

	ChangeState(8);


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

	std::cout << "Game State Changed --> " << state << std::endl;
	switch (state)
	{
	case GameController::InitialScreen:
		audioManager.PlaySoundByName("StartGame");
		coinsInserted = 0;
		coinsInsertedSound = 0;
		topUI.isActive = true;
		initialScreen.isActive = true;
		break;
	case GameController::InsertCoinScreen:
		topUI.isActive = true;
		insertCoinScreen.isActive = true;
		break;
	case GameController::TutorialScreen:
		
		break;
	case GameController::CoinInsertedScreen:
		coinInsertedScreen.isActive = true;
		topUI.isActive = true;
		break;
	case GameController::LoadingGameScreen:
		loadingGameScreen.isActive = true;
		audioManager.PlayMusicByName("IntroSong");
		break;
	case GameController::GameScreen:
		topUI.isActive = true;
		audioManager.StopMusicByName("IntroSong");
		audioManager.PlayMusicByName("GameSong");

		player1.Reset();
		player2.Reset();
		EnemyManager::Instance().Reset();
		ObjectsManager::Instance().Reset();

		break;
	case GameController::Results:
		audioManager.StopMusicByName("GameSong");
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
		if (internalTimer > LOADING_GAME_TIME)
			ChangeState(5);
		break;
	case GameController::GameScreen:

		for (size_t i = 0; i < GAME_TILE_WIDTH; i++)
		{
			if(i< player1.GetLifes() && player1.isActive && player1.GetLifes()>=0)
				lifesHUD.ModifyTile(Vector2{(float)i,0}, 385);
			else {
				lifesHUD.ModifyTile(Vector2{ (float)i,0 }, 387);
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
	LevelManager::Instance().Update();
	BubbleManager::Instance().Update();
	EnemyManager::Instance().Update();
	ObjectsManager::Instance().Update();
	if(player1.isActive)
		player1.Update();
	if (player2.isActive)
		player2.Update();

	if (!player2.isActive && !player1.isActive) {
		////Lose
		ChangeState(6);
	}
	if (IsKeyPressed(KEY_F3)) {
		player1.HitPlayer(player1.GetLifes()+1);
		player2.HitPlayer(player2.GetLifes() + 1);
	}
	if (IsKeyPressed(KEY_F4))
		player1.HitPlayer();
	if (IsKeyPressed(KEY_F5))
		player2.HitPlayer();

	if (IsKeyPressed(KEY_F2)) {
		DebugMode = !DebugMode;
	}

	if (IsKeyPressed(KEY_F1)) {
		player1.SetIfCanBeHitted_GOD_MODE(!player1.CanBeHit_GOD_MODE());
		player2.SetIfCanBeHitted_GOD_MODE(!player2.CanBeHit_GOD_MODE());

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

	if (DebugMode) {
		LevelManager::Instance().RenderDebug();
		ObjectsManager::Instance().RenderDebug();
		BubbleManager::Instance().RenderDebug();
		EnemyManager::Instance().RenderDebug();
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
	if (state == GameScreen)
		lifesHUD.Render();
}

void GameController::RenderGameLate()
{
	if (player2.isActive)
		player2.Render();
	if (player1.isActive)
		player1.Render();

	if (DebugMode) {
		if (player2.isActive)
			player2.RenderDebug();
		if (player1.isActive)
			player1.RenderDebug();
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
