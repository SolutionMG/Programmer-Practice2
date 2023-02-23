// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ChattingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API AChattingGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	/// 게임 시작 시 사용할 위젯 Subclass 변수
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "UMG Game" )
	TSubclassOf<UUserWidget> startingWidgetClass;

private:
	/// 채팅방에 있는 지 유무 flag 변수
	UPROPERTY( )
	bool m_isChattingRoom;

	/// 메인 위젯으로 사용할 변수
	UPROPERTY( )
	UUserWidget* CurrentWidget;

	/// 메인 팝업 위젯으로 사용할 변수
	UPROPERTY()
	UUserWidget* CurrentUI;
public:

	/// 메인 위젯 변경 시 호출할 함수
	UFUNCTION(BlueprintCallable )
	void ChangeMenuWidget( TSubclassOf<UUserWidget> NewWidgetClass);

	/// 메인 팝업 위젯 변경 시 호출할 함수
	UFUNCTION()
	UUserWidget* ChangeUIWidget( TSubclassOf<UUserWidget> NewWidgetClass );

	/// 메인 팝업 위젯을 생성할 시 호출할 함수
	UFUNCTION()
	UUserWidget* CreateUIWidget( TSubclassOf<UUserWidget> NewWidgetClass );

	/// Set
	UFUNCTION( BlueprintCallable )
	void SetisChattingRoom( const bool& isRoom );


	/// Get
	UFUNCTION( )
	const bool& GetisChattingRoom( );
	UFUNCTION( )
	UUserWidget* GetCurrentWidget( );

protected:
	
	virtual void BeginPlay( ) override;

	virtual void Tick( float DeletaSecond) override;


};
