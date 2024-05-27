#pragma once
#include "Entity.hpp"
#include "AudioManager.hpp"
#include "BubbleManager.hpp"
#include "ParticleManager.hpp"
#include "TilemapController.hpp"
#include "EnemyManager.hpp"
#include "PuntuationHolder.hpp"
#include "PointsUI.hpp"
#include "Player.hpp"

#define MAX_COINS  9

#include "IRendereable.h"
#include "IUpdateable.h"
#include "ITimeable.h"
class GameController : public IRendereable, public IUpdateable, public ITimeable
{
public:
	enum GameState
	{
		InitialScreen,
		InsertCoinScreen,
		TutorialScreen,

		CoinInsertedScreen,
		LoadingGameScreen,
		GameScreen,

		Results,
		GameOver, 
		Cover,
		Win
	};
	GameController();
	~GameController();
	void Update() override;
	void Render() override;
	void ChangeState(int stateIndex);
private:
	
	void UpdateUI();
	void UpdateGame();

	void RenderUIEarly();
	void RenderGameEarly();

	void RenderUILate();
	void RenderGameLate();

	void InsertCoin();
	void CheckInsertedCoinsSound();

	void ChangeNextLevelUI();
	void ChangeLevelRecordUI(int level);

	void SaveGameData(int highScore, const char* name);
	void LoadGameData(int* highScore, const char* name);

	int FromNumberToTile(int num);

	GameState state = InitialScreen;

	Player player1 =  Player(Player::Keys{ KEY_W,KEY_A,KEY_D,KEY_Q }, true, &player1Points);
	Player player2 =  Player(Player::Keys{ KEY_UP,KEY_LEFT,KEY_RIGHT,KEY_RIGHT_SHIFT }, false, &player2Points);

	int coinsInserted = 0;
	int coinsInsertedSound = 0;

	Color logoColors[6]{ Color{255,248,65,255}, Color{241,181,0,255}, Color{255,136,45,255}, Color{255,126,88,255}, Color{255,116,122,255}, Color{221,43,50,255} };
	float logoColorIndex = 0;

	Entity hurryModeSprite;
	AnimationRenderer hurryModeRenderer;
	float hurryModeYTilePosition = 15 * TILE_SIZE;
	float hurryModeMoveSpeed = 18*TILE_SIZE;
	float hurryModeTimer = 0;
	bool isHurryOnMode = false;


	float endLevelTimer = 0;
	bool levelEnded = false;

	float loadingShootTimer = 0;

	int currentLevelRecord;
	int maxPlayerLevel;
	
	bool resultsProgressionDone = false;
	float  resultsProgressionSpeed = 3 * TILE_SIZE;
	Vector2  resultsProgressionInitialPos = { 13 * TILE_SIZE,5 * TILE_SIZE };
	Vector2  resultsProgressionMaxPos = { 13 * TILE_SIZE,25 * TILE_SIZE };
	Vector2 greenResultProgressionPos;
	Vector2 greenResultProgressionTargetPos;
	Vector2 blueResultProgressionPos;
	Vector2 blueResultProgressionTargetPos;
	Vector2 recordResultProgressionPos;
	bool resultProgressionUIShow = true;
	float resultProgressionUIAnimationTimer = 0;
	AnimationRenderer greenResultFlagRenderer;
	AnimationRenderer blueResultFlagRenderer;
	float greenProgressBarLevelNumber = 0;
	float blueProgressBarLevelNumber = 0;
	Renderer textProgressLevelRender = Renderer({ 10,12 }, {0,0}, { 0,0 });


	Vector2 winAnimGround = { 0,27 * TILE_SIZE };
	Vector2 endOffsetProgression = { 0,0 };
	AnimationRenderer girlGreenBubbleRenderer;
	AnimationRenderer girlBlueBubbleRenderer;
	AnimationRenderer blueCoupleRenderer;
	AnimationRenderer greenCoupleRenderer;
	AnimationRenderer bigBobRenderer;
	AnimationRenderer curtainRenderer;
	Renderer happyEndRender = Renderer({80,32}, { 0,0 }, { 0,0 });
	float cryAniamtionTimer = 0;
	float girlBubbleExplodeTimer = 0;
	float bigBobExplodeTimer = 0;
	bool bigBobExploded = false;
	bool girlsSpawned = false;
	bool girlsPositioned = false;
	bool girlsExploded = false;
	bool spawnParents = false;
	bool playersPositioned = false;
	bool hugStarted = false;
	bool hugEnded = false;
	float winDelaysTimer=0;
	Vector2 curtainPosition = { 0,0 };

	Vector2 bigBobInitialPosition = {16 * TILE_SIZE,13 * TILE_SIZE };
	Vector2 bigBobPosition;
	Vector2 girlGreenBubblePosition = {6.5* TILE_SIZE,7.5* TILE_SIZE };
	Vector2 girlBlueBubblePosition = {25 * TILE_SIZE,7 * TILE_SIZE };

