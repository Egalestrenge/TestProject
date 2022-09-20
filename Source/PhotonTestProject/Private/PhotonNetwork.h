// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LoadBalancing-cpp/inc/Client.h"
#include "Common-cpp/inc/Common.h"
#include "PhotonNetwork.generated.h"

using namespace ExitGames::LoadBalancing;
using namespace ExitGames::Common;


class PhotonGeneralFunctionality {
public:
	//Put type
	static void PutUnrealPropertyToHashtable(Hashtable& PropertiesHashtable, bool NewProperty, JString NewPropertyKey);
	static void PutUnrealPropertyToHashtable(Hashtable& PropertiesHashtable, FVector NewProperty, JString NewPropertyKey);
	static void PutUnrealPropertyToHashtable(Hashtable& PropertiesHashtable, FLinearColor NewProperty, JString NewPropertyKey);
	static void PutUnrealPropertyToHashtable(Hashtable& PropertiesHashtable, float NewProperty, JString NewPropertyKey);
	static void PutUnrealPropertyToHashtable(Hashtable& PropertiesHashtable, int NewProperty, JString NewPropertyKey);
	static void PutUnrealPropertyToHashtable(Hashtable& PropertiesHashtable, FString NewProperty, JString NewPropertyKey);
	//Put Tarray of type
	static void PutUnrealPropertyToHashtable(Hashtable& PropertiesHashtable, TArray<FString> NewProperty, JString NewPropertyKey);

	//Get type
	static bool GetUnrealPropertyFromHashtable(Hashtable& PropertiesHashtable, bool& Property, JString PropertyKey);
	static bool GetUnrealPropertyFromHashtable(Hashtable& PropertiesHashtable, FVector& Property, JString PropertyKey);
	static bool GetUnrealPropertyFromHashtable(Hashtable& PropertiesHashtable, FLinearColor& Property, JString PropertyKey);
	static bool GetUnrealPropertyFromHashtable(Hashtable& PropertiesHashtable, float& Property, JString PropertyKey);
	static bool GetUnrealPropertyFromHashtable(Hashtable& PropertiesHashtable, int& Property, JString PropertyKey);
	static bool GetUnrealPropertyFromHashtable(Hashtable& PropertiesHashtable, FString& Property, JString PropertyKey);
	//Get array of type
	static bool GetUnrealPropertyFromHashtable(Hashtable& PropertiesHashtable, TArray<FString>& Property, int ArraySize, JString PropertyKey);

	//Get Map
	static bool GetMapFromHashtable(Hashtable& PropertiesHashtable, TMap<FString, bool>& PropertiesMap);
	static bool GetMapFromHashtable(Hashtable& PropertiesHashtable, TMap<FString, int>& PropertiesMap);
	static bool GetMapFromHashtable(Hashtable& PropertiesHashtable, TMap<FString, float>& PropertiesMap);
	static bool GetMapFromHashtable(Hashtable& PropertiesHashtable, TMap<FString, FVector>& PropertiesMap);
	static bool GetMapFromHashtable(Hashtable& PropertiesHashtable, TMap<FString, FLinearColor>& PropertiesMap);
	static bool GetMapFromHashtable(Hashtable& PropertiesHashtable, TMap<FString, FString>& PropertiesMap);
	static bool GetMapFromHashtable(Hashtable& PropertiesHashtable, TMap<FString, TArray<FString>>& PropertiesMap, bool IsArraySizeInHash = true, TArray<int> ArraySizes = TArray<int>());

};

//LISTENER FOR THE LOBBY
class PhotonNetworkLobbyListener : public ExitGames::LoadBalancing::Listener
{
public:
	PhotonNetworkLobbyListener(UPhotonNetwork* Network);
	~PhotonNetworkLobbyListener(void);

private:
	//From Common::BaseListener

	// receive and print out debug out here
	virtual void debugReturn(int debugLevel, const ExitGames::Common::JString& string);

