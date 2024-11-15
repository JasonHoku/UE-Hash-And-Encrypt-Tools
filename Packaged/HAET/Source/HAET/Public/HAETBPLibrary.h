// By Jason Hoku Levien, Published 2024	

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "HAETBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UHAETBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()


	UFUNCTION(BlueprintCallable, Category = "Bytes Array To String")
	static FString ConvertBytesToString(TArray <uint8> In);

	UFUNCTION(BlueprintCallable, Category = "String To Array Of Bytes")
	static TArray<uint8> ConvertStringToBytes(FString InString);

	UFUNCTION(BlueprintCallable, Category = "Save AOB To File")
	static FString SaveArrayOfBytesToFile(TArray <uint8> In, FString SavePath);

	UFUNCTION(BlueprintCallable, Category = "Save AOB To File")
	static TArray <uint8> LoadArrayOfBytesFromFile(FString FileName, FString SavePath);

	UFUNCTION(BlueprintCallable, Category = "Custom Encrypt String")
	static FString CustomEncryptString(FString InString);


	UFUNCTION(BlueprintCallable, Category = "Custom Encrypt String")
	static FString CustomDecryptString(FString InString);



	UFUNCTION(BlueprintCallable, Category = "Generate Encryption String")
	static FString GenerateRandomString(int Length);

	UFUNCTION(BlueprintCallable, Category = "Hash String")
	static FString ConvertStringToHash(FString InString);


};

