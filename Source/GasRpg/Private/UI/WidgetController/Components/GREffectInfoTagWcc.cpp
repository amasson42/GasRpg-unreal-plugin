// Amasson


#include "UI/WidgetController/Components/GREffectInfoTagWcc.h"
#include "AbilitySystem/GRAbilitySystemComponent.h"
#include "GasRpgGameplayTags.h"


void UGREffectInfoTagWcc::BroadcastValues()
{

}

void UGREffectInfoTagWcc::BindCallbacksToDependencies()
{
    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->OnEffectAssetTags.AddLambda([this](const FGameplayTagContainer& AssetTags) {
            for (const FGameplayTag& AssetTag : AssetTags)
            {
                if (AssetTag.MatchesTag(FGRGameplayTags::Get().Effect_Info))
                {
                    OnNewEffectInfoTag.Broadcast(AssetTag);
                }
            }
        });
    }
}