	//From LoadBalancing::LoadBalancingListener

	// implement your error-handling here
	virtual void connectionErrorReturn(int errorCode);
	virtual void clientErrorReturn(int errorCode);
	virtual void warningReturn(int warningCode);
	virtual void serverErrorReturn(int errorCode);

	// events, triggered by certain operations of all players in the same room
	virtual void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player);
	virtual void leaveRoomEventAction(int playerNr, bool isInactive);
	virtual void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent);

	// callbacks for operations on PhotonLoadBalancing server
	virtual void connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& region, const ExitGames::Common::JString& cluster);
	virtual void disconnectReturn(void);
	virtual void createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString);
	virtual void gotQueuedReturn(void);
	virtual void joinLobbyReturn(void);
	virtual void leaveLobbyReturn(void);
	virtual void onRoomListUpdate(void);
	virtual void onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats);
	virtual void onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats);
	virtual void onRoomPropertiesChange(const ExitGames::Common::Hashtable& changes);

	UPhotonNetwork* PhotonNetwork;
};

//LISTENER FOR THE PLAYER
class PhotonNetworkPlayerListener : public ExitGames::LoadBalancing::Listener
{
public:
	PhotonNetworkPlayerListener(UPhotonNetwork* Network);
	~PhotonNetworkPlayerListener(void);	

private:
	//From Common::BaseListener

	// receive and print out debug out here
	virtual void debugReturn(int debugLevel, const ExitGames::Common::JString& string);

	//From LoadBalancing::LoadBalancingListener

	// implement your error-handling here
	virtual void connectionErrorReturn(int errorCode);
	virtual void clientErrorReturn(int errorCode);
	virtual void warningReturn(int warningCode);
	virtual void serverErrorReturn(int errorCode);

	// events, triggered by certain operations of all players in the same room
	virtual void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player);
	virtual void leaveRoomEventAction(int playerNr, bool isInactive);
	virtual void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent);

	// callbacks for operations on PhotonLoadBalancing server
	virtual void connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& region, const ExitGames::Common::JString& cluster);
	virtual void disconnectReturn(void);
	virtual void createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString);
	virtual void gotQueuedReturn(void);
	virtual void joinLobbyReturn(void);
	virtual void leaveLobbyReturn(void);
	virtual void onRoomListUpdate(void);
	virtual void onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats);
	virtual void onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats);
	virtual void onRoomPropertiesChange(const ExitGames::Common::Hashtable& changes);
	virtual void onPlayerPropertiesChange(int PlayerNr, const ExitGames::Common::Hashtable& changes);

	UPhotonNetwork* PhotonNetwork;
};

//STRUCTS
USTRUCT(BlueprintType)
struct FRoom {

	GENERATED_BODY()	

	UPROPERTY(BlueprintReadWrite)
	FString RoomName;
	UPROPERTY(BlueprintReadWrite)
	FString LevelName;
	UPROPERTY(BlueprintReadWrite)
	int PlayerCount;
	UPROPERTY(BlueprintReadWrite)
	int MaxPlayers;
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> PlayerList;
	UPROPERTY(BlueprintReadWrite)
	bool bIsOpen;	

	FRoom() {
		RoomName = "";
		PlayerCount = 0;
		LevelName = "";
		MaxPlayers = 0;
		PlayerList = TArray<FString>();
		bIsOpen = true;
	}

