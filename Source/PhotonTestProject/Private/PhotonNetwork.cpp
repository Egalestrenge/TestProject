// Fill out your copyright notice in the Description page of Project Settings.


#include "PhotonNetwork.h"

////
//// LOBBY LISTENER  //////////////////////////////////////////////////////////////////////////
////

PhotonNetworkLobbyListener::PhotonNetworkLobbyListener(UPhotonNetwork* Network)
{
	this->PhotonNetwork = Network;
}

PhotonNetworkLobbyListener::~PhotonNetworkLobbyListener(void)
{
	delete PhotonNetwork;
}

void PhotonNetworkLobbyListener::debugReturn(int debugLevel, const ExitGames::Common::JString& string)
{
}

void PhotonNetworkLobbyListener::connectionErrorReturn(int errorCode)
{
	//UE_LOG(LogTemp, Error, TEXT("Connection error returned number %d"), errorCode);
}

void PhotonNetworkLobbyListener::clientErrorReturn(int errorCode)
{
	//UE_LOG(LogTemp, Error, TEXT("Client error number %d"), errorCode);
}

void PhotonNetworkLobbyListener::warningReturn(int warningCode)
{
	//UE_LOG(LogTemp, Error, TEXT("Warning number %d"), warningCode);
}

void PhotonNetworkLobbyListener::serverErrorReturn(int errorCode)
{
	//UE_LOG(LogTemp, Error, TEXT("Server error number %d"),errorCode);
}

void PhotonNetworkLobbyListener::joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player)
{
	
}

void PhotonNetworkLobbyListener::leaveRoomEventAction(int playerNr, bool isInactive)
{
	
}

void PhotonNetworkLobbyListener::customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent)
{
}

void PhotonNetworkLobbyListener::connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& region, const ExitGames::Common::JString& cluster)
{
	if (errorCode == 0)
	{
		PhotonNetwork->PlayerClient->setAutoJoinLobby(true);
		PhotonNetwork->PlayerClient->connect();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Connection error code: %d"), errorCode);
	}

}

void PhotonNetworkLobbyListener::disconnectReturn(void)
{
}

void PhotonNetworkLobbyListener::createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
{
	/*if (errorCode == 0) {
		PhotonNetwork->RoomCreated.Broadcast(localPlayerNr);
	}*/
	//UE_LOG(LogTemp, Warning, TEXT("Create room"));
}

void PhotonNetworkLobbyListener::joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
{
	//UE_LOG(LogTemp, Warning, TEXT("Join or create room. Error code: %d"),errorCode);
}

void PhotonNetworkLobbyListener::joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
{
	
}

void PhotonNetworkLobbyListener::joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
{
}

void PhotonNetworkLobbyListener::leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
}

void PhotonNetworkLobbyListener::gotQueuedReturn(void)
{
}

void PhotonNetworkLobbyListener::joinLobbyReturn(void)
{
}

void PhotonNetworkLobbyListener::leaveLobbyReturn(void)
{	
}

void PhotonNetworkLobbyListener::onRoomListUpdate(void)
{
	//UE_LOG(LogTemp, Warning, TEXT("Room list updated"));
	PhotonNetwork->RoomList = PhotonNetwork->LobbyClient->getRoomList();
}

void PhotonNetworkLobbyListener::onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
	//UE_LOG(LogTemp, Error, TEXT("Lobby stats updated"));
}

void PhotonNetworkLobbyListener::onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
}

void PhotonNetworkLobbyListener::onRoomPropertiesChange(const ExitGames::Common::Hashtable& changes)
{
	
}

////
//// PLAYER LISTENER  //////////////////////////////////////////////////////////////////////////
////

PhotonNetworkPlayerListener::PhotonNetworkPlayerListener(UPhotonNetwork* Network)
{
	this->PhotonNetwork = Network;
}

PhotonNetworkPlayerListener::~PhotonNetworkPlayerListener(void)
{
	delete PhotonNetwork;
}

void PhotonNetworkPlayerListener::debugReturn(int debugLevel, const ExitGames::Common::JString& string)
{
}

void PhotonNetworkPlayerListener::connectionErrorReturn(int errorCode)
{
	//UE_LOG(LogTemp, Error, TEXT("Connection error returned number %d"), errorCode);
}

void PhotonNetworkPlayerListener::clientErrorReturn(int errorCode)
{
	//UE_LOG(LogTemp, Error, TEXT("Client error number %d"), errorCode);
}

void PhotonNetworkPlayerListener::warningReturn(int warningCode)
{
	//UE_LOG(LogTemp, Error, TEXT("Warning number %d"), warningCode);
}

void PhotonNetworkPlayerListener::serverErrorReturn(int errorCode)
{
	//UE_LOG(LogTemp, Error, TEXT("Server error number %d"),errorCode);
}

void PhotonNetworkPlayerListener::joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player)
{
	PhotonNetwork->PlayerJoinedCurrentRoom.Broadcast(playerNr);
}

void PhotonNetworkPlayerListener::leaveRoomEventAction(int playerNr, bool isInactive)
{
	PhotonNetwork->PlayerLeftCurrentRoom.Broadcast(playerNr);
}

void PhotonNetworkPlayerListener::customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent)
{
	if (eventCode == PlayerEventCodes::PlayerPing) {

		Hashtable EventProperties = ValueObject<Hashtable>(eventContent).getDataCopy(); 

		FVector SpawnTransformLocation = FVector();
		PhotonGeneralFunctionality::GetUnrealPropertyFromHashtable(EventProperties, SpawnTransformLocation, "SpawnTransformLocation");
		
		float Size = 0;
		PhotonGeneralFunctionality::GetUnrealPropertyFromHashtable(EventProperties, Size, "Size");
		
		float Thickness = 0;
		PhotonGeneralFunctionality::GetUnrealPropertyFromHashtable(EventProperties, Thickness, "Thickness");
		
		FLinearColor Color = FLinearColor();
		PhotonGeneralFunctionality::GetUnrealPropertyFromHashtable(EventProperties, Color, "Color");
		
		PhotonNetwork->PlayerPingEvent.Broadcast(playerNr, SpawnTransformLocation, Size, Thickness, Color);
	}

	else if (eventCode == PlayerEventCodes::RoomMasterChangedLevel) {

		Hashtable EventProperties = ValueObject<Hashtable>(eventContent).getDataCopy();
		FString DestinationLevel = FString();
		PhotonGeneralFunctionality::GetUnrealPropertyFromHashtable(EventProperties, DestinationLevel, "DestinationLevel");

		PhotonNetwork->RoomMasterChangedLevel.Broadcast(DestinationLevel);

	}
	else if (eventCode == PlayerEventCodes::GeneralEvent) {

		PhotonNetwork->GeneralEventReceived.Broadcast(FGeneralEventParams(ValueObject<Hashtable>(eventContent).getDataCopy()));

	}
}

