// By Jason Hoku Levien, Published 2024

#include "HAETBPLibrary.h"
#include "HAET.h"

#include "Serialization/BufferArchive.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/SecureHash.h"
#include "Internationalization/TextKey.h"
#include "Json.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Misc/SecureHash.h" 

UHAETBPLibrary::UHAETBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}



FString UHAETBPLibrary::ConvertBytesToString(TArray <uint8> In)
{
	FString contents;
	FFileHelper::BufferToString(contents, In.GetData(), In.Num());

	FString BuiltString;

	for (int i = 0; i < In.Num(); i++) {


		BuiltString = BuiltString + FString::FromInt((int32)In[i]);


	}


	return contents;

}







FString UHAETBPLibrary::CustomEncryptString(FString InString)
{
	FString alphanum = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ//=-_//\\,+:;<=>?!\'()*+,-.[]!@#$%^&*";
	FString outChars = "";

	if (InString.Len() < 2) {
		return  " ";
	}

	while (InString.Len() > alphanum.Len()) {
		alphanum += alphanum;
	}

	for (int i = 0; i < InString.Len(); ++i) {


		FString gotLetter = FString(InString.Mid(i, 1));

		int32 gotIndex = alphanum.Find(gotLetter);
		outChars += " " + FString::FromInt(gotIndex) + "";

	}


	return outChars;
}

FString UHAETBPLibrary::CustomDecryptString(FString InString)
{
	FString alphanum = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ//=-_//\\,+:;<=>?!\'()*+,-.[]!@#$%^&*";
	FString outString = "";

	TArray<FString> parts;
	InString.ParseIntoArray(parts, TEXT(" "), true);

	for (const FString& part : parts)
	{
		if (part.IsNumeric())
		{
			int32 index = FCString::Atoi(*part);
			if (index >= 0 && index < alphanum.Len())
			{
				outString += alphanum.Mid(index, 1);
			}
		}
	}

	return outString;
}



FString UHAETBPLibrary::ConvertStringToHash(FString InString)
{
	// Log the input string
	UE_LOG(LogTemp, Warning, TEXT("ConvertStringToHash: %s"), *InString);

	// Convert FString to a byte array
	TArray<uint8> StringBytes;
	StringBytes.Append((const uint8*)TCHAR_TO_ANSI(*InString), InString.Len());

	// Create an MD5 hash object
	FMD5 Md5Gen;

	// Update MD5 with the byte array
	Md5Gen.Update(StringBytes.GetData(), StringBytes.Num());

	// Finalize the MD5 hash into a digest
	uint8 Digest[16];
	Md5Gen.Final(Digest);

	// Convert digest to FString
	FString OutHash;
	for (int i = 0; i < 16; ++i)
	{
		OutHash += FString::Printf(TEXT("%02x"), Digest[i]);
	}

	// Log the hashed string
	UE_LOG(LogTemp, Warning, TEXT("Hashed String: %s"), *OutHash);

	return OutHash;
}


FString UHAETBPLibrary::GenerateRandomString(int Length)
{
	FString alphanum = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ//=-_//\\,+:;<=>?!\'()*+,-.[]!@#$%^&*";

	FString generatedString = "";

	for (int i = 0; i < Length; ++i) {

		generatedString = generatedString + alphanum[1 + (rand() % (alphanum.Len() - 2))];


	}


	return generatedString;
}

TArray<uint8> UHAETBPLibrary::ConvertStringToBytes(FString InString)
{

	uint32 size = InString.Len();
	TArray<uint8> data;
	data.AddUninitialized(size);
	StringToBytes(InString, data.GetData(), size);
	return data;

}

FString UHAETBPLibrary::SaveArrayOfBytesToFile(TArray <uint8> In, FString SavePath) {
	FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()) + TEXT("/GameData/credKey.txt");

	FFileHelper::SaveArrayToFile(In, *FilePath);
	return "True!";

}

TArray <uint8> UHAETBPLibrary::LoadArrayOfBytesFromFile(FString FileName, FString SavePath) {
	FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()) + TEXT("/GameData/credKey.txt");

	TArray <uint8> gotData;
	FFileHelper::LoadFileToArray(gotData, *FilePath);
	return gotData;


}