	FRoom(Room* PhotonRoom) {
		UTF8String RoomNameUTF8String = PhotonRoom->getName().UTF8Representation();
		RoomName = FString(RoomNameUTF8String.cstr());

		UTF8String LevelNameUTF8String = ValueObject<JString>(PhotonRoom->getCustomProperties().getValue("LevelName")).getDataCopy().UTF8Representation();
		LevelName = FString(LevelNameUTF8String.cstr());

		PlayerCount = PhotonRoom->getPlayerCount();
		MaxPlayers = PhotonRoom->getMaxPlayers();

		PlayerList = TArray<FString>();
		const JString* PlayerListC = ValueObject<JString*>(PhotonRoom->getCustomProperties().getValue("PlayerList")).getDataCopy();
		int PlayerListLength = ValueObject<int>(PhotonRoom->getCustomProperties().getValue("PlayerListLength")).getDataCopy();
		//JString* PlayerListC = (JString*)PhotonRoom->getCustomProperties().getValue("PlayerList");//->toString();
		//JString* PlayerListC = &PlayerListString;
		JVector<JString> JPlayerList = JVector<JString>(PlayerListC, PlayerListLength);
		for (int i = 0; i < (int)JPlayerList.getSize(); i++) {
			UTF8String PlayerNameUTF8String = JPlayerList[i].UTF8Representation();
			FString PlayerName = FString(PlayerNameUTF8String.cstr());
			PlayerList.Add(PlayerName);
		}
		//JVector<JString> JPlayerList = JVector<JString>();
		/*for (int i = 0; i < (int)PhotonRoom->getPlayerCount(); i++) {

			FString PlayerName = PlayerListString;
			PlayerList.Add(PlayerName);
		}*/

		bIsOpen = PhotonRoom->getIsOpen();
	}
};

USTRUCT(BlueprintType)
struct FGeneralEventParams {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int GeneralEventCode;
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, bool> EventBoolParams;
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, int> EventIntParams;
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, float> EventFloatParams;
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FVector> EventVectorParams;
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FLinearColor> EventColorParams;
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FString> EventStringParams;

	FGeneralEventParams() {
		GeneralEventCode = 0;
		EventBoolParams = TMap<FString, bool>();
		EventIntParams = TMap<FString, int>();
		EventFloatParams = TMap<FString, float>();
		EventVectorParams = TMap<FString, FVector>();
		EventColorParams = TMap<FString, FLinearColor>();
		EventStringParams = TMap<FString, FString>();
	}

	FGeneralEventParams(Hashtable EventProperties) {
		GeneralEventCode = ValueObject<int>(EventProperties.getValue(JString("GeneralEventCode"))).getDataCopy();

		EventBoolParams = TMap<FString, bool>();
		PhotonGeneralFunctionality::GetMapFromHashtable(EventProperties, EventBoolParams);
		
		EventIntParams = TMap<FString, int>();
		PhotonGeneralFunctionality::GetMapFromHashtable(EventProperties, EventIntParams);

		EventFloatParams = TMap<FString, float>();
		PhotonGeneralFunctionality::GetMapFromHashtable(EventProperties, EventFloatParams);

		EventVectorParams = TMap<FString, FVector>();
		PhotonGeneralFunctionality::GetMapFromHashtable(EventProperties, EventVectorParams);

		EventColorParams = TMap<FString, FLinearColor>();
		PhotonGeneralFunctionality::GetMapFromHashtable(EventProperties, EventColorParams);

		EventStringParams = TMap<FString, FString>();
		PhotonGeneralFunctionality::GetMapFromHashtable(EventProperties, EventStringParams);

	}
};

//ENUMS
enum PlayerEventCodes : nByte {
	PlayerPing = 0,
	RoomMasterChangedLevel = 1,
	GeneralEvent
};

//CLASSES

UCLASS(BlueprintType)
class UPhotonNetwork : public UObject
{
	GENERATED_BODY()

public:	