void PhotonNetworkPlayerListener::connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& region, const ExitGames::Common::JString& cluster)
{	
	if (errorCode == 0)
	{
		PhotonNetwork->PlayerClient->getLocalPlayer().addCustomProperty("IsRoomMaster", false);
		PhotonNetwork->ConnectionSuccess.Broadcast();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Connection error code: %d"), errorCode);
	}	
}

void PhotonNetworkPlayerListener::disconnectReturn(void)
{
}

void PhotonNetworkPlayerListener::createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
{
	if (errorCode == 0) {
		PhotonNetwork->RoomCreated.Broadcast(localPlayerNr, true);
	}
	else {
		PhotonNetwork->RoomCreated.Broadcast(localPlayerNr, false);
	}
}

void PhotonNetworkPlayerListener::joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
{
	//UE_LOG(LogTemp, Warning, TEXT("Join or create room. Error code: %d"),errorCode);
}

void PhotonNetworkPlayerListener::joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
{
	if (errorCode == 0) {
		MutableRoom CurrentRoom = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom();

		const JString* PlayerListC = ValueObject<JString*>(CurrentRoom.getCustomProperties().getValue("PlayerList")).getDataCopy();
		int PlayerListLength = ValueObject<int>(CurrentRoom.getCustomProperties().getValue("PlayerListLength")).getDataCopy();
		JVector<JString> JPlayerList = JVector<JString>(PlayerListC, PlayerListLength);
		JPlayerList.addElement(PhotonNetwork->PlayerClient->getLocalPlayer().getName());
		const JString* ConstPlayerListC = JPlayerList.getCArray();

		Hashtable CustomProperties = Hashtable();
		CustomProperties.put("PlayerList", ConstPlayerListC, JPlayerList.getSize());
		CustomProperties.put("PlayerListLength", PlayerListLength + 1);

		CurrentRoom.mergeCustomProperties(CustomProperties,gameProperties);

		//CurrentRoom.addCustomProperties(CustomProperties);

		PhotonNetwork->UpdateConnection();

		PhotonNetwork->RoomJoined.Broadcast(localPlayerNr);
	}
	//UE_LOG(LogTemp, Warning, TEXT("Join room"));
}

void PhotonNetworkPlayerListener::joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString)
{
}

void PhotonNetworkPlayerListener::leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
	PhotonNetwork->RoomLeft.Broadcast();
}

void PhotonNetworkPlayerListener::gotQueuedReturn(void)
{
}

void PhotonNetworkPlayerListener::joinLobbyReturn(void)
{
}

void PhotonNetworkPlayerListener::leaveLobbyReturn(void)
{
	
}

void PhotonNetworkPlayerListener::onRoomListUpdate(void)
{
	
}

void PhotonNetworkPlayerListener::onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
	//UE_LOG(LogTemp, Error, TEXT("Lobby stats updated"));
}

void PhotonNetworkPlayerListener::onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
}

void PhotonNetworkPlayerListener::onRoomPropertiesChange(const ExitGames::Common::Hashtable& changes)
{
	//UE_LOG(LogTemp, Warning, TEXT("Room property changed"));
	PhotonNetwork->RoomPropertiesChanged.Broadcast();
}

void PhotonNetworkPlayerListener::onPlayerPropertiesChange(int PlayerNr, const ExitGames::Common::Hashtable& changes)
{
	if (changes.getValue(JString("AvatarURL"))) {
		JString URLJstring = ValueObject<JString>(changes.getValue(JString("AvatarURL"))).getDataCopy();
		UTF8String URLUTF8String = URLJstring.UTF8Representation();
		FString URLString = FString(URLUTF8String.cstr());
		PhotonNetwork->URLReceived.Broadcast(PlayerNr,URLString);
	}
}


////
//// PHOTON NETWORK  //////////////////////////////////////////////////////////////////////////
////

void UPhotonNetwork::SetNetworkParams(FString AppIdStr, FString AppVerStr)
{	
	this->AppID = JString(TCHAR_TO_UTF8(*AppIdStr));	
	this->AppVer = JString(TCHAR_TO_UTF8(*AppVerStr));

	//Set lobby network
	LobbyListener = new PhotonNetworkLobbyListener(this);
	LobbyClient = new ExitGames::LoadBalancing::Client(*LobbyListener, AppID, AppVer);
	LobbyClient->setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS)); // that instance of LoadBalancingClient and its implementation details
	ExitGames::Common::Base::setListener(LobbyListener);
	ExitGames::Common::Base::setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS)); // all classes that inherit from Base

	//Set player network
	PlayerListener = new PhotonNetworkPlayerListener(this);
	PlayerClient = new ExitGames::LoadBalancing::Client(*PlayerListener, AppID, AppVer);
	PlayerClient->setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS)); // that instance of LoadBalancingClient and its implementation details
	ExitGames::Common::Base::setListener(PlayerListener);
	ExitGames::Common::Base::setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS)); // all classes that inherit from Base

}

void UPhotonNetwork::Connect()
{
	LobbyClient->setAutoJoinLobby(true);
	LobbyClient->connect();

	/*if (!NetworkClient->connect()) {
		UE_LOG(LogTemp, Error, TEXT("Error connecting to Photon servers"));
	}*/	
}

void UPhotonNetwork::UpdateConnection()
{
	LobbyClient->service();
	PlayerClient->service();
	//UE_LOG(LogTemp, Warning, TEXT("CLient state: %d"), NetworkClient->getState());
	
}

TArray<FRoom> UPhotonNetwork::GetRoomList()
{
	TArray<FRoom> RoomArray = TArray<FRoom>();
	if (!RoomList.getIsEmpty()) {
		for (int i = 0; i < (int)RoomList.getSize(); i++) {
			RoomArray.Add(FRoom(RoomList[i]));
		}
	}
	return RoomArray;
}

