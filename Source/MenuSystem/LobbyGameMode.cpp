// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

		if (GEngine) 
		{
			GEngine->AddOnScreenDebugMessage(
				1,
				60.0f,
				FColor::Yellow,
				FString::Printf(TEXT("Players in game %d"), NumberOfPlayers)
				);
		

			// Get player name
			APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
			if (PlayerState) {
				
				GEngine->AddOnScreenDebugMessage(
					-1,
					60.0f,
					FColor::Cyan,
					FString::Printf(TEXT("Players %s has joined the game"), *PlayerState->GetPlayerName())
				);
			}
		}
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	// Get player name
	APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();
	if (PlayerState) {
		GEngine->AddOnScreenDebugMessage(
			-1,
			60.0f,
			FColor::Cyan,
			FString::Printf(TEXT("Players %s has left the game"), *PlayerState->GetPlayerName())
		);
	}


	int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
	GEngine->AddOnScreenDebugMessage(
		1,
		60.0f,
		FColor::Yellow,
		FString::Printf(TEXT("Players in game %d"), NumberOfPlayers - 1)
	);
	Super::Logout(Exiting);
}
