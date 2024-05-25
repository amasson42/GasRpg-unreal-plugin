// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * How to use:
 * To define an expression that should execute on all attribute
 * 
 * 1. Create a macro that takes two parameters
 * #define MyDefinition(AttributeName, CategoryName, AttributeSetClass) \
 *  std::cout << "I love my " << #AttributeName << " that belongs to " << #CategoryName << " from " << #AttributeSetClass << std::endl; \
 * 
 * 2. Use the correct FOREACH call
 * FOREACH_ATTRIBUTE_All(MyDefinition)
 * 
 * 3. Attributes list are All, Vital, Primary, Secondary, Meta, Replicated, Stats
 * 
*/

/**
 * Some files are using attribute set list boilerplate and may have to be modified manually.
 * To find them, search for the text:
 * [MainAttributeListBoilerplate]
*/

#define FOREACH_ATTRIBUTE_Vital(FunctionExpression) \
    FunctionExpression(Health, Vital) \
    FunctionExpression(MaxHealth, Vital) \
    FunctionExpression(Mana, Vital) \
    FunctionExpression(MaxMana, Vital) \
    FunctionExpression(Stamina, Vital) \
    FunctionExpression(MaxStamina, Vital) \

#define FOREACH_ATTRIBUTE_Vital_NoMax(FunctionExpression) \
    FunctionExpression(Health, Vital) \
    FunctionExpression(Mana, Vital) \
    FunctionExpression(Stamina, Vital) \

#define FOREACH_ATTRIBUTE_Primary(FunctionExpression) \
    FunctionExpression(Strength, Primary) \
    FunctionExpression(Dexterity, Primary) \
    FunctionExpression(Intelligence, Primary) \

#define FOREACH_ATTRIBUTE_Secondary(FunctionExpression) \
    FunctionExpression(MovementSpeed, Secondary) \
    FunctionExpression(HealthRegeneration, Secondary) \
    FunctionExpression(ManaRegeneration, Secondary) \
    FunctionExpression(StaminaRegeneration, Secondary) \

#define FOREACH_ATTRIBUTE_Meta(FunctionExpression) \
    FunctionExpression(IncomingDamage, Meta) \

#define FOREACH_ATTRIBUTE_Replicated(FunctionExpression) \
    FOREACH_ATTRIBUTE_Vital(FunctionExpression) \
    FOREACH_ATTRIBUTE_Primary(FunctionExpression) \
    FOREACH_ATTRIBUTE_Secondary(FunctionExpression) \

#define FOREACH_ATTRIBUTE_Stats(FunctionExpression) \
    FOREACH_ATTRIBUTE_Primary(FunctionExpression) \
    FOREACH_ATTRIBUTE_Secondary(FunctionExpression) \

#define FOREACH_ATTRIBUTE_All(FunctionExpression) \
    FOREACH_ATTRIBUTE_Vital(FunctionExpression) \
    FOREACH_ATTRIBUTE_Primary(FunctionExpression) \
    FOREACH_ATTRIBUTE_Secondary(FunctionExpression) \
    FOREACH_ATTRIBUTE_Meta(FunctionExpression) \