void UPhotonNetwork::CreateRoom(FRoom Room, bool bIsVisible)
{
	RoomOptions PhotonRoomOptions = RoomOptions(bIsVisible, Room.bIsOpen, Room.MaxPlayers);
	//PhotonRoomOptions.setLobbyType(LobbyType::DEFAULT);
	const char* RoomName = TCHAR_TO_UTF8(*Room.RoomName);
	JString LevelName = JString(TCHAR_TO_UTF8(*Room.LevelName));

	Hashtable RoomCustomProperties;
	JString UserID = PlayerClient->getLocalPlayer().getName();

	JVector<JString> PlayerListJVector = JVector<JString>();
	PlayerListJVector.addElement(UserID);

	const JString* PlayerList = PlayerListJVector.getCArray();

	RoomCustomProperties.put("LevelName", LevelName);
	RoomCustomProperties.put("PlayerList", PlayerList, PlayerListJVector.getSize());
	RoomCustomProperties.put("PlayerListLength", 1);
	PhotonRoomOptions.setCustomRoomProperties(RoomCustomProperties);
	JVector<JString> CustomPropertiesListed = JVector<JString>();
	CustomPropertiesListed.addElement("LevelName");
	CustomPropertiesListed.addElement("PlayerList");
	CustomPropertiesListed.addElement("PlayerListLength");
	PhotonRoomOptions.setPropsListedInLobby(CustomPropertiesListed);
	PhotonRoomOptions.setPublishUserID(true);

	PlayerClient->opCreateRoom(RoomName, PhotonRoomOptions);
	
}

void UPhotonNetwork::JoinRoom(FString RoomName)
{
	PlayerClient->opJoinRoom(JString(TCHAR_TO_UTF8(*RoomName)));
}

void UPhotonNetwork::LeaveRoom()
{
	MutableRoom CurrentRoom = PlayerClient->getCurrentlyJoinedRoom();

	const JString* PlayerListC = ValueObject<JString*>(CurrentRoom.getCustomProperties().getValue("PlayerList")).getDataCopy();
	int PlayerListLength = ValueObject<int>(CurrentRoom.getCustomProperties().getValue("PlayerListLength")).getDataCopy();
	JVector<JString> JPlayerList = JVector<JString>(PlayerListC, PlayerListLength);

	JPlayerList.removeElement(PlayerClient->getLocalPlayer().getName());
	const JString* ConstPlayerListC = JPlayerList.getCArray();

	Hashtable CustomProperties = Hashtable();
	CustomProperties.put("PlayerList", ConstPlayerListC, JPlayerList.getSize());
	CustomProperties.put("PlayerListLength", PlayerListLength-1);	

	Hashtable gameProperties = CurrentRoom.getCustomProperties();
	CurrentRoom.mergeCustomProperties(CustomProperties, gameProperties);

	PlayerClient->opLeaveRoom();
}

FRoom UPhotonNetwork::GetCurrentRoomInfo()
{
	if (!PlayerClient->getIsInLobby()) {
		return FRoom(&PlayerClient->getCurrentlyJoinedRoom());
	}
	else {
		return FRoom();
	}
	
}

void UPhotonNetwork::SetPlayerName(FString PlayerName)
{
	const char* PlayerNameChar = TCHAR_TO_UTF8(*PlayerName);
	PlayerClient->getLocalPlayer().setName(JString(PlayerNameChar));
}

UPhotonPlayer* UPhotonNetwork::GetLocalPhotonPlayer()
{
	MutablePlayer LocalPlayer = PlayerClient->getLocalPlayer();

	JString PlayerIDJString = LocalPlayer.getName();
	JString PlayerNameJString = LocalPlayer.getUserID();

	if (&PlayerIDJString != nullptr && &PlayerNameJString != nullptr) {
		UTF8String utf8Name = LocalPlayer.getName().UTF8Representation();
		UTF8String utf8Id = LocalPlayer.getUserID().UTF8Representation();
		FString Name = FString(utf8Name.cstr());
		FString Id = FString(utf8Id.cstr());
		UPhotonPlayer* LocalPhotonPlayer = NewObject<UPhotonPlayer>();
		bool bRoomMaster = ValueObject<bool>(LocalPlayer.getCustomProperties().getValue("IsRoomMaster")).getDataCopy();
		LocalPhotonPlayer->InitializePhotonPlayer(true, Name, Id, LocalPlayer.getNumber(), this, bRoomMaster, !PlayerClient->getIsInLobby());

		return LocalPhotonPlayer;
	}
	else {
		return NewObject<UPhotonPlayer>();
	}

	
}

UPhotonPlayer* UPhotonNetwork::GetRoomPhotonPlayer(int PlayerNr)
{
	const Player* RoomPlayer = PlayerClient->getCurrentlyJoinedRoom().getPlayerForNumber(PlayerNr);
	UTF8String utf8Name = RoomPlayer->getName().UTF8Representation();
	UTF8String utf8Id = RoomPlayer->getUserID().UTF8Representation();
	FString Name = FString(utf8Name.cstr());
	FString Id = FString(utf8Id.cstr());
	UPhotonPlayer* RoomPhotonPlayer = NewObject<UPhotonPlayer>();
	bool bRoomMaster = ValueObject<bool>(RoomPlayer->getCustomProperties().getValue("IsRoomMaster")).getDataCopy();
	RoomPhotonPlayer->InitializePhotonPlayer(false, Name, Id, PlayerNr, this, bRoomMaster, true);	
	return RoomPhotonPlayer;
}

TArray<UPhotonPlayer*> UPhotonNetwork::GetRoomPhotonPlayers()
{
	TArray<UPhotonPlayer*> RoomPlayers = TArray<UPhotonPlayer*>();

	JVector<Player*> RoomPhotonPlayers = PlayerClient->getCurrentlyJoinedRoom().getPlayers();

	JString LocalPlayerID = PlayerClient->getUserID();



	for (int i = 0; i < (int)RoomPhotonPlayers.getSize(); i++) {

		UPhotonPlayer* RoomPlayer = NewObject<UPhotonPlayer>();
		bool bRoomMaster = ValueObject<bool>(RoomPhotonPlayers[i]->getCustomProperties().getValue("IsRoomMaster")).getDataCopy();
		if (RoomPhotonPlayers[i]->getUserID() != LocalPlayerID) {
			RoomPlayer->InitializePhotonPlayer(RoomPhotonPlayers[i], false, this, bRoomMaster, true);
			//UE_LOG(LogTemp, Warning, TEXT("GetLocalPhotonPlayers"));
		}
		else {
			RoomPlayer->InitializePhotonPlayer(RoomPhotonPlayers[i], true, this, bRoomMaster, true);
			//UE_LOG(LogTemp, Warning, TEXT("GetLocalPhotonPlayers"));
		}
		RoomPlayers.Add(RoomPlayer);
		
	}
	return RoomPlayers;
}

//// PHOTON PLAYER //////////////////////////////////////////////////////////////////////////

/// ROOM PROPERTIES

