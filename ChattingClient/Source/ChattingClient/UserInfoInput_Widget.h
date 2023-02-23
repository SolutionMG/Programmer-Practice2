// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserInfoInput_Widget.generated.h"

class UButton;
class UEditableTextBox;
/**
 * 
 */
UCLASS()
class CHATTINGCLIENT_API UUserInfoInput_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/// ���� ����� ����
	UPROPERTY( meta = ( BindWidget ) )
	UButton* QuitButton;

	/// ���� ���� ��û�� ���� �̸� ����� ����
	UPROPERTY( meta = ( BindWidget ) )
	UEditableTextBox* Name_Textblock;

public:

	///�ش� Widget ������ ���� �Լ�
	virtual void NativeConstruct() override;

private:
	
	UFUNCTION()
	void QuitUI();

	/// ���� ���� ��û ������
	UFUNCTION()
	void SendChatting( const FText& Text, ETextCommit::Type CommitMethod );
};
