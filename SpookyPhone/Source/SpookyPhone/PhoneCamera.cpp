#include "SpookyPhone.h"
#include "PhoneCamera.h"

#pragma region init/shutdown

APhoneCamera::APhoneCamera(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FObjectFinder<UMaterial> camMat(TEXT("Material'/Game/Materials/PhoneCamera_Mat'"));
	cameraMaterial = camMat.Object;

	ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> target(TEXT("Material'/Game/Textures/PhoneCamera'"));
	renderTarget = target.Object;

	this->GetCaptureComponent2D()->TextureTarget = renderTarget;
}

void APhoneCamera::BeginPlay()
{
	//default to normal filter.
	currentFilter = FilterType::VE_NORMAL;

	//load textures if any saved (stretch goal), if not then make a new vector. 
	pictureGallery = std::vector<materialPTR>();

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
			delete pictureGallery.back();
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
	pictureGallery.push_back(dynamicMaterialInstance);

	//tempRAW->ReleaseResource();
	
	//clean up pointers. 
	//delete tempRAW;

	numPictures++;

	return true;
}

UMaterialInstanceDynamic* APhoneCamera::DisplayPicture(int32 _index)
{
	//make sure it is a viable index. 
	if (pictureGallery.size() > _index)
	{
		return NULL;
	}

	//display the picture at a given index on the phone. 
	return pictureGallery[_index];
}

bool APhoneCamera::DeletePicture(int32 _index)
{
	//play a noise and return false if there is no picture to delete.
	if (pictureGallery.size() == 0 || pictureGallery.size() > _index)
	{
		return false;
	}

	//removes a picture from the vector. 
	pictureGallery.erase(pictureGallery.begin() + _index);

	return true;
}

//removes all items from the picture gallery vector. 
bool APhoneCamera::DeleteAllPictures()
{
	//don't need to delete the pointers because they're shared.
	//clearing the photo gallery ought to be sufficient.
	if (pictureGallery.size() > 0)
	{
		while (!pictureGallery.back())
		{
			///release hold on texture. 
			delete pictureGallery.back();
			//remove object from vector.
			pictureGallery.pop_back();
		}
	}

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