FVector UPhotonPlayer::GetRoomVectorProperty(FString PropertyKey)
{
	if (PhotonNetwork) {
		MutableRoom CurrentRoom = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom();
		
		Hashtable CustomProperties = CurrentRoom.getCustomProperties();

		const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));
		if (CustomProperties.getValue(Key)) {

			float* Value = ValueObject<float*>(CustomProperties.getValue(Key)).getDataCopy();
			return FVector(Value[0], Value[1], Value[2]);
		}

		else {
			return FVector();
		}

	}
	else {
		return FVector();
	}

}

void UPhotonPlayer::SetRoomVectorProperty(FString PropertyKey, FVector PropertyValue)
{
	if (PhotonNetwork) {
		const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));

		float* Value = new float[3];
		Value[0] = PropertyValue.X;
		Value[1] = PropertyValue.Y;
		Value[2] = PropertyValue.Z;

		Hashtable CustomProperties = Hashtable();
		CustomProperties.put(Key, Value, 3);

		MutableRoom CurrentRoom = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom();
		Hashtable CurrentProperties = CurrentRoom.getCustomProperties();
		CurrentRoom.mergeCustomProperties(CustomProperties,CurrentProperties);
	}

}

float UPhotonPlayer::GetRoomFloatProperty(FString PropertyKey)
{
	if (PhotonNetwork) {
	
		MutableRoom CurrentRoom = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom();

		Hashtable CustomProperties = CurrentRoom.getCustomProperties();

		const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));
		if (CustomProperties.getValue(Key)) {

			float Value = ValueObject<float>(CustomProperties.getValue(Key)).getDataCopy();
			return Value;
		}

		else {
			return 0.0f;
		}

	}
	else {
		return 0.0f;
	}
}

void UPhotonPlayer::SetRoomFloatProperty(FString PropertyKey, float PropertyValue)
{
	if (PhotonNetwork) {
		const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));

		Hashtable CustomProperties = Hashtable();
		CustomProperties.put(Key, PropertyValue);

		MutableRoom CurrentRoom = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom();
		Hashtable CurrentProperties = CurrentRoom.getCustomProperties();
		CurrentRoom.mergeCustomProperties(CustomProperties, CurrentProperties);
	}
}

int UPhotonPlayer::GetRoomIntProperty(FString PropertyKey)
{
	if (PhotonNetwork) {
		
		MutableRoom CurrentRoom = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom();

		Hashtable CustomProperties = CurrentRoom.getCustomProperties();

		const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));
		if (CustomProperties.getValue(Key)) {

			int Value = ValueObject<int>(CustomProperties.getValue(Key)).getDataCopy();
			return Value;
		}

		else {
			return 0;
		}

	}
	else {
		return 0;
	}
}

void UPhotonPlayer::SetRoomIntProperty(FString PropertyKey, int PropertyValue)
{
	if (PhotonNetwork) {
		const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));

		Hashtable CustomProperties = Hashtable();
		CustomProperties.put(Key, PropertyValue);

		MutableRoom CurrentRoom = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom();
		Hashtable CurrentProperties = CurrentRoom.getCustomProperties();
		CurrentRoom.mergeCustomProperties(CustomProperties, CurrentProperties);
	}
}

bool UPhotonPlayer::GetRoomBoolProperty(FString PropertyKey)
{
	if (PhotonNetwork) {
		
		MutableRoom CurrentRoom = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom();

		Hashtable CustomProperties = CurrentRoom.getCustomProperties();

		const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));
		if (CustomProperties.getValue(Key)) {

			bool Value = ValueObject<bool>(CustomProperties.getValue(Key)).getDataCopy();
			return Value;
		}

		else {
			return false;
		}
		

	}
	else {
		return false;
	}
}

void UPhotonPlayer::SetRoomBoolProperty(FString PropertyKey, bool PropertyValue)
{
	if (PhotonNetwork) {
		const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));

		bool Value = false;


		Hashtable CustomProperties = Hashtable();
		CustomProperties.put(Key, Value);

		MutableRoom CurrentRoom = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom();
		Hashtable CurrentProperties = CurrentRoom.getCustomProperties();
		CurrentRoom.mergeCustomProperties(CustomProperties, CurrentProperties);
	}
}

FString UPhotonPlayer::GetRoomStringProperty(FString PropertyKey)
{
	if (PhotonNetwork) {

		MutableRoom CurrentRoom = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom();

		Hashtable CustomProperties = CurrentRoom.getCustomProperties();

		const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));
		if (CustomProperties.getValue(Key)) {

			JString ValueJString = ValueObject<JString>(CustomProperties.getValue(Key)).getDataCopy();
			UTF8String ValueUTF8String = ValueJString.UTF8Representation();
			FString Value = FString(ValueUTF8String.cstr());
			return Value;
		}

		else {
			return FString();
		}


	}
	else {
		return FString();
	}
}

void UPhotonPlayer::SetRoomStringProperty(FString PropertyKey, FString PropertyValue)
{
	if (PhotonNetwork) {
		const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));

		const JString Value = JString(TCHAR_TO_UTF8(*PropertyValue));


		Hashtable CustomProperties = Hashtable();
		CustomProperties.put(Key, Value);

		MutableRoom CurrentRoom = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom();
		Hashtable CurrentProperties = CurrentRoom.getCustomProperties();
		CurrentRoom.mergeCustomProperties(CustomProperties, CurrentProperties);
	}
}

TArray<FString> UPhotonPlayer::GetRoomStringArrayProperty(FString PropertyKey, FString ArraySizeKey, int ArraySize)
{
	if (PhotonNetwork) {

		MutableRoom CurrentRoom = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom();

		Hashtable CustomProperties = CurrentRoom.getCustomProperties();

		const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));
		if (CustomProperties.getValue(Key)) {
			
			TArray<FString> Value;
			int ValueArraySize = 0;

			if (ArraySizeKey.Equals("")) {
				ValueArraySize = ArraySize;
			}
			else {
				JString ValueArraySizeKey = JString(TCHAR_TO_UTF8(*ArraySizeKey));
				PhotonGeneralFunctionality::GetUnrealPropertyFromHashtable(CustomProperties, ValueArraySize, ValueArraySizeKey);
			}

			if (ArraySize != 0) {
				PhotonGeneralFunctionality::GetUnrealPropertyFromHashtable(CustomProperties, Value, ValueArraySize, Key);
			}		

			return Value;
		}

		else {
			return TArray<FString>();
		}


	}
	else {
		return TArray<FString>();
	}
}

