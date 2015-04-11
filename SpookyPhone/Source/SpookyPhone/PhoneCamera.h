// KW 
// Camera for the in-game phone.
// Acts as a scenecapture2d that renders to the surface of the phone (always, if active). Sometimes it's 'live' (when looking through the camera)
// and sometimes it's 'static' (when browsing the gallery). Becomes active when the camera or gallery apps are selected.
// always located in 'front' of the phone and rotates with the players rotation/phone; locked there?

#pragma once

//standard includes
#include <vector>
#include <memory>
#include <algorithm>

//Engine includes.
#include "Engine/SceneCapture2D.h"
#include "PhoneCamera.generated.h"

//typedefing shared pointers to Textures for pictures.
//change these to the material proper and delete the temporary texture as you go -> vector of materials instead. 
typedef UMaterialInstanceDynamic* materialPTR;
typedef std::vector<materialPTR>::iterator materialIT;

//filters. 
// NORMAL - standard camera, no changes.
// NIGHTVISION - mostly dark, highlights spec as green, reflects certain things especially?
// SPOOKY - reveals hidden 'spooky' things, including hints and general fuckery. 
UENUM(BlueprintType)
enum class FilterType : uint8
{
	VE_NORMAL		UMETA(DisplayName = "Normal"),
	VE_NIGHT		UMETA(DisplayName = "Night Vision"),
	VE_SPOOKY		UMETA(DisplayName = "Spooky"),
	VE_MAX			UMETA(Hidden)
};


UCLASS()
class SPOOKYPHONE_API APhoneCamera : public ASceneCapture2D
{
	GENERATED_BODY()

private:
	//holds the textures of the taken photographs so they can be redisplayed on the phone. 
	std::vector<materialPTR> pictureGallery;
protected:
	//
public:
	//constructor.
	APhoneCamera(const FObjectInitializer& ObjectInitializer);

	//keeps track of filters that can be applied to camera as needed; affects the playback/tint or whatnot.d
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	TEnumAsByte<FilterType> currentFilter;

	//constructor.
	//APhoneCamera(const FObjectInitializer &_obj);
	//maybe takes in what it is going to be locked to and its render target. 
	void BeginPlay() override;
	//destructore. 
	//flushes out that vector, anything else this happens to store. 
	void BeginDestroy() override;

	//changes the display mode to another filter type. 
	void SwitchFilter(FilterType _new);

	//takes a picture, saves it as a texture.
	UFUNCTION(BlueprintCallable, Category = TEST)
	bool TakePicture();
	//displays the picture on the phone.
	UFUNCTION(BlueprintCallable, Category = TEST)
	UMaterialInstanceDynamic* DisplayPicture(int32 _index);
	//pops a given picture from the vector.
	UFUNCTION(BlueprintCallable, Category = TEST)
	bool DeletePicture(int32 _index);
	UFUNCTION(BlueprintCallable, Category = TEST)
	bool DeleteAllPictures();

	UMaterial* cameraMaterial;
	UTextureRenderTarget2D* renderTarget;
};
