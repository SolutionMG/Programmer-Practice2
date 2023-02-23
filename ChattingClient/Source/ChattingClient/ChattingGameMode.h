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
	/// ���� ���� �� ����� ���� Subclass ����
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "UMG Game" )
	TSubclassOf<UUserWidget> startingWidgetClass;

private:
	/// ä�ù濡 �ִ� �� ���� flag ����
	UPROPERTY( )
	bool m_isChattingRoom;

	/// ���� �������� ����� ����
	UPROPERTY( )
	UUserWidget* CurrentWidget;

	/// ���� �˾� �������� ����� ����
	UPROPERTY()
	UUserWidget* CurrentUI;
public:

	/// ���� ���� ���� �� ȣ���� �Լ�
	UFUNCTION(BlueprintCallable )
	void ChangeMenuWidget( TSubclassOf<UUserWidget> NewWidgetClass);

	/// ���� �˾� ���� ���� �� ȣ���� �Լ�
	UFUNCTION()
	UUserWidget* ChangeUIWidget( TSubclassOf<UUserWidget> NewWidgetClass );

	/// ���� �˾� ������ ������ �� ȣ���� �Լ�
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