void UPhotonPlayer::SetRoomStringArrayProperty(FString PropertyKey, TArray<FString> PropertyValue)
{
	if (PhotonNetwork) {
		const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));
		
		JString* Value = new JString[PropertyValue.Num()];
		
		for (int i = 0; i < PropertyValue.Num(); i++) {
			Value[i] = JString(TCHAR_TO_UTF8(*PropertyValue[i]));
		}		

		Hashtable CustomProperties = Hashtable();
		CustomProperties.put(Key, Value, PropertyValue.Num());

		MutableRoom CurrentRoom = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom();
		Hashtable CurrentProperties = CurrentRoom.getCustomProperties();
		CurrentRoom.mergeCustomProperties(CustomProperties, CurrentProperties);
	}
}

/// PLAYER PROPERTIES

FVector UPhotonPlayer::GetVectorProperty(FString PropertyKey)
{
	if (PhotonNetwork) {
		const Player* PhotonPlayer = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom().getPlayerForNumber(Number);
		if (PhotonPlayer) {
			Hashtable CustomProperties = PhotonPlayer->getCustomProperties();

			const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));
			if (CustomProperties.getValue(Key)) {

				float* Value = ValueObject<float*>(CustomProperties.getValue(Key)).getDataCopy();
				return FVector(Value[0], Value[1], Value[2]);
			}

			else {
				return FVector();
			}
		}
		else {
			return FVector();
		}
		
		
	}
	else {
		return FVector();
	}
	
}

void UPhotonPlayer::SetVectorProperty(FString PropertyKey, FVector PropertyValue)
{	
	if (PhotonNetwork && bIsLocal) {
		const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));

		float* Value = new float[3];
		Value[0] = PropertyValue.X;
		Value[1] = PropertyValue.Y;
		Value[2] = PropertyValue.Z;

		Hashtable CustomProperties = Hashtable();
		CustomProperties.put(Key, Value, 3);

		MutablePlayer PhotonPlayer = PhotonNetwork->PlayerClient->getLocalPlayer();
		PhotonPlayer.mergeCustomProperties(CustomProperties);
	}

}

float UPhotonPlayer::GetFloatProperty(FString PropertyKey)
{
	if (PhotonNetwork) {
		const Player* PhotonPlayer = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom().getPlayerForNumber(Number);
		if (PhotonPlayer) {
			Hashtable CustomProperties = PhotonPlayer->getCustomProperties();

			const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));
			if (CustomProperties.getValue(Key)) {

				float Value = ValueObject<float>(CustomProperties.getValue(Key)).getDataCopy();
				return Value;
			}

			else {
				return 0.0f;
			}
		}
		else {
			return 0.0f;
		}


	}
	else {
		return 0.0f;
	}
}

void UPhotonPlayer::SetFloatProperty(FString PropertyKey, float PropertyValue)
{
	if (PhotonNetwork && bIsLocal) {
		const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));

		Hashtable CustomProperties = Hashtable();
		CustomProperties.put(Key, PropertyValue);

		MutablePlayer PhotonPlayer = PhotonNetwork->PlayerClient->getLocalPlayer();
		PhotonPlayer.mergeCustomProperties(CustomProperties);
	}
}

int UPhotonPlayer::GetIntProperty(FString PropertyKey)
{
	if (PhotonNetwork) {
		const Player* PhotonPlayer = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom().getPlayerForNumber(Number);
		if (PhotonPlayer) {
			Hashtable CustomProperties = PhotonPlayer->getCustomProperties();

			const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));
			if (CustomProperties.getValue(Key)) {

				int Value = ValueObject<int>(CustomProperties.getValue(Key)).getDataCopy();
				return Value;
			}

			else {
				return 0;
			}
		}
		else {
			return 0;
		}


	}
	else {
		return 0;
	}
}

void UPhotonPlayer::SetIntProperty(FString PropertyKey, int PropertyValue)
{
	if (PhotonNetwork && bIsLocal) {
		const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));

		Hashtable CustomProperties = Hashtable();
		CustomProperties.put(Key, PropertyValue);

		MutablePlayer PhotonPlayer = PhotonNetwork->PlayerClient->getLocalPlayer();
		PhotonPlayer.mergeCustomProperties(CustomProperties);
	}
}

bool UPhotonPlayer::GetBoolProperty(FString PropertyKey)
{
	if (PhotonNetwork) {
		const Player* PhotonPlayer = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom().getPlayerForNumber(Number);
		if (PhotonPlayer) {
			Hashtable CustomProperties = PhotonPlayer->getCustomProperties();

			const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));
			if (CustomProperties.getValue(Key)) {

				bool Value = ValueObject<bool>(CustomProperties.getValue(Key)).getDataCopy();
				return Value;
			}

			else {
				return false;
			}
		}
		else {
			return false;
		}

	}
	else {
		return false;
	}
}

void UPhotonPlayer::SetBoolProperty(FString PropertyKey, bool PropertyValue)
{
	if (PhotonNetwork && bIsLocal) {
		const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));

		bool Value = PropertyValue;


		Hashtable CustomProperties = Hashtable();
		CustomProperties.put(Key, Value);

		MutablePlayer PhotonPlayer = PhotonNetwork->PlayerClient->getLocalPlayer();
		PhotonPlayer.mergeCustomProperties(CustomProperties);
	}
}

FString UPhotonPlayer::GetStringProperty(FString PropertyKey)
{	
	if (PhotonNetwork) {
		const Player* PhotonPlayer = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom().getPlayerForNumber(Number);
		UE_LOG(LogTemp, Warning, TEXT("entro en GetStringProperty"));
		if (PhotonPlayer) {
			Hashtable CustomProperties = PhotonPlayer->getCustomProperties();

			JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));
			if (CustomProperties.getValue(Key)) {
				//UE_LOG(LogTemp, Warning, TEXT("String property key found"));
				JString ValueJString = ValueObject<JString>(CustomProperties.getValue(Key)).getDataCopy();
				UTF8String ValueUTF8String = ValueJString.UTF8Representation();
				FString Value = FString(ValueUTF8String.cstr());
				return Value;
			}

			else {
				//UE_LOG(LogTemp, Warning, TEXT("String property key NOT found"));
				return FString();
			}
		}
		else {
			return FString();
		}

	}
	else {
		return FString();
	}
}

void UPhotonPlayer::SetStringProperty(FString PropertyKey, FString PropertyValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("llamo a SetStringProperty"));
	if (PhotonNetwork && bIsLocal) {
		//UE_LOG(LogTemp, Warning, TEXT("entro en SetStringProperty"));
		JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));

		JString Value = JString(TCHAR_TO_UTF8(*PropertyValue));

		Hashtable CustomProperties = Hashtable();
		CustomProperties.put(Key, Value);

		MutablePlayer PhotonPlayer = PhotonNetwork->PlayerClient->getLocalPlayer();
		PhotonPlayer.addCustomProperties(CustomProperties);		

	}
}

