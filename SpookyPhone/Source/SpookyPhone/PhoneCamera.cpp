#include "SpookyPhone.h"
#include "PhoneCamera.h"

#pragma region init/shutdown

void APhoneCamera::BeginPlay()
{
	//default to normal filter.
	currentFilter = FilterType::VE_NORMAL;

	//load textures if any saved (stretch goal), if not then make a new vector. 
	pictureGallery = std::vector<texturePTR>();

	//call the super? 
	Super::BeginPlay();
}

void APhoneCamera::BeginDestroy()
{
	//cleaning up texture vector as needed. 
	if (pictureGallery.size() > 0)
	{
		while (!pictureGallery.back())
		{
			///release hold on texture. 
			pictureGallery.back().reset();
			//remove object from vector.
			pictureGallery.pop_back();
		}
	}
	//call the super? 
	UnregisterAllComponents();
	Super::BeginDestroy();
}

#pragma endregion 

#pragma region filters

void APhoneCamera::SwitchFilter(FilterType _new)
{
	//sets it to another filter.
	currentFilter = _new;

	FPostProcessSettings temp = this->GetCaptureComponent2D()->PostProcessSettings;

	//adjust camera options according to the currentFilter (tiny, staticyness, etc.)
	switch (currentFilter)
	{
	case FilterType::VE_NORMAL:
		temp.VignetteIntensity = 0.0f;
		temp.VignetteColor = FLinearColor(0.0f, 0.0f, 0.0f);
		temp.GrainIntensity = 0.0f;
		temp.SceneColorTint = FLinearColor(1.0f, 1.0f, 1.0f);
		temp.FilmSaturation = 0.0;
		temp.FilmContrast = 0.0f; 
		break;
	case FilterType::VE_NIGHT:
		temp.VignetteIntensity = 0.8f;
		temp.VignetteColor = FLinearColor(0.0f, 0.0f, 0.0f);
		temp.GrainIntensity = 0.8f;
		temp.SceneColorTint = FLinearColor(0.2f, 1.0f, 0.0f);
		temp.FilmSaturation = 0.0;
		temp.FilmContrast = 0.0f;
		break;
	case FilterType::VE_SPOOKY:
		temp.VignetteIntensity = 0.0f;
		temp.VignetteColor = FLinearColor(0.0f, 0.0f, 0.0f);
		temp.GrainIntensity = 2.0f;
		temp.SceneColorTint = FLinearColor(1.0f, 0.155f, 1.0f);
		temp.FilmSaturation = 1.5;
		temp.FilmContrast = 1.0f;
		break;
	default:
		break;
	}

	this->GetCaptureComponent2D()->PostProcessSettings = temp;
}

#pragma endregion

#pragma region pictures

bool APhoneCamera::TakePicture()
{
	//snap a screenshot, save it to a texture. 
	UTextureRenderTarget2D* tempRAW = new UTextureRenderTarget2D(FObjectInitializer());
	tempRAW = this->GetCaptureComponent2D()->TextureTarget;

	//create a material with the texture data. 
	std::string ts = "Material'/Game/Materials/kwParentGalleryMaterial.kwParentGalleryMaterial'";
	std::wstring ws(ts.begin(), ts.end());
	UMaterialInstance *tempMaterialInstance = LoadObject<UMaterialInstance>(NULL, ws.c_str()); // Returns NULL ?
	UMaterialInstanceDynamic *dynamicMaterialInstance = UMaterialInstanceDynamic::Create(UMaterial::GetDefaultMaterial(MD_Surface), tempMaterialInstance);
	dynamicMaterialInstance->SetTextureParameterValue("temptexture", tempRAW);

	//push the material into our vector thereof. 
	//pictureGallery.push_back(tempSHARED);

	//play a snapshot sound
	GEngine->AddOnScreenDebugMessage(3, 5.0f, FColor::Red, "Click!");

	//clean up pointers. 
	delete tempRAW;

	return true;
}

texturePTR APhoneCamera::DisplayPicture(int _index)
{
	//display the picture at a given index on the phone. 
	
	//also display left/right arrows so the user can cycle through their pictures.

	//display delete button, allows deletion of current photograph.

	//play a swipe noise if swiped to left/right.

	return NULL;
}

bool APhoneCamera::DeletePicture(int _index)
{
	//play a noise and return false if there is no picture to delete.

	//removes a picture from the vector. 
	
	//displays next photograph in gallery if possible; if none exists, go to the previous one.

	//play a noise if needed.

	return true;
}

//removes all items from the picture gallery vector. 
bool APhoneCamera::DeleteAllPictures()
{
	//don't need to delete the pointers because they're shared.
	//clearing the photo gallery ought to be sufficient.
	pictureGallery.clear();

	//if the gallery is empty, return true. 
	if (pictureGallery.empty())
	{
		return true;
	}
	
	//default return.
	return false;
}

#pragma endregion

//KW 




