// Copyright 2017-2018 Vanny Sou. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClassInterface/DataSaveInterface.h"
#include "Grid.generated.h"

class ATile;
class AGridPlayerController;
class USpawnContainer;
class UActionTurnBasedComponent;
class USoundCue;

USTRUCT()
struct FTileData
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY()
    int Type = -1;
    
    UPROPERTY()
    int TotalNum = 0;
};

USTRUCT()
struct FGridSpawningParameters
{
    GENERATED_USTRUCT_BODY()
    
    bool bRandomTileType;
    bool bLoadSprites;
    
    FGridSpawningParameters()
    {
        bRandomTileType = true;
        bLoadSprites = true;
    }
};
/**
 * The grid contain information that determines the spawning position of each Tile objects, and events that
 * trigger when certain conditions are met.
 */
UCLASS()
class PROJECTODIMH_API AGrid : public AActor, public IDataSaveInterface
{
	GENERATED_BODY()
	
public:
    friend class UGridEvent;
    
	// Sets default values for this actor's properties
	AGrid();
    
    // DataSave interface
    virtual void NotifySave(USaveGame* Data) override;
    virtual const bool NotifyLoad(USaveGame* Data) override;
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    void InitTiles(FGridSpawningParameters Param);
    
    /** This will get the return MyGridSize that was retrieved from blueprint */
    UFUNCTION()
    const float GetGridSize() const;
    
    /** Returns the grid coordinates based on an FVector */
    const FVector2D& GetGridLocation(const FVector& Location);
    const FVector2D& GetGridLocation(ATile* Tile);
    
    /** Collect data on the number of type occurences that is currently on the grid */
    const TArray<FTileData> CountTileTypes();
    
    /** Find the number of occurences based on a tile type */
    UFUNCTION(BlueprintCallable)
    const int GetNumOfOccurences(const int Type);
    
    /** Check the grid if there are available matching tiles */
    UFUNCTION(BlueprintCallable)
    const bool MatchingTilesAvailable();
    
    /** Register its new position and release the selected Tile */
    void ReleasePickedTile();
    
    /** Set the NewSelection as the currently selected Tile object and limits its movement by tile ability */
    void PickTile(ATile* NewSelection, UActionTurnBasedComponent* MoveLimit);
    
    /** Get the Tile object that is currently being selected on the Grid */
    ATile* GetPickedTile() const;
    
    /** Determines the distance between a Tile object and another location */
    const float GetDistanceBetween(ATile* Tile, FVector2D OtherPosition);
    
    /** Get the distance between two Tile objects. */
    const float GetDistanceBetween(ATile* TileA, ATile* TileB);
    
    /** Score is calculated based on number of tiles, the tile value and a multiplier */
    UFUNCTION(BlueprintCallable)
    const int32 CalculateTileValue(const int NumOfMatchingTiles, const int TileValue, const int Multiplier) const;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USoundCue* StateChangeCue;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USoundCue* TileMatchCue;
    
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    /** Set up the tiles on the grid by calling blueprint function Spawn Initial Tiles */
    UFUNCTION(BlueprintImplementableEvent)
    void InitTiles(const bool bRandomTileType, const bool bLoadSprites);
    
    /** Get the value of GridSize that was assigned in blueprint and assign it to this object's member data MyGridSize */
    UFUNCTION(BlueprintImplementableEvent)
    void SetGridSizeFromBlueprint();
    
    /** Blueprint function that stores all the tiles that are currently in play to the member data, TileList */
    UFUNCTION(BlueprintImplementableEvent)
    void CopyTileDataFromBlueprint();
    
    /** Return TileList after tile data has been copied from blueprint */
    TArray<ATile*> GetTileList();
    
    /** Spawn an actor directly to grid. Only possible if that grid's space is empty. Can notify GameMode of a grid state change after spawning. */
    UFUNCTION(BlueprintNativeEvent)
    void SpawnTileToGrid(ATile* Tile, const bool bNotifyStateChange);
    
    /** Call the blueprint library function GetGridFromLocation to get the grid coordinates by using a Vector location
     * and set it to this object's member data - GridLocation */
    UFUNCTION(BlueprintImplementableEvent)
    void SetGridLocationFromBlueprint(const FVector& Location);
    
    /** Spawn a tile on the grid based on a transform and tile type. Tile type of -1 is a random spawn. */
    UFUNCTION(BlueprintCallable)
    ATile* SpawnTile(TSubclassOf<ATile> Class, const FTransform& Transform, const int Type = -1);
    
    /** This is the grid size that was retrieved from blueprint */
    UPROPERTY(BlueprintReadWrite)
    float MyGridSize;
    
    /** The arrays of gems that was retrieved from blueprint */
    UPROPERTY(BlueprintReadWrite)
    TArray<ATile*> TileList;
    
    /** The grid coordinates that was last retrieved from blueprint */
    UPROPERTY(BlueprintReadWrite)
    FVector2D GridLocation;
    
    /** The distance it takes for a tile to consume a movement */
    UPROPERTY()
    float GridUnit;
    
    /** Tracks a list of tile types to spawn next */
    UPROPERTY(BlueprintReadWrite)
    TArray<int> NextTileToSpawn;
    
    /** The required number of consecutive row or column for the game to consider it a successful tile match */
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int TilesNeededForMatch;
    
private:
    /** A state in which there are no matching tiles (2 or less occurences) available */
    uint16 bNoMatchingTiles : 1;
    
    /** The currently selected Tile object on the grid */
    UPROPERTY()
    ATile* PickedTile;

    /** The reference to the player controller */
    UPROPERTY()
    AGridPlayerController* PlayerController;
    
    
    

};