TArray<FString> UPhotonPlayer::GetStringArrayProperty(FString PropertyKey, FString ArraySizeKey, int ArraySize)
{
	if (PhotonNetwork) {

		const Player* PhotonPlayer = PhotonNetwork->PlayerClient->getCurrentlyJoinedRoom().getPlayerForNumber(Number);
		if (PhotonPlayer) {

			Hashtable CustomProperties = PhotonPlayer->getCustomProperties();

			const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));
			if (CustomProperties.getValue(Key)) {

				TArray<FString> Value;
				int ValueArraySize = 0;

				if (ArraySizeKey.Equals("")) {
					ValueArraySize = ArraySize;
				}
				else {
					JString ValueArraySizeKey = JString(TCHAR_TO_UTF8(*ArraySizeKey));
					PhotonGeneralFunctionality::GetUnrealPropertyFromHashtable(CustomProperties, ValueArraySize, ValueArraySizeKey);
				}

				if (ArraySize != 0) {
					PhotonGeneralFunctionality::GetUnrealPropertyFromHashtable(CustomProperties, Value, ValueArraySize, Key);
				}

				return Value;
			}

			else {
				return TArray<FString>();
			}
		}

		else {
			return TArray<FString>();
		}


	}
	else {
		return TArray<FString>();
	}
}

void UPhotonPlayer::SetStringArrayProperty(FString PropertyKey, TArray<FString> PropertyValue)
{
	if (PhotonNetwork && bIsLocal) {
		const JString Key = JString(TCHAR_TO_UTF8(*PropertyKey));

		JString* Value = new JString[PropertyValue.Num()];

		for (int i = 0; i < PropertyValue.Num(); i++) {
			JString ValueJString = JString(TCHAR_TO_UTF8(*PropertyValue[i]));
			Value[i] = ValueJString;
		}

		Hashtable CustomProperties = Hashtable();
		CustomProperties.put(Key, Value, PropertyValue.Num());

		MutablePlayer PhotonPlayer = PhotonNetwork->PlayerClient->getLocalPlayer();
		PhotonPlayer.mergeCustomProperties(CustomProperties);
	}
}



void UPhotonPlayer::SpawnPingInPhoton(FVector SpawnTransformLocation, float Size, float Thickness, FLinearColor Color)
{
	Hashtable EventParams = Hashtable();
	
	PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(EventParams, SpawnTransformLocation, "SpawnTransformLocation");
	PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(EventParams, Size, "Size");
	PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(EventParams, Thickness, "Thickness");
	PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(EventParams, Color, "Color");

	PhotonNetwork->PlayerClient->opRaiseEvent(true, EventParams, PlayerEventCodes::PlayerPing);
}

void UPhotonPlayer::RoomMasterChangedLevelInPhoton(FString DestinationLevel)
{
	Hashtable EventParams = Hashtable();

	PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(EventParams, DestinationLevel, "DestinationLevel");

	PhotonNetwork->PlayerClient->opRaiseEvent(true, EventParams, PlayerEventCodes::RoomMasterChangedLevel);
}

void UPhotonPlayer::SendGeneralEventToPhoton(FGeneralEventParams GeneralEventParams, bool bSelfReceive)
{

	int GeneralEventCode = GeneralEventParams.GeneralEventCode;
	TMap<FString, bool> EventBoolParams = GeneralEventParams.EventBoolParams;
	TMap<FString, int> EventIntParams = GeneralEventParams.EventIntParams;
	TMap<FString, float> EventFloatParams = GeneralEventParams.EventFloatParams;
	TMap<FString, FVector> EventVectorParams = GeneralEventParams.EventVectorParams;
	TMap<FString, FLinearColor> EventColorParams = GeneralEventParams.EventColorParams;
	TMap<FString, FString> EventStringParams = GeneralEventParams.EventStringParams;

	Hashtable EventParams = Hashtable();
	PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(EventParams, GeneralEventCode, JString("GeneralEventCode"));	

	if (!EventBoolParams.IsEmpty()) {

		TArray<FString> Keys;
		EventBoolParams.GenerateKeyArray(Keys);		

		for(FString Key : Keys) {
			FString NewKey = Key + "_BOOL_";
			PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(EventParams, EventBoolParams[Key], JString(TCHAR_TO_UTF8(*NewKey)));
		}
	}

	if (!EventIntParams.IsEmpty()) {

		TArray<FString> Keys;
		EventIntParams.GenerateKeyArray(Keys);

		for (FString Key : Keys) {
			FString NewKey = Key + "_INT_";
			PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(EventParams, EventIntParams[Key], JString(TCHAR_TO_UTF8(*NewKey)));
		}
	}

	if (!EventFloatParams.IsEmpty()) {

		TArray<FString> Keys;
		EventFloatParams.GenerateKeyArray(Keys);

		for (FString Key : Keys) {
			FString NewKey = Key + "_FLOAT_";
			PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(EventParams, EventFloatParams[Key], JString(TCHAR_TO_UTF8(*NewKey)));
		}
	}

	if (!EventVectorParams.IsEmpty()) {

		TArray<FString> Keys;
		EventVectorParams.GenerateKeyArray(Keys);

		for (FString Key : Keys) {
			FString NewKey = Key + "_VECTOR_";
			PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(EventParams, EventVectorParams[Key], JString(TCHAR_TO_UTF8(*NewKey)));
		}
	}

	if (!EventColorParams.IsEmpty()) {

		TArray<FString> Keys;
		EventColorParams.GenerateKeyArray(Keys);

		for (FString Key : Keys) {
			FString NewKey = Key + "_COLOR_";
			PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(EventParams, EventColorParams[Key], JString(TCHAR_TO_UTF8(*NewKey)));
		}
	}

	if (!EventStringParams.IsEmpty()) {

		TArray<FString> Keys;
		EventStringParams.GenerateKeyArray(Keys);

		for (FString Key : Keys) {
			FString NewKey = Key + "_STRING_";
			PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(EventParams, EventStringParams[Key], JString(TCHAR_TO_UTF8(*NewKey)));
		}
	}
	RaiseEventOptions EventOptions = RaiseEventOptions();

	if (bSelfReceive) {
		EventOptions.setReceiverGroup(ExitGames::Lite::ReceiverGroup::ALL);
	}
	else {
		EventOptions.setReceiverGroup(ExitGames::Lite::ReceiverGroup::OTHERS);
	}
	
	PhotonNetwork->PlayerClient->opRaiseEvent(true, EventParams, PlayerEventCodes::GeneralEvent, EventOptions);
	
}

void PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(Hashtable& PropertiesHashtable, bool NewProperty, JString NewPropertyKey)
{
	PropertiesHashtable.put(NewPropertyKey, NewProperty);
}

void PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(Hashtable& PropertiesHashtable, FVector NewProperty, JString NewPropertyKey)
{
	float* NewPropertyValue = new float[3];
	NewPropertyValue[0] = NewProperty.X;
	NewPropertyValue[1] = NewProperty.Y;
	NewPropertyValue[2] = NewProperty.Z;

	PropertiesHashtable.put(NewPropertyKey, NewPropertyValue, 3);
}

void PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(Hashtable& PropertiesHashtable, FLinearColor NewProperty, JString NewPropertyKey)
{
	float* NewPropertyValue = new float[4];
	NewPropertyValue[0] = NewProperty.R;
	NewPropertyValue[1] = NewProperty.G;
	NewPropertyValue[2] = NewProperty.B;
	NewPropertyValue[3] = NewProperty.A;

	PropertiesHashtable.put(NewPropertyKey, NewPropertyValue, 4);
}

void PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(Hashtable& PropertiesHashtable, float NewProperty, JString NewPropertyKey)
{
	PropertiesHashtable.put(NewPropertyKey, NewProperty);
}

void PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(Hashtable& PropertiesHashtable, int NewProperty, JString NewPropertyKey)
{
	PropertiesHashtable.put(NewPropertyKey, NewProperty);
}

void PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(Hashtable& PropertiesHashtable, FString NewProperty, JString NewPropertyKey)
{
	JString NewPropertyValue = JString(TCHAR_TO_UTF8(*NewProperty));
	PropertiesHashtable.put(NewPropertyKey, NewPropertyValue);

}

void PhotonGeneralFunctionality::PutUnrealPropertyToHashtable(Hashtable& PropertiesHashtable, TArray<FString> NewProperty, JString NewPropertyKey)
{
	JVector<JString> NewPropertyValueJVector;
	for (FString TArrayElem : NewProperty) {
		NewPropertyValueJVector.addElement(JString(TCHAR_TO_UTF8(*TArrayElem)));
	}
	const JString* NewPropertyValue = NewPropertyValueJVector.getCArray();
	PropertiesHashtable.put(NewPropertyKey, NewPropertyValue, NewPropertyValueJVector.getSize());

}

bool PhotonGeneralFunctionality::GetUnrealPropertyFromHashtable(Hashtable& PropertiesHashtable, bool& Property, JString PropertyKey)
{
	if (PropertiesHashtable.getValue(PropertyKey)) {

		bool Value = ValueObject<bool>(PropertiesHashtable.getValue(PropertyKey)).getDataCopy();
		Property = Value;

		return true;
	}

	else {
		return false;
	}
}
bool PhotonGeneralFunctionality::GetUnrealPropertyFromHashtable(Hashtable& PropertiesHashtable, FVector& Property, JString PropertyKey)
{

	if (PropertiesHashtable.getValue(PropertyKey)) {

		float* Value = ValueObject<float*>(PropertiesHashtable.getValue(PropertyKey)).getDataCopy();
		Property.X = Value[0];
		Property.Y = Value[1];
		Property.Z = Value[2];

		return true;
	}

	else {
		return false;
	}

}

bool PhotonGeneralFunctionality::GetUnrealPropertyFromHashtable(Hashtable& PropertiesHashtable, FLinearColor& Property, JString PropertyKey)
{
	if (PropertiesHashtable.getValue(PropertyKey)) {

		float* Value = ValueObject<float*>(PropertiesHashtable.getValue(PropertyKey)).getDataCopy();
		Property.R = Value[0];
		Property.G = Value[1];
		Property.B = Value[2];
		Property.A = Value[3];

		return true;
	}

	else {
		return false;
	}
}

bool PhotonGeneralFunctionality::GetUnrealPropertyFromHashtable(Hashtable& PropertiesHashtable, float& Property, JString PropertyKey)
{
	if (PropertiesHashtable.getValue(PropertyKey)) {

		float Value = ValueObject<float>(PropertiesHashtable.getValue(PropertyKey)).getDataCopy();		
		Property = Value;

		return true;
	}

	else {
		return false;
	}
}

bool PhotonGeneralFunctionality::GetUnrealPropertyFromHashtable(Hashtable& PropertiesHashtable, int& Property, JString PropertyKey)
{
	if (PropertiesHashtable.getValue(PropertyKey)) {

		int Value = ValueObject<int>(PropertiesHashtable.getValue(PropertyKey)).getDataCopy();
		Property = Value;

		return true;
	}

	else {
		return false;
	}
}

bool PhotonGeneralFunctionality::GetUnrealPropertyFromHashtable(Hashtable& PropertiesHashtable, FString& Property, JString PropertyKey)
{
	if (PropertiesHashtable.getValue(PropertyKey)) {
		
		JString ValueJString = ValueObject<JString>(PropertiesHashtable.getValue(PropertyKey)).getDataCopy();
		UTF8String ValueUTF8String = ValueJString.UTF8Representation();
		FString Value = FString(ValueUTF8String.cstr());

		Property = Value;

		return true;
	}

	else {
		return false;
	}
}

bool PhotonGeneralFunctionality::GetUnrealPropertyFromHashtable(Hashtable& PropertiesHashtable, TArray<FString>& Property, int ArraySize, JString PropertyKey)
{
	if (PropertiesHashtable.getValue(PropertyKey)) {

		Property.Empty();
		
		JString* ValueJStringArray = ValueObject<JString*>(PropertiesHashtable.getValue(PropertyKey)).getDataCopy();
		for (int i = 0; i < ArraySize; i++) {
			UTF8String ValueUTF8String = ValueJStringArray[i].UTF8Representation();
			FString Value = FString(ValueUTF8String.cstr());
			Property.Add(Value);
		}

		return true;
	}

	else {
		return false;
	}
}

bool PhotonGeneralFunctionality::GetMapFromHashtable(Hashtable& PropertiesHashtable, TMap<FString, bool>& PropertiesMap)
{
	JVector Keys = PropertiesHashtable.getKeys();
	bool KeyFound = false;

	for (int i = 0; i < (int)Keys.getSize(); i++) {

		JString KeyChar = KeyObject<JString>(Keys[i]).getDataCopy();
		UTF8String KeyUTF8String = KeyChar.UTF8Representation();
		FString Key = FString(KeyUTF8String.cstr());

		if (Key.Contains("_BOOL_")) {

			PropertiesMap.Add(Key.Replace(TEXT("_BOOL_"), TEXT("")), ValueObject<bool>(PropertiesHashtable.getValue(Keys[i])).getDataCopy());
			KeyFound = true;
		}

	}
	return KeyFound;
}

