// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#include "Grid.h"
#include "Engine/World.h"
#include "Events/BaseEvent.h"
#include "ProjectOdimh.h"
#include "Entities/Game/Match3GameMode.h"
#include "Entities/Game/Tile.h"
#include "Entities/Player/Match3Controller.h"
#include "Entities/States/State.h"
#include "Components/TurnMovement.h"
#include "POdimhGameInstance.h"
#include "Events/GameEvent.h"
#include "Events/GridEvent.h"
#include "Sound/SoundCue.h"


// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    SelectedTile = nullptr;
    MyGridSize = 0.f;
    GridUnit = 0;
    GridLocation = FVector2D();
    TilesNeededForMatch = 3;
    bNoMatchingTiles = false;
    bGridFinishedFilling = false;
}

void AGrid::NotifySave(USaveGame* SaveData)
{
    if(UPOdimhSaveGame* Data = Cast<UPOdimhSaveGame>(SaveData))
    {
        // save the tile types
        for(auto* Tile : GetTileList())
        {
            // for each tile, assign types to save data
            Data->Board.AddTile(Tile->M_Type);
        }
    
        // save the score
        if(AMatch3GameMode* GameMode = Cast<AMatch3GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
        {
            Data->Board.GameScore = GameMode->GetCurrentScore();
        }
        TileList.Empty();
    }
}

const bool AGrid::NotifyLoad(USaveGame* LoadData)
{
    bool bSuccess = false;
    
    if(UPOdimhSaveGame* Data = Cast<UPOdimhSaveGame>(LoadData))
    {
        CopyTileDataFromBlueprint(); // copy to TileList
        if(ensure(TileList.Num() == Data->Board.GetNumberOfTiles()))
        {
            // retrieve the list of tile types from save data
            for(int32 Index = 0; Index != TileList.Num(); ++Index )
            {
                // for each tile, set type from save data
                const int32 Type = Data->Board.TileTypes[Index];
                TileList[Index]->SetTileType(Type);
                TileList[Index]->LoadTileSprite();
            }

            if(AMatch3GameMode* GameMode = Cast<AMatch3GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
            {
                GameMode->SetCurrentScore(Data->Board.GameScore);
                bSuccess = true;
            }
        }
        TileList.Empty();
    }
    return bSuccess;
}

void AGrid::InitTiles(FGridSpawningParameters Param)
{
    InitTiles(Param.bRandomTileType, Param.bLoadSprites);
}

const float AGrid::GetGridSize() const
{
    return MyGridSize;
}

const FVector2D& AGrid::GetGridLocation(const FVector& Location)
{
    // call the blueprint library function to retrieve the data
    SetGridLocationFromBlueprint(Location);
    
    return GridLocation;
}

const bool AGrid::HasFinishFilling() const
{
    return bGridFinishedFilling;
}

void AGrid::OnTileSpawned(AActor* Tile)
{
    if(ATile* SpawnedTile = Cast<ATile>(Tile))
    {
        // register the tile to the TArray of tiles in blueprint
        bool bFindEmptySpace = true;
        bool bStateChange = true;
        RegisterTileToGrid(SpawnedTile, bFindEmptySpace, bStateChange);
    }
}

const TArray<FTileData> AGrid::CountTileTypes()
{
    TArray<FTileData> GridData;
    
    for(auto* Tile: GetTileList())
    {
        if(Tile)
        {
            bool bDataTypeFound = false;
            
            for(FTileData& CurrData : GridData)
            {
                if(CurrData.Type == Tile->M_Type)
                {
                    CurrData.TotalNum++;
                    bDataTypeFound = true;
                    break;
                }
            }
            
            // create new data only if a certain type doesn't exist
            if(!bDataTypeFound)
            {
                FTileData NewData;
                NewData.Type = Tile->M_Type;
                NewData.TotalNum++;
                GridData.Add(NewData);
            }
        }
    }
    TileList.Empty();
    return GridData;
}

const int AGrid::GetNumOfOccurences(const int Type)
{
    int Count = 0;
    
    for(const FTileData& CurrTileData : CountTileTypes())
    {
        if(CurrTileData.Type == Type)
        {
            Count = CurrTileData.TotalNum;
            break;
        }
    }
    return Count;
}

const bool AGrid::MatchingTilesAvailable()
{
    for(int type = 0; type < NUMBER_OF_TILE_TYPES; type++ )
    {
        // TODO: note that function GetNumOfOccurences() is calling CountTileTypes() in a loop
        int TileCount = GetNumOfOccurences(type);
        
        // return true if there are available matches
        if(TileCount >= TilesNeededForMatch)
        {
            return true;
        }
    }
    
    return false;
}

void AGrid::OnTileSpawnedFromComponent(AActor* Tile, UActorComponent* Container)
{
	OnTileSpawned(Tile);
	
	// TODO: handle component
}

void AGrid::OnTileMatched(const int Type, const int NumTilesMatching, const int NumTilesNeeded)
{
    Cast<UPOdimhGameInstance>(GetGameInstance())->GlobalEvent->OnTileMatch.Broadcast(Type, NumTilesMatching, NumTilesNeeded);
}

void AGrid::ReleaseSelectedTile()
{
    if(SelectedTile)
        RegisterTileToGrid(SelectedTile, false, true);
}

void AGrid::SelectTile(ATile* NewSelection, UTurnMovement* MoveLimit)
{
    SelectedTile = NewSelection;
    
    // bound the tile from to its remaining moves
    if(MoveLimit)
    {

    }
}

ATile* AGrid::GetSelectedTile() const
{
    return SelectedTile;
}

const float AGrid::GetDistanceBetween(ATile* Tile, FVector2D OtherPosition)
{
    // determine the distance between its current position and its new position
    return FVector2D::Distance(FVector2D(Tile->GetActorLocation()), OtherPosition);
}

const float GetDistanceBetween(ATile* TileA, ATile* TileB)
{
    return FVector::Distance(TileA->GetActorLocation(), TileB->GetActorLocation());
}

const int32 AGrid::CalculateTileValue(const int NumOfMatchingTiles, const int TileValue, const int Multiplier) const
{
    const int TotalScore = NumOfMatchingTiles * TileValue * Multiplier;
    
    return TotalScore;
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();

    FGridSpawningParameters Param;
    Param.bRandomTileType = true; // TODO: find solution. redundant NotifyLoad() function redundantly loads tile types and sprites
    Param.bLoadSprites = true;

    InitTiles(Param);
    
    if(AMatch3GameMode* ActiveGameMode = Cast<AMatch3GameMode>(UGameplayStatics::GetGameMode(GetWorld())))
    {
        ActiveGameMode->SetGrid(this);
        
    }

    // keep a reference to the Match3Controller
    PlayerController = Cast<AMatch3Controller>(UGameplayStatics::GetPlayerController(GetWorld(), (int32)EPlayer::One));
    
    // update the gridsize that was set in blueprint
    SetGridSizeFromBlueprint();
    
    // TODO: need to test if magic number will scale properly if GridSize changes
    // TODO: remove once TileMovementBound have been implemented
    GridUnit = MyGridSize / 1.5f;
}

TArray<ATile*> AGrid::GetTileList()
{
    CopyTileDataFromBlueprint();
    return TileList;
}

void AGrid::RegisterTileToGrid_Implementation(ATile* Tile, const bool bLoopForEmpty, const bool bNotifyStateChange)
{
    if(bNotifyStateChange && HasFinishFilling())
        Cast<UPOdimhGameInstance>(GetGameInstance())->GlobalEvent->Create(NewObject<UGridStateChange>(this));

    SelectedTile = nullptr;
}

ATile* AGrid::SpawnTile(TSubclassOf<ATile> BlueprintClass, const FTransform& Transform, const int Type /* = -1 */)
{
    ATile* SpawnedTile = GetWorld()->SpawnActor<ATile>(BlueprintClass, Transform);
    
    // spawn random tile if tile type is -1
    if(SpawnedTile)
    {
        if(Type == -1)
        {
            int32 RandomInt = FMath::RandRange(0, NUMBER_OF_TILE_TYPES - 1);
            SpawnedTile->SetTileType(RandomInt);
        }
        else
        {
            SpawnedTile->SetTileType(Type);
        }
        // register grid
        
    }
    
    return SpawnedTile;
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
}