	//DELEGATES FOR UE EVENTS
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPhotonConnectionSuccessDelegate);	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FPhotonConnectionSuccessDelegate ConnectionSuccess;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateRoomDelegate, int, LocalPlayerNr, bool, RoomCreated);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FCreateRoomDelegate RoomCreated;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRoomPropertiesChangeDelegate);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FRoomPropertiesChangeDelegate RoomPropertiesChanged;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FJoinRoomDelegate, int, LocalPlayerNr);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FJoinRoomDelegate RoomJoined;	

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerJoinedCurrentRoomDelegate, int, PlayerNr);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FPlayerJoinedCurrentRoomDelegate PlayerJoinedCurrentRoom;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLeaveRoomDelegate);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FLeaveRoomDelegate RoomLeft;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerLeftCurrentRoomDelegate, int, PlayerNr);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FPlayerLeftCurrentRoomDelegate PlayerLeftCurrentRoom;	

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FPlayerPingEventDelegate, int, PlayerNr, FVector, SpawnTransformLocation, float, Size, float, Thickness, FLinearColor, Color);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FPlayerPingEventDelegate PlayerPingEvent;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRoomMasterChangedLevel, FString, DestinationLevel);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FRoomMasterChangedLevel RoomMasterChangedLevel;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGeneralEventReceived, FGeneralEventParams, GeneralEventParams);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FGeneralEventReceived GeneralEventReceived;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FURLReceived, int, PlayerNr, FString, URLString);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FURLReceived URLReceived;


	UFUNCTION(BlueprintCallable)
	void SetNetworkParams(FString AppIdStr, FString AppVerStr);

	UFUNCTION(BlueprintCallable)
	void Connect();

	UFUNCTION(BlueprintCallable)
	void UpdateConnection();

	UFUNCTION(BlueprintCallable)
	TArray<FRoom> GetRoomList();

	//Creates and joins a new room (if the room already exists, it will only join the room)
	UFUNCTION(BlueprintCallable)
	void CreateRoom(FRoom Room, bool bIsVisible = true);

	//Joins a room
	UFUNCTION(BlueprintCallable)
	void JoinRoom(FString RoomName);

	//Joins a room
	UFUNCTION(BlueprintCallable)
	void LeaveRoom();

	//Gets the current room info
	UFUNCTION(BlueprintCallable)
	FRoom GetCurrentRoomInfo();

	//Sets the player name
	UFUNCTION(BlueprintCallable)
	void SetPlayerName(FString PlayerName);

	//Gets the local photon player
	UFUNCTION(BlueprintCallable)
	UPhotonPlayer* GetLocalPhotonPlayer();

	//Gets the local photon player
	UFUNCTION(BlueprintCallable)
	UPhotonPlayer* GetRoomPhotonPlayer(int PlayerNr);

	UFUNCTION(BlueprintCallable)
	TArray<UPhotonPlayer*> GetRoomPhotonPlayers();

	//Network
	ExitGames::LoadBalancing::Client* LobbyClient;
	PhotonNetworkLobbyListener* LobbyListener;

	//Player
	ExitGames::LoadBalancing::Client* PlayerClient;
	PhotonNetworkPlayerListener* PlayerListener;

	//Rooms
	JVector<Room*> RoomList;
	

private:

	JString AppID;
	JString AppVer;

	//void PostEditChangeProperty(struct FPropertyChangedEvent& e);	
	
};

UCLASS(BlueprintType)
class UPhotonPlayer : public UObject
{
	GENERATED_BODY()

public:

	//// INITIALIZATION ////

	UFUNCTION(BlueprintCallable)
		void InitializePhotonPlayer(bool _IsLocal, FString _Name, FString _Id, int _Number, UPhotonNetwork* _PhotonNetwork, bool _RoomMaster, bool _IsInRoom) {
		this->bIsLocal = _IsLocal;
		this->Name = _Name;
		this->Id = _Id;
		this->Number = _Number;
		this->PhotonNetwork = _PhotonNetwork;
		this->bRoomMaster = _RoomMaster;
		this->bIsInRoom = _IsInRoom;
	}

