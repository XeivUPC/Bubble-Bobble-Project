#define _CRT_SECURE_NO_WARNINGS
#include "GameController.hpp"
#include "EnemyManager.hpp"
#include "LevelManager.hpp"
#include "TextureManager.hpp"
#include "ObjectsManager.hpp"
#include "LoadingScreenParticle.hpp"
#include "LoadingScreenStaticParticle.hpp"
#include "ExplodeParticle.hpp"
#include "ZenChan.hpp"
#include <iostream>


GameController::GameController()
{
	ParticleManager::Instance();
	LevelManager::Instance();

	AudioManager& audioManager = AudioManager::Instance();
	audioManager.CreateSound("Assets/Sounds/SFX/Pause.wav","StartGame");
	audioManager.CreateSound("Assets/Sounds/SFX/Credito.wav","InsertCoin");
	audioManager.CreateSound("Assets/Sounds/SFX/HurryMode.wav","GameHurryModeStart");
	audioManager.CreateMusic("Assets/Sounds/Music/02_Room Theme (The Quest Begins).ogg","IntroSong");
	audioManager.CreateMusic("Assets/Sounds/Music/03_Room Theme.ogg","GameSong");
	audioManager.CreateMusic("Assets/Sounds/Music/06_Room Theme - Hurry (No Intro).ogg","GameHurryModeSong");
	audioManager.CreateMusic("Assets/Sounds/Music/10_Thanks.ogg","ResultsSong");
	audioManager.CreateMusic("Assets/Sounds/Music/11_Final Boss.ogg","BossSong");
	audioManager.CreateMusic("Assets/Sounds/Music/12_Game Over.ogg","GameOverSong");
	audioManager.CreateMusic("Assets/Sounds/Music/15_Good Ending.ogg","VictorySong");

	TextureManager::Instance().CreateTexture("Assets/Sprites/Text.png","TextUI");
	TextureManager::Instance().CreateTexture("Assets/Sprites/TextTransparent.png","TextUITransparent");
	TextureManager::Instance().CreateTexture("Assets/Sprites/IntroductionCover.png","IntroductionCover");
	TextureManager::Instance().CreateTexture("Assets/Sprites/Points.png", "PointsParticlesTileSet");
	TextureManager::Instance().CreateTexture("Assets/Sprites/Numbers_Result.png", "ResultNumbersTileSet");
	TextureManager::Instance().CreateTexture("Assets/Sprites/WinSceneSpriteSheet.png", "WinTileSet");

	topUI.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	initialScreen.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	insertCoinScreen.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	coinInsertedScreen.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	loadingGameScreen.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	controlsScreen.SetTexture(TextureManager::Instance().GetTexture("TextUI"));
	gameOverScreen.SetTexture(TextureManager::Instance().GetTexture("TextUI"));

	lifesHUD.SetTexture(TextureManager::Instance().GetTexture("TextUITransparent"));
	lifesHUD.ModifyRenderer().ChangeDisplacement({ 0,(GAME_TILE_HEIGHT-1) * TILE_SIZE });

	newRoundUI.SetTexture(TextureManager::Instance().GetTexture("TextUITransparent"));
	newRoundUI.ModifyRenderer().ChangeDisplacement({ ((GAME_TILE_WIDTH/ 2)-4) * TILE_SIZE,((GAME_TILE_HEIGHT/2)-1) * TILE_SIZE });
	newRoundUI.isActive = false;

	resultScreen.SetTexture(TextureManager::Instance().GetTexture("MapTileSet"));
	resultScreenUI.SetTexture(TextureManager::Instance().GetTexture("TextUITransparent"));
	recordLevelUI.SetTexture(TextureManager::Instance().GetTexture("TextUITransparent"));
	recordLevelUI.ModifyRenderer().ChangeDisplacement({ 19 * TILE_SIZE,3 * TILE_SIZE });
	

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

	Animation greenRoundFlag = { TextureManager::Instance().GetTexture("TextUITransparent"),4 };
	greenRoundFlag.frames.push_back({10* TILE_REAL_SIZE,4* TILE_REAL_SIZE,11* TILE_REAL_SIZE,4* TILE_REAL_SIZE});
	Animation greenClearFlag = { TextureManager::Instance().GetTexture("TextUITransparent"),4 };
	greenClearFlag.frames.push_back({ 22 * TILE_REAL_SIZE,4 * TILE_REAL_SIZE,11 * TILE_REAL_SIZE,4 * TILE_REAL_SIZE });
	greenResultFlagRenderer.AddAnimation("GreenResultRound", greenRoundFlag);
	greenResultFlagRenderer.AddAnimation("GreenResultClear", greenClearFlag);
	greenResultFlagRenderer.PlayAniamtion("GreenResultRound");

	Animation blueRoundFlag = { TextureManager::Instance().GetTexture("TextUITransparent"),4 };
	blueRoundFlag.frames.push_back({ 33 * TILE_REAL_SIZE,4 * TILE_REAL_SIZE,11 * TILE_REAL_SIZE,4 * TILE_REAL_SIZE });
	Animation blueClearFlag = { TextureManager::Instance().GetTexture("TextUITransparent"),4 };
	blueClearFlag.frames.push_back({ 44 * TILE_REAL_SIZE,4 * TILE_REAL_SIZE,11 * TILE_REAL_SIZE,4 * TILE_REAL_SIZE });
	blueResultFlagRenderer.AddAnimation("BlueResultRound", blueRoundFlag);
	blueResultFlagRenderer.AddAnimation("BlueResultClear", blueClearFlag);
	blueResultFlagRenderer.PlayAniamtion("BlueResultRound");


	Animation greenGirlBubbleAnim = { TextureManager::Instance().GetTexture("WinTileSet"),0.1f };
	greenGirlBubbleAnim.frames.push_back({0,4* TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4 });
	greenGirlBubbleAnim.frames.push_back({1* TILE_REAL_SIZE * 4 ,4* TILE_REAL_SIZE * 4 ,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4 });
	Animation greenGirlBubbleExplodeAnim = { TextureManager::Instance().GetTexture("WinTileSet"),0.2f };
	greenGirlBubbleExplodeAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 4,4 * TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4 });
	greenGirlBubbleExplodeAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 4 ,4 * TILE_REAL_SIZE * 4 ,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4 });
	greenGirlBubbleExplodeAnim.frames.push_back({ 4 * TILE_REAL_SIZE * 4 ,4 * TILE_REAL_SIZE * 4 ,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4 });
	greenGirlBubbleExplodeAnim.frames.push_back({ 5 * TILE_REAL_SIZE * 4 ,4 * TILE_REAL_SIZE * 4 ,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4 });
	greenGirlBubbleExplodeAnim.frames.push_back({ 4 * TILE_REAL_SIZE * 4 ,5 * TILE_REAL_SIZE * 4 ,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4 });
	girlGreenBubbleRenderer.AddAnimation("GreenGirlBubbleIdle", greenGirlBubbleAnim);
	girlGreenBubbleRenderer.AddAnimation("GreenGirlBubbleExplode", greenGirlBubbleExplodeAnim);
	girlGreenBubbleRenderer.PlayAniamtion("GreenGirlBubbleIdle");

	Animation blueGirlBubbleAnim = { TextureManager::Instance().GetTexture("WinTileSet"),0.1f };
	blueGirlBubbleAnim.frames.push_back({ 0,5 * TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4 });
	blueGirlBubbleAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 4 ,5 * TILE_REAL_SIZE * 4 ,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4 });
	Animation blueGirlBubbleExplodeAnim = { TextureManager::Instance().GetTexture("WinTileSet"),0.2f };
	blueGirlBubbleExplodeAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 4,5 * TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4 });
	blueGirlBubbleExplodeAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 4 ,5 * TILE_REAL_SIZE * 4 ,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4 });
	blueGirlBubbleExplodeAnim.frames.push_back({ 4 * TILE_REAL_SIZE * 4 ,4 * TILE_REAL_SIZE * 4 ,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4 });
	blueGirlBubbleExplodeAnim.frames.push_back({ 5 * TILE_REAL_SIZE * 4 ,4 * TILE_REAL_SIZE * 4 ,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4 });
	blueGirlBubbleExplodeAnim.frames.push_back({ 4 * TILE_REAL_SIZE * 4 ,5 * TILE_REAL_SIZE * 4 ,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 4 });
	girlBlueBubbleRenderer.AddAnimation("BlueGirlBubbleIdle", blueGirlBubbleAnim);
	girlBlueBubbleRenderer.AddAnimation("BlueGirlBubbleExplode", blueGirlBubbleExplodeAnim);
	girlBlueBubbleRenderer.PlayAniamtion("BlueGirlBubbleIdle");

	Animation bigBobFallAnim = { TextureManager::Instance().GetTexture("WinTileSet"),1 };
	bigBobFallAnim.frames.push_back({ 0,0,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobRenderer.AddAnimation("BigBobFall", bigBobFallAnim);
	bigBobRenderer.PlayAniamtion("BigBobFall");

	Animation bigBobCryAnim = { TextureManager::Instance().GetTexture("WinTileSet"),0.1f };
	bigBobCryAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 8,0 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 8,0 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 8,0 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 8,0 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 8,1 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 8,0 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 8,0 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 8,0 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 8,0 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 8,1 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 8,0 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 8,0 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 8,0 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 8,0 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 8,1 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });

	bigBobCryAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 8,1 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 8,1 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 8,1 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 8,1 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 8,1 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 8,1 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 8,1 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 8,1 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 8,1 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 8,1 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 8,1 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobCryAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 8,1 * TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8,TILE_REAL_SIZE * 8 });
	bigBobRenderer.AddAnimation("BigBobFall", bigBobFallAnim);
	bigBobRenderer.AddAnimation("BigBobCry", bigBobCryAnim);
	bigBobRenderer.PlayAniamtion("BigBobFall");

	Animation greenCoupleIdleAnim = { TextureManager::Instance().GetTexture("WinTileSet"),0.2f };
	greenCoupleIdleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 4,12 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 2 });
	Animation greenCoupleHugAnim = { TextureManager::Instance().GetTexture("WinTileSet"),0.1f };
	greenCoupleHugAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 4,12 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 2 });
	greenCoupleHugAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 4,12 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 2 });
	greenCoupleHugAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 4,12 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 2 });
	greenCoupleHugAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 4,12 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 2 });
	greenCoupleHugAnim.frames.push_back({ 4 * TILE_REAL_SIZE * 4,12 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 2 });
	Animation greenCoupleEndHugAnim = { TextureManager::Instance().GetTexture("WinTileSet"),0.2f };
	greenCoupleEndHugAnim.frames.push_back({ 4 * TILE_REAL_SIZE * 4,12 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 2 });
	greenCoupleRenderer.AddAnimation("GreenCoupleHug", greenCoupleHugAnim);
	greenCoupleRenderer.AddAnimation("GreenCoupleIdle", greenCoupleIdleAnim);
	greenCoupleRenderer.AddAnimation("GreenCoupleEndHug", greenCoupleEndHugAnim);
	greenCoupleRenderer.PlayAniamtion("GreenCoupleIdle");

	Animation blueCoupleIdleAnim = { TextureManager::Instance().GetTexture("WinTileSet"),0.2f };
	blueCoupleIdleAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 4,13 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 2 });
	Animation blueCoupleHugAnim = { TextureManager::Instance().GetTexture("WinTileSet"),0.1f };
	blueCoupleHugAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 4,13 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 2 });
	blueCoupleHugAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 4,13 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 2 });
	blueCoupleHugAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 4,13 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 2 });
	blueCoupleHugAnim.frames.push_back({ 3 * TILE_REAL_SIZE * 4,13 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 2 });
	blueCoupleHugAnim.frames.push_back({ 4 * TILE_REAL_SIZE * 4,13 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 2 });
	Animation blueCoupleEndHugAnim = { TextureManager::Instance().GetTexture("WinTileSet"),0.2f };
	blueCoupleEndHugAnim.frames.push_back({ 4 * TILE_REAL_SIZE * 4,13 * TILE_REAL_SIZE * 2,TILE_REAL_SIZE * 4,TILE_REAL_SIZE * 2 });
	blueCoupleRenderer.AddAnimation("BlueCoupleHug", blueCoupleHugAnim);
	blueCoupleRenderer.AddAnimation("BlueCoupleIdle", blueCoupleIdleAnim);
	blueCoupleRenderer.AddAnimation("BlueCoupleEndHug", blueCoupleEndHugAnim);
	blueCoupleRenderer.PlayAniamtion("BlueCoupleIdle");

	Animation curtainAnim = { TextureManager::Instance().GetTexture("WinTileSet"),0.111111111 };
	curtainAnim.frames.push_back({ 0 * TILE_REAL_SIZE * 1,40 * TILE_REAL_SIZE * 1,TILE_REAL_SIZE *1,TILE_REAL_SIZE * 1 });
	curtainAnim.frames.push_back({ 1 * TILE_REAL_SIZE * 1,40 * TILE_REAL_SIZE * 1,TILE_REAL_SIZE *1,TILE_REAL_SIZE * 1 });
	curtainAnim.frames.push_back({ 2 * TILE_REAL_SIZE * 1,40 * TILE_REAL_SIZE * 1,TILE_REAL_SIZE *1,TILE_REAL_SIZE * 1 });
	curtainRenderer.AddAnimation("CurtainEar", curtainAnim);
	curtainRenderer.PlayAniamtion("CurtainEar");


	ChangeState(8);
	

	EnemyManager::Instance().AddTarget(&player1);
	EnemyManager::Instance().AddTarget(&player2);

	ObjectsManager::Instance().AddCollector(&player1);
	ObjectsManager::Instance().AddCollector(&player2);


	int highScore = 0;
	int* highScore_ptr = &highScore;
	LoadGameData(highScore_ptr,"HighScore.txt");
	highScorePoints.SetPuntutation(highScore);

}