bool PhotonGeneralFunctionality::GetMapFromHashtable(Hashtable& PropertiesHashtable, TMap<FString, int>& PropertiesMap)
{
	JVector Keys = PropertiesHashtable.getKeys();
	bool KeyFound = false;
	
	for (int i = 0; i < (int)Keys.getSize(); i++) {

		JString KeyChar = KeyObject<JString>(Keys[i]).getDataCopy();
		UTF8String KeyUTF8String = KeyChar.UTF8Representation();
		FString Key = FString(KeyUTF8String.cstr());

		if (Key.Contains("_INT_")) {

			PropertiesMap.Add(Key.Replace(TEXT("_INT_"),TEXT("")),ValueObject<int>(PropertiesHashtable.getValue(Keys[i])).getDataCopy());
			KeyFound = true;
		}			

	}
	return KeyFound;
}

bool PhotonGeneralFunctionality::GetMapFromHashtable(Hashtable& PropertiesHashtable, TMap<FString, float>& PropertiesMap)
{
	JVector<Object> Keys = PropertiesHashtable.getKeys();
	bool KeyFound = false;

	for (int i = 0; i < (int)Keys.getSize(); i++) {

		JString KeyChar = KeyObject<JString>(Keys[i]).getDataCopy();
		UTF8String KeyUTF8String = KeyChar.UTF8Representation();
		FString Key = FString(KeyUTF8String.cstr());

		if (Key.Contains("_FLOAT_")) {

			PropertiesMap.Add(Key.Replace(TEXT("_FLOAT_"), TEXT("")), ValueObject<float>(PropertiesHashtable.getValue(Keys[i])).getDataCopy());
			KeyFound = true;
		}

	}
	return KeyFound;
}

bool PhotonGeneralFunctionality::GetMapFromHashtable(Hashtable& PropertiesHashtable, TMap<FString, FVector>& PropertiesMap)
{
	JVector Keys = PropertiesHashtable.getKeys();
	bool KeyFound = false;

	for (int i = 0; i < (int)Keys.getSize(); i++) {

		JString KeyChar = KeyObject<JString>(Keys[i]).getDataCopy();
		UTF8String KeyUTF8String = KeyChar.UTF8Representation();
		FString Key = FString(KeyUTF8String.cstr());

		if (Key.Contains("_VECTOR_")) {

			FVector VectorValue = FVector();
			GetUnrealPropertyFromHashtable(PropertiesHashtable, VectorValue, KeyChar);
			PropertiesMap.Add(Key.Replace(TEXT("_VECTOR_"), TEXT("")), VectorValue);
			KeyFound = true;
		}

	}
	return KeyFound;
}

bool PhotonGeneralFunctionality::GetMapFromHashtable(Hashtable& PropertiesHashtable, TMap<FString, FLinearColor>& PropertiesMap)
{
	JVector Keys = PropertiesHashtable.getKeys();
	bool KeyFound = false;

	for (int i = 0; i < (int)Keys.getSize(); i++) {

		JString KeyChar = KeyObject<JString>(Keys[i]).getDataCopy();
		UTF8String KeyUTF8String = KeyChar.UTF8Representation();
		FString Key = FString(KeyUTF8String.cstr());

		if (Key.Contains("_COLOR_")) {

			FLinearColor ColorValue = FLinearColor();
			GetUnrealPropertyFromHashtable(PropertiesHashtable, ColorValue, KeyChar);
			PropertiesMap.Add(Key.Replace(TEXT("_COLOR_"), TEXT("")), ColorValue);
			KeyFound = true;
		}

	}
	return KeyFound;
}

bool PhotonGeneralFunctionality::GetMapFromHashtable(Hashtable& PropertiesHashtable, TMap<FString, FString>& PropertiesMap)
{
	JVector Keys = PropertiesHashtable.getKeys();
	bool KeyFound = false;

	for (int i = 0; i < (int)Keys.getSize(); i++) {

		JString KeyChar = KeyObject<JString>(Keys[i]).getDataCopy();
		UTF8String KeyUTF8String = KeyChar.UTF8Representation();
		FString Key = FString(KeyUTF8String.cstr());

		if (Key.Contains("_STRING_")) {

			FString StringValue = FString();
			GetUnrealPropertyFromHashtable(PropertiesHashtable, StringValue, KeyChar);
			PropertiesMap.Add(Key.Replace(TEXT("_STRING_"), TEXT("")), StringValue);
			KeyFound = true;
		}

	}
	return KeyFound;
}

bool PhotonGeneralFunctionality::GetMapFromHashtable(Hashtable& PropertiesHashtable, TMap<FString, TArray<FString>>& PropertiesMap, bool IsArraySizeInHash, TArray<int> ArraySizes)
{
	JVector Keys = PropertiesHashtable.getKeys();
	bool KeyFound = false;

	if (IsArraySizeInHash) {

		for (int i = 0; i < (int)Keys.getSize(); i++) {

			JString KeyChar = KeyObject<JString>(Keys[i]).getDataCopy();			
			UTF8String KeyUTF8String = KeyChar.UTF8Representation();
			FString Key = FString(KeyUTF8String.cstr());

			if (Key.Contains("_STRING_ARRAY_")) {

				JString SizeKey = KeyChar.concat("SIZE_");
				int ArraySize = 0;
				GetUnrealPropertyFromHashtable(PropertiesHashtable, ArraySize, SizeKey);

				TArray<FString> StringArrayValue = TArray<FString>();
				GetUnrealPropertyFromHashtable(PropertiesHashtable, StringArrayValue,ArraySize, KeyChar);

				PropertiesMap.Add(Key.Replace(TEXT("_STRING_ARRAY_"), TEXT("")), StringArrayValue);
				KeyFound = true;
			}

		}

	}
	else {

		int SizeIndex = -1;

		for (int i = 0; i < (int)Keys.getSize(); i++) {

			JString KeyChar = KeyObject<JString>(Keys[i]).getDataCopy();
			UTF8String KeyUTF8String = KeyChar.UTF8Representation();
			FString Key = FString(KeyUTF8String.cstr());
			
			if (Key.Contains("_STRING_ARRAY_")) {
				
				SizeIndex++;
				int ArraySize = ArraySizes[SizeIndex];				

				TArray<FString> StringArrayValue = TArray<FString>();
				GetUnrealPropertyFromHashtable(PropertiesHashtable, StringArrayValue, ArraySize, KeyChar);

				PropertiesMap.Add(Key.Replace(TEXT("_STRING_ARRAY_"), TEXT("")), StringArrayValue);
				KeyFound = true;
			}

		}
	}
	
	return KeyFound;
}