	void InitializePhotonPlayer(Player* Player, bool _IsLocal, UPhotonNetwork* _PhotonNetwork, bool _RoomMaster, bool _IsInRoom) {
		this->bIsLocal = _IsLocal;

		UTF8String NameUTF8String = Player->getName().UTF8Representation();
		this->Name = FString(NameUTF8String.cstr());

		UTF8String IDUTF8String = Player->getUserID().UTF8Representation();
		this->Id = FString(IDUTF8String.cstr());

		this->Number = Player->getNumber();
		this->PhotonNetwork = _PhotonNetwork;
		this->bRoomMaster = _RoomMaster;
		this->bIsInRoom = _IsInRoom;

	}

	UFUNCTION(BlueprintCallable)
		bool GetIsLocal() {
		return this->bIsLocal;
	}
	UFUNCTION(BlueprintCallable)
		void SetIsLocal(bool _bIsLocal) {
		this->bIsLocal = _bIsLocal;		
	}

	UFUNCTION(BlueprintCallable)
		FString GetName() {
		return this->Name;
	}
	UFUNCTION(BlueprintCallable)
		void SetName(FString _Name) {
		this->Name = _Name;
	}

	UFUNCTION(BlueprintCallable)
		FString GetId() {
		return this->Id;
	}
	UFUNCTION(BlueprintCallable)
		void SetId(FString _Id) {
		this->Id = _Id;
	}

	UFUNCTION(BlueprintCallable)
		int GetNumber() {
		return this->Number;
	}
	UFUNCTION(BlueprintCallable)
		void SetNumber(int _Number) {
		this->Number = _Number;
	}

	UFUNCTION(BlueprintCallable)
		UPhotonNetwork* GetPhotonNetwork() {
		return this->PhotonNetwork;
	}
	UFUNCTION(BlueprintCallable)
		void SetPhotonNetwork(UPhotonNetwork* _PhotonNetwork) {
		this->PhotonNetwork = _PhotonNetwork;
	}

	UFUNCTION(BlueprintCallable)
		bool GetIsRoomMaster() {
		return this->bRoomMaster;
	}
	UFUNCTION(BlueprintCallable)
		void SetIsRoomMaster(bool _IsRoomMaster) {
		this->bRoomMaster = _IsRoomMaster;
	}

	UFUNCTION(BlueprintCallable)
		bool GetIsInRoom() {
		return this->bIsInRoom;
	}
	UFUNCTION(BlueprintCallable)
		void SetIsInRoom(bool _IsInRoom) {
		this->bIsInRoom = _IsInRoom;
	}

	//// ROOM PROPERTIES ////

	//Get a vector property of the currently joined room
	UFUNCTION(BlueprintCallable)
		FVector GetRoomVectorProperty(FString PropertyKey);
	//Set a vector property of the currently joined room
	UFUNCTION(BlueprintCallable)
		void SetRoomVectorProperty(FString PropertyKey, FVector PropertyValue);

	//Get a float property of the currently joined room
	UFUNCTION(BlueprintCallable)
		float GetRoomFloatProperty(FString PropertyKey);
	//Set a float property of the currently joined room
	UFUNCTION(BlueprintCallable)
		void SetRoomFloatProperty(FString PropertyKey, float PropertyValue);

	//Get an int property of the currently joined room
	UFUNCTION(BlueprintCallable)
		int GetRoomIntProperty(FString PropertyKey);
	//Set an int property of the currently joined room
	UFUNCTION(BlueprintCallable)
		void SetRoomIntProperty(FString PropertyKey, int PropertyValue);

	//Get an bool property of the currently joined room
	UFUNCTION(BlueprintCallable)
		bool GetRoomBoolProperty(FString PropertyKey);
	//Set an bool property of the currently joined room
	UFUNCTION(BlueprintCallable)
		void SetRoomBoolProperty(FString PropertyKey, bool PropertyValue);

	//Get an FString property of the currently joined room
	UFUNCTION(BlueprintCallable)
		FString GetRoomStringProperty(FString PropertyKey);
	//Set an FString property of the currently joined room
	UFUNCTION(BlueprintCallable)
		void SetRoomStringProperty(FString PropertyKey, FString PropertyValue);