GameController::~GameController()
{
	SaveGameData(highScorePoints.GetPuntuation(),"HighScore.txt");
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
	if (state == GameScreen || state == Win)
		RenderGameEarly();
	RenderUILate();
	if (state == GameScreen || state == Win)
		RenderGameLate();

	//Borders
	DrawRectangle(0, TILE_SIZE*GAME_TILE_HEIGHT, TILE_SIZE*GAME_TILE_WIDTH, TILE_SIZE * GAME_TILE_HEIGHT, BLACK);

	DrawRectangle(0, TILE_SIZE*GAME_TILE_HEIGHT, TILE_SIZE*GAME_TILE_WIDTH, TILE_SIZE/3, WHITE);

	DrawRectangle(-TILE_SIZE / 3, 0, TILE_SIZE / 3, TILE_SIZE * GAME_TILE_HEIGHT, WHITE);
	DrawRectangle(TILE_SIZE * GAME_TILE_WIDTH, 0, TILE_SIZE / 3, TILE_SIZE * GAME_TILE_HEIGHT, WHITE);
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
	resultScreen.isActive = false;
	resultScreenUI.isActive = false;
	gameOverScreen.isActive = false;
	logoColorIndex = 0;

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
		ParticleManager::Instance().AddParticle(new LoadingScreenStaticParticle({ GAME_TILE_WIDTH / 2 * TILE_SIZE, 15 * TILE_SIZE }, LOADING_GAME_TIME - 2));
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

		girlGreenBubbleRenderer.PlayAniamtion("GreenGirlBubbleIdle");
		girlBlueBubbleRenderer.PlayAniamtion("BlueGirlBubbleIdle");

		break;
	case GameController::Results:
		audioManager.StopMusicByName("GameSong");
		audioManager.StopMusicByName("GameHurryModeSong");
		audioManager.PlayMusicByName("ResultsSong");
		topUI.isActive = true;
		resultScreen.isActive = true;
		resultScreenUI.isActive = true;

		greenResultFlagRenderer.PlayAniamtion("GreeResultRound");
		blueResultFlagRenderer.PlayAniamtion("BlueResultRound");


		LoadGameData(&currentLevelRecord, "LevelRecord.txt");
		maxPlayerLevel = player1.GetLevel() - 1 > player2.GetLevel() - 1 ? player1.GetLevel() - 1 : player2.GetLevel() - 1;
		maxPlayerLevel *= LEVEL_MULTIPLICATION;
		if (currentLevelRecord < maxPlayerLevel){
			SaveGameData(maxPlayerLevel, "LevelRecord.txt");
			currentLevelRecord = maxPlayerLevel;
		}
		/// SetRecord
		ChangeLevelRecordUI(currentLevelRecord);

		greenResultProgressionPos = resultsProgressionInitialPos;
		blueResultProgressionPos = resultsProgressionInitialPos;
		blueResultProgressionPos.x += 4 * TILE_SIZE;
		recordResultProgressionPos = resultsProgressionInitialPos;

		resultProgressionUIAnimationTimer = 0;
		resultsProgressionDone = false;


		greenResultProgressionTargetPos = { greenResultProgressionPos.x,greenResultProgressionPos.y + ((player1.GetLevel()-1)*LEVEL_MULTIPLICATION * ((20.f * TILE_SIZE) / 100.f))};
		blueResultProgressionTargetPos = { blueResultProgressionPos.x,blueResultProgressionPos.y + ((player2.GetLevel()-1) * LEVEL_MULTIPLICATION * ((20.f * TILE_SIZE) / 100.f))};
		recordResultProgressionPos = { recordResultProgressionPos.x,recordResultProgressionPos.y + (currentLevelRecord - 1) * ((20.f * TILE_SIZE) / 100.f)};
		break;
	case GameController::GameOver:
		audioManager.StopMusicByName("ResultsSong");
		audioManager.PlayMusicByName("GameOverSong");
		audioManager.SetMusicLoopStatus("GameOverSong", false);
		topUI.isActive = true;
		gameOverScreen.isActive = true;
		break;
	case GameController::Win:
		topUI.isActive = true;
		player1.TpToSpawnPoint();
		player1.position.x += 2 * TILE_SIZE;
		player2.TpToSpawnPoint();
		player2.position.x -= 2 * TILE_SIZE;

		player1.SetState(0);
		player2.SetState(0);
		player1.ForceBaseStates();
		player2.ForceBaseStates();

		bigBobPosition = bigBobInitialPosition;
		bigBobRenderer.PlayAniamtion("BigBobFall");
		cryAniamtionTimer = 0;
		girlBubbleExplodeTimer = 0;
		bigBobExplodeTimer = 0;
		winDelaysTimer = 0;
		bigBobExploded = false;
		girlsSpawned = false;
		girlsPositioned = false;
		girlsExploded = false;
		spawnParents = false;
		playersPositioned = false;
		hugStarted = false;
		hugEnded = false;
		endOffsetProgression = { 0,0 };
		curtainPosition = { 0,0 };
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

		if (internalTimer < LOADING_GAME_TIME - 2) {
			loadingShootTimer += deltaTime;
			if (loadingShootTimer >= LOADING_GAME_SHOOT_TIME) {
				ParticleManager::Instance().AddParticle(new LoadingScreenParticle({ GAME_TILE_WIDTH / 2 * TILE_SIZE, 15 * TILE_SIZE }, { -sin(internalTimer * 6),0 + cos(internalTimer * 6) }));
				ParticleManager::Instance().AddParticle(new LoadingScreenParticle({ GAME_TILE_WIDTH / 2 * TILE_SIZE, 15 * TILE_SIZE }, { -sin(PI / 2 + internalTimer * 6), cos(PI / 2 + internalTimer * 6) }));
				ParticleManager::Instance().AddParticle(new LoadingScreenParticle({ GAME_TILE_WIDTH / 2 * TILE_SIZE, 15 * TILE_SIZE }, { -sin(PI + internalTimer * 6), cos(PI + internalTimer * 6) }));
				ParticleManager::Instance().AddParticle(new LoadingScreenParticle({ GAME_TILE_WIDTH / 2 * TILE_SIZE, 15 * TILE_SIZE }, { -sin(3 * PI / 2 + internalTimer * 6), cos(3 * PI / 2 + internalTimer * 6) }));
				loadingShootTimer = 0;
			}
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

		girlGreenBubblePosition.x = 7 * TILE_SIZE + sin(internalTimer * 3) * TILE_SIZE * 1;
		girlGreenBubblePosition.y = 7.5 * TILE_SIZE + cos(internalTimer * 3) * TILE_SIZE * 1;

		girlBlueBubblePosition.x = 25 * TILE_SIZE - sin(internalTimer * 3) * TILE_SIZE * 1;
		girlBlueBubblePosition.y = 7.5 * TILE_SIZE + cos(internalTimer * 3) * TILE_SIZE * 1;

		break;
	case GameController::Results:
		resultProgressionUIAnimationTimer += deltaTime;

		if (resultProgressionUIAnimationTimer > RESULTS_TIME_UI_ANIMATIONS)
		{
			resultProgressionUIAnimationTimer = 0;
			resultProgressionUIShow= !resultProgressionUIShow;
		}


		if (!resultsProgressionDone) {
			internalTimer = 0;
			greenResultProgressionPos.y += resultsProgressionSpeed * deltaTime;
			blueResultProgressionPos.y += resultsProgressionSpeed * deltaTime;
			if (greenResultProgressionPos.y > greenResultProgressionTargetPos.y) {
				greenResultProgressionPos.y = greenResultProgressionTargetPos.y;	
				greenResultFlagRenderer.PlayAniamtion("GreenResultClear");
			}
			if (blueResultProgressionPos.y > blueResultProgressionTargetPos.y) {
				blueResultProgressionPos.y = blueResultProgressionTargetPos.y;
				blueResultFlagRenderer.PlayAniamtion("BlueResultClear");
			}
			if (greenResultProgressionPos.y >= greenResultProgressionTargetPos.y && blueResultProgressionPos.y >= blueResultProgressionTargetPos.y) {
				resultsProgressionDone = true;
			}
			greenProgressBarLevelNumber = ((greenResultProgressionPos.y - resultsProgressionInitialPos.y) / (resultsProgressionMaxPos.y - resultsProgressionInitialPos.y)) * 100 +0.001f;
			
			blueProgressBarLevelNumber = ((blueResultProgressionPos.y - resultsProgressionInitialPos.y) / (resultsProgressionMaxPos.y - resultsProgressionInitialPos.y)) * 100 + 0.001f;

		}
		if (internalTimer >= RESULTS_TIME)
			ChangeState(7);
		break;
	case GameController::GameOver:
		if (internalTimer >= GAME_OVER_TIME)
			ChangeState(0);
		break;
	case GameController::Cover:
		if (internalTimer >= COVER_SCREEN_TIME)
			ChangeState(0);
		break;
	case GameController::Win:

		if (!girlsExploded) {
			girlGreenBubblePosition.x = 7 * TILE_SIZE + sin(internalTimer * 3) * TILE_SIZE * 1;
			girlGreenBubblePosition.y = 7.5 * TILE_SIZE + cos(internalTimer * 3) * TILE_SIZE * 1;

			girlBlueBubblePosition.x = 25 * TILE_SIZE - sin(internalTimer * 3) * TILE_SIZE * 1;
			girlBlueBubblePosition.y = 7.5 * TILE_SIZE + cos(internalTimer * 3) * TILE_SIZE * 1;
		}
		


		bigBobPosition.y+= TILE_SIZE * 7.f *deltaTime;
		if (bigBobPosition.y >= winAnimGround.y) {
			bigBobPosition.y = winAnimGround.y;
			bigBobRenderer.PlayAniamtion("BigBobCry");
			if(!bigBobExploded)
				cryAniamtionTimer += deltaTime;
			
		}

		if (!girlsExploded && spawnParents) {
			dadPosition.y += TILE_SIZE * 4.f * deltaTime;
			momPosition.y += TILE_SIZE * 4.f * deltaTime;
			if (dadPosition.y >= winAnimGround.y) {
				dadPosition.y = winAnimGround.y;
				momPosition.y = winAnimGround.y;


				winDelaysTimer += deltaTime;
				if (winDelaysTimer > WIN_ANIMATION_DELAYS) {
					dadPosition.x -= TILE_SIZE * 1.f * deltaTime;
					momPosition.x += TILE_SIZE * 1.f * deltaTime;
					if (momPosition.x >= momInitialPosition.x + 0.5 * TILE_SIZE) {
						dadPosition.x = dadInitialPosition.x - 0.5 * TILE_SIZE;
						momPosition.x = momInitialPosition.x + 0.5 * TILE_SIZE;
						girlsExploded = true;
						AudioManager::Instance().StopMusicByName("BossSong");
						winDelaysTimer = 0;
					}
				}
			}
		}

		if (girlsExploded && !girlsSpawned) {
			winDelaysTimer += deltaTime;
			if (winDelaysTimer > WIN_ANIMATION_DELAYS) {
				girlBubbleExplodeTimer += deltaTime;
				girlGreenBubbleRenderer.PlayAniamtion("GreenGirlBubbleExplode");
				girlBlueBubbleRenderer.PlayAniamtion("BlueGirlBubbleExplode");
				if (girlBubbleExplodeTimer > BUBBLE_EXPLODE_ANIMATION) {
					girlsSpawned = true;
					///SpawnGirls
					girlGreenPosition = girlGreenInitialPosition;
					girlBluePosition = girlBlueInitialPosition;
					winDelaysTimer = 0;
				}
			}
			else {
				girlGreenBubblePosition.x = 7 * TILE_SIZE + sin(internalTimer * 3) * TILE_SIZE * 1;
				girlGreenBubblePosition.y = 7.5 * TILE_SIZE + cos(internalTimer * 3) * TILE_SIZE * 1;

				girlBlueBubblePosition.x = 25 * TILE_SIZE - sin(internalTimer * 3) * TILE_SIZE * 1;
				girlBlueBubblePosition.y = 7.5 * TILE_SIZE + cos(internalTimer * 3) * TILE_SIZE * 1;
			}
		}

		if (girlsSpawned && !girlsPositioned) {
			girlGreenPosition.y += TILE_SIZE * 5.f * deltaTime;
			girlBluePosition.y += TILE_SIZE * 5.f * deltaTime;
			if (girlGreenPosition.y >= winAnimGround.y) {
				girlGreenPosition.y = winAnimGround.y;
				girlBluePosition.y = winAnimGround.y;
				girlsPositioned = true;
			}
		}

		if (girlsPositioned && !playersPositioned) {
			player1.position.x+= TILE_SIZE * 5.f * deltaTime;
			player2.position.x-= TILE_SIZE * 5.f * deltaTime;
			if (player1.position.x >= girlGreenInitialPosition.x + 2 * TILE_SIZE) {
				player1.position.x = girlGreenInitialPosition.x + 2 * TILE_SIZE;
				player2.position.x = girlBlueInitialPosition.x - 2 * TILE_SIZE;
				ParticleManager::Instance().AddParticle(new ExplodeParticle({ player1.position.x,player1.position.y-1*TILE_SIZE}, 0));
				ParticleManager::Instance().AddParticle(new ExplodeParticle({ player2.position.x,player2.position.y - 1 * TILE_SIZE },0));
				player1.isActive = false;
				player2.isActive = false;
				playersPositioned = true;
				winDelaysTimer = 0;
			}
		}

		if (playersPositioned && !hugStarted) {
			winDelaysTimer += deltaTime;
			if (winDelaysTimer <2) {
				blueCoupleRenderer.PlayAniamtion("BlueCoupleIdle");
				greenCoupleRenderer.PlayAniamtion("GreenCoupleIdle");
			}
			else {
				hugStarted = true;
				blueCoupleRenderer.PlayAniamtion("BlueCoupleHug");
				greenCoupleRenderer.PlayAniamtion("GreenCoupleHug");
				winDelaysTimer = 0;
				AudioManager::Instance().PlaySoundByName("StartGame");
			}
		}

		if (hugStarted && !hugEnded) {
			winDelaysTimer += deltaTime;
			if (winDelaysTimer > 0.5) {
				hugEnded = true;
				winDelaysTimer = 0;
				blueCoupleRenderer.PlayAniamtion("BlueCoupleEndHug");
				greenCoupleRenderer.PlayAniamtion("GreenCoupleEndHug");

				
				AudioManager::Instance().PlayMusicByName("VictorySong");
			}
		}

		if (hugEnded) {
			curtainPosition.y += 3 * TILE_SIZE * deltaTime;
			if (curtainPosition.y > TILE_SIZE * GAME_TILE_HEIGHT) {
				winDelaysTimer += deltaTime;
				endOffsetProgression.y -= 2 * TILE_SIZE * deltaTime;
				if (winDelaysTimer > WIN_ANIMATION_DELAYS * 17) {
					AudioManager::Instance().StopMusicByName("VictorySong");
					curtainPosition = { 0,0 };
					ChangeState(6);
				}
			}
		}

		if (cryAniamtionTimer > CRY_ANIMATION)
		{
			bigBobExploded = true;
			cryAniamtionTimer = false;
			///TrIGGER EXPLOSIONS
			for (size_t i = 0; i < 4; i++)
			{
				for (size_t j = 0; j < 5; j++)
				{
					float angulo = (float)rand() / RAND_MAX * 2 * PI;
					float r = (4 * TILE_SIZE) * sqrt((float)rand() / RAND_MAX);
					float x = bigBobPosition.x + r * cos(angulo);
					float y = (bigBobPosition.y - 4 * TILE_SIZE) + r * sin(angulo);
					ParticleManager::Instance().AddParticle(new ExplodeParticle({ x ,y }, i / 8.f));
				}
			}
		}
		if (!spawnParents && bigBobExploded) {
			bigBobExplodeTimer += deltaTime;
			if (bigBobExplodeTimer > BIG_BOB_EXPLODE_ANIMATION) {
				spawnParents = true;
				momPosition = momInitialPosition;
				dadPosition = dadInitialPosition;
			}
		}
		ParticleManager::Instance().Update();
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
		if (!newRoundUI.isActive) {
			ChangeNextLevelUI();
			if (LevelManager::Instance().IsLastLevel()) {
				AudioManager::Instance().StopMusicByName("GameSong");
				AudioManager::Instance().PlayMusicByName("BossSong");
			}
		}
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
				if (!LevelManager::Instance().IsLastLevel()) {
					AudioManager::Instance().PlayMusicByName("GameHurryModeSong");
				}
			}
		}
	}
	ParticleManager::Instance().Update();
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
		if (endLevelTimer >= END_LEVEL_TIME_WAIT || LevelManager::Instance().IsLastLevel()) {
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

			if(player1.isActive)
				player1.SetLevel(LevelManager::Instance().GetNextLevelIndex());
			if(player2.isActive)
				player2.SetLevel(LevelManager::Instance().GetNextLevelIndex());
			if (LevelManager::Instance().IsLastLevel())
				ChangeState(9);
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
	resultScreen.Render();
	resultScreenUI.Render();
	gameOverScreen.Render();
	
	if (state == Cover) {
		DrawTextureEx(*TextureManager::Instance().GetTexture("IntroductionCover"), { 0,0 }, 0, TILE_SCALE_FACTOR, WHITE);
	}

	if (state == Results) {
		
		greenResultFlagRenderer.UpdateAnimation();
		blueResultFlagRenderer.UpdateAnimation();

		greenResultFlagRenderer.Draw(greenResultProgressionPos.x - TILE_SIZE * 12, greenResultProgressionPos.y - TILE_SIZE,0,WHITE);
		blueResultFlagRenderer.Draw(blueResultProgressionPos.x + TILE_SIZE * 2, blueResultProgressionPos.y - TILE_SIZE,0,WHITE);
		DrawRectangle(greenResultProgressionPos.x, greenResultProgressionPos.y, TILE_SIZE * 2, TILE_SIZE / TILE_REAL_SIZE, GREEN);
		DrawRectangle(blueResultProgressionPos.x, blueResultProgressionPos.y, TILE_SIZE * 2, TILE_SIZE / TILE_REAL_SIZE, {0,176,255,255});
		if (resultProgressionUIShow) {
			DrawRectangle(recordResultProgressionPos.x, recordResultProgressionPos.y, TILE_SIZE * 2, TILE_SIZE / TILE_REAL_SIZE, { 255 ,0,115,255});
			recordLevelUI.Render();
		}
		
		int level = greenProgressBarLevelNumber;
		int num1 = 0;
		int num2 = 0;
		int offset1 = 0;
		int offset2 = 0;
		num1 = level % 10;

		level -= num1;
		level /= 10;
		num2 = level % 10;

		if (num1 > 4) {
			num1 -= 5;
			offset1 += 1;
		}
		if (num2 > 4) {
			num2 -= 5;
			offset2 += 1;
		}
			

		Vector2 positionText = { greenResultProgressionPos.x - TILE_SIZE * 9.7f ,greenResultProgressionPos.y + TILE_SIZE };
		if (greenProgressBarLevelNumber < 10) {
			positionText.x -= 0.4 * TILE_SIZE;
			textProgressLevelRender.Paint(*TextureManager::Instance().GetTexture("ResultNumbersTileSet"), positionText, {(float)num1,(float)offset1 }, { 1 * TILE_SIZE ,1.2f * TILE_SIZE }, 0);
		}
		else if (greenProgressBarLevelNumber < 100) {
			positionText.x -= 1 * TILE_SIZE;
			textProgressLevelRender.Paint(*TextureManager::Instance().GetTexture("ResultNumbersTileSet"), positionText , { (float)num2,(float)offset2 }, { 1 * TILE_SIZE ,1.2f * TILE_SIZE }, 0);
			positionText.x += 1 * TILE_SIZE;
			textProgressLevelRender.Paint(*TextureManager::Instance().GetTexture("ResultNumbersTileSet"), positionText, { (float)num1,(float)offset1 }, { 1 * TILE_SIZE ,1.2f * TILE_SIZE }, 0);
		}
		else {
			positionText.x -= 1 * TILE_SIZE;
			positionText.x -= 0.6 * TILE_SIZE;
			textProgressLevelRender.Paint(*TextureManager::Instance().GetTexture("ResultNumbersTileSet"), positionText, { 1,0 }, { 1 * TILE_SIZE ,1.2f * TILE_SIZE }, 0);
			positionText.x += 1 * TILE_SIZE;
			textProgressLevelRender.Paint(*TextureManager::Instance().GetTexture("ResultNumbersTileSet"), positionText, {0,0 }, { 1 * TILE_SIZE ,1.2f * TILE_SIZE }, 0);
			positionText.x += 1 * TILE_SIZE;
			textProgressLevelRender.Paint(*TextureManager::Instance().GetTexture("ResultNumbersTileSet"), positionText, { 0,0 }, { 1 * TILE_SIZE ,1.2f * TILE_SIZE }, 0);
		}	

		level = blueProgressBarLevelNumber;
		num1 = level % 10;

		level -= num1;
		level /= 10;
		num2 = level % 10;
		offset1 = 0;
		offset2 = 0;

		if (num1 > 4) {
			num1 -= 5;
			offset1 += 1;
		}
		if (num2 > 4) {
			num2 -= 5;
			offset2 += 1;
		}
		positionText = { blueResultProgressionPos.x + TILE_SIZE * 10.5f ,blueResultProgressionPos.y + TILE_SIZE };
		if (blueProgressBarLevelNumber < 10) {
			positionText.x -= 0.4 * TILE_SIZE;
			textProgressLevelRender.Paint(*TextureManager::Instance().GetTexture("ResultNumbersTileSet"), positionText, { (float)num1,(float)offset1 }, { 1 * TILE_SIZE ,1.2f * TILE_SIZE }, 0);
		}
		else if (blueProgressBarLevelNumber < 100) {
			positionText.x -= 1 * TILE_SIZE;
			textProgressLevelRender.Paint(*TextureManager::Instance().GetTexture("ResultNumbersTileSet"), positionText, { (float)num2,(float)offset2 }, { 1 * TILE_SIZE ,1.2f * TILE_SIZE }, 0);
			positionText.x += 1 * TILE_SIZE;
			textProgressLevelRender.Paint(*TextureManager::Instance().GetTexture("ResultNumbersTileSet"), positionText, { (float)num1,(float)offset1 }, { 1 * TILE_SIZE ,1.2f * TILE_SIZE }, 0);
		}
		else {
			positionText.x -= 1 * TILE_SIZE;
			positionText.x -= 0.6 * TILE_SIZE;
			textProgressLevelRender.Paint(*TextureManager::Instance().GetTexture("ResultNumbersTileSet"), positionText, { 1,0 }, { 1 * TILE_SIZE ,1.2f * TILE_SIZE }, 0);
			positionText.x += 1 * TILE_SIZE;
			textProgressLevelRender.Paint(*TextureManager::Instance().GetTexture("ResultNumbersTileSet"), positionText, { 0,0 }, { 1 * TILE_SIZE ,1.2f * TILE_SIZE }, 0);
			positionText.x += 1 * TILE_SIZE;
			textProgressLevelRender.Paint(*TextureManager::Instance().GetTexture("ResultNumbersTileSet"), positionText, { 0,0 }, { 1 * TILE_SIZE ,1.2f * TILE_SIZE }, 0);
		}
	}

	if (state == Win) {

	}

}

