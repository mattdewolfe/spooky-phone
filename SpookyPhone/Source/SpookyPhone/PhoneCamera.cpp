#include "SpookyPhone.h"
#include "PhoneCamera.h"

#pragma region init/shutdown

APhoneCamera::APhoneCamera(const FObjectInitializer &_obj)
	{

	}

void APhoneCamera::BeginPlay()
{
	

	//default to normal filter.
	currentFilter = FilterType::NORMAL;

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
	case NORMAL:
		temp.VignetteIntensity = 0.0f;
		temp.VignetteColor = FLinearColor(0.0f, 0.0f, 0.0f);
		temp.GrainIntensity = 0.0f;
		temp.SceneColorTint = FLinearColor(1.0f, 1.0f, 1.0f);
		temp.FilmSaturation = 0.0;
		temp.FilmContrast = 0.0f; 
		break;
	case NIGHTVISION:
		temp.VignetteIntensity = 0.8f;
		temp.VignetteColor = FLinearColor(0.0f, 0.0f, 0.0f);
		temp.GrainIntensity = 0.8f;
		temp.SceneColorTint = FLinearColor(0.2f, 1.0f, 0.0f);
		temp.FilmSaturation = 0.0;
		temp.FilmContrast = 0.0f;
		break;
	case SPOOKY:
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
	//move this object to the location and orientation of the player. 

	//set the frustum to take in what the phone camera sees. 

	//snap a screenshot, save it to a texture. 

	//save that texture into our vector of pictures. 

	//play a snapshot sound

	//return render target to phone. 
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

#pragma endregion

//KW 