	//Get an TArray<FString> property of the currently joined room. It will look for the size in the Room Properites given the Array Size Key, or you can give the Array Size directly.
	UFUNCTION(BlueprintCallable)
		TArray<FString> GetRoomStringArrayProperty(FString PropertyKey, FString ArraySizeKey, int ArraySize);
	//Set an TArray<FString> property of the currently joined room
	UFUNCTION(BlueprintCallable)
		void SetRoomStringArrayProperty(FString PropertyKey, TArray<FString> PropertyValue);

	
	//// PLAYER PROPERTIES ////

	//Get a vector property of this player from the Photon network, if the local player is in the same photon room as this player
	UFUNCTION(BlueprintCallable)
		FVector GetVectorProperty(FString PropertyKey);
	//Set a vector property of this player from the Photon network. NOTE: This function must be called from the local player!
	UFUNCTION(BlueprintCallable)
		void SetVectorProperty(FString PropertyKey, FVector PropertyValue);

	//Get a float property of this player from the Photon network, if the local player is in the same photon room as this player
	UFUNCTION(BlueprintCallable)
		float GetFloatProperty(FString PropertyKey);
	//Set a float property of this player from the Photon network. NOTE: This function must be called from the local player!
	UFUNCTION(BlueprintCallable)
		void SetFloatProperty(FString PropertyKey, float PropertyValue);

	//Get an int property of this player from the Photon network, if the local player is in the same photon room as this player
	UFUNCTION(BlueprintCallable)
		int GetIntProperty(FString PropertyKey);
	//Set an int property of this player from the Photon network. NOTE: This function must be called from the local player!
	UFUNCTION(BlueprintCallable)
		void SetIntProperty(FString PropertyKey, int PropertyValue);

	//Get an bool property of this player from the Photon network, if the local player is in the same photon room as this player
	UFUNCTION(BlueprintCallable)
		bool GetBoolProperty(FString PropertyKey);
	//Set an bool property of this player from the Photon network. NOTE: This function must be called from the local player!
	UFUNCTION(BlueprintCallable)
		void SetBoolProperty(FString PropertyKey, bool PropertyValue);

	//Get an FString property of this player from the Photon network, if the local player is in the same photon room as this player
	UFUNCTION(BlueprintCallable)
		FString GetStringProperty(FString PropertyKey);
	//Set an FString property of this player from the Photon network. NOTE: This function must be called from the local player!
	UFUNCTION(BlueprintCallable)
		void SetStringProperty(FString PropertyKey, FString PropertyValue);

	//Get an TArray<FString> property of this player from the Photon network, if the local player is in the same photon room as this player. It will look for the size in the Room Properites given the Array Size Key, or you can give the Array Size directly.
	UFUNCTION(BlueprintCallable)
		TArray<FString> GetStringArrayProperty(FString PropertyKey, FString ArraySizeKey, int ArraySize);
	//Set an TArray<FString> property of this player from the Photon network. NOTE: This function must be called from the local player!
	UFUNCTION(BlueprintCallable)
		void SetStringArrayProperty(FString PropertyKey, TArray<FString> PropertyValue);

	//// EVENTS ////

	UFUNCTION(BlueprintCallable)
		void SpawnPingInPhoton(FVector SpawnTransformLocation, float Size, float Thickness, FLinearColor Color);

	UFUNCTION(BlueprintCallable)
		void RoomMasterChangedLevelInPhoton(FString DestinationLevel);

	UFUNCTION(BlueprintCallable)
		void SendGeneralEventToPhoton(FGeneralEventParams GeneralEventParams, bool bSelfReceive = false);

private:

	bool bIsLocal = true;
	FString Name;
	FString Id;
	int Number;
	UPhotonNetwork* PhotonNetwork;
	bool bRoomMaster = false;
	bool bIsInRoom = false;

};