void GameController::RenderGameEarly()
{
	LevelManager::Instance().Render();
	ObjectsManager::Instance().Render();
	BubbleManager::Instance().Render();

	


	if (LevelManager::Instance().IsLastLevel() && !LevelManager::Instance().IsOnTransition()) {

		///Render LAST LEVEL GIRLS
		girlGreenBubbleRenderer.UpdateAnimation();
		girlBlueBubbleRenderer.UpdateAnimation();
		bigBobRenderer.UpdateAnimation();
		curtainRenderer.UpdateAnimation();

		if (hugEnded) {
			DrawRectangle(0, 0, TILE_SIZE * GAME_TILE_WIDTH, curtainPosition.y + TILE_SIZE / 2, BLACK);
			for (size_t i = 0; i < GAME_TILE_WIDTH; i++)
			{
				curtainRenderer.Draw(i * TILE_SIZE, curtainPosition.y, 0, WHITE);
			}
		}
		if (!girlsSpawned) {
			girlGreenBubbleRenderer.Draw(girlGreenBubblePosition.x - 2 * TILE_SIZE, girlGreenBubblePosition.y - 2 * TILE_SIZE, 0, WHITE);
			girlBlueBubbleRenderer.Draw(girlBlueBubblePosition.x - 2 * TILE_SIZE, girlBlueBubblePosition.y - 2 * TILE_SIZE, 0, WHITE);
		}
		

		if(!bigBobExploded)
			bigBobRenderer.Draw(bigBobPosition.x - 4 * TILE_SIZE, bigBobPosition.y - 8 * TILE_SIZE, 0, WHITE);

		if (spawnParents) {
			winAnim32Renderer.Paint(*TextureManager::Instance().GetTexture("WinTileSet"), { dadPosition.x - 2 * TILE_SIZE,dadPosition.y - 4 * TILE_SIZE + endOffsetProgression.y }, { 7,2 }, { 4 * TILE_SIZE ,4 * TILE_SIZE }, 0);
			winAnim32Renderer.Paint(*TextureManager::Instance().GetTexture("WinTileSet"), { momPosition.x - 2 * TILE_SIZE,momPosition.y - 4 * TILE_SIZE + endOffsetProgression.y }, { 6,2 }, { 4 * TILE_SIZE ,4 * TILE_SIZE }, 0);

		}

		if (girlsSpawned && !playersPositioned) {
			winAnim16Renderer.Paint(*TextureManager::Instance().GetTexture("WinTileSet"), { girlGreenPosition.x - 1 * TILE_SIZE,girlGreenPosition.y - 2 * TILE_SIZE }, { 0,12 }, { 2 * TILE_SIZE ,2 * TILE_SIZE }, 0);
			winAnim16Renderer.Paint(*TextureManager::Instance().GetTexture("WinTileSet"), { girlBluePosition.x - 1 * TILE_SIZE,girlBluePosition.y - 2 * TILE_SIZE }, { 1,13 }, { 2 * TILE_SIZE ,2 * TILE_SIZE }, 0);
		}

		if (playersPositioned) {
			greenCoupleRenderer.UpdateAnimation();
			blueCoupleRenderer.UpdateAnimation();
			greenCoupleRenderer.Draw(girlGreenPosition.x - 1 * TILE_SIZE, girlGreenPosition.y - 2 * TILE_SIZE + endOffsetProgression.y,0,WHITE);
			blueCoupleRenderer.Draw(girlBluePosition.x - 3 * TILE_SIZE, girlBluePosition.y - 2 * TILE_SIZE + endOffsetProgression.y, 0, WHITE);
		}

		if (hugEnded) {

			logoColorIndex += deltaTime * 25;
			if (logoColorIndex >= 6)
				logoColorIndex -= 6;

			winAnim16Renderer.Paint(*TextureManager::Instance().GetTexture("WinTileSet"), { girlGreenPosition.x,girlGreenPosition.y - 5 * TILE_SIZE + endOffsetProgression.y}, { 10,13 }, { 2 * TILE_SIZE ,2 * TILE_SIZE }, 0, logoColors[(int)logoColorIndex]);
			winAnim16Renderer.Paint(*TextureManager::Instance().GetTexture("WinTileSet"), { girlGreenPosition.x,girlGreenPosition.y - 5 * TILE_SIZE + endOffsetProgression.y }, { 11,13 }, { 2 * TILE_SIZE ,2 * TILE_SIZE }, 0, WHITE);

			winAnim16Renderer.Paint(*TextureManager::Instance().GetTexture("WinTileSet"), { girlBluePosition.x - 2*TILE_SIZE ,girlBluePosition.y - 5 * TILE_SIZE + endOffsetProgression.y }, { 10,13 }, { 2 * TILE_SIZE ,2 * TILE_SIZE }, 0, logoColors[(int)logoColorIndex]);
			winAnim16Renderer.Paint(*TextureManager::Instance().GetTexture("WinTileSet"), { girlBluePosition.x - 2 * TILE_SIZE ,girlBluePosition.y - 5 * TILE_SIZE + endOffsetProgression.y }, { 11,13 }, { 2 * TILE_SIZE ,2 * TILE_SIZE }, 0, WHITE);

			winAnim64Renderer.Paint(*TextureManager::Instance().GetTexture("WinTileSet"), { (16*TILE_SIZE) - 4 * TILE_SIZE,momPosition.y - 17 * TILE_SIZE + endOffsetProgression.y }, { 0,4 }, { 8 * TILE_SIZE ,8 * TILE_SIZE }, 0, logoColors[(int)logoColorIndex]);
			winAnim64Renderer.Paint(*TextureManager::Instance().GetTexture("WinTileSet"), { (16 * TILE_SIZE) - 4* TILE_SIZE,momPosition.y - 17 * TILE_SIZE + endOffsetProgression.y }, {1,4 }, { 8 * TILE_SIZE ,8 * TILE_SIZE }, 0, WHITE);

			happyEndRender.Paint(*TextureManager::Instance().GetTexture("WinTileSet"), { girlGreenPosition.x -6 *TILE_SIZE,momPosition.y - 13 * TILE_SIZE + endOffsetProgression.y }, {0,7}, { 10* TILE_SIZE ,4 * TILE_SIZE }, 0, WHITE);
			happyEndRender.Paint(*TextureManager::Instance().GetTexture("WinTileSet"), { girlBluePosition.x - 5 * TILE_SIZE ,momPosition.y - 13 * TILE_SIZE + endOffsetProgression.y }, { 0,7 }, { 10 * TILE_SIZE ,4 * TILE_SIZE }, 0, WHITE);
		}
	}

	EnemyManager::Instance().Render();
	ParticleManager::Instance().Render();
	if (DebugMode) {
		LevelManager::Instance().Debug();
		ObjectsManager::Instance().Debug();
		BubbleManager::Instance().Debug();
		EnemyManager::Instance().Debug();
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

	if (state == Win) {
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
	int levelNumber = LevelManager::Instance().GetActualLevelIndex()*10;
	if (levelNumber > 9) {
		int num = levelNumber % 10;
		int numTile = FromNumberToTile(num);
		newRoundUI.ModifyTile(7, 0, numTile);
		levelNumber -= num;
		levelNumber /= 10;
		num = levelNumber % 10;
		numTile = FromNumberToTile(num);
		newRoundUI.ModifyTile(6, 0, numTile);
	}
	else {
		newRoundUI.ModifyTile(7, 0, FromNumberToTile(levelNumber));
		newRoundUI.ModifyTile(6, 0, 63);
	}
}

void GameController::ChangeLevelRecordUI(int level)
{
	int levelNumber =level;
	if (levelNumber > 9) {
		int num = levelNumber % 10;
		int numTile = FromNumberToTile(num);
		recordLevelUI.ModifyTile(9, 0, numTile-64);
		levelNumber -= num;
		levelNumber /= 10;
		num = levelNumber % 10;
		numTile = FromNumberToTile(num);
		recordLevelUI.ModifyTile(8, 0, numTile-64);
	}
	else {
		recordLevelUI.ModifyTile(9, 0, FromNumberToTile(levelNumber)-64);
		recordLevelUI.ModifyTile(8, 0, 63);
	}
}

void GameController::SaveGameData(int highScore, const char* name)
{
	string path = "Assets/SaveData/";
	path.append(name);
	FILE* file;
	file = fopen(path.c_str(), "w");
	fprintf(file, "%d", highScore);
	fclose(file);
}

void GameController::LoadGameData(int* highScore, const char* name)
{
	string path = "Assets/SaveData/";
	path.append(name);
	FILE* file;
	file = fopen(path.c_str(), "r");
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