	Vector2 girlGreenInitialPosition = {7 * TILE_SIZE,8 * TILE_SIZE };
	Vector2 girlGreenPosition = { 0,0};
	Vector2 girlBlueInitialPosition = { 25 * TILE_SIZE,8 * TILE_SIZE };
	Vector2 girlBluePosition = { 0,0 };

	Vector2 momPosition = {0,0 };
	Vector2 momInitialPosition = {14 * TILE_SIZE,24 * TILE_SIZE };
	Vector2 dadPosition = {0,0 };
	Vector2 dadInitialPosition = {18 * TILE_SIZE,24 * TILE_SIZE };

	Renderer winAnim32Renderer = Renderer({ 32,32 }, { 0,0 }, { 0,0 });
	Renderer winAnim16Renderer = Renderer({ 16,16 }, { 0,0 }, { 0,0 });
	Renderer winAnim64Renderer = Renderer({ 64,64 }, { 0,0 }, { 0,0 });


	TilemapController topUI = TilemapController("Assets/UI/UI.json", 64, Vector2{ GAME_TILE_WIDTH,2 });
	TilemapController initialScreen = TilemapController("Assets/UI/InitialScreen.json", 64, Vector2{ GAME_TILE_WIDTH,GAME_TILE_HEIGHT });
	TilemapController insertCoinScreen = TilemapController("Assets/UI/InsertCoinScreen.json", 64, Vector2{ GAME_TILE_WIDTH,GAME_TILE_HEIGHT });
	TilemapController coinInsertedScreen = TilemapController("Assets/UI/CoinInsertedScreen.json", 64, Vector2{ GAME_TILE_WIDTH,GAME_TILE_HEIGHT });
	TilemapController loadingGameScreen = TilemapController("Assets/UI/LoadingGameScreen.json", 64, Vector2{ GAME_TILE_WIDTH,GAME_TILE_HEIGHT });
	TilemapController controlsScreen = TilemapController("Assets/UI/ControlsUI.json", 64, Vector2{ GAME_TILE_WIDTH,GAME_TILE_HEIGHT });
	TilemapController gameOverScreen = TilemapController("Assets/UI/GameOverScreen.json", 64, Vector2{ GAME_TILE_WIDTH,GAME_TILE_HEIGHT });

	TilemapController newRoundUI = TilemapController("Assets/UI/NewRoundUI.json", 64, Vector2{ 8,3 });


	TilemapController lifesHUD = TilemapController(nullptr, 64, Vector2{ GAME_TILE_WIDTH,1 });

	TilemapController resultScreen = TilemapController("Assets/UI/ResultsScreen.json", 32, Vector2{ GAME_TILE_WIDTH,GAME_TILE_HEIGHT });
	TilemapController resultScreenUI = TilemapController("Assets/UI/ResultsScreenUI.json", 64, Vector2{ GAME_TILE_WIDTH,GAME_TILE_HEIGHT });
	TilemapController recordLevelUI = TilemapController("Assets/UI/RecordLevelUI.json", 64, Vector2{ 11,1 });


	TilemapController player1PointsMap = TilemapController(nullptr,64 ,Vector2{ 8,1,});
	PuntuationHolder player1Points = PuntuationHolder(0, 1);
	PointsUI player1PointsUpdater = PointsUI(&player1Points, &player1PointsMap);

	TilemapController player2PointsMap = TilemapController(nullptr,64 ,Vector2{ 8,1,});
	PuntuationHolder player2Points = PuntuationHolder(0, 1);
	PointsUI  player2PointsUpdater = PointsUI(&player2Points, &player2PointsMap);

	TilemapController highScorePointsMap = TilemapController(nullptr,64 ,Vector2{ 8,1,});
	PuntuationHolder highScorePoints = PuntuationHolder(0, 1);
	PointsUI  highScorePointsUpdater = PointsUI(&highScorePoints, &highScorePointsMap);


	bool DebugMode = false;


	/////CONSTANTS
	#define INIT_SCREEN_TIME 8
	#define INSERT_COIN_TIME 1
	#define TUTORIAL_TIME 15
	#define LOADING_GAME_TIME 8
	#define LOADING_GAME_SHOOT_TIME 0.2
	#define RESULTS_TIME 6
	#define RESULTS_TIME_UI_ANIMATIONS 0.5
	#define GAME_OVER_TIME 3

	#define MAX_COINS 9

	////Cover
	#define COVER_SCREEN_TIME 3

	////Win
	#define CRY_ANIMATION 2.7
	#define BUBBLE_EXPLODE_ANIMATION 1
	#define BIG_BOB_EXPLODE_ANIMATION 1
	#define WIN_ANIMATION_DELAYS 1
	#define HUG_ANIMATION 0.5

	/// Game
	#define START_GAME_DELAY 1.5f
	#define HURRY_MODE_TIME_HOLD 2
	#define HURRY_MODE_TIME_WAIT 30
	#define END_LEVEL_TIME_WAIT 4

};
