# Gas Rpg



## How to install

1. Add the plugin
2. Add the lines
```ini
# Config/DefaultGame.ini
[/Script/GameplayAbilities.AbilitySystemGlobals]
AbilitySystemGlobalsClassName="/Script/GasRpg.GasRpgAbilitySystemGlobals"
```
3. Set the asset manager class
```ini
# Config/DefaultEngine.ini
[/Script/Engine.Engine]
AssetManagerClassName=/Script/GasRpg.GasRpgAssetManager
bUseFixedFrameRate=True
```
